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
	private:
		asset::ImageAsset* s_errorTextureAsset;

	public:
		// Inits the neccesary data
		void Start() override;
		void Init() override;
		void OnStateChange(ECSStates a_newState);

		// Empty constructor
		SpriteComponent();

		// Loads new texture for sprite component
		void LoadNewAsset(asset::ImageAsset* a_imageAsset);

		// Override for the renderer 
		int GetVertexCount() override { return 4; }
	};

} }