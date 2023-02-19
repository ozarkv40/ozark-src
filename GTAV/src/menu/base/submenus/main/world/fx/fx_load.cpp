#include "fx_load.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"
#include "util/log.h"
#include "util/dirs.h"
#include "fx_sky.h"
#include "fx_traffic.h"
#include "fx_cross_multiplier.h"
#include "fx_liquid.h"
#include "fx_puddles.h"
#include "fx_vehicle.h"
#include "fx_vehicle_neons.h"
#include <fstream>

using namespace world::fx::load::vars;

namespace world::fx::load::vars {
	variables m_vars;

	void save_ui_struct(nlohmann::json& json, std::string name, rage::types::ui_element_color_struct elem) {
		json[name]["intensity"] = elem.m_intensity;
		json[name]["radius"] = elem.m_radius;
		json[name]["falloff"] = elem.m_falloff_exp;
		json[name]["inner cone"] = elem.m_inner_cone_angle;
		json[name]["outer cone"] = elem.m_outer_cone_angle;
		json[name]["corona hdr"] = elem.m_corona_hdr;
		json[name]["corona size"] = elem.m_corona_size;
		json[name]["shadow blur"] = elem.m_shadow_blur;
		json[name]["capsule length"] = elem.m_capsule_length;
		json[name]["r"] = elem.m_color.x;
		json[name]["g"] = elem.m_color.y;
		json[name]["b"] = elem.m_color.z;
	}

	void read_ui_struct(nlohmann::json& json, std::string name, rage::types::ui_element_color_struct* elem) {
		elem->m_intensity = json[name]["intensity"];
		elem->m_radius = json[name]["radius"];
		elem->m_falloff_exp = json[name]["falloff"];
		elem->m_inner_cone_angle = json[name]["inner cone"];
		elem->m_outer_cone_angle = json[name]["outer cone"];
		elem->m_corona_hdr = json[name]["corona hdr"];
		elem->m_corona_size = json[name]["corona size"];
		elem->m_shadow_blur = json[name]["shadow blur"];
		elem->m_capsule_length = json[name]["capsule length"];
		elem->m_color.x = json[name]["r"];
		elem->m_color.y = json[name]["g"];
		elem->m_color.z = json[name]["b"];
	}

	void save_config(std::string name) {
		try {
			std::ofstream output(util::dirs::get_path(gamefx) + name + ".json");
			if (output.good()) {
				nlohmann::json json;

				fx_sky_menu::get();
				fx_traffic_menu::get();
				fx_cross_multiplier_menu::get();
				fx_liquid_menu::get();
				fx_puddles_menu::get();
				fx_vehicle_menu::get();
				fx_vehicle_neons_menu::get();

				json["blackout"] = world::fx::vars::m_vars.m_disable_lights;
				json["dome"] = *(bool*)((uint64_t)global::vars::g_ui_weather - 0x60);

				json["water"]["enabled"] = world::fx::vars::m_vars.m_water_toggle;
				json["water"]["value"] = world::fx::vars::m_vars.m_water;

				json["fog"]["enabled"] = world::fx::vars::m_vars.m_fog_toggle;
				json["fog"]["value"] = world::fx::vars::m_vars.m_fog;

				nlohmann::json& sky = json["sky"];
				for (scroll_struct<world::fx::sky::vars::sky_color*>& n : world::fx::sky::vars::sky_colors) {
					sky[n.m_name.get_original()]["rainbow"] = n.m_result->m_rainbow_toggle;
					sky[n.m_name.get_original()]["r"] = n.m_result->m_color.x;
					sky[n.m_name.get_original()]["g"] = n.m_result->m_color.y;
					sky[n.m_name.get_original()]["b"] = n.m_result->m_color.z;
					sky[n.m_name.get_original()]["luminance"] = n.m_result->m_luminance;
				}

				nlohmann::json& traffic = json["traffic"];
				save_ui_struct(traffic, "near", *world::fx::traffic::vars::m_vars.m_near_color.m_color);

				traffic["far start"] = *world::fx::traffic::vars::m_vars.m_far_fade_start;
				traffic["far end"] = *world::fx::traffic::vars::m_vars.m_far_fade_end;
				traffic["near start"] = *world::fx::traffic::vars::m_vars.m_near_fade_start;
				traffic["near end"] = *world::fx::traffic::vars::m_vars.m_near_fade_end;

				traffic["red"]["rainbow"] = world::fx::traffic::vars::m_vars.m_red_color.m_rainbow_toggle;
				traffic["red"]["r"] = world::fx::traffic::vars::m_vars.m_red_color.m_color->x;
				traffic["red"]["g"] = world::fx::traffic::vars::m_vars.m_red_color.m_color->y;
				traffic["red"]["b"] = world::fx::traffic::vars::m_vars.m_red_color.m_color->z;

				traffic["green"]["rainbow"] = world::fx::traffic::vars::m_vars.m_green_color.m_rainbow_toggle;
				traffic["green"]["r"] = world::fx::traffic::vars::m_vars.m_green_color.m_color->x;
				traffic["green"]["g"] = world::fx::traffic::vars::m_vars.m_green_color.m_color->y;
				traffic["green"]["b"] = world::fx::traffic::vars::m_vars.m_green_color.m_color->z;

				traffic["amber"]["rainbow"] = world::fx::traffic::vars::m_vars.m_amber_color.m_rainbow_toggle;
				traffic["amber"]["r"] = world::fx::traffic::vars::m_vars.m_amber_color.m_color->x;
				traffic["amber"]["g"] = world::fx::traffic::vars::m_vars.m_amber_color.m_color->y;
				traffic["amber"]["b"] = world::fx::traffic::vars::m_vars.m_amber_color.m_color->z;

				traffic["walk"]["rainbow"] = world::fx::traffic::vars::m_vars.m_walk_color.m_rainbow_toggle;
				traffic["walk"]["r"] = world::fx::traffic::vars::m_vars.m_walk_color.m_color->x;
				traffic["walk"]["g"] = world::fx::traffic::vars::m_vars.m_walk_color.m_color->y;
				traffic["walk"]["b"] = world::fx::traffic::vars::m_vars.m_walk_color.m_color->z;

				traffic["dont walk"]["rainbow"] = world::fx::traffic::vars::m_vars.m_dont_walk_color.m_rainbow_toggle;
				traffic["dont walk"]["r"] = world::fx::traffic::vars::m_vars.m_dont_walk_color.m_color->x;
				traffic["dont walk"]["g"] = world::fx::traffic::vars::m_vars.m_dont_walk_color.m_color->y;
				traffic["dont walk"]["b"] = world::fx::traffic::vars::m_vars.m_dont_walk_color.m_color->z;

				nlohmann::json& cross_multiplier = json["cross"];
				cross_multiplier["rim light"] = global::vars::g_ui_visual_settings->m_rim_light;
				cross_multiplier["reflection"] = global::vars::g_ui_visual_settings->m_global_environment_reflection;
				cross_multiplier["gamma"] = global::vars::g_ui_visual_settings->m_gamma;
				cross_multiplier["mid blur"] = global::vars::g_ui_visual_settings->m_mid_blur;
				cross_multiplier["far blur"] = global::vars::g_ui_visual_settings->m_far_blur;
				cross_multiplier["sky multiplier"] = global::vars::g_ui_visual_settings->m_sky_multiplier;
				cross_multiplier["desaturation"] = global::vars::g_ui_visual_settings->m_desaturation;

				nlohmann::json& liquid = json["liquid"];
				liquid["puddle"]["r"] = global::vars::g_vfx_liquid[0].r;
				liquid["puddle"]["g"] = global::vars::g_vfx_liquid[0].g;
				liquid["puddle"]["b"] = global::vars::g_vfx_liquid[0].b;
				liquid["puddle"]["a"] = global::vars::g_vfx_liquid[0].a;

				liquid["blood"]["r"] = global::vars::g_vfx_liquid[1].r;
				liquid["blood"]["g"] = global::vars::g_vfx_liquid[1].g;
				liquid["blood"]["b"] = global::vars::g_vfx_liquid[1].b;
				liquid["blood"]["a"] = global::vars::g_vfx_liquid[1].a;

				liquid["oil"]["r"] = global::vars::g_vfx_liquid[2].r;
				liquid["oil"]["g"] = global::vars::g_vfx_liquid[2].g;
				liquid["oil"]["b"] = global::vars::g_vfx_liquid[2].b;
				liquid["oil"]["a"] = global::vars::g_vfx_liquid[2].a;

				liquid["petrol"]["r"] = global::vars::g_vfx_liquid[3].r;
				liquid["petrol"]["g"] = global::vars::g_vfx_liquid[3].g;
				liquid["petrol"]["b"] = global::vars::g_vfx_liquid[3].b;
				liquid["petrol"]["a"] = global::vars::g_vfx_liquid[3].a;

				liquid["mud"]["r"] = global::vars::g_vfx_liquid[4].r;
				liquid["mud"]["g"] = global::vars::g_vfx_liquid[4].g;
				liquid["mud"]["b"] = global::vars::g_vfx_liquid[4].b;
				liquid["mud"]["a"] = global::vars::g_vfx_liquid[4].a;

				nlohmann::json& puddles = json["puddles"];
				puddles["scale"] = global::vars::g_ui_puddle->m_scale;
				puddles["range"] = global::vars::g_ui_puddle->m_range;
				puddles["depth"] = global::vars::g_ui_puddle->m_depth;
				puddles["depth test"] = global::vars::g_ui_puddle->m_depth_test;
				puddles["reflectivity"] = global::vars::g_ui_puddle->m_reflectivity;
				puddles["ripple min size"] = global::vars::g_ui_puddle->m_ripples->m_ripple_min_size;
				puddles["ripple max size"] = global::vars::g_ui_puddle->m_ripples->m_ripple_max_size;
				puddles["ripple min duration"] = global::vars::g_ui_puddle->m_ripples->m_ripple_min_duration;
				puddles["ripple max duration"] = global::vars::g_ui_puddle->m_ripples->m_ripple_max_duration;
				puddles["ripple speed"] = global::vars::g_ui_puddle->m_ripples->m_ripple_speed;
				puddles["ripple drop factor"] = global::vars::g_ui_puddle->m_ripples->m_ripple_drop_factor;
				puddles["ripple wind strength"] = global::vars::g_ui_puddle->m_ripples->m_ripple_wind_strength;
				puddles["ripple strength"] = global::vars::g_ui_puddle->m_ripples->m_ripple_strength;
				puddles["ripple player speed"] = global::vars::g_ui_puddle->m_ripples->m_ripple_player_speed;
				puddles["ripple player map size"] = global::vars::g_ui_puddle->m_ripples->m_ripple_player_map_size;
				puddles["ripple wind damping"] = global::vars::g_ui_puddle->m_ripples->m_ripple_wind_damping;

				nlohmann::json& neons = json["neons"];
				neons["intensity"] = *world::fx::vehicle::neons::vars::m_vars.m_intensity;
				neons["radius"] = *world::fx::vehicle::neons::vars::m_vars.m_radius;
				neons["fall off exponent"] = *world::fx::vehicle::neons::vars::m_vars.m_fall_off_exponent;
				neons["capsule extent sides"] = *world::fx::vehicle::neons::vars::m_vars.m_capsule_extent_sides;
				neons["capsule extent front back"] = *world::fx::vehicle::neons::vars::m_vars.m_capsule_extent_front_back;
				neons["clip plane height"] = *world::fx::vehicle::neons::vars::m_vars.m_clip_plane_height;
				neons["bike clip plane height"] = *world::fx::vehicle::neons::vars::m_vars.m_bike_clip_plane_height;

				save_ui_struct(json["vehicle"], "interior", *world::fx::vehicle::vars::m_vars.m_interior_light_color.m_color);

				output << json.dump(4);
				output.close();
			}
		} catch (std::exception& E) {
			LOG_WARN("[Json] %s", E.what());
		}
	}

	void load_config(std::string name) {
		try {
			std::ifstream input(util::dirs::get_path(gamefx) + name + ".json");
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				fx_sky_menu::get();
				fx_cross_multiplier_menu::get();
				fx_liquid_menu::get();
				fx_puddles_menu::get();
				fx_traffic_menu::get();
				fx_vehicle_menu::get();
				fx_vehicle_neons_menu::get();

				world::fx::vars::m_vars.m_disable_lights = json["blackout"];
				*(bool*)((uint64_t)global::vars::g_ui_weather - 0x60) = json["dome"];

				world::fx::vars::m_vars.m_water_toggle = json["water"]["enabled"];
				world::fx::vars::m_vars.m_water = json["water"]["value"];

				world::fx::vars::m_vars.m_fog_toggle = json["fog"]["enabled"];
				world::fx::vars::m_vars.m_fog = json["fog"]["value"];

				if (!json["sky"].is_null()) {
					nlohmann::json& sky = json["sky"];

					int index = 0;
					for (scroll_struct<world::fx::sky::vars::sky_color*>& n : world::fx::sky::vars::sky_colors) {
						if (!sky[n.m_name.get_original()].is_null()) {
							n.m_result->m_rainbow_toggle = sky[n.m_name.get_original()]["rainbow"];
							n.m_result->m_color.x = sky[n.m_name.get_original()]["r"];
							n.m_result->m_color.y = sky[n.m_name.get_original()]["g"];
							n.m_result->m_color.z = sky[n.m_name.get_original()]["b"];
							n.m_result->m_luminance = sky[n.m_name.get_original()]["luminance"];
							world::fx::sky::vars::handle_patch(index);
						}

						index++;
					}
				}

				if (!json["traffic"].is_null()) {
					nlohmann::json& traffic = json["traffic"];
					read_ui_struct(traffic, "near", world::fx::traffic::vars::m_vars.m_near_color.m_color);

					*world::fx::traffic::vars::m_vars.m_far_fade_start = traffic["far start"];
					*world::fx::traffic::vars::m_vars.m_far_fade_end = traffic["far end"];
					*world::fx::traffic::vars::m_vars.m_near_fade_start = traffic["near start"];
					*world::fx::traffic::vars::m_vars.m_near_fade_end = traffic["near end"];

					world::fx::traffic::vars::m_vars.m_red_color.m_rainbow_toggle = traffic["red"]["rainbow"];
					world::fx::traffic::vars::m_vars.m_red_color.m_color->x = traffic["red"]["r"];
					world::fx::traffic::vars::m_vars.m_red_color.m_color->y = traffic["red"]["g"];
					world::fx::traffic::vars::m_vars.m_red_color.m_color->z = traffic["red"]["b"];

					world::fx::traffic::vars::m_vars.m_green_color.m_rainbow_toggle = traffic["green"]["rainbow"];
					world::fx::traffic::vars::m_vars.m_green_color.m_color->x = traffic["green"]["r"];
					world::fx::traffic::vars::m_vars.m_green_color.m_color->y = traffic["green"]["g"];
					world::fx::traffic::vars::m_vars.m_green_color.m_color->z = traffic["green"]["b"];

					world::fx::traffic::vars::m_vars.m_amber_color.m_rainbow_toggle = traffic["amber"]["rainbow"];
					world::fx::traffic::vars::m_vars.m_amber_color.m_color->x = traffic["amber"]["r"];
					world::fx::traffic::vars::m_vars.m_amber_color.m_color->y = traffic["amber"]["g"];
					world::fx::traffic::vars::m_vars.m_amber_color.m_color->z = traffic["amber"]["b"];

					world::fx::traffic::vars::m_vars.m_walk_color.m_rainbow_toggle = traffic["walk"]["rainbow"];
					world::fx::traffic::vars::m_vars.m_walk_color.m_color->x = traffic["walk"]["r"];
					world::fx::traffic::vars::m_vars.m_walk_color.m_color->y = traffic["walk"]["g"];
					world::fx::traffic::vars::m_vars.m_walk_color.m_color->z = traffic["walk"]["b"];

					world::fx::traffic::vars::m_vars.m_dont_walk_color.m_rainbow_toggle = traffic["dont walk"]["rainbow"];
					world::fx::traffic::vars::m_vars.m_dont_walk_color.m_color->x = traffic["dont walk"]["r"];
					world::fx::traffic::vars::m_vars.m_dont_walk_color.m_color->y = traffic["dont walk"]["g"];
					world::fx::traffic::vars::m_vars.m_dont_walk_color.m_color->z = traffic["dont walk"]["b"];
				}

				if (!json["cross"].is_null()) {
					nlohmann::json& cross_multiplier = json["cross"];
					global::vars::g_ui_visual_settings->m_rim_light = cross_multiplier["rim light"];
					global::vars::g_ui_visual_settings->m_global_environment_reflection = cross_multiplier["reflection"];
					global::vars::g_ui_visual_settings->m_gamma = cross_multiplier["gamma"];
					global::vars::g_ui_visual_settings->m_mid_blur = cross_multiplier["mid blur"];
					global::vars::g_ui_visual_settings->m_far_blur = cross_multiplier["far blur"];
					global::vars::g_ui_visual_settings->m_sky_multiplier = cross_multiplier["sky multiplier"];
					global::vars::g_ui_visual_settings->m_desaturation = cross_multiplier["desaturation"];
				}

				if (!json["liquid"].is_null()) {
					nlohmann::json& liquid = json["liquid"];
					global::vars::g_vfx_liquid[0].r = liquid["puddle"]["r"];
					global::vars::g_vfx_liquid[0].g = liquid["puddle"]["g"];
					global::vars::g_vfx_liquid[0].b = liquid["puddle"]["b"];
					global::vars::g_vfx_liquid[0].a = liquid["puddle"]["a"];

					global::vars::g_vfx_liquid[1].r = liquid["blood"]["r"];
					global::vars::g_vfx_liquid[1].g = liquid["blood"]["g"];
					global::vars::g_vfx_liquid[1].b = liquid["blood"]["b"];
					global::vars::g_vfx_liquid[1].a = liquid["blood"]["a"];

					global::vars::g_vfx_liquid[2].r = liquid["oil"]["r"];
					global::vars::g_vfx_liquid[2].g = liquid["oil"]["g"];
					global::vars::g_vfx_liquid[2].b = liquid["oil"]["b"];
					global::vars::g_vfx_liquid[2].a = liquid["oil"]["a"];

					global::vars::g_vfx_liquid[3].r = liquid["petrol"]["r"];
					global::vars::g_vfx_liquid[3].g = liquid["petrol"]["g"];
					global::vars::g_vfx_liquid[3].b = liquid["petrol"]["b"];
					global::vars::g_vfx_liquid[3].a = liquid["petrol"]["a"];

					global::vars::g_vfx_liquid[4].r = liquid["mud"]["r"];
					global::vars::g_vfx_liquid[4].g = liquid["mud"]["g"];
					global::vars::g_vfx_liquid[4].b = liquid["mud"]["b"];
					global::vars::g_vfx_liquid[4].a = liquid["mud"]["a"];
				}

				if (!json["puddles"].is_null()) {
					nlohmann::json& puddles = json["puddles"];
					global::vars::g_ui_puddle->m_scale = puddles["scale"];
					global::vars::g_ui_puddle->m_range = puddles["range"];
					global::vars::g_ui_puddle->m_depth = puddles["depth"];
					global::vars::g_ui_puddle->m_depth_test = puddles["depth test"];
					global::vars::g_ui_puddle->m_reflectivity = puddles["reflectivity"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_min_size = puddles["ripple min size"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_max_size = puddles["ripple max size"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_min_duration = puddles["ripple min duration"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_max_duration = puddles["ripple max duration"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_speed = puddles["ripple speed"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_drop_factor = puddles["ripple drop factor"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_wind_strength = puddles["ripple wind strength"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_strength = puddles["ripple strength"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_player_speed = puddles["ripple player speed"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_player_map_size = puddles["ripple player map size"];
					global::vars::g_ui_puddle->m_ripples->m_ripple_wind_damping = puddles["ripple wind damping"];
				}

				if (!json["vehicle"].is_null()) {
					read_ui_struct(json["vehicle"], "interior", world::fx::vehicle::vars::m_vars.m_interior_light_color.m_color);
				}

				if (!json["neons"].is_null()) {
					nlohmann::json& neons = json["neons"];
					*world::fx::vehicle::neons::vars::m_vars.m_intensity = neons["intensity"];
					*world::fx::vehicle::neons::vars::m_vars.m_radius = neons["radius"];
					*world::fx::vehicle::neons::vars::m_vars.m_fall_off_exponent = neons["fall off exponent"];
					*world::fx::vehicle::neons::vars::m_vars.m_capsule_extent_sides = neons["capsule extent sides"];
					*world::fx::vehicle::neons::vars::m_vars.m_capsule_extent_front_back = neons["capsule extent front back"];
					*world::fx::vehicle::neons::vars::m_vars.m_clip_plane_height = neons["clip plane height"];
					*world::fx::vehicle::neons::vars::m_vars.m_bike_clip_plane_height = neons["bike clip plane height"];
				}
			}
		} catch (std::exception& E) {
			LOG_WARN("[Json] %s", E.what());
		}
	}
}

void fx_load_menu::load() {
	set_name("Save and Load");
	set_parent<game_fx_menu>();

	add_option(button_option("Save Game FX")
		.add_translate()
		.add_keyboard("Enter FX config name", 30, [](button_option* option, const char* result) {
			save_config(result);
		}));

	add_option(break_option("Game FXs")
		.add_translate());

	add_string("~m~None");
}

void fx_load_menu::update() {}

void fx_load_menu::update_once() {
	clear_options(2);

	try {
		std::vector<std::string> fxs = util::dirs::get_files_in_directory(util::dirs::get_path(gamefx), ".json");
		if (fxs.size()) {
			for (std::string fx : fxs) {
				add_option(button_option(fx)
					.add_click([=] { load_config(fx); }));
			}
		} else {
			add_option(button_option(get_string("~m~None")).ref());
		}
	} catch (std::exception& e) {
		LOG_WARN("[Json] %s", e.what());
	}
}

void fx_load_menu::feature_update() {}

fx_load_menu* g_instance;
fx_load_menu* fx_load_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_load_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}