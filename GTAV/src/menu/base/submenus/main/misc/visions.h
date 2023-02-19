#pragma once
#include "menu/base/submenu.h"

class visions_menu : public menu::submenu::submenu {
public:
	static visions_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	visions_menu()
		: menu::submenu::submenu() {}
};

namespace misc::visions::vars {
	struct variables {
		bool m_thermal_vision;
		uint8_t m_backup[5];

		radio_context m_context = { "commonmenu", "shop_mask_icon" };
	};

	extern variables m_vars;
}