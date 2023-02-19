#include "timers.h"
#include "rage/invoker/natives.h"

namespace menu::timers {
	void run_timed(int* timer, int ms, std::function<void()> callback) {
		if (*timer < native::get_game_timer()) {
			*timer = native::get_game_timer() + ms;
			callback();
		}
	}

	void timer::start(unsigned long long ticks) {
		if (m_tick) {
			m_ready_at = GetTickCount64() + ticks;
			m_tick = false;
		}
	}

	bool timer::is_ready() {
		return GetTickCount64() > m_ready_at;
	}

	void timer::reset() {
		m_tick = true;
	}
}