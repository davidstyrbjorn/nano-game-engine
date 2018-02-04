#include"../include/widgets/Widgets.h"

#include"../include/DearImGui/imgui.h"

#include<CoreConfig.h>
#include<math\Vector2.h>

#include"../include/systems/RendererSystem.h"
#include<graphics\Simple_Renderer.h>

namespace nano { namespace editor {

	enum UtilityType {
		CAMERA,
		WINDOW
	};
#define CAM_MAX_X 1000

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
		if (utilityType == UtilityType::WINDOW) {
			utilityName = "Window";
		}
		if (ImGui::Button(utilityName.c_str())) {
			// Do the drop down logic
			ImGui::OpenPopup("utility_select_popup");
		}
		if (ImGui::BeginPopup("utility_select_popup")) {
			if (ImGui::Selectable("Camera")) {
				utilityType = UtilityType::CAMERA;
			}
			if (ImGui::Selectable("Window")) {
				utilityType = UtilityType::WINDOW;
			}
			ImGui::EndPopup();
		}
		ImGui::Separator();

		if (utilityType == UtilityType::CAMERA) {
			// Render and do the camera utility stuff
			math::Vector2 pos = m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition();
			ImGui::DragFloat2("Position", (float*)&pos);
			m_renderSystem->GetSimpleRenderer().GetCamera()->SetPosition(pos);
		}
		if (utilityType == UtilityType::WINDOW) {
			// Window utility stuff
		}

		ImGui::End();
	}

} }