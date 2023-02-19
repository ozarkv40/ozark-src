#include "network_account_unlocks.h"
#include "menu/base/submenu_handler.h"
#include "../network_account.h"
#include "menu/base/util/stats.h"

using namespace network::account::unlocks::vars;

namespace network::account::unlocks::vars {
	variables m_vars;

	void unlock_misc() {
		stats<int>::set("CHAR_HEIST_1_UNLCK", -1);
		stats<int>::set("CHAR_ABILITY_1_UNLCK", -1);
		stats<int>::set("CHAR_ABILITY_2_UNLCK", -1);
		stats<int>::set("CHAR_ABILITY_3_UNLCK", -1);
		stats<int>::set("CHAR_FM_HEALTH_1_UNLCK", -1);
		stats<int>::set("CHAR_FM_HEALTH_2_UNLCK", -1);
		stats<int>::set("CHAR_CREWUNLOCK_1_UNLCK", -1);
	}

	void unlock_heist_vehicles() {
		stats<int>::set("CHAR_FM_VEHICLE_1_UNLCK", -1);
		stats<int>::set("CHAR_FM_VEHICLE_2_UNLCK", -1);
	}

	void unlock_weapons() {
		stats<int>::set("CHAR_WEAP_UNLOCKED", -1);
		stats<int>::set("CHAR_WEAP_UNLOCKED2", -1);
		stats<int>::set("CHAR_FM_WEAP_UNLOCKED", -1);
		stats<int>::set("CHAR_FM_WEAP_UNLOCKED2", -1);
		stats<int>::set("CHAR_FM_WEAP_UNLOCKED3", -1);
		stats<int>::set("CHAR_WEAP_ADDON_1_UNLCK", -1);
		stats<int>::set("CHAR_WEAP_ADDON_2_UNLCK", -1);
		stats<int>::set("CHAR_WEAP_ADDON_3_UNLCK", -1);
		stats<int>::set("CHAR_WEAP_ADDON_4_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_1_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_2_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_3_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_4_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_5_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_6_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_7_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_8_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_9_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_10_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_11_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_12_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_13_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_14_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_15_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_16_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_17_UNLCK", -1);
		stats<int>::set("CHAR_FM_WEAP_ADDON_18_UNLCK", -1);
		stats<int>::set("GRENADE_ENEMY_KILLS", 50);
		stats<int>::set("AWD_20_KILLS_MELEE", 50);
		stats<int>::set("CMBTPISTOL_ENEMY_KILLS", 600);
		stats<int>::set("PISTOL50_ENEMY_KILLS", 600);
		stats<int>::set("APPISTOL_ENEMY_KILLS", 600);
		stats<int>::set("MICROSMG_ENEMY_KILLS", 600);
		stats<int>::set("SMG_ENEMY_KILLS", 600);
		stats<int>::set("ASLTSMG_ENEMY_KILLS", 600);
		stats<int>::set("ASLTRIFLE_ENEMY_KILLS", 600);
		stats<int>::set("CRBNRIFLE_ENEMY_KILLS", 600);
		stats<int>::set("ADVRIFLE_ENEMY_KILLS", 600);
		stats<int>::set("MG_ENEMY_KILLS", 600);
		stats<int>::set("CMBTMG_ENEMY_KILLS", 600);
		stats<int>::set("ASLTMG_ENEMY_KILLS", 600);
		stats<int>::set("PUMP_ENEMY_KILLS", 600);
		stats<int>::set("SAWNOFF_ENEMY_KILLS", 600);
		stats<int>::set("BULLPUP_ENEMY_KILLS", 600);
		stats<int>::set("ASLTSHTGN_ENEMY_KILLS", 600);
		stats<int>::set("SNIPERRFL_ENEMY_KILLS", 600);
		stats<int>::set("HVYSNIPER_ENEMY_KILLS", 600);
		stats<int>::set("GRNLAUNCH_ENEMY_KILLS", 600);
		stats<int>::set("RPG_ENEMY_KILLS", 600);
		stats<int>::set("MINIGUNS_ENEMY_KILLS", 600);
		stats<int>::set("SMKGRENADE_ENEMY_KILLS", 600);
		stats<int>::set("STKYBMB_ENEMY_KILLS", 600);
		stats<int>::set("MOLOTOV_ENEMY_KILLS", 600);
	}

	void unlock_clothes() {
		stats<int>::set("CHAR_FM_CLOTHES_1_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_2_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_3_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_4_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_5_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_6_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_7_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_8_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_9_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_10_UNLCK", -1);
		stats<int>::set("CHAR_FM_CLOTHES_11_UNLCK", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB_2", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB_3", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB_4", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB_5", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB_6", -1);
		stats<int>::set("CLTHS_AVAILABLE_JBIB_7", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS_2", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS_3", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS_4", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS_5", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS_6", -1);
		stats<int>::set("CLTHS_AVAILABLE_LEGS_7", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_2", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_3", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_4", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_5", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_6", -1);
		stats<int>::set("CLTHS_AVAILABLE_FEET_7", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD_2", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD_3", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD_4", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD_5", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD_6", -1);
		stats<int>::set("CLTHS_AVAILABLE_BERD_7", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_2", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_3", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_4", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_5", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_6", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_7", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_8", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_9", -1);
		stats<int>::set("CLTHS_AVAILABLE_PROPS_10", -1);
		stats<int>::set("CLTHS_AVAILABLE_OUTFIT", -1);
		stats<int>::set("CLTHS_ACQUIRED_HAIR", -1);
		stats<int>::set("CLTHS_ACQUIRED_HAIR_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_HAIR_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_HAIR_3", -1);
		stats<int>::set("CLTHS_ACQUIRED_HAIR_4", -1);
		stats<int>::set("CLTHS_ACQUIRED_HAIR_5", -1);;
		stats<int>::set("CLTHS_ACQUIRED_HAIR_6", -1);
		stats<int>::set("CLTHS_ACQUIRED_HAIR_7", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB_3", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB_4", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB_5", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB_6", -1);
		stats<int>::set("CLTHS_ACQUIRED_JBIB_7", -1);
		stats<int>::set("CLTHS_ACQUIRED_LEGS", -1);
		stats<int>::set("CLTHS_ACQUIRED_LEGS_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_LEGS_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_LEGS_3", -1);
		stats<int>::set("CLTHS_ACQUIRED_LEGS_4", -1);
		stats<int>::set("CLTHS_ACQUIRED_LEGS_5", -1);
		stats<int>::set("CLTHS_ACQUIRED_LEGS_6", -1);;
		stats<int>::set("CLTHS_ACQUIRED_LEGS_7", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET_3", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET_4", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET_5", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET_6", -1);
		stats<int>::set("CLTHS_ACQUIRED_FEET_7", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD_3", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD_4", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD_5", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD_6", -1);
		stats<int>::set("CLTHS_ACQUIRED_BERD_7", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_3", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_4", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_5", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_6", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_7", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_8", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_9", -1);
		stats<int>::set("CLTHS_ACQUIRED_PROPS_10", -1);
		stats<int>::set("CLTHS_ACQUIRED_OUTFIT", -1);
		stats<int>::set("CLTHS_AVAILABLE_TORSO", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL_2", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL_3", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL_4", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL_5", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL_6", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL_7", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL2", -1);
		stats<int>::set("CLTHS_AVAILABLE_SPECIAL2_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_DECL", -1);
		stats<int>::set("CLTHS_AVAILABLE_TEETH", -1);
		stats<int>::set("CLTHS_AVAILABLE_TEETH_1", -1);
		stats<int>::set("CLTHS_AVAILABLE_TEETH_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_TORSO", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL_2", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL_3", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL_4", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL_5", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL_6", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL_7", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL2", -1);
		stats<int>::set("CLTHS_ACQUIRED_SPECIAL2_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_DECL", -1);
		stats<int>::set("CLTHS_ACQUIRED_TEETH", -1);
		stats<int>::set("CLTHS_ACQUIRED_TEETH_1", -1);
		stats<int>::set("CLTHS_ACQUIRED_TEETH_2", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_0", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_1", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_2", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_3", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_4", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_5", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_6", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_7", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_8", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_9", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_10", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_11", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_12", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_13", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_14", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_15", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_16", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_17", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_18", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_19", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_21", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_22", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_23", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_24", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_24", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_25", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_26", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_27", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_28", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_29", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_30", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_31", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_32", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_33", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_34", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_35", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_36", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_37", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_38", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_39", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_40", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_41", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_42", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_43", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_44", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_45", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_46", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_47", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_48", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_49", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_50", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_51", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_52", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_53", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_54", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_55", -1);
		stats<int>::set("DLC_APPAREL_ACQUIRED_56", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_1", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_2", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_3", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_4", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_5", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_6", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_7", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_8", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_9", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_10", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_11", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_12", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_13", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_1", -1);
		stats<int>::set("ADMIN_CLOTHES_RM_BS_10", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_10", -1);
		stats<int>::set("ADMIN_CLOTHES_RM_BS_11", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_11", -1);
		stats<int>::set("ADMIN_CLOTHES_RM_BS_12", -1);
		stats<int>::set("ADMIN_CLOTHES_GV_BS_12", -1);
		stats<int>::set("AWD_FMHORDWAVESSURVIVE", 10);
		stats<int>::set("AWD_FMPICKUPDLCCRATE1ST", 1);
		stats<int>::set("AWD_WIN_CAPTURE_DONT_DYING", 25);
		stats<int>::set("AWD_DO_HEIST_AS_MEMBER", 25);
		stats<int>::set("AWD_PICKUP_CAP_PACKAGES", 100);
		stats<bool>::set("AWD_FINISH_HEIST_NO_DAMAGE", 1);
		stats<int>::set("AWD_WIN_GOLD_MEDAL_HEISTS", 25);
		stats<int>::set("AWD_KILL_TEAM_YOURSELF_LTS", 25);
		stats<int>::set("AWD_KILL_PSYCHOPATHS", 100);
		stats<int>::set("AWD_DO_HEIST_AS_THE_LEADER", 25);
		stats<bool>::set("AWD_STORE_20_CAR_IN_GARAGES", 1);
	}

	void unlock_haircuts() {
		stats<int>::set("CHAR_HAIR_UNLCK1", -1);
		stats<int>::set("CHAR_HAIR_UNLCK2", -1);
		stats<int>::set("CHAR_HAIR_UNLCK3", -1);
		stats<int>::set("CHAR_HAIR_UNLCK4", -1);
		stats<int>::set("CHAR_HAIR_UNLCK5", -1);
		stats<int>::set("CHAR_HAIR_UNLCK6", -1);
		stats<int>::set("CHAR_HAIR_UNLCK7", -1);
		stats<int>::set("CHAR_HAIR_UNLCK8", -1);
		stats<int>::set("CHAR_HAIR_UNLCK9", -1);
		stats<int>::set("CHAR_HAIR_UNLCK10", -1);
		stats<int>::set("CHAR_HAIR_UNLCK11", -1);
		stats<int>::set("CHAR_HAIR_UNLCK12", -1);
		stats<int>::set("CHAR_HAIR_UNLCK13", -1);
		stats<int>::set("CHAR_HAIR_UNLCK14", -1);
		stats<int>::set("CHAR_HAIR_UNLCK15", -1);
		stats<int>::set("CHAR_HAIR_UNLCK16", -1);
		stats<int>::set("CHAR_FM_HAIRCUT_1_UNLCK", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR1", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR2", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR3", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR4", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR5", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR6", -1);
		stats<int>::set("CLTHS_AVAILABLE_HAIR7", -1);
	}

	void unlock_tattoos() {
		stats<bool>::set("AWD_FMATTGANGHQ", true);
		stats<bool>::set("AWD_FMKILLSTREAKSDM", true);
		stats<bool>::set("AWD_FMWINEVERYGAMEMODE", true);
		stats<bool>::set("AWD_FMRACEWORLDRECHOLDER", true);
		stats<bool>::set("AWD_FMFULLYMODDEDCAR", true);
		stats<bool>::set("AWD_FMMOSTKILLSSURVIVE", true);
		stats<bool>::set("AWD_FMKILL3ANDWINGTARACE", true);
		stats<int>::set("AWD_FM_DM_WINS", 50);
		stats<int>::set("AWD_FM_TDM_MVP", 50);
		stats<int>::set("AWD_FM_DM_TOTALKILLS", 500);
		stats<int>::set("AWD_FMBBETWIN", 50000);
		stats<int>::set("AWD_FMKILLBOUNTY", 25);
		stats<int>::set("AWD_FMREVENGEKILLSDM", 50);
		stats<int>::set("AWD_HOLD_UP_SHOPS", 20);
		stats<int>::set("AWD_LAPDANCES", 25);
		stats<int>::set("AWD_SECURITY_CARS_ROBBED", 25);
		stats<int>::set("AWD_RACES_WON", 50);
		stats<int>::set("AWD_CAR_BOMBS_ENEMY_KILLS", 25);
		stats<int>::set("PLAYER_HEADSHOTS", 500);
		stats<int>::set("DB_PLAYER_KILLS", 1000);
		stats<int>::set("TATTOO_FM_UNLOCKS_0", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_1", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_2", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_3", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_4", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_5", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_6", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_7", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_8", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_9", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_10", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_11", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_12", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_13", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_14", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_15", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_16", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_17", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_18", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_19", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_20", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_21", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_22", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_23", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_24", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_25", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_26", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_27", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_28", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_29", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_30", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_31", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_32", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_33", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_34", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_35", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_36", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_37", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_38", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_39", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_40", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_41", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_42", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_43", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_44", -1);
		stats<int>::set("TATTOO_FM_UNLOCKS_45", -1);
	}

	void unlock_camo_and_parachutes() {
		stats<int>::set("CHAR_KIT_1_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_2_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_3_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_4_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_5_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_6_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_7_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_8_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_9_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_10_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_11_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_12_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_13_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_14_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_15_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_16_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_17_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_18_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_19_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_20_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_21_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_22_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_23_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_24_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_25_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_26_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_27_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_28_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_29_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_30_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_31_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_32_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_33_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_34_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_35_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_36_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_37_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_38_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_39_FM_UNLCK", -1);
		stats<int>::set("CHAR_KIT_40_FM_UNLCK", -1);
	}

	void unlock_los_santos_customs() {
		stats<int>::set("RACES_WON", 50);
		stats<int>::set("CHAR_FM_CARMOD_1_UNLCK", -1);
		stats<int>::set("CHAR_FM_CARMOD_2_UNLCK", -1);
		stats<int>::set("CHAR_FM_CARMOD_3_UNLCK", -1);
		stats<int>::set("CHAR_FM_CARMOD_4_UNLCK", -1);
		stats<int>::set("CHAR_FM_CARMOD_5_UNLCK", -1);
		stats<int>::set("CHAR_FM_CARMOD_6_UNLCK", -1);
		stats<int>::set("CHAR_FM_CARMOD_7_UNLCK", -1);
		stats<int>::set("NUMBER_SLIPSTREAMS_IN_RACE", 110);
		stats<int>::set("NUMBER_TURBO_STARTS_IN_RACE", 90);
		stats<int>::set("USJS_FOUND", 50);
		stats<int>::set("USJS_COMPLETED", 50);
		stats<int>::set("AWD_FMRALLYWONDRIVE", 2);
		stats<int>::set("AWD_FMRALLYWONNAV", 2);
		stats<int>::set("AWD_FMWINSEARACE", 2);
		stats<int>::set("AWD_FMWINAIRRACE", 2);
		stats<int>::set("AWD_FM_RACES_FASTEST_LAP", 101);
		stats<int>::set("AWD_WIN_CAPTURES", 25);
		stats<int>::set("AWD_DROPOFF_CAP_PACKAGES", 100);
		stats<int>::set("AWD_KILL_CARRIER_CAPTURE", 100);
		stats<int>::set("AWD_FINISH_HEISTS", 50);
		stats<int>::set("AWD_FINISH_HEIST_SETUP_JOB", 50);
		stats<int>::set("AWD_NIGHTVISION_KILLS", 100);
		stats<int>::set("AWD_WIN_LAST_TEAM_STANDINGS", 50);
		stats<int>::set("AWD_ONLY_PLAYER_ALIVE_LTS", 50);
		stats<int>::set("AWD_ENEMYDRIVEBYKILLS", 600);
		stats<int>::set("DB_PLAYER_KILLS", 1000);
		stats<int>::set("KILLS_PLAYERS", 1000);
		stats<int>::set("AWD_FMHORDWAVESSURVIVE", 21);
		stats<int>::set("AWD_CAR_BOMBS_ENEMY_KILLS", 25);
		stats<int>::set("AWD_FM_TDM_MVP", 60);
		stats<int>::set("AWD_HOLD_UP_SHOPS", 20);
		stats<int>::set("AWD_RACES_WON", 101);
		stats<int>::set("AWD_NO_ARMWRESTLING_WINS", 21);
		stats<int>::set("AWD_FMBBETWIN", 50000);
		stats<int>::set("AWD_FM_DM_WINS", 51);
		stats<int>::set("AWD_FM_DM_TOTALKILLS", 500);
		stats<int>::set("MPPLY_DM_TOTAL_DEATHS", 412);
		stats<int>::set("MPPLY_TIMES_FINISH_DM_TOP_3", 36);
		stats<int>::set("PLAYER_HEADSHOTS", 623);
		stats<int>::set("AWD_FM_DM_WINS", 63);
		stats<int>::set("AWD_FM_TDM_WINS", 13);
		stats<int>::set("AWD_FM_GTA_RACES_WON", 12);
		stats<int>::set("AWD_FM_GOLF_WON", 2);
		stats<int>::set("AWD_FM_SHOOTRANG_TG_WON", 2);
		stats<int>::set("AWD_FM_SHOOTRANG_RT_WON", 2);
		stats<int>::set("AWD_FM_SHOOTRANG_CT_WON", 2);
		stats<int>::set("AWD_FM_SHOOTRANG_GRAN_WON", 2);
		stats<int>::set("AWD_FM_TENNIS_WON", 2);
		stats<int>::set("MPPLY_TENNIS_MATCHES_WON", 2);
		stats<int>::set("MPPLY_TOTAL_TDEATHMATCH_WON", 63);
		stats<int>::set("MPPLY_TOTAL_RACES_WON", 101);
		stats<int>::set("MPPLY_TOTAL_DEATHMATCH_LOST", 23);
		stats<int>::set("MPPLY_TOTAL_RACES_LOST", 36);
		stats<int>::set("AWD_25_KILLS_STICKYBOMBS", 50);
		stats<int>::set("AWD_50_KILLS_GRENADES", 50);
		stats<int>::set("GRENADE_ENEMY_KILLS", 50);
		stats<int>::set("AWD_20_KILLS_MELEE", 50);
		stats<int>::set("ARENAWARS_AP_TIER", 1000);
	}

	void unlock_club_popularity() {
		stats<int>::set("CLUB_POPULARITY", 1000);
	}

	void unlock_bunker_research() {
		std::map<int, int> map({ { 0, 15381 }, { 1, 15382 }, { 2, 15428 }, { 3, 15429 }, { 4, 15430 }, { 5, 15431 }, { 6, 15491 }, { 7, 15432 }, { 8, 15433 }, { 9, 15434 }, { 10, 15435 }, { 11, 15436 }, { 12, 15437 }, { 13, 15438 }, { 14, 15439 }, { 15, 15447 }, { 16, 15448 }, { 17, 15449 }, { 18, 15450 }, { 19, 15451 }, { 20, 15452 }, { 21, 15453 }, { 22, 15454 }, { 23, 15455 }, { 24, 15456 }, { 25, 15457 }, { 26, 15458 }, { 27, 15459 }, { 28, 15460 }, { 29, 15461 }, { 30, 15462 }, { 31, 15463 }, { 32, 15464 }, { 33, 15465 }, { 34, 15466 }, { 35, 15467 }, { 36, 15468 }, { 37, 15469 }, { 38, 15470 }, { 39, 15471 }, { 40, 15472 }, { 41, 15473 }, { 42, 15474 }, { 43, 15492 }, { 44, 15493 }, { 45, 15494 }, { 46, 15495 }, { 47, 15496 }, { 48, 15497 }, { 49, 15498 }, { 50, 15499 } });

		for (auto entry : map) {
			const auto hash = native::get_ngstat_bool_hash(entry.second - 15369, 0, 1, network::account::vars::m_vars.m_selected_character, "_DLCGUNPSTAT_BOOL");
			const auto mask = ((entry.second - 15369) - native::_0xF4D8E7AC2A27758C(entry.second - 15369) * 64);
			native::stat_set_bool_masked(hash, true, mask, true);
		}

		stats<int>::set("GUNR_RESEARCH_ITEM", -1);
	}

	void unlock_max_abilities() {
		stats<int>::set("SCRIPT_INCREASE_STAM", 100);
		stats<int>::set("SCRIPT_INCREASE_STRN", 100);
		stats<int>::set("SCRIPT_INCREASE_LUNG", 100);
		stats<int>::set("SCRIPT_INCREASE_DRIV", 100);
		stats<int>::set("SCRIPT_INCREASE_FLY", 100);
		stats<int>::set("SCRIPT_INCREASE_SHO", 100);
		stats<int>::set("SCRIPT_INCREASE_STL", 100);
	}

	void unlock_max_snacks() {
		stats<int>::set("NO_BOUGHT_YUM_SNACKS", 30);
		stats<int>::set("NO_BOUGHT_HEALTH_SNACKS", 15);
		stats<int>::set("NO_BOUGHT_EPIC_SNACKS", 5);
		stats<int>::set("NUMBER_OF_CHAMP_BOUGHT", 5);
		stats<int>::set("NUMBER_OF_ORANGE_BOUGHT", 10);
		stats<int>::set("NUMBER_OF_BOURGE_BOUGHT", 10);
		stats<int>::set("CIGARETTES_BOUGHT", 20);
	}

	void unlock_max_armor() {
		stats<int>::set("MP_CHAR_ARMOUR_1_COUNT", 10);
		stats<int>::set("MP_CHAR_ARMOUR_2_COUNT", 10);
		stats<int>::set("MP_CHAR_ARMOUR_3_COUNT", 10);
		stats<int>::set("MP_CHAR_ARMOUR_4_COUNT", 10);
		stats<int>::set("MP_CHAR_ARMOUR_5_COUNT", 10);
	}

	void unlock_max_fireworks() {
		stats<int>::set("FIREWORK_TYPE_1_WHITE", 2000000);
		stats<int>::set("FIREWORK_TYPE_1_RED", 2000000);
		stats<int>::set("FIREWORK_TYPE_1_BLUE", 2000000);
		stats<int>::set("FIREWORK_TYPE_2_WHITE", 2000000);
		stats<int>::set("FIREWORK_TYPE_2_RED", 2000000);
		stats<int>::set("FIREWORK_TYPE_2_BLUE", 2000000);
		stats<int>::set("FIREWORK_TYPE_3_WHITE", 2000000);
		stats<int>::set("FIREWORK_TYPE_3_RED", 2000000);
		stats<int>::set("FIREWORK_TYPE_3_BLUE", 2000000);
		stats<int>::set("FIREWORK_TYPE_4_WHITE", 2000000);
		stats<int>::set("FIREWORK_TYPE_4_RED", 2000000);
		stats<int>::set("FIREWORK_TYPE_4_BLUE", 2000000);
	}

	void unlock_all() {
		unlock_misc();
		unlock_heist_vehicles();
		unlock_weapons();
		unlock_clothes();
		unlock_haircuts();
		unlock_tattoos();
		unlock_camo_and_parachutes();
		unlock_los_santos_customs();
		unlock_club_popularity();
		unlock_bunker_research();
		unlock_max_abilities();
		unlock_max_snacks();
		unlock_max_armor();
		unlock_max_fireworks();
	}
}

void network_account_unlocks_menu::load() {
	set_name("Unlocks");
	set_parent<network_account_menu>();

	add_option(button_option("Unlock All")
		.add_translate()
		.add_click(unlock_all));

	add_option(button_option("Tattoos")
		.add_translate()
		.add_click(unlock_tattoos));

	add_option(button_option("Clothes")
		.add_translate()
		.add_click(unlock_clothes));

	add_option(button_option("Haircuts")
		.add_translate()
		.add_click(unlock_haircuts));

	add_option(button_option("Weapons")
		.add_translate()
		.add_click(unlock_weapons));

	add_option(button_option("Camo and Parachutes")
		.add_translate()
		.add_click(unlock_camo_and_parachutes));

	add_option(button_option("Los Santos Customs")
		.add_translate()
		.add_click(unlock_los_santos_customs));

	add_option(button_option("Heist Vehicles")
		.add_translate()
		.add_click(unlock_heist_vehicles));

	add_option(button_option("Club Propularity")
		.add_translate()
		.add_click(unlock_club_popularity));

	add_option(button_option("Bunker Research")
		.add_translate()
		.add_click(unlock_bunker_research));

	add_option(button_option("Abilities")
		.add_translate()
		.add_click(unlock_max_abilities));

	add_option(button_option("Snacks")
		.add_translate()
		.add_click(unlock_max_snacks));

	add_option(button_option("Armor")
		.add_translate()
		.add_click(unlock_max_armor));

	add_option(button_option("Fireworks")
		.add_translate()
		.add_click(unlock_max_fireworks));

	add_option(button_option("Misc")
		.add_translate()
		.add_click(unlock_misc));
}

void network_account_unlocks_menu::update() {}

void network_account_unlocks_menu::update_once() {}

void network_account_unlocks_menu::feature_update() {}

network_account_unlocks_menu* g_instance;
network_account_unlocks_menu* network_account_unlocks_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_unlocks_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}