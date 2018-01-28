#include"../include/ecs/components/SpriteComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

#include"../include/opengl/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../include/stb/stb_image.h"

namespace nano { namespace ecs {  

	void SpriteComponent::Start()
	{

	}

	void SpriteComponent::Init()
	{
		m_transform = m_owner->m_transform;

		int width, height, n;
		unsigned char *data = stbi_load(m_imagePath, &width, &height, &n, 0);
		m_texture = new opengl::Texture(data, width, height);
		stbi_image_free(data);

		m_transform->size = math::Vector2(width, height);
	}

	SpriteComponent::SpriteComponent()
	{
	}

	SpriteComponent::SpriteComponent(const char * a_imagePath)
	{
		m_color = math::Vector4(0, 0, 0, 1);
		m_imagePath = a_imagePath;
	}

} }