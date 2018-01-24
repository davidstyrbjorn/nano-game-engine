#include"../include/widgets/MenuBarWidget.h"

#include<CoreConfig.h>

#include"../include/DearImGui/imgui.h"

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

			ImGui::EndMainMenuBar();
		}
	}
}
}