#include "fiber.h"
#include "global/vars.h"
#include <timeapi.h>

namespace util::fiber {
	void fiber_manager::load() {
		if (m_loaded) return;
		m_loaded = true;

		ConvertThreadToFiber(nullptr);
		m_main_fiber = GetCurrentFiber();
	}

	void fiber_manager::update() {
		if (!m_loaded || !m_current) return;

		for (fiber_context& fiber : m_fibers) {
			if (fiber.m_running) {
				if (timeGetTime() >= fiber.m_wake_time) {
					SwitchToFiber(fiber.m_handle);
				}
			}
		}

		m_current = m_current->m_next;
	}

	void fiber_manager::add(std::string name, std::function<void()> function) {
		struct Arguments {
			std::function<void()> m_function;
			void* m_main;
		};

		Arguments* arguments = new Arguments();
		arguments->m_function = function;
		arguments->m_main = m_main_fiber;

		void* fiber_handle = CreateFiber(0, [](void* param) {
			Arguments* arguments = (Arguments*)param;
			while (!global::vars::g_unloading) {
				arguments->m_function();
				SwitchToFiber(arguments->m_main);
			}

			delete[] arguments;
		}, arguments);

		m_fibers.push_back({ nullptr, fiber_handle, timeGetTime(), true, name });

		for (auto fiber = m_fibers.begin(); fiber != m_fibers.end(); ++fiber) {
			auto next = fiber + 1;
			if (next != m_fibers.end()) fiber->m_next = &*next;
			else fiber->m_next = &m_fibers.front();
		}

		m_current = &m_fibers.front();
	}

	void fiber_manager::sleep(uint32_t time) {
		auto vit = std::find_if(begin(m_fibers), end(m_fibers), [](fiber_context& fiber) { return fiber.m_handle == GetCurrentFiber(); });
		if (vit != end(m_fibers)) {
			vit->m_wake_time = timeGetTime() + time;
			SwitchToFiber(m_main_fiber);
		}
	}

	void fiber_manager::go_to_main() {
		SwitchToFiber(m_main_fiber);
	}

	void fiber_manager::cleanup() {
		for (fiber_context& fiber : m_fibers) {
			fiber.m_running = false;
			DeleteFiber(fiber.m_handle);
		}
	}

	fiber_manager* get_fiber_manager() {
		static fiber_manager instance;
		return &instance;
	}

	fiber_manager* get_fiber_manager_shv() {
		static fiber_manager instance;
		return &instance;
	}
}