#ifndef __POPUP_H__
#define __POPUP_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

#include "libmpdclient.h"
#include "config.h"
#include "playlist.h"
#include "scroller.h"

class Popup : public Scroller
{
public:
	typedef enum {POPUP_LIST, POPUP_CONFIRM, POPUP_MENU};
	typedef enum {POPUP_SAVE_PL };
	Popup(mpd_Connection* mpd, SDL_Surface* screen, Config& config, SDL_Rect& rect,
				int skipVal, int numPerScreen);
	
	void setItemsText(Scroller::listing_t& items);
	void setSize(SDL_Rect& rect);
	void setTitle(std::string name);
	std::string selectedText();
	int selectedAction();
	int processCommand(int command);	
	void draw();
	void drawSelectList();
protected:
	
	Config& m_config;
	std::string m_name;
	int m_pos;
	int m_delayCnt;

	SDL_Rect m_borderRect;
	int m_type;
};

#endif