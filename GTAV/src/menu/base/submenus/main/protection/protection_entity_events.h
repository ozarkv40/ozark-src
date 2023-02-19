#pragma once
#include "menu/base/submenu.h"

class protection_entity_events_menu : public menu::submenu::submenu {
public:
	static protection_entity_events_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_entity_events_menu()
		: menu::submenu::submenu() {}
};

namespace protection::entity::vars {
	struct variables {
		bool m_block_modder_create;
		bool m_block_modder_sync;
	};

	extern variables m_vars;
}