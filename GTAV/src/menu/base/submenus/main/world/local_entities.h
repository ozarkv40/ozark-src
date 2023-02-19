#pragma once
#include "menu/base/submenu.h"
#include "../helper/helper_esp.h"

class local_entities_menu : public menu::submenu::submenu {
public:
	static local_entities_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	local_entities_menu()
		: menu::submenu::submenu() {}
};

namespace world::local::vars {
	struct variables {
		int m_type;

		int m_driver;
		int m_boost;
		int m_acrobatics;
		int m_gravity;
		int m_teleport;

		helper::esp::vars::esp_context m_vehicle_esp;
		helper::esp::vars::esp_context m_object_esp;
		helper::esp::vars::esp_context m_ped_esp;
	};

	extern variables m_vars;
}