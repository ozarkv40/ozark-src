#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"

class fx_sky_menu : public menu::submenu::submenu {
public:
	static fx_sky_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_sky_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::sky::vars {
	struct sky_color {
		bool m_rainbow_toggle;
		float m_luminance = 1.f;
		color_rgba m_internal_color;
		math::vector3_<float> m_color;
		math::vector4<float>* m_memory_color;
		math::vector4<float> m_memory_color_cache;
		menu::rainbow m_rainbow;
		std::vector<uint8_t> m_cache;
	};

	struct variables {
		sky_color m_azimuth_east_color;
		sky_color m_azimuth_west_color;
		sky_color m_azimuth_transition_color;
		sky_color m_cloud_base_minus_mid_colour;
		sky_color m_cloud_mid_color;
		sky_color m_cloud_shadow_minus_base_colour_times_shadow_strength;
		sky_color m_moon_color;
		sky_color m_sky_plane_color;
		sky_color m_sun_color;
		sky_color m_zenith_color;
		sky_color m_zenith_transition_color;

		int m_selected;
		bool m_cached;
	};

	void handle_patch(int index = 0, bool reset = false);
	extern scroll_struct<sky_color*> sky_colors[11];
	extern variables m_vars;
}