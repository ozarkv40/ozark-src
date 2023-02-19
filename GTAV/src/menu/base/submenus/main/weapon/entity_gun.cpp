#include "entity_gun.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "global/lists.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/control.h"
#include "menu/base/util/camera.h"
#include "util/memory/memory.h"

using namespace weapon::entity::gun::vars;

namespace weapon::entity::gun::vars {
	variables m_vars;

	scroll_struct<int> types[] = {
		{ localization("Object", true), 0 },
		{ localization("Vehicle", true), 1 },
		{ localization("Ped", true), 2 },
	};

	scroll_struct<uint32_t> objects[] = {
		{ localization("Meteor", true), 0xDF9841D7 },
		{ localization("Stairs", true), 0x757C28D },
		{ localization("Egg", true), 0x6B795EBC },
		{ localization("Barbell", true), 0xE2FBA8D8 },
		{ localization("Campfire", true), 0xC079B265 },
		{ localization("Volleyball", true), 0xC79A987E },
		{ localization("Dildo", true), 0xE6CB661E },
		{ localization("Guitar", true), 0xD5C0BC07 },
		{ localization("Gold", true), 0xF046EA37 },
		{ localization("Missile", true), 0xB2274905 },
		{ localization("Toilet", true), 0x6F9939C7 },
		{ localization("Money Bag", true), 0x113FD533 },
		{ localization("Wheelchair", true), 0x4B3D240F },
		{ localization("Pumpkin", true), 0x83C07621 },
	};

	scroll_struct<uint32_t> vehicles[] = {
		{ localization("", false), 0x5A82F9AE },
		{ localization("", false), 0x5BA0FF1E },
		{ localization("", false), 0x18619B7E },
		{ localization("", false), 0x322CF98F },
		{ localization("", false), 0xB2E046FB },
		{ localization("", false), 0xE83C17 },
		{ localization("", false), 0xA29F78B0 },
		{ localization("", false), 0x42BC5E19 },
		{ localization("", false), 0x1FD824AF },
		{ localization("", false), 0x8B213907 },
		{ localization("", false), 0x2C1FEA99 },
		{ localization("", false), 0xEA6A047F },
		{ localization("", false), 0x432AA566 },
		{ localization("", false), 0xEB298297 },
		{ localization("", false), 0xB44F0582 },
		{ localization("", false), 0x9472CD24 },
		{ localization("", false), 0x23CA25F2 },
		{ localization("", false), 0x619C1B82 },
		{ localization("", false), 0xB472D2B5 },
		{ localization("", false), 0xC2974024 },
		{ localization("", false), 0x761E2AD3 },
	};

	scroll_struct<uint32_t> peds[] = {
		{ localization("Whale", true), 0x8D8AC8B9 },
		{ localization("Cow", true), 0xFCFA9E1E },
		{ localization("Seagull", true), 0xD3939DFD },
		{ localization("Topless Girl", true), 0x9CF26183 },
		{ localization("Bride", true), 0x6162EC47 },
		{ localization("Hooker", true), 0x28ABF95 },
		{ localization("Astronaut", true), 0xE7B31432 },
		{ localization("Human Statue", true), 0x795AC7A8 },
		{ localization("Mime", true), 0x3CDCA742 },
		{ localization("Jesus", true), 0xCE2CB751 },
		{ localization("Pogo", true), 0xDC59940D },
		{ localization("Zombie", true), 0xAC4B4506 },
	};

	int get_size(int type) {
		switch (type) {
			case 0:
				for (int i = 0; i < 100; i++) {
					if (objects[i].m_result == 0x0) {
						return i;
					}
				}

				break;

			case 1:
				for (int i = 0; i < 100; i++) {
					if (vehicles[i].m_result == 0x0) {
						return i;
					}
				}

				break;

			case 2:
				for (int i = 0; i < 100; i++) {
					if (peds[i].m_result == 0x0) {
						return i;
					}
				}

				break;
		}

		return 0;
	}

	int get_model_type(uint32_t model) {
		struct hash_node {
			uint32_t m_model_hash;
			uint16_t m_data;
			uint16_t m_padding;
			hash_node* m_next;
		};

		uint16_t hash_table_count = *(uint16_t*)memory::read_instruction(global::vars::g_get_model_info);
		uint64_t hash_table = *(uint64_t*)memory::read_instruction(global::vars::g_get_model_info + 0x7E);
		hash_node** hash_map = *(hash_node***)memory::read_instruction(global::vars::g_get_model_info + 0x21);

		for (uint16_t i = 0; i < hash_table_count; i++) {
			for (hash_node* current = hash_map[i]; current; current = current->m_next) {
				uint64_t element = *(uint64_t*)(hash_table + (current->m_data * 8));
				if (element) {
					if (current->m_model_hash == model) {
						return (int)*(uint8_t*)(element + 0x9D) & 0x1F;
					}
				}
			}
		}

		return 0;
	}
}

void entity_gun_menu::load() {
	set_name("Entity Gun");
	set_parent<weapon_mods_menu>();

	add_string("Could not determine models type");

	for (scroll_struct<uint32_t>& n : vehicles) {
		n.m_name = localization(native::get_label_text(native::get_display_name_from_vehicle_model(n.m_result)), false);
	}

	add_option(toggle_option("Toggle Entity Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle));
	
	add_option(scroll_option<int>(SCROLL, "Current Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(types), types));

	add_option(scroll_option<uint32_t>(SCROLL, "Delay")
		.add_translate()
		.add_scroll(m_vars.m_wait, 0, NUMOF(global::lists::g_timers), global::lists::g_timers));

	add_option(number_option<float>(SCROLL, "Speed")
		.add_translate()
		.add_number(m_vars.m_speed, "%.0f", 100.f).set_scroll_speed(10));

	add_option(button_option("Input Custom Model")
		.add_translate()
		.add_keyboard("Input the model! (Hint: name, hash or numeric)", 30, [=](button_option* option, const char* text) {
			if (text) {
				uint32_t hash = 0;
				if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
					// hash
					hash = (uint32_t)_strtoui64(text, 0, 0);
				} else {
					std::string str_name(text);
					if (std::find_if(str_name.begin(), str_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == str_name.end()) {
						// numeric
						hash = (uint32_t)atoi(text);
					} else {
						// name
						hash = native::get_hash_key(text);
					}
				}

				if (hash) {
					int type = get_model_type(hash);
					if (type > 0) {
						switch (type) {
							case 1: // object
								for (int i = 0; i < 100; i++) {
									if (objects[i].m_result == 0x0) {
										objects[i].m_name = localization(text, false);
										objects[i].m_result = hash;
										m_vars.m_object = i;
										m_vars.m_type = 0;
										break;
									}
								}

								break;

							case 5: { // vehicle
								const char* label = native::get_display_name_from_vehicle_model(hash);
								if (label) {
									label = native::get_label_text(label);
									if (strcmp(label, "NULL")) {
										text = label;
									}
								}

								for (int i = 0; i < 100; i++) {
									if (vehicles[i].m_result == 0x0) {
										vehicles[i].m_name = localization(text, false);
										vehicles[i].m_result = hash;
										m_vars.m_vehicle = i;
										m_vars.m_type = 1;
										break;
									}
								}

								break;
							}

							case 6: // ped
								for (int i = 0; i < 100; i++) {
									if (peds[i].m_result == 0x0) {
										peds[i].m_name = localization(text, false);
										peds[i].m_result = hash;
										m_vars.m_ped = i;
										m_vars.m_type = 2;
										break;
									}
								}

								break;

							default:
								menu::notify::stacked(get_name().get(), get_string("Could not determine models type"), global::ui::g_error);
								break;
						}
					}
				}
			}
		}));

	add_option(break_option("Types")
		.add_translate());

	add_option(scroll_option<uint32_t>(SCROLL, "Object")
		.add_translate()
		.add_scroll(m_vars.m_object, 0, get_size(0), objects)
		.add_update([](scroll_option<uint32_t>* option, int pos) {
			option->add_scroll(m_vars.m_object, 0, get_size(0), objects);
		}));

	add_option(scroll_option<uint32_t>(SCROLL, "Vehicle")
		.add_translate()
		.add_scroll(m_vars.m_vehicle, 0, get_size(1), vehicles)
		.add_update([](scroll_option<uint32_t>* option, int pos) {
			option->add_scroll(m_vars.m_vehicle, 0, get_size(1), vehicles);
		}));

	add_option(scroll_option<uint32_t>(SCROLL, "Ped")
		.add_translate()
		.add_scroll(m_vars.m_ped, 0, get_size(2), peds)
		.add_update([](scroll_option<uint32_t>* option, int pos) {
			option->add_scroll(m_vars.m_ped, 0, get_size(2), peds);
		}));
}

void entity_gun_menu::update() {}

void entity_gun_menu::update_once() {}

void entity_gun_menu::feature_update() {
	if (m_vars.m_toggle) {
		if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
			static int timer = 0;
			menu::timers::run_timed(&timer, global::lists::g_timers[m_vars.m_wait].m_result, [] {
				Entity handle = 0;
				switch (m_vars.m_type) {
					case 0: // object
						menu::control::simple_request_model(objects[m_vars.m_object].m_result);
						handle = native::create_object(objects[m_vars.m_object].m_result, 0.f, 0.f, 0.f, true, true, false);
						break;

					case 1: // vehicle
						menu::control::simple_request_model(vehicles[m_vars.m_vehicle].m_result);
						handle = native::create_vehicle(vehicles[m_vars.m_vehicle].m_result, 0.f, 0.f, 0.f, 0.f, true, true, 0);
						break;

					case 2: // ped
						menu::control::simple_request_model(peds[m_vars.m_ped].m_result);
						handle = native::create_ped(21, peds[m_vars.m_ped].m_result, 0.f, 0.f, 0.f, 0.f, true, false);
						break;
				}

				if (native::does_entity_exist(handle)) {
					native::set_entity_as_mission_entity(handle, true, true);
					native::set_entity_no_collision_entity(menu::player::get_local_player().m_entity, handle, true);

					math::vector3<float> rotation = native::get_gameplay_cam_rot(0);
					math::vector3<float> target = native::get_gameplay_cam_coord() + (menu::camera::get_direction(rotation) * 25.f);

					native::set_entity_coords(handle, target.x, target.y, target.z, false, false, false, false);
					native::set_entity_rotation(handle, rotation.x, 0.f, rotation.z, 0, 1);

					if (native::is_entity_a_vehicle(handle)) native::set_vehicle_out_of_control(handle, true, true);
					native::apply_force_to_entity_center_of_mass(handle, 1, 0.f, m_vars.m_speed, 0.f, false, true, true, false);
				}
			});
		}
	}
}

entity_gun_menu* g_instance;
entity_gun_menu* entity_gun_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new entity_gun_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}