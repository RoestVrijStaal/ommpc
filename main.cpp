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

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "config.h"
#include "lastfm.h"
#include "browser.h"
#include "plBrowser.h"
#include "bookmarks.h"
#include "playlist.h"
#include "settings.h"
#include "albumArt.h"
#include "overlay.h"
#include "nowPlaying.h"
#include "fullPlaying.h"
#include "buttonManager.h"
#include "libmpdclient.h"
#include "threadFunctions.h"
#include "commandFactory.h"
#include "statsBar.h"
#include "menu.h"
#include "timer.h"
#include "popup.h"
#include "gp2xregs.h"
#include "guiPos.h"
#include "songDb.h"
#include "keyboard.h"

#include "unistd.h"
#include <dirent.h>


using namespace std;

void initVolumeScale(vector<int>& volumeScale, bool f200, string softVol, int version)
{
	if(softVol == "on") {
		int softVolumeScale[21] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
		for(int i=0; i<22; ++i)
			volumeScale.push_back(softVolumeScale[i]);	

	} else {
		if(f200) {
			//int f200VolumeScale[21] = {0,1,3,5,8,12,14,18,22,26,30,34,38,42,46,50,56,62,68,74,80};
			int f200VolumeScale[21] = {0,4,8,12,16,20,25,30,35,40,45,50,55,60,65,70,76,82,88,94,100};
			for(int i=0; i<22; ++i)
				volumeScale.push_back(f200VolumeScale[i]);	

		} else {
			int f100VolumeScale[21] = {0,4,8,12,16,20,25,30,35,40,45,50,55,60,65,70,76,82,88,94,100};

			for(int i=0; i<22; ++i)
				volumeScale.push_back(f100VolumeScale[i]);	
		}
	}

}

Config config;
bool g_resized = false;
int g_width = 0;
int g_height = 0;
int g_minWidth = config.getItemAsNum("sk_min_screen_width");
int g_minHeight = config.getItemAsNum("sk_min_screen_height");
int g_maxWidth = config.getItemAsNum("sk_screen_width");
int g_maxHeight = config.getItemAsNum("sk_screen_height");

int eventFilter( const SDL_Event *e )
{
    if( e->type == SDL_VIDEORESIZE )
    {
		if(e->resize.w > g_minWidth)
			g_width = e->resize.w;
		else if(e->resize.w > g_maxWidth)
			g_width = g_maxWidth;
		else
			g_width = g_minWidth;

		if(e->resize.h > g_minHeight)
			g_height = e->resize.h;
		else if(e->resize.h > g_maxHeight)
			g_height = g_maxHeight;
		else
			g_height = g_minHeight;


        SDL_SetVideoMode(g_width,g_height,
						32,
						SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
		g_resized = true;
    }
    return 1; // return 1 so all events are added to queue
}

int main ( int argc, char** argv )
{
	bool initVolume = true;
	bool f200 = false;
	struct stat stFileInfo;
	if(stat("/dev/touchscreen/wm97xx",&stFileInfo) == 0)
		f200 = true;
#if defined(WIZ)
	f200 = true;
#endif

	vector<int> volumeScale;
	int pid;
	int wpid;
	int status;

	pid = fork();

	if(pid ==-1) {
		cout << "Fork failed" << endl;
		exit(1);
	} else if(pid == 0) { //child..attempt to launch mpd
		char pwd[129];
		getcwd(pwd, 128);
		string pwdStr(pwd);

		string mPath = config.getItem("musicRoot");	
		string pPath = config.getItem("playlistRoot");	

		int lastPos = -1;
		for(int i=0; i<3; ++i) {
			lastPos = pwdStr.find('/', lastPos+1);
		}
		string cardName = pwdStr.substr(0, lastPos+1);	
		if(mPath[0] != '/') {
			mPath = cardName + mPath;
		}
	
		if(pPath[0] != '/') {
			pPath = cardName + pPath;
		}

		ofstream mpdConf("mpd.conf", ios::out|ios::trunc);
		mpdConf << "port   \"6600\"" << endl;
		mpdConf << "audio_buffer_size    \"1024\"" << endl;
		mpdConf << "buffer_before_play    \"25%\"" << endl;
		mpdConf << "audio_output {" << endl;
		mpdConf << "type    \"alsa\"" << endl;
		mpdConf << "name    \"My ALSA Device\"" << endl;
		mpdConf << "format    \"44100:16:2\"" << endl;
//		mpdConf << "options    \"dev=dmixer\"" << endl;
//		mpdConf << "device   \"plug:dmix\"" << endl;
		mpdConf << "}" << endl;
		mpdConf << "mixer_type    \"software\"" << endl;
		mpdConf << "filesystem_charset    \"UTF-8\"" << endl;
		mpdConf << "id3v1_encoding   \"UTF-8\"" << endl;
		mpdConf << "music_directory    \"" + mPath + "\"" << endl;
		mpdConf << "playlist_directory    \"" + pPath + "\"" << endl;
		mpdConf << "log_file    \"" + pwdStr + "/.mpdlog\"" << endl;
		mpdConf << "error_file    \"" + pwdStr + "/.mpderror\"" << endl;
		mpdConf << "db_file    \"" + pwdStr + "/db\"" << endl;
		mpdConf << "pid_file    \"" + pwdStr + "/.pid\"" << endl;
		mpdConf << "state_file    \"" + pwdStr + "/.mpdstate\"" << endl;
		mpdConf.close();
		
		if(config.verifyMpdPaths()) {	
	
			struct stat stFileInfo; 

			int exists = stat("db",&stFileInfo); 
			if(exists != 0) { 
				// does not exist
				ifstream ifs("db.pnd", ios::binary);
				ofstream ofs("db", ios::binary);

				ofs << ifs.rdbuf();

			}
			pwdStr += "/mpd/mpd";
			execlp(pwdStr.c_str(), pwdStr.c_str(), "--no-create-db", "mpd.conf",  NULL);
			cout << errno << " " << strerror(errno) << endl;
#if defined(GP2X) || defined(WIZ)
			exit(-1);
#else		
			exit(1);
#endif
		} else {
			cout << "bad paths...not starting mpd" << endl;
			exit(-1);
		} 
		exit(1);
	} else {

		//we wait and then assume mpd is now running or was already running
		if(waitpid(pid,&status,0)<0)
		{
			cout << "waitpid failed" << endl;
			exit(-1);
		}
		bool mpdStarted = false;
		if(WEXITSTATUS(status) == 0 || WEXITSTATUS(status) == 1)
			mpdStarted = true;

		cout << "child exit status " << WEXITSTATUS(status) << endl;
		try {
			GuiPos guiPos;
			GP2XRegs gp2xRegs;
				
			initVolumeScale(volumeScale, f200, config.getItem("softwareVolume"), gp2xRegs.version());
			// initialize SDL video
			if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0 )
			{
				printf( "Unable to init SDL: %s\n", SDL_GetError() );
				return 1;
			}

			cout << SDL_NumJoysticks() << " joysticks were found." << endl;

			for(int i=0; i < SDL_NumJoysticks(); i++ ) 
			{
				cout << "    " <<  SDL_JoystickName(i) << endl;
				SDL_JoystickOpen(i);	
			}
			if (TTF_Init() == -1)
			{
				printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
				//Put here however you want to do about the error.
				//you could say:
				return true;
				//Or:
				//exit(1);
			}
cout << "set video mode" << endl;
			// create a new window
			SDL_SetEventFilter( &eventFilter ); 
			SDL_Surface* screen = SDL_SetVideoMode(config.getItemAsNum("sk_screen_width"),
												   config.getItemAsNum("sk_screen_height"),
#if defined(WIZ) || defined(PAND)
													16,
													SDL_SWSURFACE|SDL_FULLSCREEN);
#else
													16,
													SDL_HWSURFACE|SDL_DOUBLEBUF);
													//SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
#endif
			if ( !screen )
			{
				printf("Unable to set 320x240 video: %s\n", SDL_GetError());
				return 1;
			}
#if defined(GP2X) || defined(WIZ) || defined(PAND)
			SDL_ShowCursor(SDL_DISABLE);
#endif
			SDL_Rect mainRect = { config.getItemAsNum("sk_main_x"),
				config.getItemAsNum("sk_main_y"),
				config.getItemAsNum("sk_screen_width") * config.getItemAsFloat("sk_main_width"),
				config.getItemAsNum("sk_screen_height") - config.getItemAsFloat("sk_nowPlaying_height") 
														- config.getItemAsFloat("sk_stats_height"),
			};
			SDL_Rect artRect = { config.getItemAsNum("sk_art_x"),
				config.getItemAsNum("sk_art_y"),
				config.getItemAsNum("sk_art_width"),
				config.getItemAsNum("sk_art_height")
			};
			SDL_Rect nowPlayingRect = { config.getItemAsNum("sk_nowPlaying_x"),
				config.getItemAsNum("sk_nowPlaying_y"),
				config.getItemAsNum("sk_screen_width") * config.getItemAsFloat("sk_nowPlaying_width"),
				config.getItemAsNum("sk_nowPlaying_height")
			};
			SDL_Rect statsRect = { config.getItemAsNum("sk_stats_x"),
				config.getItemAsNum("sk_stats_y"),
				config.getItemAsNum("sk_screen_width") * config.getItemAsFloat("sk_stats_width"),
				config.getItemAsNum("sk_stats_height")
			};
			SDL_Rect helpRect = { config.getItemAsNum("sk_help_x"),
				config.getItemAsNum("sk_help_y"),
				config.getItemAsNum("sk_help_width"),
				config.getItemAsNum("sk_help_height")
			};
			SDL_Rect clearRect = { 0,0,screen->w, screen->h};

			SDL_Rect popRect;
			popRect.w = 450;
			popRect.h = 200;
			popRect.x = (screen->w - 450) / 2;
			popRect.y = (screen->h - 200) / 2;
			threadParms_t threadParms;
			if(mpdStarted) {
				threadParms.mpd = mpd_newConnection(config.getItem("host").c_str(), 
						config.getItemAsNum("port"),
						config.getItemAsNum("timeout"));
			} else {
				threadParms.mpd = NULL;
			}
			threadParms.mpdStatus = NULL;
			threadParms.mpdStatusChanged = 0;
			threadParms.mpdReady = false;
			threadParms.pollStatusDone = false;
			threadParms.lockConnection = SDL_CreateMutex();
			
			SongDb songDb(config.getItem("host"), 
					config.getItemAsNum("port"),
					config.getItemAsNum("timeout"));
			//SongDb songDb(threadParms.mpd);
			SDL_Thread *songDbThread = NULL;
			songDbThreadParms_t songDbParms;
			songDbParms.songDb = &songDb;
			songDbParms.updating = false;

			//enable status checking for interactive commands...
			mpd_Status* rtmpdStatus = NULL;
			int rtmpdState = MPD_STATUS_STATE_UNKNOWN;
			int rtmpdStatusChanged = 0;
			bool classicStatsBar = config.getItemAsBool("sk_classicStatsBar");
			
			if(mpdStarted) {
				mpd_sendStatusCommand(threadParms.mpd);
				rtmpdStatus = mpd_getStatus(threadParms.mpd);
				mpd_finishCommand(threadParms.mpd);
			}
			if(rtmpdStatus != NULL) {
				rtmpdState = rtmpdStatus->state;
				mpd_freeStatus(rtmpdStatus);
			}
			rtmpdStatus = NULL;
#if defined(GP2X) || defined(WIZ) || defined(PAND)
//			if (mpdStarted && rtmpdState == MPD_STATUS_STATE_PLAY) {
//				mpd_sendPauseCommand(threadParms.mpd, 1);
//				mpd_finishCommand(threadParms.mpd);
//			}
			//gp2xRegs.setClock(config.getItemAsNum("cpuSpeed"));
#endif
			TTF_Font* font = TTF_OpenFont(config.getItem("sk_font_main").c_str(),
										  config.getItemAsNum("sk_font_main_size"));
			int skipVal = (int)(TTF_FontLineSkip( font ) * config.getItemAsFloat("sk_font_main_extra_spacing"));
			int numPerScreen = (mainRect.h-(2*skipVal))/skipVal+1;

			string skinName = config.getItem("skin");
			SDL_Surface * tmpbg = IMG_Load(string("skins/"+skinName+"/bg.png").c_str());
			if (!tmpbg) {
				tmpbg = IMG_Load(string("skins/"+skinName+"/bg.jpg").c_str());
				
				if (!tmpbg) 
					printf("Unable to load skin image: %s\n", SDL_GetError());
			}
			SDL_Surface * bg = SDL_DisplayFormat(tmpbg);

			Keyboard keyboard(screen, config);
			int popPerScreen = (popRect.h-(2*skipVal))/skipVal;
			Popup popup(threadParms.mpd, screen, config, popRect, skipVal, popPerScreen, gp2xRegs, keyboard);
			Playlist playlist(threadParms.mpd, screen, bg, font, config, mainRect, skipVal, numPerScreen);
			Browser browser(threadParms.mpd, screen, bg, font, mainRect, config, skipVal, numPerScreen, songDb, keyboard, playlist);
			Menu menu(threadParms.mpd, screen, bg, font, mainRect, config, skipVal, numPerScreen, songDb, keyboard, playlist);
			PLBrowser plBrowser(threadParms.mpd, screen, bg, font, mainRect, config, skipVal, numPerScreen, playlist, keyboard);
			NowPlaying playing(threadParms.mpd, threadParms.lockConnection, screen, bg, config, nowPlayingRect, playlist);
			StatsBar statsBar(threadParms.mpd, threadParms.lockConnection, screen, bg, config, statsRect, initVolume, playlist, f200, volumeScale);
			//Overlay overlay(threadParms.mpd, screen, config, clearRect, playlist);
			ButtonManager buttonManager(threadParms.mpd, threadParms.lockConnection, screen, bg, config, volumeScale);
			Bookmarks bookmarks(threadParms.mpd, screen, bg, font, mainRect, skipVal, numPerScreen, playlist, config, statsBar, buttonManager, classicStatsBar, keyboard);
			CommandFactory commandFactory(threadParms.mpd, volumeScale);
			PlayerSettings settings(threadParms.mpd, screen, bg, font, mainRect, config, skipVal, numPerScreen, gp2xRegs, keyboard);
			int curMode = 0;	
			int volume = 10;
			int isPlaying = 0;
			if(mpdStarted) {
				try {
					Config stateConfig(".ommpcState");
					curMode = stateConfig.getItemAsNum("mode");
					volume = stateConfig.getItemAsNum("vol");	
					isPlaying = stateConfig.getItemAsNum("playing");

					if(volume == 0 || volume > 20)
						volume = 10;
					mpd_sendSetvolCommand(threadParms.mpd, volumeScale[volume]);
					mpd_finishCommand(threadParms.mpd);
					initVolume = true;
				} catch(exception& e) {
					//carry on
				}
			}
			//polling thread that gets current status from mpd
			SDL_Thread *statusThread;
			if(mpdStarted) {
				statusThread = SDL_CreateThread(pollMpdStatus, &threadParms);
				if(statusThread == NULL) {
					cout << "unable to create status thread" << endl;
					return -1;
				}
			}
			//art loading thread, just so we don't wait  
			SDL_Thread* artThread;
			artThreadParms_t artParms;
			artParms.doArtLoad = false;
			artParms.done = false;
			artParms.artSurface = NULL;	
			artParms.destWidth = config.getItemAsNum("sk_full_art_width");
			artParms.destHeight = config.getItemAsNum("sk_full_art_height");
			artThread = SDL_CreateThread(loadAlbumArt, &artParms);
			if(artThread == NULL) {
				cout << "unable to create album art thread" << endl;
				return -1;
			}


			AlbumArt albumArt(threadParms.mpd, screen, bg, config, artRect, artParms);
			FullPlaying fullPlaying(threadParms.mpd, screen, bg, font, mainRect, config, skipVal, numPerScreen, keyboard, artParms);



			string scrobbling = config.getItem("scrobbling");
			string scrobbleUser = config.getItem("scrobbleUser");
			string scrobblePass = config.getItem("scrobblePass");
			Lastfm lastfm;
			lastfm.toggleScrobbling(scrobbling, scrobbleUser, scrobblePass);
			

			bool forceRefresh = true;
			bool done = false;
			bool killMpd = false;
			bool launchProcess = false;
			string launchProcessName = "";
			int command = -1;
			int prevCommand = -1;
			bool keysHeld[401] = {false};
			int repeatDelay = 0;
			bool processedEvent = false;
			bool repeat = false;
			bool random = false;
			int frame = 0;
			bool popupVisible = false;
			bool overlayVisible = false;
			bool keyboardVisible = false;
			SDL_Color backColor;
			config.getItemAsColor("sk_screen_color", backColor.r, backColor.g, backColor.b);

			Timer timer;	
			Timer timer2;	
			int fps=0;
			int targetFps = (config.getItemAsNum("fps")==0 ? 15 : config.getItemAsNum("fps"));
			cout << "target fps=" << targetFps << endl;
			long frameTime = ((float)1000/(float)targetFps) * 1000;
			long now = timer.check();
			long nextFrame = 0;
			long timePerFrame = 0;
			long diffTime = 0;
cout << "away we go" << endl;
			SDL_Event event;
			int mouseState = 0; //0=unpressed, 1=down, 2=up
			if(!config.verifyMpdPaths() || threadParms.mpd == NULL) {		
				curMode=10;
				//popupVisible = showOptionsMenu(screen, popup, config);
			}
//			ofstream out("uptime", ios::out);
			Timer timer3;	
			while (!done)
			{
				if(gp2xRegs.screenIsOff())  {
					threadParms.mpdReady = false;
					if(SDL_PollEvent(&event))
					{
						if(event.type == SDL_MOUSEMOTION) {
							continue;
						}
						switch (event.type) {
							case SDL_KEYDOWN:
								command = commandFactory.keyDownWhileLocked(event.key.keysym.sym);
							break;
							case SDL_KEYUP:
								command = commandFactory.keyUpWhileLocked(event.key.keysym.sym);
							break;
						}
					}
						command = commandFactory.checkRepeatWhileLocked(command, prevCommand);
			
					if(command == CMD_TOGGLE_SCREEN) {
						gp2xRegs.toggleScreen();
/*
						if(config.getItemAsNum("cpuSpeed") != 
							config.getItemAsNum("cpuSpeedLocked")) {
							if(gp2xRegs.screenIsOff())
								gp2xRegs.setClock(config.getItemAsNum("cpuSpeedLocked"));
							else
								gp2xRegs.setClock(1);
						}
*/
						forceRefresh = true;
						popupVisible = false;
						threadParms.mpdReady = true;
					}
					prevCommand = command;
					command = 0;
					usleep(50000);

				} else {
				now = timer.check();
				nextFrame = now + frameTime;
 			
				SDL_mutexP(threadParms.lockConnection);
				// let's start with checking some polled status items
				if(threadParms.mpdStatusChanged & VOL_CHG) {
					//volume = threadParms.mpdStatus->volume;
				}
				if(threadParms.mpdStatusChanged & RND_CHG) {
					random = threadParms.mpdStatus->random;
				}
				if(threadParms.mpdStatusChanged & RPT_CHG) {
					repeat = threadParms.mpdStatus->repeat;
				}
				if (SDL_PollEvent(&event))
				{
					if(event.type == SDL_MOUSEMOTION) {
 						SDL_mutexV(threadParms.lockConnection);
						continue;
					}
					switch (event.type) {
					//this stops the mouse motion event from taking 
					//too much time and screwing sutff up.
						case SDL_KEYDOWN:
							command = commandFactory.keyDown(event.key.keysym.sym, curMode, keyboardVisible);
						break;
						case SDL_KEYUP:
							if(popupVisible)
								command = commandFactory.keyPopup(event.key.keysym.sym, curMode, command);
							else
								command = commandFactory.keyUp(event.key.keysym.sym, curMode, keyboardVisible);
						break;
						case SDL_JOYBUTTONDOWN:
							command = commandFactory.keyDown(event.jbutton.button, curMode, keyboardVisible);
						break;
						case SDL_JOYBUTTONUP:
							if(popupVisible)
								command = commandFactory.keyPopup(event.jbutton.button, curMode, command);
							else
								command = commandFactory.keyUp(event.jbutton.button, curMode, keyboardVisible);
						break;
						case SDL_MOUSEBUTTONDOWN:
							SDL_GetMouseState(&guiPos.curX, &guiPos.curY);
							command = commandFactory.mouseDown(curMode, guiPos.curX, guiPos.curY);
						break;
						case SDL_MOUSEBUTTONUP:
							SDL_GetMouseState(&guiPos.curX, &guiPos.curY);
							command = commandFactory.mouseUp(curMode, guiPos.curX, guiPos.curY);
						break;
						case SDL_QUIT:
							command = CMD_DETACH;
						break;
						default:
							processedEvent = false;
					}
					processedEvent = true;
				} // end of message processing

				//check resize event results
				if(g_resized) {
					g_resized = false;
					forceRefresh = true;
				
					cout << "doing resize code" << endl;	
					int numPerScreen = (g_height-(2*skipVal))/skipVal+1;
					//reset sizes of crap
					menu.resize(g_width, g_height, numPerScreen);
					playing.resize(g_width);
					statsBar.resize(g_width);
				}
				command = commandFactory.checkRepeat(command, prevCommand, curMode, guiPos.curX, guiPos.curY, keyboardVisible);	
				if(keyboardVisible) {
					int preCommand = command;

					command = keyboard.processCommand(command, guiPos, commandFactory.getCurKey());
					if(command == CMD_SAVE_PL || command == CMD_SAVE_BKMRK 
						|| command == CMD_HIDE_KEYBOARD || command == CMD_POP_CHG_OPTION) {
						keyboardVisible = false;
						forceRefresh = true;
						commandFactory.clearKeys();
						
					}
					if(command != preCommand) {
						forceRefresh = true;
					}
				}
				
				if(popupVisible) {
					command = popup.processCommand(command, guiPos);
					switch(command) {
						case CMD_POP_SELECT:
							command = popup.processPopupCommand();
							forceRefresh = true;
							popupVisible = false;	
							break;
					}
				}
				if(curMode == 5) {
					command = menu.processCommand(command, guiPos);
					if(command == CMD_POP_CONTEXT) {
						popupVisible = popup.showPopupTouch(screen, config, curMode);
					}
				}
				command = buttonManager.processCommand(command, guiPos);
				switch(command) {
					case CMD_QUIT:
						done = true;
						killMpd = true;
						popupVisible = false;
						break;
					case CMD_DETACH:
						done = true;
						popupVisible = false;
						break;
					case CMD_LAUNCH_PROCESS:
						done = true;
						launchProcess = true;
						popupVisible = false;
						break;
					case CMD_STOP:
						mpd_sendStopCommand(threadParms.mpd);
						mpd_finishCommand(threadParms.mpd);
						break;
					case CMD_TOGGLE_SCREEN:
						gp2xRegs.toggleScreen();
/*
						if(config.getItemAsNum("cpuSpeed") != 
							config.getItemAsNum("cpuSpeedLocked")) {
							if(gp2xRegs.screenIsOff())
								gp2xRegs.setClock(config.getItemAsNum("cpuSpeedLocked"));
							else
								gp2xRegs.setClock(1);
						}
*/
						popupVisible = popup.showPopupLocked(screen, config, curMode);
						break;
					case CMD_VOL_UP:
						if(volume < 20) {
							++volume;
							mpd_sendSetvolCommand(threadParms.mpd, volumeScale[volume]);
							mpd_finishCommand(threadParms.mpd);
							rtmpdStatusChanged += VOL_CHG;
							mpd_sendStatusCommand(threadParms.mpd);
							rtmpdStatus = mpd_getStatus(threadParms.mpd);
							mpd_finishCommand(threadParms.mpd);
						}
						break;
					case CMD_VOL_DOWN:
						if(volume > 0) {
							--volume;
							mpd_sendSetvolCommand(threadParms.mpd, volumeScale[volume]);
							mpd_finishCommand(threadParms.mpd);
							rtmpdStatusChanged += VOL_CHG;
							mpd_sendStatusCommand(threadParms.mpd);
							rtmpdStatus = mpd_getStatus(threadParms.mpd);
							mpd_finishCommand(threadParms.mpd);
						}
						break;
					case CMD_MODE_RANDOM:
						random = !random;
						mpd_sendRandomCommand(threadParms.mpd, random);
						mpd_finishCommand(threadParms.mpd);
						rtmpdStatusChanged += RND_CHG;
						mpd_sendStatusCommand(threadParms.mpd);
						rtmpdStatus = mpd_getStatus(threadParms.mpd);
						mpd_finishCommand(threadParms.mpd);
						break;
					case CMD_MODE_REPEAT:
						repeat = !repeat;
						mpd_sendRepeatCommand(threadParms.mpd, repeat);
						mpd_finishCommand(threadParms.mpd);
						rtmpdStatusChanged += RPT_CHG;
						mpd_sendStatusCommand(threadParms.mpd);
						rtmpdStatus = mpd_getStatus(threadParms.mpd);
						mpd_finishCommand(threadParms.mpd);
						break;
					case CMD_RAND_RPT:
						if(!random && !repeat) {
							random = true;
							mpd_sendRandomCommand(threadParms.mpd, random);
							mpd_finishCommand(threadParms.mpd);
							rtmpdStatusChanged += RND_CHG;
						} else if(random && !repeat) {
							repeat = true;
							mpd_sendRepeatCommand(threadParms.mpd, repeat);
							mpd_finishCommand(threadParms.mpd);
							rtmpdStatusChanged += RPT_CHG;
						} else if(random && repeat) {
							random = false;
							mpd_sendRandomCommand(threadParms.mpd, random);
							mpd_finishCommand(threadParms.mpd);
							rtmpdStatusChanged += RND_CHG;
						} else if(!random && repeat) {
							repeat = false;
							mpd_sendRepeatCommand(threadParms.mpd, repeat);
							mpd_finishCommand(threadParms.mpd);
							rtmpdStatusChanged += RPT_CHG;
						}
						mpd_sendStatusCommand(threadParms.mpd);
						rtmpdStatus = mpd_getStatus(threadParms.mpd);
						mpd_finishCommand(threadParms.mpd);
						break;
					case CMD_TOGGLE_MODE:
						++curMode;
						if(curMode >= 5)
							curMode = 0;
						forceRefresh = true;
						break;
					case CMD_SAVE_PL:
						popupVisible = playlist.showSaveDialog(popup, keyboard.getText());
						break;
					case CMD_SAVE_PL_KEYBOARD: 
						{
						keyboardVisible = true;
						int num = config.getItemAsNum("nextPlaylistNum");
						ostringstream numStr;
						numStr << num;
						keyboard.init(CMD_SAVE_PL, "playlist_"+numStr.str());
						}
						break;
					case CMD_SAVE_BKMRK:
						bookmarks.doSave();
						break;
					case CMD_SAVE_BKMRK_KEYBOARD:
						{
						string curTitle = playlist.nowPlayingTitle();
						string formattedTime;
						if(classicStatsBar)
							formattedTime = statsBar.formattedElapsedTime();
						else
							formattedTime = buttonManager.formattedElapsedTime();
						string bfile = curTitle+"_"+formattedTime;
						keyboard.init(CMD_SAVE_BKMRK, bfile);
						keyboardVisible = true;
						}
						break;
					case CMD_POP_KEYBOARD:
						{
						keyboard.init(CMD_POP_CHG_OPTION, popup.getSelOptionText());
						keyboardVisible = true;
						}
						break;
					case CMD_POP_CANCEL:
						popupVisible = false;	
						break;
					case CMD_POP_HELP:
						popupVisible = popup.showPopupHelp(screen, config,curMode);
						break;
					case CMD_SHOW_MENU:
						curMode = 5;
						forceRefresh = true;
						break;
					case CMD_MENU_SETTINGS:
cout << "command menu stetet" << endl;
						curMode = 5;
						forceRefresh = true;
						break;
/*
					case CMD_SHOW_OVERLAY:
						overlayVisible = !overlayVisible;
						forceRefresh = true;
						break;
*/
					case CMD_LAUNCH_APP:
						char pwd[129];
						getcwd(pwd, 128);
						//popupVisible = showLaunchMenu(screen, popup, pwd, config);
						break;
					case CMD_SHOW_OPTIONS:
						curMode = 10;
						forceRefresh = true;
						break;
					case CMD_MPD_UPDATE: 
						{
							mpd_Status * mpdStatus;
							mpd_sendStatusCommand(threadParms.mpd);
							mpdStatus = mpd_getStatus(threadParms.mpd);
							mpd_finishCommand(threadParms.mpd);
	
							if(mpdStatus->updatingDb == 0 && !songDb.updating()) { 
								if(songDbThread != NULL)	
									SDL_WaitThread(songDbThread, NULL);

								char path[3] = "";
								mpd_sendUpdateCommand(threadParms.mpd, path);
								mpd_finishCommand(threadParms.mpd);

								songDbThread = SDL_CreateThread(updateSongDb, &songDbParms);
								if(statusThread == NULL) {
									cout << "unable to create status thread" << endl;
									return -1;
								}
							} else {
								cout << "already updating...." << endl;
							}
						}
						break;	
					case CMD_SHOW_NP:
						curMode = 2;
						forceRefresh = true;
						break;
					case CMD_SHOW_PL:
						curMode = 1;
						forceRefresh = true;
						break;
					case CMD_SHOW_PLS:
						curMode = 3;
						forceRefresh = true;
						break;
					case CMD_SHOW_LIB:
						curMode = 0;
						forceRefresh = true;
						break;
					case CMD_SHOW_BKMRKS:
						curMode = 4;
						forceRefresh = true;
						break;
				}

					// DRAWING STARTS HERE

					playlist.updateStatus(threadParms.mpdStatusChanged, 
							threadParms.mpdStatus, 
							rtmpdStatusChanged, rtmpdStatus, repeatDelay);
					playing.updateStatus(threadParms.mpdStatusChanged, threadParms.mpdStatus, 
							rtmpdStatusChanged, rtmpdStatus);
					playing.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
					if(classicStatsBar) {
						statsBar.updateStatus(threadParms.mpdStatusChanged, 
								threadParms.mpdStatus,
								rtmpdStatusChanged, 
								rtmpdStatus, 
								forceRefresh);
						statsBar.draw(forceRefresh, fps);
					}
					browser.updateStatus(threadParms.mpdStatusChanged, 
							threadParms.mpdStatus, songDbParms.updating);
					fullPlaying.updateStatus(threadParms.mpdStatusChanged, 
							threadParms.mpdStatus, rtmpdStatusChanged, rtmpdStatus, 
							songDbParms.updating, repeatDelay);
					plBrowser.updateStatus(threadParms.mpdStatusChanged, 
							threadParms.mpdStatus);
					bookmarks.updateStatus(threadParms.mpdStatusChanged, 
							threadParms.mpdStatus);
					int rMode= 0;
					switch (curMode) {
						case 0:
							rMode = browser.processCommand(command, guiPos);
							if(rMode == CMD_SHOW_KEYBOARD) {
								keyboardVisible = true;
								forceRefresh = true;
							} else if(rMode == CMD_HIDE_KEYBOARD) {
								keyboardVisible = false;
								forceRefresh = true;
								commandFactory.clearKeys();
							} else if(rMode == CMD_POP_CONTEXT) {
								popupVisible = popup.showPopupTouch(screen, config, curMode);
							} else
								curMode = rMode;
							browser.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
							break;
						case 1:
							rMode = playlist.processCommand(command, rtmpdStatusChanged, rtmpdStatus, repeatDelay, volume, commandFactory.getHoldTime(), guiPos);
							if(rMode == CMD_POP_CONTEXT) {
								popupVisible = popup.showPopupTouch(screen, config, curMode);
							}
							playlist.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);

							break;
						case 2:
							rMode = fullPlaying.processCommand(command, guiPos, commandFactory.getHoldTime());
							if(rMode == CMD_POP_CONTEXT) {
								popupVisible = popup.showPopupTouch(screen, config, curMode);
							}
							fullPlaying.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);

							break;
						case 3:
							{
							rMode = plBrowser.processCommand(command, curMode, guiPos);
							if(rMode == CMD_SHOW_KEYBOARD) {
								keyboardVisible = true;
								forceRefresh = true;
							} else if(rMode == CMD_HIDE_KEYBOARD) {
								keyboardVisible = false;
								forceRefresh = true;
								commandFactory.clearKeys();
							} else if(rMode == CMD_POP_CONTEXT) {
								popupVisible = popup.showPopupTouch(screen, config, curMode);
							}
							else 
								curMode = rMode;
							plBrowser.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
							}
							break;
						case 4:
							rMode = bookmarks.processCommand(command, guiPos);
							if(rMode == CMD_SHOW_KEYBOARD) {
								keyboardVisible = true;
								forceRefresh = true;
							} else if(rMode == CMD_HIDE_KEYBOARD) {
								keyboardVisible = false;
								forceRefresh = true;
								commandFactory.clearKeys();
							} else if(rMode == CMD_POP_CONTEXT) {
								popupVisible = popup.showPopupTouch(screen, config, curMode);
							} else 
								curMode = rMode;
							bookmarks.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
							break;
						case 5:
							menu.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
							break;
						case 10: 
							{
								rMode = settings.processCommand(command, guiPos);
								if(rMode == CMD_SHOW_KEYBOARD) {
									keyboardVisible = true;
									forceRefresh = true;
									settings.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
								} else if(rMode == CMD_HIDE_KEYBOARD) {
									keyboardVisible = false;
									forceRefresh = true;
									commandFactory.clearKeys();
									settings.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
								} else if (rMode == CMD_MENU_SETTINGS) {
									curMode = 5;
									forceRefresh = true;
									menu.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
								} else	{ 	
									settings.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);
								}
							}
							
							break;
						default: 
							playlist.processCommand(command, rtmpdStatusChanged, rtmpdStatus, repeatDelay, volume, commandFactory.getHoldTime(), guiPos);
							playlist.draw(forceRefresh, timePerFrame,  overlayVisible||keyboardVisible);
							break;
					}
					buttonManager.updateStatus(threadParms.mpdStatusChanged, 
											  threadParms.mpdStatus,
											  rtmpdStatusChanged, 
											  rtmpdStatus, 
											  forceRefresh);
					buttonManager.draw(forceRefresh, timePerFrame, overlayVisible||keyboardVisible);

					if(popupVisible)
						popup.draw();
					if(keyboardVisible) {
						forceRefresh = keyboard.draw(forceRefresh);
					} else if(overlayVisible) {
						//overlay.draw(forceRefresh);	
						//forceRefresh = false;
					} else {
						forceRefresh = false;
					}

					if(mpdStarted) {
						threadParms.mpdStatusChanged = 0;
						rtmpdStatusChanged = 0;
						if(rtmpdStatus != NULL) {
							mpd_freeStatus(rtmpdStatus);
							rtmpdStatus = NULL;
						}
					}
					prevCommand = command;
					command = 0;

					if(done) {
						threadParms.pollStatusDone = true;
						artParms.done = true;
					}

#if defined(GP2X) || defined(WIZ) || defined(PAND)
					// start playing, if it was playing when we last exited,
					// or if we had just paused an already-playing MPD daemon
					if(mpdStarted && (rtmpdState == MPD_STATUS_STATE_PAUSE && isPlaying)) {
							//|| rtmpdState == MPD_STATUS_STATE_PLAY) {
						mpd_sendPauseCommand(threadParms.mpd, 0);
						mpd_finishCommand(threadParms.mpd);
						// only do this once
						rtmpdState = MPD_STATUS_STATE_UNKNOWN;
					}
#endif
					// mark status polling as ready
					if(mpdStarted)
						threadParms.mpdReady = true;
					
					SDL_mutexV(threadParms.lockConnection);
					
				 	SDL_Flip(screen);

					++frame;
					if(timer2.check() > 5000000) //5minutes
					{
						timer2.stop();
						int elapsed = timer2.check()/1000000;
							
						//cout << elapsed << " secs." << endl;
						fps = frame/elapsed;
						//cout << "*******************fps " << fps << endl;
						frame = 0;
						timer2.start();
					}

					diffTime = nextFrame-timer.check();
					if(diffTime > 0) {
						usleep(diffTime);
					}
					timePerFrame = timer.check() - now;	
				} //end of loop when not locked	
					
			} // end main loop

			// Quit SDL
			SDL_WaitThread(songDbThread, NULL);
			SDL_WaitThread(artThread, NULL);
			if(mpdStarted)
				SDL_WaitThread(statusThread, NULL);
			SDL_Quit();

		//	gp2xRegs.setClock(1);
			if(mpdStarted) {
				// get playing state
				mpd_sendStatusCommand(threadParms.mpd);
				rtmpdStatus = mpd_getStatus(threadParms.mpd);
				mpd_finishCommand(threadParms.mpd);
				if(rtmpdStatus != NULL) {
					if (rtmpdStatus->state == MPD_STATUS_STATE_PLAY)
						isPlaying = 1;
					else
						isPlaying = 0;
					mpd_freeStatus(rtmpdStatus);
					rtmpdStatus = NULL;
				} else isPlaying = 0;

				// pause MPD
				if (isPlaying && killMpd) {
					mpd_sendPauseCommand(threadParms.mpd, 1);
					mpd_finishCommand(threadParms.mpd);
				}

			}
			//save current state
			ofstream ommcState(".ommpcState", ios::out|ios::trunc);
			ommcState << "mode=" << curMode << endl;
			ommcState << "vol=" << volume << endl;
			ommcState << "playing=" << isPlaying << endl;
			ommcState.close();

#if defined(GP2X) || defined(WIZ) || defined(PAND)
			// kill MPD
			if(mpdStarted && killMpd) {
				mpd_sendKillCommand(threadParms.mpd);
				mpd_finishCommand(threadParms.mpd);
				lastfm.toggleScrobbling("off", "", "");
				sync();
				// Note: This causes at least the playlist file to be
				// written before syncing, because MPD writes it
				// before closing the socket.  It is possible that the
				// PID file is not cleaned up in time for this,
				// though.
			} else {
				sync();
			}
	
			if(launchProcess) {
				cout << "launching " << launchProcessName << endl;
				execlp(launchProcessName.c_str(), launchProcessName.c_str(), NULL);
			}
#endif
			// free connection data
			if(mpdStarted)
				mpd_closeConnection(threadParms.mpd);

			printf("Exited cleanly\n");
			return 0;
			//    }
	} catch (std::exception& e) {
		cout << "Process Exception: " << e.what() << endl;
	}

}
}
