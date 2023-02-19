#pragma once
#include "stdafx.h"
#include "util/math.h"

#pragma pack(push)
#pragma pack(1)
namespace rage {
	struct bit_buffer_sync_instance;

	struct bit_buffer {
		uint64_t m_raw_buffer;	// 0x0
		uint32_t m_unk1;		// 0x8
		uint32_t m_max_bit;		// 0xC
		uint32_t m_next_bit;	// 0x10
		uint32_t m_current_bit;	// 0x14
		uint32_t m_unk2;		// 0x18
		uint8_t m_bit_flag;		// 0x1C

		bit_buffer() {
			memset(this, 0, sizeof(bit_buffer));
			m_bit_flag &= 0xFC;
		}

		void prepare(uint64_t raw_buffer, uint32_t size) {
			m_bit_flag &= 0xFD;
			m_bit_flag |= 1;
			m_raw_buffer = raw_buffer;
			m_max_bit = 8 * size;
		}

		void prepare_sync(uint64_t raw_buffer, uint32_t size) {
			m_bit_flag &= 0xFC;
			m_raw_buffer = raw_buffer;
			m_max_bit = 8 * size;
		}

		void prepare_sync_local(uint64_t raw_buffer, uint32_t size, uint32_t unk) {
			m_bit_flag &= 0xFD;
			m_bit_flag |= 1;
			m_raw_buffer = raw_buffer;
			m_max_bit = size;
			m_unk1 = unk;
		}

		uint32_t get_position() {
			return m_next_bit;
		}

		bool set_position(uint32_t bits) {
			if (bits >= 0) {
				uint32_t Length = (m_bit_flag & 1) ? m_max_bit : m_current_bit;

				if (bits <= Length) {
					m_next_bit = bits;
					return true;
				}
			}

			return false;
		}

		void add_offset(uint32_t Offset) {
			m_next_bit += Offset;
		}

		size_t get_data_length() {
			return (m_current_bit / 8) + (m_current_bit % 8) ? 1 : 0;
		}

		bit_buffer_sync_instance create_reader();
		void update_bit(uint32_t LastSize);

		bool read_bool(bool* output);
		bool read_int(int* output, uint32_t bit_offset);
		bool read_uint(uint32_t* output, uint32_t bit_offset);
		bool read_ulonglong(uint64_t* output, uint32_t bit_offset);
		bool read_short(int16_t* output, uint32_t bit_offset);
		bool read_ushort(uint16_t* output, uint32_t bit_offset);
		bool read_array(int* output, uint32_t count, uint32_t Unk);
		bool read_msg_header(int* out_id);
		bool read_string(char* buffer, int size);
		bool read_token(uint64_t* out_token);
		bool read_byte(uint8_t* out, uint32_t bit_offset);

		void read_vector3(bit_buffer_sync_instance* instance, math::vector3_<float>* output, uint32_t unk, uint32_t bit_offset);
		void write_uint(uint32_t input, uint32_t bit_size, uint32_t bit_offset);
	};

	struct bit_buffer_sync_instance {
		uint64_t m_VTable;
		uint8_t m_type; // 1 = reader, 2 = writer, 3 = calculator, 4 = logger
		char _0x0009[0x7];
		uint64_t m_sub_type; // 0 = reader, 2 = writer, 3 = calculator, 4 = logger
		bit_buffer* m_buffer;
	};
}
#pragma pack(pop)