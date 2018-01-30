#pragma once

#include"EditorSystem.h"

namespace nano {
	namespace openal {
		class ContextDevice;
	}
}

namespace nano { namespace editor {

	class SoundSystem : public EditorSystem {
	private:
		// Private constructor (singleton)
		SoundSystem();

		// One sole instance
		static SoundSystem* _instance;

	public:
		static SoundSystem* Instance();

	private:
		// System members
		openal::ContextDevice* m_contextDevice;

	public:
		// System methods
		void Start() override;
		void Update() override;
		void Quit() override;
	};

} }