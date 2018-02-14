#include"../include/ecs/components/FourwayMoveComponent.h"


namespace nano { namespace ecs {

	ecs::FourwayMoveComponent::FourwayMoveComponent(float a_velocity, int a_keys[4])
	{
		m_velocity = a_velocity;
		//(*m_keys) = *a_keys;
		m_keys[0] = a_keys[0];
		m_keys[1] = a_keys[1];
		m_keys[2] = a_keys[2];
		m_keys[3] = a_keys[3];
	}

	void ecs::FourwayMoveComponent::Start()
	{

	}

	void ecs::FourwayMoveComponent::Update()
	{

	}

	int FourwayMoveComponent::GetKey(const char * a_key)
	{
		if (a_key == "up") {
			return m_keys[0];
		}
		else if (a_key == "right") {
			return m_keys[1];
		}
		else if (a_key == "down") {
			return m_keys[2];
		}
		else if (a_key == "left") {
			return m_keys[3];
		}
		else {
			return -1;
		}
	}

	void FourwayMoveComponent::SetKey(const char * a_key, int a_keyCode)
	{
		if (a_key == "up") {
			m_keys[0] = a_keyCode;
		}
		else if (a_key == "right") {
			m_keys[1] = a_keyCode;
		}
		else if (a_key == "down") {
			m_keys[2] = a_keyCode;
		}
		else if (a_key == "left") {
			m_keys[3] = a_keyCode;
		}
	}

	void FourwayMoveComponent::SetKeys(int a_keys[4])
	{
		m_keys[0] = a_keys[0];
		m_keys[1] = a_keys[1];
		m_keys[2] = a_keys[2];
		m_keys[3] = a_keys[3];
	}

} }