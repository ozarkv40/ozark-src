#include "hooks.h"
#include "util/log.h"
#include "util/json.h"
#include "rage/invoker/natives.h"
#include "menu/base/submenus/main/protection/protection_presence_events.h"

static localization t_presence_text_message("Presence: Text Message", true, true);
static localization t_presence_crew_message("Presence: Crew Message", true, true);
static localization t_presence_game_invite("Presence: Game Invite", true, true);
static localization t_presence_server_rewards("Presence: Server Rewards", true, true);
static localization t_presence_admin_invite("Presence: Admin Invite", true, true);
static localization t_presence_stat_update("Presence: Stat Update", true, true);

bool menu::hooks::receive_presence_event(uint64_t rcx, uint64_t rdx, const char** payload, uint64_t r9) {
	LOG_DEV(*payload);

	try {
		const char* key = "gm.evt";

		nlohmann::json json = nlohmann::json::parse(*payload);
		if (json[key].is_null()) {
			if (json["gta5.game.event"].is_null()) {
				return true;
			}

			key = "gta5.game.event";
		}

		nlohmann::json& event_payload = json[key];
		if (event_payload["e"].is_null() || event_payload["d"].is_null()) {
			return true;
		}

		uint32_t presence_hash = native::get_hash_key(event_payload["e"].get<std::string>().c_str());
		switch (presence_hash) {
			case PRESENCE_TEXT_MESSAGE: {
				if (protection::events::presence::vars::m_vars.m_text_message.notify()) {
					menu::notify::protection("LLLLLLLLLLLLLLLLLLLLLLLL", TRANSLATE(t_presence_text_message), false, protection::events::presence::vars::m_vars.m_text_message.block());
				}

				if (protection::events::presence::vars::m_vars.m_text_message.block()) {
					return true;
				}

				break;
			}

			case PRESENCE_CREW_MESSAGE: {
				if (protection::events::presence::vars::m_vars.m_crew_message.notify()) {
					menu::notify::protection("LLLLLLLLLLLLLLLLLLLLLLLL", TRANSLATE(t_presence_crew_message), false, protection::events::presence::vars::m_vars.m_crew_message.block());
				}

				if (protection::events::presence::vars::m_vars.m_crew_message.block()) {
					return true;
				}

				break;
			}

			case PRESENCE_GAME_INVITE: {
				std::string name = "LLLLLLLLLLLLLLLLLLLLLLLL";
				if (!event_payload["d"]["n"].is_null()) {
					name = event_payload["d"]["n"];
				}

				if (protection::events::presence::vars::m_vars.m_game_invite.notify()) {
					menu::notify::protection(name, TRANSLATE(t_presence_game_invite), false, protection::events::presence::vars::m_vars.m_game_invite.block());
				}

				if (protection::events::presence::vars::m_vars.m_game_invite.block()) {
					return true;
				}

				break;
			}

			case PRESENCE_GAME_SERVER: {
				if (protection::events::presence::vars::m_vars.m_game_server_awards.notify()) {
					menu::notify::protection("LLLLLLLLLLLLLLLLLLLLLLLL", TRANSLATE(t_presence_server_rewards), false, protection::events::presence::vars::m_vars.m_game_server_awards.block());
				}

				if (protection::events::presence::vars::m_vars.m_game_server_awards.block()) {
					return true;
				}

				break;
			}

			case PRESENCE_ADMIN_INVITE: {
				if (protection::events::presence::vars::m_vars.m_admin_invite.notify()) {
					menu::notify::protection("LLLLLLLLLLLLLLLLLLLLLLLL", TRANSLATE(t_presence_admin_invite), false, protection::events::presence::vars::m_vars.m_admin_invite.block());
				}

				if (protection::events::presence::vars::m_vars.m_admin_invite.block()) {
					return true;
				}

				break;
			}

			case PRESENCE_STAT_UPDATE: {
				std::string name = "LLLLLLLLLLLLLLLLLLLLLLLL";
				if (!event_payload["d"]["from"].is_null()) {
					name = event_payload["d"]["from"];
				}

				if (protection::events::presence::vars::m_vars.m_stat_update.notify()) {
					menu::notify::protection(name, TRANSLATE(t_presence_stat_update), false, protection::events::presence::vars::m_vars.m_stat_update.block());
				}

				if (protection::events::presence::vars::m_vars.m_stat_update.block()) {
					return true;
				}

				break;
			}
		}
	} catch (...) {
		return true;
	}

	return receive_presence_event_t(rcx, rdx, payload, r9);
}