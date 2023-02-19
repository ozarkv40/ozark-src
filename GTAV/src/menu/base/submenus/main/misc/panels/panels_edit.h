#pragma once
#include "menu/base/submenu.h"

class panels_edit_menu : public menu::submenu::submenu {
public:
	static panels_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	panels_edit_menu()
		: menu::submenu::submenu() {}
};

namespace misc::panel::edit::vars {
	struct variables {
		std::size_t m_index;
		std::string m_id;
		int m_local_column;
		int m_local_index;
	};

	extern variables m_vars;
}