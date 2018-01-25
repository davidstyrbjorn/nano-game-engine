#include"../include/widgets/MenuBarWidget.h"

#include<CoreConfig.h>
#include<iostream>

#include"../include/DearImGui/imgui.h"

#include"../include/systems/EntityManagerSystem.h"
#include"../include/systems/EditorWidgetSystem.h"

namespace nano { namespace editor {

	MenuBarWidget::MenuBarWidget()
	{
	}

	void MenuBarWidget::Start()
	{
		// Getting acess to the config file
		m_config = CoreConfig::Instance();
	}

	void MenuBarWidget::Update()
	{

	}

	void MenuBarWidget::Render()
	{
		if (ImGui::BeginMainMenuBar()) 
		{

			if (ImGui::BeginMenu("File")) 
			{
				if (ImGui::Selectable("Save Level")) {

				}
				if (ImGui::Selectable("Load Level")) {

				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Invoke")) 
			{
				if (ImGui::Selectable("Compile & Run")) {

				}
				if (ImGui::Selectable("Compile")) {

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Entity"))
			{
				if (ImGui::Selectable("Create New")) {
					EntityManagerSystem::Instance()->CreateNewEntity("unnamed");
					// Test case!
					// Send this event to the event handler!
					EntityEvent _event;
					_event._type = EventTypes::CREATED_ENTITY;
					_event._id = "unnamed";
					EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(_event);
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}
}