#include "textures.h"
#include "util/wic/wic_texture_loader.h"
#include "util/dirs.h"
#include "util/log.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "global/vars.h"
#include "menu/base/util/notify.h"
#include "rage/invoker/natives.h"

namespace menu::textures {
	void textures::load_player_img(uint8_t* img, uint32_t rid) {
		if (std::find_if(begin(m_textures), end(m_textures), [=](texture_context& elem) {return elem.m_name == std::string("playerimg_" + std::to_string(rid)); }) != end(m_textures)) return;

		ID3D11Resource* resource = nullptr;
		ID3D11ShaderResourceView* shader = nullptr;

		if (create_dds_texture_from_memory((ID3D11Device*)global::vars::g_d3d11_device, img, 16512, &resource, &shader) != ERROR_SUCCESS) {
			menu::notify::stacked("Texture", "Failed loading player image texture for rid " + std::to_string(rid), global::ui::g_error);
			return;
		}

		uint64_t vtable = *(uint64_t*)global::vars::g_grc_texture_factory_dx11;
		rage::types::grc_texture_dx11* texture = caller::call<rage::types::grc_texture_dx11*>(*(uint64_t*)(vtable + 0x20), global::vars::g_grc_texture_factory_dx11, std::string("playerimg_" + std::to_string(rid)).c_str(), 0);
		if (texture) {
			ID3D11Texture2D* texture_interface = nullptr;
			resource->QueryInterface<ID3D11Texture2D>(&texture_interface);

			D3D11_TEXTURE2D_DESC desc;
			texture_interface->GetDesc(&desc);

			texture->m_width = desc.Width;
			texture->m_height = desc.Height;
			texture->m_depth = 1;
			texture->m_shader = shader;
			texture->m_texture = resource;

			std::string key = std::string("playerimg_" + std::to_string(rid));
			texture->m_name = new char[key.length() + 1];
			strcpy(texture->m_name, key.c_str());

			rage::engine::add_grc_texture_to_dictionary(global::vars::g_player_img_dictionary, native::get_hash_key(key.c_str()), texture);

			// LOG_CUSTOM("Textures", "Loaded player texture for rid %i", rid);
			m_textures.push_back({ key, texture });
		}
	}

	std::wstring Str2Wstr(const std::string& str) {
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	void textures::load_image(std::string file) {
		ID3D11Resource* resource = nullptr;
		ID3D11ShaderResourceView* shader = nullptr;

		std::string n = util::dirs::get_path(textures) + file;
		if (create_wic_texture_from_file((ID3D11Device*)global::vars::g_d3d11_device, Str2Wstr(n).c_str(), &resource, &shader) != ERROR_SUCCESS) {
			menu::notify::stacked("Texture", "Failed loading texture " + file, global::ui::g_error);
			return;
		}

		uint64_t vtable = *(uint64_t*)global::vars::g_grc_texture_factory_dx11;

		rage::types::grc_texture_dx11* texture = caller::call<rage::types::grc_texture_dx11*>(*(uint64_t*)(vtable + 0x20), global::vars::g_grc_texture_factory_dx11, file.c_str(), 0);
		if (texture) {
			ID3D11Texture2D* texture_interface = nullptr;
			resource->QueryInterface<ID3D11Texture2D>(&texture_interface);

			D3D11_TEXTURE2D_DESC desc;
			texture_interface->GetDesc(&desc);

			texture->m_width = desc.Width;
			texture->m_height = desc.Height;
			texture->m_depth = 1;
			texture->m_shader = shader;
			texture->m_texture = resource;

			texture->m_name = new char[file.length() + 1];
			strcpy(texture->m_name, file.c_str());

			rage::engine::add_grc_texture_to_dictionary(global::vars::g_custom_dictionary, native::get_hash_key(file.c_str()), texture);

			LOG_CUSTOM("Textures", "Loaded texture %s", file.c_str());
			m_textures.push_back({ file, texture });
		}
	}

	void textures::load() {
		std::vector<std::string> files;
		
		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".png")) files.push_back(str + ".png");
		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".jpg")) files.push_back(str + ".jpg");
		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".jpeg")) files.push_back(str + ".jpeg");
		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".bmp")) files.push_back(str + ".bmp");

		if (files.size()) {
			if (!global::vars::g_custom_dictionary) {
				global::vars::g_custom_dictionary = (rage::types::dictionary*)rage::engine::thread_alloc(0x40);
				if (global::vars::g_custom_dictionary) {
					global::vars::g_custom_dictionary = rage::engine::setup_dictionary(global::vars::g_custom_dictionary, (int)files.size() * 2);

					uint32_t dictionary_hash = joaat("ozarktextures");

					uint32_t out = 0;
					uint32_t index = *rage::engine::setup_store_item((uint64_t)global::vars::g_texture_store, &out, &dictionary_hash);

					if (rage::engine::is_valid_pool_slot((uint64_t)global::vars::g_texture_store, index)) {
						rage::engine::add_dictionary_to_pool((uint64_t)global::vars::g_texture_store, index, global::vars::g_custom_dictionary);
					}
				}
			}

			for (std::string file : files) {
				load_image(file);
			}
		}

		if (!global::vars::g_player_img_dictionary) {
			global::vars::g_player_img_dictionary = (rage::types::dictionary*)rage::engine::thread_alloc(0x40);
			if (global::vars::g_player_img_dictionary) {
				global::vars::g_player_img_dictionary = rage::engine::setup_dictionary(global::vars::g_player_img_dictionary, 5000);

				uint32_t dictionary_hash = joaat("ozarkplayerimg");

				uint32_t out = 0;
				uint32_t index = *rage::engine::setup_store_item((uint64_t)global::vars::g_texture_store, &out, &dictionary_hash);

				if (rage::engine::is_valid_pool_slot((uint64_t)global::vars::g_texture_store, index)) {
					rage::engine::add_dictionary_to_pool((uint64_t)global::vars::g_texture_store, index, global::vars::g_player_img_dictionary);
				}
			}
		}
	}

	void textures::update() {
		if (m_textures.empty()) return load(); // if there's 0, attempt to load

		std::vector<std::string> files;

		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".png")) files.push_back(str + ".png");
		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".jpg")) files.push_back(str + ".jpg");
		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".jpeg")) files.push_back(str + ".jpeg");
		for (std::string str : util::dirs::get_files_in_directory(util::dirs::get_path(textures), ".bmp")) files.push_back(str + ".bmp");

		if (files.size()) {
			for (std::string file : files) {
				auto vit = std::find_if(begin(m_textures), end(m_textures), [=](texture_context& element) { return element.m_name == file; });
				if (vit == end(m_textures)) {
					load_image(file);
				}
			}
		}
	}

	bool textures::get_texture(std::string name, texture_context* out) {
		std::vector<texture_context>& list = get_list();
		if (!list.empty()) {
			auto vit = std::find_if(begin(list), end(list), [=](texture_context& context) { return context.m_name == name; });
			if (vit != end(list)) {
				*out = *(vit);
				return true;
			}
		}

		return false;
	}

	textures* get_textures() {
		static textures instance;
		return &instance;
	}
}