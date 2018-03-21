#include"../include/ecs/components/SpriteComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

#include"../include/opengl/Texture.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include"../include/stb/stb_image.h"

namespace nano { namespace ecs {

	void SpriteComponent::Start()
	{

	}

	void SpriteComponent::Init()
	{
		m_transform = m_owner->m_transform;

		// Get the format of the image to load
		GLenum format;
		//std::string extension = GetFileExtension(m_imagePath);
		//if (extension == ".png")
		//	format = GL_RGBA;
		//else if (extension == ".jpg")
		//	format = GL_RGB;
		//else
		//	format = GL_RGB; // Default format if unkown extension
		//
		//int width, height, n;
		//unsigned char *data = stbi_load(m_imagePath, &width, &height, &n, 0);
		//if (data == NULL) {
		//	data = stbi_load("resources\\error_texture.png", &width, &height, &n, 0);
		//	format = GL_RGBA;
		//}
		//
		//m_texture = new opengl::Texture(data, width, height, format);
		//
		//stbi_image_free(data);

		// Test with image asset object
		std::string suffix = m_imageAsset->getAssetInfo().file.suffix;
		if (suffix == "png")
			format = GL_RGBA;
		else if (suffix == "jpg")
			format = GL_RGB;
		else
			format = GL_RGB; // Default format if unkown extension
		m_texture = new opengl::Texture(m_imageAsset->getImageData(), m_imageAsset->getAssetInfo().width, m_imageAsset->getAssetInfo().height, format);
		m_transform->size = math::Vector2(m_imageAsset->getAssetInfo().width, m_imageAsset->getAssetInfo().height);
	}

	void SpriteComponent::OnStateChange(ECSStates a_newState)
	{
		if (a_newState == ECSStates::DESTROYED) {
			m_owner->SetRenderableComponent(nullptr);
		}
	}

	SpriteComponent::SpriteComponent()
	{
		m_imageAsset = new asset::ImageAsset();
		m_imageAsset->loadNew("resources\\error_texture.png");
	}

	SpriteComponent::SpriteComponent(const char * a_imagePath)
	{
		if (m_imageAsset != nullptr)
			m_imageAsset->freeData();
		m_imageAsset = new asset::ImageAsset();
		m_imageAsset->loadNew(a_imagePath);
	}

	void SpriteComponent::LoadNewTexture(const char * a_imagePath)
	{
		m_imagePath = a_imagePath;

		if (m_imageAsset != nullptr)
			m_imageAsset->freeData();
		m_imageAsset = new asset::ImageAsset();
		m_imageAsset->loadNew(m_imagePath);

		m_texture->Bind();
		m_texture->SetTextureData(m_imageAsset->getImageData(), m_imageAsset->getAssetInfo().width, m_imageAsset->getAssetInfo().height, GL_RGBA);
		m_texture->Unbind();

		//int width, height, n;
		//unsigned char *data = stbi_load(a_imagePath, &width, &height, &n, 0);
		//if (data == NULL) {
		//	data = stbi_load("resources\\error_texture.png", &width, &height, &n, 0);
		//	m_imagePath = "resources\\error_texture.png";
		//}
		//
		//std::string extension = GetFileExtension(a_imagePath);
		//
		//m_texture->Bind();
		//if (extension == ".png")
		//	m_texture->SetTextureData(data, width, height, GL_RGBA);
		//else if (extension == ".jpg")
		//	m_texture->SetTextureData(data, width, height, GL_RGB);
		//m_texture->Unbind();
		//
		//stbi_image_free(data);
	}

	void SpriteComponent::LoadNewAsset(asset::ImageAsset * a_imageAsset)
	{
		m_texture->Bind();
		m_texture->SetTextureData(a_imageAsset->getImageData(), a_imageAsset->getAssetInfo().width, a_imageAsset->getAssetInfo().height, GL_RGBA);
		m_texture->Unbind();
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