#include "vehicle_ramps.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "menu/base/util/control.h"

using namespace vehicle::ramps::vars;

namespace vehicle::ramps::vars {
	variables m_vars;

	Object create_attached_ramp(Entity attach_to, uint32_t model, int pos = 0, bool opacitated = true) {
		menu::control::simple_request_model(model);

		math::vector3<float> min, max;
		native::get_model_dimensions(model, &min, &max);

		math::vector3<float> dim = { max.x - min.x, max.y - min.y, max.z - min.z };

		math::vector3<float> coords = native::get_entity_coords(attach_to, true);
		Object ramp = native::create_object(model, coords.x, coords.y, coords.z, true, true, false);

		switch (pos) {
			case 0:
				native::attach_entity_to_entity(ramp, attach_to, 0, /**/ 0, dim.y, -0.5, /**/ 0, 0, 180, true, true, true, false, 2, true);
				break;

			case 1:native::attach_entity_to_entity(ramp, attach_to, 0, /**/ 0, (-1) * dim.y, -0.5, /**/ 0, 0, 0, true, true, true, false, 2, true);
				break;

			case 2:native::attach_entity_to_entity(ramp, attach_to, 0, /**/ (-1) * dim.x, 0, -0.5, /**/ 0, 0, 270, true, true, true, false, 2, true);
				break;

			case 3:native::attach_entity_to_entity(ramp, attach_to, 0, /**/ dim.x, 0, -0.5, /**/ 0, 0, 90, true, true, true, false, 2, true);
				break;
		}

		if (opacitated) {
			native::set_entity_alpha(ramp, 100, true);
		}

		return ramp;
	}

	void attach() {
		if (!menu::player::get_local_player().m_in_vehicle) return;

		char buffer[50];
		sprintf_s(buffer, "PROP_MP_RAMP_0%i", m_vars.m_ramp_type);

		uint32_t model = native::get_hash_key(buffer);

		if (m_vars.m_front_ramp) {
			create_attached_ramp(menu::player::get_local_player().m_vehicle, model, 0, m_vars.m_transparency);
		}

		if (m_vars.m_rear_ramp) {
			create_attached_ramp(menu::player::get_local_player().m_vehicle, model, 1, m_vars.m_transparency);
		}

		if (m_vars.m_left_ramp) {
			create_attached_ramp(menu::player::get_local_player().m_vehicle, model, 2, m_vars.m_transparency);
		}

		if (m_vars.m_right_ramp) {
			create_attached_ramp(menu::player::get_local_player().m_vehicle, model, 3, m_vars.m_transparency);
		}
	}

	void detach() {
		if (!menu::player::get_local_player().m_in_vehicle) return;
		math::vector3<float> coords = menu::player::get_local_player().m_coords;

		uint32_t ramps[] = { 0xB157C9E4, 0xF4F1511E, 0x93948E5E };
		for (int i = 0; i < 3; i++) {
			int counter = 0;
		search:
			Object ramp = native::get_closest_object_of_type(coords.x, coords.y, coords.z, 20.f, ramps[i], false, false, false);
			if (ramp) {
				if (native::does_entity_exist(ramp) && native::is_entity_attached_to_entity(ramp, menu::player::get_local_player().m_vehicle)) {
					menu::control::simple_request_model(ramp);

					native::set_entity_as_mission_entity(ramp, true, true);
					native::delete_entity(&ramp);

					counter++;

					if (counter < 20) {
						goto search;
					}
				}
			}
		}
	}
}

void vehicle_ramps_menu::load() {
	set_name("Ramps");
	set_parent<vehicle_menu>();

	add_option(number_option<int>(SCROLL, "Ramp Type")
		.add_translate()
		.add_number(m_vars.m_ramp_type, "%i", 1).add_min(1).add_max(3).show_max().add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Ramp Transparency")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_transparency).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Front Ramp")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_front_ramp).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Rear Ramp")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rear_ramp).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Left Ramp")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_left_ramp).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Right Ramp")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_right_ramp).add_savable(get_submenu_name_stack()));

	add_option(button_option("Apply Ramps")
		.add_translate().add_hotkey()
		.add_click(attach));

	add_option(button_option("Delete Attached Ramps")
		.add_translate().add_hotkey()
		.add_click(detach));
}

void vehicle_ramps_menu::update() {}

void vehicle_ramps_menu::update_once() {}

void vehicle_ramps_menu::feature_update() {}

vehicle_ramps_menu* g_instance;
vehicle_ramps_menu* vehicle_ramps_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_ramps_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}