#include"../include/widgets/Widgets.h"

#include"../include/DearImGui/imgui.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/LevelParser.h"
#include"../include/systems/EditorConfig.h"

#include<iostream>
#include<fstream>
#include<dirent.h>
#include<sys\types.h>

namespace nano { namespace editor {

	bool DoesFileExist(std::string a_filePath)
	{
		std::ifstream stream(a_filePath);
		if (stream.is_open()) {
			return true;
		}

		return false;
	}

	void ReadDirectory(const std::string& name, std::vector<std::string>& v)
	{
		DIR* dirp = opendir(name.c_str());
		struct dirent * dp;
		while ((dp = readdir(dirp)) != NULL) {
			v.push_back(dp->d_name);
		}
		closedir(dirp);
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
		static bool m_showLoadLevelWidget = false;
		static bool m_showSaveLevelWidget = false;
		static bool m_showCreditsWidget = false;
		static LevelParser levelParser;

		if (ImGui::BeginMainMenuBar()) 
		{

			if (ImGui::BeginMenu("File")) 
			{
				if (ImGui::Selectable("Save Level")) {
					m_showSaveLevelWidget = true;
					m_showLoadLevelWidget = false;
				}
				if (ImGui::Selectable("Load Level")) {
					m_showLoadLevelWidget = true;
					m_showSaveLevelWidget = false;
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Invoke")) 
			{
				if (ImGui::Selectable("Run Game")) {
					// Run engine.exe here please
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
		else if (m_showLoadLevelWidget) {
			static int width = 300;
			static int height = 200;
			// Center the window 
			ImGui::SetNextWindowPos(ImVec2((EditorConfig::Instance()->getWindowSize().x / 2) - (width / 2), (EditorConfig::Instance()->getWindowSize().y / 2) - (height)));
			ImGui::Begin("Load Level", &m_showLoadLevelWidget, ImVec2(width, height), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);

			static char buffer[128] = "";
			bool enter = ImGui::InputText("Level Name", buffer, 128, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue);
			if (ImGui::Button("Load") || enter) {
				// TODO @: Check if file exists before loading it
				std::string location = "resources\\levels\\" + std::string(buffer) + ".txt";
				std::vector<ecs::Entity*> temp = levelParser.GetParsedLevelFromFile(location.c_str()).entities;
				WorldSystem::Instance()->LoadedNewLevel(temp);

				// Done with loading
				m_showLoadLevelWidget = false;
			}

			ImGui::Separator();

			// List levels inside resources\levels\*
			std::vector<std::string> fileList;
			ReadDirectory("resources\\levels\\", fileList);
			for (std::string i : fileList) {
				if (i != "." && i != "..") {
					std::string temp = i.substr(0, i.length() - 4);
					if (ImGui::Selectable(temp.c_str())) {
						// TODO @: Check if file exists before loading it
						std::string location = "resources\\levels\\" + temp + ".txt";
						std::vector<ecs::Entity*> temp = levelParser.GetParsedLevelFromFile(location.c_str()).entities;
						WorldSystem::Instance()->LoadedNewLevel(temp);

						// Done with loading
						m_showLoadLevelWidget = false;
					}
				}
			}

			ImGui::End();
		}
	}
}
}