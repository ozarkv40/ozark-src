#pragma once
#include "menu/base/submenu.h"

class fonts_menu : public menu::submenu::submenu {
public:
	static fonts_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fonts_menu()
		: menu::submenu::submenu() {}
};

namespace settings::font::vars {
	struct font_edit {
		int m_var;
		std::string m_selected;
	};

	struct variables {
		font_edit m_header;
		font_edit m_sub_header;
		font_edit m_option;
		font_edit m_open_tooltip;
		font_edit m_tooltip;
		font_edit m_stacked_display;
		font_edit m_notify_title;
		font_edit m_notify_body;
		font_edit m_panel;
	};

	extern scroll_struct<int> fonts[200];
	extern variables m_vars;
}