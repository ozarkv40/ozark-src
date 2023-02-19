#pragma once
#include "menu/base/submenu.h"

class explosion_editor_menu : public menu::submenu::submenu {
public:
	static explosion_editor_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	explosion_editor_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::explosion::editor::vars {
	struct variables {
		int m_selected_explosion = 0;
		int m_selected_fx = 0;

		rage::types::explosion_data m_explosion_data;
		rage::types::explosion_fx m_explosion_fx;

		rage::types::explosion_data* m_explosion_data_ptr;
		rage::types::explosion_fx* m_explosion_fx_ptr;
	};

	extern variables m_vars;
}