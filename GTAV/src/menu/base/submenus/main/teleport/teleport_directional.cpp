#include "teleport_directional.h"
#include "menu/base/submenu_handler.h"
#include "../teleport.h"

using namespace teleport::directional::vars;

namespace teleport::directional::vars {
	variables m_vars;

	void teleport_direction(int direction) {
		math::vector3<float> coords = { 0.f, 0.f, 0.f };

		switch (direction) {
			case 0:
				coords.y = m_vars.m_directions[0] + 1.f;
				break;
			case 1:
				coords.y = (m_vars.m_directions[1] * -1.f) + 1.f;
				break;
			case 2:
				coords.z = m_vars.m_directions[2] + 1.f;
				break;
			case 3:
				coords.z = (m_vars.m_directions[3] * -1.f) + 1.f;
				break;
			case 4:
				coords.x = (m_vars.m_directions[4] * -1.f) + 1.f;
				break;
			case 5:
				coords.x = m_vars.m_directions[5] + 1.f;
				break;
		}

		bool use_vehicle = teleport::vars::m_vars.m_include_current_vehicle;
		Entity entity = use_vehicle && menu::player::get_local_player().m_in_vehicle ? menu::player::get_local_player().m_vehicle : menu::player::get_local_player().m_ped;

		math::vector3<float> velocity;
		if (use_vehicle && menu::player::get_local_player().m_in_vehicle) {
			velocity = native::get_entity_velocity(menu::player::get_local_player().m_vehicle);
		}

		math::vector3<float> world = native::get_offset_from_entity_in_world_coords(entity, coords.x, coords.y, coords.z);
		native::set_entity_coords_no_offset(entity, world.x, world.y, world.z, false, false, false);

		if (use_vehicle && menu::player::get_local_player().m_in_vehicle) {
			native::set_entity_velocity(entity, velocity.x, velocity.y, velocity.z);
			native::set_vehicle_engine_on(entity, true, true, true);
		}
	}
}

void teleport_directional_menu::load() {
	set_name("Directional");
	set_parent<teleport_menu>();

	add_option(number_option<float>(SCROLLSELECT, "Forwards")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_directions[0], "%.0f", 1.f).add_min(1.f).add_max(100.f)
		.add_click([] { teleport_direction(0); }));

	add_option(number_option<float>(SCROLLSELECT, "Backwards")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_directions[1], "%.0f", 1.f).add_min(1.f).add_max(100.f)
		.add_click([] { teleport_direction(1); }));

	add_option(number_option<float>(SCROLLSELECT, "Above")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_directions[2], "%.0f", 1.f).add_min(1.f).add_max(100.f)
		.add_click([] { teleport_direction(2); }));

	add_option(number_option<float>(SCROLLSELECT, "Below")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_directions[3], "%.0f", 1.f).add_min(1.f).add_max(100.f)
		.add_click([] { teleport_direction(3); }));

	add_option(number_option<float>(SCROLLSELECT, "Left")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_directions[4], "%.0f", 1.f).add_min(1.f).add_max(100.f)
		.add_click([] { teleport_direction(4); }));

	add_option(number_option<float>(SCROLLSELECT, "Right")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_directions[5], "%.0f", 1.f).add_min(1.f).add_max(100.f)
		.add_click([] { teleport_direction(5); }));
}

void teleport_directional_menu::update() {}

void teleport_directional_menu::update_once() {}

void teleport_directional_menu::feature_update() {}

teleport_directional_menu* g_instance;
teleport_directional_menu* teleport_directional_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new teleport_directional_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}