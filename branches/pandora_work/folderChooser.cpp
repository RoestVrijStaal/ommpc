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

#include "browser.h"
#include "threadParms.h"
#include "commandFactory.h"
#include "config.h"
#include "guiPos.h"
#include "songDb.h"
#include "keyboard.h"
#include "playlist.h"
#include <iostream>
#include <stdexcept>
#include <SDL_image.h>

using namespace std;

FolderChooser::FolderChooser(mpd_Connection* mpd, SDL_Surface* screen, SDL_Surface* bg, TTF_Font* font, 
				SDL_Rect& rect,	Config& config, int skipVal, int numPerScreen, SongDb& songdb, Keyboard& kb, Playlist& pl)
: Scroller(mpd, screen, bg, font, rect, config, skipVal, numPerScreen-1)
, m_nowPlaying(0)
, m_view(0)
, m_updatingDb(false)
, m_updatingSongDb(false)
, m_songDb(songdb)
, m_keyboard(kb)
, m_pl(pl)
, m_good(false)
{
}

void FolderChooser::initAll()
{
	m_config.getItemAsColor("sk_main_itemColor", m_itemColor.r, m_itemColor.g, m_itemColor.b);
	m_config.getItemAsColor("sk_main_curItemColor", m_curItemColor.r, m_curItemColor.g, m_curItemColor.b);
    
	string iconName = m_config.getItem("sk_overlay");
	m_drawIcons =  m_config.getItemAsNum("drawIcons");
	
	SDL_Surface* tmpSurface = NULL;	
	tmpSurface = IMG_Load(string("skins/icons/"+iconName+"/iconBrowse.png").c_str());
	if (!tmpSurface)
		tmpSurface = IMG_Load(string("skins/default/iconBrowse.png").c_str());
	if (!tmpSurface)
		printf("Unable to load image: %s\n", SDL_GetError());
	else {
		m_iconBrowse = SDL_DisplayFormatAlpha(tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
	
	tmpSurface = NULL;	
	tmpSurface = IMG_Load(string("skins/icons/"+iconName+"/iconFolder.png").c_str());
	if (!tmpSurface)
		tmpSurface = IMG_Load(string("skins/default/iconFolder.png").c_str());
	m_iconFolder = SDL_DisplayFormatAlpha(tmpSurface);
	SDL_FreeSurface(tmpSurface);
	
	tmpSurface = IMG_Load(string("skins/icons/"+iconName+"/iconFile.png").c_str());
	if (!tmpSurface)
		tmpSurface = IMG_Load(string("skins/default/iconFile.png").c_str());
	if (!tmpSurface)
		printf("Unable to load image: %s\n", SDL_GetError());
	else { 
		m_iconFile = SDL_DisplayFormatAlpha(tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}

	m_numPerScreen--;
	initItemIndexLookup();	
	ls("");
    //ls("tim");
    for(int i=0; i<=5; ++i)
	    m_filters.push_back("");

	m_good = true;
}

void FolderChooser::ls(std::string item)
{
	string dir;
	m_view = VIEW_FILES;
	
	switch(m_view) {
		case VIEW_FILES:
			if(m_curItemType == TYPE_BACK) {
				if(!m_prevItems.empty()) {
					m_curItemNum = m_prevItems[m_prevItems.size()-1].second;
					m_curItemName = m_prevItems[m_prevItems.size()-1].first;
					makeCurItemVisible();
					m_prevItems.pop_back();
					for(prevItems_t::iterator iIter = m_prevItems.begin();
						iIter != m_prevItems.end();
						++iIter) {
						dir += (*iIter).first + "/";
					}
					dir = dir.substr(0, dir.length()-1);
				} else {
					browseRoot();
					break;
				}
			} else if(item == m_config.getItem("LANG_FILESYSTEM")) {
				m_curItemNum = 0;
				m_topItemNum = 0;
				m_curItemName = "";
				dir = "";
			} else {
				cout << "inum " << m_curItemNum << "   iname   " << m_curItemName << endl;
				m_prevItems.push_back(make_pair(m_curItemName, m_curItemNum));
				m_curItemNum = 0;
				m_topItemNum = 0;
				for(prevItems_t::iterator iIter = m_prevItems.begin();
						iIter != m_prevItems.end();
						++iIter) {
					dir += (*iIter).first + "/";
				}
				dir = dir.substr(0, dir.length()-1);
			}
			browseFileSystem(dir);
			break;
	}
}

void FolderChooser::browseFileSystem(std::string dir) {
	mpd_sendLsInfoCommand(m_mpd, dir.c_str());
	m_curDir = dir;
	m_listing.clear();
	m_listing.push_back(make_pair("..", (int)TYPE_BACK));
	mpd_InfoEntity* mpdItem = mpd_getNextInfoEntity(m_mpd);
	while(mpdItem != NULL) {
		std::string item = "";
		int type = mpdItem->type;
		if(type == 0) {
			item = mpdItem->info.directory->path;
		} else if(type == 1) {
			item = mpdItem->info.song->file;
		} 
		/*else if(type == 2) {
			item = mpdItem->info.playlistFile->path;
		} else {
			throw runtime_error("Unknown mpd entity");
		}
		*/
		int pos = item.rfind("/");;
		if(pos != string::npos) {
			item = item.substr(pos+1);
		}
//	cout << item << endl;
		if(!item.empty()) 
			m_listing.push_back(make_pair(item, type));
		mpd_freeInfoEntity(mpdItem);
		mpdItem = mpd_getNextInfoEntity(m_mpd);
	}
	m_lastItemNum = m_listing.size()-1;
}

}

void FolderChooser::browseSongs() {
	SongDb::songsAndPaths_t songsAndPaths = m_songDb.getSongs();
	m_listing.clear();
	m_listing.push_back(make_pair("..", (int)TYPE_BACK));
	for(SongDb::songsAndPaths_t::iterator sIter = songsAndPaths.begin();
		sIter != songsAndPaths.end();
		++sIter) {
		if(!(*sIter).first.empty()) {
			m_listing.push_back(make_pair((*sIter).first, (int)TYPE_FILE));
			m_curSongPaths.push_back((*sIter).second);
		} else {
			m_listing.push_back(make_pair("FIXME filename", (int)TYPE_FILE));
			m_curSongPaths.push_back((*sIter).second);
		}
	}
	m_lastItemNum = m_listing.size()-1;
}

void FolderChooser::browseSongsByAlbum(string album, string artist) {
	if(artist == m_config.getItem("LANG_UNKNOWN"))
		artist.clear();
	SongDb::songsAndPaths_t songsAndPaths = m_songDb.getSongsInAlbum(album, artist);
	m_listing.clear();
	m_curSongPaths.clear();
	m_listing.push_back(make_pair("..", (int)TYPE_BACK));
	for(SongDb::songsAndPaths_t::iterator sIter = songsAndPaths.begin();
		sIter != songsAndPaths.end();
		++sIter) {
		if(!(*sIter).first.empty()) {
			m_listing.push_back(make_pair((*sIter).first, (int)TYPE_FILE));
			m_curSongPaths.push_back((*sIter).second);
		}
	}
	m_lastItemNum = m_listing.size()-1;
}

void FolderChooser::browseSongsByArtist(string artist) {
	SongDb::songsAndPaths_t songsAndPaths = m_songDb.getSongsForArtist(artist);
	m_listing.clear();
	m_curSongPaths.clear();
	m_listing.push_back(make_pair("..", (int)TYPE_BACK));
	for(SongDb::songsAndPaths_t::iterator sIter = songsAndPaths.begin();
		sIter != songsAndPaths.end();
		++sIter) {
		m_listing.push_back(make_pair((*sIter).first, (int)TYPE_FILE));
		m_curSongPaths.push_back((*sIter).second);
	}
	m_lastItemNum = m_listing.size()-1;
}

std::string FolderChooser::currentItemName()
{
	return m_curItemName;
}
std::string FolderChooser::currentItemPath()
{
	return m_curDir+m_curItemName;

}

void FolderChooser::updateStatus(int mpdStatusChanged, mpd_Status* mpdStatus, bool updatingSongDb)
{
	if(mpdStatusChanged & SONG_CHG) {
		m_nowPlaying = mpdStatus->song;	
	} 
	if(mpdStatusChanged & STATE_CHG) { 
		m_curState = mpdStatus->state;
		m_refresh = true;
	}
	if(mpdStatusChanged & UPDB_CHG) {
		if(mpdStatus->updatingDb == 0) 
			m_updatingDb = false;
		else
			m_updatingDb = true;
		ls("");
		m_refresh = true;	
		cout << "updating db " << m_updatingDb<<  endl;
	}
	if(m_updatingSongDb) {
		if(!updatingSongDb) {
			m_updatingSongDb = false;
			ls("");
			m_refresh = true;
		}
	} else if(!m_updatingSongDb) {
		if(updatingSongDb) {
			m_updatingSongDb = true;
			ls("");
			m_refresh = true;
		}	
	}
}

int FolderChooser::processCommand(int command, GuiPos& guiPos)
{
	int newMode = 0;
	if(command > 0) {
		m_refresh = true;
		if(command == CMD_CLICK || command == CMD_HOLD_CLICK) {
			if(guiPos.curY > m_clearRect.y && (guiPos.curY < m_clearRect.y + m_clearRect.h))	 {
				if(guiPos.curX < (m_clearRect.w-40)) {
					m_curItemNum = m_topItemNum + m_itemIndexLookup[guiPos.curY];	
					if(m_curItemNum < m_listing.size()) {
						m_curItemType = m_listing[m_curItemNum].second;
						m_curItemName = m_listing[m_curItemNum].first;
						if(command == CMD_CLICK)
							command = CMD_IMMEDIATE_PLAY;
						else {
							if(m_view != VIEW_ROOT)
								newMode = CMD_POP_CONTEXT;
						}
					} else {
						m_curItemNum = 0;
					}
				} else if(guiPos.curX > (m_clearRect.w-40)) {
					if(guiPos.curY < m_clearRect.y+40) {
						command = CMD_LEFT;
					} else if(guiPos.curY > m_clearRect.y + m_clearRect.h -40) {
						command = CMD_RIGHT;
					}
				}
			}
		}
		if(Scroller::processCommand(command)) {
			//scroller command...parent class processes
		} else {

			std::string dir;
			int pos;
			switch (command) {
				case CMD_IMMEDIATE_PLAY:
				case CMD_MOUSE_LEFT:
					if(m_curItemType == (int)TYPE_FOLDER || m_curItemType == (int)TYPE_BACK
							|| m_curItemType == (int)TYPE_ALL) { //directory
						ls(m_curItemName);
					} else if(m_curItemType == (int)TYPE_FILE) {
						std::string song = "";
						if(m_view == VIEW_FILES) {
							for(prevItems_t::iterator iIter = m_prevItems.begin();
									iIter != m_prevItems.end();
									++iIter) {
								dir += (*iIter).first + "/";
							}
							dir = dir.substr(0, dir.length()-1);
							if(!dir.empty())
								song = dir+"/";
							song += m_curItemName;
						} else {
							song = m_curSongPaths[m_curItemNum-1];
						}
						int id = mpd_sendAddIdCommand(m_mpd, song.c_str());
					cout << " id    " << id << endl;
					cout << " np    " << m_nowPlaying << endl;
						mpd_finishCommand(m_mpd);
						mpd_sendMoveIdCommand(m_mpd, id, m_nowPlaying+1);
						mpd_finishCommand(m_mpd);
						mpd_sendPlayCommand(m_mpd, m_nowPlaying+1);
						mpd_finishCommand(m_mpd);
						newMode = 1;
					} else if(m_curItemType == (int)TYPE_FILTER) {
						m_keyboard.init(CMD_FILTER_KEYBOARD, m_filters[m_view]);
						newMode = CMD_SHOW_KEYBOARD;
					}
					break;
				case CMD_QUEUE: 
					{
						if(m_curItemType == (int)TYPE_FILE) {
							std::string song = "";
							if(m_view == VIEW_FILES) {
								for(prevItems_t::iterator iIter = m_prevItems.begin();
										iIter != m_prevItems.end();
										++iIter) {
									dir += (*iIter).first + "/";
								}
								dir = dir.substr(0, dir.length()-1);
								if(!dir.empty())
									song = dir+"/";
								song += m_curItemName;
							} else {
								song = m_curSongPaths[m_curItemNum-1];
							}
							int pos = m_pl.lastQueued();
							if(pos == -1)
								pos = m_nowPlaying+1;
							else 
								++pos;

							int id = mpd_sendAddIdCommand(m_mpd, song.c_str());
							mpd_finishCommand(m_mpd);
							mpd_sendMoveIdCommand(m_mpd, id, pos);
							mpd_finishCommand(m_mpd);
							m_pl.lastQueued(pos);
							m_queued = true;
						}
					}
					break;
				case CMD_PREV_DIR:
				case CMD_MOUSE_RIGHT:
/*
					pos = m_curDir.rfind("/");;
					if(pos == string::npos || pos == 0) 
						dir = "";
					else
						dir = m_curDir.substr(0, pos);
*/
					m_curItemType = TYPE_BACK;
					
					if(m_prevItems.size() == 0) {
						m_topItemNum = 0;
						switch(m_view) {
							case VIEW_ARTISTS:
								m_curItemNum = 0;
							break;	
							case VIEW_ALBUMS:
								m_curItemNum = 1;
							break;	
							case VIEW_GENRES:
								m_curItemNum = 2;
							break;	
							case VIEW_FILES:
								m_curItemNum = 3;
							break;	
							case VIEW_SONGS:
								m_curItemNum = 4;
							break;	

						}
						m_curItemName = "";
					}
					ls("..");
					break;
				case CMD_ADD_TO_PL: 
					if(m_curItemType == (int)TYPE_FILE) {
						std::string song = "";
						if(m_view == VIEW_FILES) {
							for(prevItems_t::iterator iIter = m_prevItems.begin();
									iIter != m_prevItems.end();
									++iIter) {
								dir += (*iIter).first + "/";
							}
							dir = dir.substr(0, dir.length()-1);
							if(!dir.empty())
								song = dir+"/";
							song += m_curItemName;
						} else {
							song = m_curSongPaths[m_curItemNum-1];
						}
						mpd_sendAddCommand(m_mpd, song.c_str());
						mpd_finishCommand(m_mpd);
					} else if(m_curItemType == TYPE_FOLDER || m_curItemType == TYPE_ALL) {
						addFolderAsPlaylist(true);	
					}
					m_appended = true;
					break;
				case CMD_ADD_AS_PL: 
					if(m_curItemType == TYPE_FOLDER || m_curItemType == TYPE_ALL) {
						addFolderAsPlaylist();	
						newMode = 1;
					}
					break;
				case CMD_PLAY_PAUSE:
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
				case CMD_TOGGLE_VIEW:

					if(m_view == 2)
						m_view = 0;
					else
						++m_view;
					
					m_curItemNum = 0;
					m_topItemNum = 0;
					m_curItemName = "";
					m_prevItems.clear();	
					ls("");
					   
					break;
				case CMD_FILTER_KEYBOARD:
					m_filters[m_view] = m_keyboard.getText();
					std::string item;
					switch(m_view) {
						case VIEW_ARTISTS:
							item = m_config.getItem("LANG_ARTISTS");	
						break;
						case VIEW_ALBUMS:
							item = m_config.getItem("LANG_ALBUMS");	
						break;
						case VIEW_GENRES:
							item = m_config.getItem("LANG_GENRES");	
						break;
					
					}
					ls(item);
					newMode = CMD_HIDE_KEYBOARD;	
					break;
			}
		}
	}
	return newMode;
}

void FolderChooser::draw(bool forceRefresh, long timePerFrame, bool inBack)
{
	if(!m_good)
		initAll();
	if(forceRefresh || (!inBack && m_refresh) || m_queued || m_appended) {
		//clear this portion of the screen 
		SDL_SetClipRect(m_screen, &m_clearRect);
		SDL_BlitSurface(m_bg, &m_clearRect, m_screen, &m_clearRect );

		SDL_Surface *sText;
		sText = TTF_RenderUTF8_Blended(m_font, m_curDir.c_str(), m_itemColor);
		if(m_drawIcons) {
			m_destRect.x = m_curItemIconRect.x + 24;
			SDL_BlitSurface(m_iconBrowse, NULL, m_screen, &m_curItemIconRect );
		}

		SDL_BlitSurface(sText,NULL, m_screen, &m_destRect );
		SDL_FreeSurface(sText);
		
		m_destRect.y += m_skipVal*2;
		m_curItemClearRect.y += m_skipVal*2;
		m_curItemIconRect.y += m_skipVal*2;

		Scroller::draw(timePerFrame, m_drawIcons);	

		m_refresh = false;
	}
	
}
