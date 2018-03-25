#include"../include/widgets/Widgets.h"

#include<math\Vector2.h>
#include<ecs\Entity.h>
#include<math\Vector2.h>
#include<opengl\Texture.h>
#include<sound\SoundSource.h>
#include<sound\SoundBuffer.h>
#include<graphics\Simple_Renderer.h>
#include<graphics\Camera.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TriangleComponent.h>
#include<ecs\components\SpriteComponent.h>

#include"../include/components/FourwayMoveComponentEditor.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/InputSystem.h"
#include"../include/systems/RendererSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/EventHandler.h"
#include"../include/systems/EditorConfig.h"
#include"../include/systems/AssetSystem.h"

#include"../include/DearImGui/imgui.h"

#include<asset\ImageAsset.h>
#include<InputDefinitions.h>

namespace nano { namespace editor {

	EntityInspectorWidget::EntityInspectorWidget()
	{
		m_inputSystem = InputSystem::getInstance();
		m_renderSystem = RendererSystem::getInstance();
	}

	void EntityInspectorWidget::Start()
	{
	}

	void EntityInspectorWidget::Update()
	{
		highlighEntity.Update();
		if(highlighEntity.ShouldHighlight())
			RendererSystem::getInstance()->GetSimpleRenderer().Submit(highlighEntity.GetRenderable());

		math::Vector2 mousePos = m_inputSystem->GetMousePosition() + m_renderSystem->GetSimpleRenderer().GetCamera()->GetPosition();
		// Dragging input
		if (m_entityToInspect != nullptr) {
			for (InputEvent _event : m_inputSystem->GetPolledEvents()) {
				if (_event.type == InputEventType::KEY_PRESSED) {
					// "de"select entity
					if (_event.key == NANO_KEY_ESCAPE) {
						//OnEntityClick("-1"); @
					}
					// Delete the current entity
					if (_event.key == NANO_KEY_DELETE) {
						std::string temp = m_entityToInspect->GetID();
						m_entityToInspect->SetState(ecs::ECSStates::DESTROYED);
						highlighEntity.SetNewHighlightedEntity(nullptr);
						m_entityToInspect = nullptr;
						EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::MANIPULATED_ENTITY, "entity_destroyed", temp));
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
		if (m_isDraggingEntity) {
			m_entityToInspect->m_transform->position = mousePos - m_dragDeltaPosition;
		}
	}

	void EntityInspectorWidget::Render()
	{
		static AssetSystem *assetSystem = AssetSystem::getInstance();

		math::Vector2 _windowSize = EditorConfig::Instance()->getWindowSize();

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
			// State
			std::string stateString;
			if (m_entityToInspect->GetState() == ecs::ECSStates::ACTIVE) {
				stateString = "State: Active";
			}
			else {
				stateString = "State: Disabled";
			}
			ImGui::Text(stateString.c_str());

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
						// Event Handler
						BaseEvent _event(EventTypes::MANIPULATED_COMPONENT, m_entityToInspect->GetID(), "Renderable Component", "Destroyed");
						EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(_event);
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
					if (ImGui::Button("Change Image Asset")) {
						m_assetComponent = m_entityToInspect->GetComponent<ecs::SpriteComponent>();
						m_showImageAssetWindow = true;
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
						// Event handler
						BaseEvent _event(EventTypes::MANIPULATED_COMPONENT, m_entityToInspect->GetID(), "Sound Component", "Destroyed");
						EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(_event);
					}
					ImGui::EndPopup();
				}

				// Load sound asset
				if (ImGui::Button("Load Sound Asset")) {
					m_assetComponent = soundComponent;
					m_showImageAssetWindow = true;
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

			FourwayMoveComponentEditor* fwmComponent = m_entityToInspect->GetComponent<FourwayMoveComponentEditor>();
			bool hasFwmComponent = fwmComponent == nullptr ? false : true;
			if (hasFwmComponent) {

				ImGui::Text("FourwayMove Component");

				int up, right, down, left;
				up = fwmComponent->GetKey("up");
				right = fwmComponent->GetKey("right");
				down = fwmComponent->GetKey("down");
				left = fwmComponent->GetKey("left");

				ImGui::InputInt("Up", &up);
				ImGui::InputInt("Right", &right);
				ImGui::InputInt("Down", &down);
				ImGui::InputInt("Left", &left);

				int returnKeys[] = { up,right,down,left };
				fwmComponent->SetKeys(returnKeys);

				if (ImGui::Button("Show Keycodes")) {
					m_showKeycodeWindow = !m_showKeycodeWindow;
				}

				float velocity = fwmComponent->GetVelocity();
				ImGui::InputFloat("Velocity", &velocity, 0, 0, 2);
				fwmComponent->SetVelocity(velocity);

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
						m_entityToInspect->AddComponent(new ecs::SpriteComponent());
					}
					else {
						// Already have renderable component
					}
				}
				if (ImGui::Selectable("Rectangle Component")) {
					if (!hasRenderableComponent) {
						m_entityToInspect->AddComponent(new ecs::RectangleComponent(m_addComponentColor));
						if (m_entityToInspect->m_transform->size == math::Vector2(0, 0)) {
							m_entityToInspect->m_transform->size = m_addComponentSize;
						}
					}
					else {
						// Already have renderable component
					}
				}
				if (ImGui::Selectable("Triangle Component")) {
					if (!hasRenderableComponent) {
						m_entityToInspect->AddComponent(new ecs::TriangleComponent(m_addComponentColor));
						if (m_entityToInspect->m_transform->size == math::Vector2(0, 0)) {
							m_entityToInspect->m_transform->size = m_addComponentSize;
						}
					}
					else {
						// Already have renderable component
					}
				}
				if (ImGui::Selectable("Sound Component")) {
					if (!hasSoundComponent) {
						m_entityToInspect->AddComponent(new ecs::SoundComponent());
					}
					else {
						// Already have sound component
					}
				}
				if (ImGui::Selectable("Fourway Move Component")) {
					if (!hasFwmComponent) {
						m_entityToInspect->AddComponent(new FourwayMoveComponentEditor());
					}
					else {

					}
				}
				ImGui::EndPopup();
			}
		}

		ImGui::End();

		if (m_entityToInspect != nullptr && m_renameEntityWindow) 
		{
			static ImVec2 windowSize = ImVec2(300, 90);
			ImGui::Begin("Rename", &m_renameEntityWindow, windowSize, 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

			static char buffer[128] = "";
			if (ImGui::InputText("New Name", buffer, 128, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue) || ImGui::Button("Confirm"))
			{
				m_entityToInspect->SetID(buffer);
				m_renameEntityWindow = false;
			}

			ImGui::End();
		}

		if (m_entityToInspect != nullptr && m_showImageAssetWindow) 
		{
			static ImVec2 windowSize = ImVec2(200, 300);
			ImGui::SetNextWindowSize(windowSize);
			ImGui::Begin("Assets", &m_showImageAssetWindow, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);

			for (asset::Asset* asset : assetSystem->getAssetContainer()) {
				if (ImGui::Selectable(asset->getFileName().c_str())) {
					if (!m_assetComponent->LoadAsset(asset)) {
						// Failed to load asset for some reason (clicked on wrong formated asset probably)
						EditorWidgetSystem::getInstance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, "Failed to load asset!"));
					}
				}
			}

			ImGui::End();
		}

		if (m_showKeycodeWindow)
		{
			static ImVec2 windowSize = ImVec2(450, 400);
			ImGui::Begin("Keycodes", &m_showKeycodeWindow, windowSize, 1.0f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

			#pragma region KEYCODES
			ImGui::Text("NANO_MOUSE_BUTTON_1   0						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_2   1						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_3   2						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_4   3						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_5   4						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_6   5						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_7   6						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_8   7						 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_LAST   NANO_MOUSE_BUTTON_8	 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_LEFT   NANO_MOUSE_BUTTON_1	 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_RIGHT   NANO_MOUSE_BUTTON_2	 "	)  ;
			ImGui::Text("NANO_MOUSE_BUTTON_MIDDLE   NANO_MOUSE_BUTTON_3	 "	)  ;
			ImGui::Text("NANO_KEY_UNKNOWN   -1							 "	)  ;
			ImGui::Text("NANO_KEY_SPACE   32							 "	)  ;
			ImGui::Text("NANO_KEY_APOSTROPHE   39 						 "	)  ;
			ImGui::Text("NANO_KEY_COMMA   44 							 "	)  ;
			ImGui::Text("NANO_KEY_MINUS   45 							 "	)  ;
			ImGui::Text("NANO_KEY_PERIOD   46							 "	)  ;
			ImGui::Text("NANO_KEY_SLASH   47 							 "	)  ;
			ImGui::Text("Alpha0   48									 "	)  ;
			ImGui::Text("Alpha1   49									 "	)  ;
			ImGui::Text("Alpha2   50									 "	)  ;
			ImGui::Text("Alpha3   51									 "	)  ;
			ImGui::Text("Alpha4   52									 "	)  ;
			ImGui::Text("Alpha5   53									 "	)  ;
			ImGui::Text("Alpha6   54									 "	)  ;
			ImGui::Text("Alpha7   55									 "	)  ;
			ImGui::Text("Alpha8   56									 "	)  ;
			ImGui::Text("Alpha9   57									 "	)  ;
			ImGui::Text(";   59 										 "	)  ;
			ImGui::Text("=   61 										 "	)  ;
			ImGui::Text("A   65											 "	)  ;
			ImGui::Text("B   66											 "	)  ;
			ImGui::Text("C   67											 "	)  ;
			ImGui::Text("D   68											 "	)  ;
			ImGui::Text("E   69											 "	)  ;
			ImGui::Text("F   70											 "	)  ;
			ImGui::Text("G   71											 "	)  ;
			ImGui::Text("H   72											 "	)  ;
			ImGui::Text("I   73											 "	)  ;
			ImGui::Text("J   74											 "	)  ;
			ImGui::Text("K   75											 "	)  ;
			ImGui::Text("L   76											 "	)  ;
			ImGui::Text("M   77											 "	)  ;
			ImGui::Text("N   78											 "	)  ;
			ImGui::Text("O   79											 "	)  ;
			ImGui::Text("P   80											 "	)  ;
			ImGui::Text("Q   81											 "	)  ;
			ImGui::Text("R   82											 "	)  ;
			ImGui::Text("S   83											 "	)  ;
			ImGui::Text("T   84											 "	)  ;
			ImGui::Text("U   85											 "	)  ;
			ImGui::Text("V   86											 "	)  ;
			ImGui::Text("W   87											 "	)  ;
			ImGui::Text("X   88											 "	)  ;
			ImGui::Text("Y   89											 "	)  ;
			ImGui::Text("Z   90											 "	)  ;
			ImGui::Text("NANO_KEY_LEFT_BRACKET   91 					 "	)  ;
			ImGui::Text("NANO_KEY_BACKSLASH   92 						 "	)  ;
			ImGui::Text("NANO_KEY_RIGHT_BRACKET   93					 "	)  ;
			ImGui::Text("NANO_KEY_GRAVE_ACCENT   96 					 "	)  ;
			ImGui::Text("NANO_KEY_WORLD_1   161 						 "	)  ;
			ImGui::Text("NANO_KEY_WORLD_2   162 						 "	)  ;
			ImGui::Text("NANO_KEY_ESCAPE   256							 "	)  ;
			ImGui::Text("NANO_KEY_ENTER   257							 "	)  ;
			ImGui::Text("NANO_KEY_TAB   258								 "	)  ;
			ImGui::Text("NANO_KEY_BACKSPACE   259						 "	)  ;
			ImGui::Text("NANO_KEY_INSERT   260							 "	)  ;
			ImGui::Text("NANO_KEY_DELETE   261							 "	)  ;
			ImGui::Text("NANO_KEY_RIGHT   262							 "	)  ;
			ImGui::Text("NANO_KEY_LEFT   263 							 "	)  ;
			ImGui::Text("NANO_KEY_DOWN   264							 "	)  ;
			ImGui::Text("NANO_KEY_UP   265								 "	)  ;
			ImGui::Text("NANO_KEY_PAGE_UP   266							 "	)  ;
			ImGui::Text("NANO_KEY_PAGE_DOWN   267						 "	)  ;
			ImGui::Text("NANO_KEY_HOME   268							 "	)  ;
			ImGui::Text("NANO_KEY_END   269								 "	)  ;
			ImGui::Text("NANO_KEY_CAPS_LOCK   280						 "	)  ;
			ImGui::Text("NANO_KEY_SCROLL_LOCK   281						 "	)  ;
			ImGui::Text("NANO_KEY_NUM_LOCK   282						 "	)  ;
			ImGui::Text("NANO_KEY_PRINT_SCREEN   283					 "	)  ;
			ImGui::Text("NANO_KEY_PAUSE   284							 "	)  ;
			ImGui::Text("NANO_KEY_F1   290								 "	)  ;
			ImGui::Text("NANO_KEY_F2   291								 "	)  ;
			ImGui::Text("NANO_KEY_F3   292								 "	)  ;
			ImGui::Text("NANO_KEY_F4   293								 "	)  ;
			ImGui::Text("NANO_KEY_F5   294								 "	)  ;
			ImGui::Text("NANO_KEY_F6   295								 "	)  ;
			ImGui::Text("NANO_KEY_F7   296								 "	)  ;
			ImGui::Text("NANO_KEY_F8   297								 "	)  ;
			ImGui::Text("NANO_KEY_F9   298								 "	)  ;
			ImGui::Text("NANO_KEY_F10   299								 "	)  ;
			ImGui::Text("NANO_KEY_F11   300								 "	)  ;
			ImGui::Text("NANO_KEY_F12   301								 "	)  ;
			ImGui::Text("NANO_KEY_F13   302								 "	)  ;
			ImGui::Text("NANO_KEY_F14   303								 "	)  ;
			ImGui::Text("NANO_KEY_F15   304								 "	)  ;
			ImGui::Text("NANO_KEY_F16   305								 "	)  ;
			ImGui::Text("NANO_KEY_F17   306								 "	)  ;
			ImGui::Text("NANO_KEY_F18   307								 "	)  ;
			ImGui::Text("NANO_KEY_F19   308								 "	)  ;
			ImGui::Text("NANO_KEY_F20   309								 "	)  ;
			ImGui::Text("NANO_KEY_F21   310								 "	)  ;
			ImGui::Text("NANO_KEY_F22   311								 "	)  ;
			ImGui::Text("NANO_KEY_F23   312								 "	)  ;
			ImGui::Text("NANO_KEY_F24   313								 "	)  ;
			ImGui::Text("NANO_KEY_F25   314								 "	)  ;
			ImGui::Text("NANO_KEY_KP_0   320							 "	)  ;
			ImGui::Text("NANO_KEY_KP_1   321							 "	)  ;
			ImGui::Text("NANO_KEY_KP_2   322							 "	)  ;
			ImGui::Text("NANO_KEY_KP_3   323							 "	)  ;
			ImGui::Text("NANO_KEY_KP_4   324							 "	)  ;
			ImGui::Text("NANO_KEY_KP_5   325							 "	)  ;
			ImGui::Text("NANO_KEY_KP_6   326							 "	)  ;
			ImGui::Text("NANO_KEY_KP_7   327							 "	)  ;
			ImGui::Text("NANO_KEY_KP_8   328							 "	)  ;
			ImGui::Text("NANO_KEY_KP_9   329							 "	)  ;
			ImGui::Text("NANO_KEY_KP_DECIMAL   330						 "	)  ;
			ImGui::Text("NANO_KEY_KP_DIVIDE   331						 "	)  ;
			ImGui::Text("NANO_KEY_KP_MULTIPLY   332						 "	)  ;
			ImGui::Text("NANO_KEY_KP_SUBTRACT   333						 "	)  ;
			ImGui::Text("NANO_KEY_KP_ADD   334							 "	)  ;
			ImGui::Text("NANO_KEY_KP_ENTER   335						 "	)  ;
			ImGui::Text("NANO_KEY_KP_EQUAL   336						 "	)  ;
			ImGui::Text("NANO_KEY_LEFT_SHIFT   340						 "	)  ;
			ImGui::Text("NANO_KEY_LEFT_CONTROL   341					 "	)  ;
			ImGui::Text("NANO_KEY_LEFT_ALT   342						 "	)  ;
			ImGui::Text("NANO_KEY_LEFT_SUPER   343						 "	)  ;
			ImGui::Text("NANO_KEY_RIGHT_SHIFT   344						 "	)  ;
			ImGui::Text("NANO_KEY_RIGHT_CONTROL   345					 "	)  ;
			ImGui::Text("NANO_KEY_RIGHT_ALT   346						 "	)  ;
			ImGui::Text("NANO_KEY_RIGHT_SUPER   347						 "	)  ;
			ImGui::Text("NANO_KEY_MENU   348							 "	)  ;
			ImGui::Text("NANO_KEY_LAST   NANO_KEY_MENU					 "	)  ;
			#pragma endregion

			ImGui::End();
		}
	}

	void EntityInspectorWidget::OnEntityManipulation(std::string a_id, std::string a_id2) 
	{
		if (a_id == "entity_clicked") {
			if (!m_renameEntityWindow && !m_showKeycodeWindow && !m_showImageAssetWindow) {
				// "-1" - clicked on empty space
				if (a_id2 == "-1") {
					// Deselect the entity i.e set it to a nullptr
					if (m_entityToInspect != nullptr) {
						highlighEntity.SetNewHighlightedEntity(nullptr);
						m_entityToInspect = nullptr;
					}
					return;
				}
				else {
					m_entityToInspect = WorldSystem::getInstance()->GetEntityByID(a_id2);
					highlighEntity.SetNewHighlightedEntity(m_entityToInspect);
				}
			}
		}
		if (a_id == "entity_destroyed") {
			// Check if the destroyed entity is the entity we inspect
			if (m_entityToInspect != nullptr) {
				if (WorldSystem::getInstance()->GetEntityByID(a_id2) == m_entityToInspect) {
					highlighEntity.SetNewHighlightedEntity(nullptr);
					m_entityToInspect = nullptr;
				}
			}
		}
		if (a_id == "entity_rename") {
			m_renameEntityWindow = true;
		}
	}
} }