#pragma once
#include "menu/base/submenu.h"

class translation_selected_menu : public menu::submenu::submenu {
public:
	static translation_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	translation_selected_menu()
		: menu::submenu::submenu() {}
};

namespace settings::translation::selected::vars {
	struct variables {
		std::size_t m_selected;
	};

	extern variables m_vars;
}