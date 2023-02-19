#include "protection_events.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"
#include "rage/engine.h"
#include "menu/base/util/helpers.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"

using namespace protection::events::vars;

namespace protection::events::vars {
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
		{ "Player Spawns", &m_vars.m_player_spawns, 2 },
		{ "Player Model Update", &m_vars.m_player_model_update, 2 },
		{ "Spectating", &m_vars.m_spectating, 2 },
		{ "Desync Kicks", &m_vars.m_desync_kicks, 2 },
		{ "Host Kicks", &m_vars.m_host_kicks, 2 },
		{ "Script Host Kicks", &m_vars.m_sh_kick, 4 },
		{ "Script Host Migration", &m_vars.m_sh_migration, 2 },
		{ "Entity Owner Migration", &m_vars.m_entity_owner_migration, 4 },
		{ "Pickup Spawning", &m_vars.m_pickup_spawning, 2 },
		{ "Pickup Processing", &m_vars.m_pickup_processing, 4 },
		{ "Crashing", &m_vars.m_crashing, 2 },
		{ "Cloning", &m_vars.m_clone, 8 },
		{ "Cages", &m_vars.m_cages, 4 },
		{ "Attachments", &m_vars.m_attachments, 4 },
		{ "Rockstar Staff", &m_vars.m_rockstar_staff, 2 },
		{ "Join Timeout", &m_vars.m_join_timeout, 2 },
		{ "Ghost", &m_vars.m_ghost, 4 },
		{ "Spoofed Messages", &m_vars.m_spoofed_messages, 2 },
	};
}

void protection_events_menu::load() {
	set_name("Generic Events");
	set_parent<protection_menu>();

	for (context& c : items) {
		add_string(c.m_name);
		c.m_context->m_var = util::config::read_int(get_submenu_name_stack(), c.m_name, c.m_context->m_var);
	}

	add_string("is spectating");
	add_string("you");
	add_string("Spectating");
	add_string("Replace Spoofed Message Sender");
	add_string("If someone sends a spoofed message it'll force it to show as the real sender");
}

void protection_events_menu::update() {}

void protection_events_menu::update_once() {
	clear_options(0);

	for (context& c : items) {
		add_option(scroll_option<int>(SCROLL, get_string(c.m_name))
			.add_scroll(c.m_context->m_var, 0, c.m_size, types)
			.add_tooltip(c.m_context->m_tooltip.get())
			.add_click([=] { util::config::write_int(get_submenu_name_stack(), c.m_name, c.m_context->m_var); }));
	}

	add_option(toggle_option(get_string("Replace Spoofed Message Sender"))
		.add_toggle(m_vars.m_show_real_chat_sender)
		.add_update([this](toggle_option* option, int pos) { option->set_tooltip(get_string("If someone sends a spoofed message it'll force it to show as the real sender")); }));
}

void protection_events_menu::feature_update() {
	if (m_vars.m_spectating.notify()) {
		menu::player::for_each([this](menu::player::player_context& player) {
			if (player.m_id != menu::player::get_local_player().m_id) {
				if (!native::is_entity_dead(player.m_ped, 0)) {
					if (is_valid_ptr(player.m_ped_ptr)) {
						if (is_valid_ptr(player.m_ped_ptr->get_net_obj())) {
							if (player.m_ped_ptr->get_net_obj()->m_spectating_network_id) {
								rage::network::net_object* object = rage::engine::get_network_object_from_network_id(*(uint64_t*)(global::vars::g_network_object_manager), player.m_ped_ptr->get_net_obj()->m_spectating_network_id, true);
								if (is_valid_ptr(object)) {
									if (object->m_owner >= 0 && object->m_owner < 32) {
										if ((GetTickCount() - m_vars.m_spectate_map[player.m_id][object->m_owner]) > 5000) {
											m_vars.m_spectate_map[player.m_id][object->m_owner] = GetTickCount();

											std::string target = menu::player::get_player(object->m_owner).m_name;
											if (!target.compare(menu::player::get_local_player().m_name)) {
												target = get_string("you");
												protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SPECTATING_YOU, player.m_id);
											}

											menu::notify::stacked(get_string("Spectating"), menu::helpers::clean_name(player.m_name) + " " + get_string("is spectating") + " " + target);
										}

										menu::helpers::flag_modder(player.m_id, menu::player::REASON_SPECTATING, false);
									}
								}
							}
						}
					}
				}
			}
		}, true, true);
	}
}

protection_events_menu* g_instance;
protection_events_menu* protection_events_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_events_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}