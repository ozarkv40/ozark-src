#pragma once
#include "menu/base/submenu.h"

class triggerbot_menu : public menu::submenu::submenu {
public:
	static triggerbot_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	triggerbot_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::triggerbot::vars {
	struct variables {
		bool m_enable;
		int m_delay = 100;
		int m_aim_tag;
		int m_aim_entity;
	};

	extern variables m_vars;
}