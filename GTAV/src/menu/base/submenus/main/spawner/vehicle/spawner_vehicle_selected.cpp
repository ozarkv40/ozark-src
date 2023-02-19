#include "spawner_vehicle_selected.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "rage/engine.h"
#include "menu/base/util/panels.h"

using namespace spawner::vehicle::selected::vars;

namespace spawner::vehicle::selected::vars {
	variables m_vars;

	std::string texture_list[] = {
		"candc_apartments",
		"candc_assault",
		"candc_battle",
		"candc_casinoheist",
		"candc_chopper",
		"candc_default",
		"candc_executive1",
		"candc_gunrunning",
		"candc_hacker",
		"candc_importexport",
		"candc_smuggler",
		"candc_truck",
		"candc_xmas2017",
		"casino_suites",
		"dock_default",
		"dock_dlc_banner",
		"dock_dlc_color",
		"dock_dlc_executive1",
		"dock_dlc_fittings",
		"dock_dlc_flag",
		"dock_dlc_lights",
		"dock_dlc_model",
		"dock_dlc_slides",
		"dock_yacht_backgrounds",
		"elt_default",
		"elt_dlc_apartments",
		"elt_dlc_assault",
		"elt_dlc_battle",
		"elt_dlc_business",
		"elt_dlc_executive1",
		"elt_dlc_luxe",
		"elt_dlc_pilot",
		"elt_dlc_smuggler",
		"lgm_default",
		"lgm_dlc_apartments",
		"lgm_dlc_arena",
		"lgm_dlc_assault",
		"lgm_dlc_battle",
		"lgm_dlc_biker",
		"lgm_dlc_business",
		"lgm_dlc_business2",
		"lgm_dlc_casinoheist",
		"lgm_dlc_executive1",
		"lgm_dlc_gunrunning",
		"lgm_dlc_heist",
		"lgm_dlc_importexport",
		"lgm_dlc_lts_creator",
		"lgm_dlc_luxe",
		"lgm_dlc_pilot",
		"lgm_dlc_smuggler",
		"lgm_dlc_specialraces",
		"lgm_dlc_stunt",
		"lgm_dlc_summer2020",
		"lgm_dlc_valentines",
		"lgm_dlc_valentines2",
		"lgm_dlc_vinewood",
		"lgm_dlc_xmas2017",
		"lsc_default",
		"lsc_dlc_import_export",
		"lsc_dlc_summer2020",
		"lsc_jan2016",
		"lsc_lowrider2",
		"mba_vehicles",
		"pandm_default",
		"sssa_default",
		"sssa_dlc_arena",
		"sssa_dlc_assault",
		"sssa_dlc_battle",
		"sssa_dlc_biker",
		"sssa_dlc_business",
		"sssa_dlc_business2",
		"sssa_dlc_casinoheist",
		"sssa_dlc_christmas_2",
		"sssa_dlc_christmas_3",
		"sssa_dlc_executive_1",
		"sssa_dlc_halloween",
		"sssa_dlc_heist",
		"sssa_dlc_hipster",
		"sssa_dlc_independence",
		"sssa_dlc_lts_creator",
		"sssa_dlc_mp_to_sp",
		"sssa_dlc_smuggler",
		"sssa_dlc_stunt",
		"sssa_dlc_summer2020",
		"sssa_dlc_valentines",
		"sssa_dlc_vinewood",
		"sssa_dlc_xmas2017",
		"lgm_dlc_tuner",
		"sssa_dlc_tuner"
	};

	void populate_textures() {
		util::fiber::pool::add([=] {
			for (std::string texture : texture_list) {
				bool loaded = true;

				while (!native::has_streamed_texture_dict_loaded(texture.c_str())) {
					loaded = false;
					native::request_streamed_texture_dict(texture.c_str(), true);
					util::fiber::sleep(100);
				}

				util::fiber::sleep(250);

				rage::types::texture_store* store = global::vars::g_texture_store;
				if (is_valid_ptr(store) && is_valid_ptr(store->m_pool) && is_valid_ptr(store->m_mask)) {
					rage::types::dictionary_pool* pool = store->m_pool;
					for (uint32_t i = 0; i < store->m_count; i++) {
						if (~(store->m_mask[i] >> 7) & 1) {
							rage::types::dictionary_pool element = pool[i];
							if (is_valid_ptr(element.m_pool)) {
								if (element.m_dictionary_hash == native::get_hash_key(texture.c_str())) {
									for (short j = 0; j < element.m_pool->m_count; j++) {
										rage::types::grc_texture_dx11* item = element.m_pool->m_items[j];
										if (is_valid_ptr(item)) {
											if (is_valid_ptr(item->m_name)) {
												if (!strstr(item->m_name, "_")) {
													m_vars.m_textures[native::get_hash_key(item->m_name)] = texture;
												}
											}
										}
									}
								}
							}
						}
					}
				}

				if (!loaded) {
					native::set_streamed_texture_dict_as_no_longer_needed(texture.c_str());
				}
			}
		});
	}

	std::pair<std::pair<std::string, std::string>, rage::types::vehicle_model_info*> get_vehicle_model_texture(uint32_t model) {
		rage::types::vehicle_model_info* info = (rage::types::vehicle_model_info*)rage::engine::get_model_info(model);
		if (info) {
			auto vit = std::find_if(m_vars.m_textures.begin(), m_vars.m_textures.end(), [=](std::pair<uint32_t, std::string> Element) {
				return Element.first == model;
			});

			if (vit != m_vars.m_textures.end()) {
				return { std::make_pair(vit->second, info->m_model_name), info };
			}

			// try again for 2
			std::string name = std::string(info->m_model_name) + "2";

			vit = std::find_if(m_vars.m_textures.begin(), m_vars.m_textures.end(), [=](std::pair<uint32_t, std::string> Element) {
				return Element.first == native::get_hash_key(name.c_str());
			});

			if (vit != m_vars.m_textures.end()) {
				return { std::make_pair(vit->second, name), info };
			}
		}

		return { std::make_pair("", ""), nullptr };
	}

	void preview(uint32_t model) {
		menu::panels::panel_custom_vehicle_preview data;

		std::pair<std::pair<std::string, std::string>, rage::types::vehicle_model_info*> texture = get_vehicle_model_texture(model);
		if (!texture.first.first.empty()) {
			strcpy_s(data.m_dict, texture.first.first.c_str());
			strcpy_s(data.m_name, texture.first.second.c_str());
		}

		data.m_model = model;
		data.m_max_speed = native::get_vehicle_model_max_speed(model) * global::vars::g_selected_metric_system.first;
		data.m_seats = native::get_vehicle_model_number_of_seats(model);
		data.m_max_braking = native::get_vehicle_model_max_braking(model);
		data.m_max_traction = native::get_vehicle_model_max_traction(model);

		if (texture.second) {
			strcpy_s(data.m_manufacturer, texture.second->m_manufacturer_name);
		} else {
			menu::panels::toggle_panel_render("PANEL_VEHICLE_PREVIEW", false);
			return;
		}

		menu::panels::set_structure(menu::panels::get_child(menu::panels::get_parent("PANEL_VEHICLE_PREVIEW"), "PANEL_VEHICLE_PREVIEW_INFO"), &data, sizeof(data));
		menu::panels::toggle_panel_render("PANEL_VEHICLE_PREVIEW", spawner::vars::m_vars.m_flag == spawner::vars::SPAWNER_SELF);
	}
}

void spawner_vehicle_selected_menu::load() {
	set_name("Spawner", false, false);
	set_parent<spawner_menu>();

	populate_textures();
}

void spawner_vehicle_selected_menu::update() {}

void spawner_vehicle_selected_menu::update_once() {
	clear_options(0);
	set_name(spawner_menu::get()->get_string(spawner::vars::get_class_name(m_vars.m_selected)), false, false);

	struct found_vehicles {
		std::string m_name;
		int m_count;
		uint32_t m_hash;
	};

	std::vector<found_vehicles> vehicles;

	for (uint32_t hash : spawner::vars::m_vars.m_vehicle_hashes[m_vars.m_selected]) {
		const char* name = native::get_display_name_from_vehicle_model(hash);
		if (name) {
			name = native::get_label_text(name);
			if (strcmp(name, "NULL")) {
				vehicles.push_back({ name, 0, hash });
			}
		}
	}

	std::vector<std::pair<std::string, int>> names;

	for (found_vehicles& vehicle : vehicles) {
		auto& vit = std::find_if(names.begin(), names.end(), [=](std::pair<std::string, int >& Element) {
			return Element.first == vehicle.m_name;
		});

		if (vit == names.end()) {
			names.push_back({ vehicle.m_name, 0 });
		} else {
			vit->second++;
			vehicle.m_name += " " + std::to_string(vit->second + 1);
		}
	}

	for (found_vehicles& vehicle : vehicles) {
		add_option(button_option(vehicle.m_name)
			.add_hover([=] { preview(vehicle.m_hash); })
			.add_click([=] { spawner::vars::spawn_vehicle(vehicle.m_hash); }));
	}
}

void spawner_vehicle_selected_menu::feature_update() {}

spawner_vehicle_selected_menu* g_instance;
spawner_vehicle_selected_menu* spawner_vehicle_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}