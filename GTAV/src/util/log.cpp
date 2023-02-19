#include "log.h"
#include "util/dirs.h"
#include <unordered_map>
#include <filesystem>
#include <fstream>

namespace util::log {
	std::unordered_map<uint32_t, char*> g_log_storage;

	void load() {
		AllocConsole();
		SetConsoleTitleA(XOR("Ozark | ozark.gg"));

		FILE* stream;
		freopen_s(&stream, XOR("CONIN$"), XOR("w"), stdin);
		freopen_s(&stream, XOR("CONOUT$"), XOR("w"), stdout);
		freopen_s(&stream, XOR("CONOUT$"), XOR("w"), stderr);

		SMALL_RECT rect;
		rect.Left = 0;
		rect.Top = 0;
		rect.Right = 150;
		rect.Bottom = 50;
		SetConsoleWindowInfo(GetStdHandle(-11), TRUE, &rect);

		std::ofstream output(util::dirs::get_path(log));
		output.close();
	}

	void set_color(int color) {
		SetConsoleTextAttribute(GetStdHandle(-11), color);
	}

	void print(int color, const char* tag, const char* fmt, ...) {
		if (g_log_storage.find(GetCurrentThreadId()) == end(g_log_storage)) {
			g_log_storage[GetCurrentThreadId()] = new char[0x1000];
		}

		char* buffer = g_log_storage[GetCurrentThreadId()];
		memset(buffer, 0, 0x1000);

		va_list va_l;
		va_start(va_l, fmt);
		vsprintf(buffer, fmt, va_l);
		va_end(va_l);

		set_color(color);
		if (!tag || strlen(tag) <= 0) printf("%s\n", buffer);
		else printf("%s | %s\n", tag, buffer);

		set_color(foreground::WHITE);

		time_t raw_time;
		time(&raw_time);

		tm time;
		localtime_s(&time, &raw_time);

		char time_string[128];
		strftime(time_string, 128, "%a %b %d %T %Y", &time);

		char print_buffer[0x1000];
		if (!tag || strlen(tag) <= 0) sprintf_s(print_buffer, "[%s] %s\n", time_string, buffer);
		else sprintf_s(print_buffer, "[%s] %s | %s\n", time_string, tag, buffer);

		std::ofstream output(util::dirs::get_path(log), std::ios::app);
		if (output.good()) {
			output << print_buffer;
			output.close();
		}
	}

	void cleanup() {
		for (std::pair<uint32_t, char*> ptr : g_log_storage) {
			delete[] ptr.second;
		}
	}
}