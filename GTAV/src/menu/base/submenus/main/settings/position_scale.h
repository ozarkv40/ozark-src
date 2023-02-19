#pragma once
#include "menu/base/submenu.h"

class position_scale_menu : public menu::submenu::submenu {
public:
	static position_scale_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	position_scale_menu()
		: position_scale_menu::submenu::submenu() {}
};

namespace settings::pos::vars {
	extern scroll_struct<math::vector2<float>*> scales[10];
}