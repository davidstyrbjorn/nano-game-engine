#pragma once

namespace nano { namespace editor { 

	// Base class for every editor system singleton class
	class EditorSystem {
	public:
		// Gets called on editor start
		virtual void Start() = 0;

		// Gets called every tick
		virtual void Update() = 0;

		// Gets called on editor close
		virtual void Quit() = 0;
	};

} }