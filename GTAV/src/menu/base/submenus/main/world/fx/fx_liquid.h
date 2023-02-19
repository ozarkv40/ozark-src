#pragma once
#include "menu/base/submenu.h"

class fx_liquid_menu : public menu::submenu::submenu {
public:
	static fx_liquid_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_liquid_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::liquid::vars {
	enum eLiquid {
		LIQUID_PUDDLE,
		LIQUID_BLOOD,
		LIQUID_OIL,
		LIQUID_PETROL,
		LIQUID_MUD
	};

	struct variables {
		int m_selected;
		rage::types::vfx_liquid m_backup[5];
		color_rgba m_color;
	};

	extern variables m_vars;
}