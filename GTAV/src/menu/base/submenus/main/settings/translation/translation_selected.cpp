#include "translation_selected.h"
#include "menu/base/submenu_handler.h"
#include "../translation.h"
#include "util/dirs.h"
#include "util/config.h"

using namespace settings::translation::selected::vars;

namespace settings::translation::selected::vars {
	variables m_vars;
}

void translation_selected_menu::load() {
	set_name("Translation");
	set_parent<translation_menu>();

	add_option(button_option("Load")
		.add_translate()
		.add_click([] { settings::translation::vars::load_translation(settings::translation::vars::m_vars.m_cached_translations[m_vars.m_selected].first); }));

	add_option(button_option("Delete")
		.add_translate()
		.add_click([] {
			remove(util::va::va("%s%s.json", util::dirs::get_path(translation), settings::translation::vars::m_vars.m_cached_translations[m_vars.m_selected].first.c_str()));
			menu::submenu::handler::set_submenu_previous(true);
		}));

	add_option(button_option("Set as Load Default")
		.add_translate()
		.add_click([this] { util::config::write_string(get_submenu_name_stack(), "Launch", settings::translation::vars::m_vars.m_cached_translations[m_vars.m_selected].first); }));

	std::string launch = util::config::read_string(get_submenu_name_stack(), "Launch", "-none-");
	if (launch.compare("-none-")) {
		settings::translation::vars::load_translation(launch);
	}
}

void translation_selected_menu::update() {}

void translation_selected_menu::update_once() {}

void translation_selected_menu::feature_update() {}

translation_selected_menu* g_instance;
translation_selected_menu* translation_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new translation_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}