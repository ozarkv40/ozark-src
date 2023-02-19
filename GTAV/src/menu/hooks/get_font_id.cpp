#include "hooks.h"
#include "util/caller.h"
#include "menu/base/util/fonts.h"
#include "util/log.h"

void* menu::hooks::get_font_id(uint64_t font, int id) {
	std::vector<menu::fonts::font_context> fonts = menu::fonts::get_list();
	for (menu::fonts::font_context font_ : fonts) {
		if (font_.m_font_id == id) {
			return caller::call<void*>(global::vars::g_get_font_id_table, font, font_.m_font_name.c_str());
		}
	}

	return get_font_id_t(font, id);
}