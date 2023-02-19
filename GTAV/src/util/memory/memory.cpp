#include "memory.h"

namespace memory {
	void write_vector(uint64_t address, std::vector<uint8_t> data) {
		write(address, data.data(), (uint32_t)data.size());
	}

	uint64_t read_instruction(uint64_t address, int opcode_size, int opcode_length) {
		return (uint64_t)(*(int*)(address + opcode_size) + address + opcode_length);
	}

	void nop(uint64_t address, uint32_t size) {
		uint32_t old;
		VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, (DWORD*)&old);
		memset((void*)address, 0x90, size);
		VirtualProtect((void*)address, size, old, (DWORD*)&old);
	}
}