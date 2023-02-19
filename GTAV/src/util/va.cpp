#include "va.h"
#include <unordered_map>

namespace util::va {
	std::unordered_map<uint32_t, char*> g_va_storage;
	std::unordered_map<uint32_t, std::pair<wchar_t*, char*>> g_vaw_storage;

	const char* va(const char* fmt, ...) {
		if (g_va_storage.find(GetCurrentThreadId()) == end(g_va_storage)) {
			g_va_storage[GetCurrentThreadId()] = new char[0x300];
		}

		char* buffer = g_va_storage[GetCurrentThreadId()];
		memset(buffer, 0, 0x300);

		va_list va_l;
		va_start(va_l, fmt);
		vsnprintf(buffer, 0x300, fmt, va_l);
		va_end(va_l);

		return buffer;
	}

	const char* vap(char* buffer, const char* fmt, ...) {
		va_list va_l;
		va_start(va_l, fmt);
		vsprintf(buffer, fmt, va_l);
		va_end(va_l);
		return buffer;
	}

	const wchar_t* vaw(const char* fmt, ...) {
		if (g_vaw_storage.find(GetCurrentThreadId()) == end(g_vaw_storage)) {
			g_vaw_storage[GetCurrentThreadId()] = { new wchar_t[0x300], new char[0x300] };
		}

		wchar_t* message = g_vaw_storage[GetCurrentThreadId()].first;
		memset(message, 0, 0x300);

		char* buffer = g_vaw_storage[GetCurrentThreadId()].second;
		memset(buffer, 0, 0x300);

		va_list va_l;
		va_start(va_l, fmt);
		vsnprintf(buffer, 0x300, fmt, va_l);
		va_end(va_l);

		mbstowcs(message, buffer, strlen(buffer) + 1);
		return message;
	}

	void cleanup() {
		for (std::pair<uint32_t, char*> ptr : g_va_storage) {
			delete[] ptr.second;
		}

		for (std::pair<uint32_t, std::pair<wchar_t*, char*>> ptr : g_vaw_storage) {
			delete[] ptr.second.first;
			delete[] ptr.second.second;
		}
	}
}