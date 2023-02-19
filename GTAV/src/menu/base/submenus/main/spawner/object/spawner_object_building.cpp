#include "spawner_object_building.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "menu/base/util/control.h"

using namespace spawner::object::building::vars;

namespace spawner::object::building::vars {
	variables m_vars;

	scroll_struct<int> types[] = {
		{ localization("Half Pipe - Straight", true), 0 },
		{ localization("Half Pipe - Curved Wide", true), 1 },
		{ localization("Half Pipe - Curved Small", true), 2 },
		{ localization("Forest", true), 3 },
	};

	void build_straight_half_pipe() {
		menu::control::request_model(0xF66F582F, [](uint32_t model) {
			math::vector3<float> min_dimensions;
			math::vector3<float> max_dimensions;

			native::get_model_dimensions(model, &min_dimensions, &max_dimensions);
			math::vector3<float> diameter = max_dimensions - min_dimensions;

			math::vector3<float> spawn_coords = menu::player::get_local_player().m_coords + (native::get_entity_forward_vector(menu::player::get_local_player().m_ped) * 10.f);
			native::get_ground_z_for_3d_coord(spawn_coords.x, spawn_coords.y, spawn_coords.z, &spawn_coords.z, false);

			Object first_object = native::create_object(model, spawn_coords.x, spawn_coords.y, spawn_coords.z, true, true, false);
			if (native::does_entity_exist(first_object)) {
				native::set_entity_rotation(first_object, -m_vars.m_vertical_angle, 0.f, menu::player::get_local_player().m_heading, 2, true);
				native::freeze_entity_position(first_object, true);

				Object next_object = first_object;
				for (int i = 0; i < m_vars.m_count[0]; i++) {
					math::vector3<float> next = native::get_offset_from_entity_in_world_coords(next_object, 0.f, diameter.y - 0.15f, 0.f);
					next_object = native::create_object(model, next.x, next.y, next.z, true, true, false);
					if (native::does_entity_exist(next_object)) {
						native::set_entity_rotation(next_object, -m_vars.m_vertical_angle, 0.f, menu::player::get_local_player().m_heading, 2, true);
						native::freeze_entity_position(next_object, true);
					}
				}
			}
		});
	}

	void build_curved_half_pipe_wide() {
		menu::control::request_model(0xF66F582F, [](uint32_t model) {
			math::vector3<float> min_dimensions;
			math::vector3<float> max_dimensions;

			native::get_model_dimensions(model, &min_dimensions, &max_dimensions);
			math::vector3<float> diameter = max_dimensions - min_dimensions;

			math::vector3<float> spawn_coords = menu::player::get_local_player().m_coords + (native::get_entity_forward_vector(menu::player::get_local_player().m_ped) * 10.f);
			native::get_ground_z_for_3d_coord(spawn_coords.x, spawn_coords.y, spawn_coords.z, &spawn_coords.z, false);

			Object first_object = native::create_object(model, spawn_coords.x, spawn_coords.y, spawn_coords.z, true, true, false);
			if (native::does_entity_exist(first_object)) {
				native::set_entity_heading(first_object, menu::player::get_local_player().m_heading);
				native::freeze_entity_position(first_object, true);

				Object next_object = first_object;
				for (int i = 0; i < m_vars.m_count[1]; i++) {
					math::vector3<float> next = native::get_offset_from_entity_in_world_coords(next_object, 0.4f, diameter.y - 0.15f - 0.7f, 0.f);
					next_object = native::create_object(model, next.x, next.y, next.z, true, true, false);
					if (native::does_entity_exist(next_object)) {
						native::set_entity_heading(next_object, menu::player::get_local_player().m_heading - ((i + 1) * 5.f));
						native::freeze_entity_position(next_object, true);
					}
				}
			}
		});
	}

	void build_curved_half_pipe_small() {
		menu::control::request_model(0xF66F582F, [](uint32_t model) {
			math::vector3<float> min_dimensions;
			math::vector3<float> max_dimensions;

			native::get_model_dimensions(model, &min_dimensions, &max_dimensions);
			math::vector3<float> diameter = max_dimensions - min_dimensions;

			math::vector3<float> spawn_coords = menu::player::get_local_player().m_coords + (native::get_entity_forward_vector(menu::player::get_local_player().m_ped) * 10.f);
			native::get_ground_z_for_3d_coord(spawn_coords.x, spawn_coords.y, spawn_coords.z, &spawn_coords.z, false);

			Object first_object = native::create_object(model, spawn_coords.x, spawn_coords.y, spawn_coords.z, true, true, false);
			if (native::does_entity_exist(first_object)) {
				native::set_entity_heading(first_object, menu::player::get_local_player().m_heading);
				native::freeze_entity_position(first_object, true);

				Object next_object = first_object;
				for (int i = 0; i < m_vars.m_count[2]; i++) {
					math::vector3<float> next = native::get_offset_from_entity_in_world_coords(next_object, 0.7f, diameter.y - 0.15f - 1.4f, 0.f);
					next_object = native::create_object(model, next.x, next.y, next.z, true, true, false);
					if (native::does_entity_exist(next_object)) {
						native::set_entity_heading(next_object, menu::player::get_local_player().m_heading - ((i + 1) * 10.5f));
						native::freeze_entity_position(next_object, true);
					}
				}
			}
		});
	}

	void build_forest() {
		uint32_t trees[] = {
			0xE43D331B,
			0x16770e68,
			0xb355b730,
			0xEDF5CD3C,
			0x4D11F2B,
			0x49e472aa
		};

		menu::control::request_model(0xEDF5CD3C, [=](uint32_t model) {math::vector3<float> min_dimensions;
		math::vector3<float> spawn_coords = menu::player::get_local_player().m_coords;
		native::get_ground_z_for_3d_coord(spawn_coords.x, spawn_coords.y, spawn_coords.z, &spawn_coords.z, false);

		Object first_object = native::create_object(model, spawn_coords.x, spawn_coords.y, spawn_coords.z, true, true, false);
		if (native::does_entity_exist(first_object)) {
			native::freeze_entity_position(first_object, true);

			Object next_object = first_object;
			for (int i = 0; i < m_vars.m_count[3]; i++) {
				math::vector3<float> next = native::get_offset_from_entity_in_world_coords(next_object, native::get_random_float_in_range(-10.f, 10.f), native::get_random_float_in_range(-10.f, 10.f), 0.f);
				uint32_t ModelHash = trees[native::get_random_int_in_range(0, 5)];

				next_object = native::create_object(ModelHash, next.x, next.y, spawn_coords.z - (ModelHash == 0xb355b730 ? 0.f : 3.f), true, true, false);
				if (native::does_entity_exist(next_object)) {
					native::freeze_entity_position(next_object, true);
				}
			}
		}
		});
	}

	void create() {
		switch (m_vars.m_type) {
			case 0: build_straight_half_pipe(); break;
			case 1: build_curved_half_pipe_wide(); break;
			case 2: build_curved_half_pipe_small(); break;
			case 3: build_forest(); break;
		}
	}
}

void spawner_object_building_menu::load() {
	set_name("Buildings");
	set_parent<spawner_menu>();

	add_option(scroll_option<int>(SCROLL, "Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(types), types));

	add_option(number_option<int>(SCROLL, "Count")
		.add_translate()
		.add_number(m_vars.m_count[0], "%i", 1).add_min(1).add_max(50)
		.add_update([](number_option<int>* option, int pos) { option->add_number(m_vars.m_count[m_vars.m_type], "%i", 1); }));

	add_option(number_option<float>(SCROLL, "Vertical Angle")
		.add_translate()
		.add_number(m_vars.m_vertical_angle, "%.0f", 1.f).add_min(-90.f).add_max(90.f)
		.add_hover([] { menu::renderer::draw_sprite({ "ozarktextures", "half_pipe_side.png" }, { 0.5f, 0.5f }, { 0.1f, 0.1f }, -m_vars.m_vertical_angle, { 255, 255, 255, 255 }); })
		.add_requirement([] { return m_vars.m_type == 0; }));

	add_option(button_option("Create Building")
		.add_translate().add_hotkey()
		.add_click(create));
}

void spawner_object_building_menu::update() {}

void spawner_object_building_menu::update_once() {}

void spawner_object_building_menu::feature_update() {}

spawner_object_building_menu* g_instance;
spawner_object_building_menu* spawner_object_building_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_object_building_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}