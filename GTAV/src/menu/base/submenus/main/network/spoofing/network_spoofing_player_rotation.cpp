#include "network_spoofing_player_rotation.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"

using namespace network::spoofing::rotation::player::vars;

namespace network::spoofing::rotation::player::vars {
	variables m_vars;

	scroll_struct<int> face_direction[] = {
		{ localization("Left", true), 0 },
		{ localization("Right", true), 1 },
		{ localization("Back", true), 2 }
	};

	scroll_struct<int> static_type[] = {
		{ localization("Relative", true), 0 },
		{ localization("Static", true), 1 }
	};
}

void network_spoofing_player_rotation_menu::load() {
	set_name("Player Rotation");
	set_parent<network_spoofing_menu>();

	add_option(number_option<float>(TOGGLE, "Spinbot")
		.add_translate()
		.add_toggle(m_vars.m_spinbot)
		.add_number(m_vars.m_spinbot_speed, "%.0f", 1.f).add_min(0.f).add_max(14.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_face_direction = false; m_vars.m_jitter = false; }));

	add_option(scroll_option<int>(TOGGLE, "Face Direction")
		.add_translate()
		.add_toggle(m_vars.m_face_direction)
		.add_scroll(m_vars.m_face_direction_val, 0, NUMOF(face_direction), face_direction)
		.add_click([] { m_vars.m_spinbot = false; m_vars.m_jitter = false; }));

	add_option(toggle_option("Jitter")
		.add_translate()
		.add_toggle(m_vars.m_jitter)
		.add_click([] { m_vars.m_spinbot = false; m_vars.m_face_direction = false; }));

	add_option(toggle_option("Relative")
		.add_translate()
		.add_toggle(m_vars.m_relative)
		.add_tooltip("Current rotation will be added to new rotation"));
}

void network_spoofing_player_rotation_menu::update() {}

void network_spoofing_player_rotation_menu::update_once() {}

void network_spoofing_player_rotation_menu::feature_update() {
	if (m_vars.m_spinbot) {
		static float value = 0.f;
		value += m_vars.m_spinbot_speed;

		if (value > 180.f) value = -180.f + (value - 180.f);
		m_vars.m_hook_value = { value * 0.0174532924f, value * 0.0174532924f };
		return;
	}

	if (m_vars.m_jitter) {
		static float value = 0.f;
		value += 40.f;
		if (value > 180.f) value = -180.f + (value - 180.f);

		m_vars.m_hook_value = { value * 0.0174532924f, value * 0.0174532924f };
	}
}

network_spoofing_player_rotation_menu* g_instance;
network_spoofing_player_rotation_menu* network_spoofing_player_rotation_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_player_rotation_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}