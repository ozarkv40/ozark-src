#include "ocean_tuning.h"
#include "menu/base/submenu_handler.h"
#include "../ocean.h"

using namespace world::ocean::tuning::vars;

namespace world::ocean::tuning::vars {
	variables m_vars;
}

void ocean_tuning_menu::load() {
	set_name("Ocean Tuning");
	set_parent<ocean_menu>();

	add_option(number_option<float>(SCROLL, "Ripple Scale")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_ripple_scale, "%.2f", 0.01f).add_min(0.f).add_max(100.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_ripple_scale = m_vars.m_water_tune.m_ripple_scale; }));

	add_option(number_option<float>(SCROLL, "Foam Scale")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_ocean_foam_scale, "%.2f", 0.01f).add_min(0.f).add_max(100.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_ocean_foam_scale = m_vars.m_water_tune.m_ocean_foam_scale; }));

	add_option(number_option<float>(SCROLL, "Specular Falloff")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_specular_falloff, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_specular_falloff = m_vars.m_water_tune.m_specular_falloff; }));

	add_option(number_option<float>(SCROLL, "Fog Pierce Intensity")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_fog_pierce_intensity, "%.1f", 0.1f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_fog_pierce_intensity = m_vars.m_water_tune.m_fog_pierce_intensity; }));

	add_option(number_option<float>(SCROLL, "Refraction Blend")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_refraction_blend, "%.1f", 0.1f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_refraction_blend = m_vars.m_water_tune.m_refraction_blend; }));

	add_option(number_option<float>(SCROLL, "Refraction Exponent")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_refraction_exponent, "%.2f", 0.25f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_refraction_exponent = m_vars.m_water_tune.m_refraction_exponent; }));

	add_option(number_option<float>(SCROLL, "Water Cycle Depth")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_water_cycle_depth, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_water_cycle_depth = m_vars.m_water_tune.m_water_cycle_depth; }));

	add_option(number_option<float>(SCROLL, "Water Cycle Fade")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_water_cycle_fade, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_water_cycle_fade = m_vars.m_water_tune.m_water_cycle_fade; }));

	add_option(number_option<float>(SCROLL, "Water Lightning Depth")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_water_lightning_depth, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_water_lightning_depth = m_vars.m_water_tune.m_water_lightning_depth; }));

	add_option(number_option<float>(SCROLL, "Water Lightning Fade")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_water_lightning_fade, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_water_lightning_fade = m_vars.m_water_tune.m_water_lightning_fade; }));

	add_option(number_option<float>(SCROLL, "Deep Water Mod Depth")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_deep_water_mod_depth, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_deep_water_mod_depth = m_vars.m_water_tune.m_deep_water_mod_depth; }));

	add_option(number_option<float>(SCROLL, "Deep Water Mod Fade")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_deep_water_mod_fade, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_deep_water_mod_fade = m_vars.m_water_tune.m_deep_water_mod_fade; }));

	add_option(number_option<float>(SCROLL, "God Rays Lerp Start")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_god_rays_lerp_start, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_god_rays_lerp_start = m_vars.m_water_tune.m_god_rays_lerp_start; }));

	add_option(number_option<float>(SCROLL, "God Rays Lerp End")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_god_rays_lerp_end, "%.0f", 1.f).add_min(0.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_god_rays_lerp_end = m_vars.m_water_tune.m_god_rays_lerp_end; }));

	add_option(number_option<float>(SCROLL, "Disturb Foam Scale")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_disturb_foam_scale, "%.2f", 0.01f).add_min(0.f).add_max(100.f).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_disturb_foam_scale = m_vars.m_water_tune.m_disturb_foam_scale; }));

	add_option(number_option<float>(SCROLL, "Fog Minimum - X")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_fog_min.x, "%.0f", 1.f).add_min(-std::numeric_limits<float>::max()).add_max(std::numeric_limits<float>::max()).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_fog_min.x = m_vars.m_water_tune.m_fog_min.x; }));

	add_option(number_option<float>(SCROLL, "Fog Minimum - Y")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_fog_min.y, "%.0f", 1.f).add_min(-std::numeric_limits<float>::max()).add_max(std::numeric_limits<float>::max()).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_fog_min.y = m_vars.m_water_tune.m_fog_min.y; }));

	add_option(number_option<float>(SCROLL, "Fog Maximum - X")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_fog_max.x, "%.0f", 1.f).add_min(-std::numeric_limits<float>::max()).add_max(std::numeric_limits<float>::max()).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_fog_max.x = m_vars.m_water_tune.m_fog_max.x; }));

	add_option(number_option<float>(SCROLL, "Fog Maximum - Y")
		.add_translate()
		.add_number(m_vars.m_water_tune.m_fog_max.y, "%.0f", 1.f).add_min(-std::numeric_limits<float>::max()).add_max(std::numeric_limits<float>::max()).set_scroll_speed(10)
		.add_click([] { global::vars::g_water_tune->m_fog_max.y = m_vars.m_water_tune.m_fog_max.y; }));
}

void ocean_tuning_menu::update() {}

void ocean_tuning_menu::update_once() {
	memcpy(&m_vars.m_water_tune, global::vars::g_water_tune, sizeof(m_vars.m_water_tune));
}

void ocean_tuning_menu::feature_update() {}

ocean_tuning_menu* g_instance;
ocean_tuning_menu* ocean_tuning_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ocean_tuning_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
