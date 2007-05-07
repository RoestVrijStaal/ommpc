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


	void saveState(std::ofstream& ommcState);
	void loadState(Config& stateConfig);
	void makeNowPlayingVisible();
	bool showSaveDialog(Popup& popup);
	int getRand(int max);
	void initRandomPlaylist();
	void initNewPlaylist();
	void initName(std::string name);
	void save();
	std::string nowPlayingText(int song=-1);
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

	bool m_refresh;
	Timer m_timer;
};

#endif
	
