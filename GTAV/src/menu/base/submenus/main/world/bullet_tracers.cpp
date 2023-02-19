#include "bullet_tracers.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "global/lists.h"
#include "rage/engine.h"
#include "../helper/helper_color.h"

using namespace world::tracers::vars;

namespace world::tracers::vars {
	variables m_vars;

	scroll_struct<int> colors[] = {
		{ localization("NPC", true), 0 },
		{ localization("Player", true), 1 },
		{ localization("Self", true), 2 },
	};
}

void bullet_tracers_menu::load() {
	set_name("Bullet Tracers");
	set_parent<world_menu>();

	add_option(scroll_option<uint32_t>(TOGGLE, "Toggle NPC")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_npc)
		.add_scroll(m_vars.m_npc_timer, 1, NUMOF(global::lists::g_timers), global::lists::g_timers)
		.add_tooltip("The max time a tracer will show up for NPCs"));

	add_option(scroll_option<uint32_t>(TOGGLE, "Toggle Player")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_player)
		.add_scroll(m_vars.m_player_timer, 1, NUMOF(global::lists::g_timers), global::lists::g_timers)
		.add_tooltip("The max time a tracer will show up for players"));

	add_option(scroll_option<uint32_t>(TOGGLE, "Toggle Self")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_self)
		.add_scroll(m_vars.m_self_timer, 1, NUMOF(global::lists::g_timers), global::lists::g_timers)
		.add_tooltip("The max time a tracer will show up for self"));

	add_option(break_option("Colors")
		.add_translate());

	add_option(scroll_option<int>(SCROLL, "Selected Color")
		.add_translate().add_hotkey()
		.add_hover([] { menu::renderer::render_color_preview(m_vars.m_colors[m_vars.m_selected_color]); })
		.add_scroll(m_vars.m_selected_color, 0, NUMOF(colors), colors));

	add_option(submenu_option("Edit Color")
		.add_translate()
		.add_submenu<helper_color_menu>()
		.add_click([this] {
			helper_color_menu::get()->set_name(colors[m_vars.m_selected_color].m_name.get(), false, false);
			helper_color_menu::get()->set_parent<bullet_tracers_menu>();
			helper::color::vars::m_vars.m_color = &m_vars.m_colors[m_vars.m_selected_color];
			helper::color::vars::m_vars.m_callback = [] {};
		})
		.add_update([] (submenu_option* option, int position) {
			option->add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, &m_vars.m_colors[m_vars.m_selected_color]);
		}));
}

void bullet_tracers_menu::update() {}

void bullet_tracers_menu::update_once() {}

void bullet_tracers_menu::feature_update() {
	if (m_vars.m_npc || m_vars.m_player || m_vars.m_self) {
		for (int i = 0; i < NUMOF(m_vars.m_tracers); i++) {
			tracer& trace = m_vars.m_tracers[i];

			if (trace.m_populated) {
				if (is_valid_ptr(trace.m_shooter) && is_valid_vtable(*(uint64_t*)((uint64_t)(trace.m_shooter)))) {
					rage::types::ped* ped = (rage::types::ped*)trace.m_shooter;
					rage::types::vehicle* vehicle = (rage::types::vehicle*)trace.m_shooter;

					if (m_vars.m_self) {
						if (is_valid_ptr(global::vars::g_ped_factory) && is_valid_ptr(global::vars::g_ped_factory->m_local_ped)) {
							if (trace.m_shooter == global::vars::g_ped_factory->m_local_ped || trace.m_shooter == global::vars::g_ped_factory->m_local_ped->m_vehicle) {
								native::draw_line(trace.m_spawn_position.x, trace.m_spawn_position.y, trace.m_spawn_position.z, trace.m_end_position.x, trace.m_end_position.y, trace.m_end_position.z, m_vars.m_colors[2].r, m_vars.m_colors[2].g, m_vars.m_colors[2].b, m_vars.m_colors[2].a);

								if (GetTickCount() - trace.m_spawn_time > global::lists::g_timers[m_vars.m_self_timer].m_result) {
									trace.m_populated = false;
								}

								continue;
							}
						}
					}

					Entity handle = rage::engine::get_entity_handle((uint64_t)trace.m_shooter);
					if (m_vars.m_npc) {
						if (native::does_entity_exist(handle)) {
							Entity new_handle = handle;
							if (native::is_entity_a_vehicle(handle)) {
								Ped driver = native::get_ped_in_vehicle_seat(handle, -1, 0);
								if (native::does_entity_exist(driver)) {
									new_handle = driver;
								}
							}
							
							if (native::is_entity_a_ped(new_handle) && !native::is_ped_a_player(new_handle)) {
								native::draw_line(trace.m_spawn_position.x, trace.m_spawn_position.y, trace.m_spawn_position.z, trace.m_end_position.x, trace.m_end_position.y, trace.m_end_position.z, m_vars.m_colors[0].r, m_vars.m_colors[0].g, m_vars.m_colors[0].b, m_vars.m_colors[0].a);

								if (GetTickCount() - trace.m_spawn_time > global::lists::g_timers[m_vars.m_npc_timer].m_result) {
									trace.m_populated = false;
								}

								continue;
							}
						}
					}

					if (m_vars.m_player) {
						bool run = false;

						if (is_valid_ptr(global::vars::g_ped_factory->m_local_ped)) {
							if (trace.m_shooter == global::vars::g_ped_factory->m_local_ped) {
								goto ex;
							}
						}

						if (is_valid_ptr(ped->get_net_obj())) {
							if (ped->get_net_obj()->m_type == NetObjectPlayer) {
								run = true;
								goto ex;
							}

							if (native::does_entity_exist(handle)) {
								if (native::is_entity_a_vehicle(handle)) {
									menu::player::for_each([&](menu::player::player_context& context) {
										if (run) return;

										if (is_valid_ptr(context.m_ped_ptr)) {
											if (is_valid_ptr(context.m_ped_ptr->m_ped_weapon_manager)) {
												if (context.m_ped_ptr->m_ped_weapon_manager->get_vehicle_weapon() == trace.m_weapon_info) {
													run = true;
												}
											}
										}
									});
								}
							}
						}

					ex:
						if (run) {
							native::draw_line(trace.m_spawn_position.x, trace.m_spawn_position.y, trace.m_spawn_position.z, trace.m_end_position.x, trace.m_end_position.y, trace.m_end_position.z, m_vars.m_colors[1].r, m_vars.m_colors[1].g, m_vars.m_colors[1].b, m_vars.m_colors[1].a);

							if (GetTickCount() - trace.m_spawn_time > global::lists::g_timers[m_vars.m_player_timer].m_result) {
								trace.m_populated = false;
							}

							continue;
						}
					}

					if (GetTickCount() - trace.m_spawn_time > 3000) {
						trace.m_populated = false;
					}
				}
			}
		}
	}
}

bullet_tracers_menu* g_instance;
bullet_tracers_menu* bullet_tracers_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new bullet_tracers_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}