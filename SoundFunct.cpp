#include "SoundFunct.h"
#include <iostream>

using namespace std;



void SoundFunct :: init_all() {
	this->sound = NULL;
	memset(&this->search_data, 0, sizeof(WIN32_FIND_DATA));
	this->file = NULL;
	this->lib_chosen = 0;

	// Initializing the library array
	this->size = 0;
	this->handle = FindFirstFile(".\\Libraries\\*", &this->search_data);

	while (this->handle != INVALID_HANDLE_VALUE) { // Does the measuring of how many songs are in the directory
		if (strcmp(".", this->search_data.cFileName) && strcmp("..", this->search_data.cFileName) ) {
			size++;
		}
		if (FindNextFile(this->handle, &this->search_data) == FALSE)
			break;
	}
	CloseHandle(this->handle);
	this->lib_total = this->size;

	// Filling the library array
	this->libraries = (char **)malloc(sizeof(char *) * this->lib_total);

	for (short index = 0; index < this->lib_total; index++)
		this->libraries[index] = (char *)malloc(sizeof(char) * MAX_PATH);

	this->search_param = (char *)malloc(sizeof(MAX_PATH));

	this->handle = FindFirstFile(".\\Libraries\\*", &this->search_data);
	while (this->handle != INVALID_HANDLE_VALUE) { // Does the measuring of how many songs are in the directory
		if (strcmp(".", this->search_data.cFileName) && strcmp("..", this->search_data.cFileName)) {

			strcpy(this->libraries[this->lib_chosen], ".\\Libraries\\");

			strcat(this->libraries[this->lib_chosen], this->search_data.cFileName);
			strcat(this->libraries[this->lib_chosen], "/");


			this->lib_chosen++;
		}
		if (FindNextFile(this->handle, &this->search_data) == FALSE)
			break;
	}

	this->lib_chosen = 0;

	strcpy(this->search_param, this->libraries[this->lib_chosen]);
	strcat(this->search_param, "*");

	this->get_size();
}

void SoundFunct :: change_library() {
	this->lib_chosen = (this->lib_chosen + 1) % this->lib_total;

	strcpy(this->search_param, this->libraries[this->lib_chosen]);
	strcat(this->search_param, "*");

	this->clear_noise();

	this->get_size();
}

void SoundFunct :: play_noise() {
	this->get_song();
	this->sound = Mix_LoadMUS(this->file);
	if (this->sound == NULL) // No point in proceeding if sound cannot be obtained to play
		return;

	Mix_PlayMusic(this->sound, 0); // Play the sound, and loop '0' times
}


void SoundFunct :: clear_noise() {
	// Must check these as, through testing, these would often not be allocated to begin with
	if (this->sound != NULL) {
		Mix_FreeMusic(this->sound);
		this->sound = NULL;
	}
	if ( this->file != NULL ) {
		free(this->file);
		this->file = NULL;
	}
}

void SoundFunct :: get_size() {
	this->size = 0; // Zero out the size of the directory


	srand((unsigned int)time(NULL));


	handle = FindFirstFile(this->search_param, &this->search_data); // The directory being searched is arbitrary. Can be swapped with any directory that your songs are located in

	while (this->handle != INVALID_HANDLE_VALUE) { // Does the measuring of how many songs are in the directory
		this->size++;
		if (FindNextFile(this->handle, &this->search_data) == FALSE)
			break;
	}
	CloseHandle(this->handle);
}

void SoundFunct :: get_song() {
	short int index;
	this->file = (char *)malloc(sizeof(char) * (MAX_PATH + MAX_PATH));


	this->get_size();

	index = rand() % this->size; // Randomly selects song


	this->handle = FindFirstFile(search_param, &search_data);

	while ( (this->handle != INVALID_HANDLE_VALUE) && (index > 1) ) { // Goes to the song, and pretty much selects it
		if (strcmp(".", this->search_data.cFileName) && strcmp("..", this->search_data.cFileName))
			index--;
		if (FindNextFile(this->handle, &this->search_data) == FALSE)
			break;

	}

	strcpy(this->file, this->libraries[this->lib_chosen]); // Errors here
	strcat(this->file, this->search_data.cFileName);

	CloseHandle(this->handle);
}

void SoundFunct::free_library() {
	short index;
	for (index = 0; index < this->lib_total; index++) {
		free(this->libraries[index]);
	}
	free(this->libraries);
	free(this->file);
	free(this->search_param);
}