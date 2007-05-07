#ifndef __BROWSER_H__
#define __BROWSER_H__

#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "libmpdclient.h"
#include "scroller.h"

class Config;

class Browser : public Scroller
{
public:
    Browser(mpd_Connection* mpd, SDL_Surface* screen, TTF_Font* font, SDL_Rect& rect, 
				Config& config, int skipVal, int numPerScreen);
    void ls(std::string dir="");
	
	void browseFileSystem(std::string dir);
	void browseArtists();	
	void browseAlbumsByArtist(std::string artist);	
	void updateStatus(int mpdStatusChanged, mpd_Status* mpdStatus);
	void processCommand(int command);
	void draw(bool forceRefresh);
	std::string currentItemName();
	std::string currentItemPath();

	bool updatingDb() { return m_updatingDb;}
protected:
	std::string m_curDir;
	
	int m_view;
	int m_curState;
	std::string m_curTitle;
	std::string m_curAlbum;	
	int m_nowPlaying;
	bool m_updatingDb;
	bool m_refresh;
};

#endif
