#pragma once

#include"../../graphics/Renderable.h"
#include"../Component.h"

#include"../../math/Vector2.h"
#include"../../math/Vector4.h"

namespace nano { namespace ecs {

	class SpriteComponent : public graphics::Renderable, public Component
	{
	private:
		const char* m_imagePath;

	public:
		// Inits the neccesary data
		void Start() override;
		void Init() override;

		// Empty constructor
		SpriteComponent();

		// Constructor with arguments
		SpriteComponent(const char* a_imagePath);

		// Override for the renderer 
		int GetVertexCount() override { return 4; }
	};

} }