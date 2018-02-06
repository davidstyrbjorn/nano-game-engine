#include "../include/graphics/Camera.h"

namespace nano { namespace graphics { 

	OrthographicCamera::OrthographicCamera(const math::Vector2& a_windowSize)
	{
		m_cameraSize = a_windowSize;
		m_position = math::Vector2(0, 0);
		this->UpdateViewMatrix();
		this->UpdateProjectionMatrix();
	}

	void OrthographicCamera::UpdateViewMatrix()
	{
		m_viewMatrix = math::Matrix4x4::Translation(math::Vector3(-m_position.x, -m_position.y, 0));
	}

	void OrthographicCamera::UpdateProjectionMatrix()
	{
		m_projectionMatrix = math::Matrix4x4::Orthographic(0, m_cameraSize.x, m_cameraSize.y, 0, -1, 1);
	}

	///////////////////////
	// Setters
	///////////////////////

	void OrthographicCamera::Translate(const math::Vector2 & a_translationVector)
	{
		m_position += (a_translationVector);
		this->UpdateViewMatrix();
	}

	void OrthographicCamera::SetPosition(const math::Vector2 & a_positionVector)
	{
		m_position = a_positionVector;
		this->UpdateViewMatrix();
	}

	void OrthographicCamera::SetSize(const math::Vector2 & a_cameraSize)
	{
		m_cameraSize = a_cameraSize;
		this->UpdateProjectionMatrix();
	}

	///////////////////////
	// Getters
	///////////////////////
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

	math::Vector2 OrthographicCamera::GetSize()
	{
		return m_cameraSize;
	}

} } 