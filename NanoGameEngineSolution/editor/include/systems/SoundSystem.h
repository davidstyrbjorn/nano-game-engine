#pragma once

#include"EditorSystem.h"

namespace nano {
	namespace openal {
		class ContextDevice;
	}
}

namespace nano { namespace editor {

	class SoundSystem : public EditorSystem<SoundSystem> {
		friend class EditorSystem<SoundSystem>;
	private:
		// Private constructor (singleton)
		SoundSystem() { }

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