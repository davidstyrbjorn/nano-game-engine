#pragma once

#include"../math/Vector2.h"
#include"../math/Vector4.h"

namespace nano {
	namespace ecs {
		class Transform;
	}
	namespace opengl {
		class Texture;
	}
}

namespace nano { namespace graphics { 

	// Base class for every renderable component (rectangle, triangle, sprite... etc)
	class Renderable {
	protected:
		// Renderable shared data
		math::Vector4 m_color = math::Vector4(0, 0, 0, 1); // deafault black color
		ecs::Transform* m_transform;
		opengl::Texture *m_texture;

	public:
		// Default constructor
		Renderable() { }

		// Setters

		///////////
		// \brief Sets the color
		//
		void SetColor(const math::Vector4 a_color);

		// Getters

		// brief Returns a vector copy of the color
		math::Vector4 GetColor();

		// brief Returns a pointer to the transform of the renderable
		ecs::Transform *GetTransformComponent();

		// brief Returns a pointer to the transform of the renderable
		opengl::Texture *GetTexture();

		///////////
		// \brief Returns the number of vertices for renderable 
		// \brief 3 - triangle, 4 - quad
		virtual int GetVertexCount();
	};

} } 