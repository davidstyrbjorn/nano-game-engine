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
		math::Vector4 m_color = math::Vector4(1, 1, 1, 1); // deafault white color
		ecs::Transform* m_transform;
		opengl::Texture *m_texture;
		int m_renderOrder = 0;

	public:
		// Default constructor
		Renderable() { }

		// Virtual destructor
		virtual ~Renderable();

		// Setters

		///////////
		// \brief Sets the color
		//
		void SetColor(const math::Vector4 a_color);

		///////////
		// \brief Sets the render order member
		//
		void SetRenderOrder(const int a_renderOrder);

		// Getters

		// brief Returns a vector copy of the color
		math::Vector4 GetColor();

		// brief Returns a pointer to the transform of the renderable
		ecs::Transform *GetTransformComponent();

		// brief Returns a pointer to the transform of the renderable
		opengl::Texture *GetTexture();

		int GetRenderOrder() const;

		///////////
		// \brief Returns the number of vertices for renderable 
		// \brief 3 - triangle, 4 - quad
		virtual int GetVertexCount();
	};

} } 