#include"../include/widgets/Widgets.h"

#include<CoreConfig.h>
#include<math\Vector2.h>

#include"../include/DearImGui/imgui.h"

namespace nano { namespace editor {

	UtilitySelectWidget::UtilitySelectWidget()
	{
		m_config = CoreConfig::Instance();
	}

	void UtilitySelectWidget::Start()
	{

	}

	void UtilitySelectWidget::Update()
	{

	}

	void UtilitySelectWidget::Render()
	{
		math::Vector2 _windowSize = m_config->GetWindowSize();

		// Calculate size
		ImVec2 size;
		size.y = (_windowSize.y * UNNAMED_WIDGET_HEIGHT_RATIO); // Make sure height is the ratio based on the current window height
		size.x = UNNAMED_WIDGET_WIDTH;

		// Calculate position
		ImVec2 pos;
		pos.x = 0;
		pos.y = MAIN_MENU_BAR_HEIGHT + (_windowSize.y * ENTITY_SELECT_HEIGHT_RATIO);

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("Utility Select", false, size, 1.0f,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
		);

		ImGui::Text("test");

		ImGui::End();
	}

} }