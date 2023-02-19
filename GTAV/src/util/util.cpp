#include "util.h"
#include <sstream>
#include <iomanip>
#include <psapi.h>
#include <random>

namespace util {
	std::string mock_string(std::string str) {
		auto is_char = [](char c) {
			return c >= 0x41 && c <= 0x7A;
		};

		auto is_capital = [](char c) {
			return c >= 0x41 && c <= 0x5A;
		};

		auto get_capital = [](char c) {
			return c - 0x20;
		};

		auto get_lower = [](char c) {
			return c + 0x20;
		};

		bool capital = true;
		for (char& c : str) {
			if (is_char(c)) {
				if (capital) {
					if (!is_capital(c)) {
						c = get_capital(c);
					}
				} else {
					if (is_capital(c)) {
						c = get_lower(c);
					}
				}

				capital ^= true;
			}
		}

		return str;
	}

	std::string create_random_string(size_t Length) {
		auto randchar = []() -> char {
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};

		std::string str(Length, 0);
		std::generate_n(str.begin(), Length, randchar);
		return str;
	}

	void create_random_bytes(uint8_t* data, int length) {
		for (int i = 0; i < length; i++) {
			std::random_device r;
			std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
			std::mt19937 rng(seed2);
			std::uniform_int_distribution<int> val(0, 255);
			data[i] = (uint8_t)val(rng);
		}
	}

	std::vector<uint8_t> convert_number_to_bytes(int value) {
		std::vector<uint8_t> bytes(4);

		for (int i = 0; i < 4; i++) {
			bytes[3 - i] = (value >> (i * 8));
		}

		return bytes;
	}

	std::vector<std::string> split_string(std::string str, std::string splitter) {
		size_t pos;
		std::vector<std::string> out;

		while ((pos = str.find(splitter)) != std::string::npos) {
			std::string token = str.substr(0, pos);
			out.push_back(token);
			str.erase(0, pos + splitter.length());
		}

		out.push_back(str);
		return out;
	}

	std::vector<uint8_t> convert_string_to_bytes(std::string str) {
		std::vector<uint8_t> bytes;

		for (std::size_t i = 0; i < str.length(); i += 2) {
			std::string byte_string = str.substr(i, 2);
			bytes.push_back((uint8_t)strtol(byte_string.c_str(), NULL, 16));
		}

		return bytes;
	}

	std::string convert_bytes_to_string(uint8_t* data, int length, bool space) {
		std::stringstream str;
		str.setf(std::ios_base::hex, std::ios::basefield);
		str.setf(std::ios_base::uppercase);
		str.fill('0');

		for (int i = 0; i < length; ++i) {
			str << std::setw(2) << (unsigned short)data[i];

			if (space && i != length - 1) {
				str << " ";
			}
		}

		return str.str();
	}

	std::string get_stack_trace() {
		std::string s("[");

		typedef USHORT(WINAPI* CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
		CaptureStackBackTraceType func = (CaptureStackBackTraceType)(GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlCaptureStackBackTrace"));

		if (func != NULL) {
			HMODULE hMods[1024];
			DWORD cbNeeded;
			EnumProcessModules((HANDLE)-1, hMods, sizeof(hMods), &cbNeeded);
			const int kMaxCallers = 62;
			void* callers[kMaxCallers];
			int count = (func)(0, kMaxCallers, callers, NULL);
			for (int i = 1; i < count; i++) {
				DWORD64 callerAddr = (DWORD64)callers[i];
				HMODULE currentCallerModule = NULL;

				for (unsigned int i2 = 0; i2 < (cbNeeded / sizeof(HMODULE)); i2++) {
					MODULEINFO information = { 0 };
					GetModuleInformation((HANDLE)-1, hMods[i2], &information, sizeof(information));
					if (callerAddr >= (DWORD64)information.lpBaseOfDll && callerAddr <= (DWORD64)information.lpBaseOfDll + information.SizeOfImage) {
						currentCallerModule = hMods[i2];
						break;
					}
				}

				if (currentCallerModule != NULL) {
					char moduleName[MAX_PATH];
					GetModuleBaseNameA((HANDLE)-1, currentCallerModule, moduleName, MAX_PATH);
					char buf[512];
					sprintf_s(buf, "0x%llx [%s]%s", callerAddr - (DWORD64)currentCallerModule, moduleName, i != count - 1 ? ", " : "");
					s += buf;
				} else {
					char buf[512];
					sprintf_s(buf, "0x%llx %s", callerAddr, i != count - 1 ? ", " : "");
					s += buf;
				}
			}

			s += "]";
			return s;
		}

		return "Unk";
	}

	void replace_string(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			size_t end_pos = start_pos + from.length();
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, from.length(), to);
				start_pos += to.length();
			}

			start_pos += to.length();
		}
	}

	void replace_char(std::string& str, char from, std::string to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			size_t end_pos = start_pos + 1;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, 1, to);
				start_pos += 1;
			}

			start_pos += 1;
		}
	}

	std::vector<image_section> get_image_sections(std::string module_name, std::vector<char> override_header) {
		std::vector<image_section> _return;

		uint64_t module_address = (uint64_t)GetModuleHandleA(module_name.c_str());
		if (module_address == 0) return _return;

		PIMAGE_DOS_HEADER dos_header = nullptr;
		PIMAGE_NT_HEADERS nt_header = nullptr;

		if (override_header.empty()) {
			dos_header = (PIMAGE_DOS_HEADER)module_address;
			nt_header = (PIMAGE_NT_HEADERS)(module_address + dos_header->e_lfanew);
		} else {
			dos_header = (PIMAGE_DOS_HEADER)override_header.data();
			nt_header = (PIMAGE_NT_HEADERS)(override_header.data() + dos_header->e_lfanew);
		}

		IMAGE_SECTION_HEADER* header = (IMAGE_SECTION_HEADER*)(nt_header + 1);
		for (int i = 0; i < nt_header->FileHeader.NumberOfSections; i++) {
			const char* section_name = (const char*)header->Name;
			uint64_t address = module_address + header->VirtualAddress;

			_return.push_back({ section_name, address, header->Misc.VirtualSize });
			header++;
		}

		return _return;
	}
}