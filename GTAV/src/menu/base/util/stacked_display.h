#pragma once
#include "stdafx.h"
#include <unordered_map>

namespace menu::display {
	struct stacked_display_context {
		bool m_rendering = false;
		std::string m_id;
		std::string m_key;
		std::string m_value;
		long long m_add_time = 0;
	};

	class stacked_display {
	public:
		void render();
		void update(std::string id, std::string key, std::string value);
		void disable(std::string id);
	private:
		std::vector<stacked_display_context> m_messages;
	};

	stacked_display* get_stacked_display();

	inline void render() {
		get_stacked_display()->render();
	}

	inline void update(std::string id, std::string key, std::string value) {
		get_stacked_display()->update(id, key, value);
	}

	inline void disable(std::string id) {
		get_stacked_display()->disable(id);
	}
}