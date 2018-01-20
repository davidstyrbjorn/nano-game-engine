#include"../include/sound/SoundBuffer.h"

#include<iostream>

#include<alc.h>
#include<al.h>

namespace nano { namespace sound {

		SoundBuffer::SoundBuffer()
		{
			alGenBuffers(1, &buffer);
		}

		SoundBuffer::~SoundBuffer()
		{
			alDeleteBuffers(1, &buffer);
		}

		void SoundBuffer::setData(int a_format, char* a_data, int a_size, int a_sampleRate)
		{
			alBufferData(buffer, a_format, a_data, a_size, a_sampleRate);

			if (alGetError() != AL_NO_ERROR) {
				std::cout << "Error creating buffer" << std::endl;
				alDeleteBuffers(1, &buffer);
				return;
			}
		}
} }