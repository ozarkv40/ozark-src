#pragma once
#include "menu/base/submenu.h"

class network_session_overseer_menu : public menu::submenu::submenu {
public:
	static network_session_overseer_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_session_overseer_menu()
		: menu::submenu::submenu() {}
};

namespace network::session::overseer::vars {
#define OVERSEER_ENABLED (1 << 0)
#define OVERSEER_NOTIFY (1 << 1)
#define OVERSEER_BLOCK_JOIN (1 << 2)
#define OVERSEER_CRASH (1 << 3)
#define OVERSEER_KICK (1 << 4)
#define OVERSEER_CAGE (1 << 5)
#define OVERSEER_KICK_FROM_VEHICLE (1 << 6)
#define OVERSEER_SET_ON_FIRE (1 << 7)
#define OVERSEER_RAGDOLL (1 << 8)
#define OVERSEER_GLITCH_PHYSICS (1 << 9)
#define OVERSEER_BLACK_SCREEN (1 << 10)
#define OVERSEER_BLAME (1 << 11)
#define OVERSEER_GIVE_WANTED_LEVEL (1 << 12)
#define OVERSEER_SEND_TO_ISLAND (1 << 13)
#define OVERSEER_REMOVE_WEAPONS (1 << 14)
#define OVERSEER_HOSTILE_CLONE (1 << 15)
#define OVERSEER_BAIL (1 << 16)
#define OVERSEER_EXPLODE (1 << 17)

	struct overseer {
		std::string m_name;
		std::string m_reason;
		uint64_t m_rockstar_id;
		int m_flags;
	};

	struct variables {
		bool m_enabled;
		std::vector<overseer> m_players;

		std::vector<uint64_t> m_queue;
		std::vector<uint64_t> m_image_queue;


		bool m_update_players = true;
		bool m_update_online = true;
	};

	void save(std::string name, uint64_t rid, std::string reason);
	bool process_join_request(uint64_t rid, std::string name);
	void process_join_notify(uint64_t rid, std::string name);
	void process_event(Player id, int flag);
	extern variables m_vars;
}
