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

void MusicHelper::playTrack(std::string file, bool loop)
{
	/* Load your soundfile and play it */
	const char* fileString = file.c_str();

	HSTREAM streamHandle;

	if (loop)
	{
		streamHandle = BASS_StreamCreateFile(FALSE, fileString, 0, 0, BASS_SAMPLE_LOOP);
	}
	else
	{
		streamHandle = BASS_StreamCreateFile(FALSE, fileString, 0, 0, 0);
	}

	audioStreams.push_back(streamHandle);
	BASS_ChannelPlay(streamHandle, FALSE);
}
