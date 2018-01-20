#pragma once

#include<vector>

namespace nano { namespace ecs {

	// Forward decleration
	class Entity;

	class BasicEntityManager {
	protected:
		std::vector<Entity*> m_entitiesToManage;

	public:
		//////////
		// \brief Empty Constructor
		//
		BasicEntityManager() { }

		//////////
		// \brief Destructor frees/deletes all the entity pointers inside the managed list
		//
		virtual ~BasicEntityManager();

		//////////
		// \brief Adds a entity to be managed by the entity manager
		//  
		void AddNewEntity(Entity* a_entityToAdd);

		//////////
		// \brief Implementation class will override this to start the managed entities
		// \brief Engine will override this to start the entities while editor will not
		virtual void Start() { }

		//////////
		// \brief Implementation class will override this to update the managed entities
		// \brief Engine will override this to update entities run time while editor will not
		virtual void Update() { } 
	};
	
} }