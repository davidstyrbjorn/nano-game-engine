#include"../include/widgets/Widgets.h"

#include"../include/DearImGui/imgui.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/systems/RendererSystem.h"
#include"../include/LevelParser.h"
#include"../include/systems/EditorConfig.h"

#include<graphics\Camera.h>
#include<graphics\Simple_Renderer.h>

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
		static bool m_showVersionWidget = false;
		static LevelParser levelParser;
		std::string currentLevelName = EditorConfig::Instance()->getCurrentlyLevelName();

		if (ImGui::BeginMainMenuBar()) 
		{

			if (ImGui::BeginMenu("File")) 
			{
				if (ImGui::Selectable("Save Level As")) {
					m_showSaveLevelWidget = true;
					m_showLoadLevelWidget = false;
				}
				if (currentLevelName != "none") {
					std::string temp = "Save Level (" + currentLevelName + ")";
					if(ImGui::Selectable(temp.c_str())) {
						SaveLevel(currentLevelName);
					}
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
					m_showVersionWidget = true;
					m_showCreditsWidget = false;
				}
				if (ImGui::Selectable("Credit")) {
					m_showCreditsWidget = true;
					m_showVersionWidget = false;
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

		// About Widgets
		if (m_showCreditsWidget) {
			static int width = 300;
			static int height = 200;
			// Center the window 
			ImGui::SetNextWindowPos(ImVec2((EditorConfig::Instance()->getWindowSize().x / 2) - (width / 2), (EditorConfig::Instance()->getWindowSize().y / 2) - (height)));
			ImGui::Begin("Credits", &m_showCreditsWidget, ImVec2(300, 200), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);
			ImGui::Text("Programmer: David Styrbjörn");
			ImGui::Text("License: GNU General Public License v3.0");

			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
			
			ImGui::Text("David Styrbjörn Contact Info");
			ImGui::Text("Email: davidstyrbjorn@gmail.com");
			ImGui::Text("GitHub: https://github.com/Mieeh");
			ImGui::Text("LinkedIn: 'David Styrbjorn'");

			ImGui::End();
		}
		else if (m_showVersionWidget) {
			static int width = 300;
			static int height = 75;
			// Center the window 
			ImGui::SetNextWindowPos(ImVec2((EditorConfig::Instance()->getWindowSize().x / 2) - (width / 2), (EditorConfig::Instance()->getWindowSize().y / 2) - (height*2)));
			ImGui::Begin("Version", &m_showVersionWidget, ImVec2(width, height), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

			std::string temp = "Version: " + EditorConfig::Instance()->getVersionString();
			ImGui::Text(temp.c_str());

			ImGui::End();
		}

		// Saving/Loading Widgets
		if (m_showSaveLevelWidget) {
			static int width = 300;
			static int height = 200;
			// Center the window 
			ImGui::SetNextWindowPos(ImVec2((EditorConfig::Instance()->getWindowSize().x / 2)-(width/2), (EditorConfig::Instance()->getWindowSize().y/2)-(height)));
			ImGui::Begin("Save Level", &m_showSaveLevelWidget, ImVec2(width, height), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);

			static char buffer[128] = "";
			ImGui::InputText("Level Name", buffer, 128);
			if (ImGui::Button("Save")) {
				SaveLevel(buffer);

				// Done with saving
				m_showSaveLevelWidget = false;
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
				LoadLevel(buffer);

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
						LoadLevel(temp); 

						// Done with loading
						m_showLoadLevelWidget = false;
					}
				}
			}

			ImGui::End();
		}
	}

	void MenuBarWidget::SaveLevel(std::string a_name)
	{
		static LevelParser levelParser;

		std::string location = "resources\\levels\\" + std::string(a_name) + ".txt";
		// Check if there's already a saved level with this name!
		// @ TODO: Handle if there's already a existing level with said name
		if (DoesFileExist(location)) {
			levelParser.ParseCurrentLevelToFile(location.c_str());
		}
		else {
			levelParser.ParseCurrentLevelToFile(location.c_str());
		}

		// We've loaded a new level (name)
		EditorConfig::Instance()->setCurrentLevelName(a_name);

		std::string message = "Saved Level " + std::string(a_name) + " at resources/levels/" + std::string(a_name) + ".txt";
		EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, message));
	}

	void MenuBarWidget::LoadLevel(std::string a_name)
	{
		static LevelParser levelParser;

		// TODO @: More than entities are to be loaded from the file
		std::string location = "resources\\levels\\" + std::string(a_name) + ".txt";
		ParsedLevel level = levelParser.GetParsedLevelFromFile(location.c_str());
		std::vector<ecs::Entity*> temp = level.entities;
		WorldSystem::Instance()->LoadedNewLevel(temp);

		// Set camera pos 
		RendererSystem::Instance()->GetSimpleRenderer().GetCamera()->SetPosition(level.camPos);

		// We've loaded a new level (name)
		EditorConfig::Instance()->setCurrentLevelName(a_name);


	}
}
}