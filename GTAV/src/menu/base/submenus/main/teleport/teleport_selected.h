#pragma once
#include "menu/base/submenu.h"

class teleport_selected_menu : public menu::submenu::submenu {
public:
	static teleport_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_selected_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::selected::vars {
	struct variables {
		scroll_struct<math::vector3<float>>* m_selected;
		int m_size;
	};

	extern variables m_vars;
}