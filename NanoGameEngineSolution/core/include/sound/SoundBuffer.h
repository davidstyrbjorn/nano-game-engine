#pragma once

namespace nano { namespace openal { 

	class SoundBuffer {
	private:
		unsigned int buffer;
	
	public:
		// Constructor
		SoundBuffer();
		
		// Destructor 
		~SoundBuffer();
		
		// Sets the sound buffers data 
		void SetData(int a_format, void* a_data, int a_size, int a_sampleRate);
		
		// Returns sound buffer
		unsigned int GetBufferId() const { return buffer; }
	};

} } 