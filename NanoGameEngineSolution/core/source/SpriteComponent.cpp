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

	void SpriteComponent::Init()
	{
		static asset::ImageAsset* s_errorTextureAsset;

		s_errorTextureAsset = new asset::ImageAsset();
		s_errorTextureAsset->loadNew("resources\\error_texture.png");
		m_imageAsset = s_errorTextureAsset; // Default asset pointer

		// Test with image asset object
		m_Texture = new opengl::Texture(s_errorTextureAsset->getImageData(), s_errorTextureAsset->getAssetInfo().width, s_errorTextureAsset->getAssetInfo().height, s_errorTextureAsset->getAssetInfo().format);
		if(m_owner->Transform()->size == math::Vector2::Zero())
			setTransformSizeToAssetSize();
	}

	bool SpriteComponent::LoadAsset(asset::Asset * a_assetPtr)
	{
		asset::ImageAsset* castAsset = dynamic_cast<asset::ImageAsset*>(a_assetPtr);
		if (castAsset == nullptr) {
			// Failed to cast to correct asset type!
			return false;
		}

		m_imageAsset = castAsset;

		m_Texture->Bind();
		m_Texture->SetTextureData(castAsset->getImageData(), castAsset->getAssetInfo().width, castAsset->getAssetInfo().height, castAsset->getAssetInfo().format);
		m_Texture->Unbind();
		return true;
	}

	asset::ImageAsset * SpriteComponent::getImageAsset()
	{
		return m_imageAsset;
	}

	void SpriteComponent::setTransformSizeToAssetSize()
	{
		float x = m_imageAsset->getAssetInfo().width;
		float y = m_imageAsset->getAssetInfo().height;
		m_owner->Transform()->size = math::Vector2(x, y);
	}

	void SpriteComponent::OnStateChange(ECSStates a_newState)
	{

	}

} }