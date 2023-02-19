#pragma once
#include "menu/base/submenu.h"

class model_swaps_menu : public menu::submenu::submenu {
public:
	static model_swaps_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	model_swaps_menu()
		: menu::submenu::submenu() {}
};

namespace misc::swaps::model::vars {
	struct model_swap {
		uint32_t m_original_model = 0;
		uint32_t m_new_model = 0;

		uint16_t m_original_offset = 0;

		// UI
		std::string m_original_name = "";
		std::string m_new_name = "";
		bool m_toggled = true;
	};

	struct variables {
		std::vector<model_swap> m_swaps;
	};

	void add_json(model_swap swap);
	bool add_swap(const char* original_model, const char* new_model, model_swap* out = nullptr);
	void remove_swap(uint32_t original_model);
	extern variables m_vars;
}