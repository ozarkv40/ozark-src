#pragma once
#include "menu/base/submenu.h"

class network_spoofing_vehicle_rotation_menu : public menu::submenu::submenu {
public:
	static network_spoofing_vehicle_rotation_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_vehicle_rotation_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::rotation::vehicle::vars {
	struct variables {
		bool m_ghost;
		bool m_spinbot;
		bool m_jitter;
		bool m_static;
		bool m_relative;

		float m_spinbot_speed = 10.f;

		int m_spinbot_axis;
		int m_jitter_axis;

		math::vector3_<float> m_static_value;
		math::vector3_<bool> m_static_toggle;
		math::vector3_<float> m_hook_value;

		Vehicle m_ghost_handle;
	};

	extern variables m_vars;
}