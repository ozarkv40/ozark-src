#pragma once
#include "menu/base/submenu.h"

class network_spoofing_name_menu : public menu::submenu::submenu {
public:
	static network_spoofing_name_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_name_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::name::vars {
	struct variables {
		std::string m_spoofed_name;
		std::string m_temp_name;

		int m_color;
		int m_style;
		int m_icon;
		bool m_save_to_config;

		char m_original_name[20];
		char m_preview_name[50];
		std::shared_ptr<button_option> m_preview_button;
	};

	extern scroll_struct<const char*> text_colors[10];
	extern scroll_struct<const char*> text_settings[3];
	extern scroll_struct<const char*> text_icons[4];

	void spoof(bool reset, const char* name = nullptr);
	extern variables m_vars;
}