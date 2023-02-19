#pragma once
#include "menu/base/submenu.h"

class texture_swaps_menu : public menu::submenu::submenu {
public:
	static texture_swaps_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	texture_swaps_menu()
		: menu::submenu::submenu() {}
};

namespace misc::swaps::texture::vars {
	struct texture_swap {
		std::pair<std::string, std::string> m_asset = {};
		std::string m_texture = "";
		bool m_toggled = false;
		bool m_initialized = false;
		rage::types::grc_texture_dx11 m_original;
	};

	struct variables {
		std::vector<texture_swap*> m_swaps;
	};

	void add_json(texture_swap* swap);
	bool add_swap(texture_swap* swap);
	extern variables m_vars;
}