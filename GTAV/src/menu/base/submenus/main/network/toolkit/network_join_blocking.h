#pragma once
#include "menu/base/submenu.h"

class network_join_blocking_menu : public menu::submenu::submenu {
public:
	static network_join_blocking_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_blocking_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blocking::vars {
	enum eHostToolkit {
		TOOLKIT_NEXT_SESSION_HOST,
		TOOLKIT_RID,
		TOOLKIT_NAME,
		TOOLKIT_IP,
		TOOLKIT_DEV
	};

	struct toolkit_block {
		bool m_enabled;
		bool m_notify = true;
		radio_context m_context = { "commonmenu", "shop_tick_icon" };
	};

	struct user_block {
		int m_type; // 1 = rid, 2 = name, 3 = IP
		uint64_t m_rockstar_id;
		char m_name[32];
		uint32_t m_ip;
		eJoinResponses m_response;
		bool m_enabled;
	};

	struct variables {
		int m_who_can_join;
		toolkit_block m_responses[8];
		std::vector<user_block> m_blocked_users;
	};

	extern variables m_vars;
}