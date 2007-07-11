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

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <vector>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "config.h"
#include "libmpdclient.h"
#include "scroller.h"
#include "timer.h"

class Popup;

class Playlist : public Scroller
{
public:
	typedef std::vector<std::pair<std::string, int> >listing_t;

	Playlist(mpd_Connection* mpd, SDL_Surface* screen, TTF_Font* font, Config& config, SDL_Rect& rect, int skipVal, int numPerScreen);
	void load(std::string dir);
	void updateStatus(int mpdStatusChanged, mpd_Status* mpdStatus, 
							int rtmpdStatusChanged, mpd_Status* rtmpdStatus, int repeatDelay);
    void processCommand(int event, int& rtmpdStatusChanged, mpd_Status* rtmpdStatus, int repeatDelay, int volume, long delayTime);
    void draw(bool force);
	std::string currentItemName();
	std::string currentItemPath();

	void makeNowPlayingVisible();
	bool showSaveDialog(Popup& popup);
	void setNextNumOnSave();
	int getRand(int max);
	void initRandomPlaylist();
	void initNewPlaylist();
	void initName(std::string name);
	void save();
	std::string nowPlayingTitle(int song=-1);
	std::string nowPlayingArtist(int song=-1);
	std::string nowPlayingFile(int song=-1);
	std::string nowPlayingFormat(int song=-1);
	void nowPlaying(int song);
protected:
	std::string m_curDir;

	int m_view;
	int m_curElapsed;
	int m_nowPlaying;
	int m_random;
	bool m_otg;
	bool m_modified;	
	std::vector<std::string> m_all;	
	std::string m_name;
	int m_id;
	int m_moveFrom;
	int m_moveTo;

	std::vector<int> m_used;
	bool m_refresh;
	Timer m_timer;
	typedef struct { 
		std::string title;
		std::string artist;
		std::string file;
	} songInfo_t;

	std::vector<songInfo_t> m_songsInfo;

};

#endif
	
