#pragma once
#include "menu/base/submenu.h"

class protection_spawn_rate_limit_add_menu : public menu::submenu::submenu {
public:
	static protection_spawn_rate_limit_add_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_spawn_rate_limit_add_menu()
		: menu::submenu::submenu() {}
};

namespace protection::limits::spawn::add::vars {
	struct variables {
		uint32_t m_model = 0;
		int m_delay = 0;
		std::string m_comment = "";

		std::vector<std::shared_ptr<base_option>> m_options;
	};

	extern variables m_vars;
}