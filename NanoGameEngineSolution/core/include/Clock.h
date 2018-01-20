#pragma once

#include<ctime>

namespace nano {

	// Class taken from SudoGameEngine
	// Measures time in milliseconds
	class Clock {
	private:
		clock_t m_startedAt, m_pausedAt;
		bool m_paused, m_started;

	public:
		Clock();

		// Getters
		bool IsStarted();
		bool IsStopped();
		bool IsPaused();
		bool IsActive();
		clock_t GetTicks(); 

		// State modifications
		void Pause();
		void Resume();
		void Stop();
		void Start();
		void Reset();

	};

}