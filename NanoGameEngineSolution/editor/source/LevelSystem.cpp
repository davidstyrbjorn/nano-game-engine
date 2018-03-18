#include"../include/systems/LevelSystem.h"

#include"../include/LevelParser.h"

#include"../include/systems/WorldSystem.h"
#include"../include/systems/RendererSystem.h"
#include"../include/systems/WindowSystem.h"
#include"../include/systems/EditorWidgetSystem.h"
#include"../include/systems/EditorConfig.h"

#include<graphics\Simple_Renderer.h>
#include<graphics\Camera.h>
#include<graphics\Window.h>

namespace nano { namespace editor {

	void LevelSystem::Start()
	{
		EditorConfig* c = EditorConfig::Instance();
		static EditorWidgetSystem *widgetSystem = EditorWidgetSystem::getInstance();

		if (!loadLevel(c->getProjectInfo().startupLevel)) {
			widgetSystem->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, "Failed to load startup level!"));
		}
	}

	bool LevelSystem::loadLevel(std::string a_name)
	{
		static LevelParser levelParser;
		static WorldSystem *world = WorldSystem::getInstance();
		static RendererSystem *renderer = RendererSystem::getInstance();
		static WindowSystem *window = WindowSystem::getInstance();
		static EditorWidgetSystem *widgetSystem = EditorWidgetSystem::getInstance();

		std::string location = "resources\\levels\\" + a_name + ".txt";
		ParsedLevel level;
		bool loadResult = levelParser.GetParsedLevelFromFile(location.c_str(), level);
		if (loadResult) {
			world->LoadedNewLevel(level.entities);

			renderer->GetSimpleRenderer().GetCamera()->SetPosition(level.camPos);
			renderer->GetSimpleRenderer().GetCamera()->SetSize(level.camSize);
			window->GetWindow().SetNewWindowSize(level.camSize);

			EditorConfig::Instance()->setCurrentLevelName(a_name);

			widgetSystem->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, "Managed to load level " + a_name));
			return true;
		}
		else {
			widgetSystem->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, "Failed to load level " + a_name));
			return false;
		}
	}

	void LevelSystem::saveLevel(std::string a_name)
	{
		static LevelParser levelParser;
		static RendererSystem *renderer = RendererSystem::getInstance();
		static EditorWidgetSystem *widgetSystem = EditorWidgetSystem::getInstance();

		// @TODO: Check if we're over-saving some already existing level
		std::string location = "resources\\levels\\" + a_name + ".txt";
		graphics::OrthographicCamera *c = RendererSystem::getInstance()->GetSimpleRenderer().GetCamera();
		levelParser.ParseCurrentLevelToFile(location.c_str(), WorldSystem::getInstance()->GetEntityListCopy(), c->GetPosition(), c->GetSize());

		EditorConfig::Instance()->setCurrentLevelName(a_name);

		widgetSystem->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, "Managed to save level " + a_name));
	}

} }