#include"../include/widgets/EntityInspectorWidget.h"

#include<CoreConfig.h>
#include<math\Vector2.h>
#include<ecs\Entity.h>
#include<math\Vector2.h>
#include<opengl\Texture.h>

#include"../include/systems/WorldSystem.h"
#include"../include/systems/InputSystem.h"

#include"../include/DearImGui/imgui.h"

#include<ecs\components\TransformComponent.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TriangleComponent.h>
#include<ecs\components\SpriteComponent.h>

#include<sound\SoundSource.h>
#include<sound\SoundBuffer.h>

#include<stb\stb_image.h>

namespace nano { namespace editor {

	EntityInspectorWidget::EntityInspectorWidget()
	{
		m_config = CoreConfig::Instance();
		m_inputSystem = InputSystem::Instance();
	}

	void EntityInspectorWidget::Start()
	{

	}

	void EntityInspectorWidget::Update()
	{
		// Dragging input
		if (m_entityToInspect != nullptr) {
			for (InputEvent _event : m_inputSystem->GetPolledEvents()) {
				if (_event.type == InputEventType::MOUSE_PRESSED) {
					math::Vector2 mousePos = m_inputSystem->GetMousePosition();

					if (mousePos.x > m_entityToInspect->m_transform->position.x && mousePos.x < m_entityToInspect->m_transform->position.x + m_entityToInspect->m_transform->size.x) {
						if (mousePos.y > m_entityToInspect->m_transform->position.y && mousePos.y < m_entityToInspect->m_transform->position.y + m_entityToInspect->m_transform->size.y) {
							m_isDraggingEntity = true;
							m_dragDeltaPosition = mousePos - m_entityToInspect->m_transform->position;
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
		if (m_isDraggingEntity) {
			m_entityToInspect->m_transform->position = m_inputSystem->GetMousePosition() - m_dragDeltaPosition;
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

			ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();

			// Start listing components
			graphics::Renderable* renderableComponent = m_entityToInspect->GetRenderableComponent();
			if (renderableComponent != nullptr) {
				// Shape type
				ImGui::Text("Renderable Component");
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
			}
			
			ImGui::Separator(); ImGui::Spacing();

			ecs::SoundComponent* soundComponent = m_entityToInspect->GetComponent<ecs::SoundComponent>();
			bool hasSoundComponent = soundComponent == nullptr ? false : true;
			if (hasSoundComponent) {

				openal::SoundSource *source = soundComponent->GetSource();

				ImGui::Text("Sound Component");
				
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
			}
		}

		ImGui::End();
	}

	void EntityInspectorWidget::OnEntityClick(std::string a_id)
	{
		// "-1" - clicked on empty space
		if (a_id == "-1") {
			if(m_entityToInspect != nullptr)
				m_entityToInspect->SetEditorState(ecs::ECSEditorStates::NOT_HIGHLIGHTED);
			m_entityToInspect = nullptr;
			return;
		}
		else {
			m_entityToInspect = WorldSystem::Instance()->GetEntityByID(a_id);
			m_entityToInspect->SetEditorState(ecs::ECSEditorStates::HIGHLIGHTED);
		}
	}

	void EntityInspectorWidget::OnEntityDestroyed(std::string a_id)
	{
		// Check if the destroyed entity is the entity we inspect
		if (WorldSystem::Instance()->Instance()->GetEntityByID(a_id) == m_entityToInspect) {
			m_entityToInspect = nullptr;
		}
	}

} }