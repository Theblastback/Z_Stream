#include "SoundFunct.h"


// Created by Mitchell P. Zarnoch


int main(int argc, char **argv) {
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false); // This hides the console window once the program has been initiated

	unsigned char toggle; // Will serve as the exit statement for the main loop, and potentially as a check to see if SDL was initialized
	short int total = 0; // Total songs located in directory
	SoundFunct function; // This allows access to the functions inside the ImageFunct class
	


	if (((toggle = SDL_Init(SDL_INIT_AUDIO)) != -1) && (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1)) {
		// Above statement ensures that SDL and SDL_mixer are both initiated. Reason why I did it this way is because visual studio can't "find" stdlib.h
		function.init_all();
		toggle = 1;
		while (toggle) {
			// One can only change songs by 'enabling' the controls; Should help prevent accidental song switches
			// NOTE This can only detect songs in its dedicated directory, and there's no implementation to automatically copy song files over from one directory to another
			if ( ((GetAsyncKeyState(VK_RSHIFT) & 0x8000) > 0) || ((toggle | Mix_PlayingMusic()) == 2) ) { // Checks to see if right shift is being pressed
				if ( ((GetAsyncKeyState(VK_LEFT) & 0x8000) > 0) || ( (toggle | Mix_PlayingMusic()) == 2) ) { // Checks if the left arrow key is pressed, or if song has ended
					function.clear_noise();
					function.play_noise();
					SDL_Delay(1000); // Delay for 1 second before going onto next song
					toggle = 2;
				} else if ( ((GetAsyncKeyState(VK_UP) & 0x8000) > 0) && (toggle == 2) ) { // Pause the song
					if (Mix_PausedMusic() == 0) // Returns 0 if music is playing
						Mix_PauseMusic();
					else
						Mix_ResumeMusic();
					SDL_Delay(1000);
				} else if ( (GetAsyncKeyState(VK_DOWN) & 0X8000) > 0) { // End sequence
					toggle = 0;
				} else if ( (GetAsyncKeyState(VK_RIGHT) & 0x8000) > 0) { // Change libraries
					function.change_library();
					SDL_Delay(1000);
				}
			} else if ( ((GetAsyncKeyState(VK_RCONTROL) & 0x8000) > 0) || ((toggle | Mix_PlayingMusic()) == 2) ) {
				if ( (GetAsyncKeyState(VK_UP) & 0x8000) > 0) { // Volume up
					Mix_VolumeMusic(Mix_VolumeMusic(-1) + 8);
					SDL_Delay(500);
				} else if ( (GetAsyncKeyState(VK_DOWN) & 0x8000) > 0) {
					Mix_VolumeMusic(Mix_VolumeMusic(-1) - 8);
					SDL_Delay(500);
				}
			}
			SDL_Delay(1);
		}
		// No matter what, SDL_mixer would have been initialized by now
		// Freeing the files used as well
		function.clear_noise();
		function.free_library();
		Mix_CloseAudio();
	}
	// Closing up shop for SDL, that is if it's been initialized
	if (toggle == 0)
		SDL_Quit();
				
	// Must free the hidden console, otherwise this could eat up memory
	FreeConsole();
	return 0;
}