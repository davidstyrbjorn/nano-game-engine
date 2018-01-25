#include"../include/widgets/EntitySelectWidget.h"

#include<math\Vector2.h>
#include<CoreConfig.h>

#include"../include/DearImGui/imgui.h"

#include"../include/systems/EntityManagerSystem.h"
#include"../include/systems/EditorWidgetSystem.h"

namespace nano { namespace editor { 

	EntitySelectWidget::EntitySelectWidget()
	{
		m_config = CoreConfig::Instance();
		m_entityManager = EntityManagerSystem::Instance();
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

		// Title
		ImGui::Text("Level Entities: ");

		ImGui::Separator();

		// Simple column-major list of entities
		std::vector<ecs::Entity*> _list = m_entityManager->GetEntityList();
		ImGui::Columns(1, "entity_columns", true);
		int i = 0;
		for(ecs::Entity* entity : _list)
		{
			i++; // Incrementer for selectable ID

			if (entity->GetState() != ecs::ECSStates::DESTROYED) 
			{
				std::string selectableID = entity->GetID() + "##" + std::to_string(i);
				
				// Check if we clicked on entity, if we did send that event to the event handler
				if (ImGui::Selectable(selectableID.c_str())) {
					// Clicked on entity
					BaseEvent _event;
					_event._type = EventTypes::CLICKED_ON_ENTITY;
					_event._strID = entity->GetID(); 	
					EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(_event); // Message the event handler this happend!
				}

				// Check if we left click
				if (ImGui::IsItemHovered()) {
					if (ImGui::GetIO().MouseClicked[1]) {
						ImGui::OpenPopup("right_click_entity");
					}
				}

				// Left click menu
				if (ImGui::BeginPopup("right_click_entity")) {
					ImGui::Separator(); ImGui::Spacing();

					if (ImGui::Selectable("Destroy")) {
						entity->SetState(ecs::ECSStates::DESTROYED);
					}

					ImGui::EndPopup();
				}

				// Done with this entity
				ImGui::NextColumn();
			}
		}

		ImGui::End();
	}

} }