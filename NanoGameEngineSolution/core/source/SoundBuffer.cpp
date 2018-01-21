#include "../include/sound/SoundBuffer.h"

#include<alc.h>
#include<al.h>

namespace nano { namespace openal { 

	SoundBuffer::SoundBuffer()
	{
		alGenBuffers(1, &buffer);
	}

	SoundBuffer::~SoundBuffer()
	{
		alDeleteBuffers(1, &buffer);
	}

	void SoundBuffer::SetData(int a_format, char * a_data, int a_size, int a_sampleRate)
	{
		alBufferData(buffer, a_format, a_data, a_size, a_sampleRate);

		if (alGetError() != AL_NO_ERROR) {
			alDeleteBuffers(1, &buffer);
			return;
		}
	}

} } 