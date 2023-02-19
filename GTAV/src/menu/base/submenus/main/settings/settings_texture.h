#pragma once
#include "menu/base/submenu.h"

class texture_menu : public menu::submenu::submenu {
public:
	static texture_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	texture_menu()
		: menu::submenu::submenu() {}
};

namespace settings::texture::vars {
	struct pixel_info {
		math::vector2<float> m_pixel_size;
		bool m_can_resize = false;
		std::string m_resize_type = "";
	};

	struct variables {
		std::shared_ptr<toggle_option> m_toggle_button;
		menu_texture* m_texture;

		pixel_info m_pixel_info;
	};

	extern variables m_vars;
}