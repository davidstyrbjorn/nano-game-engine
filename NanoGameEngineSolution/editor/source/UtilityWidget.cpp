#include"../include/widgets/UtilityWidget.h"

#include"../include/DearImGui/imgui.h"

#include<CoreConfig.h>

namespace nano { namespace editor {

	UtilityWidget::UtilityWidget()
	{
		m_config = CoreConfig::Instance();
	}

	void UtilityWidget::Start()
	{

	}

	void UtilityWidget::Update()
	{

	}

	void UtilityWidget::Render()
	{
		ImGui::Begin("Utility", false, ImVec2(300,400), 1.0f, 
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize 
		);

		ImGui::End();
	}

} }