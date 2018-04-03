#pragma once

#include"EditorSystem.h" // base class

#include<vector>
#include<ecs\Entity.h>

namespace nano { namespace editor {
	
	/*
	*
	* std::vector<Entity*> m_entitiesToManage;
	* void AddNewEntity(Entity* a_entityToAdd);
	* std::vector<Entity*>& GetEntityList();
	*
	*/

	class WorldSystem : public EditorSystem<WorldSystem> {
		friend class EditorSystem<WorldSystem>;
	private:
		// Private Constructor (singleton)
		WorldSystem() { }

	private:
		std::vector<ecs::Entity*> m_entityList;

		// Private methods
		inline void removeDeadEntities();

	public:
		// Entity handling
		void AddNewEntity(ecs::Entity* a_entityToAdd);
		ecs::Entity* GetEntityByID(std::string a_id);
		std::vector<ecs::Entity*> &GetEntityList();
		std::vector<ecs::Entity*> GetEntityListCopy();
		// Outside creation
		void CreateNewEntity(std::string a_entityName);
		// Loaded new level
		void LoadedNewLevel(std::vector<ecs::Entity*> a_entityList); // Called when a new level is loaded
		void clearEntityList();

		// EditorSystem base class
		void Start() override;
		void Update() override;
		void Quit() override;
	};
	
} }