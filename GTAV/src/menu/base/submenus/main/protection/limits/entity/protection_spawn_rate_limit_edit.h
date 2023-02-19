#pragma once
#include "menu/base/submenu.h"

class protection_spawn_rate_limit_edit_menu : public menu::submenu::submenu {
public:
	static protection_spawn_rate_limit_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_spawn_rate_limit_edit_menu()
		: menu::submenu::submenu() {}
};

namespace protection::limits::spawn::edit::vars {
	struct variables {
		std::size_t m_selected;
	};

	extern variables m_vars;
}