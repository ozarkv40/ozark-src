#pragma once
#include "menu/base/submenu.h"

class network_spoofing_crew_name_menu : public menu::submenu::submenu {
public:
	static network_spoofing_crew_name_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_crew_name_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::crew::name::vars {
	struct variables {
		std::string m_temp_name;
		std::string m_spoofed_name;
		bool m_save_to_config;
		char m_preview_name[50];
		std::shared_ptr<button_option> m_preview_button;
	};

	void spoof(bool reset, const char* name = nullptr);
	extern variables m_vars;
}