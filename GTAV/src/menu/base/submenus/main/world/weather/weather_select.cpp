#include "weather_select.h"
#include "menu/base/submenu_handler.h"
#include "../world_weather.h"
#include "util/memory/memory.h"
#include "rage/engine.h"
#include "menu/base/util/timers.h"

using namespace world::weather::select::vars;

namespace world::weather::select::vars {
	variables m_vars;

	scroll_struct<std::pair<const char*, const char*>> weathers[] = {
		{ localization("Sunny", true), { "CLEAR", "weather_sunny.png" } },
		{ localization("Extra Sunny", true), { "EXTRASUNNY", "weather_extrasunny.png" } },
		{ localization("Rain", true), { "RAIN", "weather_rain.png" } },//
		{ localization("Clearing", true), { "CLEARING", "weather_clearing.png" } },//
		{ localization("Cloudy", true), { "CLOUDS", "weather_cloudy_overcast.png" } },
		{ localization("Smoggy", true), { "SMOG", "weather_smoggy_foggy.png" } },
		{ localization("Foggy", true), { "FOGGY", "weather_smoggy_foggy.png" } },
		{ localization("Stormy", true), { "THUNDER", "weather_stormy.png" } },
		{ localization("Overcast", true), { "OVERCAST", "weather_cloudy_overcast.png" } },
		{ localization("Light Snow", true), { "SNOWLIGHT", "weather_lightsnow_snow_blizzard.png" } },
		{ localization("Snow", true), { "SNOW", "weather_lightsnow_snow_blizzard.png" } },
		{ localization("Blizzard", true), { "BLIZZARD", "weather_lightsnow_snow_blizzard.png" } },
		{ localization("Christmas", true), { "XMAS", "weather_christmas.png" } },
		{ localization("Neutral", true), { "NEUTRAL", "weather_nuetral.png" } },
		{ localization("Halloween", true), { "HALLOWEEN", "weather_halloween.png" } }
	};

	void set_weather(const char* weather) {
		// 0 = self only
		// 1 = session only
		// 2 = both

		if (m_vars.m_target == 0 || m_vars.m_target == 2) {
			native::set_weather_type_now_persist(weather);
			native::set_weather_type_now(weather);
			native::set_override_weather(weather);
		}

		if (m_vars.m_target == 1 || m_vars.m_target == 2) {
			if (native::network_is_in_session()) {
				rage::engine::send_weather_event(rage::engine::get_weather_id(weather));
			}
		}
	}

	void epilepsy() {
		static int timer = 0;
		menu::timers::run_timed(&timer, 100, [] {
			set_weather(weathers[native::get_random_int_in_range(0, NUMOF(weathers) - 1)].m_result.first);
		});
	}
}

void weather_select_menu::load() {
	set_name("Weather");
	set_parent<weather_menu>();

	/*add_option(scroll_option<int>(SCROLL, "Target")
		.add_translate()
		.add_scroll(m_vars.m_target, 0, NUMOF(world::weather::vars::target_type), world::weather::vars::target_type));*/

	add_option(toggle_option("Epilepsy")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_epilepsy));

	add_option(break_option("Weathers")
		.add_translate());

	for (int i = 0; i < NUMOF(weathers); i++) {
		add_option(button_option(weathers[i].m_name.get())
			.add_update_this([=](button_option* option, int position) {
				option->add_offset(0.0165f);
				menu::renderer::draw_sprite({ "ozarktextures", weathers[i].m_result.second }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.005f + 0.012f }, { 0.0136f, 0.0216f }, 0.f, { 255, 255, 255, 255 });
			})
			.add_click([=] { set_weather(weathers[i].m_result.first); }));
	}
}

void weather_select_menu::update() {}

void weather_select_menu::update_once() {}

void weather_select_menu::feature_update() {
	if (m_vars.m_epilepsy) {
		epilepsy();
	}
}

weather_select_menu* g_instance;
weather_select_menu* weather_select_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weather_select_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}