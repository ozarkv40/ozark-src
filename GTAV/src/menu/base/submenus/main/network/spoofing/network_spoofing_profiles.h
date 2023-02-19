#pragma once
#include "menu/base/submenu.h"

class network_spoofing_profiles_menu : public menu::submenu::submenu {
public:
	static network_spoofing_profiles_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_profiles_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::profiles::vars {
	struct spoof_profile {
		std::string m_file_name;
		
		uint32_t m_rockstar_id;
		int m_crew_icon;
		std::string m_crew_motto;
		std::string m_crew_name;
		std::string m_crew_rank;
		std::string m_crew_tag;
		std::string m_ip;
		std::string m_name;
	};

	struct spoof_active {
		bool m_active;
		bool m_spoof_name;
		bool m_spoof_rockstar_id;
		bool m_spoof_ip;
		bool m_spoof_crew;
		spoof_profile m_profile;
	};

	struct variables {
		std::vector<spoof_profile> m_profiles;
		spoof_active m_active;
	};

	void save_profile(spoof_profile profile);
	void disable_active_profile();
	extern variables m_vars;
}