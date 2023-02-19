#pragma once
#include "menu/base/submenu.h"

class position_scale_selected_menu : public menu::submenu::submenu {
public:
	static position_scale_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	position_scale_selected_menu()
		: menu::submenu::submenu() {}
};

namespace settings::pos::selected::vars {
	struct variables {
		math::vector2<float>* m_selected;
	};

	extern variables m_vars;
}