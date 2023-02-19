#pragma once
#include "stdafx.h"

namespace util::wmi {
	bool load();
	std::string read(std::string part, std::string property);
	void cleanup();
}