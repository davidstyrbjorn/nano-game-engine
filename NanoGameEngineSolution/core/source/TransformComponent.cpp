#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	Transform::Transform()
	{
		position = math::Vector2(0, 0);
		angle = 0;
	}

	void Transform::SetSize(math::Vector2 a_size)
	{
		size = a_size;
	}

	void Transform::move(math::Vector2 a_direction, float a_speed)
	{
		math::Vector2 newPosition = position + (a_direction * a_speed); 
	}

}
}