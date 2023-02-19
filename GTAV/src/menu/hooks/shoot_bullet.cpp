#include "hooks.h"
#include "menu/base/submenus/main/world/bullet_tracers.h"
#include "menu/base/submenus/main/weapon/entity_gun.h"
#include "menu/base/submenus/main/protections.h"
#include <mutex>

std::mutex g_tracer_mutex;

__declspec(noinline) void add_tracer(math::vector3_<float> start_pos, math::vector3_<float> end_pos, void* shooter, rage::types::weapon_info* info) {
	using namespace world::tracers::vars;

	g_tracer_mutex.lock();

	tracer trace;
	trace.m_spawn_time = GetTickCount();
	trace.m_spawn_position = start_pos;
	trace.m_end_position = end_pos;
	trace.m_shooter = shooter;
	trace.m_weapon_info = info;
	trace.m_populated = true;

	m_vars.m_tracers[m_vars.m_tracer_current_index] = trace;
	m_vars.m_tracer_current_index++;
	m_vars.m_tracer_current_index %= 1000;

	g_tracer_mutex.unlock();
}

bool menu::hooks::shoot_bullet(rage::types::weapon* weapon, uint64_t shooter_info, math::vector3_<float>* start_pos, math::vector3_<float>* end_pos) {
	if (start_pos && end_pos && shooter_info) {
		add_tracer(*start_pos, *end_pos, *(void**)shooter_info, weapon->m_weapon_info);

		if (protection::vars::m_vars.m_disable_bullets) {
			void* shooter = *(void**)shooter_info;
			if (shooter) {
				if (is_valid_ptr(global::vars::g_ped_factory) && is_valid_ptr(global::vars::g_ped_factory->m_local_ped)) {
					if (shooter == global::vars::g_ped_factory->m_local_ped
						|| shooter == global::vars::g_ped_factory->m_local_ped->m_vehicle) {
						return shoot_bullet_t(weapon, shooter_info, start_pos, end_pos);
					}
				}
			}

			return true;
		}
	}
	
	return shoot_bullet_t(weapon, shooter_info, start_pos, end_pos);
}

bool menu::hooks::shoot_projectile(rage::types::weapon* weapon, uint64_t shooter_info, math::vector3_<float>* start_pos, math::vector3_<float>* end_pos) {
	if (start_pos && end_pos && shooter_info) {
		add_tracer(*start_pos, *end_pos, *(void**)shooter_info, weapon->m_weapon_info);

		if (protection::vars::m_vars.m_disable_projectiles) {
			void* shooter = *(void**)shooter_info;
			if (shooter) {
				if (is_valid_ptr(global::vars::g_ped_factory) && is_valid_ptr(global::vars::g_ped_factory->m_local_ped)) {
					if (shooter == global::vars::g_ped_factory->m_local_ped
						|| shooter == global::vars::g_ped_factory->m_local_ped->m_vehicle) {
						return shoot_projectile_t(weapon, shooter_info, start_pos, end_pos);
					}
				}
			}

			return true;
		}
	}

	return shoot_projectile_t(weapon, shooter_info, start_pos, end_pos);
}