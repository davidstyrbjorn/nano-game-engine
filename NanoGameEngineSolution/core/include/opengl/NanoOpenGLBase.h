#pragma once

namespace nano { namespace opengl {

	class OpenGLBase {
	public:
		//virtual ~OpenGLBase() { }

		////////////
		// \brief Pure virtual method for binding opengl object
		//
		virtual void Bind() = 0;

		////////////
		// \brief Pure virtual method for unbinding opengl object
		//
		virtual void Unbind() = 0;
	};

} }