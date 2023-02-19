#include "main.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "global/ui_vars.h"
#include "rage/invoker/natives.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/util/instructionals.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/panels.h"
#include "main/player.h"
#include "main/weapon/weapon_mods.h"
#include "main/misc.h"
#include "main/world.h"
#include "main/settings.h"
#include "main/teleport.h"
#include "main/spawner.h"
#include "main/vehicle.h"
#include "main/protections.h"
#include "main/network.h"
#include "main/helper/helper_color.h"
#include "main/helper/helper_esp.h"
#include "main/helper/helper_rainbow.h"
#include "rage/engine.h"
#include "util/caller.h"
#include "util/log.h"
#include "util/dirs.h"
#include "util/util.h"
#include "util/memory/memory.h"
#include "menu/base/util/global.h"
#include "rage/ros.h"
#include "menu/base/util/control.h"
#include "auth/crypto/crypto.h"
#include "rage/types/global_types.h"
#include <fstream>

using namespace main::vars;

namespace main::vars {
	variables m_vars;

	void scaleform_fade_out_time(const char* sParam0, float fParam1) {
		native::push_scaleform_movie_function(m_vars.m_scaleform_handle, "HIDE");
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam0);
		native::end_text_command_scaleform_string();
		native::push_scaleform_movie_function_parameter_float(fParam1);
		native::pop_scaleform_movie_function_void();
	}

	void scaleform_fade_in_time(const char* sParam0, float fParam1) {
		native::push_scaleform_movie_function(m_vars.m_scaleform_handle, "SHOW_SINGLE_LINE");
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam0);
		native::end_text_command_scaleform_string();
		native::push_scaleform_movie_function_parameter_float(fParam1);
		native::pop_scaleform_movie_function_void();
	}

	void scaleform_render_line(const char* sParam0, const char* sParam1, const char* sParam2, const char* sParam3, bool bParam4) {
		native::push_scaleform_movie_function(m_vars.m_scaleform_handle, "ADD_TEXT_TO_SINGLE_LINE");
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam0);
		native::end_text_command_scaleform_string();
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam1);
		native::end_text_command_scaleform_string();
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam2);
		native::end_text_command_scaleform_string();
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam3);
		native::end_text_command_scaleform_string();
		native::push_scaleform_movie_function_parameter_bool(bParam4);
		native::pop_scaleform_movie_function_void();
	}

	void scaleform_setup_single_line(const char* sParam0, float fParam1, float fParam2, float fParam3, float fParam4, const char* sParam5) {
		native::push_scaleform_movie_function(m_vars.m_scaleform_handle, "SETUP_SINGLE_LINE");
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam0);
		native::end_text_command_scaleform_string();
		native::push_scaleform_movie_function_parameter_float(fParam1);
		native::push_scaleform_movie_function_parameter_float(fParam2);
		native::push_scaleform_movie_function_parameter_float(fParam3);
		native::push_scaleform_movie_function_parameter_float(fParam4);
		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(sParam5);
		native::end_text_command_scaleform_string();
		native::pop_scaleform_movie_function_void();
	}

	void scaleform_render() {
		if (!m_vars.m_has_initialized) {
			native::transition_to_blurred(1000);
			m_vars.m_scaleform_handle = native::request_scaleform_movie("OPENING_CREDITS");
			m_vars.m_has_initialized = true;
		}

		if (native::has_scaleform_movie_loaded(m_vars.m_scaleform_handle)) {
			static const DWORD TIMER = GetTickCount();
			switch (m_vars.m_current_index) {
				case -1:
					if (GetTickCount() - TIMER > 750) {
						m_vars.m_current_index++;
					}
					break;
				case 0:
					scaleform_setup_single_line("presents", 1.5f, 1.5f, 20.f, 20.f, "left");
					scaleform_render_line("presents", "OZARK CHEATS", "$font2", "HUD_COLOUR_WHITE", 1);
					scaleform_render_line("presents", "presents", "$font5", "HUD_COLOUR_FREEMODE", 1);
					scaleform_fade_in_time("presents", 0.166f);
					m_vars.m_cached_time = GetTickCount();
					m_vars.m_current_index++;
					break;
				case 1:
					if (GetTickCount() - m_vars.m_cached_time > 3250) {
						scaleform_fade_out_time("presents", 0.166f);
						m_vars.m_current_index++;
					}

					break;
				case 2:
					if (GetTickCount() - m_vars.m_cached_time > 5750) { // 70
						scaleform_setup_single_line("presents", 1.5f, 1.5f, 0.f, 190.f, "left");
						scaleform_render_line("presents", "a", "$font5", "HUD_COLOUR_MICHAEL", 1);
						scaleform_render_line("presents", "NEW ERA", "$font2", "HUD_COLOUR_WHITE", 1);
						scaleform_render_line("presents", "of modding", "$font5", "HUD_COLOUR_MICHAEL", 1);
						scaleform_fade_in_time("presents", 0.166f);
						m_vars.m_current_index++;
					}
					break;
				case 3:
					if (GetTickCount() - m_vars.m_cached_time > 5750 + 3250) {
						scaleform_fade_out_time("presents", 0.166f);
						m_vars.m_current_index++;
					}

					break;

				case 4:
					if (GetTickCount() - m_vars.m_cached_time > 5750 + 3250 + 3250) {
						native::set_scaleform_movie_as_no_longer_needed(&m_vars.m_scaleform_handle);
						m_vars.m_scaleform_handle = -1;
						m_vars.m_shown_welcome = true;
						native::transition_from_blurred(1000);

						util::fiber::pool::add([=] {
							util::fiber::sleep(1500);
							global::ui::g_stop_rendering = false;
						});
					}
					break;
			}

			if (m_vars.m_scaleform_handle != -1) {
				native::draw_scaleform_movie_fullscreen(m_vars.m_scaleform_handle, 255, 255, 255, 255, 0);
			}
		}
	}

	void log_player_globals(Player player, int base, int size) {
		LOG("--- Global_%i[%i <%i>] -------------------------", base, player, size);

		for (int i = 0; i < size; i++) {
			int _int = *menu::script_global(base).at(player, size).at(i).get<int>();
			uint32_t _uint = *menu::script_global(base).at(player, size).at(i).get<uint32_t>();
			float _float = *menu::script_global(base).at(player, size).at(i).get<float>();

			LOG("Global_%i[%i <%i>].f_%i = %i (%u %.3f)", base, player, size, i, _int, _uint, _float);
		}

		LOG("----------------------------------------------------------");
	}
}

void main_menu::load() {
	set_name("Ozark", false, false);

	get_submenu_name_stack().push("Ozark");
	set_default_instructionals(false);

	m_vars.m_shown_welcome = util::config::read_bool(get_submenu_name_stack(), "Shown Welcome", false, { "Main" });
	if (!m_vars.m_shown_welcome) {
		global::ui::g_stop_rendering = true;
		util::config::write_bool(get_submenu_name_stack(), "Shown Welcome", true, { "Main" });
	}

	menu::panels::load();

	add_option(submenu_option("Player")
		.add_translate().add_hotkey()
		.add_submenu<player_menu>());

	add_option(submenu_option("Network")
		.add_translate().add_hotkey()
		.add_submenu<network_menu>());

	add_option(submenu_option("Protections")
		.add_translate().add_hotkey()
		.add_submenu<protection_menu>());

	add_option(submenu_option("Teleport")
		.add_translate().add_hotkey()
		.add_submenu<teleport_menu>());

	add_option(submenu_option("Weapon")
		.add_translate().add_hotkey()
		.add_submenu<weapon_mods_menu>());

	add_option(submenu_option("Vehicle")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_menu>());

	add_option(submenu_option("Spawner")
		.add_translate().add_hotkey()
		.add_submenu<spawner_menu>()
		.add_click([] { spawner::vars::m_vars.m_flag = spawner::vars::SPAWNER_SELF; }));

	add_option(submenu_option("World")
		.add_translate().add_hotkey()
		.add_submenu<world_menu>());

	add_option(submenu_option("Miscellaneous")
		.add_translate().add_hotkey()
		.add_submenu<misc_menu>());

	add_option(submenu_option("Settings")
		.add_translate().add_hotkey()
		.add_submenu<settings_menu>());

	helper_color_menu::get();
	helper_esp_menu::get();
	helper_rainbow_menu::get();

	int language = native::get_current_language_id();
	if (language == 9 || language == 12) {
		global::vars::g_chinese = true;

		global::ui::g_option_font = 0;
		global::ui::g_header_font = 0;
		global::ui::g_sub_header_font = 0;
		global::ui::g_open_tooltip_font = 0;
		global::ui::g_tooltip_font = 0;
		global::ui::g_stacked_display_font = 0;
		global::ui::g_notify_title_font = 0;
		global::ui::g_notify_body_font = 0;
		global::ui::g_panel_font = 0;
		global::ui::g_option_height = 0.30f;
	}
}

void main_menu::update() {
	instructionals::main_menu();
}

void main_menu::update_once() {}

void main_menu::feature_update() {
	if (!m_vars.m_shown_welcome) {
		scaleform_render();
	}

	if (global::vars::g_network_base_config) {
		rage::network::network_base_config* real_config = global::vars::g_network_base_config;
		if (global::vars::g_steam) {
			real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
		}

		real_config->set_network_session_was_invited(false);
	}

	for (int i = 0; i < 10; i++) {
		if (global::vars::g_arxan_called[i]) {
			global::vars::g_arxan_called[i] = false;
			LOG_DEV("[ARXAN] Called %i", i + 1);
		}
	}

	menu::script_global(rage::global::_155_spawn_dlc_in_sp).as<bool>() = true;
}

main_menu* g_instance;
main_menu* main_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new main_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}