#pragma once
#include "menu/base/submenu.h"
#include "../../../helper/helper_esp.h"

class spawner_vehicle_manage_edit_menu : public menu::submenu::submenu {
public:
	static spawner_vehicle_manage_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_vehicle_manage_edit_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vehicle::manage::edit::vars {
	struct variables {
		bool m_editing_all = false;
		std::size_t m_selected;

		int m_driver;
		int m_boost;
		int m_acrobatics;
		int m_gravity;
		int m_teleport;

		helper::esp::vars::esp_context* m_esp;
	};

	extern variables m_vars;
	void run(int index, bool editing_all = m_vars.m_editing_all, bool editing_pool = false, int* var = nullptr, Entity entity = 0);
}