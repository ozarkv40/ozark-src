#include "network_players_text.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "menu/base/util/helpers.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_name.h"
#include "text/network_players_text_presets.h"
#include "text/network_players_text_save.h"
#include "menu/base/submenus/main/network/network_session.h"

using namespace network::players::text::vars;

namespace network::players::text::vars {
	variables m_vars;

	scroll_struct<const char*> text_fonts[] = {
		{ localization("Default", true), "" },
		{ localization("Chalet Comprime 60", true), "$Font2_cond" },
		{ localization("Sign Painter", true), "$Font5" },
		{ localization("Rockstar Tag", true), "$RockstarTAG" },
		{ localization("Pricedown", true), "$gtaCash" },
		{ localization("Blocky", true), "$WebFont3_Times" },
	};

	scroll_struct<const char*> text_sizes[] = {
		{ localization("Default", true), "" },
		{ localization("Small", true), "10" },
		{ localization("Large", true), "30" },
		{ localization("Larger", true), "40" },
		{ localization("Big", true), "50" },
		{ localization("Massive", true), "70" }
	};

	void send_text_message(menu::player::player_context& player, menu::player::player_context& sender, const char* message) {
		if (!menu::helpers::is_valid_net_player(player.m_net_player)) return;
		if (!menu::helpers::is_valid_net_player(sender.m_net_player)) return;

		rage::network::net_msg_text_message identifier;
		memset(&identifier.m_sender, 0, sizeof(identifier.m_sender));

		identifier.m_sender.m_rockstar_id = sender.m_net_player->m_player_info->m_identifier.m_rockstar_id; // spoofed sender
		identifier.m_sender.m_type = 3;

		rage::network::net_msg_identifier target;
		memset(&target, 0, sizeof(target));

		target.m_rockstar_id = player.m_net_player->m_player_info->m_identifier.m_rockstar_id; // recipient
		target.m_type = 3;

		strncpy_s(identifier.m_message, message, 0x100);
		rage::engine::send_text_message_net_msg(&target, &identifier);
	}
}

void network_players_text_menu::load() {
	set_name("Text Message");
	set_parent<network_players_selected_menu>();

	add_option(submenu_option("Save and Load")
		.add_translate()
		.add_submenu<network_players_text_save_menu>());

	add_option(submenu_option("Presets")
		.add_translate()
		.add_submenu<network_players_text_presets_menu>());

	add_option(button_option("Input Message")
		.add_translate()
		.add_keyboard("Enter the message to send", 100, [] (button_option* option, const char* msg) {
			menu::player::get_selected_player().m_text_message_msg = msg;
		}));

	add_option(scroll_option<const char*>(SCROLL, "Color")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_text_message_color, 0, NUMOF(network::spoofing::name::vars::text_colors), network::spoofing::name::vars::text_colors)
		.add_update([] (scroll_option<const char*>* option, int pos) { option->add_scroll(menu::player::get_selected_player().m_text_message_color, 0, NUMOF(network::spoofing::name::vars::text_colors), network::spoofing::name::vars::text_colors); }));

	add_option(scroll_option<const char*>(SCROLL, "Font")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_text_message_font, 0, NUMOF(text_fonts), text_fonts)
		.add_update([] (scroll_option<const char*>* option, int pos) { option->add_scroll(menu::player::get_selected_player().m_text_message_font, 0, NUMOF(text_fonts), text_fonts); }));

	add_option(scroll_option<const char*>(SCROLL, "Size")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_text_message_size, 0, NUMOF(text_sizes), text_sizes)
		.add_update([] (scroll_option<const char*>* option, int pos) { option->add_scroll(menu::player::get_selected_player().m_text_message_size, 0, NUMOF(text_sizes), text_sizes); }));

	add_option(scroll_option<int>(TOGGLE, "Spoof Sender")
		.add_translate()
		.add_toggle(m_vars.m_sender_toggle)
		.add_click([] {
			m_vars.m_randomize_sender = false;
			m_vars.m_sender_id = m_vars.m_player_list[m_vars.m_sender].m_result;
		})
		.add_scroll(m_vars.m_sender, 0, NUMOF(m_vars.m_player_list), m_vars.m_player_list)
		.add_update([] (scroll_option<int>* option, int pos) { option->add_scroll(m_vars.m_sender, 0, m_vars.m_list_size, m_vars.m_player_list); })
		.add_requirement([] { return m_vars.m_list_size >= 1; }));

	add_option(toggle_option("Randomize Sender")
		.add_translate()
		.add_toggle(m_vars.m_randomize_sender)
		.add_click([] { m_vars.m_sender_toggle = false; })
		.add_requirement([] { return m_vars.m_list_size >= 1; }));

	add_option(number_option<int>(SCROLLSELECT, "Send Message")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_text_message_count, "%i", 1).add_min(1).add_max(100)
		.add_update([] (number_option<int>* option, int pos) { option->add_number(menu::player::get_selected_player().m_text_message_count, "%i", 1); })
		.add_click([] {
			for (int i = 0; i < menu::player::get_selected_player().m_text_message_count; i++) {
				menu::player::player_context& sender = m_vars.m_sender_toggle ? menu::player::get_player(m_vars.m_player_list[m_vars.m_sender].m_result) : menu::player::get_local_player();
				if (m_vars.m_randomize_sender) {
					int max_range = 0;
					menu::player::for_each([&] (menu::player::player_context& player) {
						max_range = player.m_id;
					});

					sender = menu::player::get_player(native::get_random_int_in_range(0, max_range));
				}

				if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
					send_text_message(menu::player::get_selected_player(), sender, menu::player::get_selected_player().m_text_message_final);
				} else {
					menu::player::for_each([&] (menu::player::player_context& player) {
						send_text_message(player, sender, menu::player::get_selected_player().m_text_message_final);
					});
				}
			}
		}));

	add_string("Spoof sender disabled, player is no longer valid");
}

void network_players_text_menu::update() {
	const char* font_face = menu::player::get_selected_player().m_text_message_font > 0 ? text_fonts[menu::player::get_selected_player().m_text_message_font].m_result : "$Font2";
	const char* font_size = menu::player::get_selected_player().m_text_message_size > 0 ? text_sizes[menu::player::get_selected_player().m_text_message_size].m_result : "20";

	if (menu::player::get_selected_player().m_text_message_font == 0 && menu::player::get_selected_player().m_text_message_size == 0) {
		snprintf(menu::player::get_selected_player().m_text_message_final, 100, "%s%s",
			network::spoofing::name::vars::text_colors[menu::player::get_selected_player().m_text_message_color].m_result,
			menu::player::get_selected_player().m_text_message_msg.c_str());
	} else {
		snprintf(menu::player::get_selected_player().m_text_message_final, 100, "<font face=\"%s\" size=\"%s\">%s%s",
			font_face,
			font_size,
			network::spoofing::name::vars::text_colors[menu::player::get_selected_player().m_text_message_color].m_result,
			menu::player::get_selected_player().m_text_message_msg.c_str());
	}

	if (menu::player::get_selected_player().m_text_message_msg.length()) {
		menu::notify::subtitle(menu::player::get_selected_player().m_text_message_final);
	}

	m_vars.m_list_size = 0;
	menu::player::for_each([&] (menu::player::player_context& player) {
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
			menu::notify::stacked(get_name().get(), get_string("Spoof sender disabled, player is no longer valid"), global::ui::g_error);
		}
	}
}

void network_players_text_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}
}

void network_players_text_menu::feature_update() {}

network_players_text_menu* g_instance;
network_players_text_menu* network_players_text_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_text_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}