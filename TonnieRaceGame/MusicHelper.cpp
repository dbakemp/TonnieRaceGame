#include "MusicHelper.h"
#include "CIntegerHelper.h"
#include "CDebugLogger.h"
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

void MusicHelper::playBackgroundMusic()
{
	std::string songs[] = {"hdl.mp3", "intro.mp3", "myfavouritegame.mp3", "paradisecity.mp3", "spaansetroep.mp3", "daargaatze.mp3", "boerharms.mp3"};

	int songIndex = CIntegerHelper::GetRandomIntBetween(0, 6);

	playTrack("Resources/Music/" + songs[songIndex], true);
}

void MusicHelper::pauseMusic()
{
	for (HSTREAM stream : audioStreams)
	{
		BASS_ChannelPause(stream);
	}
}

void MusicHelper::resumeMusic()
{
	for (HSTREAM stream : audioStreams)
	{
		BASS_ChannelPlay(stream, true);
	}
}

void MusicHelper::playTrack(std::string file, bool loop)
{
	CDebugLogger::PrintDebug(file);

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

void MusicHelper::stopAll()
{
	for (HSTREAM stream : audioStreams)
	{
		BASS_ChannelStop(stream);
	}
	audioStreams.clear();
}
