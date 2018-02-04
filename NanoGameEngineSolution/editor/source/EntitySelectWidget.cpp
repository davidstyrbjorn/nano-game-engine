#include"../include/widgets/Widgets.h"

#include<CoreConfig.h>
#include<ecs\components\TransformComponent.h>

#include"../include/DearImGui/imgui.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/systems/InputSystem.h"
#include"../include/systems/RendererSystem.h"

#include<graphics\Simple_Renderer.h>

namespace nano { namespace editor {

	EntitySelectWidget::EntitySelectWidget()
	{
		m_config = CoreConfig::Instance();
		m_entityManager = WorldSystem::Instance();
		m_inputSystem = InputSystem::Instance();
		m_renderSystem = RendererSystem::Instance();
	}

	void EntitySelectWidget::Start() 
	{
		
	}

	bool EntitySelectWidget::IsMouseInViewFrustrum(const math::Vector2& a_position) {
		// View frustrum dimensions
		// @ Make this work with camera position
		float x = ENTITY_SELECT_WIDTH + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().x;
		float y = MAIN_MENU_BAR_HEIGHT + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().y;
		float width = (m_config->GetWindowSize().x - ENTITY_INSPECTOR_WIDTH) + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().x;
		float height = (m_config->GetWindowSize().y - (m_config->GetWindowSize().y * UTILITY_HEIGHT_RATIO)) + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().y;
		
		if (a_position.x > x && a_position.x < width && a_position.y > y && a_position.y < height)
			return true;

		return false;
	}		  

	void EntitySelectWidget::Update()
	{
		for (InputEvent _event : m_inputSystem->GetPolledEvents()) {
			if (_event.type == InputEventType::MOUSE_PRESSED) {
				math::Vector2 mousePos = m_inputSystem->GetMousePosition() + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition();
				// TODO: Check if mouse is within the view frustrum
				if (IsMouseInViewFrustrum(mousePos)) 
				{
					bool hitDetect = false;
					for (ecs::Entity* entity : m_entityManager->GetEntityList()) {
						if (mousePos.x > entity->m_transform->position.x && mousePos.x < entity->m_transform->position.x + entity->m_transform->size.x && mousePos.y > entity->m_transform->position.y && mousePos.y < entity->m_transform->position.y + entity->m_transform->size.y) {
							EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::CLICKED_ON_ENTITY, entity->GetID()));
							hitDetect = true;
						}
					}
					if (!hitDetect) {
						EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::CLICKED_ON_ENTITY, "-1"));
						// Mouse drag
						m_isDraggingView = true;
						m_dragOrigin = m_inputSystem->GetMousePosition();
					}

				}
			
			}
			if (_event.type == InputEventType::MOUSE_RELEASE) {
				if (m_isDraggingView)
					m_isDraggingView = false;
			}
		}

		// Drag logic
		if (m_isDraggingView) {
			// Mouse drag delta 
			math::Vector2 mousePos = m_inputSystem->GetMousePosition();
			math::Vector2 delta = mousePos - m_lastFrameMousePos;
			m_renderSystem->GetSimpleRenderer().GetCamera()->Translate(delta*-1);
		}

		m_lastFrameMousePos = m_inputSystem->GetMousePosition();
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
					EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::CLICKED_ON_ENTITY, entity->GetID())); // Message the event handler this happend!
				}

				// Check if we left click
				if (ImGui::IsItemHovered()) {
					if (ImGui::GetIO().MouseClicked[1]) {
						m_leftClickedEntity = entity;
						ImGui::OpenPopup("right_click_entity");
					}
				}

				// Done with this entity
				ImGui::NextColumn();
			}
		}

		if (ImGui::BeginPopup("right_click_entity")) {
			//ImGui::Spacing();

			if (ImGui::Selectable("Destroy")) 
			{
				EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::REMOVED_ENTITY, m_leftClickedEntity->GetID()));
				m_leftClickedEntity->SetState(ecs::ECSStates::DESTROYED);
			}
			if (ImGui::Selectable("Rename")) {
				std::cout << "Rename not yet implemented" << std::endl;
			}
			
			ImGui::EndPopup();
		}

		ImGui::End();
	}

} }