#include "network_spoofing_rid.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"
#include "util/log.h"

using namespace network::spoofing::rid::vars;

namespace network::spoofing::rid::vars {
	variables m_vars;

	void spoof(bool reset, uint64_t rockstar_id) {
		network_spoofing_rid_menu* _this = network_spoofing_rid_menu::get();

		if (reset) {
			m_vars.m_spoofing_rid = global::vars::g_rs_info->m_rockstar_id;

			if (m_vars.m_save_to_config) {
				util::config::write_uint64(_this->get_submenu_name_stack(), "Rockstar ID", global::vars::g_rs_info->m_rockstar_id);
			}

			if (is_valid_ptr(menu::player::get_local_player().m_net_player)) {
				if (is_valid_ptr(menu::player::get_local_player().m_net_player->m_player_info)) {
					menu::player::get_local_player().m_net_player->m_player_info->m_identifier.m_rockstar_id = global::vars::g_rs_info->m_rockstar_id;
				}
			}

			return;
		}

		m_vars.m_spoofing_rid = rockstar_id;
		menu::notify::stacked(_this->get_name().get(), _this->get_string("Spoofing rockstar id to") + " " + std::to_string(rockstar_id));

		if (m_vars.m_save_to_config) {
			util::config::write_uint64(_this->get_submenu_name_stack(), "Rockstar ID", rockstar_id);
		}

		if (is_valid_ptr(menu::player::get_local_player().m_net_player)) {
			if (is_valid_ptr(menu::player::get_local_player().m_net_player->m_player_info)) {
				menu::player::get_local_player().m_net_player->m_player_info->m_identifier.m_rockstar_id = rockstar_id;
			}
		}
	}
}

void network_spoofing_rid_menu::load() {
	set_name("Rockstar ID");
	set_parent<network_spoofing_menu>();

	m_vars.m_spoofing_rid = global::vars::g_rs_info->m_rockstar_id;
	m_vars.m_loaded = true;
	LOG_DEV("RID: %i", m_vars.m_spoofing_rid);

	add_option(button_option("Input Rockstar ID")
		.add_translate()
		.add_keyboard("Enter Rockstar ID", 16, [this](button_option* _this, const char* name) {
			m_vars.m_temp_spoofing_rid = atoll(name);
			if (m_vars.m_temp_spoofing_rid == 0) {
				menu::notify::stacked(get_name().get(), get_string("Setting to 0 crashes others when they leave the session, that's naughty!"));
			}
		}));
	 
	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([] { spoof(true); }));

	add_option(toggle_option("Save to Config")
		.add_translate()
		.add_toggle(m_vars.m_save_to_config).add_savable(get_submenu_name_stack())
		.add_tooltip("Saves to the config when applied"));

	m_vars.m_preview_button = add_option(button_option("")
		.add_click([this] { spoof(false, m_vars.m_temp_spoofing_rid); }));

	if (m_vars.m_save_to_config) {
		m_vars.m_spoofing_rid = m_vars.m_temp_spoofing_rid = util::config::read_uint64(get_submenu_name_stack(), "Rockstar ID", m_vars.m_spoofing_rid);
		spoof(false, m_vars.m_spoofing_rid);
	}

	add_string("Spoofing rockstar id to");
	add_string("Setting to 0 crashes others when they leave the session, that's naughty!");
}

void network_spoofing_rid_menu::update() {
	snprintf(m_vars.m_preview_name, 50, "Apply: %I64d", m_vars.m_temp_spoofing_rid);
	m_vars.m_preview_button->set_name(m_vars.m_preview_name);
}

void network_spoofing_rid_menu::update_once() {}

void network_spoofing_rid_menu::feature_update() {}

network_spoofing_rid_menu* g_instance;
network_spoofing_rid_menu* network_spoofing_rid_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_rid_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}