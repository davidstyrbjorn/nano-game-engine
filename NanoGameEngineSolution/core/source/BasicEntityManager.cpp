#include"../include/ecs/BasicEntityManager.h"
#include"../include/ecs/Entity.h"

namespace nano { namespace ecs {

	BasicEntityManager::~BasicEntityManager()
	{
		for (std::vector<Entity*>::iterator _it = m_entitiesToManage.begin(); _it != m_entitiesToManage.end(); ++_it) {
			delete (*_it);
		}
		m_entitiesToManage.clear();
	}

	void BasicEntityManager::AddNewEntity(Entity * a_entityToAdd)
	{
		m_entitiesToManage.push_back(a_entityToAdd);
	}

}
}