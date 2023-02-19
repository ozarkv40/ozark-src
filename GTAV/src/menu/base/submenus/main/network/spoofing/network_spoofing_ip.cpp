#include "network_spoofing_ip.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"
#include "util/util.h"

using namespace network::spoofing::ip::vars;

namespace network::spoofing::ip::vars {
	variables m_vars;

	void spoof(bool reset, std::string ip) {
		network_spoofing_ip_menu* _this = network_spoofing_ip_menu::get();

		if (reset) {
			std::vector<std::string> split = util::split_string(m_vars.m_default_ip, ".");
			if (split.size() == 4) {
				util::config::write_string(_this->get_submenu_name_stack(), "IP", m_vars.m_default_ip.c_str());

				m_vars.m_spoofing_ip = m_vars.m_default_ip;

				if (m_vars.m_save_to_config) {
					util::config::write_string(_this->get_submenu_name_stack(), "IP", m_vars.m_default_ip.c_str());
				}
			} else {
				menu::notify::stacked(_this->get_name().get(), _this->get_string("Invalid default IP"), global::ui::g_error);
			}

			return;
		}

		std::vector<std::string> split = util::split_string(ip, ".");
		if (split.size() == 4) {
			m_vars.m_spoofing_ip = ip;
			if (m_vars.m_save_to_config) {
				util::config::write_string(_this->get_submenu_name_stack(), "IP", m_vars.m_spoofing_ip.c_str());
			}

			menu::notify::stacked(_this->get_name().get(), _this->get_string("Spoofing IP to") + " " + ip);
		} else {
			menu::notify::stacked(_this->get_name().get(), _this->get_string("Invalid IP format (has to be xxx.xxx.xxx.xxx)"), global::ui::g_error);
		}
	}
}

void network_spoofing_ip_menu::load() {
	set_name("IP Address");
	set_parent<network_spoofing_menu>();

	add_option(button_option("Input IP")
		.add_translate()
		.add_keyboard("Enter IP", 15, [this](button_option* _this, const char* Name) {
		std::vector<std::string> split = util::split_string(Name, ".");
			if (split.size() == 4) {
				m_vars.m_temp_spoofing_ip = Name;
			} else {
				menu::notify::stacked(get_name().get(), get_string("Invalid IP format (has to be xxx.xxx.xxx.xxx)"), global::ui::g_error);
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
		.add_click([this] { spoof(false, m_vars.m_temp_spoofing_ip); }));

	if (m_vars.m_save_to_config) {
		m_vars.m_spoofing_ip = m_vars.m_temp_spoofing_ip = util::config::read_string(get_submenu_name_stack(), "IP", m_vars.m_spoofing_ip.c_str());
		spoof(false, m_vars.m_spoofing_ip);
	}

	add_string("Invalid IP format (has to be xxx.xxx.xxx.xxx)");
	add_string("Invalid default IP");
	add_string("Spoofing IP to");
}

void network_spoofing_ip_menu::update() {
	snprintf(m_vars.m_preview_name, 50, "Apply: %s", m_vars.m_temp_spoofing_ip.c_str());
	m_vars.m_preview_button->set_name(m_vars.m_preview_name);
}

void network_spoofing_ip_menu::update_once() {}

void network_spoofing_ip_menu::feature_update() {
	if (m_vars.m_default_ip.empty()) {
		if (menu::player::get_local_player().m_net_player) {
			if (menu::player::get_local_player().m_net_player->m_player_info) {
				uint8_t* ip = (uint8_t*)&menu::player::get_local_player().m_net_player->m_player_info->m_external_ip;
				m_vars.m_default_ip = util::va::va("%i.%i.%i.%i", ip[3], ip[2], ip[1], ip[0]);

				if (m_vars.m_temp_spoofing_ip.empty()) {
					m_vars.m_temp_spoofing_ip = m_vars.m_default_ip;
				}
			}
		}
	}
}

network_spoofing_ip_menu* g_instance;
network_spoofing_ip_menu* network_spoofing_ip_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_ip_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}