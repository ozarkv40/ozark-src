#include "protection_net_events.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"

using namespace protection::events::net::vars;

namespace protection::events::net::vars {
	variables m_vars;

	struct context {
		std::string m_name;
		protection_context* m_context;
		int m_size;
	};

	scroll_struct<int> types[] = {
		{ localization("Off", true), 0 },
		{ localization("Notify", true), 0 },
		{ localization("Block", true), 0 },
		{ localization("Block + Notify", true), 0 },
		{ localization("Redirect", true), 0 },
		{ localization("Redirect + Block", true), 0 },
		{ localization("Redirect + Notify", true), 0 },
		{ localization("All", true), 0 },
	};

	context items[] = {
		{ "Give Weapon", &m_vars.m_give_weapon, 8 },
		{ "Remove Weapon", &m_vars.m_remove_weapon, 8 },
		{ "Remove All Weapons", &m_vars.m_remove_all_weapons, 8 },
		{ "Freeze", &m_vars.m_freeze, 8 },
		{ "Explosion", &m_vars.m_explosion, 8 },
		{ "Fire", &m_vars.m_fire, 4 },
		{ "Particle FX", &m_vars.m_particle_fx, 4 },
		{ "Script Events", &m_vars.m_script_events, 8 },
		{ "Increment Stat", &m_vars.m_increment_stat, 8 },
		{ "Weather", &m_vars.m_weather, 4 },
		{ "Clock", &m_vars.m_clock, 4 },
		{ "Sound", &m_vars.m_sound, 4 },
		{ "Vehicle Control", &m_vars.m_vehicle_control, 4 },
		{ "Blame Explosion", &m_vars.m_blame_explosion, 2 },
	};
}

void protection_net_events_menu::load() {
	set_name("Network Events");
	set_parent<protection_menu>();

	for (context& c : items) {
		add_string(c.m_name);
		c.m_context->m_var = util::config::read_int(get_submenu_name_stack(), c.m_name, c.m_context->m_var);
	}
}

void protection_net_events_menu::update() {}

void protection_net_events_menu::update_once() {
	clear_options(0);

	for (context& c : items) {
		add_option(scroll_option<int>(SCROLL, get_string(c.m_name))
			.add_scroll(c.m_context->m_var, 0, c.m_size, types)
			.add_tooltip(c.m_context->m_tooltip.get())
			.add_click([=] { util::config::write_int(get_submenu_name_stack(), c.m_name, c.m_context->m_var); }));
	}
}

void protection_net_events_menu::feature_update() {}

protection_net_events_menu* g_instance;
protection_net_events_menu* protection_net_events_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_net_events_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}