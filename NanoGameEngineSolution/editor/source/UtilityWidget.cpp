#include"../include/widgets/Widgets.h"

#include<math\Vector2.h>
#include<graphics\Camera.h>
#include<graphics\Simple_Renderer.h>

#include"../include/DearImGui/imgui.h"
#include"../include/systems/RendererSystem.h"
#include"../include/systems/EditorConfig.h"

namespace nano { namespace editor {

	enum UtilityType {
		CAMERA,
		WINDOW
	};
#define CAM_MAX_X 1000

	UtilityWidget::UtilityWidget()
	{
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

		math::Vector2 _windowSize = EditorConfig::Instance()->getWindowSize();
	
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

			// Camera position
			ImGui::PushItemWidth(150);
			math::Vector2 pos = m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition();
			ImGui::DragFloat2("Position", (float*)&pos, 1.0f, 0.0f, 0.0f, "%.1f");
			m_renderSystem->GetSimpleRenderer().GetCamera()->SetPosition(pos);

			// Camera size
			ImGui::PushItemWidth(150);
			math::Vector2 size = m_renderSystem->GetSimpleRenderer().GetCamera()->GetSize();
			ImGui::DragFloat2("Size", (float*)&size, 1.0f, 0.0f, 0.0f, "%.0f");
			m_renderSystem->GetSimpleRenderer().GetCamera()->SetSize(size);
			// Button for reseting camera position to zero, zero
			if (ImGui::Button("Reset Position")) {
				m_renderSystem->GetSimpleRenderer().GetCamera()->SetPosition(math::Vector2(0, 0));
			}
			ImGui::SameLine(120);
			// Button for matching the camera size to the current window size
			if (ImGui::Button("Math Window Size")) {
				math::Vector2 _windowSize = EditorConfig::Instance()->getWindowSize();
				m_renderSystem->GetSimpleRenderer().GetCamera()->SetSize(_windowSize);
			}
		}
		if (utilityType == UtilityType::WINDOW) {
			// Window utility stuff
		}

		ImGui::End();
	}

} }