#include "..\..\engine\engine\include\WorldSystem.h"

#include"../include/systems/WorldSystem.h"

#include<iostream>

namespace nano { namespace editor {

	ecs::Entity& WorldSystem::getEntity(int a_index)
	{
		return m_entityArray[a_index];
	}

	std::vector<ecs::Entity> WorldSystem::getArray()
	{
		return std::vector<ecs::Entity>(std::begin(m_entityArray), std::end(m_entityArray));
	}

	int WorldSystem::createNewEntity(std::string a_name) 
	{
		// Create new entity -> array at the current entity count index
		int at = m_entityCount;

		m_entityArray[at] = ecs::Entity(a_name);
		m_entityArray[at].SlotIndex = at;

		m_entityCount++;

		return at;
	}

	void WorldSystem::removeEntity(int a_index)
	{
		// Check if we're removing something besides the head of the array
		if (a_index < m_entityCount) {
			int delta = m_entityCount - a_index;
			// @@ Implement this somehow
		}
		else {
			m_entityArray[a_index].Kill(); // @@ make sure entity deallocates all allocated memory here!
			m_entityCount--;
		}
	}

	void WorldSystem::LoadedNewLevel(std::vector<ecs::Entity*> a_entityList)
	{

	}

	void WorldSystem::Start()
	{
		m_entityCount = 0;
	}

	void WorldSystem::Update()
	{
		for (int i = 0; i < m_entityCount; i++) {
			m_entityArray[i].Update();
		}
	}

	void WorldSystem::FixedUpdate()
	{
		for (int i = 0; i < m_entityCount; i++) {
			m_entityArray[i].FixedUpdate();
		}
	}

	void WorldSystem::Quit()
	{
		std::cout << "Entity Manager system quit correctly" << std::endl;
	}
} }