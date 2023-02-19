#include "auth.h"
#include "global/auth_vars.h"
#include "auth/server/auth_packets.h"
#include "auth/crypto/crypto.h"
#include "util/log.h"
#include "util/wmi.h"
#include "util/json.h"
#include "util/dirs.h"
#include "util/util.h"
#include <filesystem>
#include <fstream>

namespace auth {
	LONG read_registry_string(HKEY key, const std::string& name, std::string& value, const std::string& default_value) {
		value = default_value;

		char buffer[512];
		DWORD size = sizeof(buffer);
		ULONG error = RegQueryValueExA(key, name.c_str(), 0, NULL, (LPBYTE)buffer, &size);

		if (ERROR_SUCCESS == error) {
			value = buffer;
		}

		return error;
	}

	bool run() {
		LOG(XOR("Starting hardware process..."));
		if (util::wmi::load()) {
			std::string str = util::wmi::read(XOR("Win32_OperatingSystem"), XOR("Manufacturer"));
			str += util::wmi::read(XOR("Win32_OperatingSystem"), XOR("OSArchitecture"));
			str += util::wmi::read(XOR("Win32_OperatingSystem"), XOR("SerialNumber"));
			str += util::wmi::read(XOR("Win32_OperatingSystem"), XOR("SystemDrive"));
			str += util::wmi::read(XOR("Win32_OperatingSystem"), XOR("WindowsDirectory"));
			str += util::wmi::read(XOR("Win32_ComputerSystem"), XOR("Model"));
			str += util::wmi::read(XOR("Win32_ComputerSystem"), XOR("Manufacturer"));
			str += util::wmi::read(XOR("Win32_BIOS"), XOR("Manufacturer"));
			str += util::wmi::read(XOR("Win32_Processor"), XOR("Name"));

			LOG(XOR("Starting hardware hashing process..."));
			crypto::XECRYPT_SHA512_STATE state;
			crypto::sha_init(&state);
			crypto::sha_update(&state, (uint8_t*)str.data(), (uint32_t)str.length());
			crypto::sha_final(&state, global::auth::g_hardware_id, sizeof(global::auth::g_hardware_id));
			LOG(XOR("Hardware hashing process complete :)"));

			str.clear();
			util::wmi::cleanup();
		} else {
			LOG_CUSTOM_ERROR(XOR("Auth"), XOR("Failed to initialize hardware"));
			return false;
		}

		LOG(XOR("Hardware process complete :)"));

		if (std::filesystem::exists(util::dirs::get_path(auth)) && std::filesystem::file_size(util::dirs::get_path(auth)) > 45) {
			std::ifstream auth_file(util::dirs::get_path(auth));
			if (auth_file.good()) {
				nlohmann::json temp;

				try {
					auth_file >> temp;
				} catch (std::exception& E) {
					LOG_WARN("[JSON] %s", E.what());
				}

				auth_file.close();

				global::auth::g_username = temp[XOR("username")].get<std::string>();
				global::auth::g_password = temp[XOR("password")].get<std::string>();

				if (global::auth::g_password.length() == 128) {
					// Old password from old format
					LOG_CUSTOM_ERROR(XOR("Auth"), XOR("Detected Ozark.auth having old password format, checking registry..."));
					goto UseReg;
				}

				uint8_t hash[64];

				LOG(XOR("Starting hashing process..."));
				crypto::XECRYPT_SHA512_STATE state;
				crypto::sha_init(&state);
				crypto::sha_update(&state, (uint8_t*)global::auth::g_password.data(), (uint32_t)global::auth::g_password.length());
				crypto::sha_final(&state, hash, sizeof(hash));
				LOG(XOR("Hashing process complete :)"));

				LOG(XOR("Starting rotate process..."));
				global::auth::g_password = crypto::rotate(crypto::rotate_number(util::convert_bytes_to_string(hash, sizeof(hash))));
				LOG(XOR("Rotate process complete :)"));
			} else {
				LOG_CUSTOM_ERROR(XOR("Auth"), XOR("Failed to open Ozark.auth"));
			}
		} else {
		UseReg:
			HKEY key;
			if (RegOpenKeyExW(HKEY_CURRENT_USER, XOR(L"SOFTWARE\\Ozark"), 0, KEY_READ, &key) == ERROR_SUCCESS) {
				if (read_registry_string(key, XOR("Username"), global::auth::g_username, "") == ERROR_SUCCESS) {
					std::string password = "";
					if (read_registry_string(key, XOR("Password"), password, "") == ERROR_SUCCESS) {
						global::auth::g_username = crypto::rotate(crypto::aes_decrypt(crypto::base64_decode(global::auth::g_username), XOR("ahfgcbfhghghtydh"), 0));
						password = crypto::rotate(crypto::aes_decrypt(crypto::base64_decode(password), XOR("ahfgcbfhghghtydh"), 0));

						uint8_t hash[64];

						LOG(XOR("Starting hashing process..."));
						crypto::XECRYPT_SHA512_STATE state;
						crypto::sha_init(&state);
						crypto::sha_update(&state, (uint8_t*)password.data(), (uint32_t)password.length());
						crypto::sha_final(&state, hash, sizeof(hash));
						LOG(XOR("Hashing process complete :)"));

						LOG(XOR("Starting rotate process..."));
						global::auth::g_password = crypto::rotate(crypto::rotate_number(util::convert_bytes_to_string(hash, sizeof(hash))));
						LOG(XOR("Rotate process complete :)"));
						goto Auth;
					}
				}

				LOG_CUSTOM_ERROR(XOR("Auth"), XOR("Failed to extract credentials from registry"));
				return false;
			}

			LOG_CUSTOM_ERROR(XOR("Auth"), XOR("Failed to find credentials in registry"));
			return false;
		}

	Auth:
		if (auth::server::packet_ping()) {
			if (auth::server::packet_welcome()) {
				if (auth::server::packet_get_time()) {
					if (auth::server::packet_get_signatures()) {
						LOG_CUSTOM_SUCCESS(XOR("Auth"), XOR("Successfully passed All authentication stages"));
						return true;
					}
				}
			}
		}

		return false;
	}

	bool run_heartbeat() {
		return auth::server::packet_heartbeat();
	}
}