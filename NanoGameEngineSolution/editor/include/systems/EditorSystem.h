#pragma once

namespace nano { namespace editor { 

	// Base class for every editor system singleton class
	template<typename T>
	class EditorSystem {
	public:
		static T* getInstance() {
			static T* instance;
			if (instance == nullptr)
				instance = new T();
			return instance;
		}

		// Gets called on editor start
		virtual void Start() = 0;

		// Gets called every tick
		virtual void Update() = 0;

		// Gets called at a fixed tick rate
		virtual void FixedUpdate() { }

		// Gets called on editor close
		virtual void Quit() = 0;
	};

} }