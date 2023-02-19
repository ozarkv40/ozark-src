#pragma once
#include "menu/base/submenu.h"

class wardrobe_menu : public menu::submenu::submenu {
public:
	static wardrobe_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	wardrobe_menu()
		: menu::submenu::submenu() {}
};

namespace player::wardrobe::vars {
	struct variables {
		int m_clothing;
		int m_clothing_model;
		int m_clothing_variation;
		int m_accessory;
		int m_accessory_model;
		int m_accessory_variation;
		int m_accessory_clear;

		bool m_preview_camera;
		Cam m_preview_cam;

		bool m_zoom_to_body_part;
		math::vector3_<float> m_current_offset = { 0.00f, -2.00f, 0.40f };
	};

	void remove_camera();

	extern scroll_struct<std::pair<int, math::vector3_<float>>> components[12];
	extern scroll_struct<std::pair<int, math::vector3_<float>>> accessories[5];
	extern variables m_vars;
}