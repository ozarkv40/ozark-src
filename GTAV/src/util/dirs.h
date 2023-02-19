#pragma once
#include "stdafx.h"
#include <unordered_map>

#undef GetTempPath

namespace util::dirs {
	class directories {
	public:
		bool load();
		std::string create_string(std::string base, std::string folder);
		std::vector<std::string> get_files_in_directory(std::string dir, std::string extension);

		const char* get_log() { return get_path(PATH_LOG); }
		const char* get_auth() { return get_path(PATH_AUTH); }
		const char* get_gfx() { return get_path(PATH_GFX); }
		const char* get_config() { return get_path(PATH_CONFIG); }
		const char* get_outfit() { return get_path(PATH_OUTFIT); }
		const char* get_ozark() { return get_path(PATH_OZARK); }
		const char* get_ammo_modifier() { return get_path(PATH_AMMO_MODIFIER); }
		const char* get_scripthook() { return get_path(PATH_SCRIPTHOOK); }
		const char* get_tmp() { return get_path(PATH_TMP); }
		const char* get_textures() { return get_path(PATH_TEXTURES); }
		const char* get_texture_swap() { return get_path(PATH_TEXTURE_SWAP); }
		const char* get_model_swap() { return get_path(PATH_MODEL_SWAP); }
		const char* get_translation() { return get_path(PATH_TRANSLATION); }
		const char* get_theme() { return get_path(PATH_THEME); }
		const char* get_teleport() { return get_path(PATH_TELEPORT); }
		const char* get_modded_vehicles() { return get_path(PATH_MODDED_VEHICLES); }
		const char* get_rainbow() { return get_path(PATH_RAINBOW); }
		const char* get_handling() { return get_path(PATH_HANDLING); }
		const char* get_gamefx() { return get_path(PATH_GAMEFX); }
		const char* get_entity_limits() { return get_path(PATH_ENTITY_LIMITS); }
		const char* get_join_blocking() { return get_path(PATH_JOIN_BLOCKING); }
		const char* get_recent_players() { return get_path(PATH_RECENT_PLAYERS); }
		const char* get_spoofing_profiles() { return get_path(PATH_SPOOFING_PROFILES); }
		const char* get_text_messages() { return get_path(PATH_TEXT_MESSAGES); }
		const char* get_overseer() { return get_path(PATH_OVERSEER); }
		const char* get_lsc() { return get_path(PATH_LSC); }

		enum Paths {
			PATH_DOCUMENTS,
			PATH_OZARK,
			PATH_LOG,
			PATH_AUTH,
			PATH_GFX,
			PATH_CONFIG,
			PATH_OUTFIT,
			PATH_AMMO_MODIFIER,
			PATH_SCRIPTHOOK,
			PATH_TMP,
			PATH_TEXTURES,
			PATH_TEXTURE_SWAP,
			PATH_MODEL_SWAP,
			PATH_TRANSLATION,
			PATH_THEME,
			PATH_TELEPORT,
			PATH_MODDED_VEHICLES,
			PATH_RAINBOW,
			PATH_HANDLING,
			PATH_GAMEFX,
			PATH_ENTITY_LIMITS,
			PATH_JOIN_BLOCKING,
			PATH_RECENT_PLAYERS,
			PATH_SPOOFING_PROFILES,
			PATH_TEXT_MESSAGES,
			PATH_OVERSEER,
			PATH_LSC
		};
	private:
		std::unordered_map<Paths, char[MAX_PATH]> m_paths;

		const char* get_path(Paths path) {
			return m_paths[path];
		}
	};

	directories* get_directories();

	inline std::vector<std::string> get_files_in_directory(std::string dir, std::string extension = ".txt") {
		return get_directories()->get_files_in_directory(dir, extension);
	}

	inline bool load() {
		return get_directories()->load();
	}

	inline std::string create_string(std::string base, std::string folder) {
		return get_directories()->create_string(base, folder);
	}

#define get_path(name) get_directories()->get_##name##()
}