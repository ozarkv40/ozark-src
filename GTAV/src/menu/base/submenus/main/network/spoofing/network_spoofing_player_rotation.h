#pragma once
#include "menu/base/submenu.h"

class network_spoofing_player_rotation_menu : public menu::submenu::submenu {
public:
	static network_spoofing_player_rotation_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_player_rotation_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::rotation::player::vars {
	struct variables {
		bool m_spinbot;
		bool m_jitter;
		bool m_face_direction;
		bool m_relative;

		int m_face_direction_val;
		float m_spinbot_speed = 10.f;

		math::vector2<float> m_hook_value;
	};

	extern variables m_vars;
}