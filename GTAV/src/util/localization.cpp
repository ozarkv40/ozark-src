#include "localization.h"
#include "global/vars.h"

localization::localization() {}

localization::localization(std::string original, bool translate, bool global_register) {
	if (global_register) {
		register_translation();
	}

	m_translate = translate;
	set(original);
}

void localization::reset() {
	set_mapped(m_original);
}

void localization::set(std::string str) {
	m_original = str;
	set_mapped(m_original);
}

void localization::set_mapped(std::string str) {
	m_mapped = str;
}

void localization::set_translate(bool translate) {
	m_translate = translate;
}

void localization::register_translation() {
	global::vars::g_localization_table.push_back(this);
}

std::string localization::get_original() {
	return m_original;
}

std::string localization::get() {
	return m_translate ? m_mapped : m_original;
}

bool localization::has_translation(){
	return m_translate;
}