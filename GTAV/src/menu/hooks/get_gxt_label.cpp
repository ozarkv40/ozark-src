#include "hooks.h"
#include "menu/base/base.h"
#include "util/util.h"
#include "util/log.h"

const char* menu::hooks::get_gxt_label(uint64_t table, const char* label) {
	if (label && !strcmp(label, "Ozark")) {
		return menu::base::get_keyboard_title().c_str();
	}

	return get_gxt_label_t(table, label);
}

const char* menu::hooks::get_gxt_label_from_hash(uint64_t table, uint32_t label_hash) {
	if (label_hash == joaat("Ozark")) {
		return "Ozark";
	}

	return get_gxt_label_from_hash_t(table, label_hash);
}