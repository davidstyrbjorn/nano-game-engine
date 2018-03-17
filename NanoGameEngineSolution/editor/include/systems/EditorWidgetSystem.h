#pragma once

#include"EditorSystem.h"

// Widgets include
#include"../widgets/Widgets.h"

#include"../EventHandler.h"

namespace nano { namespace editor { 

	class EditorWidgetSystem : public EditorSystem<EditorWidgetSystem> {
		friend class EditorSystem<EditorWidgetSystem>;
	private:
		// Private constructor (singleton)
		EditorWidgetSystem() { }

		bool m_renderWidgets = true;

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

		// Other
		bool GetRenderWidgets();
		void SetRenderWidgets(bool a_value);
		EventHandler& GetEventHandler();
	};

} }