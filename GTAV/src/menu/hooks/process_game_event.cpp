#include "hooks.h"
#include "util/caller.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/util/notify.h"
#include "util/log.h"
#include "util/util.h"
#include "menu/base/util/helpers.h"

struct event_player_spawn {
	char _0x0000[0x18];
	char m_name[0x20];
};

struct event_player_collected_ambient_pickup {
	char _0x0000[0x18];
	uint32_t m_pickup_hash;
	char _0x001c[0x4];
	int m_value;
	char _0x0024[0xc];
	uint32_t m_model;
};

static localization t_player_spawn("Player Spawn", true, true);
static localization t_just_spawned("just spawned", true, true);
static localization t_pickup_processing("Pickup Processing", true, true);

uint64_t menu::hooks::process_game_event(uint64_t _this) {
	uint64_t vtable = *(uint64_t*)_this;
	uint32_t id = caller::call<uint32_t>(*(uint64_t*)(vtable + 0x18), _this);

	switch (id) {
		case 164: { // CEventNetworkPlayerSpawn
			event_player_spawn* _event = (event_player_spawn*)_this;

			if (protection::events::vars::m_vars.m_player_spawns.notify()) {
				menu::notify::stacked(TRANSLATE(t_player_spawn), menu::helpers::clean_name(_event->m_name) + " " + TRANSLATE(t_just_spawned));
			}

			break;
		}

		case 166: { // CEventNetworkPlayerCollectedAmbientPickup
			event_player_collected_ambient_pickup* _event = (event_player_collected_ambient_pickup*)_this;

			if (protection::events::vars::m_vars.m_pickup_processing.enabled()) {
				if (protection::events::vars::m_vars.m_pickup_processing.notify()) {
					menu::notify::protection("LLLLLLLLLLLLLLLLLLLLLLLL", TRANSLATE(t_pickup_processing), false, protection::events::vars::m_vars.m_pickup_processing.block());
				}

				if (protection::events::vars::m_vars.m_pickup_processing.block()) {
					_event->m_value = 0;
					_event->m_pickup_hash = 0;
					_event->m_model = 0;
				}
			}

			break;
		}
	}

	return process_game_event_t(_this);
}