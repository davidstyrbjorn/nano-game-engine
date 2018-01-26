#include"../include/widgets/EntityInspectorWidget.h"

#include<CoreConfig.h>
#include<math\Vector2.h>
#include<ecs\Entity.h>
#include<math\Vector2.h>

#include"../include/systems/WorldSystem.h"

#include"../include/DearImGui/imgui.h"

#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TriangleComponent.h>

namespace nano { namespace editor {

	EntityInspectorWidget::EntityInspectorWidget()
	{
		m_config = CoreConfig::Instance();
	}

	void EntityInspectorWidget::Start()
	{

	}

	void EntityInspectorWidget::Update()
	{

	}

	void EntityInspectorWidget::Render()
	{
		math::Vector2 _windowSize = m_config->GetWindowSize();

		// Calculate size
		ImVec2 size;
		size.y = (_windowSize.y * ENTITY_INSPECTOR_HEIGHT_RATIO); // Make sure height is the ratio based on the current window height
		size.x = ENTITY_INSPECTOR_WIDTH;

		// Calculate position
		ImVec2 pos;
		pos.x = _windowSize.x - size.x;
		pos.y = MAIN_MENU_BAR_HEIGHT;

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("Entity Inspector", false, size, 1.0f,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
		);

		if (m_entityToInspect != nullptr) 
		{
			// ID section
			static std::string nameString = "ID: " + m_entityToInspect->GetID();
			ImGui::Text(nameString.c_str());
			
			ImGui::Separator(); ImGui::Spacing();
			
			ImGui::Text("Transform Component");
			// Position
			ImGui::DragFloat2("Position", (float*)&m_entityToInspect->m_transform->position, 0.5f, 0, 0,"%.2f");
			// Size
			ImGui::DragFloat2("Size", (float*)&m_entityToInspect->m_transform->size, 0.5f, 0, 0, "%.2f");
			// Angle
			ImGui::SliderAngle("Angle", (float*)&m_entityToInspect->m_transform->angle);

			ImGui::Separator(); ImGui::Spacing();

			// Start listing components
			graphics::Renderable* renderableComponent = m_entityToInspect->GetRenderableComponent();
			if (renderableComponent != nullptr) {
				// Shape type
				ImGui::Text("Renderable Component");
				if (renderableComponent->GetVertexCount() == 3) {
					ImGui::Text("Type: Triangle");
				}
				if (renderableComponent->GetVertexCount() == 4) {
					ImGui::Text("Type: Rectangle");
				}

				// Color
				math::Vector4 renderableColor = renderableComponent->GetColor();
				ImGui::ColorEdit4("Color", (float*)&renderableColor);
				renderableComponent->SetColor(renderableColor);
			}
		}

		ImGui::End();
	}

	void EntityInspectorWidget::OnEntityClick(std::string a_id)
	{
		m_entityToInspect = WorldSystem::Instance()->GetEntityByID(a_id);
	}

	void EntityInspectorWidget::OnEntityDestroyed(std::string a_id)
	{
		// Check if the destroyed entity is the entity we inspect
		if (WorldSystem::Instance()->Instance()->GetEntityByID(a_id) == m_entityToInspect) {
			m_entityToInspect = nullptr;
		}
	}

} }