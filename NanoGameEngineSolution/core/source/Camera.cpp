#include "../include/graphics/Camera.h"

namespace nano { namespace graphics { 

	OrthographicCamera::OrthographicCamera()
	{
		m_translation = math::Vector2(0, 0);
		this->UpdateMatrix();
	}

	void OrthographicCamera::UpdateMatrix()
	{
		m_viewMatrix = math::Matrix4x4::Translation(math::Vector3(-m_translation.x, -m_translation.y, 0));
	}

	void OrthographicCamera::Translate(const math::Vector2 & a_translationVector)
	{
		m_translation += (a_translationVector);
		this->UpdateMatrix();
	}

	void OrthographicCamera::SetPosition(const math::Vector2 & a_positionVector)
	{
		m_translation = a_positionVector;
		this->UpdateMatrix();
	}

	math::Matrix4x4 OrthographicCamera::GetViewMatrix()
	{
		return m_viewMatrix;
	}

	math::Vector2 OrthographicCamera::GetPosition()
	{
		return m_translation;
	}

} } 