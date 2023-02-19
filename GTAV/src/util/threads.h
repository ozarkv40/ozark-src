#pragma once
#include "stdafx.h"
#include <functional>

namespace util::threads {
	struct thread_context {
		const char* m_name = "";
		HANDLE m_handle = 0;
		bool m_running = true;
		void* m_argument = nullptr;
		std::function<void(void*)> m_callback = {};
	};
	
	class threads {
	public:
		void add_job(std::function<void(void*)> callback, void* argument = nullptr);
		void add_thread(const char* name, std::function<void(void*)> callback, void* argument = nullptr);
		void remove_thread(const char* name);
		void cleanup();
	private:
		std::vector<thread_context*> m_threads;
	};

	threads* get_threads();

	inline void add_job(std::function<void(void*)> callback, void* argument = nullptr) {
		get_threads()->add_job(callback, argument);
	}

	inline void add_thread(const char* name, std::function<void(void*)> callback, void* argument = nullptr) {
		get_threads()->add_thread(name, callback, argument);
	}

	inline void remove_thread(const char* name) {
		get_threads()->remove_thread(name);
	}

	inline void cleanup() {
		get_threads()->cleanup();
	}
}