#pragma once
#include "menu/base/submenu.h"

class protection_reactions_menu : public menu::submenu::submenu {
public:
	static protection_reactions_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_reactions_menu()
		: menu::submenu::submenu() {}
};

namespace protection::reactions::vars {
	enum eEventReactions {
		EVENT_DEATH,
		EVENT_AIM,
		EVENT_REPORT,
		EVENT_SPOOFED_HOST_TOKEN,
		EVENT_SPOOFED_RID,
		EVENT_SPOOFED_NAME,
		EVENT_SPOOFED_IP,
		EVENT_SPOOFED_CHAT,
		EVENT_SPOOFED_TEXT,
		EVENT_ARXAN,
		EVENT_CRASH_ATTEMPT,
		EVENT_SPECTATING_YOU,
		EVENT_MONEY_DROP,
		EVENT_QUANTUM_KICK,
		EVENT_SCRIPT_MIGRATION,
		EVENT_SUPER_JUMP,
		EVENT_JOIN_TIMEOUT,
		EVENT_INVALID_MODEL,
		EVENT_INFO_CHANGE
	};

	struct event_reaction {
		bool m_explode;
		bool m_crash;
		bool m_kick;
		bool m_add_to_overseer;
		bool m_cage;
		bool m_kick_from_vehicle;
		bool m_set_on_fire;
		bool m_ragdoll;
		bool m_glitch_physics;
		bool m_black_screen;
		bool m_blame;
		bool m_give_wanted_level;
		bool m_send_to_island;
		bool m_remove_weapons;
		bool m_hostile_clone;
		bool m_bail;

		bool is_active() {
			for (int i = 0; i < sizeof(event_reaction); i++) {
				if (*(bool*)((uint64_t)this + i)) return true;
			}

			return false;
		}
	};

	struct variables {
		event_reaction m_reactions[19];
	};

	void process_event(eEventReactions _event, Player id);
	extern variables m_vars;
}