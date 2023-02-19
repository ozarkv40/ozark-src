#include "hooks.h"
#include "menu/base/submenus/main/protection/protection_limits.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/misc/misc_disables.h"
#include "menu/base/submenus/main/network/network_global_chat.h"
#include "menu/base/submenus/main/network/chat/network_global_chat_ozark.h"
#include "menu/base/submenus/main/network/players/network_players_commands.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "menu/base/util/helpers.h"
#include "util/caller.h"
#include "util/util.h"
#include "util/log.h"
#include "util/memory/memory.h"
#include "global/lists.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"
#include <sstream>

static localization t_spoofing_chat_to("Spoofing chat message to", true, true);
static localization t_spoofing_text_to("Spoofing text message to", true, true);

Player get_player_id_from_chat_token(uint64_t token) {
	Player id = -1;

	menu::player::for_each([&](menu::player::player_context& player) {
		if (menu::helpers::is_valid_net_player(player.m_net_player)) {
			if (player.m_connected) {
				if (player.m_net_player->m_player_info->m_chat_token == token) {
					id = player.m_id;
				}
			}
		}
	}, true, true);

	return id;
}

bool menu::hooks::read_chat_message(rage::network::global_msg_context* context, rage::bit_buffer* bit_buffer) {
	bool _return = read_chat_message_t(context, bit_buffer);
	if (!_return) return _return;

	if (protection::limits::vars::m_vars.m_chat_message.m_block_all) {
		context->m_sender_chat_token = 0;
		return true;
	}

	bool spoofed = false;
	uint64_t real_token = 0;

	Player sender_id = menu::helpers::get_net_msg_sender(bit_buffer->m_raw_buffer);
	if (sender_id != -1) {
		Player token_id = get_player_id_from_chat_token(context->m_sender_chat_token);
		if (token_id != -1) {
			if (sender_id != token_id) {
				spoofed = true;

				menu::player::player_context& player = menu::player::get_player(sender_id);
				if (protection::events::vars::m_vars.m_show_real_chat_sender) {
					if (menu::helpers::is_valid_net_player(player.m_net_player)) {
						context->m_sender_chat_token = player.m_net_player->m_player_info->m_chat_token;
						real_token = player.m_net_player->m_player_info->m_chat_token;
					}
				}

				if (protection::events::vars::m_vars.m_spoofed_messages.notify()) {
					menu::notify::protection(player.m_name, util::va::va("%s %s", TRANSLATE(t_spoofing_chat_to), menu::player::get_player(token_id).m_name.c_str()), false, protection::limits::vars::m_vars.m_chat_message.m_block_spoofed);
				}

				if (protection::limits::vars::m_vars.m_chat_message.m_block_spoofed) {
					context->m_sender_chat_token = 0;
					return true;
				}
			}
		}

		static std::unordered_map<int, uint32_t> limits;
		if ((GetTickCount() - limits[sender_id]) < global::lists::g_timers[protection::limits::vars::m_vars.m_chat_message.m_delay].m_result) {
			context->m_sender_chat_token = 0;
			return true;
		}

		limits[sender_id] = GetTickCount();

		// OZARK
		/*if (context->m_message[0] == 1 && context->m_message[1] == 2) {
			if (menu::player::get_player(sender_id).m_ozark) {
				if (!spoofed) {
					real_token = context->m_sender_chat_token;
				} else {
					if (real_token == 0) {
						context->m_sender_chat_token = 0;
						return true;
					}
				}

				rage::network::chat_config* config = *(rage::network::chat_config**)global::vars::g_chat_config;
				config->m_override_gxt = joaat("ozark");

				global::vars::g_hack_patches["CHAT"].m_patch[1] = context->m_message[2];
				memory::write_vector(global::vars::g_hack_patches["CHAT"].m_address, global::vars::g_hack_patches["CHAT"].m_patch);

				caller::call<void>(global::vars::g_add_chat_message, config, config, &real_token, context->m_message + 3, true);

				config->m_override_gxt = 0;

				global::vars::g_hack_patches["CHAT"].m_patch[1] = 1;
				memory::write_vector(global::vars::g_hack_patches["CHAT"].m_address, global::vars::g_hack_patches["CHAT"].m_patch);
			}

			context->m_sender_chat_token = 0;
			return true;
		}*/

		std::string spoof = "";
		if (spoofed) {
			protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SPOOFED_CHAT, sender_id);
			spoof = "[Spoofed to " + menu::player::get_player(token_id).m_name + "]";
		} else {
			std::istringstream buffer(context->m_message);
			std::istream_iterator<std::string> begin(buffer), end;
			std::vector<std::string> tokens(begin, end);

			if (!tokens.empty()) {
				if (tokens.at(0).at(0) == '?' && tokens.at(0).length() > 1) {
					network::players::commands::vars::call_command((tokens.at(0).data() + 1), menu::player::get_player(sender_id).m_net_player, tokens);
				}
			}
		}

		LOG_CUSTOM("Chat", "[%s]%s %s", menu::player::get_player(sender_id).m_name.c_str(), spoof.c_str(), context->m_message);

		if (network::gchat::vars::m_vars.m_mocking) {
			rage::network::global_chat_raw* data = (rage::network::global_chat_raw*)(*(uint64_t*)(global::vars::g_global_chat_ptr) + 0x78);
			rage::network::chat_config* config = *(rage::network::chat_config**)global::vars::g_chat_config;

			rage::network::global_msg_context* new_context = new rage::network::global_msg_context();
			memcpy(new_context, context, sizeof(rage::network::global_msg_context));

			new_context->m_sender_chat_token = menu::player::get_local_player().m_net_player->m_player_info->m_chat_token;
			strcpy_s(new_context->m_message, util::mock_string(new_context->m_message).c_str());

			if (network::gchat::vars::m_vars.m_mocking_type == 0) {
				send_global_chat_message(data->m_manager_ptr, network::gchat::vars::get_key_from_player(sender_id), new_context, 0, 0);
			} else {
				menu::player::for_each([=] (menu::player::player_context& player) {
					if (player.m_id == menu::player::get_local_player().m_id) return;
					send_global_chat_message(data->m_manager_ptr, network::gchat::vars::get_key_from_player(player.m_id), new_context, 0, 0);
				}, true, true);
			}

			util::fiber::pool::add([=] {
				util::fiber::sleep(250);
				caller::call<void>(global::vars::g_add_chat_message, config, config, &new_context->m_sender_chat_token, new_context->m_message, false);
				delete new_context;
			});
		}
	}

	if (misc::disables::vars::m_vars.m_disable_chat_on_open) {
		if (menu::base::is_open()) {
			context->m_sender_chat_token = 0;
			return true;
		}
	}

	return _return;
}

bool menu::hooks::receive_text_message(rage::network::net_msg_text_message* identifier, rage::bit_buffer* bit_buffer) {
	bool _return = receive_text_message_t(identifier, bit_buffer);
	if (!_return)
		return _return;

	if (protection::limits::vars::m_vars.m_text_message.m_block_all)
		return false;

	bool spoofed = false;
	uint64_t real_rid = 0;

	Player sender_id = menu::helpers::get_net_msg_sender(bit_buffer->m_raw_buffer);
	if (sender_id != -1) {
		Player token_id = menu::helpers::get_player_from_rid(identifier->m_sender.m_rockstar_id).m_id;
		if (token_id != -1) {
			if (sender_id != token_id) {
				spoofed = true;

				menu::player::player_context& player = menu::player::get_player(sender_id);
				if (protection::events::vars::m_vars.m_show_real_chat_sender) {
					if (menu::helpers::is_valid_net_player(player.m_net_player)) {
						identifier->m_sender.m_rockstar_id = player.m_net_player->m_player_info->m_identifier.m_rockstar_id;
						real_rid = player.m_net_player->m_player_info->m_identifier.m_rockstar_id;
					}
				}

				if (protection::events::vars::m_vars.m_spoofed_messages.notify()) {
					menu::notify::protection(player.m_name, util::va::va("%s %s", TRANSLATE(t_spoofing_text_to), menu::player::get_player(token_id).m_name.c_str()), false, protection::limits::vars::m_vars.m_text_message.m_block_spoofed);
				}

				if (protection::limits::vars::m_vars.m_text_message.m_block_spoofed)
					return false;
			}
		}

		static std::unordered_map<int, uint32_t> limits;
		if ((GetTickCount() - limits[sender_id]) < global::lists::g_timers[protection::limits::vars::m_vars.m_text_message.m_delay].m_result) {
			return false;
		}

		limits[sender_id] = GetTickCount();

		std::string spoof = "";
		if (spoofed) {
			protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SPOOFED_TEXT, sender_id);
			spoof = "[Spoofed to " + menu::player::get_player(token_id).m_name + "]";
		}

		LOG_CUSTOM("Text", "[%s]%s %s", menu::player::get_player(sender_id).m_name.c_str(), spoof.c_str(), identifier->m_message);
	}

	return _return;
}

void menu::hooks::send_global_chat_message(uint64_t manager, int key, rage::network::global_msg_context* context, uint64_t unk1, uint64_t unk2) {
	/*if (network::gchat::ozark::vars::m_vars.m_enabled) {
		if (!network::gchat::ozark::vars::m_vars.m_prefix.empty()) {
			if ((context->m_message[0] == 1 && context->m_message[1] == 2) || std::string(context->m_message).find(network::gchat::ozark::vars::m_vars.m_prefix + " ") == 0) {
				Player id = network::gchat::vars::get_player_from_key(key);
				if (id != -1) {
					if (network::gchat::vars::can_send_to_player(id)) {
						if (menu::player::get_player(id).m_ozark) {
							if (!(context->m_message[0] == 1 && context->m_message[1] == 2)) {
								char msg[0x100];
								strcpy_s(msg, std::string(context->m_message + network::gchat::ozark::vars::m_vars.m_prefix.size() + 1).c_str());

								context->m_message[0] = 1;
								context->m_message[1] = 2;
								context->m_message[2] = network::gchat::ozark::vars::colors[network::gchat::ozark::vars::m_vars.m_color].m_result;
								strcpy(context->m_message + 3, msg);
								LOG(XOR("Sending Ozark chat - %s"), msg);
							}

							return send_global_chat_message_t(manager, key, context, unk1, unk2);
						}
					}
				}

				return;
			}
		}
	}*/

	LOG_DEV("Sending chat message to %i", key);
	context->m_sender_chat_token = network::gchat::vars::get_sender_chat_token(context->m_sender_chat_token);
	LOG_DEV("Chat token: %llx", context->m_sender_chat_token);

	Player id = network::gchat::vars::get_player_from_key(key);
	if (id != -1) {
		if (!network::gchat::vars::can_send_to_player(id)) {
			LOG_DEV("Preventing message send");
			return;
		}
	}

	return send_global_chat_message_t(manager, key, context, unk1, unk2);
}