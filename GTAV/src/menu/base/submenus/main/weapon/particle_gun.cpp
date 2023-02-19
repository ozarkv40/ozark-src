#include "particle_gun.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "global/lists.h"
#include "menu/base/util/control.h"
#include "menu/base/util/raycast.h"

using namespace weapon::particle::vars;

namespace weapon::particle::vars {
	variables m_vars;
}

void particle_gun_menu::load() {
	set_name("Particle Gun");
	set_parent<weapon_mods_menu>();

	add_option(toggle_option("Toggle Particle Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Scale")
		.add_translate()
		.add_number(m_vars.m_scale, "%.2f", 0.01f).add_min(0.f).add_max(10.f).set_scroll_speed(10).show_max().add_savable(get_submenu_name_stack()));

	add_option(break_option("Particles")
		.add_translate());
}

void particle_gun_menu::update() {}

void particle_gun_menu::update_once() {
	clear_options(3);

	for (int i = 0; i < 20; i++) {
		add_option(radio_option(global::lists::g_particles[i].m_name.get())
			.add_radio(m_vars.m_radio));
	}
}

void particle_gun_menu::feature_update() {
	if (m_vars.m_toggle) {
		if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
			menu::raycast cast = menu::raycast_infront(9999.f);
			if (!cast.get_coords().is_null()) {
				if (cast.get_coords().get_distance(menu::player::get_local_player().m_coords) > 3.5f) {
					scroll_struct<global::lists::particle> particle = global::lists::g_particles[m_vars.m_radio.m_selected];
					math::vector3<float> position = cast.get_coords();

					menu::control::request_particle({ particle.m_result.m_dict, particle.m_result.m_texture }, [=](std::pair<const char*, const char*> anim) {
						native::use_particle_fx_asset_next_call(anim.first);
						native::start_particle_fx_non_looped_at_coord2(anim.second, position.x, position.y, position.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false);
					});
				}
			}
		}
	}
}

particle_gun_menu* g_instance;
particle_gun_menu* particle_gun_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new particle_gun_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
