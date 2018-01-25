#include"../include/widgets/EntityInspectorWidget.h"

#include<CoreConfig.h>
#include<math\Vector2.h>
#include<ecs\Entity.h>

#include"../include/systems/WorldSystem.h"

#include"../include/DearImGui/imgui.h"

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
				ImGui::Text(m_entityToInspect->GetID().c_str());
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