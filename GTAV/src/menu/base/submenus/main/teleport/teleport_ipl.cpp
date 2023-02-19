#include "teleport_ipl.h"
#include "menu/base/submenu_handler.h"
#include "../teleport.h"

using namespace teleport::ipl::vars;

namespace teleport::ipl::vars {
	variables m_vars;

	void request(const char** ipls, int count) {
		for (int i = 0; i < count; i++) {
			if (!native::is_ipl_active(ipls[i])) {
				native::request_ipl(ipls[i]);
			}
		}
	}

	void remove(const char** ipls, int count) {
		for (int i = 0; i < count; i++) {
			if (native::is_ipl_active(ipls[i])) {
				native::remove_ipl(ipls[i]);
			}
		}
	}
}

void teleport_ipl_menu::load() {
	set_name("IPL");
	set_parent<teleport_menu>();

	add_option(button_option("North Yankton")
		.add_translate().add_hotkey()
		.add_click([] {
			const char* maps[] = { "plg_01", "prologue01", "prologue01_lod", "prologue01c", "prologue01c_lod", "prologue01d", "prologue01d_lod", "prologue01e", "prologue01e_lod", "prologue01f", "prologue01f_lod", "prologue01g", "prologue01h", "prologue01h_lod", "prologue01i", "prologue01i_lod", "prologue01j", "prologue01j_lod", "prologue01k", "prologue01k_lod", "prologue01z", "prologue01z_lod", "plg_02", "prologue02", "prologue02_lod", "plg_03", "prologue03", "prologue03_lod", "prologue03b", "prologue03b_lod", "prologue03_grv_dug", "prologue03_grv_dug_lod", "prologue_grv_torch", "plg_04", "prologue04", "prologue04_lod", "prologue04b", "prologue04b_lod", "prologue04_cover", "des_protree_end", "des_protree_start", "des_protree_start_lod", "plg_05", "prologue05", "prologue05_lod", "prologue05b", "prologue05b_lod", "plg_06", "prologue06", "prologue06_lod", "prologue06b", "prologue06b_lod", "prologue06_int", "prologue06_int_lod", "prologue06_pannel", "prologue06_pannel_lod", "prologue_m2_door", "prologue_m2_door_lod", "plg_occl_00", "prologue_occl", "plg_rd", "prologuerd", "prologuerdb", "prologuerd_lod" };
			request(maps, 64);
			teleport::vars::teleport({ 3360.19f, -4849.67f, 111.8f });
		}));

	add_option(button_option("Carrier")
		.add_translate().add_hotkey()
		.add_click([] {
			const char* maps[] = { "hei_carrier", "hei_carrier_DistantLights", "hei_Carrier_int1", "hei_Carrier_int2", "hei_Carrier_int3", "hei_Carrier_int4", "hei_Carrier_int5", "hei_Carrier_int6", "hei_carrier_LODLights" };
			request(maps, 9);
			teleport::vars::teleport({ 3016.46f, -4534.09f, 14.84f });
		}));

	add_option(button_option("Dignity Heist Yacht")
		.add_translate().add_hotkey()
		.add_click([] {
			native::remove_ipl("smboat");
			const char* maps[] = { "hei_yacht_heist", "hei_yacht_heist_Bar", "hei_yacht_heist_Bedrm", "hei_yacht_heist_Bridge", "hei_yacht_heist_DistantLights", "hei_yacht_heist_enginrm", "hei_yacht_heist_LODLights", "hei_yacht_heist_Lounge" };
			request(maps, 8);
			teleport::vars::teleport({ -2045.8f, -1031.2f, 11.9f });
		}));

	add_option(button_option("Dignity Party Yacht")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("smboat");
			const char* maps[] = { "hei_yacht_heist", "hei_yacht_heist_Bar", "hei_yacht_heist_Bedrm", "hei_yacht_heist_Bridge", "hei_yacht_heist_DistantLights", "hei_yacht_heist_enginrm", "hei_yacht_heist_LODLights", "hei_yacht_heist_Lounge" };
			remove(maps, 8);
			teleport::vars::teleport({ -2045.8f, -1031.2f, 11.9f });
		}));

	add_option(button_option("Desert UFO")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("ufo");
			teleport::vars::teleport({ 2490.47729f, 3774.84351f, 2414.035f });
		}));

	add_option(button_option("Fort Zancudo UFO")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("ufo");
			teleport::vars::teleport({ -2051.99463f, 3237.05835f, 1456.97021f });
		}));

	add_option(button_option("Cluckin Bell")
		.add_translate().add_hotkey()
		.add_click([] {
			native::remove_ipl("CS1_02_cf_offmission");
			const char* maps[] = { "CS1_02_cf_onmission1", "CS1_02_cf_onmission2", "CS1_02_cf_onmission3", "CS1_02_cf_onmission4" };
			request(maps, 4);
			teleport::vars::teleport({ -72.68752f, 6253.72656f, 31.08991f });
		}));

	add_option(button_option("Jewelery Store")
		.add_translate().add_hotkey()
		.add_click([] {
			native::remove_ipl("jewel2fake");
			native::remove_ipl("bh1_16_refurb");
			native::request_ipl("post_hiest_unload");
			teleport::vars::teleport({ -630.4f, -236.7f, 40.0f });
		}));

	add_option(button_option("Morgue")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("Coroner_Int_on");
			teleport::vars::teleport({ 244.9f, -1374.7f, 39.5f });
		}));

	add_option(button_option("FIB Lobby")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("FIBlobby");
			teleport::vars::teleport({ 110.4f, -744.2f, 45.7f });
		}));

	add_option(button_option("LifeInvader Lobby")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("facelobby");
			teleport::vars::teleport({ -1047.9f, -233.0f, 39.0f });
		}));

	add_option(button_option("Destroyed Hospital")
		.add_translate().add_hotkey()
		.add_click([] {
			native::remove_ipl("RC12B_Default");
			native::remove_ipl("RC12B_Fixed");
			native::request_ipl("RC12B_Destroyed");
			native::request_ipl("RC12B_HospitalInterior");
			teleport::vars::teleport({ 356.8f, -590.1f, 43.3f });
		}));

	add_option(button_option("Cargo Ship")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("cargoship");
			teleport::vars::teleport({ -90.0f, -2365.8f, 14.3f });
		}));

	add_option(button_option("Train Crash")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("canyonriver01_traincrash");
			native::request_ipl("railing_end");
			native::remove_ipl("railing_start");
			native::remove_ipl("canyonriver01");
			teleport::vars::teleport({ -532.1309f, 4526.187f, 88.7955f });
		}));

	add_option(button_option("Broken Stilt House")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("DES_StiltHouse_imapend");
			native::remove_ipl("DES_StiltHouse_imapstart");
			native::remove_ipl("des_stilthouse_rebuild");
			teleport::vars::teleport({ -1020.5f, 663.41f, 154.75f });
		}));

	add_option(button_option("Plane Crash")
		.add_translate().add_hotkey()
		.add_click([] {
			native::request_ipl("Plane_crash_trench");
			teleport::vars::teleport({ 2814.7f, 4758.5f, 50.0f });
		}));

	add_option(button_option("Gunrunning Heist Yacht")
		.add_translate().add_hotkey()
		.add_click([] {
			const char* maps[] = {
				"gr_heist_yacht2",
				"gr_heist_yacht2_bar",
				"gr_heist_yacht2_bedrm",
				"gr_heist_yacht2_bridge",
				"gr_heist_yacht2_enginrm",
				"gr_heist_yacht2_lounge"
			};

			request(maps, NUMOF(maps));
			teleport::vars::teleport({ 1373.828f, 6737.393f, 6.707596f });
		}));
}

void teleport_ipl_menu::update() {}

void teleport_ipl_menu::update_once() {}

void teleport_ipl_menu::feature_update() {}

teleport_ipl_menu* g_instance;
teleport_ipl_menu* teleport_ipl_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new teleport_ipl_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}