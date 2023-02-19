#pragma once
#include "menu/base/submenu.h"

class camera_menu : public menu::submenu::submenu {
public:
	static camera_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	camera_menu()
		: menu::submenu::submenu() {}
};

namespace misc::camera::vars {
	struct variables {
		bool m_freecam;
		Cam m_freecam_handle;

		bool m_camera_zoom;
		float m_camera_zoom_val = 1.f;
	};

	extern variables m_vars;
}