#ifndef __STATSBAR_H__
#define __STATSBAR_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "libmpdclient.h"
#include "config.h"
#include "playlist.h"
#include <vector>
class StatsBar
{
public:
	StatsBar(mpd_Connection* mpd, SDL_mutex* lock,  SDL_Surface* screen, Config& config, SDL_Rect& rect);
	
	void draw(int mpdStatusChanged, mpd_Status* mpdStatus,
					int rtmpdStatusChanged, mpd_Status* rtmpdStatus);
protected:
	
	mpd_Connection* m_mpd;
	SDL_mutex* m_lock;
	SDL_Surface* m_screen;
	SDL_Rect m_destRect;
	SDL_Rect& m_clearRect;
	Config& m_config;
	TTF_Font* m_font;
	
	std::string m_name;
	std::string m_volume;
	std::string m_playType;
	std::string m_crossfade;
	std::string m_elapsed;
	std::string m_total;
	std::string m_bitRate;
	std::vector<std::string> m_items;
	
	int m_cols;
	int m_itemH;
	int m_pos;
	int m_inc;
	int m_origY;
};

#endif