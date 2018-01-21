#pragma once

namespace nano { namespace sound { 

	class SoundBuffer {
	private:
		unsigned int buffer;
	
	public:
		// Constructor
		SoundBuffer();
		
		// Destructor 
		~SoundBuffer();
		
		// Sets the sound buffers data 
		void SetData(int a_format, char* a_data, int a_size, int a_sampleRate);
		
		// Returns sound buffer
		unsigned int GetBufferId() const { return buffer; }
	};

} } 