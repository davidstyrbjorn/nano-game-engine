#pragma once

#include"EditorSystem.h"

// Widgets include
#include"../widgets/Widgets.h"

#include"../EventHandler.h"

namespace nano { namespace editor { 

	class EditorWidgetSystem : public EditorSystem {
	private:
		// Private constructor (singleton)
		EditorWidgetSystem() { }

		// The one sole instance
		static EditorWidgetSystem *_instance;

	public:
		// Singleton connection
		static EditorWidgetSystem *Instance();

	private:
		// Widgets
		MenuBarWidget m_menuBarWidget;
		UtilityWidget m_utilityWidget;
		UtilitySelectWidget m_utilitySelectWidget;
		EntitySelectWidget m_entitySelectWidget;
		EntityInspectorWidget m_entityInspectorWidget;
		ConsoleWidget m_consoleWidget;

		// Other
		EventHandler *m_eventHandler;

		// Methods
		void SetupStyle();

	public:
		// EditorSystem base class
		void Start() override;
		void Update() override;
		void Quit() override;

		// Render routines
		void Begin();
		void Flush();

		// Other methods
		EventHandler& GetEventHandler();
	};

} }