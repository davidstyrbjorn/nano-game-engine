#include"../include/ecs/components/SpriteComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

#include"../include/opengl/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../include/stb/stb_image.h"

#include"../include/CoreConfig.h"

namespace nano { namespace ecs {

	void SpriteComponent::Start()
	{

	}

	void SpriteComponent::Init()
	{
		m_transform = m_owner->m_transform;

		int width, height, n;
		unsigned char *data = stbi_load(m_imagePath, &width, &height, &n, 0);
		if (data == NULL) {
			data = stbi_load(CoreConfig::Instance()->GetErrorTexturePath(), &width, &height, &n, 0);
		}

		GLenum format;
		std::string extension = GetFileExtension(m_imagePath);
		if (extension == ".png")
			format = GL_RGBA;
		else if (extension == ".jpg")
			format = GL_RGB;
		else
			format = GL_RGB; // Default format if unkown extension

		m_texture = new opengl::Texture(data, width, height, format);

		stbi_image_free(data);

		m_transform->size = math::Vector2(width, height);
	}

	void SpriteComponent::OnStateChange(ECSStates a_newState)
	{
		if (a_newState == ECSStates::DESTROYED) {
			m_owner->SetRenderableComponent(nullptr);
		}
	}

	SpriteComponent::SpriteComponent()
	{
		
	}

	SpriteComponent::SpriteComponent(const char * a_imagePath)
	{
		m_imagePath = a_imagePath;
	}

	void SpriteComponent::LoadNewTexture(const char * a_imagePath)
	{
		int width, height, n;
		unsigned char *data = stbi_load(a_imagePath, &width, &height, &n, 0);
		if (data == NULL) {
			data = stbi_load(CoreConfig::Instance()->GetErrorTexturePath(), &width, &height, &n, 0);
		}

		std::string extension = GetFileExtension(a_imagePath);

		m_texture->Bind();
		if (extension == ".png")
			m_texture->SetTextureData(data, width, height, GL_RGBA);
		else if (extension == ".jpg")
			m_texture->SetTextureData(data, width, height, GL_RGB);
		m_texture->Unbind();

		stbi_image_free(data);
	}

	std::string SpriteComponent::GetFileExtension(const char * a_string)
	{
		std::string temp = std::string(a_string);
		std::string extension = "";
		int extensionIndex = temp.find('.');
		for (int i = extensionIndex; i < temp.length(); i++) { extension += temp[i]; }

		return extension;
	}

} }