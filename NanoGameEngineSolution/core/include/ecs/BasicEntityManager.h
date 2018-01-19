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
		// \brief Implementation class will override this to start the managed entities
		// \brief Engine will override this to start the entities while editor will not
		virtual void Start();

		//////////
		// \brief Implementation class will override this to update the managed entities
		// \brief Engine will override this to update entities run time while editor will not
		virtual void Update();
	};
	
} }