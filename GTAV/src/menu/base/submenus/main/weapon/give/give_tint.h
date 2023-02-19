#pragma once
#include "menu/base/submenu.h"

class give_tint_menu : public menu::submenu::submenu {
public:
	static give_tint_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	give_tint_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::give::tint::vars {
	std::vector<std::pair<std::string, int>> get_tints(int weapon);
}