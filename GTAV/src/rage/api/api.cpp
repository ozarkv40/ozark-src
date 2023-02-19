#include "api.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "util/json.h"
#include "util/log.h"
#include "util/va.h"
#include "util/util.h"
#include "global/vars.h"
#include "auth/http/curl.h"
#include "rage/invoker/natives.h"
#include <fstream>

namespace rage::api {
	void social_club::update() {
		if (m_clear_queue) {
			m_clear_queue = false;
			m_queue.clear();
			return;
		}

		if (!m_queue.empty()) {
			queue_item& item = m_queue.front();
			LOG_DEV("URL: %s", item.m_endpoint.c_str());

			std::unordered_map<std::string, std::string> headers;
			headers[XOR("User-Agent")] = util::create_random_string(10);
			headers[XOR("X-Requested-With")] = XOR("XMLHttpRequest");
			headers[XOR("Authorization")] = util::va::va(XOR("SCAUTH val=\"%s\""), global::vars::g_rs_info->m_scs_ticket);
			headers[XOR("Content-Type")] = XOR("application/json; charset=utf-8");
			headers[XOR("Content-Length")] = std::to_string(item.m_data.size());

			curl::request_state context((uint8_t*)item.m_data.c_str(), item.m_data.size());
			curl::setup_context(&context);
			curl::set_url(&context, item.m_endpoint);
			curl::set_headers(&context, headers);

			CURLcode code = curl::send(&context);
			if (code == CURLE_OK) {
				if (item.m_callback) {
					item.m_callback(context.m_write_chunk.c_str(), item.m_custom);
				} else {
					LOG_DEV("No callback!");
				}
			} else {
				LOG_DEV("CURL Error: %i", code);
			}

			m_queue.erase(m_queue.begin());

			Sleep(1000);
		}
	}

	void social_club::send(std::string endpoint, std::string data, std::function<void(const char*, void*)> callback, void* custom_data) {
		LOG("Adding request to api pool...");
		m_queue.push_back({ endpoint, data, callback, custom_data, 0 });
	}

	void social_club::get_profiles_from_rid(uint64_t rockstar_id, std::function<void(bool, std::vector<rockstar_account>, void*)> callback, void* custom_data) {
		if (rockstar_id < 0x1000) {
			util::fiber::pool::add([=] {
				callback(false, {}, custom_data);
			});

			return;
		}

		send("https://scui.rockstargames.com/api/friend/getprofile",
			nlohmann::json({ { "RockstarId", rockstar_id } }).dump(), [=](const char* jresponse, void* data) {
				if (!nlohmann::json::accept(jresponse)) {
					LOG_DEV("BAD JSON");
					util::fiber::pool::add([=] {
						callback(false, {}, data);
					});

					return;
				}

				try {
					nlohmann::json json = nlohmann::json::parse(jresponse);
					if ((json["Status"].is_null() || !json["Status"].get<bool>()) || (json["Accounts"].is_null() || json["Accounts"].get<nlohmann::json::array_t>().size() == 0)) {
						LOG_DEV("BAD STATUS");

						util::fiber::pool::add([=] {
							callback(false, {}, data);
						});

						return;
					}

					std::vector<rockstar_account> accounts;
					
					int total = json["Total"].is_null() ? 1 : json["Total"];
					for (int i = 0; i < total; i++) {
						accounts.push_back({ json["Accounts"][i]["RockstarAccount"]["Name"], json["Accounts"][i]["RockstarAccount"]["RockstarId"] });
					}

					util::fiber::pool::add([=] {
						callback(true, accounts, data);
					});
				} catch (std::exception& e) {
					LOG_WARN("[Json] %s", e.what());

					util::fiber::pool::add([=] {
						callback(false, {}, data);
					});
				}
			}, custom_data);
	}

	void social_club::get_profiles_from_name(std::string name, std::function<void(bool, std::vector<rockstar_account>, result_info*)> callback, void* custom_data, int page_offset) {
		send("https://scui.rockstargames.com/api/friend/accountsearch",
			nlohmann::json({
				{ "env", "prod" },
				{ "title", "gta5" },
				{ "version", 11 },
				{ "searchNickname", name },
				{ "pageIndex", page_offset }
				}).dump(), [=](const char* jresponse, void* data) {
			if (!nlohmann::json::accept(jresponse)) {
				util::fiber::pool::add([=] {
					callback(false, {}, nullptr);
				});

				return;
			}

			try {
				nlohmann::json json = nlohmann::json::parse(jresponse);
				if ((json["Status"].is_null() || !json["Status"].get<bool>()) || (json["Accounts"].is_null() || json["Accounts"].get<nlohmann::json::array_t>().size() == 0)) {
					util::fiber::pool::add([=] {
						callback(false, {}, nullptr);
					});

					return;
				}

				std::vector<rockstar_account> accounts;

				for (nlohmann::json& account : json["Accounts"]) {
					accounts.push_back({ account["Nickname"], account["RockstarId"] });
				}

				result_info* out_info = new result_info();
				out_info->m_next_offset = json["NextOffset"];
				out_info->m_total = json["Total"];

				util::fiber::pool::add([=] {
					callback(true, accounts, out_info);
				});
			} catch (std::exception& e) {
				LOG_WARN("[Json] %s", e.what());

				util::fiber::pool::add([=] {
					callback(false, {}, nullptr);
				});
			}
		}, custom_data);
	}

	social_club* get_social_club() {
		static social_club instance;
		return &instance;
	}
}