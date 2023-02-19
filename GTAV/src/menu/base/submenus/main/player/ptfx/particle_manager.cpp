#include "particle_manager.h"
#include "menu/base/submenu_handler.h"
#include "../particles.h"
#include "global/lists.h"
#include "menu/base/util/control.h"
#include "menu/base/util/timers.h"

using namespace player::ptfx::vars;

namespace player::ptfx::vars {
	variables m_vars;

	scroll_struct<int> type[] = {
		{ localization("Attach to Socket", true), 0 },
		{ localization("Current Position", true), 1 }
	};

	void start_particle(const char* dict, const char* texture, bool looped = false) {
		menu::control::request_particle({ dict, texture }, [=](std::pair<const char*, const char*> anim) {
			native::use_particle_fx_asset_next_call(anim.first);

			int handle = 0;
			if (m_vars.m_type == 0) {
				// stop current if exists
				auto vit = std::find_if(m_vars.m_looped_particles.begin(), m_vars.m_looped_particles.end(), [](looped_particle& element) {
					return element.m_bone == global::lists::g_ped_bones[m_vars.m_socket].m_result && element.m_loop_required;
				});

				if (vit != m_vars.m_looped_particles.end()) {
					native::remove_particle_fx(vit->m_handle, true);
				}

				handle = looped ? native::start_particle_fx_looped_on_entity_bone2(anim.second, menu::player::get_local_player().m_ped, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, native::get_ped_bone_index(menu::player::get_local_player().m_ped, global::lists::g_ped_bones[m_vars.m_socket].m_result), m_vars.m_scale, false, false, false, 0, 0, 0)
					: native::start_particle_fx_non_looped_on_ped_bone2(anim.second, menu::player::get_local_player().m_ped, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, global::lists::g_ped_bones[m_vars.m_socket].m_result, m_vars.m_scale, false, false, false);
			} else {
				// current position
				math::vector3<float> position = menu::player::get_local_player().m_coords;
				native::start_particle_fx_non_looped_at_coord2(anim.second, position.x, position.y, position.z, 0.f, 0.f, 0.f, m_vars.m_scale, false, false, false);
			}

			if ((m_vars.m_looped && m_vars.m_type == 0) || looped) {
				m_vars.m_looped_particles.push_back({ {anim.first, anim.second}, global::lists::g_ped_bones[m_vars.m_socket].m_result, m_vars.m_scale, global::lists::g_timers[m_vars.m_wait].m_result, handle, looped, 0 });
			}
		});
	}

	void update_particle_list(particle_manager_menu* this_) {
		this_->clear_options(7);

		if (m_vars.m_type == 0) {
			int max = m_vars.m_looped ? NUMOF(global::lists::g_particles) : 20;
			m_vars.m_radio.reset();
			m_vars.m_radio.m_selected = 0;

			for (int i = 0; i < max; i++) {
				scroll_struct<global::lists::particle> particle = global::lists::g_particles[i];
				this_->add_option(radio_option(particle.m_name.get())
					.add_radio(m_vars.m_radio)
					.add_click([=] { start_particle(particle.m_result.m_dict, particle.m_result.m_texture, particle.m_result.m_looped); }));
			}
		} else {
			for (scroll_struct<global::lists::particle> particle : global::lists::g_particles) {
				this_->add_option(button_option(particle.m_name.get())
					.add_click([=] { start_particle(particle.m_result.m_dict, particle.m_result.m_texture, particle.m_result.m_looped); }));
			}
		}
	}
}

void particle_manager_menu::load() {
	set_name("Particle Manager");
	set_parent<particle_menu>();

	add_option(button_option("Stop Particles")
		.add_translate().add_hotkey()
		.add_click([] {
			for (looped_particle& particle : m_vars.m_looped_particles) {
				native::remove_particle_fx(particle.m_handle, true);
			}

			m_vars.m_looped_particles.clear();
		})
		.add_tooltip("Stops running looped particles"));

	add_option(scroll_option<int>(SCROLL, "Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(type), type)
		.add_click([this] { update_particle_list(this); }));

	add_option(scroll_option<int>(SCROLL, "Selected Socket")
		.add_translate()
		.add_scroll(m_vars.m_socket, 0, NUMOF(global::lists::g_ped_bones), global::lists::g_ped_bones)
		.add_requirement([] { return m_vars.m_type == 0; }));

	add_option(scroll_option<uint32_t>(SCROLL, "Wait")
		.add_translate()
		.add_scroll(m_vars.m_wait, 0, NUMOF(global::lists::g_timers), global::lists::g_timers)
		.add_requirement([] { return m_vars.m_type == 0 && m_vars.m_looped; }));

	add_option(toggle_option("Looped")
		.add_translate()
		.add_toggle(m_vars.m_looped)
		.add_click([this] { update_particle_list(this); })
		.add_requirement([] { return m_vars.m_type == 0; }));

	add_option(number_option<float>(SCROLL, "Scale")
		.add_translate()
		.add_number(m_vars.m_scale, "%.2f", 0.01f).add_min(0.f).set_scroll_speed(10));

	add_option(break_option("Particles")
		.add_translate());
}

void particle_manager_menu::update() {}

void particle_manager_menu::update_once() {
	update_particle_list(this);
}

void particle_manager_menu::feature_update() {
	for (looped_particle& particle : m_vars.m_looped_particles) {
		if (!particle.m_loop_required) {
			menu::timers::run_timed(&particle.m_timer, particle.m_wait, [=] {
				native::use_particle_fx_asset_next_call(particle.m_asset.first);
				native::start_particle_fx_non_looped_on_ped_bone2(particle.m_asset.second, menu::player::get_local_player().m_ped, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, particle.m_bone, particle.m_scale, false, false, false);
			});
		}
	}
}

particle_manager_menu* g_instance;
particle_manager_menu* particle_manager_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new particle_manager_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
