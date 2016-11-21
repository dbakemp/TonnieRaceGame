#include "MusicHelper.h"
#include "Bass.h"


MusicHelper::MusicHelper()
{
	int device = -1; // Default Sounddevice
	int freq = 44100; // Sample rate (Hz)
	HSTREAM streamHandle; // Handle for open stream


	/* Initialize output device */
	BASS_Init(device, freq, 0, 0, NULL);


	/* Load your soundfile and play it */
	streamHandle = BASS_StreamCreateFile(FALSE, "C:\\Users\\Tim\\Desktop\\background.mp3", 0, 0, 0);
	BASS_ChannelPlay(streamHandle, FALSE);

}


MusicHelper::~MusicHelper()
{
}
