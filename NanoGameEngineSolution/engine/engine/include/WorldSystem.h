#pragma once

#include"EngineSystemBase.h"

#include<vector>

namespace nano {
	namespace ecs {
		class Entity;
} }

namespace nano { namespace engine {  
	
	class WorldSystem : public EngineSystemBase<WorldSystem> {
	friend class EngineSystemBase<WorldSystem>;

	private:
		WorldSystem() {}

		std::vector<ecs::Entity*> m_entityList;

		// Called internally to de-allocate entities we want removed
		void deleteDeadEntities();

	public:
		void start() override;
		void update() override;
		void shutdown() override;

		// Entity adding/removing/getter
		void addEntity(ecs::Entity* a_entity);
		void createNewEntity(std::string a_id);

		ecs::Entity* getEntityByID(std::string a_id);
		std::vector<ecs::Entity*>& getEntityListReference();
		std::vector<ecs::Entity*>  getEntityListCopy();
	};


} }