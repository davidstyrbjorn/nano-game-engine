#include"../include/components/FourwayMoveComponentEngine.h"

#include"../include/InputSystem.h"

namespace nano { namespace engine {  

	FourwayMoveComponentEngine::FourwayMoveComponentEngine(float a_velocity, int a_keys[4])
	{
		m_velocity = a_velocity;
		m_keys[0] = a_keys[0];
		m_keys[1] = a_keys[1];
		m_keys[2] = a_keys[2];
		m_keys[3] = a_keys[3];
	}

	FourwayMoveComponentEngine::FourwayMoveComponentEngine()
	{
		m_velocity = 0;
		m_keys[0] = 0;
		m_keys[1] = 0;
		m_keys[2] = 0;
		m_keys[3] = 0;
	}

	void FourwayMoveComponentEngine::Start()
	{

	}

	void FourwayMoveComponentEngine::Update()
	{
		static InputSystem* i = InputSystem::getInstance();
		for (InputEvent event : i->getPolledEvents()) {
			if (event.type == INPUT_TYPE::KEY_PRESSED) {
				//std::cout << "dundundundun" << std::endl;
			}
		}
	}

	int FourwayMoveComponentEngine::GetKey(const char * a_key)
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

	void FourwayMoveComponentEngine::SetKey(const char * a_key, int a_keyCode)
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

	void FourwayMoveComponentEngine::SetKeys(int a_keys[4])
	{
		m_keys[0] = a_keys[0];
		m_keys[1] = a_keys[1];
		m_keys[2] = a_keys[2];
		m_keys[3] = a_keys[3];
	}

} }