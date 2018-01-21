#include "SoundBuffer.h"

#include<alc.h>
#include<al.h>

nano::sound::SoundBuffer::SoundBuffer()
{
	alGenBuffers(1, &buffer);
}

nano::sound::SoundBuffer::~SoundBuffer()
{
	alDeleteBuffers(1, &buffer);
}

void nano::sound::SoundBuffer::SetData(int a_format, char * a_data, int a_size, int a_sampleRate)
{
	alBufferData(buffer, a_format, a_data, a_size, a_sampleRate);

	if (alGetError() != AL_NO_ERROR) {
		alDeleteBuffers(1, &buffer);
		return;
	}
}
