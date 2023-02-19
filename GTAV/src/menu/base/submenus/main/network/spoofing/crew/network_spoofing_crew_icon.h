#pragma once
#include "menu/base/submenu.h"

class network_spoofing_crew_icon_menu : public menu::submenu::submenu {
public:
	static network_spoofing_crew_icon_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_crew_icon_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::crew::icon::vars {
	struct variables {
		int m_spoofed_icon = -1;
		std::string m_temp_name;
		bool m_save_to_config = true;
		char m_preview_name[50];
		std::shared_ptr<button_option> m_preview_button;
	};

	void spoof(bool reset, int icon = -1);
	extern variables m_vars;
}