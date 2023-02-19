#pragma once
#include "menu/base/submenu.h"

class network_account_outfits_edit_name_menu : public menu::submenu::submenu {
public:
	static network_account_outfits_edit_name_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_outfits_edit_name_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::outfits::edit::name::vars {
	struct variables {
		int m_color;
		int m_style;
		int m_icon;
		std::string m_temp_name;
		char m_preview_name[50];
		std::shared_ptr<button_option> m_preview_button;
	};

	extern variables m_vars;
}