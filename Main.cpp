#include "SoundFunct.h"


// Created by Mitchell P. Zarnoch


int main(int argc, char **argv) {
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false); // This hides the console window once the program has been initiated

	unsigned char Toggle; // Will serve as the exit statement for the main loop, and potentially as a check to see if SDL was initialized
	short int Total = 0; // Total songs located in directory
	SoundFunct Function; // This allows access to the functions inside the ImageFunct class
	char * Song;


	if (((Toggle = SDL_Init(SDL_INIT_AUDIO)) != -1) && (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1)) {
		// Above statement ensures that SDL and SDL_mixer are both initiated. Reason why I did it this way is because visual studio can't "find" stdlib.h
		Function.InitAll(); // NULL's all of ImageFunct's private variables
		Function.GetSize();
		Toggle = 1;
		while (Toggle) {
			// One can only change songs by 'enabling' the controls; Should help prevent accidental song switches
			// NOTE This can only detect songs in its dedicated directory, and there's no implementation to automatically copy song files over from one directory to another
			if ( ((GetAsyncKeyState(VK_RSHIFT) & 0x8000) > 0) || ((Toggle | Mix_PlayingMusic()) == 2) ) { // Checks to see if right shift is being pressed
				if ( ((GetAsyncKeyState(VK_LEFT) & 0x8000) > 0) || ( (Toggle | Mix_PlayingMusic()) == 2) ) { // Checks if the left arrow key is pressed, or if song has ended
					Song = Function.GetSong();
					Function.ClearNoise();
					Function.PlayNoise(Song);
					SDL_Delay(1000); // Delay for 1 second before going onto next song
					Toggle = 2;
				} else if ( ((GetAsyncKeyState(VK_UP) & 0x8000) > 0) && (Toggle == 2) ) { // Pause the song
					if (Mix_PausedMusic() == 0) // Returns 0 if music is playing
						Mix_PauseMusic();
					else
						Mix_ResumeMusic();
					SDL_Delay(1000);
				} else if ( (GetAsyncKeyState(VK_DOWN) & 0X8000) > 0) { // End sequence
					Toggle = 0;
				}
			}
			SDL_Delay(1);
		}
		// No matter what, SDL_mixer would have been initialized by now
		// Freeing the files used as well
		Function.ClearNoise();
		Mix_CloseAudio();
	}
	// Closing up shop for SDL, that is if it's been initialized
	if (Toggle == 0)
		SDL_Quit();
				
	// Must free the hidden console, otherwise this could eat up memory
	FreeConsole();
	return 0;
}