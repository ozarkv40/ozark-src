#pragma once
#include "menu/base/submenu.h"

class protection_events_menu : public menu::submenu::submenu {
public:
	static protection_events_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_events_menu()
		: menu::submenu::submenu() {}
};

namespace protection::events::vars {
	struct variables {
		protection_context m_spoofed_messages = { 1, localization("Notifies when a player is sending spoofed chat messages", true, true) };
		protection_context m_clone = { 3, localization("Prevents players cloning you", true, true) };
		protection_context m_cages = { 3, localization("Prevents players spawning cages on you", true, true) };
		protection_context m_attachments = { 3, localization("Prevents players attaching things to you", true, true) };
		protection_context m_crashing = { 1, localization("Prevents players crashing you. NOTE: \"Off\" in this case only disables the notification", true, true) };
		protection_context m_sh_kick = { 3, localization("Prevents players SH kicking you, also notifies when another player is being SH kicked", true, true) };
		protection_context m_ghost = { 3, localization("Prevents a player ghosting themselves", true, true) };
		protection_context m_player_spawns = { 1, localization("Notifies when a player spawns", true, true) };
		protection_context m_pickup_processing = { 3, localization("Prevents pickups being processed", true, true) };
		protection_context m_pickup_spawning = { 1, localization("Notifies when a player gets reported for spawning a pickup", true, true) };
		protection_context m_spectating = { 1, localization("Notifies when a player spectates another player", true, true) };
		protection_context m_desync_kicks = { 1, localization("Notifies when a player uses a menu that pasted quantum and desync kicks another player", true, true) };
		protection_context m_entity_owner_migration = { 3, localization("Prevents modders taking ownership of your spawned entities. NOTE: This will desync the entity for the modder", true, true) };
		protection_context m_host_kicks = { 1, localization("Notifies when a player is being host kicked", true, true) };
		protection_context m_sh_migration = { 1, localization("Notifies when a player is taking SH", true, true) };
		protection_context m_join_timeout = { 1, localization("Notifies when a player is trying to time you out of joining the session", true, true) };
		protection_context m_rockstar_staff = { 1, localization("Notifies when a players real IP address is that of R*'s range", true, true) };
		protection_context m_player_model_update = { 1, localization("Prevents players changing their models. NOTE: THE BLOCK IS USED AS A CRASH PROTECTION, KEEP IT ENABLED TO PREVENT MODEL SWAP CRASHES", true, true) };

		std::unordered_map<int, std::unordered_map<int, uint32_t>> m_spectate_map;
		std::unordered_map<int, uint32_t> m_money_drop_map;

		bool m_show_real_chat_sender = true;
	};

	extern variables m_vars;
}