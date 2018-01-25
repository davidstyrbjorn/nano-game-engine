#pragma once

#include"../include/systems/EntityManagerSystem.h"

namespace nano { namespace editor {

	EntityManagerSystem* EntityManagerSystem::_instance = nullptr;
	EntityManagerSystem* EntityManagerSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new EntityManagerSystem();
		return _instance;
	}

	void EntityManagerSystem::AddNewEntity(ecs::Entity * a_entityToAdd)
	{
		m_entityList.push_back(a_entityToAdd);
	}

	std::vector<ecs::Entity*>& EntityManagerSystem::GetEntityList()
	{
		return m_entityList;
	}

	std::vector<ecs::Entity*> EntityManagerSystem::GetEntityListCopy()
	{
		std::vector<ecs::Entity*> _list = m_entityList;
		return _list;
	}

	void EntityManagerSystem::CreateNewEntity(std::string a_entityName)
	{
		ecs::Entity* newEntity = new ecs::Entity(a_entityName);
		newEntity->Start();
		AddNewEntity(newEntity);
	}

	void EntityManagerSystem::Start()
	{
		for (ecs::Entity* entity : m_entityList) {
			entity->Start();
		}
	}

	void EntityManagerSystem::Update()
	{
		// Presumebly call update on all the entities
		for (ecs::Entity *entity : m_entityList) {
			entity->Update();
		}
	}

	void EntityManagerSystem::Quit()
	{
		for (std::vector<ecs::Entity*>::iterator _it = m_entityList.begin(); _it != m_entityList.end(); ++_it) {
			delete (*_it);
		}
		m_entityList.clear();

		std::cout << "Entity Manager system quit correctly" << std::endl;
	}

} }