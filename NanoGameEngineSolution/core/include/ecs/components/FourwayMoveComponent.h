#pragma once

#include"../Component.h"

namespace nano { namespace ecs {  

	class FourwayMoveComponent : public Component
	{
	private:
		float m_velocity;
		int m_keys[4]; // up, right, down, left

	public:
		// Default constructor
		FourwayMoveComponent(float a_velocity, int a_keys[4]);
		FourwayMoveComponent();

		// Component base methods
		void Start() override;
		virtual void Update() override;

		// Member methods
		float GetVelocity() { return m_velocity; }
		void SetVelocity(float a_velocity) { m_velocity = a_velocity; }
		int GetKey(const char* a_key);
		void SetKey(const char* a_key, int a_keyCode);
		void SetKeys(int a_keys[4]);
	};

} }