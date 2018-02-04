#include"../include/widgets/Widgets.h"

#include"../include/DearImGui/imgui.h"

#include<CoreConfig.h>
#include<math\Vector2.h>

namespace nano {
	namespace editor {

		ConsoleWidget::ConsoleWidget()
		{
			m_config = CoreConfig::Instance();
		}

		void ConsoleWidget::Start()
		{

		}

		void ConsoleWidget::Update()
		{

		}

		void ConsoleWidget::Render()
		{
			math::Vector2 _windowSize = m_config->GetWindowSize();

			// Calculate size
			ImVec2 size;
			size.x = (_windowSize.x * CONSOLE_WIDTH_RATIO);
			size.y = (_windowSize.y * CONSOLE_HEIGHT_RATIO) - MAIN_MENU_BAR_HEIGHT;

			// Calculate position
			ImVec2 pos;
			pos.x = (_windowSize.x * UTILITY_WIDTH_RATIO);
			pos.y = MAIN_MENU_BAR_HEIGHT + (_windowSize.y * ENTITY_SELECT_HEIGHT_RATIO) + (_windowSize.y * UNNAMED_WIDGET_HEIGHT_RATIO);

			ImGui::SetNextWindowPos(pos);
			ImGui::SetNextWindowSize(size);
			ImGui::Begin("Console", false, size, 1.0f,
				ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
			);

			ImGui::Text("test");

			ImGui::End();
		}

	}
}