#pragma once

typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;

namespace nano { namespace openal { 

	class ContextDevice {
	private:
		ALCcontext *m_context;
		ALCdevice *m_device;

	public:
		// Default Constructor
		ContextDevice();

		// Destructor
		~ContextDevice();

		// Creates OpenAL context
		void CreateContext();

		// Creates OpenAL device
		void CreateDevice();
	};

} } 