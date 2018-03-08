#include"../include/WorldSystem.h"

#include<ecs\Entity.h>

namespace nano { namespace engine {  

	void WorldSystem::shutdown()
	{
		std::vector<ecs::Entity*>::iterator it;
		for (it = m_entityList.begin(); it != m_entityList.end(); ++it) {
			delete *it;
		}
		m_entityList.clear();

		// This does not account for individual entity size (components)
		//std::cout << sizeof(std::vector<ecs::Entity*>) + (sizeof(ecs::Entity) * m_entityList.size()) << std::endl;
		
		std::cout << "World System quit correctly" << std::endl;
	}

	void WorldSystem::start()
	{
		// Call start on every entity
		for (ecs::Entity* entity : m_entityList) {
			entity->Start();
		}
	}

	void WorldSystem::update()
	{
		deleteDeadEntities();

		// Call update on every entity 
		for (ecs::Entity* entity : m_entityList) {
			entity->Update();
		}
	}

	void WorldSystem::deleteDeadEntities()
	{
		std::vector<ecs::Entity*>::iterator it;
		for (it = m_entityList.begin(); it != m_entityList.end();) {
			if ((*it)->GetState() == ecs::ECSStates::DESTROYED) {
				delete *it;
				it = m_entityList.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void WorldSystem::addEntity(ecs::Entity * a_entity)
	{
		m_entityList.push_back(a_entity);
	}

	ecs::Entity* WorldSystem::createNewEntity(std::string a_id)
	{
		ecs::Entity* newEntity = new ecs::Entity(a_id);
		newEntity->Start();
		addEntity(newEntity);
		return newEntity;
	}

	ecs::Entity * nano::engine::WorldSystem::getEntityByID(std::string a_id)
	{
		for (ecs::Entity* entity : m_entityList) {
			if (entity->GetID() == a_id) {
				if (entity->GetState() != ecs::ECSStates::DESTROYED) {
					return entity;
				}
			}
		}
	}

	std::vector<ecs::Entity*>& nano::engine::WorldSystem::getEntityListReference()
	{
		return m_entityList;
	}

	std::vector<ecs::Entity*> nano::engine::WorldSystem::getEntityListCopy()
	{
		return m_entityList;
	}

	void WorldSystem::newLevel(std::vector<ecs::Entity*> a_entities)
	{
		std::vector<ecs::Entity*>::iterator it;
		for (it = m_entityList.begin(); it != m_entityList.end(); ++it) {
			delete *it;
		}
		m_entityList.clear();

		m_entityList = a_entities;
	}

} }