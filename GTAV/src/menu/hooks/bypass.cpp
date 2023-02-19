#include "hooks.h"
#include "util/log.h"
#include "util/caller.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "global/vars.h"
#include <vector>

std::vector<std::string> g_blocked_metrics = {
	"DIG",
	"XP_LOSS",
	"AWARD_XP",
	"CF",
	"CC",
	"CNR",
	"SCRIPT",
	"CHEAT",
	"AUX_DEUX",
	"WEATHER",
	"HARDWARE_OS",
	"HARDWARE_GPU",
	"HARDWARE_MOBO",
	"HARDWARE_MEM",
	"HARDWARE_CPU",
	"PCSETTINGS",
	"CASH_CREATED",
	"DR_PS",
	"UVC",
	"W_L",
	"ESVCS",
	"IDLEKICK",
	"GSCB",
	"GSINV",
	"GSCW",
	"GSINT",
	"EARN",
	"GARAGE_TAMPER"
};

void menu::hooks::add_metric_to_json_array(uint32_t ecx, uint64_t rdx, uint64_t r8, rage::network::metric* metric) {
	if (metric) {
		if (!strcmp(metric->get_name(), "SPAWN")) {
			util::fiber::pool::add([] {
				util::fiber::sleep(2000);
				global::vars::g_reapply_weapons = true;
			});
		}

		if (std::find(begin(g_blocked_metrics), end(g_blocked_metrics), metric->get_name()) != end(g_blocked_metrics)) {
			LOG_CUSTOM_DEV("AC", "Blocking metric %s", metric->get_name());
			return;
		}
	}

	return add_metric_to_json_array_t(ecx, rdx, r8, metric);
}

void menu::hooks::rockstar_integrity(uint64_t rcx) {
	*(uint64_t*)(rcx + 0x10) = global::vars::g_nullsub;
	return rockstar_integrity_t(rcx);
}

void menu::hooks::send_network_event(uint64_t net_table, uint64_t event) {
	if (event) {
		short type = *(short*)(event + 8);

		if (type == REPORT_MYSELF_EVENT || type == REPORT_CASH_SPAWN_EVENT || type == NETWORK_CHECK_CODE_CRCS_EVENT) {
			LOG_CUSTOM_DEV("AC", "Blocking network event - %i", type);

			uint64_t table = *(uint64_t*)event;
			caller::call<int>(*(uint64_t*)table, event, 1); // Deallocate event
			return;
		}
	}

	return send_network_event_t(net_table, event);
}

bool menu::hooks::process_transaction_id(uint64_t manager, int id, uint64_t table) {
	if (manager) {
		rage::network::transaction_node* node = *(rage::network::transaction_node**)(manager + 0x20);

		while (node) {
			if (node->m_transaction->m_transaction_id == id) {
				if (node->m_transaction->m_category == (int)0xAE04310C) {
					for (int i = 0; i < node->m_transaction->m_transaction_count; i++) {
						rage::network::transaction transaction = node->m_transaction->m_transactions[i];
						LOG_CUSTOM_DEV("Arxan", "%i %i %i %i %i", transaction.m_id, transaction.m_variation, transaction.m_price, transaction.m_multiplier, transaction.m_value);
					}

					LOG_CUSTOM_DEV("AC", "Blocked arxan report adding to queue");
					return false;
				}
			}

			node = node->m_next;
		}
	}

	return process_transaction_id_t(manager, id, table);
}

BOOL menu::hooks::get_thread_context(HANDLE thread, LPCONTEXT context) {
	BOOL ret = get_thread_context_t(thread, context);
	
	context->Dr0 = 0;
	context->Dr1 = 0;
	context->Dr2 = 0;
	context->Dr3 = 0;
	context->Dr6 = 0;
	context->Dr7 = 0;

	return ret;
}