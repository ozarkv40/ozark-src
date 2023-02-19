#include "dirs.h"
#include "va.h"
#include <ShlObj.h>
#include <filesystem>

namespace util::dirs {
	bool create_directories(std::vector<std::string> directories) {
		for (std::string dir : directories) {
			std::error_code error;
			std::filesystem::create_directories(dir, error);

			if (error.value()) {
				printf("[Dirs] Failed creating dir \"%s\" -> %s\n", dir.c_str(), error.message().c_str());
				return false;
			}
		}

		return true;
	}

	std::vector<std::string> directories::get_files_in_directory(std::string dir, std::string extension) {
		std::vector<std::string> buffer;

		WIN32_FIND_DATAA fd;
		HANDLE vit = FindFirstFileA((dir + "*" + extension).c_str(), &fd);

		if (vit != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					std::string original = fd.cFileName;
					buffer.push_back(original.substr(0, original.length() - extension.length()));
				}
			} while (FindNextFileA(vit, &fd));

			FindClose(vit);
		}

		return buffer;
	}

	std::string directories::create_string(std::string base, std::string folder) {
		return base + "\\" + folder;
	}

	bool directories::load() {
		if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, m_paths[PATH_DOCUMENTS]) != S_OK) {
			printf("[Dirs] Failed to get documents folder\n");
			return false;
		}

		char tmp[MAX_PATH];
		SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, tmp);

		sprintf_s(m_paths[PATH_TMP], XOR("%s\\"), tmp);
		sprintf_s(m_paths[PATH_OZARK], XOR("%s\\Ozark\\Grand Theft Auto V"), m_paths[PATH_DOCUMENTS]);
		sprintf_s(m_paths[PATH_GFX], XOR("%s\\Fonts\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_OUTFIT], XOR("%s\\Outfits\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_SCRIPTHOOK], XOR("%s\\ScriptHook\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_TEXTURES], XOR("%s\\Textures\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_TRANSLATION], XOR("%s\\Translations\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_THEME], XOR("%s\\Themes\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_MODDED_VEHICLES], XOR("%s\\Modded Vehicles\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_HANDLING], XOR("%s\\Handling\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_GAMEFX], XOR("%s\\FX\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_JOIN_BLOCKING], XOR("%s\\Join Blocking\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_SPOOFING_PROFILES], XOR("%s\\Profiles\\"), m_paths[PATH_OZARK]);
		sprintf_s(m_paths[PATH_LSC], XOR("%s\\LSC\\"), m_paths[PATH_OZARK]);

		sprintf_s(m_paths[PATH_AUTH], XOR("%s\\Ozark\\Ozark.auth"), m_paths[PATH_DOCUMENTS]);
		sprintf_s(m_paths[PATH_LOG], create_string(m_paths[PATH_OZARK], XOR("Log.txt")).c_str());
		sprintf_s(m_paths[PATH_CONFIG], create_string(m_paths[PATH_OZARK], XOR("config.json")).c_str());
		sprintf_s(m_paths[PATH_AMMO_MODIFIER], create_string(m_paths[PATH_OZARK], XOR("Ammo Modifiers.json")).c_str());
		sprintf_s(m_paths[PATH_TEXTURE_SWAP], create_string(m_paths[PATH_OZARK], XOR("Texture Swap.json")).c_str());
		sprintf_s(m_paths[PATH_MODEL_SWAP], create_string(m_paths[PATH_OZARK], XOR("Model Swap.json")).c_str());
		sprintf_s(m_paths[PATH_TELEPORT], create_string(m_paths[PATH_OZARK], XOR("Teleports.json")).c_str());
		sprintf_s(m_paths[PATH_RAINBOW], create_string(m_paths[PATH_OZARK], XOR("Rainbow.json")).c_str());
		sprintf_s(m_paths[PATH_ENTITY_LIMITS], create_string(m_paths[PATH_OZARK], XOR("Entity Limits.json")).c_str());
		sprintf_s(m_paths[PATH_RECENT_PLAYERS], create_string(m_paths[PATH_OZARK], XOR("Recent Players.json")).c_str());
		sprintf_s(m_paths[PATH_TEXT_MESSAGES], create_string(m_paths[PATH_OZARK], XOR("Text Messages.json")).c_str());
		sprintf_s(m_paths[PATH_OVERSEER], create_string(m_paths[PATH_OZARK], XOR("Overseer.json")).c_str());

		bool success = create_directories({
			m_paths[PATH_OZARK],
			create_string(m_paths[PATH_OZARK], XOR("Modded Vehicles")),
			create_string(m_paths[PATH_OZARK], XOR("Fonts")),
			create_string(m_paths[PATH_OZARK], XOR("FX")),
			create_string(m_paths[PATH_OZARK], XOR("Outfits")),
			create_string(m_paths[PATH_OZARK], XOR("ScriptHook")),
			create_string(m_paths[PATH_OZARK], XOR("Themes")),
			create_string(m_paths[PATH_OZARK], XOR("Translations")),
			create_string(m_paths[PATH_OZARK], XOR("Textures")),
			create_string(m_paths[PATH_OZARK], XOR("Handling")),
			create_string(m_paths[PATH_OZARK], XOR("Modded Vehicles")),
			create_string(m_paths[PATH_OZARK], XOR("Join Blocking")),
			create_string(m_paths[PATH_OZARK], XOR("LSC")),
			create_string(m_paths[PATH_OZARK], XOR("Profiles")),
		});

		if (success == false) return success;

		return true;
	}

	directories* get_directories() {
		static directories instance;
		return &instance;
	}
}