#pragma once

#include"../math/Vector2.h"
#include"../math/Vector4.h"

#include"../ecs/components/TransformComponent.h"

namespace nano { namespace graphics { 

	// Base class for every renderable component (rectangle, triangle, sprite... etc)
	class Renderable {
	protected:
		// Renderable shared data
		math::Vector2 m_size;
		math::Vector4 m_color;
		ecs::Transform* m_transform;

		int m_vertexCount;

	public:
		// Default constructor
		Renderable();

		// Constructor w/in arguments
		Renderable(const math::Vector2& a_size, const math::Vector4& a_color);

		// Setters

		///////////
		// \brief Sets the size
		//
		void SetSize(const math::Vector2 a_size);

		///////////
		// \brief Sets the color
		//
		void SetColor(const math::Vector4 a_color);

		// Getters

		///////////
		// \brief Returns a vector copy of the size
		//
		math::Vector2 GetSize();

		///////////
		// \brief Returns a vector copy of the color
		//
		math::Vector4 GetColor();

		///////////
		// \brief Returns a pointer to the transform of the renderable
		//
		ecs::Transform *GetTransformComponent();

		///////////
		// \brief Returns the number of vertices for renderable 
		// \brief 3 - triangle, 4 - quad
		virtual int GetVertexCount();
	};

} } 