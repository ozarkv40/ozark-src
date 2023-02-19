#pragma once
#include "menu/base/submenu.h"

class ocean_quads_menu : public menu::submenu::submenu {
public:
	static ocean_quads_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ocean_quads_menu()
		: menu::submenu::submenu() {}
};

namespace world::ocean::quads::vars {
	struct variables {
		int m_type;
		uint64_t m_closest_quad;
	};

	void quad_esp();
	extern variables m_vars;
}