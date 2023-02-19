#pragma once
#include "menu/base/submenu.h"

class aerial_camera_menu : public menu::submenu::submenu {
public:
	static aerial_camera_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	aerial_camera_menu()
		: menu::submenu::submenu() {}
};

namespace misc::camera::aerial::vars {
	struct variables {
		bool m_toggle_camera;
		int m_distance = 100;
		Cam m_aerial_cam;
	};

	extern variables m_vars;
}