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

#include <iostream>

#include "keyboard.h"
#include "config.h"
#include "guiPos.h"
#include "commandFactory.h"
#include "SDL_image.h"

using namespace std;

Keyboard::Keyboard(SDL_Surface* screen, Config& config)
: m_config(config)
, m_screen(screen)
, m_viewMore(false)
, m_shift(0)
, m_curRow(4)
, m_curCol(3)
, m_refresh(true)
, m_foundKey(false)
, m_counter(0)
, m_good(false)
{
}

void Keyboard::initAll() 
{
	SDL_Surface* tmpSurface = NULL;	
	string keyboardName = m_config.getItem("sk_keyboard");

	tmpSurface = IMG_Load(string("keyboards/"+keyboardName+"/keyboard_entry.png").c_str());
	if (!tmpSurface)
		tmpSurface = IMG_Load(string("keyboards/default/keyboard_entry.png").c_str());
	m_keyboardEntry = SDL_DisplayFormatAlpha(tmpSurface);
	SDL_FreeSurface(tmpSurface);
	
	m_config.getItemAsColor("sk_main_itemColor", m_itemColor.r, m_itemColor.g, m_itemColor.b);
	
	m_font = TTF_OpenFont(m_config.getItem("sk_font_main").c_str(),
										  28);
	
	m_good = true;
}

void Keyboard::initVector(vector<string>& myVect, string myArray[], int size)
{
	for(int i=0; i<size; ++i) {
		myVect.push_back(myArray[i]);
	}

}

void Keyboard::initKeys()
{
}

Keyboard::~Keyboard()
{

}

void Keyboard::init(int returnCmd, string initialText)
{
	m_returnCmd = returnCmd;
	m_text = initialText;
}

std::string Keyboard::getText()
{
	return m_text;
}

bool Keyboard::inRect(int x, int y, SDL_Rect& rect)
{
	if(x > rect.x && x < rect.x+rect.w && y > rect.y && y < rect.y+rect.w) 
		return true;
	else 
		return false;
}

int Keyboard::processCommand(int command, GuiPos& guiPos, int curKey)
{
	int rCommand = command;
	bool foundKey = false;
	int i=0;
	if(command > 0) {
		if(command == CMD_CLICK) {
			rCommand = CMD_HIDE_KEYBOARD;
			foundKey = false;

		} else if(command == CMD_RIGHT) {
		} else if(command == CMD_LEFT) {
		} else if(command == CMD_LOAD_PL 
				|| command == CMD_LOAD_BKMRK
				|| command == CMD_IMMEDIATE_PLAY
				|| command == CMD_POP_SELECT
				//|| command == CMD_HIT_KEY
				|| command == CMD_PLAY_PAUSE ) {
		} else if(command == CMD_STOP
				|| command == CMD_POP_CANCEL
				|| command == CMD_PREV_DIR
				|| command == CMD_PREV_DIR ) {
			rCommand = CMD_HIDE_KEYBOARD;
			foundKey = false;
		} else if(command == CMD_SHOW_MENU) {
			rCommand = m_returnCmd;	
			foundKey = false;
		} else if(command == CMD_ADD_AS_PL
				|| command == CMD_MOVE_IN_PL) {
			rCommand = 0;
			m_text = m_text.substr(0, m_text.length()-1);
		} else if(command == CMD_REAL_KEY_DOWN || command == CMD_REAL_KEY_UP) {
			if(curKey == SDLK_ESCAPE || curKey == 281) {
				rCommand = CMD_HIDE_KEYBOARD;
			} else if(curKey == SDLK_RETURN || curKey == 279) {
				rCommand = m_returnCmd;	
			} else if(curKey == SDLK_BACKSPACE) {
				m_text = m_text.substr(0, m_text.length()-1);

			} else if(curKey != -1) {
				m_text += char(curKey);
			}
			m_refresh = true;
		}

	}

	return rCommand;
	
}

bool Keyboard::draw(bool forceRefresh)
{
	if(!m_good)
		initAll();
	bool refreshRet = false;
	if(forceRefresh || m_refresh) {
		SDL_Rect entryRect;
		SDL_Surface *sText;

		entryRect.w = 500;
		entryRect.h = 32;
		entryRect.x = (m_screen->w - entryRect.w) / 2;
		entryRect.y = 140;
	
		SDL_Rect letterRect = entryRect;
		SDL_SetClipRect(m_screen, &entryRect);
		SDL_BlitSurface(m_keyboardEntry, NULL, m_screen, &entryRect );
		sText = TTF_RenderText_Blended(m_font, m_text.c_str(), m_itemColor);
		SDL_BlitSurface(sText, NULL, m_screen, &letterRect );
		SDL_FreeSurface(sText);

		m_refresh = false;
		refreshRet = true;
	}

	return refreshRet;
}



