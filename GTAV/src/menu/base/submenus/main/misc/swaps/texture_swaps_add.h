#pragma once
#include "menu/base/submenu.h"

class texture_swaps_add_menu : public menu::submenu::submenu {
public:
	static texture_swaps_add_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	texture_swaps_add_menu()
		: menu::submenu::submenu() {}
};

namespace misc::swaps::texture::add::vars {
	struct variables {
		int m_image;
		std::pair<std::string, std::string> m_asset;
		std::vector<std::shared_ptr<base_option>> m_options;
	};

	extern variables m_vars;
}