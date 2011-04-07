#ifndef __LASTFM_H__
#define  __LASTFM_H__

#include <string>
#include <iostream>
class Lastfm {

public:
	Lastfm();
	~Lastfm();
	void startScrobbling(std::string user, std::string pass);
	void stopScrobbling();
	
	void toggleScrobbling(std::string scrobbling, std::string user, std::string pass);
private:
std::string m_user;
std::string m_pass;
bool m_scrobbling;
};

#endif
