#pragma once

#include"../RenderableComponent.h"

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano {
	namespace asset {
		class ImageAsset;
} }

namespace nano { namespace ecs {

	class SpriteComponent : public RenderableComponent
	{
	public:
		// Inits texture and asset data (default: error_texture.png)
		void Init();

		// Empty constructor
		SpriteComponent();

		// Loads new texture for sprite component
		bool LoadAsset(asset::Asset* a_assetPtr);
		asset::ImageAsset* getImageAsset();
		void setTransformSizeToAssetSize();

		// For the renderer 
		int getVertexCount() const { return 4; }

	private:
		asset::ImageAsset* m_imageAsset;
	};

} }