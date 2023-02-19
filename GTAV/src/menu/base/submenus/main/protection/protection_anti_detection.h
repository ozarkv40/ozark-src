#pragma once
#include "menu/base/submenu.h"

class protection_anti_detection_menu : public menu::submenu::submenu {
public:
	static protection_anti_detection_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_anti_detection_menu()
		: menu::submenu::submenu() {}
};

namespace protection::detection::vars {
	struct variables {
		bool m_godmode = true;
		bool m_super_jump = true;
		bool m_health = true;
		bool m_armor = true;
		bool m_spectate = true;
	};

	extern variables m_vars;
}