#include "network_players_trolling_attachments.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_trolling.h"
#include "global/lists.h"
#include "util/memory/memory.h"
#include "menu/base/submenus/main/weapon/entity_gun.h"
#include "menu/base/util/control.h"
#include "attachments/network_players_trolling_attachments_presets.h"

using namespace network::players::trolling::attachments::vars;

namespace network::players::trolling::attachments::vars {
	variables m_vars;

	scroll_struct<std::pair<uint32_t, int>> custom_models[100];

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

	int get_custom_size() {
		for (int i = 0; i < 100; i++) {
			if (custom_models[i].m_result.first == 0) {
				return i;
			}
		}

		return 0;
	}

	void attach(uint32_t model, int model_type) {
		menu::control::request_model(model, [=] (uint32_t m) {
			std::vector<std::pair<Entity, int>> handles;

			switch (model_type) {
				case 0: // ped
					if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
						menu::player::player_context& player = menu::player::get_selected_player();
						handles.push_back({ native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, player.m_heading, true, false), player.m_id });
					} else {
						menu::player::for_each([&] (menu::player::player_context& player) {
							handles.push_back({ native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, player.m_heading, true, false), player.m_id});
						});
					}

					break;

				case 1: // object
				case 3: // flag
					if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
						menu::player::player_context& player = menu::player::get_selected_player();
						handles.push_back({ native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false), player.m_id});
					} else {
						menu::player::for_each([&] (menu::player::player_context& player) {
							handles.push_back({ native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false), player.m_id });
						});
					}

					break;

				case 2: // vehicle
					if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
						menu::player::player_context& player = menu::player::get_selected_player();
						handles.push_back({ native::create_vehicle(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, player.m_heading, true, true, false), player.m_id });
					} else {
						menu::player::for_each([&] (menu::player::player_context& player) {
							handles.push_back({ native::create_vehicle(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, player.m_heading, true, true, false), player.m_id });
						});
					}

					break;
			}

			if (!handles.empty()) {
				for (auto& [handle, id] : handles) {
					if (!native::does_entity_exist(handle)) continue;

					math::vector3<float> rotation = { 0.f, 0.f, 0.f };
					if ((global::vars::g_network_menu_type == SELECTED_PLAYER && menu::player::get_selected_player().m_attachment_randomize_rotation)
						|| (global::vars::g_network_menu_type == ALL_PLAYERS && m_vars.m_attachment_randomize_rotation)) {
						rotation = {
							native::get_random_float_in_range(0.f, 360.f),
							native::get_random_float_in_range(0.f, 360.f),
							native::get_random_float_in_range(0.f, 360.f)
						};
					}

					int bone = global::lists::g_ped_bones[global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_attachment_bone : m_vars.m_attachment_bone].m_result;
					if ((global::vars::g_network_menu_type == SELECTED_PLAYER && menu::player::get_selected_player().m_attachment_randomize_bone)
						|| (global::vars::g_network_menu_type == ALL_PLAYERS && m_vars.m_attachment_randomize_bone)) {
						bone = global::lists::g_ped_bones[native::get_random_int_in_range(0, 12)].m_result;
					}

					native::attach_entity_to_entity(handle, menu::player::get_player(id).m_ped, native::get_ped_bone_index(menu::player::get_player(id).m_ped, bone), 0.f, 0.f, 0.f, rotation.x, rotation.y, rotation.z, true, true, false, true, 1, true);
				}
			}
		});
	}

	void attach_random() {
		uint32_t model = 0;
		int type = native::get_random_int_in_range(0, 3);

		switch (type) {
			case 0:
				model = weapon::entity::gun::vars::peds[native::get_random_int_in_range(0, 12)].m_result;
				break;

			case 1:
			default:
				model = weapon::entity::gun::vars::objects[native::get_random_int_in_range(0, 14)].m_result;
				break;
			
			case 2:
				model = weapon::entity::gun::vars::vehicles[native::get_random_int_in_range(0, 21)].m_result;
				break;
			
			case 3:
				model = global::lists::g_object_model_flags[native::get_random_int_in_range(0, 17)].m_result;
				break;

		}

		attach(model, type);
	}
}

void network_players_trolling_attachments_menu::load() {
	set_name("Attachments");
	set_parent<network_players_trolling_menu>();

	for (int i = 0; i < 100; i++) {
		custom_models[i].m_name.set("");
		custom_models[i].m_result.first = 0;
		custom_models[i].m_result.second = 0;
	}

	add_option(submenu_option("Presets")
		.add_translate()
		.add_submenu<network_players_trolling_attachments_presets_menu>());

	add_option(scroll_option<int>(SCROLL, "Bone")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_attachment_bone, 0, NUMOF(global::lists::g_ped_bones), global::lists::g_ped_bones)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_attachment_bone, 0, NUMOF(global::lists::g_ped_bones), global::lists::g_ped_bones);
			} else {
				option->add_scroll(m_vars.m_attachment_bone, 0, NUMOF(global::lists::g_ped_bones), global::lists::g_ped_bones);
			}
		}));

	add_option(toggle_option("Randomize Bone")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_attachment_randomize_bone)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_attachment_randomize_bone);
			} else {
				option->add_toggle(m_vars.m_attachment_randomize_bone);
			}
		}));

	add_option(toggle_option("Randomize Rotation")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_attachment_randomize_rotation)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_attachment_randomize_rotation);
			} else {
				option->add_toggle(m_vars.m_attachment_randomize_rotation);
			}
		}));

	add_option(button_option("Input Custom Model")
		.add_translate()
		.add_keyboard("Input the model! (Hint: name, hash or numeric)", 30, [=] (button_option* option, const char* text) {
			if (text) {
				uint32_t hash = 0;
				if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
					// hash
					hash = (uint32_t)_strtoui64(text, 0, 0);
				} else {
					std::string str_name(text);
					if (std::find_if(str_name.begin(), str_name.end(), [] (unsigned char c) { return !std::isdigit(c); }) == str_name.end()) {
						// numeric
						hash = (uint32_t)atoi(text);
					} else {
						// name
						hash = native::get_hash_key(text);
					}
				}

				if (hash) {
					int type = get_model_type(hash);
					if (type == 1 || type == 5 || type == 6) {
						for (int i = 0; i < 100; i++) {
							if (custom_models[i].m_result.first == 0x0) {
								custom_models[i].m_name = localization(text, false);
								custom_models[i].m_result.first = hash;
								custom_models[i].m_result.second = 0;

								switch (type) {
									case 1: // object
										custom_models[i].m_result.second = 1;
										break;

									case 5: // vehicle
										custom_models[i].m_result.second = 2;
										break;

									case 6: // ped
										custom_models[i].m_result.second = 0;
										break;
								}

								// vehicle
								if (type == 5) {
									const char* label = native::get_display_name_from_vehicle_model(hash);
									if (label) {
										label = native::get_label_text(label);
										if (strcmp(label, "NULL")) {
											custom_models[i].m_name = localization(label, false);
											
											if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
												menu::player::get_selected_player().m_attachment_custom = i;
											} else {
												m_vars.m_attachment_custom = i;
											}
										}
									}
								}

								break;
							}
						}
					}
				}
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Peds")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_attachment_peds, 0, 12, weapon::entity::gun::vars::peds)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_attachment_peds, 0, 12, weapon::entity::gun::vars::peds);
			} else {
				option->add_scroll(m_vars.m_attachment_peds, 0, 12, weapon::entity::gun::vars::peds);
			}
		})
		.add_click([] { attach(weapon::entity::gun::vars::peds[global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_attachment_peds : m_vars.m_attachment_peds].m_result, 0); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Objects")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_attachment_objects, 0, 14, weapon::entity::gun::vars::objects)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_attachment_objects, 0, 14, weapon::entity::gun::vars::objects);
			} else {
				option->add_scroll(m_vars.m_attachment_objects, 0, 14, weapon::entity::gun::vars::objects);
			}
		})
		.add_click([] { attach(weapon::entity::gun::vars::objects[global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_attachment_objects : m_vars.m_attachment_objects].m_result, 1); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Vehicles")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_attachment_vehicles, 0, 21, weapon::entity::gun::vars::vehicles)
			.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_attachment_vehicles, 0, 21, weapon::entity::gun::vars::vehicles);
			} else {
				option->add_scroll(m_vars.m_attachment_vehicles, 0, 21, weapon::entity::gun::vars::vehicles);
			}
		})
		.add_click([] { attach(weapon::entity::gun::vars::vehicles[global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_attachment_vehicles : m_vars.m_attachment_vehicles].m_result, 2); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Flags")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_attachment_flags, 0, NUMOF(global::lists::g_object_model_flags), global::lists::g_object_model_flags)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_attachment_flags, 0, NUMOF(global::lists::g_object_model_flags), global::lists::g_object_model_flags);
			} else {
				option->add_scroll(m_vars.m_attachment_flags, 0, NUMOF(global::lists::g_object_model_flags), global::lists::g_object_model_flags);
			}
		})
		.add_click([] { attach(global::lists::g_object_model_flags[global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_attachment_flags : m_vars.m_attachment_flags].m_result, 3); }));

	add_option(scroll_option<std::pair<uint32_t, int>>(SCROLLSELECT, "Custom")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_attachment_custom, 0, 1, custom_models)
		.add_update([] (scroll_option<std::pair<uint32_t, int>>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_attachment_custom, 0, get_custom_size(), custom_models);
			} else {
				option->add_scroll(m_vars.m_attachment_custom, 0, get_custom_size(), custom_models);
			}
		})
		.add_click([] { attach(custom_models[global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_attachment_custom : m_vars.m_attachment_custom].m_result.second, custom_models[global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_attachment_custom : m_vars.m_attachment_custom].m_result.first); })
		.add_requirement([] { return get_custom_size() > 0; }));

	add_option(button_option("Attach Random Entity")
		.add_translate()
		.add_click(attach_random));
}

void network_players_trolling_attachments_menu::update() {}

void network_players_trolling_attachments_menu::update_once() {}

void network_players_trolling_attachments_menu::feature_update() {}

network_players_trolling_attachments_menu* g_instance;
network_players_trolling_attachments_menu* network_players_trolling_attachments_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_trolling_attachments_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}