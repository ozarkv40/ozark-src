#pragma once
#include "menu/base/submenu.h"

class model_swaps_add_menu : public menu::submenu::submenu {
public:
	static model_swaps_add_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	model_swaps_add_menu()
		: menu::submenu::submenu() {}
};

namespace misc::swaps::model::add::vars {
	struct variables {
		std::string m_original;
		std::string m_new;

		std::vector<std::shared_ptr<button_option>> m_options;
	};

	extern variables m_vars;
}