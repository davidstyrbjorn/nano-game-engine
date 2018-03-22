#include"../include/ecs/components/SpriteComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

#include"../include/opengl/Texture.h"

#include"../include/asset/ImageAsset.h"

namespace nano { namespace ecs {

	void SpriteComponent::Start()
	{

	}

	void SpriteComponent::Init()
	{
		m_transform = m_owner->m_transform;
		s_errorTextureAsset = new asset::ImageAsset();
		s_errorTextureAsset->loadNew("resources\\error_texture.png");

		// Test with image asset object
		m_texture = new opengl::Texture(s_errorTextureAsset->getImageData(), s_errorTextureAsset->getAssetInfo().width, s_errorTextureAsset->getAssetInfo().height, s_errorTextureAsset->getAssetInfo().format);
		m_transform->size = math::Vector2(s_errorTextureAsset->getAssetInfo().width, s_errorTextureAsset->getAssetInfo().height);
	}

	void SpriteComponent::OnStateChange(ECSStates a_newState)
	{
		if (a_newState == ECSStates::DESTROYED) {
			m_owner->SetRenderableComponent(nullptr);
		}
	}

	SpriteComponent::SpriteComponent()
	{
		//m_imageAsset = new asset::ImageAsset();
		//m_imageAsset->loadNew("resources\\error_texture.png");
	}

	void SpriteComponent::LoadNewAsset(asset::ImageAsset * a_imageAsset)
	{
		if (a_imageAsset == nullptr) {
			std::cout << "Asset is nullptr" << std::endl;
		}
		m_texture->Bind();
		m_texture->SetTextureData(a_imageAsset->getImageData(), a_imageAsset->getAssetInfo().width, a_imageAsset->getAssetInfo().height, a_imageAsset->getAssetInfo().format);
		m_texture->Unbind();
	}

} }