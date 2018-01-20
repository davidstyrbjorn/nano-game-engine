#include"../include/Clock.h"

namespace nano {

	Clock::Clock() {
		m_startedAt = 0;
		m_pausedAt = 0;
		m_paused = false;
		m_started = false;
	}

	bool Clock::IsStarted() {
		return m_started;
	}

	bool Clock::IsStopped() {
		return !m_started;
	}

	bool Clock::IsPaused() {
		return m_paused;
	}

	bool Clock::IsActive() {
		return !m_paused & m_started;
	}

	void Clock::Pause() {
		if (m_paused || !m_started)
			return;

		m_paused = true;
		m_pausedAt = clock();
	}

	void Clock::Resume() {
		if (!m_paused)
			return;

		m_paused = false;
		m_startedAt = clock() - m_pausedAt;
	}

	void Clock::Stop() {
		m_started = false;
	}

	void Clock::Start() {
		if (m_started)
			return;

		m_started = true;
		m_paused = false;
		m_startedAt = clock();
	}

	void Clock::Reset() {
		m_paused = false;
		m_startedAt = clock();
	}

	clock_t Clock::GetTicks()
	{
		if (!m_started)
			return 0;
		if (m_paused)
			return m_pausedAt - m_startedAt;
		return clock() - m_startedAt;
	}

}