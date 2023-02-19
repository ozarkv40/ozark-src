#pragma once
#include "menu/base/submenu.h"

class entity_gun_menu : public menu::submenu::submenu {
public:
	static entity_gun_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	entity_gun_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::entity::gun::vars {
	struct variables {
		int m_type = 0;
		int m_wait = 0;
		int m_object = 0;
		int m_vehicle = 0;
		int m_ped = 0;
		float m_speed = 900.f;

		bool m_toggle = false;
	};
	
	extern scroll_struct<uint32_t> objects[100];
	extern scroll_struct<uint32_t> vehicles[100];
	extern scroll_struct<uint32_t> peds[100];
	extern variables m_vars;
}