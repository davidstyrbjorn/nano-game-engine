#include"../include/widgets/Widgets.h"

#include<CoreConfig.h>
#include<math\Vector2.h>
#include<ecs\Entity.h>
#include<math\Vector2.h>
#include<opengl\Texture.h>
#include<sound\SoundSource.h>
#include<sound\SoundBuffer.h>
#include<graphics\Simple_Renderer.h>

#include"../include/systems/WorldSystem.h"
#include"../include/systems/InputSystem.h"
#include"../include/systems/RendererSystem.h"

#include"../include/DearImGui/imgui.h"

#include<ecs\components\TransformComponent.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TriangleComponent.h>
#include<ecs\components\SpriteComponent.h>

#include<stb\stb_image.h>

#include<InputDefinitions.h>

namespace nano { namespace editor {

	EntityInspectorWidget::EntityInspectorWidget()
	{
		m_config = CoreConfig::Instance();
		m_inputSystem = InputSystem::Instance();
	}

	void EntityInspectorWidget::Start()
	{
		m_renderSystem = RendererSystem::Instance();
	}

	void EntityInspectorWidget::Update()
	{
		highlighEntity.Update();
		if(highlighEntity.ShouldHighlight())
			RendererSystem::Instance()->GetSimpleRenderer().Submit(highlighEntity.GetRenderable());

		math::Vector2 mousePos = m_inputSystem->GetMousePosition() + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition();
		// Dragging input
		if (m_entityToInspect != nullptr) {
			for (InputEvent _event : m_inputSystem->GetPolledEvents()) {
				if (_event.type == InputEventType::KEY_PRESSED) {
					// "de"select entity
					if (_event.key == NANO_KEY_ESCAPE) {
						if (m_entityToInspect != nullptr)
							m_entityToInspect = nullptr;
					}
				}
				if (_event.type == InputEventType::MOUSE_PRESSED) {
					if (_event.key == NANO_MOUSE_BUTTON_LEFT) {
						if (mousePos.x > m_entityToInspect->m_transform->position.x && mousePos.x < m_entityToInspect->m_transform->position.x + m_entityToInspect->m_transform->size.x) {
							if (mousePos.y > m_entityToInspect->m_transform->position.y && mousePos.y < m_entityToInspect->m_transform->position.y + m_entityToInspect->m_transform->size.y) {
								m_isDraggingEntity = true;
								m_dragDeltaPosition = mousePos - m_entityToInspect->m_transform->position;
							}
						}
					}
				}
				else if (_event.type == InputEventType::MOUSE_RELEASE) {
					if (m_isDraggingEntity)
						m_isDraggingEntity = false;
				}
			}
		}
		else {
			m_isDraggingEntity = false;
		}

		// Dragging logic
		if (m_isDraggingEntity && !m_addComponentWindow) {
			m_entityToInspect->m_transform->position = mousePos - m_dragDeltaPosition;
		}
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
			std::string nameString = "ID: " + m_entityToInspect->GetID();
			ImGui::Text(nameString.c_str());
			if (ImGui::IsItemHovered()) {
				if (ImGui::GetIO().MouseClicked[1]) {
					ImGui::OpenPopup("rename_entity");
				}
			}
			if (ImGui::BeginPopup("rename_entity")) {
				if (ImGui::Selectable("Rename")) {
					m_renameEntityWindow = true;
				}
				ImGui::EndPopup();
			}

			ImGui::Separator(); ImGui::Spacing();
			
			ImGui::Text("Transform Component");
			// Position
			ImGui::DragFloat2("Position", (float*)&m_entityToInspect->m_transform->position, 0.5f, 0, 0,"%.2f");
			// Size
			ImGui::DragFloat2("Size", (float*)&m_entityToInspect->m_transform->size, 0.5f, 0, 0, "%.2f");
			// Angle
			ImGui::SliderAngle("Angle", (float*)&m_entityToInspect->m_transform->angle);

			ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

			// Start listing components
			graphics::Renderable* renderableComponent = m_entityToInspect->GetRenderableComponent();
			bool hasRenderableComponent = renderableComponent == nullptr ? false : true;
			if (hasRenderableComponent) {
				// Shape type
				ImGui::Text("Renderable Component");
				// Right click component name
				if (ImGui::IsItemHovered()) {
					if (ImGui::GetIO().MouseClicked[1]) {
						ImGui::OpenPopup("right_click_component_renderable");
					}
				}
				if (ImGui::BeginPopup("right_click_component_renderable")) {
					if (ImGui::Selectable("Destroy")) {
						if (renderableComponent->GetTexture() != nullptr)
							m_entityToInspect->GetComponent<ecs::SpriteComponent>()->SetState(ecs::ECSStates::DESTROYED);
						else if (renderableComponent->GetVertexCount() == 3)
							m_entityToInspect->GetComponent<ecs::TriangleComponent>()->SetState(ecs::ECSStates::DESTROYED);
						else
							m_entityToInspect->GetComponent<ecs::RectangleComponent>()->SetState(ecs::ECSStates::DESTROYED);
					}
					ImGui::EndPopup();
				}

				if (renderableComponent->GetTexture() != nullptr) {
					ImGui::Text("Type: Sprite");
				}
				else if (renderableComponent->GetVertexCount() == 3) {
					ImGui::Text("Type: Triangle");
				}
				else if (renderableComponent->GetVertexCount() == 4) {
					ImGui::Text("Type: Rectangle");
				}

				// Color
				math::Vector4 renderableColor = renderableComponent->GetColor();
				ImGui::ColorEdit4("Color", (float*)&renderableColor);
				renderableComponent->SetColor(renderableColor);

				// Image if there is any
				if (renderableComponent->GetTexture() != nullptr) 
				{
					// Display the sprite image
					ImGui::Image((ImTextureID*)renderableComponent->GetTexture()->GetTextureID(), ImVec2(150,150));

					// Input for changing texture
					static char texturePath[128] = "";
					ImGui::InputText("Texture Path", texturePath, 128);
					if (ImGui::Button("Load Texture")) {
						m_entityToInspect->GetComponent<ecs::SpriteComponent>()->LoadNewTexture(texturePath);
					}
				}	
				
				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
			}

			ecs::SoundComponent* soundComponent = m_entityToInspect->GetComponent<ecs::SoundComponent>();
			bool hasSoundComponent = soundComponent == nullptr ? false : true;
			if (hasSoundComponent) {

				openal::SoundSource *source = soundComponent->GetSource();

				ImGui::Text("Sound Component");
				// Right click component name
				if (ImGui::IsItemHovered()) {
					if (ImGui::GetIO().MouseClicked[1]) {
						ImGui::OpenPopup("right_click_component_sound");
					}
				}
				if (ImGui::BeginPopup("right_click_component_sound")) {
					if (ImGui::Selectable("Destroy")) {
						soundComponent->SetState(ecs::ECSStates::DESTROYED);
					}
					ImGui::EndPopup();
				}

				// Load sound
				static char soundPath[128] = "";
				ImGui::InputText("Sound Path", soundPath, 128);
				if (ImGui::Button("Load Sound")) {
					soundComponent->LoadNewSound(soundPath);
				}

				// Data modifiers
				// Volume/Gain
				static float gain = source->GetVolume();
				ImGui::SliderFloat("Gain", &gain, 0, 5, "%.1f");
				source->SetVolume(gain);

				// Pitch
				static float pitch = source->GetPitch();
				ImGui::SliderFloat("Pitch", &pitch, 0, 5, "%.1f");
				source->SetPitch(pitch);

				// Looping
				static bool looping;
				ImGui::Checkbox("Looping", &looping);
				source->SetLooping(looping);

				// State modifiers
				if (ImGui::Button("Play")) {
					source->Play();
				}
				ImGui::SameLine(100);
				if (ImGui::Button("Stop")) {
					source->Stop();
				}
				if (ImGui::Button("Pause")) {
					source->Pause();
				}
				ImGui::SameLine(100);
				if (ImGui::Button("Continue")) {
					source->Continue();
				}

				ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
			}

			// Add component
			static ImVec2 buttonSize = ImVec2(100, 30);
			ImGui::Indent((ImGui::GetWindowSize().x/2)-(buttonSize.x*0.7));
			if (ImGui::Button("Add Component", buttonSize)) {
				ImGui::OpenPopup("add_component");
			}
			if (ImGui::BeginPopup("add_component")) {
				if (ImGui::Selectable("Sprite Component")) {
					if (!hasRenderableComponent) {
						m_addComponentWindow = true;
						m_componentType = "Sprite Component";
					}
					else {
						// Already have renderable component
					}
				}
				if (ImGui::Selectable("Rectangle Component")) {
					if (!hasRenderableComponent) {
						m_addComponentColor = math::Vector4(1, 1, 1, 1);
						m_addComponentSize = math::Vector2(50, 50);
						m_addComponentWindow = true;
						m_componentType = "Rectangle Component";
					}
					else {
						// Already have renderable component
					}
				}
				if (ImGui::Selectable("Triangle Component")) {
					if (!hasRenderableComponent) {
						m_addComponentColor = math::Vector4(1, 1, 1, 1);
						m_addComponentSize = math::Vector2(50, 50);
						m_addComponentWindow = true;
						m_componentType = "Triangle Component";
					}
					else {
						// Already have renderable component
					}
				}
				if (ImGui::Selectable("Sound Component")) {
					if (!hasSoundComponent) {
						m_addComponentWindow = true;
						m_componentType = "Sound Component";
					}
					else {
						// Already have sound component
					}
				}
				ImGui::EndPopup();
			}
		}

		ImGui::End();

		if (m_entityToInspect != nullptr && m_addComponentWindow) 
		{
			static ImVec2 windowSize = ImVec2(325, 275);
			ImGui::Begin("Add Component", &m_addComponentWindow, windowSize, 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

			ImGui::Text(m_componentType.c_str());
			ImGui::Separator(); ImGui::Spacing();

			if (m_componentType == "Sound Component") {
				// Soundfile path
				static char buffer[128];
				ImGui::InputText("Sound File Path", buffer, 128);

				if (ImGui::Button("Confirm")) {
					m_entityToInspect->AddComponent(new ecs::SoundComponent(buffer));
					m_addComponentWindow = false;
					m_componentType = "none";
				}
			}
			else if (m_componentType == "Sprite Component") {
				// Texture path
				static char buffer[128];
				ImGui::InputText("Texture Path", buffer, 128);

				if (ImGui::Button("Confirm")) {
					m_entityToInspect->AddComponent(new ecs::SpriteComponent(buffer));
					m_addComponentWindow = false;
					m_componentType = "none";
				}
			}
			else if (m_componentType == "Rectangle Component") {
				// Color & Size
				ImGui::DragFloat2("Size", (float*)&m_addComponentSize);
				ImGui::ColorEdit4("Color", (float*)&m_addComponentColor);

				if (ImGui::Button("Confirm")) {
					m_entityToInspect->AddComponent(new ecs::RectangleComponent(m_addComponentColor));
					m_entityToInspect->m_transform->size = m_addComponentSize;
					m_addComponentWindow = false;
					m_componentType = "none";
				}
			}
			else if (m_componentType == "Triangle Component") {
				// Color & Size
				ImGui::DragFloat2("Size", (float*)&m_addComponentSize);
				ImGui::ColorEdit4("Color", (float*)&m_addComponentColor);

				if (ImGui::Button("Confirm")) {
					m_entityToInspect->AddComponent(new ecs::TriangleComponent(m_addComponentColor));
					m_entityToInspect->m_transform->size = m_addComponentSize;
					m_addComponentWindow = false;
					m_componentType = "none";
				}
			}

			ImGui::End();
		}

		if (m_entityToInspect != nullptr && m_renameEntityWindow) 
		{
			static ImVec2 windowSize = ImVec2(300, 60);
			ImGui::Begin("Rename", &m_renameEntityWindow, windowSize, 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

			static char buffer[128] = "";
			if (ImGui::InputText("New Name", buffer, 128, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue) || ImGui::Button("Confirm"))
			{
				m_entityToInspect->SetID(buffer);
				m_renameEntityWindow = false;
			}

			ImGui::End();
		}
	}

	void EntityInspectorWidget::OnEntityClick(std::string a_id)
	{
		if (!m_addComponentWindow && !m_renameEntityWindow) {
			// "-1" - clicked on empty space
			if (a_id == "-1") {
				// Deselect the entity i.e set it to a nullptr
				if (m_entityToInspect != nullptr) {
					m_entityToInspect->SetEditorState(ecs::ECSEditorStates::NOT_HIGHLIGHTED);
					highlighEntity.SetNewHighlightedEntity(nullptr);
					m_entityToInspect = nullptr;
				}
				return;
			}
			else {
				//m_addComponentWindow = false;
				m_entityToInspect = WorldSystem::Instance()->GetEntityByID(a_id);
				m_entityToInspect->SetEditorState(ecs::ECSEditorStates::HIGHLIGHTED);
				highlighEntity.SetNewHighlightedEntity(m_entityToInspect);
			}
		}
	}

	void EntityInspectorWidget::OnEntityDestroyed(std::string a_id)
	{
		// Check if the destroyed entity is the entity we inspect
		if (WorldSystem::Instance()->Instance()->GetEntityByID(a_id) == m_entityToInspect) {
			highlighEntity.SetNewHighlightedEntity(nullptr);
			m_entityToInspect = nullptr;
		}
	}

} }