#pragma once

#include"../math/Matrix4x4.h"
#include"../math/Vector2.h"
#include"../math/Vector3.h"

namespace nano { namespace graphics {

	class OrthographicCamera {
	public:
		// Default Constructor
		OrthographicCamera();

		// Destructor
		~OrthographicCamera() { }

	private:
		// Camera data
		math::Matrix4x4 m_viewMatrix;
		math::Vector2 m_translation;

	public:
		// Updates the m_viewMatrix with m_translation vector
		void UpdateMatrix();

		// Translates the camera's position
		void Translate(const math::Vector2 &a_translationVector);
		// Sets the camera's position
		void SetPosition(const math::Vector2 &a_positionVector);

		// Getters
		math::Matrix4x4 GetViewMatrix();
		math::Vector2 GetPosition();
	};
	
}}