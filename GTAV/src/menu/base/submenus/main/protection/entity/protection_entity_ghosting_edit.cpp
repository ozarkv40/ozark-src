#include "protection_entity_ghosting_edit.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/util/timers.h"

using namespace protection::entity::ghosting::edit::vars;

namespace protection::entity::ghosting::edit::vars {
	variables m_vars;

	void update_config() {

	}
}

void protection_entity_ghosting_edit_menu::load() {
	set_name("Spawn Ghosting");
	set_parent<protection_entity_ghosting_menu>();

	add_string("Ghost for Session");
	add_string("Ghost for Player");
}

void protection_entity_ghosting_edit_menu::update() {
	if (!m_vars.m_ready) return;

	static int timer = 0;
	menu::timers::run_timed(&timer, 250, [this] {
		clear_options(2);

		menu::player::for_each([this](menu::player::player_context& player) {
			add_option(toggle_option(player.m_name)
				.add_toggle(player.m_ghost[m_vars.m_selected->m_type]));
		}, true, true);
	});
}

void protection_entity_ghosting_edit_menu::update_once() {
	clear_options(0);

	add_option(toggle_option(get_string("Ghost for Session"))
		.add_toggle(m_vars.m_selected->m_enabled_for_session)
		.add_click(update_config));

	add_option(break_option(get_string("Ghost for Player")));

	m_vars.m_ready = true;
}

void protection_entity_ghosting_edit_menu::feature_update() {}

protection_entity_ghosting_edit_menu* g_instance;
protection_entity_ghosting_edit_menu* protection_entity_ghosting_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_entity_ghosting_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}