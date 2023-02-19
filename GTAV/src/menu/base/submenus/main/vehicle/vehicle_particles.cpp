#include "vehicle_particles.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "global/lists.h"
#include "menu/base/util/timers.h"

using namespace vehicle::particles::vars;

namespace vehicle::particles::vars {
	variables m_vars;
}

void vehicle_particles_menu::load() {
	set_name("Particle FX");
	set_parent<vehicle_menu>();

	add_option(toggle_option("Toggle Particle FX")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<global::lists::particle>(SCROLL, "Particle")
		.add_translate()
		.add_scroll(m_vars.m_particle, 0, NUMOF(global::lists::g_particles), global::lists::g_particles).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Scale")
		.add_translate()
		.add_number(m_vars.m_scale, "%.2f", 0.01f).add_min(0.01f).add_max(10.f).set_scroll_speed(10).add_savable(get_submenu_name_stack()));

	add_option(break_option("Bones")
		.add_translate());
}

void vehicle_particles_menu::update() {}

void vehicle_particles_menu::update_once() {
	clear_options(3);

	for (int i = 0; i < NUMOF(global::lists::g_vehicle_bones); i++) {
		scroll_struct<const char*> bone = global::lists::g_vehicle_bones[i];

		if (native::get_entity_bone_index_by_name(menu::player::get_local_player().m_vehicle, bone.m_result) > 0) {
			add_option(toggle_option(bone.m_name.get())
				.add_toggle(m_vars.m_bones[i]));
		} else {
			m_vars.m_bones[i] = false;
		}
	}
}

void vehicle_particles_menu::feature_update() {
	static int timer[11];
	static int timer2[16];

	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_toggle) {
			for (int i = 0; i < NUMOF(global::lists::g_vehicle_bones); i++) {
				if (m_vars.m_bones[i]) {
					if (i == NUMOF(global::lists::g_vehicle_bones) - 1) {
						for (int j = 0; j < 16; j++) {
							int index = native::get_entity_bone_index_by_name(menu::player::get_local_player().m_vehicle, j == 0 ? "exhaust" : util::va::va("exhaust_%i", j));

							if (index) {
								math::vector3<float> coords = native::get_world_position_of_entity_bone(menu::player::get_local_player().m_vehicle, index);
								if (!coords.is_null()) {
									scroll_struct<global::lists::particle> particle = global::lists::g_particles[m_vars.m_particle];

									menu::timers::run_timed(&timer2[j], 100, [=] {
										native::request_named_ptfx_asset(particle.m_result.m_dict);
										native::use_particle_fx_asset_next_call(particle.m_result.m_dict);
										native::start_particle_fx_non_looped_at_coord2(particle.m_result.m_texture, coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false);
									});
								}
							}
						}
					} else {
						scroll_struct<const char*> bone = global::lists::g_vehicle_bones[i];
						int index = native::get_entity_bone_index_by_name(menu::player::get_local_player().m_vehicle, bone.m_result);

						if (index) {
							math::vector3<float> coords = native::get_world_position_of_entity_bone(menu::player::get_local_player().m_vehicle, index);
							if (!coords.is_null()) {
								scroll_struct<global::lists::particle> particle = global::lists::g_particles[m_vars.m_particle];

								menu::timers::run_timed(&timer[i], 100, [=] {
									native::request_named_ptfx_asset(particle.m_result.m_dict);
									native::use_particle_fx_asset_next_call(particle.m_result.m_dict);
									native::start_particle_fx_non_looped_at_coord2(particle.m_result.m_texture, coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false);
								});
							}
						} else {
							m_vars.m_bones[i] = false;
						}
					}
				}
			}
		}
	}
}

vehicle_particles_menu* g_instance;
vehicle_particles_menu* vehicle_particles_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_particles_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}