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

#include "playlist.h"
#include "threadParms.h"
#include "commandFactory.h"
#include "popup.h"
#include "timestamp.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <time.h>

using namespace std;
#define X2DELAY 3000000
#define X4DELAY 8000000
#define X8DELAY 25000000
#define FFWAIT 500000

Playlist::Playlist(mpd_Connection* mpd, SDL_Surface* screen, TTF_Font* font, Config& config, SDL_Rect& rect, int skipVal, int numPerScreen)
: Scroller(mpd, screen, font, rect, config, skipVal, numPerScreen)
, m_curElapsed(0)
, m_view(0)
, m_random(false)
, m_otg(false)
, m_modified(false)
, m_name("")
, m_moveTo(-1)
, m_moveFrom(-1)
, m_refresh(true)
{
	m_origY = m_destRect.y;
	m_config.getItemAsColor("sk_main_backColor", m_backColor.r, m_backColor.g, m_backColor.b);
	m_config.getItemAsColor("sk_main_itemColor", m_itemColor.r, m_itemColor.g, m_itemColor.b);
	m_config.getItemAsColor("sk_main_curItemBackColor", m_curItemBackColor.r, m_curItemBackColor.g, m_curItemBackColor.b);
	m_config.getItemAsColor("sk_main_curItemColor", m_curItemColor.r, m_curItemColor.g, m_curItemColor.b);

	load("");
	m_timer.stop();
}

void Playlist::saveState(ofstream& ommcState)
{
	ommcState << "plview=" << m_view << endl;

	mpd_sendRmCommand(m_mpd, ".ommcPL");
	mpd_finishCommand(m_mpd);
	mpd_sendSaveCommand(m_mpd, ".ommcPL");
	mpd_finishCommand(m_mpd);
}

void Playlist::loadState(Config& stateConfig)
{
	m_view = stateConfig.getItemAsNum("plview");
	mpd_sendClearCommand(m_mpd);
	mpd_finishCommand(m_mpd);
	mpd_sendLoadCommand(m_mpd, ".ommcPL");	
	mpd_finishCommand(m_mpd);
}

void Playlist::load(std::string dir)
{
	if(!dir.empty()) { //load playlist from disk
	}
	mpd_sendPlaylistInfoCommand(m_mpd, -1);
cout <<"here" <<endl;
	//m_path = dir;
	m_listing.clear();	
	m_songsInfo.clear();
	mpd_InfoEntity* mpdItem = mpd_getNextInfoEntity(m_mpd);
	while(mpdItem != NULL) {
		std::string item = "";
		int type = mpdItem->type;
		if(type == 1) {
			if(m_view == 0 && mpdItem->info.song->title != NULL
						   && mpdItem->info.song->artist != NULL) { //Artist - Title
				item = mpdItem->info.song->title;
				item = " - " + item;
				item = mpdItem->info.song->artist + item;
			} else if(m_view ==1 && mpdItem->info.song->title != NULL) { //Title
				item = mpdItem->info.song->title;
			} else {
				item = mpdItem->info.song->file;
			}
			int pos = item.rfind("/");;
			if(pos != string::npos) {
				item = item.substr(pos+1);
			}
			m_listing.push_back(make_pair(item, type));
			songInfo_t song;
			if(mpdItem->info.song->title != NULL)
				song.title  = mpdItem->info.song->title;
			else 
				song.title  = mpdItem->info.song->file;
			if(mpdItem->info.song->artist != NULL)
				song.artist  = mpdItem->info.song->artist;
			song.file  = mpdItem->info.song->file;
			m_songsInfo.push_back(song);
			mpd_freeInfoEntity(mpdItem);
			mpdItem = mpd_getNextInfoEntity(m_mpd);
		} else {
			throw runtime_error("Unknown mpd entity for playlist");
		}
	}
//	mpd_finishCommand(m_mpd);

	m_lastItemNum = m_listing.size()-1;
}

void Playlist::makeNowPlayingVisible()
{
	if(m_nowPlaying < m_topItemNum ||
		m_nowPlaying > m_topItemNum + m_numPerScreen) {

		m_topItemNum  = m_nowPlaying - (m_numPerScreen/2);
	}

}

bool Playlist::showSaveDialog(Popup& popup)
{
	bool show = false;	
	
	Scroller::listing_t items;
	int type = Popup::POPUP_LIST;
	if(!m_name.empty())
		items.push_back(make_pair(m_name, type));	
			
	int num = m_config.getItemAsNum("nextPlaylistNum");
	ostringstream numStr;
	numStr << num;
	items.push_back(make_pair("playlist_" + numStr.str(), (int)Popup::POPUP_DO_SAVE_PL)); 
	items.push_back(make_pair("Cancel", (int)Popup::POPUP_CANCEL)); 
	popup.setItemsText(items, type);
	SDL_Rect popRect;
	popRect.w = 180;
	popRect.h = m_skipVal*5+15;
	popRect.x = (m_screen->w - popRect.w) / 2;
	popRect.y = (m_screen->h - popRect.h) / 2;
	popup.setSize(popRect);
	popup.setTitle("Save Playlist As...");
	show = true;

	return show;
}

void Playlist::setNextNumOnSave()
{
	int num = m_config.getItemAsNum("nextPlaylistNum");
	
	++num;
	ostringstream numStr;
	numStr << num;
	m_config.setItem("nextPlaylistNum", numStr.str().c_str());
	m_config.saveConfigFile();
//	m_config.readConfigFile();
}

int Playlist::getRand(int max)
{
    /* r is a random floating point value in the range [0,1) {including 0, not including 1}. Note we must convert rand() and/or RAND_MAX+1 to floating point values to avoid integer division. In addition, Sean Scanlon pointed out the possibility that RAND_MAX may be the largest positive integer the architecture can represent, so (RAND_MAX+1) may result in an overflow, or more likely the value will end up being the largest negative integer the architecture can represent, so to avoid this we convert RAND_MAX and 1 to doubles before adding. */
	double r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
   /* x is a random integer in the range [0,M) {including 0, not including M}. If M is an integer then the range is [0,M-1] {inclusive} */
    int x = (int)(r * (max));
	return x;
}

void Playlist::initRandomPlaylist()
{
	m_random = true;
	time_t t = time(NULL);
	srand(t);
	mpd_sendListallCommand(m_mpd, "");

	m_listing.clear();	
	m_all.clear();
	mpd_InfoEntity* mpdItem = mpd_getNextInfoEntity(m_mpd);
	int i = 0;
	while(mpdItem != NULL) {
		std::string item = "";
		if(mpdItem->type == 1) {
			item = mpdItem->info.song->file;
			m_all.push_back(item);	
		}	
		mpdItem = mpd_getNextInfoEntity(m_mpd);
	}

	int size = m_all.size();
	for(int i=0; i<65; ++i) {
		mpd_sendAddCommand(m_mpd, m_all[getRand(size)].c_str());	
		mpd_finishCommand(m_mpd);
	}
	m_otg = true;
	load("");
}

void Playlist::initNewPlaylist()
{
	m_otg = true;
}

void Playlist::initName(std::string name)
{
	m_name = name;
}

std::string Playlist::currentItemName()
{
	return m_curItemName;
}
std::string Playlist::currentItemPath()
{
	return m_curDir+m_curItemName;

}

std::string Playlist::nowPlayingTitle(int song)
{
	if(song == -1) {
		song = m_nowPlaying;
	}

	if(song <= m_songsInfo.size() && !m_songsInfo.empty())
		return m_songsInfo[song].title;
	else 
		return "";
}

std::string Playlist::nowPlayingArtist(int song)
{
	if(song == -1) {
		song = m_nowPlaying;
	}

	if(song <= m_songsInfo.size() && !m_songsInfo.empty())
		return m_songsInfo[song].artist;
	else 
		return "";
}

std::string Playlist::nowPlayingFile(int song)
{
	if(song == -1) {
		song = m_nowPlaying;
	}

	if(song <= m_songsInfo.size() && !m_songsInfo.empty())
		return m_songsInfo[song].file;
	else 
		return "";
}

std::string Playlist::nowPlayingFormat(int song)
{
	if(song == -1) {
		song = m_nowPlaying;
	}

	if(song <= m_songsInfo.size() && !m_songsInfo.empty()) {
		string title =  m_songsInfo[song].file;
		int pos = title.rfind('.');
		string ext = title.substr(pos+1);
		if(ext == "mp3")
			ext = " MP3";
		else if(ext == "ogg")
			ext = " OGG";
		else if(ext == "mp4" || ext == "m4p" || ext == "m4a")
			ext = " AAC";
		else if (ext == "flac")
			ext = "FLAC";
		else if (ext.length() == 2)
			ext = "  " + ext;
		else if (ext.length() == 3)
			ext = " " + ext;

		return ext;
	}
	else 
		return "";
}

void Playlist::updateStatus(int mpdStatusChanged, mpd_Status* mpdStatus,
							int rtmpdStatusChanged, mpd_Status* rtmpdStatus, int repeatDelay)
{
	mpd_Status * status;
	int statusChanged;

	if(rtmpdStatusChanged > 0) {
		status = rtmpdStatus;
		statusChanged = rtmpdStatusChanged;
	} else {
		status = mpdStatus;
		statusChanged = mpdStatusChanged;
	}

	if(statusChanged & PL_CHG) {
		load("");
		m_refresh = true;
	}		
	if((statusChanged & ELAPSED_CHG) && repeatDelay == 0) { 
		m_curElapsed = status->elapsedTime;	
	}
	if(statusChanged & STATE_CHG) { 
		m_curState = status->state;
		m_refresh = true;
	}
	if(statusChanged & SONG_CHG) {
		m_nowPlaying = status->song;	
		m_curItemNum = m_nowPlaying;
		makeNowPlayingVisible();
		m_refresh = true;
/*
		if(m_random && m_safe) {
			//append new random song
			mpd_sendDeleteCommand(m_mpd, 0);
			mpd_finishCommand(m_mpd);
			mpd_sendAddCommand(m_mpd, m_all[getRand(m_all.size())].c_str());	
			mpd_finishCommand(m_mpd);
			m_safe = false;
		} else {
			m_safe = true;
		}
*/
	}

}

void Playlist::processCommand(int command, int& rtmpdStatusChanged, mpd_Status* rtmpdStatus, int repeatDelay, int volume, long delayTime)
{
	if(command > 0) {
		m_refresh = true;
		if(m_moveFrom >= 0 && command != 0 && command != CMD_UP && command != CMD_DOWN && command != CMD_MOVE_IN_PL) {
			m_moveFrom = -1;
		}	
		if(Scroller::processCommand(command)) {
			//scroller command...parent class processes
		} else if(command == CMD_PLAY_PAUSE) {
			if(m_curItemType == 1) {
				if(m_curState == MPD_STATUS_STATE_PAUSE && m_nowPlaying == m_curItemNum) {
					m_curState = MPD_STATUS_STATE_PLAY;	
					mpd_sendPauseCommand(m_mpd, 0);
					mpd_finishCommand(m_mpd);
				} else if(m_curState == MPD_STATUS_STATE_PLAY && m_nowPlaying == m_curItemNum) {
					m_curState = MPD_STATUS_STATE_PAUSE;
					mpd_sendPauseCommand(m_mpd, 1);
					mpd_finishCommand(m_mpd);
				} else {
					mpd_sendPlayCommand(m_mpd, m_curItemNum);
					mpd_finishCommand(m_mpd);
					SDL_Delay(100);
					mpd_sendSetvolCommand( m_mpd, volume);
					mpd_finishCommand(m_mpd);
				}
			}
		} else if(command == CMD_PAUSE) {
			if(m_curState == MPD_STATUS_STATE_PAUSE) {
				m_curState = MPD_STATUS_STATE_PLAY;	
				mpd_sendPauseCommand(m_mpd, 0);
				mpd_finishCommand(m_mpd);
			} else if(m_curState == MPD_STATUS_STATE_PLAY) {
				m_curState = MPD_STATUS_STATE_PAUSE;
				mpd_sendPauseCommand(m_mpd, 1);
				mpd_finishCommand(m_mpd);
			}
		} else if(command == CMD_NEXT) {
					mpd_sendPlayCommand(m_mpd, m_nowPlaying+1);
					mpd_finishCommand(m_mpd);
//			mpd_sendNextCommand(m_mpd);
//			mpd_finishCommand(m_mpd);
			mpd_sendSetvolCommand( m_mpd, volume);
			mpd_finishCommand(m_mpd);
		} else if(command == CMD_PREV) {
					mpd_sendPlayCommand(m_mpd, m_nowPlaying-1);
					mpd_finishCommand(m_mpd);
//			mpd_sendPrevCommand(m_mpd);
//			mpd_finishCommand(m_mpd);
			mpd_sendSetvolCommand( m_mpd, volume);
			mpd_finishCommand(m_mpd);
		} else if(command == CMD_FF) {
			if(repeatDelay > 0) {
				m_timer.start();
				int jump = 0;
				if(delayTime > X2DELAY) {
					if(delayTime > X8DELAY)
						jump = 16;	
					else if(delayTime > X4DELAY)
						jump = 8;	
					else
						jump = 4;
				}
				else 	
					jump = 2;
			
				if(jump > 0 && (m_timer.check() > FFWAIT)) {	
					mpd_sendSeekCommand(m_mpd, m_curItemNum, m_curElapsed + jump);
					mpd_finishCommand(m_mpd);
					m_curElapsed += jump;
					m_timer.stop();
					m_timer.start();
				}
			} 
		} else if(command == CMD_RW) {
			if(repeatDelay > 0) {
				int jump = 0;
				if(delayTime > X2DELAY) {
					if(delayTime > X8DELAY)
						jump = 16;	
					else if(delayTime > X4DELAY)
						jump = 8;	
					else
						jump = 4;
				}
				else 	
					jump = 2;
			
				if(jump > 0 && (m_timer.check() > FFWAIT)) {	
					mpd_sendSeekCommand(m_mpd, m_curItemNum, m_curElapsed - jump);
					mpd_finishCommand(m_mpd);
					m_curElapsed -= jump;
					m_timer.stop();
					m_timer.start();
				}
			}
		} else if(command == CMD_TOGGLE_VIEW) {
			if(m_view == 2)
				m_view = 0;
			else
				++m_view;

			load("");
		} else if(command == CMD_DEL_FROM_PL) {
			mpd_sendDeleteCommand(m_mpd, m_curItemNum);
			mpd_finishCommand(m_mpd);
			rtmpdStatusChanged += PL_CHG;
			mpd_sendStatusCommand(m_mpd);
			rtmpdStatus = mpd_getStatus(m_mpd);
		} else if(command == CMD_MOVE_IN_PL) {
			if(m_moveFrom >= 0) {
				m_moveTo = m_curItemNum;
				mpd_sendMoveCommand(m_mpd, m_moveFrom, m_moveTo);
				mpd_finishCommand(m_mpd);
				m_moveFrom = -1;
				rtmpdStatusChanged += PL_CHG;
				mpd_sendStatusCommand(m_mpd);
				rtmpdStatus = mpd_getStatus(m_mpd);
			} else if(command == CMD_TOGGLE_MODE) {
			} else {	
				m_moveFrom = m_curItemNum;
			}
		}
	}
}

void Playlist::draw(bool forceRefresh)
{
	if(forceRefresh || m_refresh) {
		//clear this portion of the screen 
		SDL_SetClipRect(m_screen, &m_clearRect);
		SDL_FillRect(m_screen, &m_clearRect, SDL_MapRGB(m_screen->format, m_backColor.r, m_backColor.g, m_backColor.b));
		
	if(m_listing.size() == 0) {
			SDL_Surface *sText;
			sText = TTF_RenderText_Blended(m_font, "No songs in playlist...", m_itemColor);
			SDL_BlitSurface(sText,NULL, m_screen, &m_destRect );
			SDL_FreeSurface(sText);
		}
		
		Scroller::draw();

		m_refresh = false;
	}
}
