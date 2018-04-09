#include"../include/widgets/Widgets.h"

#include"../include/DearImGui/imgui.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/systems/RendererSystem.h"
#include"../include/LevelParser.h"
#include"../include/systems/EditorConfig.h"
#include"../include/systems/WindowSystem.h"
#include"../include/systems/InputSystem.h"
#include"../include/systems/LevelSystem.h"

#include"../include/components/FourwayMoveComponentEditor.h"

#include<math\Vector2.h>
#include<graphics\Camera.h>
#include<graphics\Simple_Renderer.h>
#include<InputDefinitions.h>
#include<StringHelp.h>
#include<FileHelp.h>

#include<iostream>
#include<fstream>
#include<dirent.h>
#include<sys\types.h>
#include<windows.h>

void startup(LPCTSTR lpApplicationName)
{
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess(lpApplicationName,   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

namespace nano { namespace editor {

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
		input = InputSystem::getInstance();
	}

	void MenuBarWidget::Update()
	{
		for (InputEvent event : input->GetPolledEvents()) {
			if (event.type == InputEventType::KEY_PRESSED) {
				if (event.key == NANO_KEY_F) {
					EditorWidgetSystem::getInstance()->SetRenderWidgets(!EditorWidgetSystem::getInstance()->GetRenderWidgets());
				}
			}
		}
	}

	void MenuBarWidget::Render()
	{
		static bool m_showLoadLevelWidget = false;
		static bool m_showSaveLevelWidget = false;
		static bool m_showCreditsWidget = false;
		static bool m_showVersionWidget = false;
		static bool m_showEntityLoadWidget = false;
		static bool oversaveConfirm = false;
		static char saveBuffer[128] = "";
		static char loadBuffer[128] = "";
		static LevelParser levelParser;
		static LevelSystem *levelSystem = LevelSystem::getInstance();
		std::string currentLevelName = EditorConfig::Instance()->getCurrentlyLevelName();

		if (ImGui::BeginMainMenuBar()) 
		{

			if (ImGui::BeginMenu("File")) 
			{
				if (ImGui::Selectable("New Level")) {
					levelSystem->newLevel();
				}
				if (ImGui::Selectable("Save Level As")) {
					m_showSaveLevelWidget = true;
					m_showLoadLevelWidget = false;
					oversaveConfirm = false;
					strcpy_s(saveBuffer, "");
				}
				if (currentLevelName != "none") {
					std::string temp = "Save Level (" + currentLevelName + ")";
					if(ImGui::Selectable(temp.c_str())) {
						levelSystem->saveLevel(currentLevelName);
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
					// Run engine.exe 
					startup("engine.exe");
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
					WorldSystem::getInstance()->CreateNewEntity("unnamed");
					// Send this event to the event handler!
					EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_created", "unnamed"));
				}
				if (ImGui::Selectable("Load Entity")) {
					m_showEntityLoadWidget = true;
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

			bool enter = ImGui::InputText("Level Name", saveBuffer, 128, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue);
			if (ImGui::Button("Save") || enter) {
				if (doesFileExist("resources\\levels\\" + std::string(saveBuffer) + ".txt") && !oversaveConfirm) {
					oversaveConfirm = true;
				}
				else {
					levelSystem->saveLevel(saveBuffer);
					// Done with saving
					m_showSaveLevelWidget = false;
				}
			}

			if (oversaveConfirm) {
				ImGui::Text("Level with name already exists");
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "(level will be overwritten!!!)");
			}

			ImGui::End();
		}
		else if (m_showLoadLevelWidget) {
			static int width = 300;
			static int height = 200;
			// Center the window 
			ImGui::SetNextWindowPos(ImVec2((EditorConfig::Instance()->getWindowSize().x / 2) - (width / 2), (EditorConfig::Instance()->getWindowSize().y / 2) - (height)));
			ImGui::Begin("Load Level", &m_showLoadLevelWidget, ImVec2(width, height), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);

			bool enter = ImGui::InputText("Level Name", loadBuffer, 128, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue);
			if (ImGui::Button("Load") || enter) {
				levelSystem->loadLevel(loadBuffer);

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
						levelSystem->loadLevel(temp); 
						// Done with loading
						m_showLoadLevelWidget = false;
					}
				}
			}

			ImGui::End();
		}
		else if (m_showEntityLoadWidget) {
			static int width = 300;
			static int height = 200;
			// Center the window
			ImGui::SetNextWindowPos(ImVec2((EditorConfig::Instance()->getWindowSize().x / 2) - (width / 2), (EditorConfig::Instance()->getWindowSize().y / 2) - (height)));
			ImGui::Begin("Load Entity", &m_showEntityLoadWidget, ImVec2(width, height), 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);

			std::vector<std::string> entityFileList;
			ReadDirectory("resources\\assets\\", entityFileList);
			for (std::string i : entityFileList) {
				if (i != "." && i != ".." && getFileSuffix(i) == "txt") {
					std::string temp = i.substr(0, i.length() - 4);
					if (ImGui::Selectable(temp.c_str())) {
						std::string loc = "resources\\assets\\" + i;
						ecs::Entity* loadedEntity = levelParser.getParsedEntityFromFile(loc.c_str());
						WorldSystem::getInstance()->AddNewEntity(loadedEntity);
						m_showEntityLoadWidget = false;
					}
				}
			}

			ImGui::End();
		}
	}
}
}