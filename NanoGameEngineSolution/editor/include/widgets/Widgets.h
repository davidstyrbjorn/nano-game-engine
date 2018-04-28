#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"
#include"../HighlightEntity.h"

#include<math\Vector2.h>
#include<math\Vector4.h>

#include<deque>

// FWD
namespace nano {
	namespace ecs {
		class RenderableComponent;
		class Entity;
		class Component;
		class SoundComponent;
	}
	namespace editor {
		class InputSystem;
		class RendererSystem;
		class WorldSystem;
		class FourwayMoveComponentEditor;
		class ScriptComponent;
	}
}

namespace nano { namespace editor {

	// Console Widget bottom-right
	class ConsoleWidget : EditorWidget, public EventObserver {
	private:
		struct ConsoleMessage {
			std::string messageString;
			math::Vector4 color;
		};

		std::deque<ConsoleMessage> m_messageQueue;
		const int MESSAGE_COUNT_MAX = 7;

		void AddConsoleMessage(const std::string& a_message, const math::Vector4& a_color = math::Vector4(1, 1, 1, 1));

	public:
		ConsoleWidget();

		// Base methods
		void Start() override;
		void Update() override;
		void Render() override;

		// Methods from event observer base
		void OnEntityManipulation(std::string a_id, std::string a_id2);
		void OnComponentManipulation(std::string a_id, std::string a_id2, std::string a_id3) override;
		void OnNewConsoleMessage(std::string a_id) override;
	};

	// ===============================================================================
	// ===============================================================================
	// ===============================================================================


	// Entity Inspector upper-right
	class EntityInspectorWidget : EditorWidget, public EventObserver {
	private:
		WorldSystem* m_worldSystem;
		InputSystem* m_inputSystem;
		RendererSystem *m_renderSystem;
		//ecs::Entity *m_entityToInspect;
		int m_currentEntityIndex = -1;
		HighlightEntity highlighEntity;

		// Drag entity
		bool m_isDraggingEntity = false;
		math::Vector2 m_dragDeltaPosition;

		// Add component
		const math::Vector2 m_addComponentSize = math::Vector2(100, 100);
		const math::Vector4 m_addComponentColor = math::Vector4(1, 1, 1, 1);

		// Other
		bool m_renameEntityWindow = false;
		bool m_showKeycodeWindow = false;
		bool m_showImageAssetWindow = false; 
		bool m_showScriptBrowser = false;

		ecs::Component *m_assetComponent;
		ecs::RenderableComponent *m_renderableComponent;
		ecs::SoundComponent *m_soundComponent;
		FourwayMoveComponentEditor *m_fourwayMoveComponent;
		ScriptComponent* m_scriptComponent;

	public:
		EntityInspectorWidget();

		// Base methods
		void Start() override;
		void Update() override;
		void Render() override;

		// Inspection ImGui routines
		void displayTransformComponentGraphics();
		void displayRenderableComponentGraphics();
		void displaySoundComponentGraphics();
		void displayFourwayMoveComponentGraphics();
		void displayScriptComponentGraphics();

		void clickedOnNewEntity(ecs::Entity* a_entity);
		void clickedOnNewEntity(int a_index);

		inline bool rightClickRemoveComponent(ecs::_ComponentTypes a_type, std::string a_componentName);

		void OnEntityManipulation(std::string a_id, std::string a_id2);
	};

	// ===============================================================================
	// ===============================================================================
	// ===============================================================================

	// Entity selection upper-left
	class EntitySelectWidget : EditorWidget, public EventObserver {
	private:
		WorldSystem* m_entityManager;
		InputSystem* m_inputSystem;
		RendererSystem *m_renderSystem;
		//ecs::Entity *m_leftClickedEntity;
		int m_leftClickedIndex;

		bool m_isDraggingView = false;
		math::Vector2 m_dragOrigin;
		math::Vector2 m_lastFrameMousePos;

		// Private methods
		bool IsMouseInViewFrustrum(const math::Vector2& a_pos);

	public:
		EntitySelectWidget();

		// Base class 
		void Start() override;
		void Update() override;
		void Render() override;
	};

	// ===============================================================================
	// ===============================================================================
	// ===============================================================================

	// Main menu bar "file, invoke, about" upper
	class MenuBarWidget : EditorWidget {
	private:
		InputSystem *input;

	public:
		// Default constructor
		MenuBarWidget();

		// Base class
		void Start() override;
		void Update() override;
		void Render() override;
	};

	// middle-left
	class AssetBrowserWidget : EditorWidget, public EventObserver {
	private:
		char m_fileNameBuffer[260]; // Buffer for file name

	public:
		AssetBrowserWidget();

		// Base methods
		void Start() override;
		void Update() override;
		void Render() override;
	};

	// ===============================================================================
	// ===============================================================================
	// ===============================================================================

	// Utility manipulation widget bottom-left
	class UtilityWidget : EditorWidget, public EventObserver {
	public:
		// Default constructor
		UtilityWidget();

		// Editor Widget Base
		void Start() override;
		void Update() override;
		void Render() override;

	private:
		RendererSystem *m_renderSystem;
	};
} }