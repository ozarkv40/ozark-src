#pragma once
#include "stdafx.h"
#include <vector>

struct image_section {
	std::string m_name;
	uint64_t m_address;
	uint64_t m_size;
};

namespace util {
	std::string mock_string(std::string str);
	std::string create_random_string(size_t length);
	void create_random_bytes(uint8_t* data, int length);
	std::vector<uint8_t> convert_number_to_bytes(int value);
	std::vector<std::string> split_string(std::string str, std::string splitter);
	std::vector<uint8_t> convert_string_to_bytes(std::string str);
	std::string convert_bytes_to_string(uint8_t* data, int length, bool space = false);
	std::string get_stack_trace();
	void replace_string(std::string& str, const std::string& from, const std::string& to);
	void replace_char(std::string& str, char from, std::string to);
	std::vector<image_section> get_image_sections(std::string module_name, std::vector<char> override_header);

	template<typename T>
	T* alloc() {
		void* allocated = malloc(sizeof(T));
		memset(allocated, 0, sizeof(T));
		return (T*)allocated;
	}

	template<class T>
	std::string format_with_commas(T value) {
		std::stringstream ss;
		ss.imbue(std::locale("en_US.UTF-8"));
		ss << std::fixed << value;
		return ss.str();
	}
}