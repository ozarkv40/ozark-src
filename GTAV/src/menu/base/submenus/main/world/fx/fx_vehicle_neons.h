#pragma once
#include "menu/base/submenu.h"

class fx_vehicle_neons_menu : public menu::submenu::submenu {
public:
	static fx_vehicle_neons_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_vehicle_neons_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::vehicle::neons::vars {
	struct variables {
		float m_backup_intensity;
		float m_backup_radius;
		float m_backup_fall_off_exponent;
		float m_backup_capsule_extent_sides;
		float m_backup_capsule_extent_front_back;
		float m_backup_clip_plane_height;
		float m_backup_bike_clip_plane_height;

		float* m_intensity;
		float* m_radius;
		float* m_fall_off_exponent;
		float* m_capsule_extent_sides;
		float* m_capsule_extent_front_back;
		float* m_clip_plane_height;
		float* m_bike_clip_plane_height;
	};

	extern variables m_vars;
}