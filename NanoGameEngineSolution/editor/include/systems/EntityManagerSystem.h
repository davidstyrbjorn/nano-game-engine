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

	class EntityManagerSystem : EditorSystem
	{
	private:
		// Private Constructor (singleton)
		EntityManagerSystem() { }

		static EntityManagerSystem *_instance;

	public:
		static EntityManagerSystem* Instance();

	private:
		std::vector<ecs::Entity*> m_entityList;

	public:
		// Entity handling
		void AddNewEntity(ecs::Entity* a_entityToAdd);
		std::vector<ecs::Entity*> &GetEntityList();

		// EditorSystem base class
		void Start() override;
		void Update() override;
		void Quit() override;
	};
	
} }