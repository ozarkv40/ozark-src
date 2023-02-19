#include "threads.h"
#include "global/vars.h"

namespace util::threads {
	void threads::add_job(std::function<void(void*)> callback, void* argument) {
		struct thread_job {
			void* m_argument;
			std::function<void(void*)> m_callback;
		};

		thread_job* job = new thread_job();
		job->m_callback = callback;
		job->m_argument = argument;

		CreateThread(0, 0, [](void* argument) -> DWORD {
			thread_job* job = (thread_job*)argument;
			job->m_callback(job->m_argument);
			delete job;
			return 0;
		}, job, 0, 0);
	}

	void threads::add_thread(const char* name, std::function<void(void*)> callback, void* argument) {
		thread_context* thread = new thread_context();
		thread->m_name = name;
		thread->m_callback = callback;
		thread->m_argument = argument;
		thread->m_running = true;

		thread->m_handle = CreateThread(0, 0, [](void* argument) -> DWORD {
			thread_context* thread = (thread_context*)argument;

			while (thread && !global::vars::g_unloading) {
				if (!thread->m_running) {
					break;
				}

				if (thread->m_callback) {
					thread->m_callback(thread->m_argument);
				}
			}

			if (thread) delete thread;
			return 0;
		}, thread, 0, 0);

		m_threads.push_back(thread);
	}

	void threads::remove_thread(const char* name) {
		for (thread_context* thread : m_threads) {
			if (!strcmp(thread->m_name, name)) {
				thread->m_running = false;
			}
		}
	}

	void threads::cleanup() {
		for (thread_context* thread : m_threads) {
			thread->m_running = false;
			TerminateThread(thread->m_handle, 0);
		}
	}

	threads* get_threads() {
		static threads instance;
		return &instance;
	}
}