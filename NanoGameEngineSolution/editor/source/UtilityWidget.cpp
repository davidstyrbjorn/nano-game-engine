#include"../include/widgets/UtilityWidget.h"
#include"../include/systems/RendererSystem.h"

#include"../include/DearImGui/imgui.h"

#include<CoreConfig.h>
#include<math\Vector2.h>

namespace nano { namespace editor {

	enum UtilityType {
		CAMERA
	};

	UtilityWidget::UtilityWidget()
	{
		m_config = CoreConfig::Instance();
		m_renderSystem = RendererSystem::Instance();
	}

	void UtilityWidget::Start()
	{

	}

	void UtilityWidget::Update()
	{
		
	}

	void UtilityWidget::Render()
	{
		static UtilityType utilityType = UtilityType::CAMERA;

		math::Vector2 _windowSize = m_config->GetWindowSize();
	
		// Calculate size
		ImVec2 size;
		size.x = (_windowSize.x * 0.5f);
		size.y = (_windowSize.y * UTILITY_HEIGHT_RATIO) - MAIN_MENU_BAR_HEIGHT;

		// Calculate position
		ImVec2 pos;
		pos.x = 0;
		pos.y = MAIN_MENU_BAR_HEIGHT + (_windowSize.y * ENTITY_SELECT_HEIGHT_RATIO) + (_windowSize.y * UNNAMED_WIDGET_HEIGHT_RATIO);

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("Utility", false, size, 1.0f, 
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
		);

		// Upper left corner drop down to select utility type to modify
		std::string utilityName;
		if (utilityType == UtilityType::CAMERA) {
			utilityName = "Camera";
		}
		if (ImGui::Button(utilityName.c_str())) {
			// Do the drop down logic
		}

		if (utilityType == UtilityType::CAMERA) {
			// Render and do the camera utility stuff
			math::Vector2 pos;
			ImGui::DragFloat(
		}

		ImGui::End();
	}

} }