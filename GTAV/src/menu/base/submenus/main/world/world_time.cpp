#include "world_time.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "time/time_preset.h"
#include "menu/base/util/panels.h"
#include "rage/engine.h"
#include "menu/base/util/timers.h"

using namespace world::time::vars;

namespace world::time::vars {
	variables m_vars;

	scroll_struct<int> lock_time[] = {
		{ localization("Freeze", true), 0 },
		{ localization("Noon", true), 1 },
		{ localization("Midnight", true), 2 },
		{ localization("Sunrise", true), 3 },
		{ localization("Sunset", true), 4 }
	};

	scroll_struct<float> time_scales[] = {
		{ localization("Default", true), 1.f },
		{ localization("Slow", true), 0.7f },
		{ localization("Slower", true), 0.4f },
		{ localization("Slowest", true), 0.f }
	};

	void set_time(int hour, int minute, int second, bool sync_override) {
		native::set_clock_time(hour, minute, second);

		if (native::network_is_session_active()) {
			native::network_override_clock_time(hour, minute, second);

			if (m_vars.m_sync && sync_override) {
				rage::engine::send_clock_event();
			}
		}
	}

	void precision_time() {
		if (menu::input::is_left_pressed() || menu::input::is_right_pressed()) {
			m_vars.m_lock_time = false;
			m_vars.m_accelerate_time = false;
			m_vars.m_system_time = false;
			m_vars.m_sync = false;

			if (menu::input::is_left_pressed()) {
				rage::engine::add_to_clock_time(0, -1, 0);
			} else {
				rage::engine::add_to_clock_time(0, 1, 0);
			}

			set_time(native::get_clock_hours(), native::get_clock_minutes(), native::get_clock_seconds());
		}
	}
}

void time_menu::load() {
	set_name("Time");
	set_parent<world_menu>();
	
	add_option(submenu_option("Presets")
		.add_translate().add_hotkey()
		.add_submenu<time_preset_menu>());

	add_option(button_option("Advance Time")
		.add_translate().add_hotkey()
		.add_click([] {
			int hour = native::get_clock_hours() + 1;
			if (hour > 23) hour = 0;
			set_time(hour, native::get_clock_minutes(), native::get_clock_seconds());
		}));

	add_option(button_option("Rewind Time")
		.add_translate().add_hotkey()
		.add_click([] {
			int hour = native::get_clock_hours() - 1;
			if (hour < 0) hour = 23;
			set_time(hour, native::get_clock_minutes(), native::get_clock_seconds());
		}));

	add_option(button_option("Precision Time")
		.add_translate()
		.add_hover(precision_time)
		.add_tooltip("Use LEFT & RIGHT, only works while hovering on this option"));

	add_option(scroll_option<int>(TOGGLE, "Lock Time")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_lock_time)
		.add_scroll(m_vars.m_lock_time_var, 0, NUMOF(lock_time), lock_time)
		.add_click([] {
			m_vars.m_accelerate_time = false;
			m_vars.m_system_time = false;

			if (m_vars.m_lock_time && m_vars.m_lock_time_var == 0) {
				m_vars.m_lock_time_freeze[0] = native::get_clock_hours();
				m_vars.m_lock_time_freeze[1] = native::get_clock_minutes();
				m_vars.m_lock_time_freeze[2] = native::get_clock_seconds();
			}
		}));

	add_option(scroll_option<float>(SCROLL, "Timescale")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_time_scale, 0, NUMOF(time_scales), time_scales)
		.add_click([] { if (m_vars.m_time_scale == 0) native::set_time_scale(1.f); }));

	add_option(toggle_option("Accelerate Time")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_accelerate_time)
		.add_click([] {
			m_vars.m_system_time = false;
			m_vars.m_lock_time = false;
		}));

	add_option(toggle_option("Sync to System Time")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_system_time)
		.add_click([] {
			m_vars.m_accelerate_time = false;
			m_vars.m_lock_time = false;
		}));

	/*add_option(toggle_option("Sync to Session")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_sync)
		.add_update([](toggle_option* option, int position) {
			bool selected = menu::base::is_option_selected(position);
			color_rgba color = selected ? global::ui::g_option_selected : global::ui::g_option;

			option->add_offset(0.0165f);
			menu::renderer::draw_sprite({ "ozarktextures", "sync_cloud.png" }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (position * 0.global::ui::g_option_scale) + 0.005f + 0.012f }, { 0.0132f, 0.0216f }, 0.f, color);
		}));*/
}

void time_menu::update() {}

void time_menu::update_once() {
	menu::panels::toggle_panel_render("PANEL_CLOCK", true);
}

void time_menu::feature_update() {
	static int timer = 0;
	static bool can_sync = true;

	menu::timers::run_timed(&timer, 1000, [] {
		can_sync = true;
	});

	if (m_vars.m_time_scale != 0) {
		native::set_time_scale(time_scales[m_vars.m_time_scale].m_result);
	}

	if (m_vars.m_system_time) {
		int day, month, year, hour, min, sec;
		native::get_local_time(&year, &month, &day, &hour, &min, &sec);

		set_time(hour, min, sec, can_sync);
	}

	if (m_vars.m_accelerate_time) {
		rage::engine::add_to_clock_time(0, 2, 0);

		if (native::network_is_session_active()) {
			native::network_override_clock_time(native::get_clock_hours(), native::get_clock_minutes(), native::get_clock_seconds());

			if (m_vars.m_sync && can_sync) {
				rage::engine::send_clock_event();
			}
		}
	}

	if (m_vars.m_lock_time) {
		switch (m_vars.m_lock_time_var) {
			case 0: // Freeze
				set_time(m_vars.m_lock_time_freeze[0], m_vars.m_lock_time_freeze[1], m_vars.m_lock_time_freeze[2], can_sync);
				break;

			case 1: // Noon
				set_time(12, 0, 0, can_sync);
				break;

			case 2: // Midnight
				set_time(0, 0, 0, can_sync);
				break;

			case 3: // Sunrise
				set_time(8, 0, 0, can_sync);
				break;

			case 4: // Sunset
				set_time(20, 0, 0, can_sync);
				break;
		}
	}

	can_sync = false;
}

time_menu* g_instance;
time_menu* time_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new time_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}