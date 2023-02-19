#include "network_join_blocking_edit.h"
#include "menu/base/submenu_handler.h"
#include "network_join_blocking_manual.h"

using namespace network::htoolkit::blocking::edit::vars;

namespace network::htoolkit::blocking::edit::vars {
	variables m_vars;

	scroll_struct<std::pair<std::string, eJoinResponses>> responses[] = {
		{ localization("Failed Intended Session", true), { "Failed to join intended session", FAILED_TO_JOIN_INTENDED_SESSION } },
		{ localization("Failed Intended GTA Session", true), { "Failed to join intended GTA Online session", FAILED_TO_JOIN_INTENDED_GTA_ONLINE_SESSION } },
		{ localization("Incompatible Assets", true), { "Failed to join session due to incompatible assets", FAILED_TO_JOIN_DUE_TO_INCOMPATIBLE_ASSETS } },
		{ localization("Incompatible Downloadable Content", true), { "Incompatible downloadable content. All players must have the latest compatibility pack", INCOMPATILBLE_DOWNLOADABLE_CONTENT } },
		{ localization("Currently Full", true), { "The session you're trying to join is currently full", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_CURRENTLY_FULL } },
		{ localization("Currently Full - Queue", true), { "The session you're trying to join is currently full of players", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_CURRENTLY_FULL_OF_PLAYERS_DO_YOU_WANT_TO_JOIN_QUEUE } },
		{ localization("Wrong Version (Title Update)", true), { "Please make sure all players have the latest Title Update", PLEASE_MAKE_SURE_ALL_PLAYERS_HAVE_THE_LATEST_TITLE_UPDATE } },
		{ localization("Voted Out", true), { "You have already been voted out of this game session", YOU_HAVE_BEEN_VOTED_OUT } },
		{ localization("Invites are Disabled", true), { "Invites are currently disabled in the session", INVITES_ARE_CURRENTLY_DISABLED_IN_THIS_SESSION } },
		{ localization("Active Crew Limit", true), { "The session you are trying to join has an active Crew limit and cannot accommodate your Crew", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_HAS_AN_ACTIVE_CREW_LIMIT } },
		{ localization("You are Bad Sport", true), { "The session you are trying to join is for people who are not Bad Sports or cheaters - you are a Bad Sport", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_FOR_PEOPLE_WHO_ARE_NOT_BADSPORT_OR_CHEATERS_YOU_ARE_BADSPORT } },
		{ localization("Cheat", true), { "You are classed as a cheat and can only play with other cheats until you are forgiven", YOU_ARE_CLASSED_AS_A_CHEAT_AND_CAN_ONLY_PLAY_WITH_OTHER_CHEATS_UNTIL_YOU_ARE_FORGIVEN } },
		{ localization("Cheaters Only", true), { "The session you are trying to join is for cheaters only", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_FOR_CHEATERS_ONLY } },
		{ localization("Bad Sport Only", true), { "The session you are trying to join is for Bad Sports only", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_FOR_BADSPORTS_ONLY } },
		{ localization("Session No Longer Exists", true), { "The session you are trying to join no longer exists", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_NO_LONGER_EXISTS } },
		{ localization("Invite Only", true), { "The session you are trying to join is private. You will need to be invited to join this session", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_PRIVATE } },
		{ localization("Friends Only", true), { "The session you are trying to join is friends only", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_FRIENDS_ONLY } },
		{ localization("Different Targeting Preference", true), { "The session you are trying to join is using a different targeting preference. You can change your preference in the Settings tab of the Pause Menu in Grand Theft Auto V. Joining a new GTA Online Session", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_USING_A_DIFFERENT_TARGETING_PREFERENCE } },
		{ localization("Different Build Type", true), { "The session you are trying to join is a different build type", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_A_DIFFERENT_BUILD_TYPE } },
		{ localization("Different Content", true), { "The session you are trying to join is not using the same content", THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_NOT_USING_THE_SAME_CONTENT } },
		{ localization("Bad Reputation", true), { "Unable to join this session, your account has a bad reputation", UNABLE_TO_JOIN_THIS_SESSION_YOUR_ACCOUNT_HAS_A_BAD_REPUTATION } },
		{ localization("Unable To Connect", true), { "Unable to connect to session. The session may no longer exist", UNABLE_TO_CONNECT_TO_SESSION } },
		{ localization("Premium Race", true), { "Unable to Join. The session you are trying to join is a Premium Race. Joining and accepting invites is disabled for this mode", UNABLE_TO_JOIN_THE_SESSION_YOU_ARE_TRYING_TO_JOIN_IS_A_PREMIUM_RACE } },
	};
}

void network_join_blocking_edit_menu::load() {
	set_parent<network_join_blocking_menu>();

	add_string("Block");
	add_string("Notify");
	add_string("Response Message");

	for (scroll_struct<std::pair<std::string, eJoinResponses>>& response : responses) {
		add_string(response.m_result.first);
	}
}

void network_join_blocking_edit_menu::update() {}

void network_join_blocking_edit_menu::update_once() {
	clear_options(0);

	add_option(toggle_option(get_string("Block"))
		.add_toggle(m_vars.m_selected->m_enabled));

	add_option(toggle_option(get_string("Notify"))
		.add_toggle(m_vars.m_selected->m_notify));

	add_option(break_option(get_string("Response Message")));

	int last_index = m_vars.m_selected->m_context.m_selected;
	m_vars.m_selected->m_context.reset();
	m_vars.m_selected->m_context.m_selected = 0;

	std::vector<std::shared_ptr<radio_option>> temp_options;

	for (scroll_struct<std::pair<std::string, eJoinResponses>>& response : responses) {
		temp_options.push_back(add_option(radio_option(response.m_name.get())
			.add_radio(m_vars.m_selected->m_context)
			.add_tooltip(get_string(response.m_result.first))));
	}

	if (last_index > 0) {
		temp_options[last_index]->update_selected();
	}
}

void network_join_blocking_edit_menu::feature_update() {}

network_join_blocking_edit_menu* g_instance;
network_join_blocking_edit_menu* network_join_blocking_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_blocking_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}