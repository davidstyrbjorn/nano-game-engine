#pragma once

#include"Component.h"

#include"../math/Vector2.h"
#include"../math/Vector4.h"

#include"../opengl/Texture.h"

namespace nano { namespace ecs {

	class RenderableComponent : public Component {
	protected:
		// Renderable daa
		math::Vector4 m_Color = math::Vector4(1, 1, 1, 1);
		opengl::Texture *m_Texture;

	public:
		// Virtual destructor
		virtual ~RenderableComponent();

		// Setters
		void setColor(const math::Vector4 a_Color);
		// Gets color
		math::Vector4 getColor();
		// Returns the texture attatched to the renderable 
		opengl::Texture* getTexture();
		// Returns the vertex count for renderable
		virtual int getVertexCount() const { return -1; }
	};

} }