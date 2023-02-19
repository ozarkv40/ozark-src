#include "hooks.h"
#include "util/json.h"
#include "global/vars.h"
#include "util/log.h"
#include "util/util.h"
#include "rage/engine.h"

bool menu::hooks::receive_session_info(uint64_t rcx) {
	bool _return = true;

	if (rcx && *(int*)(rcx + 0x2944)) {
		int i = 0;
		do {
			uint64_t address = rcx + 0x2840 + (i * 8);
			if (*(uint64_t*)(address)) {
				const char* response = *(const char**)(address);
				if (response) {
					try {
						nlohmann::json json = nlohmann::json::parse(response);
						if (json.find("gsinfo") == json.end()) {
							return false;
						}

						uint64_t rockstar_id = std::stoull(json["_id"].get<std::string>().substr(3));
						std::string gs_info = json["gsinfo"].get<std::string>();
						int gs_type = json["gstype"].is_null() ? -1 : json["gstype"];

						rage::network::gs_session session;
						rage::engine::get_session_info_from_gs(&session, gs_info.c_str());

						LOG_DEV("[%i] %s", rockstar_id, util::convert_bytes_to_string((uint8_t*)&session, sizeof(session), true).c_str());

						if (!global::vars::g_gs_info_requests.empty()) {
							for (gs_info_request& request : global::vars::g_gs_info_requests) {
								if (request.m_rockstar_id == rockstar_id) {
									request.m_callback(gs_info, rockstar_id);
									request.m_finished = true;
									_return = false;
								}
							}
						}

						auto vit = std::find_if(begin(global::vars::g_online_rockstar_ids_queue), end(global::vars::g_online_rockstar_ids_queue), [=](uint64_t value) {
							return value == rockstar_id;
						});;

						if (vit != end(global::vars::g_online_rockstar_ids_queue)) {
							_return = false;

							global::vars::g_online_rockstar_ids[rockstar_id] = { !gs_info.empty(), gs_type };
							global::vars::g_online_rockstar_ids_queue.erase(vit);
						}
					} catch (...) {
						return false;
					}
				}
			}

			i++;
		} while (i < *(int*)(rcx + 0x2944));
	}

	if (!_return) return false;
	return receive_session_info_t(rcx);
}