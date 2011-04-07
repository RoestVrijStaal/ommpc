#include "lastfm.h"
#include <fstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 

using namespace std;

Lastfm::Lastfm()
: m_scrobbling(false)
{
}

Lastfm::~Lastfm() 
{
}

void Lastfm::startScrobbling(std::string user, std::string pass)
{
	char pwd[129];
	getcwd(pwd, 128);
	string pwdStr(pwd);
	ofstream mpdConf("mpdscribble.conf", ios::out|ios::trunc);
	mpdConf << "username = " << user << endl;
	mpdConf << "password = " << pass << endl;
	mpdConf << "verbose = 1" << endl;
	mpdConf << "log = " << pwdStr << "/.scribble_log" << endl;
	mpdConf << "cache = " << pwdStr << "/.scribble_cache" << endl;
	mpdConf << "pidfile= " << pwdStr << "/.scribble_pid" << endl;
	mpdConf.close();
	cout  << "Scrobble Start" << endl;	
	system("./scrobble.sh &> scribble.out");
	m_scrobbling = true;
}

void Lastfm::stopScrobbling()
{
	char pwd[129];
	getcwd(pwd, 128);
	string pwdStr(pwd);
	pwdStr += "/.scribble_pid";

	struct stat stFileInfo;
	if(stat(pwdStr.c_str(),&stFileInfo) == 0) {

		ifstream pidFile(pwdStr.c_str(), ios::in);
		std::string pid;
		getline(pidFile, pid);

		system(string("kill " + pid).c_str());
		unlink(pwdStr.c_str());
		cout  << "Scrobble Ended" << endl;
		m_scrobbling = false;	
	}
}

void Lastfm::toggleScrobbling(string scrobbling, string scrobbleUser, string scrobblePass)
{
	if(!m_scrobbling) {
		if(scrobbling == "on" && !scrobbleUser.empty() 
				&& !scrobblePass.empty()) {
			startScrobbling(scrobbleUser, scrobblePass);

		} 
	} else {	
		if(scrobbling == "off") {
			stopScrobbling();
		}
	}	

}
