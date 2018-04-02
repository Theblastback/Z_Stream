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

class SoundFunct {
public:
	void play_noise();
	void clear_noise();	// Clear noise just removes the current song that's playing and deallocs it
	void init_all();
	void get_size();
	void change_library();
	void free_library();

private:
	void get_song();

	Mix_Music	*	sound;
	short int		size;

	short int		lib_chosen;
	short int		lib_total;

	HANDLE		handle;
	WIN32_FIND_DATA	search_data;

	char		**	libraries;
	char		*	search_param;
	char		*	file;
};


#endif
