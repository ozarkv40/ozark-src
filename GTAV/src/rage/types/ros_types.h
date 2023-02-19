#pragma once
#include "stdafx.h"

namespace rage::ros {
	struct ros_state {
		char m_ticket[0x100];
		char m_session_ticket[0x100];
		char m_session_key[0x100];
		std::string m_challenge;

		uint8_t m_platform_rc4[0x10];
		uint8_t m_platform_xor[0x10];
		uint8_t m_platform_hashing[0x10];

		uint8_t* m_decrypted_response;
		uint32_t m_decrypted_response_size;
	};

	struct read_stats_state {
		uint64_t m_gamers;
		int m_gamers_count;
		uint64_t m_stats;
		int m_stats_count;
	};

	struct crypto_state {
		uint64_t m_sha1_init;
		uint64_t m_sha1_transform; // sets hmac key
		uint64_t m_sha1_update;
		uint64_t m_sha1_final;
	};
}