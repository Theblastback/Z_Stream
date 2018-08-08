#include "SoundFunct.h"
#include <iostream>

using namespace std;



void SoundFunct :: init_all() {
	this->sound = NULL;
	memset(&this->search_data, 0, sizeof(WIN32_FIND_DATA));
	this->file = "";
	this->lib_chosen = 0;

	// Initializing the library array
	this->handle = FindFirstFile(".\\Libraries\\*", &this->search_data);

	// Determine how many libraries there are in the folder, to determine how much space to malloc for the libraries array
	while (this->handle != INVALID_HANDLE_VALUE) { 
		if (strcmp(".", this->search_data.cFileName) && strcmp("..", this->search_data.cFileName) ) {
			char * temp_name = (char *) malloc(15 + strlen(this->search_data.cFileName) * sizeof(char));
			strcpy(temp_name, ".\\Libraries\\");
			strcat(temp_name, this->search_data.cFileName);
			strcat(temp_name, "/");
			this->libraries_list.push_back(temp_name);
			temp_name = NULL;
		}

		if (FindNextFile(this->handle, &this->search_data) == FALSE)
			break;
	}

	CloseHandle(this->handle);

	this->search_param = (char *)malloc(sizeof(MAX_PATH));

	this->lib_chosen = 0;

	strcpy(this->search_param, this->libraries_list[this->lib_chosen]);
	strcat(this->search_param, "*");

	this->load_song_list();
}

void SoundFunct :: change_library() {
	// Free up the old song list
	for (unsigned int index = 0; index < this -> song_list.size(); index++)
		free(this -> song_list[index]);

	this->past_songs.clear();

	this->lib_chosen = (this->lib_chosen + 1) % this->libraries_list.size();

	strcpy(this->search_param, this->libraries_list[this->lib_chosen]);
	strcat(this->search_param, "*");

	this->clear_noise();

	this->load_song_list();
}

void SoundFunct :: play_noise() {
	this->get_song();
	this->sound = Mix_LoadMUS(this->file.c_str());
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

}

void SoundFunct :: load_song_list() {
	// Generic randomization here. 
	srand((unsigned int)time(NULL));

	// The directory being searched is arbitrary. Can be swapped with any directory that your songs are located in
	handle = FindFirstFile(this->search_param, &this->search_data);

	while (this->handle != INVALID_HANDLE_VALUE) {
		// Copies the names of all the songs into song_list, except for . and ..
		if (strcmp(".", this->search_data.cFileName) && strcmp("..", this->search_data.cFileName)) {
			// Save memory space by only allocating enough space for the filename. Max filename size is 260 bytes
			char * temp_name = (char *) malloc((strlen(this->search_data.cFileName) + 1) * sizeof(char));
			strcpy(temp_name, this->search_data.cFileName);
			song_list.push_back(temp_name);
			temp_name = NULL;
		}

		if (FindNextFile(this->handle, &this->search_data) == FALSE)
			break;
	}

	CloseHandle(this->handle);
}

void SoundFunct :: get_song() {
	short int song;

	song = rand() % this->song_list.size(); // Randomly selects song

	// Check to see if this song (indicated by song) has already been played
	if (this->past_songs.size()) {
		for (std::list<int>::iterator index = past_songs.begin(); index != past_songs.end(); index++) {
			// Song has already been played, play a new one
			cout << song << "==" << *index << endl;
			if (song == *index) {
				this->get_song();
				return;
			}
		}
		// New song has been selected
		this->file = std::string(this->libraries_list[this->lib_chosen]) + std::string(song_list[song]);
	} else {
		this->file = std::string(this->libraries_list[this->lib_chosen]) + std::string(song_list[song]);
	}

	// Add song to list
	past_songs.push_front(song);
	// Check to see if list has exceeded 33% of the songs in the library
	if (past_songs.size() > (song_list.size() / 3))
		past_songs.pop_back();

}

void SoundFunct::free_library() {
	short index;
	for (index = 0; index < this->libraries_list.size(); index++) {
		free(this->libraries_list[index]);
	}
	free(this->search_param);
}