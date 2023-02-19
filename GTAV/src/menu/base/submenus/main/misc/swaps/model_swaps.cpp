#include "model_swaps.h"
#include "menu/base/submenu_handler.h"
#include "../misc_swaps.h"
#include "util/memory/memory.h"
#include "menu/base/util/control.h"
#include "util/log.h"
#include "util/dirs.h"
#include "model_swaps_presets.h"
#include "model_swaps_add.h"
#include <fstream>
#include <filesystem>

using namespace misc::swaps::model::vars;

namespace misc::swaps::model::vars {
	variables m_vars;

	struct HashNode {
		uint32_t m_hash;
		uint16_t m_data;
		uint16_t m_padding;
		HashNode* m_next;
	};

	HashNode* find_model_in_map(uint32_t model) {
		uint16_t count = *(uint16_t*)memory::read_instruction(global::vars::g_get_model_info);
		HashNode** map = *(HashNode***)memory::read_instruction(global::vars::g_get_model_info + 0x21);

		for (uint16_t i = 0; i < count; i++) {
			for (HashNode* Current = map[i]; Current; Current = Current->m_next) {
				if (Current->m_hash == model) {
					return Current;
				}
			}
		}

		return nullptr;
	}

	void remove_swap(uint32_t original_model) {
		auto vit = std::find_if(begin(m_vars.m_swaps), end(m_vars.m_swaps), [=](model_swap& element) { return element.m_original_model == original_model; });
		if (vit != end(m_vars.m_swaps)) {
			HashNode* node = find_model_in_map(original_model);
			if (node) {
				node->m_data = vit->m_original_offset;
			}

			m_vars.m_swaps.erase(vit);
		}
	}

	bool add_swap(const char* original_model, const char* new_model, model_swap* out) {
		if (!strcmp(original_model, new_model)) {
			return false;
		}

		for (model_swap& swap : m_vars.m_swaps) {
			if (!strcmp(swap.m_original_name.c_str(), original_model)) {
				remove_swap(swap.m_original_model);
				break;
			}
		}

		uint32_t original_hash = 0;
		uint32_t new_hash = 0;

		if (original_model[0] == '0' && (original_model[1] == 'x' || original_model[1] == 'X')) {
			original_hash = (uint32_t)_strtoui64(original_model, 0, 0);
		} else {
			std::string string_name(original_model);
			if (std::find_if(string_name.begin(), string_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
				original_hash = (uint32_t)std::stoul(original_model);
			} else {
				original_hash = native::get_hash_key(original_model);
			}
		}

		if (new_model[0] == '0' && (new_model[1] == 'x' || new_model[1] == 'X')) {
			new_hash = (uint32_t)_strtoui64(new_model, 0, 0);
		} else {
			std::string string_name(new_model);
			if (std::find_if(string_name.begin(), string_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
				new_hash = (uint32_t)std::stoul(new_model);
			} else {
				new_hash = native::get_hash_key(new_model);
			}
		}

		menu::control::simple_request_model(original_hash);
		menu::control::simple_request_model(new_hash);

		if (!native::is_model_valid(original_hash) || !native::is_model_valid(new_hash)
			|| !native::is_model_in_cdimage(original_hash) || !native::is_model_in_cdimage(new_hash)) {
			return false;
		}

		HashNode* node = find_model_in_map(original_hash);
		if (node) {
			HashNode* new_node = find_model_in_map(new_hash);
			if (new_node) {
				model_swap swap;
				swap.m_original_model = original_hash;
				swap.m_new_model = new_hash;
				swap.m_original_name = original_model;
				swap.m_new_name = new_model;
				swap.m_original_offset = node->m_data;
				node->m_data = new_node->m_data;

				if (out) *out = swap;
				m_vars.m_swaps.push_back(swap);
				return true;
			}
		}

		return false;
	}

	void add_json(model_swap swap) {
		nlohmann::json json;

		try {
			if (std::filesystem::exists(util::dirs::get_path(model_swap))) {
				std::ifstream input(util::dirs::get_path(model_swap));
				if (input.good()) {
					input >> json;
					input.close();
				}

				json = json["models"];
				json[std::to_string(swap.m_original_model)]["model"] = swap.m_new_model;
				json[std::to_string(swap.m_original_model)]["enabled"] = true;

				std::ofstream output(util::dirs::get_path(model_swap));
				if (output.good()) {
					output << json.dump(4);
					output.close();
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void swap_existing(model_swap& instance) {
		add_json(instance);

		if (instance.m_toggled) {
			HashNode* node = find_model_in_map(instance.m_original_model);
			if (node) {
				HashNode* new_node = find_model_in_map(instance.m_new_model);
				if (new_node) {
					instance.m_original_offset = node->m_data;
					node->m_data = new_node->m_data;
				}
			}
		} else {
			HashNode* node = find_model_in_map(instance.m_original_model);
			if (node) {
				node->m_data = instance.m_original_offset;
			}
		}
	}

	void load_swaps(model_swaps_menu* _this) {
		try {
			std::ifstream input(util::dirs::get_path(model_swap));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				if (json.size() > 0) {
					json = json["models"];

					for (auto& it = json.begin(); it != json.end(); ++it) {
						nlohmann::json& element = *it;

						if (std::find_if(begin(m_vars.m_swaps), end(m_vars.m_swaps), [=](model_swap& swap) { return !strcmp(swap.m_original_name.c_str(), it.key().c_str()); }) == end(m_vars.m_swaps)) {
							model_swap swap;
							swap.m_original_name = it.key();
							swap.m_original_model = std::stoul(it.key());
							swap.m_new_model = element["model"].get<uint32_t>();
							swap.m_toggled = element["enabled"].get<bool>();

							if (swap.m_toggled) {
								add_swap(it.key().c_str(), std::to_string(element["model"].get<uint32_t>()).c_str());
							} else m_vars.m_swaps.push_back(swap);
						}
					}
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void model_swaps_menu::load() {
	set_name("Model Swaps");
	set_parent<misc_swaps_menu>();

	add_option(submenu_option("Add Swap")
		.add_translate().add_hotkey()
		.add_submenu<model_swaps_add_menu>());

	add_option(submenu_option("Presets")
		.add_translate().add_hotkey()
		.add_submenu<model_swaps_presets_menu>());

	add_option(break_option("Swaps")
		.add_translate());

	add_string("~m~None");
	add_string("Swapped with");
	load_swaps(this);
}

void model_swaps_menu::update() {}

void model_swaps_menu::update_once() {
	clear_options(3);

	for (model_swap& swap : m_vars.m_swaps) {
		add_option(toggle_option(swap.m_original_name)
			.add_toggle(swap.m_toggled)
			.add_click([&] { swap_existing(swap); })
			.add_tooltip(util::va::va("%s %s", get_string("Swapped with").c_str(), swap.m_new_name.c_str())));
	}

	if (m_vars.m_swaps.size() == 0) {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void model_swaps_menu::feature_update() {}

model_swaps_menu* g_instance;
model_swaps_menu* model_swaps_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new model_swaps_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}