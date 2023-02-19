#pragma once
#include "menu/base/submenu.h"

class hotkey_selected_menu : public menu::submenu::submenu {
public:
	static hotkey_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	hotkey_selected_menu()
		: menu::submenu::submenu() {}
};

namespace settings::hotkey::vars {
	struct variables {
		void* m_hotkey;
		int m_event = 0;
	};

	extern variables m_vars;
}