#include "SoundFunct.h"

void SoundFunct :: InitAll() {
	Sound = NULL;
	memset(&SearchData, 0, sizeof(WIN32_FIND_DATA));
	File = NULL;	
}


void SoundFunct :: PlayNoise(char *Path) {
	Sound = Mix_LoadMUS(Path);
	if (Sound == NULL) // No point in proceeding if sound cannot be obtained to play
		return;

	Mix_PlayMusic(Sound, 0); // Play the sound, and loop '0' times
}


void SoundFunct :: ClearNoise() {
	// Must check these as, through testing, these would often not be allocated to begin with
	if (Sound != NULL) {
		Mix_FreeMusic(Sound);
		Sound = NULL;
	}
	if (File != NULL) {
		free(File);
		File = NULL;
	}
}

void SoundFunct :: GetSize() {
	Size = 0; // Zero out the size of the directory

	srand((unsigned int)time(NULL));

	Handle = FindFirstFile("c:\\Users\\Mpzar_000\\Documents\\Auto-Music\\Music\\*", &SearchData); // The directory being searched is arbitrary. Can be swapped with any directory that your songs are located in

	while (Handle != INVALID_HANDLE_VALUE) { // Does the measuring of how many songs are in the directory
		Size++;
		if (FindNextFile(Handle, &SearchData) == FALSE)
			break;
	}
	CloseHandle(Handle);
}

char * SoundFunct :: GetSong() {
	File = (char*) malloc(sizeof(char)*100);
	int Index;


	Index = rand() % Size; // Randomly selects song

	Handle = FindFirstFile(".\\Music\\*", &SearchData);

	while ( (Handle != INVALID_HANDLE_VALUE) && (Index > 1) ) { // Goes to the song, and pretty much selects it
		Index--;
		if (FindNextFile(Handle, &SearchData) == FALSE)
			break;
	}

	strcpy(File, ".\\Music\\"); // Directory is based off of the auto music directory, so I gotta add this in front of the song file's name
	strcat(File, SearchData.cFileName); 

	CloseHandle(Handle);
	return(File);
}