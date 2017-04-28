#pragma once
#ifndef SOUNDFUNCT_H
#define SOUNDFUNCT_H


#include "SDL.h"
#include "SDL_mixer.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class SoundFunct {
public:
	void PlayNoise(char *);
	void ClearNoise();	// Clear noise just removes the current song that's playing and deallocs it
	void InitAll();
	void GetSize();
	char * GetSong();

private:
	Mix_Music	*Sound;
	short int	Size;
	HANDLE		Handle;
	WIN32_FIND_DATA	SearchData;
	char * File;
};


#endif
