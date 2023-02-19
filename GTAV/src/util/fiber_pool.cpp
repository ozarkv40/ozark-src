#include "fiber_pool.h"
#include "fiber.h"

namespace util::fiber::pool {
	void fiber_pool::load() {
		static std::function<void()> job1;
		static std::function<void()> job2;
		static std::function<void()> job3;
		static std::function<void()> job4;
		static std::function<void()> job5;
		static std::function<void()> job6;
		static std::function<void()> job7;
		static std::function<void()> job8;

		util::fiber::add("F_JOB1", [] { get_fiber_pool()->update(job1); });
		util::fiber::add("F_JOB2", [] { get_fiber_pool()->update(job2); });
		util::fiber::add("F_JOB3", [] { get_fiber_pool()->update(job3); });
		util::fiber::add("F_JOB4", [] { get_fiber_pool()->update(job4); });
		util::fiber::add("F_JOB5", [] { get_fiber_pool()->update(job5); });
		util::fiber::add("F_JOB6", [] { get_fiber_pool()->update(job6); });
		util::fiber::add("F_JOB7", [] { get_fiber_pool()->update(job7); });
		util::fiber::add("F_JOB8", [] { get_fiber_pool()->update(job8); });
	}

	void fiber_pool::update(std::function<void()>& function) {
		if (m_jobs.empty()) return;
		function = m_jobs.front();
		m_jobs.pop();
		function();
	}

	void fiber_pool::add(std::function<void()> function) {
		if (m_jobs.size() >= 200)
			return;

		m_jobs.emplace(function);
	}

	fiber_pool* get_fiber_pool() {
		static fiber_pool instance;
		return &instance;
	}
}