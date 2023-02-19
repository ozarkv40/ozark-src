#include "fx_sky.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"
#include "util/memory/memory.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "../../helper/helper_color.h"
#include "../../helper/helper_rainbow.h"
#include "menu/base/util/instructionals.h"

using namespace world::fx::sky::vars;

namespace world::fx::sky::vars {
	variables m_vars;

	scroll_struct<sky_color*> sky_colors[] = {
		{ localization("Azimuth East Color", true), &m_vars.m_azimuth_east_color },
		{ localization("Azimuth West Color", true), &m_vars.m_azimuth_west_color },
		{ localization("Azimuth Transition Color", true), &m_vars.m_azimuth_transition_color },
		{ localization("Cloud Base Minus Mid Color", true), &m_vars.m_cloud_base_minus_mid_colour },
		{ localization("Cloud Mid Color", true), &m_vars.m_cloud_mid_color },
		{ localization("Cloud Shadow Base Color", true), &m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength },
		{ localization("Moon Color", true), &m_vars.m_moon_color },
		{ localization("Sky Plane Color", true), &m_vars.m_sky_plane_color },
		{ localization("Sun Color", true), &m_vars.m_sun_color },
		{ localization("Zenith Color", true), &m_vars.m_zenith_color },
		{ localization("Zenith Transition Color", true), &m_vars.m_zenith_transition_color }
	};

	std::pair<int, uint64_t> offsets[] = {
		{ 1, 0x39 },  // [1] 0x39
		{ 1, 0x6D },  // [1] 0x6D
		{ 1, 0xA1 },  // [1] 0xA1
		{ 2, 0x2E1 }, // [2] 0x2E1
		{ 1, 0x461 }, // [1] 0x461
		{ 2, 0x2CA }, // [2] 0x2CA
		{ 1, 0x36B }, // [1] 0x36B
		{ 1, 0x19F }, // [1] 0x19F
		{ 1, 0x261 }, // [1] 0x261
		{ 1, 0xE7 },  // [1] 0xE7
		{ 1, 0x121 }, // [1] 0x121
	};

	void handle_patch(int index, bool reset) {
		if (reset) {
			// Just patch back the cache, the game will auto-update for us
			memory::write_vector(offsets[index].second, sky_colors[index].m_result->m_cache);

			util::fiber::sleep(1000);

			sky_colors[index].m_result->m_color.x = sky_colors[index].m_result->m_memory_color_cache.x;
			sky_colors[index].m_result->m_color.y = sky_colors[index].m_result->m_memory_color_cache.y;
			sky_colors[index].m_result->m_color.z = sky_colors[index].m_result->m_memory_color_cache.z;

			sky_colors[index].m_result->m_memory_color->x = sky_colors[index].m_result->m_memory_color_cache.x;
			sky_colors[index].m_result->m_memory_color->y = sky_colors[index].m_result->m_memory_color_cache.y;
			sky_colors[index].m_result->m_memory_color->z = sky_colors[index].m_result->m_memory_color_cache.z;
			return;
		}

		if (*(uint8_t*)(offsets[index].second) != 0x90) {
			memory::nop(offsets[index].second, (int)sky_colors[index].m_result->m_cache.size());
		}

		math::vector3_<float> floats = sky_colors[index].m_result->m_color;
		sky_colors[index].m_result->m_memory_color->x = floats.x * sky_colors[index].m_result->m_luminance;
		sky_colors[index].m_result->m_memory_color->y = floats.y * sky_colors[index].m_result->m_luminance;
		sky_colors[index].m_result->m_memory_color->z = floats.z * sky_colors[index].m_result->m_luminance;
	}

	void reset() {
		sky_colors[m_vars.m_selected].m_result->m_rainbow_toggle = false;
		sky_colors[m_vars.m_selected].m_result->m_rainbow.stop();
		util::fiber::pool::add([] { handle_patch(m_vars.m_selected, true); });
	}
}

void fx_sky_menu::load() {
	set_name("Sky");
	set_parent<game_fx_menu>();

	set_default_instructionals(false);

	if (!is_valid_ptr(global::vars::g_ui_weather)) return;

	for (std::pair<int, uint64_t>& offset : offsets) {
		if (offset.first == 1) {
			offset.second += global::vars::g_update_ui_values;
		} else offset.second += global::vars::g_update_ui_values_2;
	}

	for (int i = 0; i < 7; i++) {
		uint64_t sevens = offsets[2].second;
		sky_colors[2].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[3].second;
		sky_colors[3].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[4].second;
		sky_colors[4].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[5].second;
		sky_colors[5].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[6].second;
		sky_colors[6].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[7].second;
		sky_colors[7].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[8].second;
		sky_colors[8].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[9].second;
		sky_colors[9].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));

		sevens = offsets[10].second;
		sky_colors[10].m_result->m_cache.push_back(*(uint8_t*)(sevens + i));
	}

	for (int i = 0; i < 4; i++) {
		uint64_t fours = offsets[0].second;
		sky_colors[0].m_result->m_cache.push_back(*(uint8_t*)(fours + i));

		fours = offsets[1].second;
		sky_colors[1].m_result->m_cache.push_back(*(uint8_t*)(fours + i));
	}

	sky_colors[0].m_result->m_memory_color = &global::vars::g_ui_weather->m_azimuth_east_color.m_value;
	sky_colors[1].m_result->m_memory_color = &global::vars::g_ui_weather->m_azimuth_west_color.m_value;
	sky_colors[2].m_result->m_memory_color = &global::vars::g_ui_weather->m_azimuth_transition_color.m_value;
	sky_colors[3].m_result->m_memory_color = &global::vars::g_ui_weather->m_cloud_base_minus_mid_colour.m_value;
	sky_colors[4].m_result->m_memory_color = &global::vars::g_ui_weather->m_cloud_mid_color.m_value;
	sky_colors[5].m_result->m_memory_color = &global::vars::g_ui_weather->m_cloud_shadow_minus_base_colour_times_shadow_strength.m_value;
	sky_colors[6].m_result->m_memory_color = &global::vars::g_ui_weather->m_moon_color.m_value;
	sky_colors[7].m_result->m_memory_color = &global::vars::g_ui_weather->m_sky_plane_color.m_value;
	sky_colors[8].m_result->m_memory_color = &global::vars::g_ui_weather->m_sun_color.m_value;
	sky_colors[9].m_result->m_memory_color = &global::vars::g_ui_weather->m_zenith_color.m_value;
	sky_colors[10].m_result->m_memory_color = &global::vars::g_ui_weather->m_zenith_transition_color.m_value;

	for (scroll_struct<sky_color*> c : sky_colors) {
		if (is_valid_ptr(c.m_result)) {
			if (is_valid_ptr(c.m_result->m_memory_color)) {
				c.m_result->m_memory_color_cache = *c.m_result->m_memory_color;

				c.m_result->m_internal_color.r = (int)(c.m_result->m_memory_color->x * 255.f);
				c.m_result->m_internal_color.g = (int)(c.m_result->m_memory_color->y * 255.f);
				c.m_result->m_internal_color.b = (int)(c.m_result->m_memory_color->z * 255.f);
				c.m_result->m_internal_color.a = 255;

				if (c.m_result->m_memory_color->x > 1.f) {
					c.m_result->m_luminance = c.m_result->m_memory_color->x / 1.f;
					c.m_result->m_internal_color.r /= (int)c.m_result->m_luminance;
				}
				
				if(c.m_result->m_memory_color->y > 1.f) {
					c.m_result->m_luminance = c.m_result->m_memory_color->y / 1.f;
					c.m_result->m_internal_color.g /= (int)c.m_result->m_luminance;
				}
				
				if (c.m_result->m_memory_color->z > 1.f) {
					c.m_result->m_luminance = c.m_result->m_memory_color->z / 1.f;
					c.m_result->m_internal_color.b /= (int)c.m_result->m_luminance;
				}

				if (c.m_result->m_internal_color.r < 0) c.m_result->m_internal_color.r = 0;
				if (c.m_result->m_internal_color.g < 0) c.m_result->m_internal_color.g = 0;
				if (c.m_result->m_internal_color.b < 0) c.m_result->m_internal_color.b = 0;

				c.m_result->m_color.x = c.m_result->m_memory_color->x;
				c.m_result->m_color.y = c.m_result->m_memory_color->y;
				c.m_result->m_color.z = c.m_result->m_memory_color->z;
			}
		}
	}

	add_option(scroll_option<sky_color*>(SCROLLSELECT, "Element")
		.add_translate()
		.add_scroll(m_vars.m_selected, 0, NUMOF(sky_colors), sky_colors));

	add_option(submenu_option("Edit Color")
		.add_translate()
		.add_submenu<helper_color_menu>()
		.add_click([=] {
			helper_color_menu::get()->set_name(get_name().get(), false, false);
			helper_color_menu::get()->set_parent<fx_sky_menu>();
			helper::color::vars::m_vars.m_color = &sky_colors[m_vars.m_selected].m_result->m_internal_color;

			helper::color::vars::m_vars.m_callback = [] {
				sky_colors[m_vars.m_selected].m_result->m_color.x = sky_colors[m_vars.m_selected].m_result->m_internal_color.r / 255.f;
				sky_colors[m_vars.m_selected].m_result->m_color.y = sky_colors[m_vars.m_selected].m_result->m_internal_color.g / 255.f;
				sky_colors[m_vars.m_selected].m_result->m_color.z = sky_colors[m_vars.m_selected].m_result->m_internal_color.b / 255.f;
				handle_patch(m_vars.m_selected);
			};
		})
		.add_update([] (submenu_option* option, int pos) {
			option->add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, &sky_colors[m_vars.m_selected].m_result->m_internal_color);
		}));

	add_option(number_option<float>(SCROLL, "Luminance")
		.add_translate()
		.add_number(sky_colors[m_vars.m_selected].m_result->m_luminance, "%.1f", 0.1f).add_min(0.1f).add_max(100.f)
		.add_update([](number_option<float>* option, int pos) { option->add_number(sky_colors[m_vars.m_selected].m_result->m_luminance, "%.1f", 0.1f); })
		.add_click([] { handle_patch(m_vars.m_selected); }));

	add_option(toggle_option("Rainbow")
		.add_translate()
		.add_toggle(sky_colors[m_vars.m_selected].m_result->m_rainbow_toggle)
		.add_update([](toggle_option* option, int pos) { option->add_toggle(sky_colors[m_vars.m_selected].m_result->m_rainbow_toggle); })
		.add_click([] {
			sky_colors[m_vars.m_selected].m_result->m_rainbow.toggle(sky_colors[m_vars.m_selected].m_result->m_rainbow_toggle);
			if (sky_colors[m_vars.m_selected].m_result->m_rainbow_toggle) {
				sky_colors[m_vars.m_selected].m_result->m_rainbow.add(&sky_colors[m_vars.m_selected].m_result->m_internal_color);
			} else {
				sky_colors[m_vars.m_selected].m_result->m_rainbow.remove(&sky_colors[m_vars.m_selected].m_result->m_internal_color);
				handle_patch(m_vars.m_selected);
			}
		}));

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click(reset));
}

void fx_sky_menu::update() {
	if (menu::base::get_current_option() == 3) {
		instructionals::rainbow();

		if (menu::input::is_just_pressed(false, ControlFrontendX)) {
			helper::rainbow::vars::m_vars.m_rainbow = &sky_colors[m_vars.m_selected].m_result->m_rainbow;
			helper_rainbow_menu::get()->set_parent<fx_sky_menu>();
			menu::submenu::handler::set_submenu(helper_rainbow_menu::get());
		}
	} else instructionals::standard(false, false, false);
}

void fx_sky_menu::update_once() {}

void fx_sky_menu::feature_update() {
	for (int i = 0; i < NUMOF(sky_colors); i++) {
		scroll_struct<sky_color*>& c = sky_colors[i];
		if (is_valid_ptr(c.m_result)) {
			if (is_valid_ptr(c.m_result->m_memory_color)) {
				if (c.m_result->m_rainbow_toggle) {
					c.m_result->m_rainbow.run();

					c.m_result->m_color.x = c.m_result->m_internal_color.r / 255.f;
					c.m_result->m_color.y = c.m_result->m_internal_color.g / 255.f;
					c.m_result->m_color.z = c.m_result->m_internal_color.b / 255.f;

					handle_patch(i);
				}
			}
		}
	}
}

fx_sky_menu* g_instance;
fx_sky_menu* fx_sky_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_sky_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}