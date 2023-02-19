#include "time_preset.h"
#include "menu/base/submenu_handler.h"
#include "../world_time.h"
#include "rage/engine.h"
#include "../world_weather.h"

using namespace world::time::preset::vars;

namespace world::time::preset::vars {
	variables m_vars;
}

void time_preset_menu::load() {
	set_name("Presets");
	set_parent<time_menu>();

	add_option(button_option("Noon")
		.add_translate().add_hotkey()
		.add_update_this([=](button_option* option, int position) {
			option->add_offset(0.0165f);
			menu::renderer::draw_sprite({ "ozarktextures", "time_midday.png" }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.005f + 0.012f }, { 0.0136f, 0.0216f }, 0.f, { 222, 164, 38, 255 });
		})
		.add_click([] { world::time::vars::set_time(12, 0, 0); }));

	add_option(button_option("Midnight")
		.add_translate().add_hotkey()
		.add_update_this([=](button_option* option, int position) {
			option->add_offset(0.0165f);
			menu::renderer::draw_sprite({ "ozarktextures", "time_midnight.png" }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.005f + 0.012f }, { 0.0136f, 0.0216f }, 0.f, { 111, 51, 232, 255 });
		})
		.add_click([] { world::time::vars::set_time(0, 0, 0); }));

	add_option(button_option("Sunrise")
		.add_translate().add_hotkey()
		.add_update_this([=](button_option* option, int position) {
			option->add_offset(0.0165f);
			menu::renderer::draw_sprite({ "ozarktextures", "time_sunrise.png" }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.005f + 0.012f }, { 0.0136f, 0.0216f }, 0.f, { 250, 178, 22, 255 });
		})
		.add_click([] { world::time::vars::set_time(8, 0, 0); }));

	add_option(button_option("Sunset")
		.add_translate().add_hotkey()
		.add_update_this([=](button_option* option, int position) {
			option->add_offset(0.0165f);
			menu::renderer::draw_sprite({ "ozarktextures", "time_sunset.png" }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.005f + 0.012f }, { 0.0136f, 0.0216f }, 0.f, { 250, 109, 22, 255 });
		})
		.add_click([] { world::time::vars::set_time(20, 0, 0); }));
}

void time_preset_menu::update() {}

void time_preset_menu::update_once() {}

void time_preset_menu::feature_update() {}

time_preset_menu* g_instance;
time_preset_menu* time_preset_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new time_preset_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}