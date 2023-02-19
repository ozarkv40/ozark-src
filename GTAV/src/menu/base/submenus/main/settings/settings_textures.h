#pragma once
#include "menu/base/submenu.h"

class textures_menu : public menu::submenu::submenu {
public:
	static textures_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	textures_menu()
		: menu::submenu::submenu() {}
};

namespace settings::textures::vars {
	struct variables {
		std::shared_ptr<base_option> m_header_option;
		std::shared_ptr<base_option> m_sub_header_option;
		std::shared_ptr<base_option> m_background_option;
		std::shared_ptr<base_option> m_scroller_option;
		std::shared_ptr<base_option> m_footer_option;
		std::shared_ptr<base_option> m_tooltip_background_option;
		std::shared_ptr<base_option> m_stacked_display_background_option;
		std::shared_ptr<base_option> m_stacked_display_bar_option;
		std::shared_ptr<base_option> m_panel_background_option;
		std::shared_ptr<base_option> m_panel_bar_option;
		std::shared_ptr<base_option> m_notify_background_option;
		std::shared_ptr<base_option> m_notify_bar_option;
		std::shared_ptr<base_option> m_vehicle_stats_background_option;
		std::shared_ptr<base_option> m_vehicle_stats_bar_option;
	};

	extern variables m_vars;
}