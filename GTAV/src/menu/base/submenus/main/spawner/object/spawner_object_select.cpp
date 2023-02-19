#include "spawner_object_select.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"

using namespace spawner::object::select::vars;

namespace spawner::object::select::vars {
	variables m_vars;
}

void spawner_object_select_menu::load() {
	set_name("Object Spawner");
	set_parent<spawner_menu>();
}

void spawner_object_select_menu::update() {}

void spawner_object_select_menu::update_once() {
	clear_options(0);

	for (int i = 0; i < m_vars.m_size; i++) {
		add_option(button_option(m_vars.m_list[i].m_name.get())
			.add_click([=] {
				spawner::vars::spawn_object(m_vars.m_list[i].m_result, m_vars.m_list[i].m_name.get());
			}));
	}
}

void spawner_object_select_menu::feature_update() {}

spawner_object_select_menu* g_instance;
spawner_object_select_menu* spawner_object_select_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_object_select_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}