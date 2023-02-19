#pragma once
#include "stdafx.h"
#include <functional>
#include <vector>

namespace rage::api {
	struct rockstar_account {
		std::string m_name;
		uint64_t m_rockstar_id;
	};

	struct result_info {
		int m_total = 0;
		int m_next_offset = 0;
	};

	struct queue_item {
		std::string m_endpoint;
		std::string m_data;
		std::function<void(const char*, void*)> m_callback;
		void* m_custom;
		uint32_t m_data_hash;
	};

	class social_club {
	public:
		void update();
		void send(std::string endpoint, std::string data, std::function<void(const char*, void*)> callback, void* custom_data);
		void get_profiles_from_rid(uint64_t rockstar_id, std::function<void(bool, std::vector<rockstar_account>, void*)> callback, void* custom_data);
		void get_profiles_from_name(std::string name, std::function<void(bool, std::vector<rockstar_account>, result_info*)> callback, void* custom_data, int page_offset = 0);

		bool m_clear_queue = false;
	private:
		std::vector<queue_item> m_queue;
	};

	social_club* get_social_club();

	inline void update() {
		get_social_club()->update();
	}

	inline void send(std::string endpoint, std::string data, std::function<void(const char*, void*)> callback, void* custom_data) {
		get_social_club()->send(endpoint, data, callback, custom_data);
	}

	inline void get_profiles_from_rid(uint64_t rockstar_id, std::function<void(bool, std::vector<rockstar_account>, void*)> callback, void* custom_data) {
		get_social_club()->get_profiles_from_rid(rockstar_id, callback, custom_data);
	}

	inline void get_profiles_from_name(std::string name, std::function<void(bool, std::vector<rockstar_account>, result_info*)> callback, void* custom_data, int page_offset = 0) {
		get_social_club()->get_profiles_from_name(name, callback, custom_data, page_offset);
	}
}