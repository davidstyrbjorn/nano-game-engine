#include"../include/widgets/Widgets.h"

#include"../include/DearImGui/imgui.h"
#include"../include/systems/EditorConfig.h"

#include<math\Vector2.h>

namespace nano { namespace editor {

	ConsoleWidget::ConsoleWidget()
	{

	}

	void ConsoleWidget::Start()
	{

	}

	void ConsoleWidget::Update()
	{

	}

	void ConsoleWidget::Render()
	{
		math::Vector2 _windowSize = EditorConfig::Instance()->getWindowSize();

		// Calculate size
		ImVec2 size;
		size.x = (_windowSize.x * CONSOLE_WIDTH_RATIO);
		size.y = (_windowSize.y * CONSOLE_HEIGHT_RATIO) - MAIN_MENU_BAR_HEIGHT;

		// Calculate position
		ImVec2 pos;
		pos.x = (_windowSize.x * UTILITY_WIDTH_RATIO);
		pos.y = MAIN_MENU_BAR_HEIGHT + (_windowSize.y * ENTITY_SELECT_HEIGHT_RATIO) + (_windowSize.y * UNNAMED_WIDGET_HEIGHT_RATIO);

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::Begin("Console", false, size, 1.0f,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
		);

		for (ConsoleMessage message : m_messageQueue) 
		{
			ImVec4 color = ImVec4(message.color.x, message.color.y, message.color.z, message.color.w);
			ImGui::TextColored(color, message.messageString.c_str());
		}

		ImGui::End();
	}

	void ConsoleWidget::OnEntityManipulation(std::string a_id, std::string a_id2)
	{
		if (a_id == "entity_created") {
			AddConsoleMessage("Created entity with ID " + a_id2, math::Vector4(0, 1, 0, 1));
		}
		else if (a_id == "entity_clicked") {
			if (a_id == "-1") return; // Empty space
			AddConsoleMessage("Clicked on entity with ID " + a_id2);
		}
		else if (a_id == "entity_destroyed") {
			AddConsoleMessage("Destroyed entity with ID " + a_id, math::Vector4(1, 0, 0, 1));
		}
		else if (a_id == "entity_rename") {
			AddConsoleMessage("Renaming entity with ID " + a_id);
		}
	}

	void ConsoleWidget::OnComponentManipulation(std::string a_id, std::string a_id2, std::string a_id3)
	{
		AddConsoleMessage(a_id3 + " " + a_id2 + " on entity " + a_id);
	}

	void ConsoleWidget::OnNewConsoleMessage(std::string a_id)
	{
		AddConsoleMessage(a_id);
	}

	void ConsoleWidget::AddConsoleMessage(const std::string & a_message, const math::Vector4& a_color)
	{
		if (m_messageQueue.size() >= MESSAGE_COUNT_MAX)
			m_messageQueue.pop_back();
		m_messageQueue.push_front({ a_message, a_color });
	}
	
} }