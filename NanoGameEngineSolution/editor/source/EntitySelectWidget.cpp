#include"../include/widgets/EntitySelectWidget.h"

#include<math\Vector2.h>
#include<CoreConfig.h>

#include"../include/DearImGui/imgui.h"

namespace nano { namespace editor { 

	EntitySelectWidget::EntitySelectWidget()
	{
		m_config = CoreConfig::Instance();
	}

	void EntitySelectWidget::Start() 
	{

	}

	void EntitySelectWidget::Update()
	{

	}

	void EntitySelectWidget::Render()
	{
		math::Vector2 _windowSize = m_config->GetWindowSize();

		ImVec2 size;
		size.y = (_windowSize.y * ENTITY_SELECT_HEIGHT_RATIO); // Make sure height is the ratio based on the current window height
		size.x = ENTITY_SELECT_WIDTH;

		ImGui::SetNextWindowPos(ImVec2(0, MAIN_MENU_BAR_HEIGHT));
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("Entity Select", false, size, 1.0f,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse 
		);

		ImGui::Text("test");

		ImGui::End();
	}

} }