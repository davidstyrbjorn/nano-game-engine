#pragma once

#include"../../graphics/Renderable.h"
#include"../Component.h"

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano {
	namespace asset {
		class ImageAsset;
} }

namespace nano { namespace ecs {

	class SpriteComponent : public graphics::Renderable, public Component
	{
	public:
		// Inits the neccesary data
		void Start() override;
		void Init() override;
		void OnStateChange(ECSStates a_newState);

		// Empty constructor
		SpriteComponent();

		// Loads new texture for sprite component
		bool LoadAsset(asset::Asset* a_imageAsset) override;
		asset::ImageAsset* getImageAsset();

		// Override for the renderer 
		int GetVertexCount() override { return 4; }

	private:
		asset::ImageAsset* m_imageAsset;
	};

} }