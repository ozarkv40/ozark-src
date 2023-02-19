#pragma once
#include "menu/base/submenu.h"

class fx_puddles_menu : public menu::submenu::submenu {
public:
	static fx_puddles_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_puddles_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::puddles::vars {
	struct variables {
		rage::types::ui_puddle m_original;
		rage::types::ui_puddle_ripple m_original_ripple;
	};

	extern variables m_vars;
}