#pragma once
#include "menu/base/submenu.h"
#include "protection_entity_ghosting.h"

class protection_entity_ghosting_edit_menu : public menu::submenu::submenu {
public:
	static protection_entity_ghosting_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_entity_ghosting_edit_menu()
		: menu::submenu::submenu() {}
};

namespace protection::entity::ghosting::edit::vars {
	struct variables {
		bool m_ready = false;
		protection::entity::ghosting::vars::ghost* m_selected;
	};

	extern variables m_vars;
}