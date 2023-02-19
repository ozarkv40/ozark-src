#include "ocean.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "ocean/ocean_tuning.h"
#include "ocean/ocean_quads.h"

using namespace world::ocean::vars;

namespace world::ocean::vars {
	variables m_vars;

	void ocean_loop(eOceanTypes type, std::function<void(uint64_t)> callback) {
		uint64_t quad_pool = 0;
		short quad_count = 0;

		switch (type) {
			case OCEAN_TYPE_OCEAN:
				quad_pool = global::vars::g_ocean_quads.m_ocean->m_quad_pool;
				quad_count = global::vars::g_ocean_quads.m_ocean->m_quad_count;
				break;

			case OCEAN_TYPE_WAVE:
				quad_pool = global::vars::g_ocean_quads.m_wave->m_quad_pool;
				quad_count = global::vars::g_ocean_quads.m_wave->m_quad_count;
				break;

			case OCEAN_TYPE_CALMING:
				quad_pool = global::vars::g_ocean_quads.m_calming->m_quad_pool;
				quad_count = global::vars::g_ocean_quads.m_calming->m_quad_count;
				break;
		}

		for (short i = 0; i < quad_count; i++) {
			switch (type) {
				case OCEAN_TYPE_OCEAN:
					callback((quad_pool + (i * sizeof(rage::types::ocean_quad))));
					break;

				case OCEAN_TYPE_WAVE:
					callback((quad_pool + (i * sizeof(rage::types::ocean_wave_quad))));
					break;

				case OCEAN_TYPE_CALMING:
					callback((quad_pool + (i * sizeof(rage::types::ocean_calming_quad))));
					break;
			}
		}
	}

	void ocean_task(eOceanTypes type, eOceanTasks task) {
		ocean_loop(type, [=](uint64_t pool) {
			switch (task) {
				case OCEAN_DISABLE: {
					rage::types::ocean_quad* quad = (rage::types::ocean_quad*)(pool);

					if (m_vars.m_disable_ocean && quad->m_height == 0.0f) {
						quad->m_height = -10000.0f;
					} else if (!m_vars.m_disable_ocean && quad->m_height == -10000.0f) {
						quad->m_height = 0.0f;
					}

					break;
				}

				case OCEAN_CLEAR: {
					rage::types::ocean_quad* quad = (rage::types::ocean_quad*)(pool);
					quad->m_alpha = m_vars.m_clear_ocean ? 0x01010101 : 0x1A1A1A1A;
					break;
				}

				case OCEAN_FIERCE: {
					rage::types::ocean_wave_quad* quad = (rage::types::ocean_wave_quad*)(pool);
					quad->m_amplitude = m_vars.m_fierce_ocean ? quad->m_amplitude + 2000 : quad->m_amplitude - 2000;
					break;
				}
			}
		});
	}
}

void ocean_menu::load() {
	set_name("Ocean");
	set_parent<world_menu>();

	add_option(submenu_option("Ocean Quads")
		.add_translate().add_hotkey()
		.add_submenu<ocean_quads_menu>());

	add_option(submenu_option("Ocean Tuning")
		.add_translate().add_hotkey()
		.add_submenu<ocean_tuning_menu>());

	add_option(toggle_option("Disable Ocean")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_ocean)
		.add_click([] { ocean_task(OCEAN_TYPE_OCEAN, OCEAN_DISABLE); }));

	add_option(toggle_option("Clear Ocean")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_clear_ocean)
		.add_click([] { ocean_task(OCEAN_TYPE_OCEAN, OCEAN_CLEAR); }));

	add_option(toggle_option("Fierce Ocean")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fierce_ocean)
		.add_click([] { ocean_task(OCEAN_TYPE_WAVE, OCEAN_FIERCE); }));

	add_option(toggle_option("Part Water")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_part_water));

	add_option(number_option<float>(SCROLL, "Wave Intensity")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_wave_intensity, "%.1f", 0.1f).add_min(0.f).add_max(10.f)
		.add_click([] { native::set_waves_intensity(m_vars.m_wave_intensity); }));
}

void ocean_menu::update() {}

void ocean_menu::update_once() {
	m_vars.m_wave_intensity = native::get_waves_intensity();
}

void ocean_menu::feature_update() {
	if (m_vars.m_part_water) {
		float offset[] = { -4, 4 };
		for (int i = 0; i < 5; i++) {
			math::vector3<float> current_coords = menu::player::get_local_player().m_coords;
			if (i < 2) current_coords.x += offset[(i % 2 == 0)];
			else if (i < 4) current_coords.y += offset[(i % 2 == 0)];
			native::modify_water(current_coords.x, current_coords.y, -500000.0f, 0.2f);
		}
	}
}

ocean_menu* g_instance;
ocean_menu* ocean_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ocean_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}