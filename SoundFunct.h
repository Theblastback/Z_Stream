#pragma once
#ifndef SOUNDFUNCT_H
#define SOUNDFUNCT_H


#include "SDL.h"
#include "SDL_mixer.h"
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <vector>
#include <list>

class SoundFunct {
public:
	void play_noise();
	void clear_noise();	// Clear noise just removes the current song that's playing and deallocs it
	void init_all();
	void change_library();
	void free_library();
	void load_song_list();

private:

	void get_song();

	Mix_Music	*	sound;

	short int		lib_chosen;

	std::vector<char> list;

	HANDLE		handle;
	WIN32_FIND_DATA	search_data;

	std::vector<char *>	libraries_list;
	std::vector<char *>	song_list;
	std::list<int>	past_songs;
	char		*	search_param;
	std::string	file;
};


#endif
