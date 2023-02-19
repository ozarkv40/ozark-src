#include "fonts.h"
#include "util/dirs.h"
#include "global/vars.h"
#include "global/ui_vars.h"
#include "rage/engine.h"
#include "util/log.h"

namespace menu::fonts {
	int get_next_font_id() {
		uint64_t font_table = *(uint64_t*)(global::vars::g_font_table);

		int font_id = 0;
		while (true) {
			uint32_t font_ptr = 0x1E0 * font_id;

			if (*(uint32_t*)(font_table + font_ptr + 0x1B8) == 0) {
				break;
			}

			font_id++;
		}

		return font_id;
	}

	void fonts::update_queue() {
		if (get_next_font_id() < 12) return;

		static bool set_default = false;
		if (!set_default) {
			int id = get_font_id("RDR");
			if (id > 0) {
				global::ui::g_header_font = id;
				set_default = true;
			}
		}

		for (font_context& font : m_fonts) {
			if (font.m_asset_id == -1 || font.m_font_id == -1) {
				rage::types::store_module* store = rage::engine::get_store_module_extension("gfx");
				if (store) {
					if (font.m_asset_id == -1) {
						std::string asset = font.m_font_name + ".gfx";
						font.m_asset_id = rage::engine::register_streaming_file((util::dirs::get_path(gfx) + asset).c_str(), asset.c_str());

						if (font.m_asset_id) {
							store->m_pool.get<char>(font.m_asset_id - store->m_base_index)[50] = true; // create movie on load
						}
					} else {
						if (font.m_font_id == -1) {
							if ((global::vars::g_store_manager->m_entries[font.m_asset_id].m_flag & 3) == 1) {
								uint64_t font_table = *(uint64_t*)(global::vars::g_font_table);
								uint64_t memory_helper = *(uint64_t*)(global::vars::g_font_memory_helper);
								uint64_t gfx_loader_impl = (*(uint64_t(**)(uint64_t))(**(uint64_t**)(memory_helper + 0x20)))(*(uint64_t*)(memory_helper + 0x20));
								uint64_t state_bag_impl = (*(uint64_t(**)(uint64_t))(*(uint64_t*)(gfx_loader_impl)))(gfx_loader_impl);
								uint64_t state_impl = *(uint64_t*)(state_bag_impl + 0x20);

								font.m_font_id = rage::engine::create_id_for_font(font.m_font_name.c_str());
								if (font.m_font_id >= 0 && font.m_font_id < 50) {
									int index = *(int*)(font_table + (0x1E0 * font.m_font_id) + 0xB0);

									rage::engine::add_font_lib(*(uint64_t*)(state_impl + 0x1E8), font.m_asset_id);
								}
							} else {
								rage::engine::request_streaming_file(font.m_asset_id);
							}
						}
					}
				}
			}
		}
	}

	int fonts::get_font_id(std::string name) {
		auto vit = std::find_if(begin(m_fonts), end(m_fonts), [=](font_context& element) { return element.m_font_name == name; });
		if (vit != end(m_fonts)) {
			if (vit->m_font_id > -1) {
				return vit->m_font_id;
			}
		}

		return 0; // default
	}

	void fonts::load() {
		std::vector<std::string> files = util::dirs::get_files_in_directory(util::dirs::get_path(gfx), ".gfx");

		if (files.size()) {
			for (std::string file : files) {
				m_fonts.push_back({ file, -1, -1 });
			}
		}
	}

	void fonts::update() {
		if (m_fonts.empty()) return load(); // if there's 0, attempt to load

		std::vector<std::string> files = util::dirs::get_files_in_directory(util::dirs::get_path(gfx), ".gfx");

		if (files.size()) {
			for (std::string file : files) {
				auto vit = std::find_if(begin(m_fonts), end(m_fonts), [=](font_context& element) { return element.m_font_name == file; });
				if (vit == end(m_fonts)) {
					m_fonts.push_back({ file, -1, -1 });
				}
			}
		}
	}

	fonts* get_fonts() {
		static fonts instance;
		return &instance;
	}
}