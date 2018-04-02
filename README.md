Z Stream is a GUI-less music player. I made this program with the intent to select, play, and pause music while play video games, without having to tab out of the game to change songs.

To set up, Add a Libraries folder to the directory of the executable.
Then, create a folder for each groups/library of songs that you want.
Finally add whatever songs you want to the playlist.

The path to the song from the executing directory should be
./Libraries/An_Arbitrary_Folder/Song.wav

Note, for my version of SDL Mixer, only wav files seem to work. MP3s will not work with the precompiled executable

USAGE:
            |   RIGHT SHIFT  |   RIGHT CTRL  |
            |--------------------------------|
UP ARROW    | Pause/play     | Unused*       |
DOWN ARROW  | Exit program   | Unused*       |
LEFT ARROW  | Play new song  | Unused*       |
RIGHT ARROW | New lib & song | Unused*       |

* Future implementations will use these key combinations for new features
