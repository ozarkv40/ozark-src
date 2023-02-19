#pragma once
#include "stdafx.h"

#define LOG(fmt, ...) util::log::print(util::log::foreground::GRAY, "", fmt, ##__VA_ARGS__);
#define LOG_WARN(fmt, ...) util::log::print(util::log::foreground::DARKYELLOW, "Warning", fmt, ##__VA_ARGS__);
#define LOG_ERROR(fmt, ...) util::log::print(util::log::foreground::RED, "Error", fmt, ##__VA_ARGS__);
#define LOG_SUCCESS(fmt, ...) util::log::print(util::log::foreground::GREEN, "Success", fmt, ##__VA_ARGS__);

#define LOG_CUSTOM(tag, fmt, ...) util::log::print(util::log::foreground::GRAY, tag, fmt, ##__VA_ARGS__);
#define LOG_CUSTOM_WARN(tag, fmt, ...) util::log::print(util::log::foreground::DARKYELLOW, tag, fmt, ##__VA_ARGS__);
#define LOG_CUSTOM_ERROR(tag, fmt, ...) util::log::print(util::log::foreground::RED, tag, fmt, ##__VA_ARGS__);
#define LOG_CUSTOM_SUCCESS(tag, fmt, ...) util::log::print(util::log::foreground::GREEN, tag, fmt, ##__VA_ARGS__);

#ifdef DEV_MODE
#define LOG_DEV(fmt, ...) util::log::print(util::log::foreground::BLUE, "Dev", fmt, ##__VA_ARGS__);
#define LOG_CUSTOM_DEV(tag, fmt, ...) util::log::print(util::log::foreground::GRAY, tag, fmt, ##__VA_ARGS__);
#else
#define LOG_DEV(fmt, ...);
#define LOG_CUSTOM_DEV(tag, fmt, ...);
#endif

namespace util::log {
	namespace foreground {
		enum {
			BLACK = 0,
			DARKBLUE = FOREGROUND_BLUE,
			DARKGREEN = FOREGROUND_GREEN,
			DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
			DARKRED = FOREGROUND_RED,
			DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
			DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
			DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			GRAY = FOREGROUND_INTENSITY,
			BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
			GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
			CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
			RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
			MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
			YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
			WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		};
	};

	namespace background {
		enum {
			BLACK = 0,
			DARKBLUE = BACKGROUND_BLUE,
			DARKGREEN = BACKGROUND_GREEN,
			DARKCYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
			DARKRED = BACKGROUND_RED,
			DARKMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
			DARKYELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
			DARKGRAY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
			GRAY = BACKGROUND_INTENSITY,
			BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
			GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
			CYAN = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
			RED = BACKGROUND_INTENSITY | BACKGROUND_RED,
			MAGENTA = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
			YELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
			WHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		};
	};

	void load();
	void print(int color, const char* tag, const char* fmt, ...);
	void cleanup();
}