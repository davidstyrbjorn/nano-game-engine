#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"

#include<math\Vector2.h>
#include<math\Vector4.h>

#include"../HighlightEntity.h"

#include<deque>

// FWD
namespace nano {
	class CoreConfig;
	namespace ecs {
		class Entity;
	}
	namespace editor {
		class InputSystem;
		class RendererSystem;
		class WorldSystem;
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

		CoreConfig* m_config;
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
		void OnEntityCreation(std::string a_id)   override;
		void OnEntityDestroyed(std::string a_id)  override;
		void OnEntityClick(std::string a_id) 	  override;
		void OnEntityRename(std::string a_id) 	  override;
		virtual void OnComponentManipulation(std::string a_id, std::string a_id2, std::string a_id3) override;
	};

	// Entity Inspector upper-right
	class EntityInspectorWidget : EditorWidget, public EventObserver {
	private:
		CoreConfig* m_config;
		InputSystem* m_inputSystem;
		RendererSystem *m_renderSystem;
		ecs::Entity *m_entityToInspect;
		HighlightEntity highlighEntity;

		// Drag entity
		bool m_isDraggingEntity = false;
		math::Vector2 m_dragDeltaPosition;

		// Add component
		const math::Vector2 m_addComponentSize = math::Vector2(100, 100);
		const math::Vector4 m_addComponentColor = math::Vector4(1, 0, 1, 1);

		// Rename
		bool m_renameEntityWindow = false;
		bool m_showKeycodeWindow = false;

	public:
		EntityInspectorWidget();

		// Base methods
		void Start() override;
		void Update() override;
		void Render() override;

		void OnEntityRename(std::string a_id) override; 
		void OnEntityClick(std::string a_id) override;
		void OnEntityDestroyed(std::string a_id) override;
	};

	// Entity selection upper-left
	class EntitySelectWidget : EditorWidget, public EventObserver {
	private:
		CoreConfig* m_config;
		WorldSystem* m_entityManager;
		InputSystem* m_inputSystem;
		RendererSystem *m_renderSystem;
		ecs::Entity *m_leftClickedEntity;

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

	// Main menu bar "file, invoke, about" upper
	class MenuBarWidget : EditorWidget {
	public:
		// Default constructor
		MenuBarWidget();

		// Base class
		void Start() override;
		void Update() override;
		void Render() override;

	private:
		CoreConfig *m_config;
		bool m_showCreditsWidget = false;
	};

	// middle-left
	class UtilitySelectWidget : EditorWidget, public EventObserver {
	private:
		CoreConfig* m_config;

	public:
		UtilitySelectWidget();

		// Base methods
		void Start() override;
		void Update() override;
		void Render() override;
	};

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
		CoreConfig *m_config;
		RendererSystem *m_renderSystem;
	};
} }