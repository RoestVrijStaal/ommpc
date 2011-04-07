#-------------------------------------------------------------------------------
# Simple Makefile
#
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
# Be sure to use the cxx compiler
#-------------------------------------------------------------------------------
CC = gcc
CXX = g++


#-------------------------------------------------------------------------------
# Desired optimization level
#-------------------------------------------------------------------------------
O_FLAG = -Wall -Werror
#O_FLAG = -O1
OPTIMIZATION_FLAG = -g

#-------------------------------------------------------------------------------
# The directories to look for include files and libraries
#-------------------------------------------------------------------------------
INCDIR = -I. -I/usr/include/SDL
LIB = -L. 

#-------------------------------------------------------------------------------
# Compiler flags
#-------------------------------------------------------------------------------
CXXFLAGS      = $(OPTIMIZATION_FLAG) $(INCDIR) $(LIB)

#-------------------------------------------------------------------------------
# The .cpp files used to compile the client
#-------------------------------------------------------------------------------
.SUFFIXES: .cpp .c

.c.o:
	$(CC) $(CXXFLAGS) -c $<
.c:
	$(CC) $(CXXFLAGS) $< -o pc/$@
	
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

.cpp:
	$(CXX) $(CXXFLAGS) $< -o pc/$@

SRC     = plBrowser.cpp browser.cpp playlist.cpp main.cpp config.cpp nowPlaying.cpp statsBar.cpp commandFactory.cpp popup.cpp scroller.cpp timestamp.cpp helpBar.cpp albumArt.cpp threadFunctions.cpp bookmarks.cpp gp2xregs.cpp overlay.cpp songDb.cpp keyboard.cpp button.cpp volButton.cpp buttonManager.cpp seekButton.cpp rndButton.cpp rptButton.cpp rndRptButton.cpp menu.cpp menuButton.cpp fullPlaying.cpp artButton.cpp settings.cpp id3Button.cpp actionButton.cpp lastfm.cpp

OBJ = $(SRC:.cpp=.o) libmpdclient.o
#-------------------------------------------------------------------------------
# Libraries being linked with the application
#-------------------------------------------------------------------------------
LIBS = -pthread -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_gfx /usr/lib/libsqlite3.so.0 -ldl 

#-------------------------------------------------------------------------------
# Target for creating simple client
#-------------------------------------------------------------------------------
ommpc: $(OBJ)
	@echo $(OBJ)
	@echo $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS) \
		$(SYSLIBS) $(LIBS)
	@echo "SUCCESS"

watchdog: 
	$(CXX) $(CXXFLAGS) -c watchdog.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o watchdog watchdog.o config.o libmpdclient.o

#-------------------------------------------------------------------------------
# Target for "make all"
#-------------------------------------------------------------------------------
all:
	make clean
	make ommp2x 


#-------------------------------------------------------------------------------
# Target for "make clean"
#-------------------------------------------------------------------------------
clean:
	rm -rf core *.o ommp2x *~ *.*~ .*~ \#* .in* tca.* *vti* *.idl cxx_repository


#---
#Dependecies
#---
depend:
	makedepend $(CXXFLAGS) -Y $(SRC)
# DO NOT DELETE

plBrowser.o: plBrowser.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
plBrowser.o: scroller.h threadParms.h songDb.h sqlite3.h commandFactory.h
plBrowser.o: timer.h config.h playlist.h keyboard.h guiPos.h
plBrowser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
browser.o: browser.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
browser.o: scroller.h threadParms.h songDb.h sqlite3.h commandFactory.h
browser.o: timer.h config.h guiPos.h keyboard.h playlist.h
browser.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
playlist.o: playlist.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h config.h
playlist.o: libmpdclient.h scroller.h timer.h threadParms.h songDb.h
playlist.o: sqlite3.h commandFactory.h popup.h timestamp.h guiPos.h
playlist.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
main.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h config.h
main.o: browser.h libmpdclient.h scroller.h plBrowser.h bookmarks.h
main.o: playlist.h timer.h settings.h albumArt.h threadParms.h songDb.h
main.o: sqlite3.h overlay.h nowPlaying.h fullPlaying.h menuButton.h button.h
main.o: artButton.h buttonManager.h volButton.h rndRptButton.h rndButton.h
main.o: rptButton.h seekButton.h actionButton.h threadFunctions.h
main.o: commandFactory.h statsBar.h menu.h popup.h gp2xregs.h guiPos.h
main.o: keyboard.h /opt/pandora/arm-2009q3/usr/include/pnd_apps.h
main.o: /opt/pandora/arm-2009q3/usr/include/pnd_container.h
main.o: /opt/pandora/arm-2009q3/usr/include/pnd_discovery.h
config.o: config.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
config.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h utf8.h
config.o: utf8/checked.h utf8/core.h utf8/unchecked.h
nowPlaying.o: nowPlaying.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
nowPlaying.o: libmpdclient.h config.h playlist.h scroller.h timer.h
nowPlaying.o: threadParms.h songDb.h sqlite3.h commandFactory.h guiPos.h
nowPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
statsBar.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
statsBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
statsBar.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
statsBar.o: sqlite3.h commandFactory.h
commandFactory.o: commandFactory.h libmpdclient.h timer.h config.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
commandFactory.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
commandFactory.o: threadParms.h songDb.h sqlite3.h
popup.o: popup.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
popup.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
popup.o: sqlite3.h commandFactory.h gp2xregs.h guiPos.h keyboard.h
popup.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
scroller.o: scroller.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
scroller.o: config.h commandFactory.h timer.h
scroller.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
timestamp.o: timestamp.h
helpBar.o: helpBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
helpBar.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
helpBar.o: config.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
albumArt.o: albumArt.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
albumArt.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h threadParms.h
albumArt.o: libmpdclient.h songDb.h sqlite3.h config.h threadFunctions.h
threadFunctions.o: threadFunctions.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
threadFunctions.o: /opt/pandora/arm-2009q3/usr/include/SDL_rotozoom.h
threadFunctions.o: threadParms.h libmpdclient.h songDb.h sqlite3.h
bookmarks.o: bookmarks.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
bookmarks.o: scroller.h threadParms.h songDb.h sqlite3.h commandFactory.h
bookmarks.o: timer.h config.h playlist.h keyboard.h buttonManager.h
bookmarks.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h volButton.h
bookmarks.o: button.h rndRptButton.h rndButton.h rptButton.h seekButton.h
bookmarks.o: actionButton.h statsBar.h guiPos.h
gp2xregs.o: gp2xregs.h
overlay.o: overlay.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
overlay.o: config.h guiPos.h commandFactory.h timer.h playlist.h scroller.h
overlay.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
songDb.o: songDb.h libmpdclient.h sqlite3.h
keyboard.o: keyboard.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h config.h
keyboard.o: guiPos.h commandFactory.h libmpdclient.h timer.h
keyboard.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
button.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
button.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
button.o: sqlite3.h commandFactory.h button.h
button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
volButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
volButton.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
volButton.o: sqlite3.h commandFactory.h button.h
volButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h guiPos.h
volButton.o: volButton.h
buttonManager.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
buttonManager.o: libmpdclient.h config.h playlist.h scroller.h timer.h
buttonManager.o: threadParms.h songDb.h sqlite3.h commandFactory.h
buttonManager.o: buttonManager.h
buttonManager.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
buttonManager.o: volButton.h button.h rndRptButton.h rndButton.h rptButton.h
buttonManager.o: seekButton.h actionButton.h
seekButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
seekButton.o: libmpdclient.h config.h playlist.h scroller.h timer.h
seekButton.o: threadParms.h songDb.h sqlite3.h commandFactory.h button.h
seekButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h guiPos.h
seekButton.o: seekButton.h
rndButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
rndButton.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
rndButton.o: sqlite3.h commandFactory.h button.h
rndButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h guiPos.h
rndButton.o: rndButton.h
rptButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
rptButton.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
rptButton.o: sqlite3.h commandFactory.h button.h
rptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h guiPos.h
rptButton.o: rptButton.h
rndRptButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
rndRptButton.o: libmpdclient.h config.h playlist.h scroller.h timer.h
rndRptButton.o: threadParms.h songDb.h sqlite3.h commandFactory.h button.h
rndRptButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h guiPos.h
rndRptButton.o: rndRptButton.h
menu.o: menu.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
menu.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
menu.o: menuButton.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
menu.o: config.h button.h scroller.h threadParms.h songDb.h sqlite3.h
menu.o: commandFactory.h timer.h guiPos.h keyboard.h playlist.h
menuButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
menuButton.o: libmpdclient.h config.h playlist.h scroller.h timer.h
menuButton.o: threadParms.h songDb.h sqlite3.h commandFactory.h menuButton.h
menuButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h button.h
menuButton.o: guiPos.h rptButton.h
fullPlaying.o: fullPlaying.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
fullPlaying.o: libmpdclient.h menuButton.h
fullPlaying.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h config.h
fullPlaying.o: button.h artButton.h threadParms.h songDb.h sqlite3.h
fullPlaying.o: scroller.h commandFactory.h timer.h guiPos.h keyboard.h
fullPlaying.o: playlist.h
artButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
artButton.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
artButton.o: sqlite3.h commandFactory.h artButton.h
artButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h button.h
artButton.o: id3Button.h guiPos.h rptButton.h
settings.o: settings.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
settings.o: scroller.h threadParms.h songDb.h sqlite3.h commandFactory.h
settings.o: timer.h config.h gp2xregs.h playlist.h keyboard.h guiPos.h
settings.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h
id3Button.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h libmpdclient.h
id3Button.o: config.h playlist.h scroller.h timer.h threadParms.h songDb.h
id3Button.o: sqlite3.h commandFactory.h id3Button.h
id3Button.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h button.h
id3Button.o: guiPos.h rptButton.h
actionButton.o: statsBar.h /opt/pandora/arm-2009q3/usr/include/SDL/SDL.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_main.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_stdinc.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_config.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_platform.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/begin_code.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/close_code.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_audio.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_error.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_endian.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mutex.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_thread.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_rwops.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cdrom.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_cpuinfo.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_events.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_active.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keyboard.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_keysym.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_mouse.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_video.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_joystick.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_quit.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_loadso.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_timer.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_version.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_ttf.h
actionButton.o: libmpdclient.h config.h playlist.h scroller.h timer.h
actionButton.o: threadParms.h songDb.h sqlite3.h commandFactory.h button.h
actionButton.o: /opt/pandora/arm-2009q3/usr/include/SDL/SDL_image.h guiPos.h
actionButton.o: actionButton.h
