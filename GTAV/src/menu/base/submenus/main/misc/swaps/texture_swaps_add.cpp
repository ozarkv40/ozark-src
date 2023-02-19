#include "texture_swaps_add.h"
#include "menu/base/submenu_handler.h"
#include "texture_swaps.h"
#include "util/fiber_pool.h"
#include "menu/base/util/textures.h"

using namespace misc::swaps::texture::add::vars;

namespace misc::swaps::texture::add::vars {
	variables m_vars;

	scroll_struct<int> textures[200];
}

void texture_swaps_add_menu::load() {
	set_name("Add Swap");
	set_parent<texture_swaps_menu>();

	m_vars.m_options.push_back(add_option(button_option("Input Dictionary")
		.add_translate()
		.add_keyboard("Input the dictionary! (Hint: name, hash or numeric)", 100, [](button_option* option, const char* dictionary) { m_vars.m_asset.first = dictionary; })));

	m_vars.m_options.push_back(add_option(button_option("Input Texture")
		.add_translate()
		.add_keyboard("Input the texture! (Hint: name, hash or numeric)", 100, [](button_option* option, const char* texture) { m_vars.m_asset.second = texture; })));

	m_vars.m_options.push_back(add_option(scroll_option<int>(SCROLL, "Image")
		.add_translate()
		.add_scroll(m_vars.m_image, 0, NUMOF(textures), textures)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_image, 0, (int)menu::textures::get_list().size(), textures);
		})));

	m_vars.m_options.push_back(add_option(button_option("Add Swap")
		.add_translate()
		.add_click([] {
			if (!m_vars.m_asset.first.empty() && !m_vars.m_asset.second.empty()) {
				util::fiber::pool::add([] {
					misc::swaps::texture::vars::texture_swap* swap = new misc::swaps::texture::vars::texture_swap();
					swap->m_asset = m_vars.m_asset;
					swap->m_texture = menu::textures::get_list()[m_vars.m_image].m_name;
					swap->m_toggled = true;

					if (misc::swaps::texture::vars::add_swap(swap)) {
						misc::swaps::texture::vars::add_json(swap);
						misc::swaps::texture::vars::m_vars.m_swaps.push_back(swap);

						menu::submenu::handler::set_submenu_previous(true);
					}
				});
			}
		})));

	add_string("Dictionary");
	add_string("Texture");
}

void texture_swaps_add_menu::update() {
	char tooltip[100];
	sprintf_s(tooltip, "%s=%s %s=%s", get_string("Dictionary").c_str(),
		m_vars.m_asset.first.empty() ? "~italic~unset~s~" : m_vars.m_asset.first.c_str(),
		get_string("Texture").c_str(),
		m_vars.m_asset.second.empty() ? "~italic~unset~s~" : m_vars.m_asset.second.c_str());

	for (std::shared_ptr<base_option>& option : m_vars.m_options) {
		option->set_tooltip(tooltip);
	}
}

void texture_swaps_add_menu::update_once() {
	menu::textures::update();

	m_vars.m_image = 0;
	m_vars.m_asset.first.clear();
	m_vars.m_asset.second.clear();

	for (std::size_t i = 0; i < menu::textures::get_list().size(); i++) {
		if (i == 200) break;
		textures[i].m_name = menu::textures::get_list()[i].m_name;
		textures[i].m_result = (int)i;
	}
}

void texture_swaps_add_menu::feature_update() {}

texture_swaps_add_menu* g_instance;
texture_swaps_add_menu* texture_swaps_add_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new texture_swaps_add_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}