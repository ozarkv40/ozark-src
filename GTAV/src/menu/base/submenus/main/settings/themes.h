#pragma once
#include "menu/base/submenu.h"

class themes_menu : public menu::submenu::submenu {
public:
	static themes_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	themes_menu()
		: menu::submenu::submenu() {}
};

namespace settings::theme::vars {
	struct variables {
		std::vector<std::string> m_cached_themes;
	};

	extern variables m_vars;
}