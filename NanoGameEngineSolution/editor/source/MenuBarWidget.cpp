#include"../include/widgets/Widgets.h"


#include"../include/DearImGui/imgui.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/LevelParser.h"
#include"../include/systems/EditorConfig.h"

#include<iostream>
#include<fstream>

namespace nano { namespace editor {

	bool DoesFileExist(std::string a_filePath)
	{
		std::ifstream stream(a_filePath);
		if (stream.is_open()) {
			return true;
		}

		return false;
	}

	MenuBarWidget::MenuBarWidget()
	{
	}

	void MenuBarWidget::Start()
	{

	}

	void MenuBarWidget::Update()
	{

	}

	void MenuBarWidget::Render()
	{

		static bool m_showSaveLevelWidget = false;
		static bool m_showCreditsWidget = false;
		static LevelParser levelParser;

		if (ImGui::BeginMainMenuBar()) 
		{

			if (ImGui::BeginMenu("File")) 
			{
				if (ImGui::Selectable("Save Level")) {
					m_showSaveLevelWidget = true;
				}
				if (ImGui::Selectable("Load Level")) {
					std::vector<ecs::Entity*> temp = levelParser.GetParsedLevelFromFile("level.txt").entities;
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
			if (ImGui::BeginMenu("About")) {
				if (ImGui::Selectable("Version")) {

				}
				if (ImGui::Selectable("Credit")) {
					m_showCreditsWidget = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Entity"))
			{
				if (ImGui::Selectable("Create New")) {
					WorldSystem::Instance()->CreateNewEntity("unnamed");
					// Send this event to the event handler!
					EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_created", "unnamed"));
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (m_showCreditsWidget) {
			ImGui::Begin("Credits", &m_showCreditsWidget, ImVec2(300, 200), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);
			ImGui::Text("Programmer: David Styrbjörn");
			ImGui::Text("License: GNU General Public License v3.0");
			ImGui::End();
		}
		if (m_showSaveLevelWidget) {
			static int width = 300;
			static int height = 200;
			// Center the window 
			ImGui::SetNextWindowPos(ImVec2((EditorConfig::Instance()->getWindowSize().x / 2)-(width/2), (EditorConfig::Instance()->getWindowSize().y/2)-(height)));
			ImGui::Begin("Save Level", &m_showSaveLevelWidget, ImVec2(width, height), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);

			static char buffer[128] = "";
			ImGui::InputText("Level Name", buffer, 128);
			if (ImGui::Button("Save")) {
				std::string location = "resources\\levels\\" + std::string(buffer) + ".txt";
				// Check if there's already a saved level with this name!
				// @ TODO: Handle if there's already a existing level with said name
				if (DoesFileExist(location)) {
					//std::cout << "Hello! This level already exists" << std::endl;
					levelParser.ParseCurrentLevelToFile(location.c_str());
				}
				else {
					//std::cout << "File does not exist big lol" << std::endl;
					levelParser.ParseCurrentLevelToFile(location.c_str());
				}

				// Done with saving
				m_showSaveLevelWidget = false;
				std::string message = "Saved Level " + std::string(buffer) + " at resources/levels/" + std::string(buffer) + ".txt";
				EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, message));
			}

			ImGui::End();
		}
	}
}
}