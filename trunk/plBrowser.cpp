/*****************************************************************************************

ommpc(One More Music Player Client) - A Music Player Daemon client targetted for the gp2x

Copyright (C) 2007 - Tim Temple(codertimt@gmail.com)

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*****************************************************************************************/

#include "plBrowser.h"
#include "threadParms.h"
#include "commandFactory.h"
#include "playlist.h"
#include "keyboard.h"
#include "config.h"
#include "guiPos.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <SDL_image.h>

using namespace std;

PLBrowser::PLBrowser(mpd_Connection* mpd, SDL_Surface* screen, SDL_Surface * bg, TTF_Font* font, SDL_Rect& rect, Config& config, int skipVal, int numPerScreen, Playlist& pl, Keyboard& keyboard)
: Scroller(mpd, screen, bg, font, rect, config, skipVal, numPerScreen)
, m_playlist(pl)
, m_keyboard(keyboard)
{
	m_config.getItemAsColor("sk_main_itemColor", m_itemColor.r, m_itemColor.g, m_itemColor.b);
	m_config.getItemAsColor("sk_main_curItemColor", m_curItemColor.r, m_curItemColor.g, m_curItemColor.b);

	initItemIndexLookup();	
    ls("");
}


void PLBrowser::ls(std::string dir)
{ 
	if(m_mpd != NULL) {
		mpd_sendLsInfoCommand(m_mpd, dir.c_str());

		m_curDir = dir;
		m_listing.clear();
		m_listing.push_back(make_pair("Save Playlist", 5));	
		m_listing.push_back(make_pair("New Playlist", 3));	
		m_listing.push_back(make_pair("Random Playlist", 4));	
		m_listing.push_back(make_pair("Add All Songs", 6));	
		mpd_InfoEntity* mpdItem = mpd_getNextInfoEntity(m_mpd);
		while(mpdItem != NULL) {
			std::string item = "";
			int type = mpdItem->type;
			if(type == 2) { 
				item = mpdItem->info.playlistFile->path;
				int pos = item.rfind("/");;
				if(pos != string::npos) {
					item = item.substr(pos+1);
				}

				m_listing.push_back(make_pair(item, type));
			}
			mpd_freeInfoEntity(mpdItem);
			mpdItem = mpd_getNextInfoEntity(m_mpd);
		}
	}
	m_lastItemNum = m_listing.size()-1;
}

void PLBrowser::updateListing()
{
	ls("");
}

std::string PLBrowser::currentItemName()
{
	return m_curItemName;
}
std::string PLBrowser::currentItemPath()
{
	return m_curDir+m_curItemName;

}

void PLBrowser::updateStatus(int mpdStatusChanged, mpd_Status* mpdStatus)
{
	if(mpdStatusChanged & STATE_CHG) { 
		m_curState = mpdStatus->state;
		m_refresh = true;
	}
}

int PLBrowser::processCommand(int command, int curMode, GuiPos& guiPos)
{
	int newMode = curMode;
	if(command > 0) {
		if(command == CMD_CLICK) {
			if(guiPos.curY > m_clearRect.y && (guiPos.curY < m_clearRect.y + m_clearRect.h))	 {
				if(guiPos.curX < (m_clearRect.w-40)) {
					m_curItemNum = m_topItemNum + m_itemIndexLookup[guiPos.curY];	
					m_curItemType = m_listing[m_curItemNum].second;
					command = CMD_LOAD_PL;
				} else if(guiPos.curX > (m_clearRect.w-40)) {
					if(guiPos.curY < m_clearRect.y+40) {
						command = CMD_LEFT;
					} else if(guiPos.curY > m_clearRect.y + m_clearRect.h -40) {
						command = CMD_RIGHT;

					} 
				}
			}
		}
		m_refresh = true;
		if(Scroller::processCommand(command)) {
			//scroller command...parent class processes
		} else {
			switch(command) {
				case CMD_SAVE_PL_FROM_BROWSER:
					{
						int num = m_config.getItemAsNum("nextPlaylistNum");
						ostringstream numStr;
						numStr << num;
						string selText = "playlist_" + numStr.str(); 
						mpd_sendSaveCommand(m_mpd, m_keyboard.getText().c_str());
						mpd_finishCommand(m_mpd);
						updateListing();
						m_playlist.setNextNumOnSave(selText);
						m_refresh = true;
						newMode = CMD_HIDE_KEYBOARD;	
					}
					break;
				case CMD_LOAD_PL:
					if(m_curItemType == 2) {
						std::string pl = "";
						if(!m_curDir.empty())
							pl = m_curDir+"/";
						pl += m_curItemName;
						mpd_sendClearCommand(m_mpd);
						mpd_finishCommand(m_mpd);
						mpd_sendLoadCommand(m_mpd, pl.c_str());
						mpd_finishCommand(m_mpd);
						mpd_sendPlayCommand(m_mpd, 0);
						mpd_finishCommand(m_mpd);
						m_playlist.initName(pl);
						newMode = 1;
					} else if(m_curItemType == 3) {
						mpd_sendClearCommand(m_mpd);
						mpd_finishCommand(m_mpd);
					} else if(m_curItemType == 4) {
						mpd_sendClearCommand(m_mpd);
						mpd_finishCommand(m_mpd);
						m_playlist.initRandomPlaylist();	
						newMode = 1;
					} else if(m_curItemType == 5) {
						int num = m_config.getItemAsNum("nextPlaylistNum");
						ostringstream numStr;
						numStr << num;
						string selText = "playlist_" + numStr.str(); 
						m_keyboard.init(CMD_SAVE_PL_FROM_BROWSER, selText);
						newMode = CMD_SHOW_KEYBOARD;	
					} else if(m_curItemType == 6) {
						mpd_sendClearCommand(m_mpd);
						mpd_finishCommand(m_mpd);
						mpd_sendAddCommand(m_mpd, "/");
						mpd_finishCommand(m_mpd);
						newMode = 1;
					}
					break;
				case CMD_PAUSE:
					if(m_curState == MPD_STATUS_STATE_PAUSE) {
						m_curState = MPD_STATUS_STATE_PLAY;	
						mpd_sendPauseCommand(m_mpd, 0);
						mpd_finishCommand(m_mpd);
					} else if(m_curState == MPD_STATUS_STATE_PLAY) {
						m_curState = MPD_STATUS_STATE_PAUSE;
						mpd_sendPauseCommand(m_mpd, 1);
						mpd_finishCommand(m_mpd);
					}
					break;
				case CMD_APPEND_PL:
					if(m_curItemType == 2) {
						std::string pl = "";
						if(!m_curDir.empty())
							pl = m_curDir+"/";
						pl += m_curItemName;
						mpd_sendLoadCommand(m_mpd, pl.c_str());
						mpd_finishCommand(m_mpd);
						newMode = 1;
					}
					break;
				case CMD_DEL_PL:
					mpd_sendRmCommand(m_mpd, m_curItemName.c_str());
					mpd_finishCommand(m_mpd);
					ls("");
					break;
			}
		}
	}
	return newMode; 
}

void PLBrowser::draw(bool forceRefresh)
{
	if(forceRefresh || m_refresh) {
//		ls("");
		//clear this portion of the screen 
		SDL_SetClipRect(m_screen, &m_clearRect);
		SDL_BlitSurface(m_bg, &m_clearRect, m_screen, &m_clearRect );

		SDL_Surface *sText;
		sText = TTF_RenderText_Solid(m_font, "Playlists", m_itemColor);
		SDL_BlitSurface(sText,NULL, m_screen, &m_destRect );
		SDL_FreeSurface(sText);
		m_destRect.y += m_skipVal*2;
		m_curItemClearRect.y += m_skipVal*2;

		Scroller::draw();	
		m_refresh = false;
	}
}

