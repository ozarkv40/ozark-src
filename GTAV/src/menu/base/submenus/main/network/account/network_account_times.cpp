#include "network_account_times.h"
#include "menu/base/submenu_handler.h"
#include "../network_account.h"
#include "menu/base/util/stats.h"

using namespace network::account::times::vars;

namespace network::account::times::vars {
	variables m_vars;

	scroll_struct<const char*> stat_names[] = {
		{ localization("In Multiplayer", true), "MP_PLAYING_TIME" },
		{ localization("In Car", true), "TIME_IN_CAR" },
		{ localization("In Cover", true), "TIME_IN_COVER" },
		{ localization("In Water", true), "TIME_IN_WATER" },
		{ localization("As a Passenger", true), "TIME_AS_A_PASSENGER" },
		{ localization("As a Driver", true), "TIME_AS_A_DRIVER" },
		{ localization("Flying", true), "TIME_SPENT_FLYING" },
		{ localization("Swimming", true), "TIME_SWIMMING" },
		{ localization("Underwater", true), "TIME_UNDERWATER" },
		{ localization("Walking", true), "TIME_WALKING" },
		{ localization("On Lost Bike", true), "TIME_ON_LOST_BIKE" },
		{ localization("Riding a Bicycle", true), "TIME_DRIVING_BICYCLE" },
		{ localization("Riding a Bike", true), "TIME_DRIVING_BIKE" },
		{ localization("Driving a Boat", true), "TIME_DRIVING_BOAT" },
		{ localization("Driving a Car", true), "TIME_DRIVING_CAR" },
		{ localization("Flying a Helicopter", true), "TIME_DRIVING_HELI" },
		{ localization("Flying a Plane", true), "TIME_DRIVING_PLANE" },
		{ localization("Driving a Quad Bike", true), "TIME_DRIVING_QUADBIKE" },
		{ localization("Driving a Submarine", true), "TIME_DRIVING_SUBMARINE" },
		{ localization("Specating Crew Members", true), "TIME_SPECT_CREW_MEMBERS" },
		{ localization("Spectating Freeroam", true), "TIME_SPECT_FREEROAM" },
		{ localization("Spectating Friends", true), "TIME_SPECT_FRIENDS" },
		{ localization("Spectating Friends (Non Crew)", true), "TIME_SPECT_FRIEND_NOT_CREW" },
		{ localization("Spectating Jobs", true), "TIME_SPECT_JOBS" },
		{ localization("Spectating Strangers", true), "TIME_SPECT_STRANGERS" },
	};

	void set_time() {
		int math = (m_vars.m_days * 86400000) + (m_vars.m_hours * 3600000) + (m_vars.m_minutes * 60000) + (m_vars.m_seconds * 1000) + m_vars.m_milliseconds;
		stats<int>::set(stat_names[m_vars.m_type].m_result, math);
	}

	void initialize() {
		int total = stats<int>::get(stat_names[m_vars.m_type].m_result);
		m_vars.m_days = total / 86400000;
		total = total % 86400000;
		m_vars.m_hours = total / 3600000;
		total = total % 3600000;
		m_vars.m_minutes = total / 60000;
		total = total % 60000;
		m_vars.m_seconds = total / 1000;
		m_vars.m_milliseconds = total % 1000;
	}
}

void network_account_times_menu::load() {
	set_name("Times");
	set_parent<network_account_menu>();

	add_option(scroll_option<const char*>(SCROLL, "Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(stat_names), stat_names)
		.add_click(initialize));

	add_option(number_option<int>(SCROLL, "Days")
		.add_translate()
		.add_number(m_vars.m_days, "%i", 1).add_min(0).add_max(std::numeric_limits<int>::max())
		.add_click(set_time));

	add_option(number_option<int>(SCROLL, "Hours")
		.add_translate()
		.add_number(m_vars.m_hours, "%i", 1).add_min(0).add_max(24)
		.add_click(set_time));

	add_option(number_option<int>(SCROLL, "Minutes")
		.add_translate()
		.add_number(m_vars.m_minutes, "%i", 1).add_min(0).add_max(60)
		.add_click(set_time));

	add_option(number_option<int>(SCROLL, "Seconds")
		.add_translate()
		.add_number(m_vars.m_seconds, "%i", 1).add_min(0).add_max(60)
		.add_click(set_time));

	add_option(number_option<int>(SCROLL, "Milliseconds")
		.add_translate()
		.add_number(m_vars.m_milliseconds, "%i", 1).add_min(0).add_max(1000)
		.add_click(set_time));
}

void network_account_times_menu::update() {}

void network_account_times_menu::update_once() {
	initialize();
}

void network_account_times_menu::feature_update() {}

network_account_times_menu* g_instance;
network_account_times_menu* network_account_times_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_times_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}