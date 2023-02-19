#pragma once
#include "stdafx.h"
#include <vector>

namespace menu::fonts {
	struct font_context {
		std::string m_font_name;
		int m_font_id = -1;
		int m_asset_id = -1;
	};
	
	class fonts {
	public:
		void load();
		void update();
		void update_queue();

		int get_font_id(std::string name);

		std::vector<font_context>& get_list() { return m_fonts; }
	private:
		std::vector<font_context> m_fonts;
	};

	fonts* get_fonts();

	inline void load() {
		get_fonts()->load();
	}

	inline void update() {
		get_fonts()->update();
	}

	inline void update_queue() {
		get_fonts()->update_queue();
	}

	inline int get_font_id(std::string name) {
		return get_fonts()->get_font_id(name);
	}

	inline std::vector<font_context>& get_list() {
		return get_fonts()->get_list();
	}
}