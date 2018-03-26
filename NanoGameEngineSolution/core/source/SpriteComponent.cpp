#include"../include/ecs/components/SpriteComponent.h"

#include"../include/ecs/Entity.h"
#include"../include/ecs/components/TransformComponent.h"

#include"../include/opengl/Texture.h"

#include"../include/asset/ImageAsset.h"

namespace nano { namespace ecs {


	SpriteComponent::SpriteComponent()
	{
		// Ignore here, do init code in init function
	}

	void SpriteComponent::Start()
	{

	}

	void SpriteComponent::Init()
	{
		static asset::ImageAsset* s_errorTextureAsset;

		m_transform = m_owner->m_transform;
		s_errorTextureAsset = new asset::ImageAsset();
		s_errorTextureAsset->loadNew("resources\\error_texture.png");
		m_imageAsset = s_errorTextureAsset; // Default asset pointer

		// Test with image asset object
		m_texture = new opengl::Texture(s_errorTextureAsset->getImageData(), s_errorTextureAsset->getAssetInfo().width, s_errorTextureAsset->getAssetInfo().height, s_errorTextureAsset->getAssetInfo().format);
		m_transform->size = math::Vector2(s_errorTextureAsset->getAssetInfo().width, s_errorTextureAsset->getAssetInfo().height);
	}

	bool SpriteComponent::LoadAsset(asset::Asset * a_imageAsset)
	{
		asset::ImageAsset* castAsset = dynamic_cast<asset::ImageAsset*>(a_imageAsset);
		if (castAsset == nullptr) {
			// Failed to cast to correct asset type!
			return false;
		}

		m_imageAsset = castAsset;

		m_texture->Bind();
		m_texture->SetTextureData(castAsset->getImageData(), castAsset->getAssetInfo().width, castAsset->getAssetInfo().height, castAsset->getAssetInfo().format);
		m_texture->Unbind();
		return true;
	}

	asset::ImageAsset * SpriteComponent::getImageAsset()
	{
		return m_imageAsset;
	}

	void SpriteComponent::OnStateChange(ECSStates a_newState)
	{
		if (a_newState == ECSStates::DESTROYED) {
			m_owner->SetRenderableComponent(nullptr);
		}
	}

} }