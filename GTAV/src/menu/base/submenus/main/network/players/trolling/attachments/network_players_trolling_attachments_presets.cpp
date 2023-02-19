#include "network_players_trolling_attachments_presets.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_trolling_attachments.h"
#include "menu/base/util/control.h"

using namespace network::players::trolling::attachments::presets::vars;

namespace network::players::trolling::attachments::presets::vars {
	variables m_vars;

	void attach(uint32_t model, menu::player::player_context& player, int bone, math::vector3<float> pos, math::vector3<float> rot) {
		Entity object = native::create_object(model, pos.x, pos.y, pos.z, true, true, false);
		if (native::does_entity_exist(object)) {
			native::attach_entity_to_entity(object, player.m_ped, bone, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, true, true, false, true, 1, true);
		}
	}

	void rocket_cock() {
		menu::control::request_model(joaat("prop_ld_bomb_01"), [=] (uint32_t model) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				attach(model, menu::player::get_selected_player(), 0, { 0.0f, 0.5f, -0.17f }, { 180.0f, 0.0f, 0.0f });
			} else {
				menu::player::for_each([=] (menu::player::player_context& player) {
					attach(model, player, 0, { 0.0f, 0.5f, -0.17f }, { 180.0f, 0.0f, 0.0f });
				});
			}
		});
	}

	void snowman() {
		menu::control::request_model(joaat("prop_prlg_snowpile"), [=] (uint32_t model) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				attach(model, menu::player::get_selected_player(), native::get_ped_bone_index(menu::player::get_selected_player().m_ped, 0xE0FD), { -0.2f, 0.0f, 0.05f }, { 0.0f, 90.0f, -90.0f });
			} else {
				menu::player::for_each([=] (menu::player::player_context& player) {
					attach(model, player, native::get_ped_bone_index(player.m_ped, 0xE0FD), { -0.2f, 0.0f, 0.05f }, { 0.0f, 90.0f, -90.0f });
				});
			}
		});
	}
}

void network_players_trolling_attachments_presets_menu::load() {
	set_name("Presets");
	set_parent<network_players_trolling_attachments_menu>();

	add_option(button_option("Rocket Cock")
		.add_translate()
		.add_click(rocket_cock));

	add_option(button_option("Snowman")
		.add_translate()
		.add_click(snowman));
}

void network_players_trolling_attachments_presets_menu::update() {}

void network_players_trolling_attachments_presets_menu::update_once() {}

void network_players_trolling_attachments_presets_menu::feature_update() {}

network_players_trolling_attachments_presets_menu* g_instance;
network_players_trolling_attachments_presets_menu* network_players_trolling_attachments_presets_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_trolling_attachments_presets_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}