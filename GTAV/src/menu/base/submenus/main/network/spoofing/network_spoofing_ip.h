#pragma once
#include "menu/base/submenu.h"

class network_spoofing_ip_menu : public menu::submenu::submenu {
public:
	static network_spoofing_ip_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_ip_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::ip::vars {
	struct variables {
		bool m_save_to_config;

		std::string m_spoofing_ip;
		std::string m_temp_spoofing_ip;
		std::string m_default_ip;
		char m_preview_name[50];
		std::shared_ptr<button_option> m_preview_button;
	};

	void spoof(bool reset, std::string ip = "");
	extern variables m_vars;
}