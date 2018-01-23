#pragma once

namespace nano { namespace editor {
	
	class EditorWidget {
	public:
		// Called on editor start
		virtual void Start() = 0;

		// Called on editor update
		virtual void Update() = 0;

		// Called on editor render
		virtual void Render() = 0;
	};
	
} }