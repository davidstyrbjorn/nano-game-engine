#include "../include/graphics/Camera.h"

namespace nano { namespace graphics { 

	OrthographicCamera::OrthographicCamera(const math::Vector2& a_windowSize)
	{
		m_projectionMatrix = math::Matrix4x4::Orthographic(0, a_windowSize.x, a_windowSize.y, 0, -1, 1);
		m_position = math::Vector2(0, 0);
		this->UpdateMatrix();
	}

	void OrthographicCamera::UpdateMatrix()
	{
		m_viewMatrix = math::Matrix4x4::Translation(math::Vector3(-m_position.x, -m_position.y, 0));
	}

	void OrthographicCamera::Translate(const math::Vector2 & a_translationVector)
	{
		m_position += (a_translationVector);
		this->UpdateMatrix();
	}

	void OrthographicCamera::SetPosition(const math::Vector2 & a_positionVector)
	{
		m_position = a_positionVector;
		this->UpdateMatrix();
	}

	math::Matrix4x4 OrthographicCamera::GetViewMatrix()
	{
		return m_viewMatrix;
	}

	math::Matrix4x4 OrthographicCamera::GetProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	math::Vector2 OrthographicCamera::GetPosition()
	{
		return m_position;
	}

} } 