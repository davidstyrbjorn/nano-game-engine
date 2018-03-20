#pragma once

#include"../../graphics/Renderable.h"
#include"../Component.h"

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

// Test
#include"../../asset/ImageAsset.h"

namespace nano { namespace ecs {

	class SpriteComponent : public graphics::Renderable, public Component
	{
	private:
		asset::ImageAsset *m_imageAsset;
		const char* m_imagePath;

		// Private methods
		std::string GetFileExtension(const char* a_string);

	public:
		// Inits the neccesary data
		void Start() override;
		void Init() override;
		void OnStateChange(ECSStates a_newState);

		// Empty constructor
		SpriteComponent();

		// Constructor with arguments
		SpriteComponent(const char* a_imagePath);

		// Loads new texture for sprite component
		void LoadNewTexture(const char* a_imagePath);

		// Override for the renderer 
		int GetVertexCount() override { return 4; }

		// Get texture path
		const char* GetImagePath() { return m_imagePath; }
	};

} }