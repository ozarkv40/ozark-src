#pragma once
#include "stdafx.h"

namespace util::va {
	const char* va(const char* fmt, ...);
	const char* vap(char* buffer, const char* fmt, ...);
	const wchar_t* vaw(const char* fmt, ...);
	void cleanup();
}