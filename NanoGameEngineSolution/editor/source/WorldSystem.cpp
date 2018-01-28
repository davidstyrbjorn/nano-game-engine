#pragma once

#include"../include/systems/WorldSystem.h"

namespace nano { namespace editor {

	WorldSystem* WorldSystem::_instance = nullptr;
	WorldSystem* WorldSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new WorldSystem();
		return _instance;
	}

	void WorldSystem::AddNewEntity(ecs::Entity * a_entityToAdd)
	{
		m_entityList.push_back(a_entityToAdd);
	}

	ecs::Entity * WorldSystem::GetEntityByID(std::string a_id)
	{
		for (ecs::Entity* entity : m_entityList) {
			if (a_id == entity->GetID()) {
				if (entity->GetState() != ecs::ECSStates::DESTROYED) {
					return entity;
				}
			}
		}
	}

	std::vector<ecs::Entity*>& WorldSystem::GetEntityList()
	{
		return m_entityList;
	}

	std::vector<ecs::Entity*> WorldSystem::GetEntityListCopy()
	{
		std::vector<ecs::Entity*> _list = m_entityList;
		return _list;
	}

	void WorldSystem::CreateNewEntity(std::string a_entityName)
	{
		ecs::Entity* newEntity = new ecs::Entity(a_entityName);
		newEntity->Start();
		AddNewEntity(newEntity);
	}

	void WorldSystem::Start()
	{
		for (ecs::Entity* entity : m_entityList) {
			entity->Start();
		}
	}

	void WorldSystem::Update()
	{
		bool deadEntityExists = false;
		removeDeadEntities();

		// Presumebly call update on all the entities
		for (ecs::Entity *entity : m_entityList) {
			entity->Update();
			if (entity->GetState() == ecs::ECSStates::DESTROYED)
				deadEntityExists = true;
		}

		if (deadEntityExists) {
			//removeDeadEntities();
		}
	}

	inline void WorldSystem::removeDeadEntities()
	{
		std::vector<ecs::Entity*>::iterator it;
		for (it = m_entityList.begin() ; it != m_entityList.end() ; ) {
			if ((*it)->GetState() == ecs::ECSStates::DESTROYED) {
				delete *it;
				it = m_entityList.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void WorldSystem::Quit()
	{
		for (std::vector<ecs::Entity*>::iterator _it = m_entityList.begin(); _it != m_entityList.end(); ++_it) {
			delete (*_it);
		}
		m_entityList.clear();

		std::cout << "Entity Manager system quit correctly" << std::endl;
	}

} }