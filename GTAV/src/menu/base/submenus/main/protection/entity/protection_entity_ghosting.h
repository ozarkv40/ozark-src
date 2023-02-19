#pragma once
#include "menu/base/submenu.h"

class protection_entity_ghosting_menu : public menu::submenu::submenu {
public:
	static protection_entity_ghosting_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_entity_ghosting_menu()
		: menu::submenu::submenu() {}
};

namespace protection::entity::ghosting::vars {
	struct ghost {
		bool m_enabled_for_session = false;
		eNetObjectTypes m_type;
		std::string m_name;
	};

	struct variables {
		ghost m_ghosts[14];
	};

	extern variables m_vars;
}