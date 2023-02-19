#pragma once
#include "stdafx.h"

namespace rage::invoker {
	struct native_registration {
		uint64_t m_next_registration1;
		uint64_t m_next_registration2;
		uint64_t m_handlers[7];
		uint32_t m_num_entries1;
		uint32_t m_num_entries2;
		uint64_t m_hashes;

		/*__declspec(noinline) native_registration* get_next_registration() {
			uintptr_t result;
			auto v5 = reinterpret_cast<uintptr_t>(&m_next_registration1);
			auto v12 = 2i64;
			auto v13 = v5 ^ m_next_registration2;
			auto v14 = (char*)&result - v5;
			do {
				*(DWORD*)&v14[v5] = v13 ^ *(DWORD*)v5;
				v5 += 4i64;
				--v12;
			} while (v12);

			return reinterpret_cast<native_registration*>(result);
		}

		__declspec(noinline) uint32_t get_num_entries() {
			return (uint32_t)(((uintptr_t)&m_num_entries1) ^ m_num_entries1 ^ m_num_entries2);
		}

		__declspec(noinline) uint64_t get_hash(uint32_t index) {
			auto naddr = 16 * index + reinterpret_cast<uintptr_t>(&m_next_registration1) + 0x54;
			auto v8 = 2i64;
			uint64_t result;
			auto v11 = (char*)&result - naddr;
			auto v10 = naddr ^ *(DWORD*)(naddr + 8);
			do {
				*(DWORD*)&v11[naddr] = v10 ^ *(DWORD*)(naddr);
				naddr += 4i64;
				--v8;
			} while (v8);

			return result;
		}*/

		static uint64_t get_handler(uint64_t hash);
	};
}