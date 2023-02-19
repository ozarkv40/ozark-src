#include "world_weather.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "weather/weather_select.h"
#include "menu/base/util/global.h"
#include "weather/fx/weather_fx.h"
#include "rage/types/global_types.h"

using namespace world::weather::vars;

namespace world::weather::vars {
	variables m_vars;

	scroll_struct<int> target_type[] = {
		{ localization("Self", true), 0 },
		{ localization("Session", true), 1 },
		{ localization("Both", true), 2 }
	};

	scroll_struct<int> clouds[] = {
		{ localization("Clear", true), 0 },
		{ localization("Rain", true), 0 },
		{ localization("Horizonband1", true), 0 },
		{ localization("Horizonband2", true), 0 },
		{ localization("Horizonband3", true), 0 },
		{ localization("Puffs", true), 0 },
		{ localization("Wispy", true), 0 },
		{ localization("Horizon", true), 0 },
		{ localization("Contrails", true), 0 },
		{ localization("Altostratus", true), 0 },
		{ localization("Nimbus", true), 0 },
		{ localization("Cirrus", true), 0 },
		{ localization("Cirrocumulus", true), 0 },
		{ localization("Stratoscumulus", true), 0 },
		{ localization("Stripey", true), 0 },
		{ localization("Horsey", true), 0 },
		{ localization("Shower", true), 0 },
		{ localization("Cloudy 01", true), 0 },
		{ localization("Clear 01", true), 0 },
		{ localization("Snowy 01", true), 0 },
		{ localization("Stormy 01", true), 0 }
	};

	scroll_struct<float> rains[] = {
		{ localization("None", true), 0.f },
		{ localization("Light", true), 0.3f },
		{ localization("Heavy", true), 1.5f },
		{ localization("Heavier", true), 3.5f },
		{ localization("Insane", true), 5.5f },
		{ localization("Off the Charts", true), 50.f },
	};

	scroll_struct<float> wind_speeds[] = {
		{ localization("None", true), 0.f },
		{ localization("Light", true), 0.3f },
		{ localization("Fast", true), 1.5f },
		{ localization("Faster", true), 3.5f },
		{ localization("Insane", true), 5.5f },
		{ localization("Off the Charts", true), 50.f },
	};

	void ground_snow() {
		menu::script_global(rage::global::_155_tunables).at(4724).as<int>() = m_vars.m_ground_snow;	// 1.55 done
		menu::script_global(rage::global::_155_tunables).at(9098).as<int>() = !m_vars.m_ground_snow; // 1.55 done
		menu::script_global(rage::global::_155_tunables).at(9099).as<int>() = !m_vars.m_ground_snow;// 1.55 done
		menu::script_global(rage::global::_155_tunables).at(9100).as<int>() = !m_vars.m_ground_snow;// 1.55 done
		menu::script_global(rage::global::_155_tunables).at(9101).as<int>() = !m_vars.m_ground_snow;// 1.55 done
		menu::script_global(rage::global::_155_tunables).at(9106).as<int>() = m_vars.m_ground_snow ? 255 : 0;// 1.55 done
		menu::script_global(rage::global::_155_tunables).at(9107).as<int>() = m_vars.m_ground_snow ? 255 : 0;// 1.55 done
	}
}

void weather_menu::load() {
	set_name("Weather");
	set_parent<world_menu>();

	add_option(submenu_option("Weather")
		.add_translate().add_hotkey()
		.add_submenu<weather_select_menu>());

	add_option(submenu_option("Weather FX")
		.add_translate().add_hotkey()
		.add_submenu<weather_fx_menu>());

	add_option(scroll_option<int>(SCROLL, "Clouds")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_clouds, 0, NUMOF(clouds), clouds)
		.add_click([] { if (m_vars.m_clouds == 0) native::clear_cloud_hat(); else native::set_cloud_hat_transition(clouds[m_vars.m_clouds].m_name.get_original().c_str(), 0.5f); }));
	
	add_option(scroll_option<float>(SCROLL, "Wind Speed")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_wind, 0, NUMOF(wind_speeds), wind_speeds)
		.add_click([] { m_vars.m_wind_speed = wind_speeds[m_vars.m_wind].m_result; }));

	add_option(scroll_option<float>(SCROLL, "Rain Intensity")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_rain, 0, NUMOF(rains), rains)
		.add_click([] { native::set_rain_fx_intensity(rains[m_vars.m_rain].m_result); }));

	add_option(toggle_option("Thunder and Lightning")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_lightning).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Ground Snow")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_ground_snow)
		.add_click(ground_snow).add_savable(get_submenu_name_stack()));
}

void weather_menu::update() {}

void weather_menu::update_once() {}

void weather_menu::feature_update() {
	if (m_vars.m_ground_snow) {
		ground_snow();
	}

	if (m_vars.m_lightning) {
		native::create_lightning_thunder();
	}
}

weather_menu* g_instance;
weather_menu* weather_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weather_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}