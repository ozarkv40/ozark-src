#include "hooks.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/util/helpers.h"
#include "util/log.h"

static localization t_rockstar_staff("Rockstar Staff", true, true);
static localization t_detected_rockstar_staff("has been detected as R* staff!", true, true);

void menu::hooks::process_relay_usage(uint8_t cl, uint64_t rdx, rage::network::event_added_gamer* gamer, uint32_t r9d, uint64_t stack) {
	if (*(uint8_t*)(stack + 0x1E) == 1 || *(uint8_t*)(stack + 0x1E) == 2) {
		uint32_t ip = *(uint32_t*)(stack + 8);
		if (ip != 0xFFFFFFFF) {
			uint32_t my_ip = *(uint32_t*)(stack);

			LOG_DEV("%i.%i.%i.%i -> %i.%i.%i.%i",
				((ip & 0xFF000000) >> 24), ((ip & 0xFF0000) >> 16), ((ip & 0xFF00) >> 8), (ip & 0xFF),
				((my_ip & 0xFF000000) >> 24), ((my_ip & 0xFF0000) >> 16), ((my_ip & 0xFF00) >> 8), (my_ip & 0xFF));

			bool insert = true;
			for (relay_usage& usage : global::vars::g_relay_usage) {
				if (!strcmp(usage.m_name, gamer->m_name) && usage.m_rockstar_id == gamer->m_rockstar_id) {
					usage.m_external_ip = ip;
					insert = false;
					break;
				}
			}

			if (menu::helpers::is_rockstar_ip(ip)) {
				if (protection::events::vars::m_vars.m_rockstar_staff.notify()) {
					menu::notify::stacked(TRANSLATE(t_rockstar_staff), util::va::va("%s %s", gamer->m_name, TRANSLATE(t_detected_rockstar_staff)), global::ui::g_error);
				}
			}

			if (insert) {
				global::vars::g_geo_queue.push(ip);

				relay_usage relay;
				relay.m_external_ip = ip;
				relay.m_rockstar_id = gamer->m_rockstar_id;
				strcpy_s(relay.m_name, gamer->m_name);
				global::vars::g_relay_usage.push_back(relay);

				char buffer[32];
				sprintf_s(buffer, "%i.%i.%i.%i", ((ip & 0xFF000000) >> 24), ((ip & 0xFF0000) >> 16), ((ip & 0xFF00) >> 8), (ip & 0xFF));
				LOG("[%s:%i] IP=%s", gamer->m_name, gamer->m_rockstar_id, buffer);
			}
		}
	}

	process_relay_usage_t(cl, rdx, gamer, r9d, stack);
}