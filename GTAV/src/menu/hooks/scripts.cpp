#include "hooks.h"
#include "menu/base/submenus/main/weapon/weapon_disables.h"

void menu::hooks::set_current_ped_weapon(rage::invoker::native_context* context) {
	if (!weapon::disables::vars::m_vars.m_interior_weapons && !weapon::disables::vars::m_vars.m_passive_weapons) {
		native::set_current_ped_weapon(context->get_argument<Ped>(0), context->get_argument<uint32_t>(1), context->get_argument<BOOL>(2));
	}
}

void menu::hooks::disable_control_action(rage::invoker::native_context* context) {
	if (!weapon::disables::vars::m_vars.m_interior_weapons && !weapon::disables::vars::m_vars.m_passive_weapons) {
		native::disable_control_action(context->get_argument<int>(0), context->get_argument<int>(1), context->get_argument<BOOL>(2));
	}
}

void menu::hooks::set_warning_message_2(rage::invoker::native_context*) {
	return;
}

void menu::hooks::terminate_this_thread(rage::invoker::native_context*) {
	global::vars::g_freemode_terminated = true;
	native::terminate_this_thread();
}