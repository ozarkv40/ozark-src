#include "hooks.h"
#include "menu/base/submenus/main/network/spoofing/crew/network_spoofing_crew_name.h"
#include "menu/base/submenus/main/network/spoofing/crew/network_spoofing_crew_tag.h"
#include "menu/base/submenus/main/network/spoofing/crew/network_spoofing_crew_motto.h"
#include "menu/base/submenus/main/network/spoofing/crew/network_spoofing_crew_rank.h"
#include "menu/base/submenus/main/network/spoofing/crew/network_spoofing_crew_icon.h"
#include "menu/base/util/player_manager.h"
#include "util/log.h"

bool menu::hooks::write_player_gamer_data_node(rage::network::player_gamer_data_node* node, rage::bit_buffer_sync_instance* buffer) {
	if (buffer->m_type == 2) {
		rage::network::sync_tree* player_sync_tree = *(rage::network::sync_tree**)((uint64_t)node + 0x18);
		if (player_sync_tree) {
			rage::network::net_object* object = player_sync_tree->m_object;
			if (object) {
				if (object->m_owner == menu::player::get_local_player().m_id) {
					if (!network::spoofing::crew::name::vars::m_vars.m_spoofed_name.empty()) {
						strcpy(node->m_crew_name, network::spoofing::crew::name::vars::m_vars.m_spoofed_name.c_str());
					}

					if (!network::spoofing::crew::tag::vars::m_vars.m_spoofed_name.empty()) {
						strcpy(node->m_crew_abbr, network::spoofing::crew::tag::vars::m_vars.m_spoofed_name.c_str());
					}

					if (!network::spoofing::crew::motto::vars::m_vars.m_spoofed_name.empty()) {
						strcpy(node->m_crew_motto, network::spoofing::crew::motto::vars::m_vars.m_spoofed_name.c_str());
					}

					if (!network::spoofing::crew::rank::vars::m_vars.m_spoofed_name.empty()) {
						strcpy(node->m_crew_rank, network::spoofing::crew::rank::vars::m_vars.m_spoofed_name.c_str());
					}

					if (network::spoofing::crew::icon::vars::m_vars.m_spoofed_icon != -1) {
						node->m_crew_id = network::spoofing::crew::icon::vars::m_vars.m_spoofed_icon;
					}
				}
			}
		}
	}

	return write_player_gamer_data_node_t(node, buffer);
}