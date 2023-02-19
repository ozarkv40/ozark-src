#include "network_host_toolkit.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "menu/base/util/panels.h"
#include "menu/base/util/helpers.h"
#include "util/log.h"
#include "rage/engine.h"
#include "toolkit/network_blacklisted_players.h"
#include "toolkit/network_desync_kick.h"
#include "toolkit/network_join_blocking.h"

using namespace network::htoolkit::vars;

namespace network::htoolkit::vars {
	variables m_vars;

	scroll_struct<int> transitions[] = {
		{ localization("Public", true), 1 },
		{ localization("Closed Crew", true), 2 },
		{ localization("Crew", true), 3 },
		{ localization("Closed Friend", true), 6 },
		{ localization("Solo", true), 10 },
		{ localization("Invite Only", true), 11 }
	};

	bool force_host_of_script(const char* script, bool notify) {
		network_host_toolkit_menu* _this = network_host_toolkit_menu::get();

		if (!menu::helpers::is_valid_net_player(menu::player::get_local_player().m_net_player)) {
			LOG_WARN("Failed to force host of %s, player isn't valid", script);
			return false;
		}

		if (native::network_get_host_of_script(script, -1, 0) == menu::player::get_local_player().m_id) {
			LOG_WARN("Failed to force host of %s, player is already host", script);
			return true;
		}

		if (notify) {
			menu::notify::stacked(_this->get_string("Force Script Host"), util::va::va("%s %s...", _this->get_string("Attempting to migrate host of script").c_str(), script), color_rgba(255, 255, 0));
		}

		bool forced = false;
		LOG_DEV("Checking %i threads for %s", *(uint16_t*)(global::vars::g_script_handlers.m_count), script);
		for (uint16_t i = 0; i < *(uint16_t*)(global::vars::g_script_handlers.m_count); i++) {
			rage::script::gta_thread* thread = *(rage::script::gta_thread**)(global::vars::g_script_handlers.m_list + (i * 8));
			if (is_valid_ptr(thread)) {
				if (!strcmp(thread->m_name, script)) {
					rage::script::game_script_handler_network_component* component = thread->m_net_component;
					if (is_valid_ptr(component)) {
						if (is_valid_vtable(component->m_vtable)) {
							LOG_DEV("Component=%llx VTable=%llx State=%i", component, component->m_vtable, component->m_state);
							rage::engine::migrate_script_host(component, menu::player::get_local_player().m_net_player);
							forced = true;
						}
					}
				}
			}
		}

		if (forced) {
			if (notify) {
				menu::notify::stacked(_this->get_string("Force Script Host"), util::va::va("%s %s", _this->get_string("Successfully migrated host of script").c_str(), script), global::ui::g_success);
			}

			return true;
		} else {
			if (notify) {
				menu::notify::stacked(_this->get_string("Force Script Host"), util::va::va("%s %s", _this->get_string("Failed migrating host of script").c_str(), script), global::ui::g_error);
			}
		}

		return false;
	}
}

void network_host_toolkit_menu::load() {
	set_name(XOR("Host Toolkit"));
	set_parent<network_menu>();

	add_option(submenu_option(XOR("Blacklisted Players"))
		.add_translate().add_hotkey()
		.add_submenu<network_blacklisted_players_menu>()
		.add_tooltip("View and modify players who have been host kicked and are blacklisted from joining back"));

	add_option(submenu_option(XOR("Desync Kicks"))
		.add_translate().add_hotkey()
		.add_submenu<network_desync_kick_menu>()
		.add_tooltip("Block/redirect desync & net limiter kicks in your session"));

	add_option(submenu_option(XOR("Join Blocking"))
		.add_translate().add_hotkey()
		.add_submenu<network_join_blocking_menu>()
		.add_tooltip("Prevent players joining your session"));

	// [s] Ozark Guard

	add_option(toggle_option(XOR("Open Extra Slot"))
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_extra_slot)
		.add_click([] { native::_0x49EC8030F5015F8B(m_vars.m_extra_slot ? 4 : 0); }).add_savable(get_submenu_name_stack())
		.add_tooltip(XOR("Allows an extra player to join past the usual limit")));

	add_option(toggle_option(XOR("Sync Real IP"))
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_sync_real_ip).add_savable(get_submenu_name_stack())
		.add_tooltip(XOR("Sync a joining players real IP with the session when they join, making their IP spoof useless to other modders using less fortunate cheats")));
	
	add_option(toggle_option(XOR("Peer Token Correction"))
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_peer_token_correction).add_savable(get_submenu_name_stack())
		.add_tooltip(XOR("Ozark users joining with a matching peer as someone in your session can still join. WILL NOT WORK IF THEY HAVE A TOKEN MATCHING YOURS!")));

	add_option(toggle_option(XOR("Peer Token Corruption"))
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_peer_token_corruption).add_savable(get_submenu_name_stack())
		.add_tooltip(XOR("Players joining with a spoofed peer will get kicked when they get host")));

	add_option(toggle_option(XOR("Randomize Clients"))
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_randomize_clients).add_savable(get_submenu_name_stack())
		.add_tooltip(XOR("New players joining will receive a random name for current players in the session")));

	add_option(button_option(XOR("Migrate Script Host"))
		.add_translate().add_hotkey()
		.add_click([] { force_host_of_script("freemode"); }));

	add_option(scroll_option<int>(SCROLLSELECT, XOR("Host New Session"))
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_transition, 0, NUMOF(transitions), transitions)
		.add_click([] { network::vars::find_new_session(transitions[m_vars.m_transition].m_result); }));

	add_string("Force Script Host");
	add_string("Attempting to migrate host of script");
	add_string("Successfully migrated host of script");
	add_string("Failed migrating host of script");
}

void network_host_toolkit_menu::update() {}

void network_host_toolkit_menu::update_once() {
	menu::panels::toggle_panel_render("PANEL_BLACKLISTED_PLAYERS", false);
}

void network_host_toolkit_menu::feature_update() {}

network_host_toolkit_menu* g_instance;
network_host_toolkit_menu* network_host_toolkit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_host_toolkit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}