#pragma once
#include "menu/base/submenu.h"

class spawner_object_select_menu: public menu::submenu::submenu {
public:
	static spawner_object_select_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_object_select_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::object::select::vars {
	struct variables {
		scroll_struct<uint32_t>* m_list;
		int m_size;
	};

	extern variables m_vars;
}