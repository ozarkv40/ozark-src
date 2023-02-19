#include "ocean_quads.h"
#include "menu/base/submenu_handler.h"
#include "../ocean.h"
#include "ocean_quads_edit.h"

using namespace world::ocean::quads::vars;

namespace world::ocean::quads::vars {
	variables m_vars;

	scroll_struct<world::ocean::vars::eOceanTypes> ocean_types[] = {
		{ localization("Ocean", true), world::ocean::vars::OCEAN_TYPE_OCEAN },
		{ localization("Calming", true), world::ocean::vars::OCEAN_TYPE_CALMING },
		{ localization("Wave", true), world::ocean::vars::OCEAN_TYPE_WAVE }
	};

	math::vector3<float> get_quad_coords(uint64_t address) {
		rage::types::ocean_quad* water_quad_coords = (rage::types::ocean_quad*)address;

		math::vector3<float> coords = { 0.f, 0.f, 0.f };
		coords.x = (float)(water_quad_coords->m_min.x + water_quad_coords->m_max.x) / 2.0f;
		coords.y = (float)(water_quad_coords->m_min.y + water_quad_coords->m_max.y) / 2.0f;

		if (m_vars.m_type == 0) {
			coords.z = water_quad_coords->m_height;
		}

		return coords;
	}

	void cache_closest() {
		m_vars.m_closest_quad = 0;

		float distance = std::numeric_limits<float>::max();
		world::ocean::vars::ocean_loop(ocean_types[m_vars.m_type].m_result, [&](uint64_t pool) {
			float d = get_quad_coords(pool).get_distance(menu::player::get_local_player().m_coords);
			if (d < distance) {
				distance = d;
				m_vars.m_closest_quad = pool;
			}
		});
	}

	void quad_esp() {
		if (m_vars.m_closest_quad) {
			menu::renderer::draw_line(menu::player::get_local_player().m_coords, get_quad_coords(m_vars.m_closest_quad), { 255, 255, 255, 255 });
		}
	}
}

void ocean_quads_menu::load() {
	set_name("Ocean Quads");
	set_parent<ocean_menu>();

	add_option(scroll_option<world::ocean::vars::eOceanTypes>(SCROLL, "Quad Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(ocean_types), ocean_types));

	add_option(submenu_option("Edit Nearest Quad")
		.add_translate().add_hotkey()
		.add_submenu<ocean_quads_edit_menu>()
		.add_hover([](submenu_option*) { cache_closest(); quad_esp(); }));
}

void ocean_quads_menu::update() {}

void ocean_quads_menu::update_once() {}

void ocean_quads_menu::feature_update() {}

ocean_quads_menu* g_instance;
ocean_quads_menu* ocean_quads_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ocean_quads_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}