#pragma once
#include "stdafx.h"
#include <vector>

namespace memory {
	template<typename V>
	void write(uint64_t address, V value) {
		uint32_t old;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, (DWORD*)&old);
		memcpy((void*)address, &value, sizeof(value));
		VirtualProtect((void*)address, sizeof(value), old, (DWORD*)&old);
	}

	template<typename V>
	void write(uint64_t address, V value, uint32_t size) {
		uint32_t old;
		VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, (DWORD*)&old);
		memcpy((void*)address, value, size);
		VirtualProtect((void*)address, size, old, (DWORD*)&old);
	}

	void nop(uint64_t address, uint32_t size);
	void write_vector(uint64_t address, std::vector<uint8_t> data);
	uint64_t read_instruction(uint64_t address, int opcode_size = 3, int opcode_length = 7);
}