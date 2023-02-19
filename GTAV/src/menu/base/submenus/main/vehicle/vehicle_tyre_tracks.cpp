#include "vehicle_tyre_tracks.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "util/config.h"
#include "menu/base/submenus/main/helper/helper_color.h"
#include "menu/base/submenus/main/helper/helper_rainbow.h"
#include "menu/base/util/instructionals.h"

using namespace vehicle::tyres::vars;

namespace vehicle::tyres::vars {
	variables m_vars;

	void persistent() {
		rage::types::vfx_wheel* vfx_wheel = global::vars::g_vfx_wheel.first;
		rage::types::vfx_wheel* vfx_wheel_cache = m_vars.m_cache;

		for (uint32_t i = 0; i < (uint32_t)(global::vars::g_vfx_wheel.second * 4); i++) {
			if (m_vars.m_persistent) {
				vfx_wheel[i].m_type1 = 53;
				vfx_wheel[i].m_type2 = 53;
				vfx_wheel[i].m_type3 = 64;
				vfx_wheel[i].m_type4 = 255;
				vfx_wheel[i].m_unk1 = TRUE;
				vfx_wheel[i].m_unk2 = TRUE;
				vfx_wheel[i].m_unk3 = TRUE;
				vfx_wheel[i].m_unk4 = TRUE;
				vfx_wheel[i].m_pressure_min = 0.0f;
				vfx_wheel[i].m_pressure_max = 0.0f;
			} else {
				vfx_wheel[i].m_type1 = vfx_wheel_cache[i].m_type1;
				vfx_wheel[i].m_type2 = vfx_wheel_cache[i].m_type2;
				vfx_wheel[i].m_type3 = vfx_wheel_cache[i].m_type3;
				vfx_wheel[i].m_type4 = vfx_wheel_cache[i].m_type4;
				vfx_wheel[i].m_unk1 = vfx_wheel_cache[i].m_unk1;
				vfx_wheel[i].m_unk2 = vfx_wheel_cache[i].m_unk2;
				vfx_wheel[i].m_unk3 = vfx_wheel_cache[i].m_unk3;
				vfx_wheel[i].m_unk4 = vfx_wheel_cache[i].m_unk4;
				vfx_wheel[i].m_pressure_min = vfx_wheel_cache[i].m_pressure_min;
				vfx_wheel[i].m_pressure_max = vfx_wheel_cache[i].m_pressure_max;
			}
		}
	}

	void set_color(bool reset, color_rgba color) {
		rage::types::vfx_wheel* vfx_wheel = global::vars::g_vfx_wheel.first;
		rage::types::vfx_wheel* vfx_wheel_cache = m_vars.m_cache;

		for (uint32_t i = 0; i < (uint32_t)(global::vars::g_vfx_wheel.second * 4); i++) {
			if (!reset) {
				vfx_wheel[i].m_r = color.r;
				vfx_wheel[i].m_g = color.g;
				vfx_wheel[i].m_b = color.b;
			} else {
				vfx_wheel[i].m_r = vfx_wheel_cache[i].m_r;
				vfx_wheel[i].m_g = vfx_wheel_cache[i].m_g;
				vfx_wheel[i].m_b = vfx_wheel_cache[i].m_b;
			}
		}
	}
}

void vehicle_tyre_tracks_menu::load() {
	set_name("Tire Tracks");
	set_parent<vehicle_menu>();

	set_default_instructionals(false);

	m_vars.m_cache = (rage::types::vfx_wheel*)malloc((sizeof(rage::types::vfx_wheel) * global::vars::g_vfx_wheel.second) * 4);
	memcpy(m_vars.m_cache, global::vars::g_vfx_wheel.first, (sizeof(rage::types::vfx_wheel) * global::vars::g_vfx_wheel.second) * 4);

	add_option(toggle_option("Save to Config")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_save_to_config).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Persistent Tracks")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_persistent)
		.add_click(persistent));

	add_option(toggle_option("Rainbow")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rainbow_toggle)
		.add_click([] {
			m_vars.m_rainbow.toggle(m_vars.m_rainbow_toggle);
			if (m_vars.m_rainbow_toggle) {
				m_vars.m_rainbow.add(&m_vars.m_color);
			} else {
				m_vars.m_rainbow.remove(&m_vars.m_color);
				set_color(false, m_vars.m_color);
			}
		}));

	add_option(submenu_option("Edit Color")
		.add_translate()
		.add_submenu<helper_color_menu>()
		.add_click([=] {
			helper_color_menu::get()->set_name(get_name().get(), false, false);
			helper_color_menu::get()->set_parent<vehicle_tyre_tracks_menu>();
			helper::color::vars::m_vars.m_color = &m_vars.m_color;
			helper::color::vars::m_vars.m_callback = [] { set_color(false, m_vars.m_color); };
		})
		.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, & m_vars.m_color));

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([] {
			m_vars.m_rainbow_toggle = false;
			m_vars.m_rainbow.stop();
			set_color(true, color_rgba());
		}));

	if (m_vars.m_save_to_config) {
		m_vars.m_rainbow_toggle = util::config::read_bool(get_submenu_name_stack(), "Rainbow", false);
		m_vars.m_persistent = util::config::read_bool(get_submenu_name_stack(), "Persistent Tracks", false);
		util::config::read_color(get_submenu_name_stack(), "Color", &m_vars.m_color);

		if (m_vars.m_rainbow_toggle) {
			m_vars.m_rainbow.add(&m_vars.m_color);
			m_vars.m_rainbow.toggle(true);
		}

		if (m_vars.m_persistent) {
			persistent();
		}
	}
}

void vehicle_tyre_tracks_menu::update() {
	if (menu::base::get_current_option() == 2) {
		instructionals::rainbow();

		if (menu::input::is_just_pressed(false, ControlFrontendX)) {
			helper::rainbow::vars::m_vars.m_rainbow = &m_vars.m_rainbow;
			helper_rainbow_menu::get()->set_parent<vehicle_tyre_tracks_menu>();
			menu::submenu::handler::set_submenu(helper_rainbow_menu::get());
		}
	} else instructionals::standard(false, false, false);
}

void vehicle_tyre_tracks_menu::update_once() {
	if (m_vars.m_save_to_config) {
		util::config::write_color(get_submenu_name_stack(), "Color", m_vars.m_color);
	}
}

void vehicle_tyre_tracks_menu::feature_update() {
	if (m_vars.m_rainbow_toggle) {
		m_vars.m_rainbow.run();
		set_color(false, m_vars.m_color);
	}
}

vehicle_tyre_tracks_menu* g_instance;
vehicle_tyre_tracks_menu* vehicle_tyre_tracks_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_tyre_tracks_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}