#pragma once

#include"EditorSystem.h"

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