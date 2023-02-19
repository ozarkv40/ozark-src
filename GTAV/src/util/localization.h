#pragma once
#include "stdafx.h"

class localization {
public:
	localization();
	localization(std::string original, bool translate = false, bool global_register = false);

	void reset();
	void set(std::string str);
	void set_mapped(std::string str);
	void set_translate(bool translate);
	void register_translation();

	std::string get_original();
	std::string get();
	bool has_translation();
private:
	bool m_translate = false;
	std::string m_original;
	std::string m_mapped;
};