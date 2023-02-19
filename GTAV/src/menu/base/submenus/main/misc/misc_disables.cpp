#include "misc_disables.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "menu/base/util/global.h"
#include "rage/types/global_types.h"

using namespace misc::disables::vars;

namespace misc::disables::vars {
	variables m_vars;

	template <typename TYPE>
	void set_tunable(int Tunable, TYPE Value) {
		menu::script_global(rage::global::_155_tunables).at(Tunable).as<TYPE>() = Value;
	}

	void disable_phone() {
		int type = rage::global::_155_disable_phone_type;
		int bool_1 = rage::global::_155_disable_phone_bool_1;
		int phone_pos_set = rage::global::_155_disable_phone_phone_pos_set;
		int phone_pos_get = rage::global::_155_disable_phone_phone_pos_get;
		int bitset_1 = rage::global::_155_disable_phone_bitset_1;
		int bitset_2 = rage::global::_155_disable_phone_bitset_2;
		int unk_1 = rage::global::_155_disable_phone_unk_1;

		if (*menu::script_global(type).at(1).get<bool>() != 1) {
			if (native::get_number_of_instances_of_script_with_name_hash(joaat("cellphone_flashhand")) > 0 ||
				*menu::script_global(type).at(1).get<int>() > 3) {
				if (*menu::script_global(bool_1).get<bool>()) {
					menu::script_global(bool_1).as<int>() = 0;
					menu::script_global(phone_pos_set).as<int>() = *menu::script_global(phone_pos_get).get<int>();
					menu::script_global(phone_pos_set).at(1).as<int>() = *menu::script_global(phone_pos_get).at(1).get<int>();
					menu::script_global(phone_pos_set).at(2).as<int>() = *menu::script_global(phone_pos_get).at(2).get<int>();

					native::set_mobile_phone_position(*menu::script_global(phone_pos_set).get<float>(), *menu::script_global(phone_pos_set).at(1).get<float>(), *menu::script_global(phone_pos_set).at(2).get<float>());
				}

				if (*menu::script_global(type).at(1).get<int>() == 10 || *menu::script_global(type).at(1).get<int>() == 9) {
					native::set_bit((int*)menu::script_global(bitset_1).get<int>(), 16);
				}

				if (native::is_mobile_phone_call_ongoing()) {
					native::stop_scripted_conversation(false);
				}

				menu::script_global(unk_1).as<int>() = 5;
				native::clear_bit(menu::script_global(bitset_2).get<int>(), 30);

				if (*menu::script_global(type).at(1).get<int>() != 1 && *menu::script_global(type).at(1).get<int>() != 0) {
					menu::script_global(type).at(1).as<int>() = 3;
				}
			}

			native::set_bit((int*)menu::script_global(bitset_1).get<int>(), 2);
		}
	}
}

void misc_disables_menu::load() {
	set_name("Disables");
	set_parent<misc_menu>();

	add_option(toggle_option("Disable Idle Kick")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_idle_kick).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Profanity Filter")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_profanity_filter).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Phone")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_phone).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Calls")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_calls).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Stunt Jumps")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_stunt_jumps).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Cinematic Camera")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_cinematic_camera).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Minimap")
		.add_translate().add_hotkey()
		.add_click([] { native::display_radar(true); })
		.add_toggle(m_vars.m_disable_minimap).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable HUD")
		.add_translate().add_hotkey()
		.add_click([] { native::display_hud(true); })
		.add_toggle(m_vars.m_disable_hud).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Chat on Open")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_chat_on_open).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Restricted Areas")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_restricted_areas).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Notifications")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_notifications).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Loading Prompts")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_loading_prompts).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Cutscenes")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_cutscenes).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Boundary Limit")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_boundry_limit).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Easy Way Out Limit")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_easy_way_out_limit).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Passive Mode Limit")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_passive_mode_limit).add_savable(get_submenu_name_stack()));

	add_option(button_option("Disable Mission Circles")
		.add_translate().add_hotkey()
		.add_click([] { native::terminate_all_scripts_with_this_name("fmmc_launcher"); }));
}

void misc_disables_menu::update() {}

void misc_disables_menu::update_once() {}

void misc_disables_menu::feature_update() {
	if (m_vars.m_disable_easy_way_out_limit) {
		set_tunable(27907, 0);
		set_tunable(27908, 0);
	}

	if (m_vars.m_disable_passive_mode_limit) {
		set_tunable(26681, 0);
		set_tunable(26682, 0);
		set_tunable(26683, 0);
	}

	if (m_vars.m_disable_idle_kick) {
#undef max
		set_tunable(87, std::numeric_limits<int>::max());
		set_tunable(88, std::numeric_limits<int>::max());
		set_tunable(89, std::numeric_limits<int>::max());
		set_tunable(90, std::numeric_limits<int>::max());
	}

	if (m_vars.m_disable_boundry_limit) {
		native::expand_world_limits(-9000.f, -11000.f, 30.f);
		native::expand_world_limits(10000.f, 12000.f, 30.f);
	}

	if (m_vars.m_disable_cutscenes) {
		if (native::is_cutscene_active() || native::is_cutscene_playing()) {
			native::stop_cutscene_immediately();
		}
	}

	if (m_vars.m_disable_loading_prompts) {
		if (native::is_loading_prompt_being_displayed()) {
			native::remove_loading_prompt();
		}
	}

	if (m_vars.m_disable_notifications) {
		native::clear_all_help_messages();
	}

	if (m_vars.m_disable_minimap) {
		native::display_radar(false);
	}

	if (m_vars.m_disable_hud) {
		native::display_hud(false);
	}

	if (m_vars.m_disable_calls) {
		if (native::is_mobile_phone_call_ongoing()) {
			native::stop_scripted_conversation(false);
		}
	}

	if (m_vars.m_disable_stunt_jumps) {
		if (native::is_stunt_jump_in_progress()) {
			native::cancel_stunt_jump();
		}
	}

	if (m_vars.m_disable_cinematic_camera) {
		native::disable_control_action(0, ControlVehicleCinCam, true);
	}

	if (m_vars.m_disable_phone) {
		disable_phone();
	}

	if (m_vars.m_disable_restricted_areas) {
		std::string scripts[] = {
			"am_armybase",
			"restrictedareas",
			"re_armybase",
			"re_lossantosintl",
			"re_prison",
			"re_prisonvanbreak"
		};

		for (std::string area : scripts) {
			if (native::does_script_exist(area.c_str())) {
				native::terminate_all_scripts_with_this_name(area.c_str());
			}
		}
	}
}

misc_disables_menu* g_instance;
misc_disables_menu* misc_disables_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new misc_disables_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
