#pragma once
#include "menu/base/submenu.h"

class spawner_vehicle_modded_menu : public menu::submenu::submenu {
public:
	static spawner_vehicle_modded_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_vehicle_modded_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vehicle::modded::vars {
	struct variables {
		bool m_delete_current;
		bool m_use_collision;

		Entity m_vehicle_handle;
		Entity m_initial_handle;

		std::vector<Entity> m_spawned_vehicles;
		std::vector<Entity> m_spawned_attachments;
	};

	extern variables m_vars;
}