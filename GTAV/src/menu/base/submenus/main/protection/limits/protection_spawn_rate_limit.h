#pragma once
#include "menu/base/submenu.h"

class protection_spawn_rate_limit_menu : public menu::submenu::submenu {
public:
	static protection_spawn_rate_limit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_spawn_rate_limit_menu()
		: menu::submenu::submenu() {}
};

namespace protection::limits::spawn::vars {
	struct entity_rate_limit {
		uint32_t m_model;
		int m_delay = 0;
		bool m_enabled = true;
		uint32_t m_last_spawned[0x20];
		char m_comment[0x100];

		entity_rate_limit() {
			memset(m_last_spawned, 0, sizeof(m_last_spawned));
		}
	};

	struct variables {
		std::vector<entity_rate_limit> m_limits;
	};

	extern variables m_vars;
}