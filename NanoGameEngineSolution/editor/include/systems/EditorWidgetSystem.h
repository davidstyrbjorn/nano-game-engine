#pragma once

#include"EditorSystem.h"

// Widgets include
#include"../widgets/UtilityWidget.h"
#include"../widgets/MenuBarWidget.h"

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

		/*
		// The widget to be constant on the screen
		void ShowWorldWidget();
		void ShowEntityInspector();
		void ShowConsoleWidget
		void ShowUtilitySelectWidget();
		void ShowUtilityInspectorWidget();
		*/
	};

} }