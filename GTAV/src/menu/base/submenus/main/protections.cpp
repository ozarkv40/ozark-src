#include "protections.h"
#include "menu/base/submenu_handler.h"
#include "../main.h"
#include "protection/protection_events.h"
#include "protection/protection_net_events.h"
#include "protection/protection_anti_detection.h"
#include "protection/protection_join_blocking.h"
#include "protection/protection_presence_events.h"
#include "protection/protection_limits.h"
#include "protection/protection_entity_events.h"
#include "protection/protection_reactions.h"
#include "protection/entity/protection_entity_blocking.h"

using namespace protection::vars;

namespace protection::vars {
	variables m_vars;

	void enable_all() {
		protection::events::vars::m_vars.m_player_spawns.m_var = 1;
		protection::events::vars::m_vars.m_player_model_update.m_var = 1;
		protection::events::vars::m_vars.m_spectating.m_var = 1;
		protection::events::vars::m_vars.m_desync_kicks.m_var = 1;
		protection::events::vars::m_vars.m_host_kicks.m_var = 1;
		protection::events::vars::m_vars.m_sh_kick.m_var = 3;
		protection::events::vars::m_vars.m_sh_migration.m_var = 1;
		protection::events::vars::m_vars.m_entity_owner_migration.m_var = 3;
		protection::events::vars::m_vars.m_pickup_spawning.m_var = 1;
		protection::events::vars::m_vars.m_pickup_processing.m_var = 3;
		protection::events::vars::m_vars.m_crashing.m_var = 1;
		protection::events::vars::m_vars.m_clone.m_var = 3;
		protection::events::vars::m_vars.m_cages.m_var = 3;
		protection::events::vars::m_vars.m_attachments.m_var = 3;
		protection::events::vars::m_vars.m_rockstar_staff.m_var = 1;
		protection::events::vars::m_vars.m_join_timeout.m_var = 1;
		protection::events::vars::m_vars.m_ghost.m_var = 3;
		protection::events::vars::m_vars.m_spoofed_messages.m_var = 1;

		protection::events::net::vars::m_vars.m_give_weapon.m_var = 3;
		protection::events::net::vars::m_vars.m_remove_weapon.m_var = 3;
		protection::events::net::vars::m_vars.m_remove_all_weapons.m_var = 3;
		protection::events::net::vars::m_vars.m_freeze.m_var = 3;
		protection::events::net::vars::m_vars.m_explosion.m_var = 3;
		protection::events::net::vars::m_vars.m_fire.m_var = 3;
		protection::events::net::vars::m_vars.m_particle_fx.m_var = 3;
		protection::events::net::vars::m_vars.m_script_events.m_var = 3;
		protection::events::net::vars::m_vars.m_increment_stat.m_var = 3;
		protection::events::net::vars::m_vars.m_weather.m_var = 3;
		protection::events::net::vars::m_vars.m_clock.m_var = 3;
		protection::events::net::vars::m_vars.m_sound.m_var = 3;
		protection::events::net::vars::m_vars.m_vehicle_control.m_var = 3;
		protection::events::net::vars::m_vars.m_blame_explosion.m_var = 1;

		protection::joining::vars::m_vars.m_block = true;
		protection::joining::vars::block_resolves();

		protection::detection::vars::m_vars.m_godmode = true;
		protection::detection::vars::m_vars.m_super_jump = true;
		protection::detection::vars::m_vars.m_health = true;
		protection::detection::vars::m_vars.m_armor = true;
		protection::detection::vars::m_vars.m_spectate = true;

		protection::entity::vars::m_vars.m_block_modder_create = true;
		protection::entity::vars::m_vars.m_block_modder_sync = true;

		protection::events::presence::vars::m_vars.m_text_message.m_var = 1;
		protection::events::presence::vars::m_vars.m_crew_message.m_var = 1;
		protection::events::presence::vars::m_vars.m_game_invite.m_var = 1;
		protection::events::presence::vars::m_vars.m_game_server_awards.m_var = 1;
		protection::events::presence::vars::m_vars.m_admin_invite.m_var = 1;
		protection::events::presence::vars::m_vars.m_stat_update.m_var = 1;

		m_vars.m_force_visible = true;
		m_vars.m_disable_bullets = true;
		m_vars.m_disable_projectiles = true;

		// memset(protection::entity::blocking::vars::m_vars.m_toggled, 1, 14);
	}
}

void protection_menu::load() {
	set_name("Protections");
	set_parent<main_menu>();

	add_option(submenu_option("Generic Events")
		.add_translate().add_hotkey()
		.add_submenu<protection_events_menu>());

	add_option(submenu_option("Network Events")
		.add_translate().add_hotkey()
		.add_submenu<protection_net_events_menu>());

	add_option(submenu_option("Join Blocking")
		.add_translate().add_hotkey()
		.add_submenu<protection_join_blocking_menu>());

	add_option(submenu_option("Anti Detection")
		.add_translate().add_hotkey()
		.add_submenu<protection_anti_detection_menu>());

	add_option(submenu_option("Reactions")
		.add_translate().add_hotkey()
		.add_submenu<protection_reactions_menu>());

	add_option(submenu_option("Entity")
		.add_translate().add_hotkey()
		.add_submenu<protection_entity_events_menu>());

	add_option(submenu_option("Presence Events")
		.add_translate().add_hotkey()
		.add_submenu<protection_presence_events_menu>());

	add_option(submenu_option("Limits")
		.add_translate().add_hotkey()
		.add_submenu<protection_limits_menu>());

	add_option(toggle_option("Fake Lag")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fake_lag).add_savable(get_submenu_name_stack())
		.add_tooltip("Jitters your player for other players"));

	add_option(toggle_option("Force Creation Visibility")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_force_visible).add_savable(get_submenu_name_stack())
		.add_tooltip("Forces all entities being created to be visible"));

	add_option(toggle_option("Disable Bullets")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_bullets).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables bullets from other entities"));

	add_option(toggle_option("Disable Projectiles")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_projectiles).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables projectiles from other entities"));

	add_option(button_option("Enable All Protections")
		.add_translate().add_hotkey()
		.add_click(enable_all)
		.add_tooltip("Sets all protections to max level of protection"));
}

void protection_menu::update() {}

void protection_menu::update_once() {}

void protection_menu::feature_update() {
	if (m_vars.m_fake_lag) {
		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				rage::network::net_object* object = global::vars::g_ped_factory->m_local_ped->get_net_obj();
				if (object) {
					memset(object->m_player_sync_intervals, 0, sizeof(object->m_player_sync_intervals));
				}

				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					object = global::vars::g_ped_factory->m_local_ped->m_vehicle->get_net_obj();
					if (object) {
						memset(object->m_player_sync_intervals, 0, sizeof(object->m_player_sync_intervals));
					}
				}
			}
		}
	}
}

protection_menu* g_instance;
protection_menu* protection_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}