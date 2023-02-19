#include "hooks.h"
#include "menu/base/submenus/main/protection/protection_anti_detection.h"

void menu::hooks::write_ped_health_data_node(uint64_t rcx, uint64_t rdx) {
	write_ped_health_data_node_t(rcx, rdx);

	if (global::vars::g_ped_factory) {
		rage::types::ped* ped = *(rage::types::ped**)(rcx - 0x1b0);
		if (ped) {
			if (ped == global::vars::g_ped_factory->m_local_ped) {
				if (protection::detection::vars::m_vars.m_health) {
					if (*(int*)(rdx + 0xC4) > 328) {
						*(int*)(rdx + 0xC4) = 328;
					}
				}

				if (protection::detection::vars::m_vars.m_armor) {
					if (*(int*)(rdx + 0xC8) > 50) {
						*(int*)(rdx + 0xC8) = 50;
					} else {
						if ((*(int*)(rdx + 0xC8) % 50) != 0) {
							*(int*)(rdx + 0xC8) = 0;
						}
					}
				}
			}
		}
	}
}