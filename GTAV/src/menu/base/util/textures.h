#pragma once
#include "stdafx.h"
#include "rage/types/generic_types.h"

namespace menu::textures {
	struct texture_context {
		std::string m_name;
		rage::types::grc_texture_dx11* m_texture;
	};

	class textures {
	public:
		void load();
		void load_image(std::string file);
		void load_player_img(uint8_t* img, uint32_t rid);
		void update();
		bool get_texture(std::string name, texture_context* out);

		std::vector<texture_context>& get_list() { return m_textures; }
	private:
		std::vector<texture_context> m_textures;
	};

	textures* get_textures();

	inline void load() {
		get_textures()->load();
	}

	inline void load_player_img(uint8_t* img, uint32_t rid) {
		get_textures()->load_player_img(img, rid);
	}

	inline void update() {
		get_textures()->update();
	}

	inline bool get_texture(std::string name, texture_context* out) {
		return get_textures()->get_texture(name, out);
	}

	inline std::vector<texture_context>& get_list() {
		return get_textures()->get_list();
	}
}