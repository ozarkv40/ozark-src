#include "hooks.h"
#include "menu/base/submenus/main/misc.h"

bool menu::hooks::has_ros_privilege(uint64_t ros_table, int privilege) {
	if (misc::vars::m_vars.m_rockstar_developer_perks) {
		if (privilege == 12) {
			return true;
		}
	}

	return has_ros_privilege_t(ros_table, privilege);
}