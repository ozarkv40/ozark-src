#pragma once
#include "menu/base/submenu.h"

class protection_limits_menu : public menu::submenu::submenu {
public:
	static protection_limits_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_limits_menu()
		: menu::submenu::submenu() {}
};

namespace protection::limits::vars {
	struct message_limit {
		bool m_block_all;
		bool m_block_spoofed;
		int m_delay;
	};
	
	struct variables {
		message_limit m_text_message;
		message_limit m_chat_message;

		std::shared_ptr<base_option> m_text_message_option;
		std::shared_ptr<base_option> m_chat_message_option;
	};

	extern variables m_vars;
}