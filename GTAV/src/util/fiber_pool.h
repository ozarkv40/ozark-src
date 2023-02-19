#pragma once
#include "stdafx.h"
#include <queue>
#include <functional>

namespace util::fiber::pool {
	class fiber_pool {
	public:
		void load();
		void update(std::function<void()>& function);
		void add(std::function<void()> function);
	private:
		std::queue<std::function<void()>> m_jobs;
	};

	fiber_pool* get_fiber_pool();

	inline void load() {
		get_fiber_pool()->load();
	}

	inline void add(std::function<void()> function) {
		get_fiber_pool()->add(function);
	}
}