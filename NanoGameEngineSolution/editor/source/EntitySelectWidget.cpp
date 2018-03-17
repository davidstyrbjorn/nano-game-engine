#include"../include/widgets/Widgets.h"

#include<ecs\components\TransformComponent.h>
#include<graphics\Camera.h>

#include"../include/DearImGui/imgui.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/systems/InputSystem.h"
#include"../include/systems/RendererSystem.h"
#include"../include/systems/EditorConfig.h"

#include<graphics\Simple_Renderer.h>
#include<InputDefinitions.h>

namespace nano { namespace editor {

	EntitySelectWidget::EntitySelectWidget()
	{
		m_entityManager = WorldSystem::getInstance();
		m_inputSystem = InputSystem::getInstance();
		m_renderSystem = RendererSystem::getInstance();
	}

	void EntitySelectWidget::Start() 
	{
		
	}

	bool EntitySelectWidget::IsMouseInViewFrustrum(const math::Vector2& a_position) {
		// View frustrum dimensions
		static EditorConfig* c = EditorConfig::Instance();

		float x = ENTITY_SELECT_WIDTH + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().x;
		float y = MAIN_MENU_BAR_HEIGHT + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().y;
		float width = (c->getWindowSize().x - ENTITY_INSPECTOR_WIDTH) + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().x;
		float height = (c->getWindowSize().y - (c->getWindowSize().y * UTILITY_HEIGHT_RATIO)) + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().y;
		
		if (a_position.x > x && a_position.x < width && a_position.y > y && a_position.y < height)
			return true;

		return false;
	}		  

	void EntitySelectWidget::Update()
	{
		for (InputEvent _event : m_inputSystem->GetPolledEvents()) {
			if (_event.type == InputEventType::MOUSE_PRESSED) {
				math::Vector2 mousePos = m_inputSystem->GetMousePosition() + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition();
				// Check if mouse is within the view frustrum
				if (IsMouseInViewFrustrum(mousePos))
				{
					// RMB - Drag camera view
					if (_event.key == NANO_MOUSE_BUTTON_RIGHT) 
					{
						// Mouse drag
						m_isDraggingView = true;
						m_dragOrigin = m_inputSystem->GetMousePosition();
					}
					// LMB - Click to inspect entity
					else if(_event.key == NANO_MOUSE_BUTTON_LEFT) 
					{
							bool hitDetect = false;
							for (ecs::Entity* entity : m_entityManager->GetEntityList()) {
								if (mousePos.x > entity->m_transform->position.x && mousePos.x < entity->m_transform->position.x + entity->m_transform->size.x && mousePos.y > entity->m_transform->position.y && mousePos.y < entity->m_transform->position.y + entity->m_transform->size.y) {
									EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_clicked", entity->GetID()));
									hitDetect = true;
								}
							}
							if (!hitDetect) 
							{
								EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_clicked", "-1"));
							}
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
		math::Vector2 _windowSize = EditorConfig::Instance()->getWindowSize();

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
				ImGui::PushItemWidth(30);
				bool temp = entity->GetState() == ecs::ECSStates::ACTIVE ? true : false;
				ImGui::Checkbox(std::string("##" + entity->GetID()).c_str(), &temp);
				entity->SetState(temp);
				ImGui::SameLine(33);

				std::string selectableID = entity->GetID() + "##" + std::to_string(i);
				// Check if we clicked on entity, if we did send that event to the event handler
				if (ImGui::Selectable(selectableID.c_str())) {
					// Clicked on entity
					EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_clicked", entity->GetID())); // Message the event handler this happend!
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
				EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_destroyed", m_leftClickedEntity->GetID()));
				m_leftClickedEntity->SetState(ecs::ECSStates::DESTROYED);
			}
			if (ImGui::Selectable("Rename")) {
				// Making sure we "clicekd" on entity before we rename it
				// This to know which entity to rename from the entity insepctor widget functions
				EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_clicked", m_leftClickedEntity->GetID())); // Message the event handler this happend!
				EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_rename", m_leftClickedEntity->GetID()));
			}
			
			ImGui::EndPopup();
		}

		ImGui::End();
	}

} }