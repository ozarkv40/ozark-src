#pragma once
#include "stdafx.h"
#include "global/vars.h"

namespace menu {
	class script_global {
	public:
		script_global(int index)
			: m_handle(&global::vars::g_global_cache[index >> 18 & 0x3F][index & 0x3FFFF])
		{}

		script_global(void* ptr)
			: m_handle(ptr)
		{}

		script_global at(int index) const {
			return script_global((void**)(m_handle) + index);
		}

		script_global at(int index, int size) const {
			return at(1 + (index * size));
		}

		template<typename T>
		T* get() {
			return (T*)(m_handle);
		}

		template<typename T>
		T& as() {
			return *get<T>();
		}

	private:
		void* m_handle;
	};
}