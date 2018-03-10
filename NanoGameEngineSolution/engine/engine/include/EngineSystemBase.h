#pragma once

namespace nano {
	namespace ecs {
		class Entity;
	}
	namespace math {
		class Vector2;
	}
}

namespace nano { namespace engine {  

	template <typename T>
	class EngineSystemBase {
	public:
		static T* getInstance() {
			static T *instance;
			if (instance == nullptr)
				instance = new T();
			return instance;
		}

		// Virtual start-up method
		virtual void start() {}

		// Virtual update method
		virtual void update() { printf("Calling update on non-implemented update method!"); }
		virtual void update(float a_deltaTime) { printf("Calling update on non-implemented update method!"); }

		// Virtual shutdown method
		virtual void shutdown() {}

	protected:
		//EngineSystemBase() { }
		//~EngineSystemBase() { }
	};

} }