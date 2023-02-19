#include "network_global_chat.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "util/caller.h"
#include "util/log.h"
#include "rage/engine.h"
#include "chat/network_global_chat_presets.h"
#include "chat/network_global_chat_targets.h"
#include "chat/network_global_chat_ozark.h"
#include <random>

using namespace network::gchat::vars;

namespace network::gchat::vars {
	variables m_vars;

	scroll_struct<int> mocking[] = {
		{ localization("Send to Sender Only", true), 0 },
		{ localization("Send to Session", true), 0 },
	};

	uint64_t get_sender_chat_token(uint64_t _default) {
		uint64_t token = _default;

		if (_default == 0) {
			if (menu::player::get_local_player().m_net_player) {
				if (menu::player::get_local_player().m_net_player->m_player_info) {
					token = menu::player::get_local_player().m_net_player->m_player_info->m_chat_token;
				}
			}
		}

		if (m_vars.m_randomize_sender) {
			menu::player::player_context& player = menu::player::random(menu::player::get_local_player().m_id);
			if (player.m_connected) {
				if (player.m_net_player) {
					if (player.m_net_player->m_player_info) {
						return player.m_net_player->m_player_info->m_chat_token;
					}
				}
			}
		}

		if (m_vars.m_sender_toggle) {
			menu::player::player_context& player = menu::player::get_player(m_vars.m_sender_id);

			if (player.m_net_player) {
				if (player.m_net_player->m_player_info) {
					return player.m_net_player->m_player_info->m_chat_token;
				}
			}

			m_vars.m_sender_toggle = false;
			m_vars.m_sender = 0;

			network_global_chat_menu* _this = network_global_chat_menu::get();
			menu::notify::stacked(_this->get_string("Global Chat Spoof"), _this->get_string("Spoof sender disabled, player is no longer valid"), global::ui::g_error);
		}

		return token;
	}

	Player get_player_from_key(int key) {
		rage::network::global_chat_raw* data = (rage::network::global_chat_raw*)(*(uint64_t*)(global::vars::g_global_chat_ptr) + 0x78);
		if (!is_valid_ptr(data->m_manager_ptr)) return -1;

		std::vector<std::pair<uint64_t, Player>> users;
		menu::player::for_each([&](menu::player::player_context& player) {
			if (player.m_net_player) {
				if (player.m_net_player->m_player_info) {
					rage::network::network_base_config* real_config = global::vars::g_network_base_config;
					if (global::vars::g_steam) {
						real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
					}

					uint64_t config = caller::call<uint64_t>(global::vars::g_get_network_config_from_peer, real_config->m_unk_ptr, player.m_net_player->m_player_info->m_host_token);
					if (config) {
						uint64_t yes = caller::call<uint64_t>(global::vars::g_get_player_info_from_net_msg, data->m_manager_ptr, *(uint32_t*)config);
						if (yes) {
							users.push_back({ *(uint64_t*)(yes + 0xD8), player.m_id });
						}
					}
				}
			}
		});

		uint64_t ptr = caller::call<uint64_t>(global::vars::g_get_player_info_from_net_msg, data->m_manager_ptr, key);
		if (ptr) {
			auto vit = std::find_if(begin(users), end(users), [=](std::pair<uint64_t, Player> yes) { return yes.first == ptr; });
			if (vit != end(users)) {
				return vit->second;
			}
		}

		return -1;
	}

	int get_key_from_player(Player id) {
		rage::network::global_chat_raw* data = (rage::network::global_chat_raw*)(*(uint64_t*)(global::vars::g_global_chat_ptr) + 0x78);

		std::vector<std::pair<uint64_t, Player>> users;
		menu::player::for_each([&](menu::player::player_context& player) {
			if (player.m_net_player) {
				if (player.m_net_player->m_player_info) {
					rage::network::network_base_config* real_config = global::vars::g_network_base_config;
					if (global::vars::g_steam) {
						real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
					}

					uint64_t config = caller::call<uint64_t>(global::vars::g_get_network_config_from_peer, real_config->m_unk_ptr, player.m_net_player->m_player_info->m_host_token);
					if (config) {
						uint64_t yes = caller::call<uint64_t>(global::vars::g_get_player_info_from_net_msg, data->m_manager_ptr, *(uint32_t*)config);
						if (yes) {
							users.push_back({ *(uint64_t*)(yes + 0xD8), player.m_id });
						}
					}
				}
			}
		});

		if (data->m_player_count > 0) {
			for (int i = 0; i < data->m_player_count; i++) {
				rage::network::player_peer* peer = data->m_player_peers[i];
				if (peer) {
					if ((peer->get_bitset() & 2) == 0 && (peer->get_bitset() & 1) != 0 && (data->m_flag0 != -1 || peer->get_flag())) {
						int key = peer->get_player_key();
						if (key < 0) {
							key = caller::call<int>(global::vars::g_get_client_player_key, data->m_manager_ptr, peer->get_secondary_key(), (data->m_bitset & 1) ? data->m_flag2 : data->m_flag1);
						}

						if (key > 0) {
							uint64_t ptr = caller::call<uint64_t>(global::vars::g_get_player_info_from_net_msg, data->m_manager_ptr, key);
							if (ptr) {
								auto vit = std::find_if(begin(users), end(users), [=](std::pair<uint64_t, Player> yes) { return yes.first == ptr; });
								if (vit != end(users)) {
									if (vit->second == id) {
										return key;
									}
								}
							}
						}
					}
				}
			}
		}

		return 0;
	}

	bool can_send_to_player(Player id) {
		if (!network::gchat::targets::vars::m_vars.m_enabled) return true;
		return menu::player::get_player(id).m_chat_target;
	}

	void send_message(std::string str, int count, bool locally) {
		rage::network::global_chat_raw* data = (rage::network::global_chat_raw*)(*(uint64_t*)(global::vars::g_global_chat_ptr) + 0x78);
		if (!is_valid_ptr(data->m_manager_ptr)) {
			LOG_DEV("Manager ptr is bad");
			return;
		}

		rage::network::global_msg_context* context = new rage::network::global_msg_context();
		context->m_message[0xff] = 0;
		context->m_flag0_is_neg1 = data->m_flag0 == -1;
		strncpy(context->m_message, str.c_str(), 0x100);

		std::vector<uint64_t> senders;

		LOG_DEV("Players: %i", data->m_player_count);
		if (data->m_player_count > 0) {
			for (int i = 0; i < count; i++) {
				senders.push_back(get_sender_chat_token(0));
			}

			for (int i = 0; i < data->m_player_count; i++) {
				rage::network::player_peer* peer = data->m_player_peers[i];
				if (peer) {
					if ((peer->get_bitset() & 2) == 0 && (peer->get_bitset() & 1) != 0 && (data->m_flag0 != -1 || peer->get_flag())) {
						int key = peer->get_player_key();
						if (key < 0) {
							key = caller::call<int>(global::vars::g_get_client_player_key, data->m_manager_ptr, peer->get_secondary_key(), (data->m_bitset & 1) ? data->m_flag2 : data->m_flag1);
						}

						if (key > 0) {
							Player player_id = get_player_from_key(key);
							if (player_id == -1) continue;

							if (can_send_to_player(player_id)) {
								for (int j = 0; j < count; j++) {
									context->m_sender_chat_token = senders[j];
									rage::engine::send_global_chat_message(data->m_manager_ptr, key, context);
								}
							}
						} else LOG_DEV("Bad key for peer %i", i);
					} else LOG_DEV("Bad flags for peer %i", i);
				} else LOG_DEV("Bad peer for %i", i);
			}

			if (locally) {
				for (int i = 0; i < count; i++) {
					context->m_sender_chat_token = senders[i];

					rage::network::chat_config* config = *(rage::network::chat_config**)global::vars::g_chat_config;
					caller::call<void>(global::vars::g_add_chat_message, config, config, &context->m_sender_chat_token, context->m_message, false);
				}
			}
		}

		delete context;
	}
}

void network_global_chat_menu::load() {
	set_name("Global Chat");
	set_parent<network_menu>();

	// [s] Custom Messages

	add_option(submenu_option("Presets")
		.add_translate().add_hotkey()
		.add_submenu<network_global_chat_presets_menu>());

	add_option(submenu_option("Modify Targets")
		.add_translate().add_hotkey()
		.add_submenu<network_global_chat_targets_menu>()
		.add_tooltip("Global chat and messages sent from here will only be sent to these specific players"));

	/*add_option(submenu_option("Ozark Chat")
		.add_translate().add_hotkey()
		.add_submenu<network_global_chat_ozark_menu>());*/

	add_option(scroll_option<int>(TOGGLE, "Spoof Sender")
		.add_translate()
		.add_toggle(m_vars.m_sender_toggle)
		.add_click([] {
			if (m_vars.m_sender_toggle) {
				m_vars.m_randomize_sender = false;
				m_vars.m_sender_id = m_vars.m_player_list[m_vars.m_sender].m_result;
			}
		})
		.add_scroll(m_vars.m_sender, 0, NUMOF(m_vars.m_player_list), m_vars.m_player_list)
		.add_update([](scroll_option<int>* option, int pos) { option->add_scroll(m_vars.m_sender, 0, m_vars.m_list_size, m_vars.m_player_list); })
		.add_requirement([] { return m_vars.m_list_size >= 1; }));

	add_option(toggle_option("Randomize Sender")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_randomize_sender)
		.add_click([] { m_vars.m_sender_toggle = false; })
		.add_requirement([] { return m_vars.m_list_size >= 1; }));

	add_option(scroll_option<int>(TOGGLE, "Mocking")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_mocking)
		.add_scroll(m_vars.m_mocking_type, 0, NUMOF(mocking), mocking).add_savable(get_submenu_name_stack())
		.add_tooltip("Mock what everyone says in chat.\nExample: \"hey everyone\" becomes \"hEy EvERyOnE\""));

	add_string("Global Chat Spoof");
	add_string("Spoof sender disabled, player is no longer valid");
}

void network_global_chat_menu::update() {}

void network_global_chat_menu::update_once() {}

void network_global_chat_menu::feature_update() {
	m_vars.m_list_size = 0;
	menu::player::for_each([&](menu::player::player_context& player) {
		m_vars.m_player_list[m_vars.m_list_size].m_name.set(player.m_name);
		m_vars.m_player_list[m_vars.m_list_size].m_result = player.m_id;

		if (m_vars.m_sender_toggle) {
			if (m_vars.m_sender_id == player.m_id) {
				m_vars.m_sender = m_vars.m_list_size;
			}
		}

		m_vars.m_list_size++;
	});

	if (m_vars.m_sender_toggle) {
		if (!menu::player::get_player(m_vars.m_sender_id).m_connected) {
			m_vars.m_sender_toggle = false;
			m_vars.m_sender = 0;
			menu::notify::stacked(get_string("Global Chat Spoof"), get_string("Spoof sender disabled, player is no longer valid"), global::ui::g_error);
		}
	}

	if (m_vars.m_list_size == 0) {
		m_vars.m_sender_toggle = false;
		m_vars.m_randomize_sender = false;
	}
}

network_global_chat_menu* g_instance;
network_global_chat_menu* network_global_chat_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_global_chat_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}