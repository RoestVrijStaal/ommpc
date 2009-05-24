/*****************************************************************************************

ommpc(One More Music Player Client) - A Music Player Daemon client targetted for the gp2x

Copyright (C) 2007-2008 - Tim Temple(codertimt@gmail.com)

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

#ifndef __VOLBUTTON_H__
#define __VOLBUTTON_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

#include "libmpdclient.h"
#include "config.h"
#include <vector>
#include "button.h"

class VolButton : public Button
{
public:
	VolButton();
	void init(Config& config, std::vector<int>& volScale);

	void updateStatus(int mpdStatusChanged, mpd_Status* mpdStatus,
					  int rtmpdStatusChanged, mpd_Status* rtmpdStatus, 
					  bool forceRefresh);
	int processCommand(int command, GuiPos& guiPos);
	virtual void draw(SDL_Surface* screen, SDL_Surface* bg, bool forceRefresh);
protected:
	
	int m_volLookup[101];
	bool m_softVol;
	int m_width;
	int m_height;
	bool m_showBig;		
	SDL_Surface* m_backImageBig;
	SDL_Surface* m_foreImageBig;
	SDL_Rect m_destRectBig;
	SDL_Rect m_clearRectBig;
	SDL_Rect m_srcRectBig;
	
	
};

#endif
