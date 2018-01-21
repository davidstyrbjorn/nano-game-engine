#pragma once

#include"../Component.h"
#include<string>

//#include"../../sound/SoundBuffer.h"
//#include"../../sound/SoundSource.h"
//#include"../../sound/NanoOpenAL.h"

namespace nano { namespace ecs { 

	class SoundComponent : public Component {
	private:
		//sound::SoundSource *m_source;
		//sound::SoundBuffer *m_buffer;
		
	public:
		// Compiler with path to sound to load
		SoundComponent(const char* a_soundFilePath);

		//const sound::SoundSource &GetSource();
	};

} }