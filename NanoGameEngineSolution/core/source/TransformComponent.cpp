#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	Transform::Transform()
	{
		position = math::Vector2(0, 0);
		angle = 0;
	}	

}
}