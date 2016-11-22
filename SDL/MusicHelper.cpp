#include "MusicHelper.h"
#include <string>


MusicHelper::MusicHelper()
{
	int device = -1; // Default Sounddevice
	int freq = 44100; // Sample rate (Hz)

	/* Initialize output device */
	BASS_Init(device, freq, 0, 0, NULL);
}

MusicHelper::~MusicHelper()
{
}

void MusicHelper::playSingleTrack(std::string file) {
	/* Load your soundfile and play it */
	/*char fileArray[file.size + 1];
	strcpy(fileArray, file.c_str());*/

	HSTREAM streamHandle = BASS_StreamCreateFile(FALSE, "music\\title.mp3", 0, 0, 0);
	BASS_ChannelPlay(streamHandle, FALSE);
}

void MusicHelper::playBackgroundMusic(std::string file) {
	/* Load your soundfile and play it */
	/*char fileArray[file.size + 1];
	strcpy(fileArray, file.c_str());*/

	HSTREAM streamHandle = BASS_StreamCreateFile(FALSE, "music\\boerharms.mp3", 0, 0, BASS_SAMPLE_LOOP);
	//audioStreams.push_back(streamHandle);
	BASS_ChannelPlay(streamHandle, FALSE);
}
