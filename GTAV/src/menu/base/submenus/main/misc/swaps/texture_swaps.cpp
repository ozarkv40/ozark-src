#include "texture_swaps.h"
#include "menu/base/submenu_handler.h"
#include "../misc_swaps.h"
#include "util/dirs.h"
#include "util/log.h"
#include "util/fiber_pool.h"
#include "util/memory/memory.h"
#include "rage/engine.h"
#include "menu/base/util/textures.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/control.h"
#include "texture_swaps_add.h"
#include <fstream>
#include <filesystem>

using namespace misc::swaps::texture::vars;

namespace misc::swaps::texture::vars {
	variables m_vars;

	rage::types::dictionary_pool* find_dictionary(std::string dict) {
		uint32_t hash = native::get_hash_key(dict.c_str());
		uint32_t texture_hash = native::get_hash_key(("platform:/textures/" + dict).c_str());

		rage::types::texture_store* txd = global::vars::g_texture_store;
		if (is_valid_ptr(txd) && is_valid_ptr(txd->m_pool) && is_valid_ptr(txd->m_mask)) {
			rage::types::dictionary_pool* pool = txd->m_pool;
			for (uint32_t i = 0; i < txd->m_count; i++) {
				if (~(txd->m_mask[i] >> 7) & 1) {
					rage::types::dictionary_pool element = pool[i];
					if (is_valid_ptr(element.m_pool)) {
						if (element.m_dictionary_hash == hash || element.m_dictionary_hash == texture_hash) {
							return &pool[i];
						}
					}
				}
			}
		}

		return nullptr;
	}

	rage::types::grc_texture_dx11* find_texture(std::string dict, std::string name) {
		uint32_t hash = native::get_hash_key(dict.c_str());
		uint32_t texture_hash = native::get_hash_key(("platform:/textures/" + dict).c_str());

		rage::types::texture_store* txd = global::vars::g_texture_store;
		if (is_valid_ptr(txd) && is_valid_ptr(txd->m_pool) && is_valid_ptr(txd->m_mask)) {
			rage::types::dictionary_pool* pool = txd->m_pool;
			for (uint32_t i = 0; i < txd->m_count; i++) {
				if (~(txd->m_mask[i] >> 7) & 1) {
					rage::types::dictionary_pool element = pool[i];
					if (is_valid_ptr(element.m_pool)) {
						if (element.m_dictionary_hash == hash || element.m_dictionary_hash == texture_hash) {
							for (short j = 0; j < element.m_pool->m_count; j++) {
								rage::types::grc_texture_dx11* item = element.m_pool->m_items[j];
								if (is_valid_ptr(item)) {
									if (is_valid_ptr(item->m_name)) {
										if (!strcmp(item->m_name, name.c_str())) {
											return item;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		return nullptr;
	}

	void add_json(texture_swap* swap) {
		nlohmann::json json;

		try {
			if (std::filesystem::exists(util::dirs::get_path(texture_swap))) {
				std::ifstream input(util::dirs::get_path(texture_swap));
				if (input.good()) {
					input >> json;
					input.close();
				}

				nlohmann::json& arr = json["textures"][swap->m_asset.first][swap->m_asset.second];
				
				bool add = true;
				for (nlohmann::json& item : arr) {
					if (item["texture"].get<std::string>() == swap->m_texture) {
						add = false;

						item["texture"] = swap->m_texture;
						item["enabled"] = swap->m_toggled;
					}
				}

				if (add) {
					nlohmann::json& array = nlohmann::json::object();
					array["texture"] = swap->m_texture;
					array["enabled"] = swap->m_toggled;

					json["textures"][swap->m_asset.first][swap->m_asset.second].push_back(array);
				}

				std::ofstream output(util::dirs::get_path(texture_swap));
				if (output.good()) {
					output << json.dump(4);
					output.close();
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void remove_swap(texture_swap* swap);

	bool add_swap(texture_swap* swap) {
		texture_swaps_menu* instance = texture_swaps_menu::get();

		std::vector<menu::textures::texture_context> textures = menu::textures::get_list();
		rage::types::grc_texture_dx11* asset = find_texture(swap->m_asset.first.c_str(), swap->m_asset.second.c_str());

		// disable active ones for this texture
		for (texture_swap* texture : m_vars.m_swaps) {
			if (texture->m_asset.first == swap->m_asset.first
				&& texture->m_asset.second == swap->m_asset.second
				&& texture->m_toggled
				&& texture != swap) {
				remove_swap(texture);
			}
		}

		if (!swap->m_initialized) {
			if (std::find_if(begin(textures), end(textures), [=](menu::textures::texture_context& element) { return !element.m_name.compare(swap->m_texture); }) == end(textures)) {
				menu::notify::stacked(instance->get_string("Texture"), util::va::va("%s %s %s %s, %s %s %s", instance->get_string("Failed to swap texture").c_str(), swap->m_asset.second.c_str(), instance->get_string("in").c_str(), swap->m_asset.first.c_str(), instance->get_string("couldn't find").c_str(), swap->m_texture.c_str(), instance->get_string("in textures folder").c_str()), global::ui::g_error);
				return false;
			}

			if (asset) {
				swap->m_initialized = true;
				swap->m_original.m_width = asset->m_width;
				swap->m_original.m_height = asset->m_height;
				swap->m_original.m_texture = asset->m_texture;
				swap->m_original.m_shader = asset->m_shader;
				goto start;
			}

			return false;
		}

	start:
		auto vit = std::find_if(begin(textures), end(textures), [=](menu::textures::texture_context& element) { return !element.m_name.compare(swap->m_texture); });
		if (vit != end(textures)) {
			asset->m_width = vit->m_texture->m_width;
			asset->m_height = vit->m_texture->m_height;
			asset->m_texture = vit->m_texture->m_texture;
			asset->m_shader = vit->m_texture->m_shader;
			return true;
		}

		return false;
	}

	void remove_swap(texture_swap* swap) {
		swap->m_toggled = false;

		if (swap->m_initialized) {
			rage::types::grc_texture_dx11* asset = find_texture(swap->m_asset.first.c_str(), swap->m_asset.second.c_str());
			if (asset) {
				asset->m_width = swap->m_original.m_width;
				asset->m_height = swap->m_original.m_height;
				asset->m_texture = swap->m_original.m_texture;
				asset->m_shader = swap->m_original.m_shader;
			}
		}
	}

	void load_swaps(texture_swaps_menu* _this) {
		texture_swaps_menu* instance = texture_swaps_menu::get();

		try {
			std::ifstream input(util::dirs::get_path(texture_swap));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				if (json["textures"].size() > 0) {
					for (auto& it = json["textures"].begin(); it != json["textures"].end(); ++it) {
						nlohmann::json& dictionary = *it;

						for (auto& it2 = dictionary.begin(); it2 != dictionary.end(); ++it2) {
							nlohmann::json& assets = *it2;

							for (nlohmann::json& asset : assets) {
								texture_swap* swap = new texture_swap();
								swap->m_asset = { it.key(), it2.key() };
								swap->m_texture = asset["texture"].get<std::string>();
								swap->m_toggled = asset["enabled"].get<bool>();

								// if not exist
								std::vector<menu::textures::texture_context> textures = menu::textures::get_list();
								if (std::find_if(begin(textures), end(textures), [=](menu::textures::texture_context& element) { return !element.m_name.compare(swap->m_texture); }) == end(textures)) {
									menu::notify::stacked(instance->get_string("Texture"), util::va::va("%s %s %s %s, %s %s %s", instance->get_string("Failed to swap texture").c_str(), swap->m_asset.second.c_str(), instance->get_string("in").c_str(), swap->m_asset.first.c_str(), instance->get_string("couldn't find").c_str(), swap->m_texture.c_str(), instance->get_string("in textures folder").c_str()), global::ui::g_error);
									continue;
								}

								// disable active ones for this texture
								for (texture_swap* texture : m_vars.m_swaps) {
									if (texture->m_asset.first == swap->m_asset.first
										&& texture->m_asset.second == swap->m_asset.second
										&& texture->m_toggled
										&& texture != swap) {
										swap->m_toggled = false;
									}
								}

								if (swap->m_toggled) {
									util::fiber::pool::add([=] {
										menu::control::simple_request_dictionary(swap->m_asset.first);

										rage::types::grc_texture_dx11* asset = find_texture(swap->m_asset.first.c_str(), swap->m_asset.second.c_str());
										if (asset) {
											add_swap(swap);
										} else {
											menu::notify::stacked(instance->get_string("Texture"), util::va::va("%s %s %s %s, %s", instance->get_string("Failed to swap texture").c_str(), swap->m_asset.second.c_str(), instance->get_string("in").c_str(), swap->m_asset.first.c_str(), instance->get_string("couldn't find texture in memory").c_str()), global::ui::g_error);
										}
									});
								}

								m_vars.m_swaps.push_back(swap);
							}
						}
					}
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void swap_existing(texture_swap* swap) {
		texture_swaps_menu* instance = texture_swaps_menu::get();

		add_json(swap);

		if (swap->m_toggled) {
			util::fiber::pool::add([=] {
				menu::control::simple_request_dictionary(swap->m_asset.first);

				rage::types::grc_texture_dx11* asset = find_texture(swap->m_asset.first.c_str(), swap->m_asset.second.c_str());
				if (asset) {
					add_swap(swap);
				} else {
					menu::notify::stacked(instance->get_string("Texture"), util::va::va("%s %s %s %s, %s", instance->get_string("Failed to swap texture").c_str(), swap->m_asset.second.c_str(), instance->get_string("in").c_str(), swap->m_asset.first.c_str(), instance->get_string("couldn't find texture in memory").c_str()), global::ui::g_error);
				}
			});
		} else {
			remove_swap(swap);
		}
	}
}

void texture_swaps_menu::load() {
	set_name("Texture Swaps");
	set_parent<misc_swaps_menu>();

	add_option(submenu_option("Add Swap")
		.add_translate().add_hotkey()
		.add_submenu<texture_swaps_add_menu>());

	add_option(break_option("Swaps")
		.add_translate());

	add_string("~m~None");
	add_string("Texture");
	add_string("Failed to swap texture");
	add_string("in");
	add_string("couldn't find texture in memory");
	add_string("couldn't find");
	add_string("in textures folder");
	load_swaps(this);
}

void texture_swaps_menu::update() {}

void texture_swaps_menu::update_once() {
	menu::textures::update();

	clear_options(2);

	for (texture_swap* swap : m_vars.m_swaps) {
		add_option(toggle_option(swap->m_asset.first + ":" + swap->m_asset.second)
			.add_toggle(swap->m_toggled)
			.add_click([=] { swap_existing(swap); })
			.add_tooltip(util::va::va("%s %s", get_string("Swapped with").c_str(), swap->m_texture.c_str())));
	}

	if (m_vars.m_swaps.size() == 0) {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void texture_swaps_menu::feature_update() {}

texture_swaps_menu* g_instance;
texture_swaps_menu* texture_swaps_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new texture_swaps_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}