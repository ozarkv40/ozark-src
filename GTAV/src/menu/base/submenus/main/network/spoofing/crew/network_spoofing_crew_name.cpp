#include "network_spoofing_crew_name.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing_crew.h"
#include "network_spoofing_crew_presets.h"

using namespace network::spoofing::crew::name::vars;

namespace network::spoofing::crew::name::vars {
	variables m_vars;

	void spoof(bool reset, const char* name) {
		network_spoofing_crew_name_menu* _this = network_spoofing_crew_name_menu::get();

		if (reset) {
			m_vars.m_spoofed_name.clear();
			m_vars.m_temp_name.clear();

			if (m_vars.m_save_to_config) {
				util::config::write_string(_this->get_submenu_name_stack(), "Name", "");
			}

			return;
		}

		m_vars.m_spoofed_name = name;

		if (m_vars.m_save_to_config) {
			util::config::write_string(_this->get_submenu_name_stack(), "Name", name);
		}

		menu::notify::stacked(_this->get_name().get(), _this->get_string("Spoofing crew name to") + " " + name);
	}
}

void network_spoofing_crew_name_menu::load() {
	set_name("Crew Name");
	set_parent<network_spoofing_crew_menu>();

	add_option(submenu_option("Presets")
		.add_translate()
		.add_submenu<network_spoofing_crew_presets_menu>()
		.add_click([] {
			network_spoofing_crew_presets_menu::get()->set_parent<network_spoofing_crew_name_menu>();
			network::spoofing::crew::presets::vars::m_vars.m_editing = &m_vars.m_temp_name;
		}));

	add_option(button_option("Input Crew Name")
		.add_translate()
		.add_keyboard("Enter crew name", 24, [](button_option* _this, const char* result) { m_vars.m_temp_name = std::string(result); }));

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
		.add_click([] { spoof(false, m_vars.m_temp_name.c_str()); }));

	if (m_vars.m_save_to_config) {
		m_vars.m_spoofed_name = util::config::read_string(get_submenu_name_stack(), "Name", m_vars.m_spoofed_name);
		m_vars.m_temp_name = m_vars.m_spoofed_name;
		spoof(false, m_vars.m_temp_name.c_str());
	}

	add_string("Spoofing crew name to");
}

void network_spoofing_crew_name_menu::update() {
	snprintf(m_vars.m_preview_name, 50, "Apply: %s", m_vars.m_temp_name.c_str());
	m_vars.m_preview_button->set_name(m_vars.m_preview_name);
}

void network_spoofing_crew_name_menu::update_once() {}

void network_spoofing_crew_name_menu::feature_update() {}

network_spoofing_crew_name_menu* g_instance;
network_spoofing_crew_name_menu* network_spoofing_crew_name_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_crew_name_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}