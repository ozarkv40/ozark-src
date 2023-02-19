#pragma once
#include "menu/base/submenu.h"

class teleport_menu : public menu::submenu::submenu {
public:
	static teleport_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::vars {
	struct variables {
		bool m_transition;
		bool m_auto_waypoint;
		bool m_include_current_vehicle = true;
		bool m_has_teleported_flag;

		std::shared_ptr<base_option> m_popular;
		std::shared_ptr<base_option> m_docks;
		std::shared_ptr<base_option> m_airstrips;
		std::shared_ptr<base_option> m_zones;
		std::shared_ptr<base_option> m_interiors;

		int m_nearest_vehicle;
		int m_personal_vehicle;
		int m_last_vehicle;

		uint32_t m_waypoint_timer;
	};

	void teleport(math::vector3<float> coords, bool only_player = false, std::function<void(math::vector3<float>)> callback = [](math::vector3<float>) {}, bool no_tp = false);
	extern variables m_vars;
}