#pragma once
#include "invoker.h"
#include "rage/types/base_types.h"
#define _i rage::invoker::invoke

namespace native {
	static int ceil(float value) { return _i<int>(0x11E019C8F43ACC8A, value); }
	static float cos(float value) { return _i<float>(0xD0FFB162F40A139C, value); }
	static int floor(float value) { return _i<int>(0xF34EE736CF047844, value); }
	static float pow(float base, float exponent) { return _i<float>(0xE3621CC40F31FE2E, base, exponent); }
	static int round(float value) { return _i<int>(0xF2DB717A73826179, value); }
	static Void settimera(int value) { return _i<Void>(0xC1B1E9A034A63A62, value); }
	static Void settimerb(int value) { return _i<Void>(0x5AE11BC36633DE4E, value); }
	static Void _0x42B65DEEF2EDF2A1(Any p0) { return _i<Void>(0x42B65DEEF2EDF2A1, p0); }
	static int shift_left(int value, int bitShift) { return _i<int>(0xEDD95A39E5544DE8, value, bitShift); }
	static int shift_right(int value, int bitShift) { return _i<int>(0x97EF1E5BCE9DC075, value, bitShift); }
	static float sin(float value) { return _i<float>(0x0BADBFA3B172435F, value); }
	static float sqrt(float value) { return _i<float>(0x71D93B57D07F9804, value); }
	static int timera() { return _i<int>(0x83666F9FB8FEBD4B); }
	static int timerb() { return _i<int>(0xC9D9444186B5A374); }
	static float timestep() { return _i<float>(0x0000000050597EE2); }
	static float to_float(int value) { return _i<float>(0xBBDA792448DB5A89, value); }
	static float vdist2(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<float>(0xB7A628320EFF8E47, x1, y1, z1, x2, y2, z2); }
	static float vdist(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<float>(0x2A488C176D52CCA5, x1, y1, z1, x2, y2, z2); }
	static float vmag2(float x, float y, float z) { return _i<float>(0xA8CEACB4F35AE058, x, y, z); }
	static float vmag(float x, float y, float z) { return _i<float>(0x652D2EEEF1D3E62C, x, y, z); }
	static int start_new_script(const char* scriptName, int stackSize) { return _i<int>(0xE81651AD79516E48, scriptName, stackSize); }
	static int start_new_script_with_args(const char* scriptName, uint64_t* args, int argCount, int stackSize) { return _i<int>(0xB8BA7F44DF1575E1, scriptName, args, argCount, stackSize); }
	static int start_new_script_with_name_hash(uint32_t scriptHash, int stackSize) { return _i<int>(0xEB1C67C3A5333A92, scriptHash, stackSize); }
	static int start_new_script_with_name_hash_and_args(uint32_t scriptHash, Any* args, int argCount, int stackSize) { return _i<int>(0xC4BB298BD441BE78, scriptHash, args, argCount, stackSize); }
	static Void wait(int ms) { return _i<Void>(0x4EDE34FBADD967A6, ms); }

	static Void app_clear_block() { return _i<Void>(0x5FE1DF3342DB7DBA); }
	static Void app_close_app() { return _i<Void>(0xE41C65E07A5F05FC); }
	static Void app_close_block() { return _i<Void>(0xE8E3FCF72EAC0EF8); }
	static bool app_data_valid() { return _i<bool>(0x846AA8E7D55EE5B6); }
	static bool app_delete_app_data(const char* appName) { return _i<bool>(0x44151AEA95C8A003, appName); }
	static Any app_get_deleted_file_status() { return _i<Any>(0xC9853A2BE3DED1A6); }
	static float app_get_float(const char* property) { return _i<float>(0x1514FB24C02C2322, property); }
	static int app_get_int(const char* property) { return _i<int>(0xD3A58A12C77D9D4B, property); }
	static const char* app_get_string(const char* property) { return _i<const char*>(0x749B023950D2311C, property); }
	static bool app_has_linked_social_club_account() { return _i<bool>(0x71EEE69745088DA0); }
	static bool app_has_synced_data(const char* appName) { return _i<bool>(0xCA52279A7271517F, appName); }
	static Void app_save_data() { return _i<Void>(0x95C5D356CDA6E85F); }
	static Void app_set_app(const char* appName) { return _i<Void>(0xCFD0406ADAF90D2B, appName); }
	static Void app_set_block(const char* blockName) { return _i<Void>(0x262AB456A3D21F93, blockName); }
	static Void app_set_float(const char* property, float value) { return _i<Void>(0x25D7687C68E0DAA4, property, value); }
	static Void app_set_int(const char* property, int value) { return _i<Void>(0x607E8E3D3E4F9611, property, value); }
	static Void app_set_string(const char* property, const char* value) { return _i<Void>(0x3FF2FCEC4B7721B4, property, value); }

	static Void stop_stream() { return _i<Void>(0xA4718A1419D18151); }
	static Void _0xD01005D2BA2EB778(Any* p0) { return _i<Void>(0xD01005D2BA2EB778, p0); }
	static Void dynamic_mixer_related_fn(Entity p0, const char* p1, float p2) { return _i<Void>(0x153973AB99FE8980, p0, p1, p2); }
	static Void add_line_to_conversation(int p0, const char* p1, const char* p2, int p3, int p4, bool p5, bool p6, bool p7, bool p8, int p9, bool p10, bool p11, bool p12) { return _i<Void>(0xC5EF963405593646, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	static Void add_ped_to_conversation(Any p0, Any ped, const char* p2) { return _i<Void>(0x95D9F4BC443956E7, p0, ped, p2); }
	static Any _0x3D120012440E6683() { return _i<Any>(0x3D120012440E6683); }
	static Any audio_is_scripted_music_playing() { return _i<Any>(0x845FFC3A4FEEFA3E); }
	static Void blip_siren(Vehicle vehicle) { return _i<Void>(0x1B9025BDA76822B6, vehicle); }
	static Void _0xF154B8D1775B2DEC(bool p0) { return _i<Void>(0xF154B8D1775B2DEC, p0); }
	static Void disable_police_reports() { return _i<Void>(0xB4F90FAF7670B16F); }
	static bool cancel_music_event(const char* eventName) { return _i<bool>(0x5B17A90291133DA5, eventName); }
	static bool is_vehicle_radio_loud(Vehicle vehicle) { return _i<bool>(0x032A116663A4D5AC, vehicle); }
	static Void clear_all_broken_glass() { return _i<Void>(0xB32209EFFDC04913); }
	static Void clear_ambient_zone_list_state(Any* p0, bool p1) { return _i<Void>(0x120C48C614909FA4, p0, p1); }
	static Void clear_ambient_zone_state(const char* zoneName, bool p1) { return _i<Void>(0x218DD44AAAC964FF, zoneName, p1); }
	static Void _0x1654F24A88A8E3FE(const char* radioStation) { return _i<Void>(0x1654F24A88A8E3FE, radioStation); }
	static Void create_new_scripted_conversation() { return _i<Void>(0xD2C91A0B572AAE56); }
	static Void _0xDDC635D5B3262C56(Any* p0) { return _i<Void>(0xDDC635D5B3262C56, p0); }
	static Void disable_ped_pain_audio(Ped ped, bool toggle) { return _i<Void>(0xA9A41C1E940FB0E8, ped, toggle); }
	static Void force_ambient_siren(bool value) { return _i<Void>(0x552369F549563AD5, value); }
	static bool can_ped_speak(Ped ped, const char* speechName, bool unk) { return _i<bool>(0x49B99BF3FDA89A7A, ped, speechName, unk); }
	static bool _0x109697E2FFBAC8A1() { return _i<bool>(0x109697E2FFBAC8A1); }
	static Void _0xC15907D667F7CFB2(Vehicle vehicle, bool toggle) { return _i<Void>(0xC15907D667F7CFB2, vehicle, toggle); }
	static Void _0xB81CF134AEB56FFB() { return _i<Void>(0xB81CF134AEB56FFB); }
	static Void _0x2BE4BC731D039D5A(Any p0, bool p1) { return _i<Void>(0x2BE4BC731D039D5A, p0, p1); }
	static Void _0x1C073274E065C6D2(Any p0, bool p1) { return _i<Void>(0x1C073274E065C6D2, p0, p1); }
	static int find_radio_station_index(int station) { return _i<int>(0x8D67489793FF428B, station); }
	static Void _0x062D5EAD4DA2FA6A() { return _i<Void>(0x062D5EAD4DA2FA6A); }
	static Void set_vehicle_audio(Vehicle vehicle, const char* audioName) { return _i<Void>(0x4F0C413926060B38, vehicle, audioName); }
	static Void _0xD57AAAE0E2214D11() { return _i<Void>(0xD57AAAE0E2214D11); }
	static Void freeze_radio_station(const char* radioStation) { return _i<Void>(0x344F393B027E38C3, radioStation); }
	static Any _0x5E203DA2BA15D436(Any p0) { return _i<Any>(0x5E203DA2BA15D436, p0); }
	static int get_audible_music_track_text_id() { return _i<int>(0x50B196FC9ED6545B); }
	static Any get_current_scripted_conversation_line() { return _i<Any>(0x480357EE890C295A); }
	static Any _0xE73364DB90778FFA() { return _i<Any>(0xE73364DB90778FFA); }
	static Any get_music_playtime() { return _i<Any>(0xE7A0D23DC414507B); }
	static Any _0x3A48AB4445D499BE() { return _i<Any>(0x3A48AB4445D499BE); }
	static int get_network_id_from_sound_id(int soundId) { return _i<int>(0x2DE3F0A134FFBC0D, soundId); }
	static int max_radio_station_index() { return _i<int>(0xF1620ECB50E01DE7); }
	static Any get_player_radio_station_genre() { return _i<Any>(0xA571991A7FE6CCEB); }
	static int get_player_radio_station_index() { return _i<int>(0xE8AF77C4C06ADC93); }
	static const char* get_player_radio_station_name() { return _i<const char*>(0xF6D733C32076AD03); }
	static const char* get_radio_station_name(int radioStation) { return _i<const char*>(0xB28ECA15046CA8B9, radioStation); }
	static int get_sound_id() { return _i<int>(0x430386FE9BF80B45); }
	static int get_sound_id_from_network_id(int netId) { return _i<int>(0x75262FD12D0A1C84, netId); }
	static int get_stream_play_time() { return _i<int>(0x4E72BBDBCA58A3DB); }
	static Any _0xAA19F5572C38B564(Any* p0) { return _i<Any>(0xAA19F5572C38B564, p0); }
	static uint32_t get_vehicle_default_horn(Vehicle vehicle) { return _i<uint32_t>(0x02165D55000219AC, vehicle); }
	static uint32_t get_vehicle_horn_hash(Vehicle vehicle) { return _i<uint32_t>(0xACB5DCCA1EC76840, vehicle); }
	static Any _0x544810ED9DB6BBE6() { return _i<Any>(0x544810ED9DB6BBE6); }
	static Any _0x5B50ABB1FE3746F4() { return _i<Any>(0x5B50ABB1FE3746F4); }
	static bool has_sound_finished(int soundId) { return _i<bool>(0xFCBDCE714A7C88E5, soundId); }
	static Any _0x40763EA7B9B783E7(Any p0, Any p1, Any p2) { return _i<Any>(0x40763EA7B9B783E7, p0, p1, p2); }
	static Any hint_ambient_audio_bank(Any p0, Any p1, Any p2) { return _i<Any>(0x8F8C0E370AE62F5C, p0, p1, p2); }
	static Any hint_script_audio_bank(Any p0, Any p1, Any p2) { return _i<Any>(0xFB380A29641EC31A, p0, p1, p2); }
	static Void set_synchronized_audio_event_position_this_frame(const char* p0, Entity p1) { return _i<Void>(0x950A154B8DAB6185, p0, p1); }
	static Void _0xC8EDE9BDBCCBA6D4(Any* p0, float p1, float p2, float p3) { return _i<Void>(0xC8EDE9BDBCCBA6D4, p0, p1, p2, p3); }
	static Void interrupt_conversation(Any p0, Any* p1, Any* p2) { return _i<Void>(0xA018A12E5C5C2FA6, p0, p1, p2); }
	static Void _0x8A694D7A68F8DC38(Ped p0, const char* p1, const char* p2) { return _i<Void>(0x8A694D7A68F8DC38, p0, p1, p2); }
	static bool is_alarm_playing(const char* alarmName) { return _i<bool>(0x226435CB96CCFC8C, alarmName); }
	static bool is_ambient_speech_disabled(Ped ped) { return _i<bool>(0x932C2D096A2C3FFF, ped); }
	static bool is_ambient_speech_playing(Ped p0) { return _i<bool>(0x9072C8B49907BFAD, p0); }
	static bool is_ambient_zone_enabled(const char* ambientZone) { return _i<bool>(0x01E2817A479A7F9B, ambientZone); }
	static bool _0xC265DF9FB44A9FBD(Any p0) { return _i<bool>(0xC265DF9FB44A9FBD, p0); }
	static bool is_any_speech_playing(Ped ped) { return _i<bool>(0x729072355FA39EC9, ped); }
	static bool is_audio_scene_active(const char* scene) { return _i<bool>(0xB65B60556E2A9225, scene); }
	static bool is_game_in_control_of_music() { return _i<bool>(0x6D28DC1671E334FD); }
	static bool is_horn_active(Vehicle vehicle) { return _i<bool>(0x9D6BFC12B05C6121, vehicle); }
	static bool is_mission_complete_playing() { return _i<bool>(0x19A30C23F5827F8A); }
	static Any _0x6F259F82D873B8B8() { return _i<Any>(0x6F259F82D873B8B8); }
	static int get_number_of_passenger_voice_variations(Any p0) { return _i<int>(0x66E49BF55B4B1874, p0); }
	static Any _0xC8B1B2425604CDD0() { return _i<Any>(0xC8B1B2425604CDD0); }
	static bool is_mobile_phone_call_ongoing() { return _i<bool>(0x7497D2CE2C30D24C); }
	static bool is_mobile_phone_radio_active() { return _i<bool>(0xB35CE999E8EF317E); }
	static Any _0xA097AB275061FB21() { return _i<Any>(0xA097AB275061FB21); }
	static bool is_ped_in_current_conversation(Ped ped) { return _i<bool>(0x049E937F18F4020C, ped); }
	static bool is_ped_ringtone_playing(Ped ped) { return _i<bool>(0x1E8E5E20937E3137, ped); }
	static bool is_player_vehicle_radio_enabled() { return _i<bool>(0x5F43D83FD6738741); }
	static Any _0x0626A247D2405330() { return _i<Any>(0x0626A247D2405330); }
	static bool is_radio_retuning() { return _i<bool>(0xA151A7394A214E65); }
	static bool is_scripted_conversation_loaded() { return _i<bool>(0xDF0D54BE7A776737); }
	static bool is_scripted_conversation_ongoing() { return _i<bool>(0x16754C556D2EDE3D); }
	static bool is_scripted_speech_playing(Any p0) { return _i<bool>(0xCC9AA18DCC7084F4, p0); }
	static bool is_stream_playing() { return _i<bool>(0xD11FA52EB849D978); }
	static bool _0x5DB8010EE71FDEF2(Vehicle vehicle) { return _i<bool>(0x5DB8010EE71FDEF2, vehicle); }
	static Any _0x0BE4BE946463F917(Any p0) { return _i<Any>(0x0BE4BE946463F917, p0); }
	static Void _0x651D3228960D08AF(Any p0, Any p1) { return _i<Void>(0x651D3228960D08AF, p0, p1); }
	static bool load_stream(const char* streamName, const char* soundSet) { return _i<bool>(0x1F1F957154EC51DF, streamName, soundSet); }
	static bool load_streawith_start_offset(const char* streamName, int startOffset, const char* soundSet) { return _i<bool>(0x59C16B79F53B3712, streamName, startOffset, soundSet); }
	static Void _0x75773E11BA459E90(Any p0, bool p1) { return _i<Void>(0x75773E11BA459E90, p0, p1); }
	static Void _0xD2CC78CD3D0B50F9(Any p0, bool p1) { return _i<Void>(0xD2CC78CD3D0B50F9, p0, p1); }
	static Void override_trevor_rage(Any* p0) { return _i<Void>(0x13AD665062541A7E, p0); }
	static Void override_underwater_stream(Any* p0, bool p1) { return _i<Void>(0xF2A9CDABCEA04BD6, p0, p1); }
	static Void override_veh_horn(Vehicle vehicle, bool mute, int p2) { return _i<Void>(0x3CDC1E622CCE0356, vehicle, mute, p2); }
	static Void pause_scripted_conversation(bool p0) { return _i<Void>(0x8530AD776CD72B12, p0); }
	static Void play_ambient_speech_at_coords(const char* p0, const char* p1, float p2, float p3, float p4, const char* p5) { return _i<Void>(0xED640017ED337E45, p0, p1, p2, p3, p4, p5); }
	static Void _0xEE066C7006C49C0A(Any p0, Any p1, Any* p2) { return _i<Void>(0xEE066C7006C49C0A, p0, p1, p2); }
	static Void _0xCADA5A0D0702381E(const char* p0, const char* soundset) { return _i<Void>(0xCADA5A0D0702381E, p0, soundset); }
	static Void play_end_credits_music(bool play) { return _i<Void>(0xCD536C4D33DCC900, play); }
	static Void play_mission_complete_audio(const char* audioName) { return _i<Void>(0xB138AAB8A70D3C69, audioName); }
	static Void play_pain(Ped ped, int painID, int p1, Any p3) { return _i<Void>(0xBC9AE166038A5CEC, ped, painID, p1, p3); }
	static Void play_ambient_speech2(Ped ped, const char* speechName, const char* speechParam, Any p3) { return _i<Void>(0xC6941B4A3A8FBBB9, ped, speechName, speechParam, p3); }
	static Void play_ambient_speech1(Ped ped, const char* speechName, const char* speechParam, Any p3) { return _i<Void>(0x8E04FEDD28D42462, ped, speechName, speechParam, p3); }
	static Void play_ambient_speech_with_voice(Ped p0, const char* speechName, const char* voiceName, const char* speechParam, bool p4) { return _i<Void>(0x3523634255FC3318, p0, speechName, voiceName, speechParam, p4); }
	static Void play_ped_ringtone(const char* ringtoneName, Ped ped, bool p2) { return _i<Void>(0xF9E56683CA8E11A5, ringtoneName, ped, p2); }
	static Any play_police_report(const char* name, float p1) { return _i<Any>(0xDFEBD56D9BD1EB16, name, p1); }
	static Void play_sound(Player soundId, const char* audioName, const char* audioRef, bool p3, Any p4, bool p5) { return _i<Void>(0x7FF4944CC209192D, soundId, audioName, audioRef, p3, p4, p5); }
	static Void play_sound_from_coord(int soundId, const char* audioName, float x, float y, float z, const char* audioRef, bool p6, int range, bool p8) { return _i<Void>(0x8D8686B622B88120, soundId, audioName, x, y, z, audioRef, p6, range, p8); }
	static Void play_sound_from_entity(int soundId, const char* audioName, Entity entity, const char* audioRef, bool p4, Any p5) { return _i<Void>(0xE65F427EB70AB1ED, soundId, audioName, entity, audioRef, p4, p5); }
	static Void _0x5B9853296731E88D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0x5B9853296731E88D, p0, p1, p2, p3, p4, p5); }
	static Void play_sound_frontend(int soundId, const char* audioName, const char* audioRef, bool p3) { return _i<Void>(0x67C540AA08E4A6F5, soundId, audioName, audioRef, p3); }
	static Void play_stream_from_object(Object object) { return _i<Void>(0xEBAA9B64D76356FD, object); }
	static Void play_stream_from_ped(Ped ped) { return _i<Void>(0x89049DD63C08B5D1, ped); }
	static Void play_stream_from_position(float x, float y, float z) { return _i<Void>(0x21442F412E8DE56B, x, y, z); }
	static Void play_stream_from_vehicle(Vehicle vehicle) { return _i<Void>(0xB70374A758007DFA, vehicle); }
	static Void play_stream_frontend() { return _i<Void>(0x58FCE43488F9F5F4); }
	static bool play_synchronized_audio_event(Any p0) { return _i<bool>(0x8B2FD4560E55DD2D, p0); }
	static Void play_vehicle_door_close_sound(Vehicle vehicle, int p1) { return _i<Void>(0x62A456AA4769EF34, vehicle, p1); }
	static Void play_vehicle_door_open_sound(Vehicle vehicle, int p1) { return _i<Void>(0x3A539D52857EA82D, vehicle, p1); }
	static Void preload_script_conversation(bool p0, bool p1, bool p2, bool p3) { return _i<Void>(0x3B3CAD6166916D87, p0, p1, p2, p3); }
	static Void preload_script_phone_conversation(bool p0, bool p1) { return _i<Void>(0x6004BCB0E226AAEA, p0, p1); }
	static Void _0xCA4CEA6AE0000A7E(Any p0) { return _i<Void>(0xCA4CEA6AE0000A7E, p0); }
	static bool prepare_alarm(const char* alarmName) { return _i<bool>(0x9D74AE343DB65533, alarmName); }
	static bool prepare_music_event(const char* eventName) { return _i<bool>(0x1E5185B72EF5158A, eventName); }
	static Any prepare_synchronized_audio_event(const char* p0, Any p1) { return _i<Any>(0xC7ABCACA4985A766, p0, p1); }
	static bool prepare_synchronized_audio_event_for_scene(Any p0, Any* p1) { return _i<bool>(0x029FE7CD1B7E2E75, p0, p1); }
	static Void _0xFBE20329593DEC9D(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xFBE20329593DEC9D, p0, p1, p2, p3); }
	static Void _0x5D2BFAAB8D956E0E() { return _i<Void>(0x5D2BFAAB8D956E0E); }
	static Void release_mission_audio_bank() { return _i<Void>(0x0EC92A1BF0857187); }
	static Void release_ambient_audio_bank() { return _i<Void>(0x65475A218FFAA93D); }
	static Void release_script_audio_bank() { return _i<Void>(0x7A2D8AD0A9EB9C3F); }
	static Void _0x19AF7ED9B9D23058() { return _i<Void>(0x19AF7ED9B9D23058); }
	static Void _0x9AC92EED5E4793AB() { return _i<Void>(0x9AC92EED5E4793AB); }
	static Void release_sound_id(int soundId) { return _i<Void>(0x353FC880830B88FA, soundId); }
	static Void _0xCE4AC0439F607045() { return _i<Void>(0xCE4AC0439F607045); }
	static Void _0x18EB48CFC41F2EA0(Any p0, float p1) { return _i<Void>(0x18EB48CFC41F2EA0, p0, p1); }
	static Void _0xB4BBFD9CD8B3922B(const char* p0) { return _i<Void>(0xB4BBFD9CD8B3922B, p0); }
	static bool request_mission_audio_bank(const char* p0, bool p1, Any p2) { return _i<bool>(0x7345BDD95E62E0F2, p0, p1, p2); }
	static bool request_ambient_audio_bank(const char* p0, bool p1, Any p2) { return _i<bool>(0xFE02FFBED8CA9D99, p0, p1, p2); }
	static bool request_script_audio_bank(const char* p0, bool p1, Any p2) { return _i<bool>(0x2F844A8B08D76685, p0, p1, p2); }
	static Void set_ped_talk(Ped ped) { return _i<Void>(0x4ADA3F19BE4A6047, ped); }
	static Void reset_ped_audio_flags(Any p0) { return _i<Void>(0xF54BB7B61036F335, p0); }
	static Void reset_trevor_rage() { return _i<Void>(0xE78503B10C4314E0); }
	static Void _0xD2DCCD8E16E20997(Any p0) { return _i<Void>(0xD2DCCD8E16E20997, p0); }
	static Void _0x70B8EC8FC108A634(bool p0, Any p1) { return _i<Void>(0x70B8EC8FC108A634, p0, p1); }
	static Void set_aggressive_horns(bool toggle) { return _i<Void>(0x395BF71085D1B1D9, toggle); }
	static Void set_ambient_voice_name(Ped ped, const char* name) { return _i<Void>(0x6C8065A3B780185B, ped, name); }
	static Void _0x9A53DED9921DE990(Any p0, Any p1) { return _i<Void>(0x9A53DED9921DE990, p0, p1); }
	static Void set_ambient_zone_list_state(Any* p0, bool p1, bool p2) { return _i<Void>(0x9748FA4DE50CCE3E, p0, p1, p2); }
	static Void set_ambient_zone_list_state_persistent(const char* ambientZone, bool p1, bool p2) { return _i<Void>(0xF3638DAE8C4045E1, ambientZone, p1, p2); }
	static Void set_ambient_zone_state(Any* p0, bool p1, bool p2) { return _i<Void>(0xBDA07E5950085E46, p0, p1, p2); }
	static Void set_ambient_zone_state_persistent(const char* ambientZone, bool p1, bool p2) { return _i<Void>(0x1D6650420CEC9D3B, ambientZone, p1, p2); }
	static Void set_animal_mood(Ped animal, int mood) { return _i<Void>(0xCC97B29285B1DC3B, animal, mood); }
	static Void set_audio_flag(const char* flagName, bool toggle) { return _i<Void>(0xB9EFD5C25018725A, flagName, toggle); }
	static Void set_audio_scene_variable(const char* scene, const char* variable, float value) { return _i<Void>(0xEF21A9EF089A2668, scene, variable, value); }
	static Void _0xA5F377B175A699C5(Any p0) { return _i<Void>(0xA5F377B175A699C5, p0); }
	static Void _0x12561FCBB62D5B9C(int p0) { return _i<Void>(0x12561FCBB62D5B9C, p0); }
	static Void set_audio_vehicle_priority(Vehicle vehicle, Any p1) { return _i<Void>(0xE5564483E407F914, vehicle, p1); }
	static Void _0x0B568201DD99F0EB(bool p0) { return _i<Void>(0x0B568201DD99F0EB, p0); }
	static Void _0x61631F5DF50D1C34(bool p0) { return _i<Void>(0x61631F5DF50D1C34, p0); }
	static Void _0x4E404A9361F75BB2(const char* radioStation, const char* p1, bool p2) { return _i<Void>(0x4E404A9361F75BB2, radioStation, p1, p2); }
	static Void set_cutscene_audio_override(const char* p0) { return _i<Void>(0x3B4BF5F0859204D9, p0); }
	static Void set_emitter_radio_station(const char* emitterName, const char* radioStation) { return _i<Void>(0xACF57305B12AF907, emitterName, radioStation); }
	static Void _0x892B6AB8F33606F5(Any p0, Any p1) { return _i<Void>(0x892B6AB8F33606F5, p0, p1); }
	static Void set_frontend_radio_active(bool active) { return _i<Void>(0xF7F26C6E9CC9EBB8, active); }
	static Void _0x159B7318403A1CD8(Any p0) { return _i<Void>(0x159B7318403A1CD8, p0); }
	static Void set_gps_active(bool active) { return _i<Void>(0x3BD3F52BA9B1E4E8, active); }
	static Void set_horn_enabled(Vehicle vehicle, bool toggle) { return _i<Void>(0x76D683C108594D0E, vehicle, toggle); }
	static Void sound_vehicle_horn_this_frame(Vehicle vehicle) { return _i<Void>(0x9C11908013EA4715, vehicle); }
	static Void _0x9D3AF56E94C9AE98(Any p0, float p1) { return _i<Void>(0x9D3AF56E94C9AE98, p0, p1); }
	static Void set_initial_player_station(const char* radioStation) { return _i<Void>(0x88795F13FACDA88D, radioStation); }
	static Void set_microphone_position(bool p0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) { return _i<Void>(0xB6AE90EDDE95C762, p0, x1, y1, z1, x2, y2, z2, x3, y3, z3); }
	static Void set_mobile_phone_radio_state(bool state) { return _i<Void>(0xBF286C554784F3DF, state); }
	static Void set_mobile_radio_enabled_during_gameplay(bool Toggle) { return _i<Void>(0x1098355A16064BB3, Toggle); }
	static Void _0xB542DE8C3D1CB210(bool p0) { return _i<Void>(0xB542DE8C3D1CB210, p0); }
	static Void _0xA5342D390CDA41D6(Any p0, bool p1) { return _i<Void>(0xA5342D390CDA41D6, p0, p1); }
	static Void _0x8BF907833BE275DE(float p0, float p1) { return _i<Void>(0x8BF907833BE275DE, p0, p1); }
	static Void set_ped_is_drunk(Ped ped, bool toggle) { return _i<Void>(0x95D2D383D5396B8A, ped, toggle); }
	static Void _0x1B7ABE26CBCBF8C7(Any p0, Any p1, Any p2) { return _i<Void>(0x1B7ABE26CBCBF8C7, p0, p1, p2); }
	static Void set_ped_scream(Ped ped) { return _i<Void>(0x40CF0D12D142A9E8, ped); }
	static Void _0x7CDC8C3B89F661B3(Ped playerPed, uint32_t p1) { return _i<Void>(0x7CDC8C3B89F661B3, playerPed, p1); }
	static Void _0x149AEE66F0CB3A99(float p0, float p1) { return _i<Void>(0x149AEE66F0CB3A99, p0, p1); }
	static Void set_player_angry(Ped playerPed, bool disabled) { return _i<Void>(0xEA241BB04110F091, playerPed, disabled); }
	static Void _0x6FDDAD856E36988A(Any p0, bool p1) { return _i<Void>(0x6FDDAD856E36988A, p0, p1); }
	static Void _0x044DBAD7A7FA2BE5(const char* p0, const char* p1) { return _i<Void>(0x044DBAD7A7FA2BE5, p0, p1); }
	static Void _0xDA07819E452FFE8F(Any p0) { return _i<Void>(0xDA07819E452FFE8F, p0); }
	static Void _0x33E3C6C6F2F0B506(Any p0, float p1, float p2, float p3) { return _i<Void>(0x33E3C6C6F2F0B506, p0, p1, p2, p3); }
	static Void set_radio_auto_unfreeze(bool toggle) { return _i<Void>(0xC1AA9F53CE982990, toggle); }
	static Void _0x2C96CDB04FCA358E(float p0) { return _i<Void>(0x2C96CDB04FCA358E, p0); }
	static Void _0xDD6BCF9E94425DF9() { return _i<Void>(0xDD6BCF9E94425DF9); }
	static Void _0xFF266D1D0EB1195D() { return _i<Void>(0xFF266D1D0EB1195D); }
	static Void _0x774BD811F656A122(const char* radioStation, bool p1) { return _i<Void>(0x774BD811F656A122, radioStation, p1); }
	static Void set_radio_to_station_index(int radioStation) { return _i<Void>(0xA619B168B8A8570F, radioStation); }
	static Void set_radio_to_station_name(const char* stationName) { return _i<Void>(0xC69EDA28699D5107, stationName); }
	static Void set_radio_track(const char* radioStation, const char* radioTrack) { return _i<Void>(0xB39786F201FEE30B, radioStation, radioTrack); }
	static Void _0x06C0023BED16DD6B(Any p0, bool p1) { return _i<Void>(0x06C0023BED16DD6B, p0, p1); }
	static Void _0x43FA0DFC5DF87815(Vehicle vehicle, bool p1) { return _i<Void>(0x43FA0DFC5DF87815, vehicle, p1); }
	static Void set_siren_with_no_driver(Vehicle vehicle, bool toggle) { return _i<Void>(0x1FEF0683B96EBCF2, vehicle, toggle); }
	static Void _0xBEF34B1D9624D5DD(bool p0) { return _i<Void>(0xBEF34B1D9624D5DD, p0); }
	static Void set_static_emitter_enabled(const char* emitterName, bool toggle) { return _i<Void>(0x399D2D3B33F1B8EB, emitterName, toggle); }
	static Void set_user_radio_control_enabled(bool toggle) { return _i<Void>(0x19F21E63AE6EAE4E, toggle); }
	static Void set_variable_on_sound(int soundId, Any* p1, float p2) { return _i<Void>(0xAD6B3148A78AE9B6, soundId, p1, p2); }
	static Void set_variable_on_stream(const char* p0, float p1) { return _i<Void>(0x2F9D3834AEB9EF79, p0, p1); }
	static Void get_player_headset_sound_alternate(const char* p0, float p1) { return _i<Void>(0xBCC29F935ED07688, p0, p1); }
	static Void _0x733ADF241531E5C2(const char* name, float p1) { return _i<Void>(0x733ADF241531E5C2, name, p1); }
	static Void _0x01BB4D577D38BD9E(Any p0, float p1) { return _i<Void>(0x01BB4D577D38BD9E, p0, p1); }
	static Void _0x59E7B488451F4D3A(Any p0, float p1) { return _i<Void>(0x59E7B488451F4D3A, p0, p1); }
	static Void set_vehicle_boost_active(Vehicle vehicle, bool Toggle) { return _i<Void>(0x4A04DE7CAB2739A1, vehicle, Toggle); }
	static Void _0x58BB377BEC7CD5F4(bool p0, bool p1) { return _i<Void>(0x58BB377BEC7CD5F4, p0, p1); }
	static Void _0xF3365489E0DD50F9(Any p0, bool p1) { return _i<Void>(0xF3365489E0DD50F9, p0, p1); }
	static Void set_vehicle_radio_enabled(Vehicle vehicle, bool toggle) { return _i<Void>(0x3B988190C0AA6C0B, vehicle, toggle); }
	static Void set_vehicle_radio_loud(Vehicle vehicle, bool toggle) { return _i<Void>(0xBB6F1CAEC68B0BCE, vehicle, toggle); }
	static Void _0xF1F8157B8C3F171C(Any p0, const char* p1, const char* p2) { return _i<Void>(0xF1F8157B8C3F171C, p0, p1, p2); }
	static Void _0xC1805D05E6D4FE10(Vehicle vehicle) { return _i<Void>(0xC1805D05E6D4FE10, vehicle); }
	static Void set_vehicle_radio_station(Vehicle vehicle, const char* radioStation) { return _i<Void>(0x1B9C0099CB942AC6, vehicle, radioStation); }
	static Void skip_radio_forward() { return _i<Void>(0x6DDBBDD98E2E9C25); }
	static Void skip_to_next_scripted_conversation_line() { return _i<Void>(0x9663FE6B7A61EB00); }
	static Void start_alarm(const char* alarmName, bool p2) { return _i<Void>(0x0355EF116C4C97B2, alarmName, p2); }
	static bool start_audio_scene(const char* scene) { return _i<bool>(0x013A80FC08F6E4F2, scene); }
	static Void start_preloaded_conversation() { return _i<Void>(0x23641AFE870AF385); }
	static Void restart_scripted_conversation() { return _i<Void>(0x9AEB285D1818C9AC); }
	static Void start_script_conversation(bool p0, bool p1, bool p2, bool p3) { return _i<Void>(0x6B17C62C9635D2DC, p0, p1, p2, p3); }
	static Void start_script_phone_conversation(bool p0, bool p1) { return _i<Void>(0x252E5F915EABB675, p0, p1); }
	static Void stop_alarm(const char* alarmName, bool toggle) { return _i<Void>(0xA1CADDCD98415A41, alarmName, toggle); }
	static Void stop_all_alarms(bool stop) { return _i<Void>(0x2F794A877ADD4C92, stop); }
	static Void stop_audio_scene(const char* scene) { return _i<Void>(0xDFE8422B3B94E688, scene); }
	static Void stop_audio_scenes() { return _i<Void>(0xBAC7FC81A75EC1A1); }
	static Void stop_current_playing_ambient_speech(Ped ped) { return _i<Void>(0xB8BEC0CA6F0EDB0F, ped); }
	static Void set_ped_mute(Ped ped) { return _i<Void>(0x7A73D05A607734C7, ped); }
	static Void _0x806058BBDC136E06() { return _i<Void>(0x806058BBDC136E06); }
	static Void stop_ped_ringtone(Ped ped) { return _i<Void>(0x6C5AE23EFA885092, ped); }
	static Void stop_ped_speaking(Ped ped, bool shaking) { return _i<Void>(0x9D64D7405520E3D3, ped, shaking); }
	static Any stop_scripted_conversation(bool p0) { return _i<Any>(0xD79DEEFB53455EBA, p0); }
	static Void _0xE4E6DD5566D28C82() { return _i<Void>(0xE4E6DD5566D28C82); }
	static Void stop_sound(int soundId) { return _i<Void>(0xA3B0C41BA5CC0BB5, soundId); }
	static bool stop_synchronized_audio_event(Any p0) { return _i<bool>(0x92D6A88E64A94430, p0); }
	static bool trigger_music_event(const char* eventName) { return _i<bool>(0x706D57B0F50DA710, eventName); }
	static Void unfreeze_radio_station(const char* radioStation) { return _i<Void>(0xFC00454CF60B91DD, radioStation); }
	static Void release_named_script_audio_bank(const char* audioBank) { return _i<Void>(0x77ED170667F50170, audioBank); }
	static Void _0x11579D940949C49E(Any p0) { return _i<Void>(0x11579D940949C49E, p0); }
	static Void unlock_mission_news_story(int newsStory) { return _i<Void>(0xB165AB7C248B2DC1, newsStory); }
	static Void _0x031ACB6ABA18C729(const char* radioStation, const char* p1) { return _i<Void>(0x031ACB6ABA18C729, radioStation, p1); }
	static Void _0x0150B6FF25A9E2E5() { return _i<Void>(0x0150B6FF25A9E2E5); }
	static Void _0x7EC3C679D0E7E46B(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x7EC3C679D0E7E46B, p0, p1, p2, p3); }
	static Void _0xBF4DC1784BE94DFA(Any p0, bool p1, Any p2) { return _i<Void>(0xBF4DC1784BE94DFA, p0, p1, p2); }
	static Void use_siren_as_horn(Vehicle vehicle, bool toggle) { return _i<Void>(0xFA932DE350266EF8, vehicle, toggle); }
	static Void register_script_with_audio(Any p0) { return _i<Void>(0xC6ED9D5092438D91, p0); }
	static Void unregister_script_with_audio() { return _i<Void>(0xA8638BE228D4751A); }
	static Void _0x02E93C796ABD3A97(bool p0) { return _i<Void>(0x02E93C796ABD3A97, p0); }

	static Void reset_exclusive_scenario_group() { return _i<Void>(0x4202BBCB8684563D); }
	static bool is_ped_being_arrested(Ped ped) { return _i<bool>(0x90A09F3A45FED688, ped); }
	static Void add_cover_blocking_area(float playerX, float playerY, float playerZ, float radiusX, float radiusY, float radiusZ, bool p6, bool p7, bool p8, bool p9) { return _i<Void>(0x45C597097DD7CB81, playerX, playerY, playerZ, radiusX, radiusY, radiusZ, p6, p7, p8, p9); }
	static ScrHandle add_cover_point(float p0, float p1, float p2, float p3, Any p4, Any p5, Any p6, bool p7) { return _i<ScrHandle>(0xD5C12A75C7B9497F, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void add_patrol_route_link(Any p0, Any p1) { return _i<Void>(0x23083260DEC3A551, p0, p1); }
	static Void add_patrol_route_node(int p0, const char* p1, float x1, float y1, float z1, float x2, float y2, float z2, int p8) { return _i<Void>(0x8EDF950167586B7C, p0, p1, x1, y1, z1, x2, y2, z2, p8); }
	static Void add_vehicle_subtask_attack_coord(Ped ped, float x, float y, float z) { return _i<Void>(0x5CF0D8F9BBA0DD75, ped, x, y, z); }
	static Void add_vehicle_subtask_attack_ped(Ped ped, Ped ped2) { return _i<Void>(0x85F462BADC7DA47F, ped, ped2); }
	static bool assisted_movement_is_route_loaded(const char* route) { return _i<bool>(0x60F9A4393A21F741, route); }
	static Void assisted_movement_override_load_distance_this_frame(float dist) { return _i<Void>(0x13945951E16EF912, dist); }
	static Void assisted_movement_remove_route(const char* route) { return _i<Void>(0x3548536485DD792B, route); }
	static Void assisted_movement_request_route(const char* route) { return _i<Void>(0x817268968605947A, route); }
	static Void assisted_movement_set_route_properties(const char* route, int props) { return _i<Void>(0xD5002D78B7162E1B, route, props); }
	static Void clear_driveby_task_underneath_driving_task(Ped ped) { return _i<Void>(0xC35B5CDB2824CF69, ped); }
	static Void clear_ped_secondary_task(Ped ped) { return _i<Void>(0x176CECF6F920D707, ped); }
	static Void clear_ped_tasks(Ped ped) { return _i<Void>(0xE1EF3C1216AFF2CD, ped); }
	static Void clear_ped_tasks_immediately(Ped ped) { return _i<Void>(0xAAA34F8A7CB32098, ped); }
	static Void clear_sequence_task(Object* taskSequence) { return _i<Void>(0x3841422E9C488D8C, taskSequence); }
	static Void close_patrol_route() { return _i<Void>(0xB043ECA801B8CBC1); }
	static Void close_sequence_task(Object taskSequence) { return _i<Void>(0x39E72BC99E6360CB, taskSequence); }
	static bool control_mounted_weapon(Ped ped) { return _i<bool>(0xDCFE42068FE0135A, ped); }
	static Void create_patrol_route() { return _i<Void>(0xAF8A443CCC8018DC); }
	static Void delete_patrol_route(const char* patrolRoute) { return _i<Void>(0x7767DD9D65E91319, patrolRoute); }
	static bool does_scenario_exist_in_area(float x, float y, float z, float radius, bool b) { return _i<bool>(0x5A59271FFADD33C1, x, y, z, radius, b); }
	static bool does_scenario_group_exist(const char* scenarioGroup) { return _i<bool>(0xF9034C136C9E00D3, scenarioGroup); }
	static bool does_scenario_of_type_exist_in_area(float p0, float p1, float p2, Any* p3, float p4, bool p5) { return _i<bool>(0x0A9D0C2A3BBC86C1, p0, p1, p2, p3, p4, p5); }
	static bool does_scripted_cover_point_exist_at_coords(float x, float y, float z) { return _i<bool>(0xA98B8E3C088E5A31, x, y, z); }
	static int get_active_vehicle_mission_type(Vehicle veh) { return _i<int>(0x534AEBA6E5ED4CAB, veh); }
	static const char* get_clip_set_for_scripted_gun_task(int p0) { return _i<const char*>(0x3A8CADC7D37AACC5, p0); }
	static bool get_is_task_active(Ped ped, int taskNumber) { return _i<bool>(0xB0760331C7AA4155, ped, taskNumber); }
	static bool get_is_waypoint_recording_loaded(const char* name) { return _i<bool>(0xCB4E8BE8A0063C5D, name); }
	static Any get_navmesh_route_distance_remaining(Ped ped, Any* p1, Any* p2) { return _i<Any>(0xC6F5C0BCDC74D62D, ped, p1, p2); }
	static int get_navmesh_route_result(Ped ped) { return _i<int>(0x632E831F382A0FA8, ped); }
	static float get_ped_desired_move_blend_ratio(Ped ped) { return _i<float>(0x8517D4A6CA8513ED, ped); }
	static float get_ped_waypoint_distance(Any p0) { return _i<float>(0xE6A877C64CAF1BC5, p0); }
	static Any get_ped_waypoint_progress(Any p0) { return _i<Any>(0x2720AAA75001E094, p0); }
	static float get_phone_gesture_anim_current_time(Ped ped) { return _i<float>(0x47619ABE8B268C60, ped); }
	static float get_phone_gesture_anim_total_time(Ped ped) { return _i<float>(0x1EE0F68A7C25DEC6, ped); }
	static math::vector3<float> get_scripted_cover_point_coords(ScrHandle coverpoint) { return _i<math::vector3<float>>(0x594A1028FC2A3E85, coverpoint); }
	static int get_script_task_status(Ped targetPed, uint32_t taskHash) { return _i<int>(0x77F1BEB8863288D5, targetPed, taskHash); }
	static int get_sequence_progress(Ped ped) { return _i<int>(0x00A9010CFE1E3533, ped); }
	static bool _0xB4F47213DF45A64C(Any p0, Any* p1) { return _i<bool>(0xB4F47213DF45A64C, p0, p1); }
	static bool _0xA7FFBA498E4AAF67(Any p0, const char* p1) { return _i<bool>(0xA7FFBA498E4AAF67, p0, p1); }
	static const char* _0x717E4D1F2048376D(Ped ped) { return _i<const char*>(0x717E4D1F2048376D, ped); }
	static Any get_vehicle_waypoint_progress(Any p0) { return _i<Any>(0x9824CFF8FC66E159, p0); }
	static Any get_vehicle_waypoint_target_point(Any p0) { return _i<Any>(0x416B62AC8B9E5BBD, p0); }
	static float get_waypoint_distance_along_route(const char* p0, int p1) { return _i<float>(0xA5B769058763E497, p0, p1); }
	static bool _0x3E38E28A1D80DDF6(Ped ped) { return _i<bool>(0x3E38E28A1D80DDF6, ped); }
	static bool is_driveby_task_underneath_driving_task(Ped ped) { return _i<bool>(0x8785E6E40C7A8818, ped); }
	static bool is_mounted_weapon_task_underneath_driving_task(Ped ped) { return _i<bool>(0xA320EF046186FA3B, ped); }
	static bool is_move_blend_ratio_running(Ped ped) { return _i<bool>(0xD4D8636C0199A939, ped); }
	static bool is_move_blend_ratio_sprinting(Ped ped) { return _i<bool>(0x24A2AD74FA9814E2, ped); }
	static bool is_move_blend_ratio_still(Ped ped) { return _i<bool>(0x349CE7B56DAFD95C, ped); }
	static bool is_move_blend_ratio_walking(Ped ped) { return _i<bool>(0xF133BBBE91E1691F, ped); }
	static bool is_ped_active_in_scenario(Ped ped) { return _i<bool>(0xAA135F9482C82CC3, ped); }
	static bool is_ped_cuffed(Ped ped) { return _i<bool>(0x74E559B3BC910685, ped); }
	static bool is_ped_getting_up(Ped ped) { return _i<bool>(0x2A74E1D5F2F00EEC, ped); }
	static bool is_ped_in_writhe(Ped ped) { return _i<bool>(0xDEB6D52126E7D640, ped); }
	static bool _0x621C6E4729388E41(Ped ped) { return _i<bool>(0x621C6E4729388E41, ped); }
	static bool is_ped_running(Ped ped) { return _i<bool>(0xC5286FFC176F28A2, ped); }
	static bool is_ped_running_arrest_task(Ped ped) { return _i<bool>(0x3DC52677769B4AE0, ped); }
	static bool is_ped_sprinting(Ped ped) { return _i<bool>(0x57E457CD2C0FC168, ped); }
	static bool is_ped_still(Ped ped) { return _i<bool>(0xAC29253EEF8F0180, ped); }
	static bool is_ped_strafing(Ped ped) { return _i<bool>(0xE45B7F222DE47E09, ped); }
	static bool is_ped_walking(Ped ped) { return _i<bool>(0xDE4C184B2B9B071A, ped); }
	static bool is_playing_phone_gesture_anim(Ped ped) { return _i<bool>(0xB8EBB1E9D3588C10, ped); }
	static bool is_scenario_group_enabled(const char* scenarioGroup) { return _i<bool>(0x367A09DED4E05B99, scenarioGroup); }
	static bool is_scenario_occupied(float p0, float p1, float p2, float p3, bool p4) { return _i<bool>(0x788756D73AC2E07C, p0, p1, p2, p3, p4); }
	static bool is_scenario_type_enabled(const char* scenarioType) { return _i<bool>(0x3A815DB3EA088722, scenarioType); }
	static bool _0x921CE12C489C4C41(int PlayerID) { return _i<bool>(0x921CE12C489C4C41, PlayerID); }
	static bool _0x30ED88D5E0C56A37(Any p0) { return _i<bool>(0x30ED88D5E0C56A37, p0); }
	static bool is_waypoint_playback_going_on_for_ped(Any p0) { return _i<bool>(0xE03B3F2D3DC59B64, p0); }
	static bool is_waypoint_playback_going_on_for_vehicle(Any p0) { return _i<bool>(0xF5134943EA29868C, p0); }
	static Void open_patrol_route(const char* patrolRoute) { return _i<Void>(0xA36BFB5EE89F3D82, patrolRoute); }
	static Void open_sequence_task(Object* taskSequence) { return _i<Void>(0xE8854A4326B9E12B, taskSequence); }
	static bool ped_has_use_scenario_task(Ped ped) { return _i<bool>(0x295E3CCEC879CCD7, ped); }
	static Void play_anim_on_running_scenario(Ped ped, const char* animDict, const char* animName) { return _i<Void>(0x748040460F8DF5DC, ped, animDict, animName); }
	static Void play_entity_scripted_anim(Any p0, Any* p1, Any* p2, Any* p3, float p4, float p5) { return _i<Void>(0x77A1EEC547E7FCF1, p0, p1, p2, p3, p4, p5); }
	static Void remove_all_cover_blocking_areas() { return _i<Void>(0xDB6708C0B46F56D8); }
	static Void remove_cover_point(ScrHandle coverpoint) { return _i<Void>(0xAE287C923D891715, coverpoint); }
	static Void _0x1F351CF1C6475734(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Void>(0x1F351CF1C6475734, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void remove_waypoint_recording(const char* name) { return _i<Void>(0xFF1B8B4AA1C25DC8, name); }
	static Any _0xD01015C7316AE176(Ped ped, const char* p1) { return _i<Any>(0xD01015C7316AE176, ped, p1); }
	static Void request_waypoint_recording(const char* name) { return _i<Void>(0x9EEFB62EB27B5792, name); }
	static Void reset_scenario_groups_enabled() { return _i<Void>(0xDD902D0349AFAD3A); }
	static Void reset_scenario_types_enabled() { return _i<Void>(0x0D40EE2A7F2B2D6D); }
	static Void set_anim_looped(Any p0, bool p1, Any p2, bool p3) { return _i<Void>(0x70033C3CC29A1FF4, p0, p1, p2, p3); }
	static Void set_anim_rate(Ped p0, float p1, float p2, float p3) { return _i<Void>(0x032D49C5E359C847, p0, p1, p2, p3); }
	static Void set_aniweight(Any p0, float p1, Any p2, Any p3, bool p4) { return _i<Void>(0x207F1A47C0342F48, p0, p1, p2, p3, p4); }
	static Void set_driveby_task_target(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z) { return _i<Void>(0xE5B302114D8162EE, shootingPed, targetPed, targetVehicle, x, y, z); }
	static Void set_drive_task_cruise_speed(Ped driver, float cruiseSpeed) { return _i<Void>(0x5C9B84BD7D31D908, driver, cruiseSpeed); }
	static Void set_drive_task_driving_style(Ped ped, int drivingStyle) { return _i<Void>(0xDACE1BE37D88AF67, ped, drivingStyle); }
	static Void set_drive_task_max_cruise_speed(Any p0, float p1) { return _i<Void>(0x404A5AA9B9F0B746, p0, p1); }
	static Void set_exclusive_scenario_group(const char* scenarioGroup) { return _i<Void>(0x535E97E1F7FC0C6A, scenarioGroup); }
	static Any _0xAB13A5565480B6D9(Any p0, Any p1) { return _i<Any>(0xAB13A5565480B6D9, p0, p1); }
	static Void set_global_min_bird_flight_height(float height) { return _i<Void>(0x6C6B148586F934F7, height); }
	static Void set_high_fall_task(Ped ped, Any p1, Any p2, Any p3) { return _i<Void>(0x8C825BDC7741D37C, ped, p1, p2, p3); }
	static Void set_mounted_weapon_target(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z, Any p6) { return _i<Void>(0xCCD892192C6D2BB9, shootingPed, targetPed, targetVehicle, x, y, z, p6); }
	static Void set_parachute_task_target(Ped ped, float x, float y, float z) { return _i<Void>(0xC313379AF0FCEDA7, ped, x, y, z); }
	static Void set_parachute_task_thrust(Ped ped, float thrust) { return _i<Void>(0x0729BAC1B8C64317, ped, thrust); }
	static Void _0x8FD89A6240813FD0(Ped ped, bool p1, bool p2) { return _i<Void>(0x8FD89A6240813FD0, ped, p1, p2); }
	static Void set_ped_desired_move_blend_ratio(Ped ped, float p1) { return _i<Void>(0x1E982AC8716912C5, ped, p1); }
	static Void set_ped_path_avoid_fire(Ped ped, bool avoidFire) { return _i<Void>(0x4455517B28441E60, ped, avoidFire); }
	static Void set_ped_path_can_drop_from_height(Ped ped, bool Toggle) { return _i<Void>(0xE361C5C71C431A4F, ped, Toggle); }
	static Void set_ped_path_can_use_climbovers(Ped ped, bool Toggle) { return _i<Void>(0x8E06A6FE76C9EFF4, ped, Toggle); }
	static Void set_ped_path_can_use_ladders(Ped ped, bool Toggle) { return _i<Void>(0x77A5B103C87F476E, ped, Toggle); }
	static Void _0x88E32DB8C1A4AA4B(Ped ped, float p1) { return _i<Void>(0x88E32DB8C1A4AA4B, ped, p1); }
	static Void set_ped_path_may_enter_water(Ped ped, bool mayEnterWater) { return _i<Void>(0xF35425A4204367EC, ped, mayEnterWater); }
	static Void set_ped_path_prefer_to_avoid_water(Ped ped, bool avoidWater) { return _i<Void>(0x38FE1EC73743793C, ped, avoidWater); }
	static Any set_ped_waypoint_route_offset(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xED98E10B0AFCE4B4, p0, p1, p2, p3); }
	static Void set_scenario_group_enabled(const char* scenarioGroup, bool p1) { return _i<Void>(0x02C8E5B49848664E, scenarioGroup, p1); }
	static Void set_scenario_type_enabled(const char* scenarioType, bool toggle) { return _i<Void>(0xEB47EC4E34FB7EE1, scenarioType, toggle); }
	static Void set_sequence_to_repeat(Object taskSequence, bool repeat) { return _i<Void>(0x58C70CF3A41E4AE7, taskSequence, repeat); }
	static Void _0xB0A6CFD2C69C1088(Ped p0, Any* p1, bool p2) { return _i<Void>(0xB0A6CFD2C69C1088, p0, p1, p2); }
	static Void _0xD5BB4025AE449A4E(Ped p0, const char* p1, float p2) { return _i<Void>(0xD5BB4025AE449A4E, p0, p1, p2); }
	static Void set_task_vehicle_chase_behavior_flag(Ped ped, int flag, bool set) { return _i<Void>(0xCC665AAC360D31E7, ped, flag, set); }
	static Void set_task_vehicle_chase_ideal_pursuit_distance(Ped ped, float distance) { return _i<Void>(0x639B642FACBE4EDD, ped, distance); }
	static Void stop_anim_playback(Ped ped, Any p1, bool p2) { return _i<Void>(0xEE08C992D238C5D1, ped, p1, p2); }
	static Void stop_anim_task(Ped ped, const char* animDictionary, const char* animationName, float p3) { return _i<Void>(0x97FF36A1D40EA00A, ped, animDictionary, animationName, p3); }
	static Void task_achieve_heading(Ped ped, float heading, int timeout) { return _i<Void>(0x93B93A37987F1F3D, ped, heading, timeout); }
	static Void _0x19D1B791CB3670FE(Any p0, Any p1) { return _i<Void>(0x19D1B791CB3670FE, p0, p1); }
	static Void task_aim_gun_at_coord(Ped ped, float x, float y, float z, int time, bool p5, bool p6) { return _i<Void>(0x6671F3EEC681BDA1, ped, x, y, z, time, p5, p6); }
	static Void task_aim_gun_at_entity(Ped ped, Entity entity, int duration, bool p3) { return _i<Void>(0x9B53BB6E8943AF53, ped, entity, duration, p3); }
	static Void task_aim_gun_scripted(Ped ped, uint32_t scriptTask, bool p2, bool p3) { return _i<Void>(0x7A192BE16D373D00, ped, scriptTask, p2, p3); }
	static Void task_aim_gun_scripted_with_target(Any p0, Any p1, float p2, float p3, float p4, Any p5, bool p6, bool p7) { return _i<Void>(0x8605AF0DE8B3A5AC, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void task_arrest_ped(Ped ped, Ped target) { return _i<Void>(0xF3B9A78A178572B1, ped, target); }
	static Void task_boat_mission(Ped pedDriver, Vehicle boat, Any p2, Any p3, float x, float y, float z, Any p7, float maxSpeed, int drivingStyle, float p10, Any p11) { return _i<Void>(0x15C86013127CE63F, pedDriver, boat, p2, p3, x, y, z, p7, maxSpeed, drivingStyle, p10, p11); }
	static Void task_chat_to_ped(Ped ped, Ped target, Any p2, float p3, float p4, float p5, float p6, float p7) { return _i<Void>(0x8C338E0263E4FD19, ped, target, p2, p3, p4, p5, p6, p7); }
	static Void task_clear_defensive_area(Any p0) { return _i<Void>(0x95A6C46A31D1917D, p0); }
	static Void task_clear_look_at(Ped ped) { return _i<Void>(0x0F804F1DB19B9689, ped); }
	static Void task_climb(Ped ped, bool unused) { return _i<Void>(0x89D9FCC2435112F1, ped, unused); }
	static Void task_climb_ladder(Ped ped, int p1) { return _i<Void>(0xB6C987F9285A3814, ped, p1); }
	static Void task_combat_hated_targets_around_ped(Ped ped, float radius, int p2) { return _i<Void>(0x7BF835BB9E2698C8, ped, radius, p2); }
	static Void task_combat_hated_targets_around_ped_timed(Any p0, float p1, Any p2, Any p3) { return _i<Void>(0x2BBA30B854534A0C, p0, p1, p2, p3); }
	static Void task_combat_hated_targets_in_area(Ped ped, float x, float y, float z, float radius, Any p5) { return _i<Void>(0x4CF5F55DAC3280A0, ped, x, y, z, radius, p5); }
	static Void task_combat_ped(Ped ped, Ped targetPed, int p2, int p3) { return _i<Void>(0xF166E48407BAC484, ped, targetPed, p2, p3); }
	static Void task_combat_ped_timed(Any p0, Ped ped, int p2, Any p3) { return _i<Void>(0x944F30DCB7096BDE, p0, ped, p2, p3); }
	static Void task_cower(Ped ped, int duration) { return _i<Void>(0x3EB1FE9E8E908E15, ped, duration); }
	static Void task_drive_by(Ped driverPed, Ped targetPed, Vehicle targetVehicle, float targetX, float targetY, float targetZ, float distanceToShoot, int pedAccuracy, bool p8, uint32_t firingPattern) { return _i<Void>(0x2F8AF0E82773A171, driverPed, targetPed, targetVehicle, targetX, targetY, targetZ, distanceToShoot, pedAccuracy, p8, firingPattern); }
	static Void task_enter_vehicle(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int p5, Any p6) { return _i<Void>(0xC20E50AA46D09CA8, ped, vehicle, timeout, seat, speed, p5, p6); }
	static Void task_everyone_leave_vehicle(Vehicle vehicle) { return _i<Void>(0x7F93691AB4B92272, vehicle); }
	static Void task_exit_cover(Any p0, Any p1, float p2, float p3, float p4) { return _i<Void>(0x79B258E397854D29, p0, p1, p2, p3, p4); }
	static Void task_extend_route(float x, float y, float z) { return _i<Void>(0x1E7889778264843A, x, y, z); }
	static Void task_flush_route() { return _i<Void>(0x841142A1376E9006); }
	static Void task_follow_nav_mesh_to_coord(Ped ped, float x, float y, float z, float speed, int timeout, float stoppingRange, bool persistFollowing, float unk) { return _i<Void>(0x15D3A79D4E44B913, ped, x, y, z, speed, timeout, stoppingRange, persistFollowing, unk); }
	static Void task_follow_point_route(Ped ped, float speed, int unknown) { return _i<Void>(0x595583281858626E, ped, speed, unknown); }
	static Void task_follow_to_offset_of_entity(Ped ped, Entity entity, float offsetX, float offsetY, float offsetZ, float movementSpeed, int timeout, float stoppingRange, bool persistFollowing) { return _i<Void>(0x304AE42E357B8C7E, ped, entity, offsetX, offsetY, offsetZ, movementSpeed, timeout, stoppingRange, persistFollowing); }
	static Void task_follow_waypoint_recording(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x0759591819534F7B, p0, p1, p2, p3, p4); }
	static Void task_force_motion_state(Ped ped, uint32_t state, bool p2) { return _i<Void>(0x4F056E1AFFEF17AB, ped, state, p2); }
	static Void task_get_off_boat(Ped ped, Vehicle boat) { return _i<Void>(0x9C00E77AF14B2DFF, ped, boat); }
	static Void task_goto_entity_aiming(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist) { return _i<Void>(0xA9DA48FAB8A76C12, ped, target, distanceToStopAt, StartAimingDist); }
	static Void task_goto_entity_offset(Ped ped, Any p1, Any p2, float x, float y, float z, int duration) { return _i<Void>(0xE39B4FF4FDEBDE27, ped, p1, p2, x, y, z, duration); }
	static Void task_goto_entity_offset_xy(Any p0, Any p1, Any p2, float p3, float p4, float p5, float p6, Any p7) { return _i<Void>(0x338E7EF52B6095A9, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void task_go_straight_to_coord(Ped ped, float x, float y, float z, float speed, int timeout, float targetHeading, float distanceToSlide) { return _i<Void>(0xD76B57B44F1E6F8B, ped, x, y, z, speed, timeout, targetHeading, distanceToSlide); }
	static Void task_go_straight_to_coord_relative_to_entity(Entity entity1, Entity entity2, float p2, float p3, float p4, float p5, Any p6) { return _i<Void>(0x61E360B7E040D12E, entity1, entity2, p2, p3, p4, p5, p6); }
	static Void task_go_to_coord_and_aim_at_hated_entities_near_coord(Ped pedHandle, float goToLocationX, float goToLocationY, float goToLocationZ, float focusLocationX, float focusLocationY, float focusLocationZ, float speed, bool shootAtEnemies, float distanceToStopAt, float noRoadsDistance, bool unkTrue, int unkFlag, int aimingFlag, uint32_t firingPattern) { return _i<Void>(0xA55547801EB331FC, pedHandle, goToLocationX, goToLocationY, goToLocationZ, focusLocationX, focusLocationY, focusLocationZ, speed, shootAtEnemies, distanceToStopAt, noRoadsDistance, unkTrue, unkFlag, aimingFlag, firingPattern); }
	static Void task_go_to_coord_any_means(Ped ped, float x, float y, float z, float speed, Any p5, bool p6, int walkingStyle, float p8) { return _i<Void>(0x5BC448CB78FA3E88, ped, x, y, z, speed, p5, p6, walkingStyle, p8); }
	static Void task_go_to_coord_any_means_extra_params(Ped ped, float x, float y, float z, float speed, Any p5, bool p6, int walkingStyle, float p8, Any p9, Any p10, Any p11, Any p12) { return _i<Void>(0x1DD45F9ECFDB1BC9, ped, x, y, z, speed, p5, p6, walkingStyle, p8, p9, p10, p11, p12); }
	static Void task_go_to_coord_any_means_extra_params_with_cruise_speed(Ped ped, float x, float y, float z, float speed, Any p5, bool p6, int walkingStyle, float p8, Any p9, Any p10, Any p11, Any p12, Any p13) { return _i<Void>(0xB8ECD61F531A7B02, ped, x, y, z, speed, p5, p6, walkingStyle, p8, p9, p10, p11, p12, p13); }
	static Void task_go_to_coord_while_aiming_at_coord(Ped ped, float x, float y, float z, float aimAtX, float aimAtY, float aimAtZ, float moveSpeed, bool p8, float p9, float p10, bool p11, Any flags, bool p13, uint32_t firingPattern) { return _i<Void>(0x11315AB3385B8AC0, ped, x, y, z, aimAtX, aimAtY, aimAtZ, moveSpeed, p8, p9, p10, p11, flags, p13, firingPattern); }
	static Void task_go_to_coord_while_aiming_at_entity(Any p0, float p1, float p2, float p3, Any p4, float p5, bool p6, float p7, float p8, bool p9, Any p10, bool p11, Any p12, Any p13) { return _i<Void>(0xB2A16444EAD9AE47, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	static Void task_go_to_entity(Entity entity, Entity target, int duration, float distance, float speed, float p5, int p6) { return _i<Void>(0x6A071245EB0D1882, entity, target, duration, distance, speed, p5, p6); }
	static Void task_go_to_entity_while_aiming_at_coord(Any p0, Any p1, float p2, float p3, float p4, float p5, bool p6, float p7, float p8, bool p9, bool p10, Any p11) { return _i<Void>(0x04701832B739DCE5, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static Void task_go_to_entity_while_aiming_at_entity(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, bool shootatEntity, float p5, float p6, bool p7, bool p8, uint32_t firingPattern) { return _i<Void>(0x97465886D35210E9, ped, entityToWalkTo, entityToAimAt, speed, shootatEntity, p5, p6, p7, p8, firingPattern); }
	static Void task_guard_assigned_defensive_area(Any p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return _i<Void>(0xD2A207EEBDF9889B, p0, p1, p2, p3, p4, p5, p6); }
	static Void task_guard_current_position(Ped p0, float p1, float p2, bool p3) { return _i<Void>(0x4A58A47A72E3FCB4, p0, p1, p2, p3); }
	static Void task_guard_sphere_defensive_area(Ped p0, float p1, float p2, float p3, float p4, float p5, Any p6, float p7, float p8, float p9, float p10) { return _i<Void>(0xC946FE14BE0EB5E2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static Void task_hands_up(Ped ped, int duration, Ped facingPed, int p3, bool p4) { return _i<Void>(0xF2EAB31979A7F910, ped, duration, facingPed, p3, p4); }
	static Void task_heli_chase(Ped pilot, Entity entityToFollow, float x, float y, float z) { return _i<Void>(0xAC83B1DB38D0ADA0, pilot, entityToFollow, x, y, z); }
	static Void task_heli_mission(Ped pilot, Vehicle vehicle, Vehicle vehicleToFollow, Ped pedToFollow, float posX, float posY, float posZ, int mode, float speed, float radius, float angle, int p11, int height, float p13, int p14) { return _i<Void>(0xDAD029E187A2BEB4, pilot, vehicle, vehicleToFollow, pedToFollow, posX, posY, posZ, mode, speed, radius, angle, p11, height, p13, p14); }
	static Void task_jump(Ped ped, bool unused, Any p2, Any p3) { return _i<Void>(0x0AE4086104E067B1, ped, unused, p2, p3); }
	static Void task_leave_any_vehicle(Ped ped, int p1, int p2) { return _i<Void>(0x504D54DF3F6F2247, ped, p1, p2); }
	static Void task_leave_vehicle(Ped ped, Vehicle vehicle, int flags) { return _i<Void>(0xD3DBCE61A490BE02, ped, vehicle, flags); }
	static Void task_look_at_coord(Entity entity, float x, float y, float z, float duration, Any p5, Any p6) { return _i<Void>(0x6FA46612594F7973, entity, x, y, z, duration, p5, p6); }
	static Void task_look_at_entity(Ped ped, Entity lookAt, int duration, int unknown1, int unknown2) { return _i<Void>(0x69F4BE8C8CC4796C, ped, lookAt, duration, unknown1, unknown2); }
	static Void task_move_network_advanced(Ped ped, const char* p1, float p2, float p3, float p4, float p5, float p6, float p7, Any p8, float p9, bool p10, const char* animDict, int flags) { return _i<Void>(0xD5B35BEA41919ACB, ped, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, animDict, flags); }
	static Void task_move_network(Ped ped, const char* task, float multiplier, bool p3, const char* animDict, int flags) { return _i<Void>(0x2D537BA194896636, ped, task, multiplier, p3, animDict, flags); }
	static Void task_open_vehicle_door(Ped ped, Vehicle vehicle, int timeOut, int doorIndex, float speed) { return _i<Void>(0x965791A9A488A062, ped, vehicle, timeOut, doorIndex, speed); }
	static Void task_parachute(Ped ped, bool p1, Any p2) { return _i<Void>(0xD2F1C53C97EE81AB, ped, p1, p2); }
	static Void task_parachute_to_target(Ped ped, float x, float y, float z) { return _i<Void>(0xB33E291AFA6BD03A, ped, x, y, z); }
	static Void task_patrol(Ped ped, const char* p1, Any p2, bool p3, bool p4) { return _i<Void>(0xBDA5DF49D080FE4E, ped, p1, p2, p3, p4); }
	static Void task_pause(Ped ped, int ms) { return _i<Void>(0xE73A266DB0CA9042, ped, ms); }
	static Void task_ped_slide_to_coord(Ped ped, float x, float y, float z, float heading, float p5) { return _i<Void>(0xD04FE6765D990A06, ped, x, y, z, heading, p5); }
	static Void task_ped_slide_to_coord_hdg_rate(Ped ped, float x, float y, float z, float heading, float p5, float p6) { return _i<Void>(0x5A4A6A6D3DC64F52, ped, x, y, z, heading, p5, p6); }
	static Void task_perform_sequence(Ped ped, Object taskSequence) { return _i<Void>(0x5ABA3986D90D8A3B, ped, taskSequence); }
	static Void task_perform_sequence_from_progress(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x89221B16730234F0, p0, p1, p2, p3); }
	static Void _0x8C33220C8D78CA0D(Any p0, Any p1) { return _i<Void>(0x8C33220C8D78CA0D, p0, p1); }
	static Void task_plane_chase(Ped pilot, Entity entityToFollow, float x, float y, float z) { return _i<Void>(0x2D2386F273FF7A25, pilot, entityToFollow, x, y, z); }
	static Void task_plane_land(Ped pilot, Vehicle plane, float runwayStartX, float runwayStartY, float runwayStartZ, float runwayEndX, float runwayEndY, float runwayEndZ) { return _i<Void>(0xBF19721FA34D32C0, pilot, plane, runwayStartX, runwayStartY, runwayStartZ, runwayEndX, runwayEndY, runwayEndZ); }
	static Void task_plane_mission(Ped pilot, Vehicle plane, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionType, float vehicleSpeed, float p9, float heading, float maxAltitude, float minAltitude, Any p13) { return _i<Void>(0x23703CD154E83B88, pilot, plane, targetVehicle, targetPed, destinationX, destinationY, destinationZ, missionType, vehicleSpeed, p9, heading, maxAltitude, minAltitude, p13); }
	static Void _0x92C360B5F15D2302(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x92C360B5F15D2302, p0, p1, p2, p3, p4, p5, p6); }
	static Void task_plant_bomb(Ped ped, float x, float y, float z, float heading) { return _i<Void>(0x965FEC691D55E9BF, ped, x, y, z, heading); }
	static Void task_play_anim(Ped ped, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, bool lockX, bool lockY, bool lockZ) { return _i<Void>(0xEA47FE3719165B94, ped, animDictionary, animationName, speed, speedMultiplier, duration, flag, playbackRate, lockX, lockY, lockZ); }
	static Void task_play_anim_advanced(Ped ped, const char* animDict, const char* animName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float speed, float speedMultiplier, int duration, Any flag, float animTime, Any p14, Any p15) { return _i<Void>(0x83CDB10EA29B370B, ped, animDict, animName, posX, posY, posZ, rotX, rotY, rotZ, speed, speedMultiplier, duration, flag, animTime, p14, p15); }
	static Void task_play_phone_gesture_animation(Ped ped, const char* animDict, const char* animation, const char* boneMaskType, float p4, float p5, bool p6, bool p7) { return _i<Void>(0x8FBB6758B3B3E9EC, ped, animDict, animation, boneMaskType, p4, p5, p6, p7); }
	static Void task_put_ped_directly_into_cover(Ped ped, float x, float y, float z, Any timeout, bool p5, float p6, bool p7, bool p8, Any p9, bool p10) { return _i<Void>(0x4172393E6BE1FECE, ped, x, y, z, timeout, p5, p6, p7, p8, p9, p10); }
	static Void task_put_ped_directly_into_melee(Ped ped, Ped meleeTarget, float p2, float p3, float p4, bool p5) { return _i<Void>(0x1C6CD14A876FFE39, ped, meleeTarget, p2, p3, p4, p5); }
	static Void task_rappel_from_heli(Ped ped, int unused) { return _i<Void>(0x09693B0312F91649, ped, unused); }
	static Void task_react_and_flee_ped(Ped ped, Ped fleeTarget) { return _i<Void>(0x72C896464915D1B1, ped, fleeTarget); }
	static Void task_reload_weapon(Ped ped, bool unused) { return _i<Void>(0x62D2916F56B9CD2D, ped, unused); }
	static Void task_scripted_animation(Ped ped, Any* p1, Any* p2, Any* p3, float p4, float p5) { return _i<Void>(0x126EF75F1E17ABE5, ped, p1, p2, p3, p4, p5); }
	static Void task_seek_cover_from_ped(Ped ped, Ped target, int duration, bool p3) { return _i<Void>(0x84D32B3BEC531324, ped, target, duration, p3); }
	static Void task_seek_cover_from_pos(Ped ped, float x, float y, float z, int duration, bool p5) { return _i<Void>(0x75AC2B60386D89F2, ped, x, y, z, duration, p5); }
	static Void task_seek_cover_to_coords(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, Any p7, bool p8) { return _i<Void>(0x39246A6958EF072C, ped, x1, y1, z1, x2, y2, z2, p7, p8); }
	static Void task_seek_cover_to_cover_point(Any p0, Any p1, float p2, float p3, float p4, Any p5, bool p6) { return _i<Void>(0xD43D95C7A869447F, p0, p1, p2, p3, p4, p5, p6); }
	static Void task_set_blocking_of_non_temporary_events(Ped ped, bool toggle) { return _i<Void>(0x90D2156198831D69, ped, toggle); }
	static Void task_set_decision_maker(Ped p0, uint32_t p1) { return _i<Void>(0xEB8517DDA73720DA, p0, p1); }
	static Void task_set_sphere_defensive_area(Any p0, float p1, float p2, float p3, float p4) { return _i<Void>(0x933C06518B52A9A4, p0, p1, p2, p3, p4); }
	static Void task_shocking_event_react(Ped ped, int eventHandle) { return _i<Void>(0x452419CBD838065B, ped, eventHandle); }
	static Void task_shoot_at_coord(Ped ped, float x, float y, float z, int duration, uint32_t firingPattern) { return _i<Void>(0x46A6CC01E0826106, ped, x, y, z, duration, firingPattern); }
	static Void task_shoot_at_entity(Entity entity, Entity target, int duration, uint32_t firingPattern) { return _i<Void>(0x08DA95E8298AE772, entity, target, duration, firingPattern); }
	static Void task_shuffle_to_next_vehicle_seat(Ped ped, Vehicle vehicle, Any p2) { return _i<Void>(0x7AA80209BDA643EB, ped, vehicle, p2); }
	static Void task_sky_dive(Ped ped, Any p1) { return _i<Void>(0x601736CFE536B0A0, ped, p1); }
	static Void task_smart_flee_coord(Ped ped, float x, float y, float z, float distance, int time, bool p6, bool p7) { return _i<Void>(0x94587F17E9C365D5, ped, x, y, z, distance, time, p6, p7); }
	static Void task_smart_flee_ped(Ped ped, Ped fleeTarget, float distance, Any fleeTime, bool p4, bool p5) { return _i<Void>(0x22B0D0E37CCB840D, ped, fleeTarget, distance, fleeTime, p4, p5); }
	static Void task_stand_guard(Ped ped, float x, float y, float z, float heading, const char* scenarioName) { return _i<Void>(0xAE032F8BBA959E90, ped, x, y, z, heading, scenarioName); }
	static Void task_stand_still(Ped ped, int time) { return _i<Void>(0x919BE13EED931959, ped, time); }
	static Void task_start_scenario_at_position(Ped ped, const char* scenarioName, float x, float y, float z, float heading, int duration, bool sittingScenario, bool teleport) { return _i<Void>(0xFA4EFC79F69D4F07, ped, scenarioName, x, y, z, heading, duration, sittingScenario, teleport); }
	static Void task_start_scenario_in_place(Ped ped, const char* scenarioName, int unkDelay, bool playEnterAnim) { return _i<Void>(0x142A02425FF02BD9, ped, scenarioName, unkDelay, playEnterAnim); }
	static Void task_stay_in_cover(Ped ped) { return _i<Void>(0xE5DA8615A6180789, ped); }
	static Void task_stealth_kill(Ped killer, Ped target, uint32_t killType, float p3, bool p4) { return _i<Void>(0xAA5DC05579D60BD9, killer, target, killType, p3, p4); }
	static Void task_stop_phone_gesture_animation(Ped ped, Any p1) { return _i<Void>(0x3FA00D4F4641BFAE, ped, p1); }
	static Void task_swap_weapon(Ped ped, bool p1) { return _i<Void>(0xA21C51255B205245, ped, p1); }
	static Void task_sweep_aim_entity(Ped ped, const char* anim, const char* p2, const char* p3, const char* p4, int p5, Vehicle vehicle, float p7, float p8) { return _i<Void>(0x2047C02158D6405A, ped, anim, p2, p3, p4, p5, vehicle, p7, p8); }
	static Void task_sweep_aim_position(Any p0, Any* p1, Any* p2, Any* p3, Any* p4, Any p5, float p6, float p7, float p8, float p9, float p10) { return _i<Void>(0x7AFE8FDC10BC07D2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static Void task_synchronized_scene(Ped ped, int scene, const char* animDictionary, const char* animationName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, Any p9) { return _i<Void>(0xEEA929141F699854, ped, scene, animDictionary, animationName, speed, speedMultiplier, duration, flag, playbackRate, p9); }
	static Void task_throw_projectile(int ped, float x, float y, float z, Any p4, Any p5) { return _i<Void>(0x7285951DBF6B5A51, ped, x, y, z, p4, p5); }
	static Void task_toggle_duck(bool p0, bool p1) { return _i<Void>(0xAC96609B9995EDF8, p0, p1); }
	static Void task_turn_ped_to_face_coord(Ped ped, float x, float y, float z, int duration) { return _i<Void>(0x1DDA930A0AC38571, ped, x, y, z, duration); }
	static Void task_turn_ped_to_face_entity(Ped ped, Entity entity, int duration) { return _i<Void>(0x5AD23D40115353AC, ped, entity, duration); }
	static Void task_use_mobile_phone(Ped ped, int p1, Any p2) { return _i<Void>(0xBD2A8EC3AF4DE7DB, ped, p1, p2); }
	static Void task_use_mobile_phone_timed(Ped ped, int duration) { return _i<Void>(0x5EE02954A14C69DB, ped, duration); }
	static Void task_use_nearest_scenario_chain_to_coord(Any p0, float p1, float p2, float p3, float p4, Any p5) { return _i<Void>(0x9FDA1B3D7E7028B3, p0, p1, p2, p3, p4, p5); }
	static Void task_use_nearest_scenario_chain_to_coord_warp(Any p0, float p1, float p2, float p3, float p4, Any p5) { return _i<Void>(0x97A28E63F0BA5631, p0, p1, p2, p3, p4, p5); }
	static Void task_use_nearest_scenario_to_coord(Ped ped, float x, float y, float z, float distance, int duration) { return _i<Void>(0x277F471BA9DB000B, ped, x, y, z, distance, duration); }
	static Void task_use_nearest_scenario_to_coord_warp(Ped ped, float x, float y, float z, float radius, Any p5) { return _i<Void>(0x58E2E0F23F6B76C3, ped, x, y, z, radius, p5); }
	static Void task_vehicle_aim_at_coord(Ped ped, float x, float y, float z) { return _i<Void>(0x447C1E9EF844BC0F, ped, x, y, z); }
	static Void task_vehicle_aim_at_ped(Ped ped, Ped target) { return _i<Void>(0xE41885592B08B097, ped, target); }
	static Void task_vehicle_chase(Ped driver, Entity targetEnt) { return _i<Void>(0x3C08A8E30363B353, driver, targetEnt); }
	static Void task_vehicle_drive_to_coord(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, Any p6, uint32_t vehicleModel, int drivingMode, float stopRange, float p10) { return _i<Void>(0xE2A2AA2F659D77A7, ped, vehicle, x, y, z, speed, p6, vehicleModel, drivingMode, stopRange, p10); }
	static Void task_vehicle_drive_to_coord_longrange(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int driveMode, float stopRange) { return _i<Void>(0x158BB33F920D360C, ped, vehicle, x, y, z, speed, driveMode, stopRange); }
	static Void task_vehicle_drive_wander(Ped ped, Vehicle vehicle, float speed, int drivingStyle) { return _i<Void>(0x480142959D337D00, ped, vehicle, speed, drivingStyle); }
	static Void task_vehicle_escort(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int p7, float noRoadsDistance) { return _i<Void>(0x0FA6E4B75F302400, ped, vehicle, targetVehicle, mode, speed, drivingStyle, minDistance, p7, noRoadsDistance); }
	static Void task_vehicle_follow(Ped driver, Vehicle vehicle, Entity targetEntity, int drivingStyle, float speed, int minDistance) { return _i<Void>(0xFC545A9F0626E3B6, driver, vehicle, targetEntity, drivingStyle, speed, minDistance); }
	static Void task_vehicle_follow_waypoint_recording(Ped ped, Vehicle vehicle, const char* WPRecording, int p3, int p4, int p5, int p6, float p7, bool p8, float p9) { return _i<Void>(0x3123FAA6DB1CF7ED, ped, vehicle, WPRecording, p3, p4, p5, p6, p7, p8, p9); }
	static Void task_vehicle_goto_navmesh(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int behaviorFlag, float stoppingRange) { return _i<Void>(0x195AEEB13CEFE2EE, ped, vehicle, x, y, z, speed, behaviorFlag, stoppingRange); }
	static Void task_vehicle_heli_protect(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int p4, float radius, int altitude, int p7) { return _i<Void>(0x1E09C32048FEFD1C, pilot, vehicle, entityToFollow, targetSpeed, p4, radius, altitude, p7); }
	static Void task_vehicle_mission(Any p0, Any p1, Any p2, Any p3, float p4, Any p5, float p6, float p7, bool p8) { return _i<Void>(0x659427E0EF36BCDE, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Void task_vehicle_mission_coors_target(Ped ped, Vehicle vehicle, float x, float y, float z, int p5, int p6, int p7, float p8, float p9, bool p10) { return _i<Void>(0xF0AF20AA7731F8C3, ped, vehicle, x, y, z, p5, p6, p7, p8, p9, p10); }
	static Void task_vehicle_mission_ped_target(Ped ped, Vehicle vehicle, Ped pedTarget, int mode, float maxSpeed, int drivingStyle, float minDistance, float p7, bool p8) { return _i<Void>(0x9454528DF15D657A, ped, vehicle, pedTarget, mode, maxSpeed, drivingStyle, minDistance, p7, p8); }
	static Void task_vehicle_park(Ped ped, Vehicle vehicle, float x, float y, float z, float heading, int mode, float radius, bool keepEngineOn) { return _i<Void>(0x0F3E34E968EA374E, ped, vehicle, x, y, z, heading, mode, radius, keepEngineOn); }
	static Void task_vehicle_play_anim(Vehicle vehicle, const char* animation_set, const char* animation_name) { return _i<Void>(0x69F5C3BD0F3EBD89, vehicle, animation_set, animation_name); }
	static Void task_vehicle_shoot_at_coord(Ped ped, float x, float y, float z, float p4) { return _i<Void>(0x5190796ED39C9B6D, ped, x, y, z, p4); }
	static Void task_vehicle_shoot_at_ped(Ped ped, Ped target, float p2) { return _i<Void>(0x10AB107B887214D8, ped, target, p2); }
	static Void task_vehicle_temp_action(Ped driver, Vehicle vehicle, int action, int time) { return _i<Void>(0xC429DCEEB339E129, driver, vehicle, action, time); }
	static Void task_wander_in_area(Ped ped, float x, float y, float z, float radius, float minimalLength, float timeBetweenWalks) { return _i<Void>(0xE054346CA3A0F315, ped, x, y, z, radius, minimalLength, timeBetweenWalks); }
	static Void task_wander_standard(Ped ped, float p1, int p2) { return _i<Void>(0xBB9CE077274F6A1B, ped, p1, p2); }
	static Void task_warp_ped_into_vehicle(Ped ped, Vehicle vehicle, int seat) { return _i<Void>(0x9A7D091411C5F684, ped, vehicle, seat); }
	static Void task_writhe(Ped ped, Ped target, int time, int p3, Any p4, Any p5) { return _i<Void>(0xCDDC2B77CE54AC6E, ped, target, time, p3, p4, p5); }
	static Void uncuff_ped(Ped ped) { return _i<Void>(0x67406F2C8F87FC4F, ped); }
	static Void update_task_aim_gun_scripted_target(Ped p0, Ped p1, float p2, float p3, float p4, bool p5) { return _i<Void>(0x9724FB59A3E72AD0, p0, p1, p2, p3, p4, p5); }
	static Void update_task_hands_up_duration(Ped ped, int duration) { return _i<Void>(0xA98FCAFD7893C834, ped, duration); }
	static Void update_task_sweep_aim_entity(Ped ped, Entity entity) { return _i<Void>(0xE4973DBDBE6E44B3, ped, entity); }
	static Void update_task_sweep_aim_position(Any p0, float p1, float p2, float p3) { return _i<Void>(0xBB106883F5201FC4, p0, p1, p2, p3); }
	static Void use_waypoint_recording_as_assisted_movement_route(Any* p0, bool p1, float p2, float p3) { return _i<Void>(0x5A353B8E6B1095B5, p0, p1, p2, p3); }
	static Void vehicle_waypoint_playback_override_speed(Any p0, float p1) { return _i<Void>(0x121F0593E0A431D7, p0, p1); }
	static Void vehicle_waypoint_playback_pause(Any p0) { return _i<Void>(0x8A4E6AC373666BC5, p0); }
	static Void vehicle_waypoint_playback_resume(Any p0) { return _i<Void>(0xDC04FCAA7839D492, p0); }
	static Void vehicle_waypoint_playback_use_default_speed(Any p0) { return _i<Void>(0x5CEB25A7D2848963, p0); }
	static bool waypoint_playback_get_is_paused(Any p0) { return _i<bool>(0x701375A7D43F01CB, p0); }
	static Void waypoint_playback_override_speed(Any p0, float p1, bool p2) { return _i<Void>(0x7D7D2B47FA788E85, p0, p1, p2); }
	static Void waypoint_playback_pause(Any p0, bool p1, bool p2) { return _i<Void>(0x0F342546AA06FED5, p0, p1, p2); }
	static Void waypoint_playback_resume(Any p0, bool p1, Any p2, Any p3) { return _i<Void>(0x244F70C84C547D2D, p0, p1, p2, p3); }
	static Void waypoint_playback_start_aiming_at_coord(Any p0, float p1, float p2, float p3, bool p4) { return _i<Void>(0x8968400D900ED8B3, p0, p1, p2, p3, p4); }
	static Void waypoint_playback_start_aiming_at_ped(Any p0, Any p1, bool p2) { return _i<Void>(0x20E330937C399D29, p0, p1, p2); }
	static Void waypoint_playback_start_shooting_at_coord(Any p0, float p1, float p2, float p3, bool p4, Any p5) { return _i<Void>(0x057A25CFCC9DB671, p0, p1, p2, p3, p4, p5); }
	static Void waypoint_playback_start_shooting_at_ped(Any p0, Any p1, bool p2, Any p3) { return _i<Void>(0xE70BA7B90F8390DC, p0, p1, p2, p3); }
	static Void waypoint_playback_stop_aiming_or_shooting(Any p0) { return _i<Void>(0x47EFA040EBB8E2EA, p0); }
	static Void waypoint_playback_use_default_speed(Any p0) { return _i<Void>(0x6599D834B12D0800, p0); }
	static bool waypoint_recording_get_closest_waypoint(const char* name, float x, float y, float z, int* point) { return _i<bool>(0xB629A298081F876F, name, x, y, z, point); }
	static bool waypoint_recording_get_coord(const char* name, int point, math::vector3<float>* coord) { return _i<bool>(0x2FB897405C90B361, name, point, coord); }
	static bool waypoint_recording_get_num_points(const char* name, int* points) { return _i<bool>(0x5343532C01A07234, name, points); }
	static float waypoint_recording_get_speed_at_point(const char* name, int point) { return _i<float>(0x005622AEBC33ACA9, name, point); }
	static Void task_follow_nav_mesh_to_coord_advanced(Ped ped, float x, float y, float z, float speed, int timeout, float unkFloat, int unkInt, float unkX, float unkY, float unkZ, float unk_40000f) { return _i<Void>(0x17F58B88D085DBAC, ped, x, y, z, speed, timeout, unkFloat, unkInt, unkX, unkY, unkZ, unk_40000f); }
	static Void set_next_desired_move_state(float p0) { return _i<Void>(0xF1B9F16E89E2C93A, p0); }

	static Void add_cam_spline_node(Cam camera, float x, float y, float z, float xRot, float yRot, float zRot, int length, int p8, int p9) { return _i<Void>(0x8609C75EC438FB3B, camera, x, y, z, xRot, yRot, zRot, length, p8, p9); }
	static Void _0x0FB82563989CF4FB(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0FB82563989CF4FB, p0, p1, p2, p3); }
	static Void _0x0A9F2A468B328E74(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0A9F2A468B328E74, p0, p1, p2, p3); }
	static Void _0x609278246A29CA34(Any p0, Any p1, Any p2) { return _i<Void>(0x609278246A29CA34, p0, p1, p2); }
	static Void _0x271017B9BA825366(Any p0, bool p1) { return _i<Void>(0x271017B9BA825366, p0, p1); }
	static Void animated_shake_cam(Cam cam, const char* p1, const char* p2, const char* p3, float amplitude) { return _i<Void>(0xA2746EEAE3E577CD, cam, p1, p2, p3, amplitude); }
	static Void _0xC2EAE3FB8CDBED31(const char* p0, const char* p1, const char* p2, float p3) { return _i<Void>(0xC2EAE3FB8CDBED31, p0, p1, p2, p3); }
	static Any _0x4879E4FE39074CDF() { return _i<Any>(0x4879E4FE39074CDF); }
	static Void attach_cam_to_entity(Cam cam, Entity entity, float xOffset, float yOffset, float zOffset, bool isRelative) { return _i<Void>(0xFEDB7D269E8C60E3, cam, entity, xOffset, yOffset, zOffset, isRelative); }
	static Void attach_cam_to_ped_bone(Cam cam, Ped ped, int boneIndex, float x, float y, float z, bool heading) { return _i<Void>(0x61A3DBA14AB7F411, cam, ped, boneIndex, x, y, z, heading); }
	static Void stop_cutscene_cam_shaking() { return _i<Void>(0xDB629FFD9285FA06); }
	static Void _0x62374889A4D59F72() { return _i<Void>(0x62374889A4D59F72); }
	static Cam create_cam(const char* camName, bool p1) { return _i<Cam>(0xC3981DCE61D9E13F, camName, p1); }
	static Cam create_camera(uint32_t camHash, bool p1) { return _i<Cam>(0x5E3CF89C6BCCA67D, camHash, p1); }
	static Cam create_camera_with_params(uint32_t camHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, Any p9) { return _i<Cam>(0x6ABFA3E16460F22D, camHash, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); }
	static Cam create_cam_with_params(const char* camName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, int p9) { return _i<Cam>(0xB51194800B257161, camName, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); }
	static Void create_cinematic_shot(Any p0, int p1, Any p2, Entity entity) { return _i<Void>(0x741B0129D4560F31, p0, p1, p2, entity); }
	static Void destroy_all_cams(bool thisScriptCheck) { return _i<Void>(0x8E5FB15663F79120, thisScriptCheck); }
	static Void destroy_cam(Cam cam, bool thisScriptCheck) { return _i<Void>(0x865908C81A2C22E9, cam, thisScriptCheck); }
	static Void detach_cam(Cam cam) { return _i<Void>(0xA2FABBE87F4BAD82, cam); }
	static Void disable_aim_cam_this_update() { return _i<Void>(0x1A31FE0049E542F6); }
	static Void _0x49482F9FCD825AAA(Entity entity) { return _i<Void>(0x49482F9FCD825AAA, entity); }
	static Void disable_vehicle_first_person_cam_this_frame() { return _i<Void>(0xADFF1B2A555F5FBA); }
	static Any _0x17FCA7199A530203() { return _i<Any>(0x17FCA7199A530203); }
	static Void _0x62ECFCFDEE7885D6() { return _i<Void>(0x62ECFCFDEE7885D6); }
	static Void _0xB1381B97F70C7B30() { return _i<Void>(0xB1381B97F70C7B30); }
	static Void _0x59424BD75174C9B1() { return _i<Void>(0x59424BD75174C9B1); }
	static Void enable_crosshair_this_frame() { return _i<Void>(0xEA7F0AD7E9BA676F); }
	static Void _0x5A43C76F7FC7BA5F() { return _i<Void>(0x5A43C76F7FC7BA5F); }
	static Void disable_first_person_cam_this_frame() { return _i<Void>(0xDE2EF5DA284CC8DF); }
	static bool does_cam_exist(Cam cam) { return _i<bool>(0xA7A932170592B50E, cam); }
	static Void do_screen_fade_in(int duration) { return _i<Void>(0xD4E8E24955024033, duration); }
	static Void do_screen_fade_out(int duration) { return _i<Void>(0x891B5B39AC6302AF, duration); }
	static Void _0x48608C3464F58AB4(Any p0, Any p1, Any p2) { return _i<Void>(0x48608C3464F58AB4, p0, p1, p2); }
	static Void _0xA41BCD7213805AAC(bool p0) { return _i<Void>(0xA41BCD7213805AAC, p0); }
	static Void _0x0AA27680A0BD43FA() { return _i<Void>(0x0AA27680A0BD43FA); }
	static Any _0x19CAFA3C87F7C2FF() { return _i<Any>(0x19CAFA3C87F7C2FF); }
	static float get_cam_anim_current_phase(Cam cam) { return _i<float>(0xA10B2DB49E92A6B0, cam); }
	static math::vector3<float> get_cam_coord(Cam cam) { return _i<math::vector3<float>>(0xBAC038F7459AE5AE, cam); }
	static float get_cam_far_clip(Cam cam) { return _i<float>(0xB60A9CFEB21CA6AA, cam); }
	static float get_cam_far_dof(Cam cam) { return _i<float>(0x255F8DAFD540D397, cam); }
	static float get_cam_fov(Cam cam) { return _i<float>(0xC3330A45CCCDB26A, cam); }
	static float get_cam_near_clip(Cam cam) { return _i<float>(0xC520A34DAFBF24B1, cam); }
	static math::vector3<float> get_cam_rot(Cam cam, int rotationOrder) { return _i<math::vector3<float>>(0x7D304C1C955E3E12, cam, rotationOrder); }
	static bool get_cam_spline_node_index(Cam cam) { return _i<bool>(0xB22B17DF858716A6, cam); }
	static float get_cam_spline_node_phase(Cam cam) { return _i<float>(0xD9D0E694C8282C96, cam); }
	static float get_cam_spline_phase(Cam cam) { return _i<float>(0xB5349E36C546509A, cam); }
	static Any _0xEE778F8C7E1142E2(Any p0) { return _i<Any>(0xEE778F8C7E1142E2, p0); }
	static math::vector3<float> get_gameplay_cam_coords() { return _i<math::vector3<float>>(0xA200EB1EE790F448); }
	static float _0xDFC8CBC606FDB0FC() { return _i<float>(0xDFC8CBC606FDB0FC); }
	static float _0x9780F32BCAF72431() { return _i<float>(0x9780F32BCAF72431); }
	static float _0x80EC114669DAEFF4() { return _i<float>(0x80EC114669DAEFF4); }
	static float _0x162F9D995753DC19() { return _i<float>(0x162F9D995753DC19); }
	static float _0xD0082607100D7193() { return _i<float>(0xD0082607100D7193); }
	static float _0xA03502FC581F7D9B() { return _i<float>(0xA03502FC581F7D9B); }
	static math::vector3<float> get_final_rendered_cam_rot(int rotationOrder) { return _i<math::vector3<float>>(0x5B4E4C817FCC2DFB, rotationOrder); }
	static float _0x5F35F6732C3FBBA0(Any p0) { return _i<float>(0x5F35F6732C3FBBA0, p0); }
	static math::vector3<float> _0x26903D9CD1175F2C(Any p0, Any p1) { return _i<math::vector3<float>>(0x26903D9CD1175F2C, p0, p1); }
	static float get_gameplay_cazoom() { return _i<float>(0x7EC52CC40597D170); }
	static Entity _0x89215EC747DF244A(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8) { return _i<Entity>(0x89215EC747DF244A, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static int get_follow_ped_cazoom_level() { return _i<int>(0x33E6C8EFD0CD93E9); }
	static int get_follow_ped_cam_view_mode() { return _i<int>(0x8D4D46230B2C353A); }
	static int get_follow_vehicle_cazoom_level() { return _i<int>(0xEE82280AB767B690); }
	static int get_follow_vehicle_cam_view_mode() { return _i<int>(0xA4FF579AC0E3AAAE); }
	static math::vector3<float> get_gameplay_cam_coord() { return _i<math::vector3<float>>(0x14D6F5678D8F1B37); }
	static float get_gameplay_cam_fov() { return _i<float>(0x65019750A0324133); }
	static float get_gameplay_cam_relative_heading() { return _i<float>(0x743607648ADD4587); }
	static float get_gameplay_cam_relative_pitch() { return _i<float>(0x3A6867B4845BEDA2); }
	static math::vector3<float> get_gameplay_cam_rot(int rotationOrder) { return _i<math::vector3<float>>(0x837765A25378F0BB, rotationOrder); }
	static Cam get_rendering_cam() { return _i<Cam>(0x5234F9F10919EABA); }
	static Void _0x149916F50C34A40D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Void>(0x149916F50C34A40D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void _0x7B8A361C1813FBEF() { return _i<Void>(0x7B8A361C1813FBEF); }
	static Void _0x9E4CFFF989258472() { return _i<Void>(0x9E4CFFF989258472); }
	static Void _0xF4F2C0D4EE209E20() { return _i<Void>(0xF4F2C0D4EE209E20); }
	static bool is_aim_cam_active() { return _i<bool>(0x68EDDA28A5976D07); }
	static bool _0x74BD83EA840F6BC9() { return _i<bool>(0x74BD83EA840F6BC9); }
	static Any _0xEAF0FA793D05C592() { return _i<Any>(0xEAF0FA793D05C592); }
	static Any _0xD7360051C885628B() { return _i<Any>(0xD7360051C885628B); }
	static bool is_cam_active(Cam cam) { return _i<bool>(0xDFB2B516207D3534, cam); }
	static bool is_cam_interpolating(Cam cam) { return _i<bool>(0x036F97C908C2B52C, cam); }
	static bool is_cam_playing_anim(Cam cam, const char* animName, const char* animDictionary) { return _i<bool>(0xC90621D8A0CEECF2, cam, animName, animDictionary); }
	static bool is_cam_rendering(Cam cam) { return _i<bool>(0x02EC0AF5C5A49B7A, cam); }
	static bool is_cam_shaking(Cam cam) { return _i<bool>(0x6B24BFE83A2BE47B, cam); }
	static bool is_cam_spline_paused(Any p0) { return _i<bool>(0x0290F35C0AD97864, p0); }
	static bool is_cinematic_cam_rendering() { return _i<bool>(0xB15162CB5826E9E8); }
	static bool is_cinematic_cam_shaking() { return _i<bool>(0xBBC08F6B4CB8FF0A); }
	static bool is_in_vehicle_cam_disabled() { return _i<bool>(0x4F32C0D5A90A9B40); }
	static bool _0xCA9D2AA3E326D720() { return _i<bool>(0xCA9D2AA3E326D720); }
	static bool is_cinematic_shot_active(Any p0) { return _i<bool>(0xCC9F3371A7C28BC9, p0); }
	static Any _0xBF72910D0F26F025() { return _i<Any>(0xBF72910D0F26F025); }
	static bool is_first_person_aim_cam_active() { return _i<bool>(0x5E346D934122613F); }
	static bool is_follow_ped_cam_active() { return _i<bool>(0xC6D3D26810C8E0F9); }
	static bool is_follow_vehicle_cam_active() { return _i<bool>(0xCBBDE6D335D6D496); }
	static bool is_gameplay_cam_looking_behind() { return _i<bool>(0x70FDA869F3317EA9); }
	static bool is_gameplay_cam_rendering() { return _i<bool>(0x39B5D1B10383F0C8); }
	static bool is_gameplay_cam_shaking() { return _i<bool>(0x016C090630DF1F89); }
	static bool is_gameplay_hint_active() { return _i<bool>(0xE520FF1AD2785B40); }
	static bool _0x3044240D2E0FA842() { return _i<bool>(0x3044240D2E0FA842); }
	static bool _0x705A276EBFF3133D() { return _i<bool>(0x705A276EBFF3133D); }
	static Any _0x1F2300CB7FA7B7F6() { return _i<Any>(0x1F2300CB7FA7B7F6); }
	static bool is_screen_faded_in() { return _i<bool>(0x5A859503B0C08678); }
	static bool is_screen_faded_out() { return _i<bool>(0xB16FCE9DDC7BA182); }
	static bool is_screen_fading_in() { return _i<bool>(0x5C544BC6C57AC575); }
	static bool is_screen_fading_out() { return _i<bool>(0x797AC7CB535BA28F); }
	static bool is_script_global_shaking() { return _i<bool>(0xC912AF078AF19212); }
	static bool is_sphere_visible(float x, float y, float z, float radius) { return _i<bool>(0xE33D59DA70B58FDF, x, y, z, radius); }
	static Void override_cam_spline_motion_blur(Cam cam, int p1, float p2, float p3) { return _i<Void>(0x7DCF7C708D292D55, cam, p1, p2, p3); }
	static Void override_cam_spline_velocity(Cam cam, int p1, float p2, float p3) { return _i<Void>(0x40B62FA033EB0346, cam, p1, p2, p3); }
	static bool play_cam_anim(Cam cam, const char* animName, const char* animDictionary, float x, float y, float z, float xRot, float yRot, float zRot, bool p9, int p10) { return _i<bool>(0x9A2D0FB2E7852392, cam, animName, animDictionary, x, y, z, xRot, yRot, zRot, p9, p10); }
	static bool play_synchronized_cam_anim(Any p0, Any p1, const char* animName, const char* animDictionary) { return _i<bool>(0xE32EFE9AB4A9AA0C, p0, p1, animName, animDictionary); }
	static Void point_cam_at_coord(Cam cam, float x, float y, float z) { return _i<Void>(0xF75497BB865F0803, cam, x, y, z); }
	static Void point_cam_at_entity(Cam cam, Entity entity, float p2, float p3, float p4, bool p5) { return _i<Void>(0x5640BFF86B16E8DC, cam, entity, p2, p3, p4, p5); }
	static Void point_cam_at_ped_bone(Cam cam, int ped, int boneIndex, float x, float y, float z, bool p6) { return _i<Void>(0x68B2B5F33BA63C41, cam, ped, boneIndex, x, y, z, p6); }
	static Void render_script_cams(bool render, bool ease, int easeTime, bool p3, bool p4, Any p5) { return _i<Void>(0x07E5B515DB0636FC, render, ease, easeTime, p3, p4, p5); }
	static Any _0x8BFCEB5EA1B161B6() { return _i<Any>(0x8BFCEB5EA1B161B6); }
	static Void _0x4008EDF7D6E48175(bool p0) { return _i<Void>(0x4008EDF7D6E48175, p0); }
	static Void set_cam_active(Cam cam, bool active) { return _i<Void>(0x026FB97D0A425F84, cam, active); }
	static Void set_cam_active_with_interp(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation) { return _i<Void>(0x9FBDA379383A52A4, camTo, camFrom, duration, easeLocation, easeRotation); }
	static Void set_cam_affects_aiming(Cam cam, bool toggle) { return _i<Void>(0x8C1DC7770C51DC8D, cam, toggle); }
	static Void set_cam_anim_current_phase(Cam cam, float phase) { return _i<Void>(0x4145A4C44FF3B5A6, cam, phase); }
	static Void _0x661B5C8654ADD825(Any p0, bool p1) { return _i<Void>(0x661B5C8654ADD825, p0, p1); }
	static Void set_cam_coord(Cam cam, float posX, float posY, float posZ) { return _i<Void>(0x4D41783FB745E42E, cam, posX, posY, posZ); }
	static Void set_cam_effect(int p0) { return _i<Void>(0x80C8B1846639BB19, p0); }
	static Void set_cam_dof_fnumber_of_lens(Cam camera, float p1) { return _i<Void>(0x7DD234D6F3914C5B, camera, p1); }
	static Void _0x47B595D60664CFFA(Any p0, Any p1) { return _i<Void>(0x47B595D60664CFFA, p0, p1); }
	static Void set_cam_dof_focus_distance_bias(Cam camera, float p1) { return _i<Void>(0xC669EEA5D031B7DE, camera, p1); }
	static Void set_cam_dof_max_near_in_focus_distance(Cam camera, float p1) { return _i<Void>(0xC3654A441402562D, camera, p1); }
	static Void set_cam_dof_max_near_in_focus_distance_blend_level(Cam camera, float p1) { return _i<Void>(0x2C654B4943BDDF7C, camera, p1); }
	static Void _0xF55E4046F6F831DC(Any p0, float p1) { return _i<Void>(0xF55E4046F6F831DC, p0, p1); }
	static Void _0xE111A7C0D200CBC5(Any p0, float p1) { return _i<Void>(0xE111A7C0D200CBC5, p0, p1); }
	static Void set_cam_dof_planes(Cam cam, float p1, float p2, float p3, float p4) { return _i<Void>(0x3CF48F6F96E749DC, cam, p1, p2, p3, p4); }
	static Void set_cam_dof_strength(Cam cam, float dofStrength) { return _i<Void>(0x5EE29B4D7D5DF897, cam, dofStrength); }
	static Void set_cam_far_clip(Cam cam, float farClip) { return _i<Void>(0xAE306F2A904BF86E, cam, farClip); }
	static Void set_cam_far_dof(Cam cam, float farDOF) { return _i<Void>(0xEDD91296CD01AEE0, cam, farDOF); }
	static Void set_cam_fov(Cam cam, float fieldOfView) { return _i<Void>(0xB13C14F66A00D047, cam, fieldOfView); }
	static Void set_cam_inherit_roll_vehicle(Cam cam, bool p1) { return _i<Void>(0x45F1DE9C34B93AE6, cam, p1); }
	static Void _0xA2767257A320FC82(Any p0, bool p1) { return _i<Void>(0xA2767257A320FC82, p0, p1); }
	static Void set_cam_motion_blur_strength(Cam cam, float strength) { return _i<Void>(0x6F0F77FBA9A8F2E6, cam, strength); }
	static Void set_cam_near_clip(Cam cam, float nearClip) { return _i<Void>(0xC7848EFCCC545182, cam, nearClip); }
	static Void set_cam_near_dof(Cam cam, float nearDOF) { return _i<Void>(0x3FA4BF0A7AB7DE2C, cam, nearDOF); }
	static Void set_cam_params(Cam cam, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fieldOfView, Any p8, int p9, int p10, int p11) { return _i<Void>(0xBFD8727AEA3CCEBA, cam, posX, posY, posZ, rotX, rotY, rotZ, fieldOfView, p8, p9, p10, p11); }
	static Void set_cam_rot(Cam cam, float rotX, float rotY, float rotZ, int rotationOrder) { return _i<Void>(0x85973643155D0B07, cam, rotX, rotY, rotZ, rotationOrder); }
	static Void set_cam_shake_amplitude(Cam cam, float amplitude) { return _i<Void>(0xD93DB43B82BC0D00, cam, amplitude); }
	static Void set_cam_spline_duration(int cam, int timeDuration) { return _i<Void>(0x1381539FEE034CDA, cam, timeDuration); }
	static Void _0x83B8201ED82A9A2D(Any p0, Any p1, Any p2, float p3) { return _i<Void>(0x83B8201ED82A9A2D, p0, p1, p2, p3); }
	static Void _0x7BF1A54AE67AC070(Any p0, Any p1, Any p2) { return _i<Void>(0x7BF1A54AE67AC070, p0, p1, p2); }
	static Void _0xA6385DEB180F319F(Any p0, Any p1, float p2) { return _i<Void>(0xA6385DEB180F319F, p0, p1, p2); }
	static Void set_cam_spline_phase(Cam cam, float p1) { return _i<Void>(0x242B5874F0A4E052, cam, p1); }
	static Void _0xD1B0F412F109EA5D(Any p0, Any p1) { return _i<Void>(0xD1B0F412F109EA5D, p0, p1); }
	static Void set_cam_use_shallow_dof_mode(Cam cam, bool toggle) { return _i<Void>(0x16A96863A17552BB, cam, toggle); }
	static Void _0x2A2173E46DAECD12(Any p0, Any p1) { return _i<Void>(0x2A2173E46DAECD12, p0, p1); }
	static Void set_cinematic_button_active(bool p0) { return _i<Void>(0x51669F7D1FB53D9F, p0); }
	static Void set_cinematic_cam_shake_amplitude(float p0) { return _i<Void>(0xC724C701C30B2FE7, p0); }
	static Void set_cinematic_mode_active(bool p0) { return _i<Void>(0xDCF0754AC3D6FD4E, p0); }
	static Void _0xDC9DA9E8789F5246() { return _i<Void>(0xDC9DA9E8789F5246); }
	static Void _0x12DED8CA53D47EA5(float p0) { return _i<Void>(0x12DED8CA53D47EA5, p0); }
	static Void _0x0AF7B437918103B3(float p0) { return _i<Void>(0x0AF7B437918103B3, p0); }
	static Void _0x2F7F2B26DD3F18EE(float p0, float p1) { return _i<Void>(0x2F7F2B26DD3F18EE, p0, p1); }
	static Void _0xBCFC632DB7673BF0(float p0, float p1) { return _i<Void>(0xBCFC632DB7673BF0, p0, p1); }
	static Void _0x70894BD0915C5BCA(float p0) { return _i<Void>(0x70894BD0915C5BCA, p0); }
	static Void _0xCED08CBE8EBB97C7(float p0, float p1) { return _i<Void>(0xCED08CBE8EBB97C7, p0, p1); }
	static Void _0x5C41E6BABC9E2112(Any p0) { return _i<Void>(0x5C41E6BABC9E2112, p0); }
	static Void _0x11FA5D3479C7DD47(Any p0) { return _i<Void>(0x11FA5D3479C7DD47, p0); }
	static Void _0x21E253A7F8DA5DFB(const char* vehicleName) { return _i<Void>(0x21E253A7F8DA5DFB, vehicleName); }
	static Void set_gameplay_cam_raw_yaw(float yaw) { return _i<Void>(0x103991D4A307D472, yaw); }
	static Void set_gameplay_cam_raw_pitch(float pitch) { return _i<Void>(0x759E13EBC1C15C5A, pitch); }
	static Void _0xC91C6C55199308CA(Any p0, float p1, float p2, float p3) { return _i<Void>(0xC91C6C55199308CA, p0, p1, p2, p3); }
	static Void _0x503F5920162365B2(Any p0, float p1, float p2, float p3) { return _i<Void>(0x503F5920162365B2, p0, p1, p2, p3); }
	static Void set_camera_range(Cam cam, float range) { return _i<Void>(0xF9D02130ECDD1D77, cam, range); }
	static Void _0xC8B5C4A79CC18B94(Cam p0) { return _i<Void>(0xC8B5C4A79CC18B94, p0); }
	static Void _0xE827B9382CFB41BA(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xE827B9382CFB41BA, p0, p1, p2, p3); }
	static Void _0xDD79DF9F4D26E1C9() { return _i<Void>(0xDD79DF9F4D26E1C9); }
	static Void _0xC8391C309684595A() { return _i<Void>(0xC8391C309684595A); }
	static bool set_follow_ped_cam_cutscene_chat(const char* p0, int p1) { return _i<bool>(0x44A113DD6FFC48D1, p0, p1); }
	static Void set_follow_ped_cam_view_mode(int viewMode) { return _i<Void>(0x5A4F9EDF1673F704, viewMode); }
	static Void set_time_idle_drop(bool p0, bool p1) { return _i<Void>(0x9DFE13ECDC1EC196, p0, p1); }
	static Void _0x91EF6EE6419E5B97(bool p0) { return _i<Void>(0x91EF6EE6419E5B97, p0); }
	static Void set_follow_vehicle_cazoom_level(int zoomLevel) { return _i<Void>(0x19464CB6E4078C8A, zoomLevel); }
	static Void set_follow_vehicle_cam_view_mode(int viewMode) { return _i<Void>(0xAC253D7842768F48, viewMode); }
	static Void _0xDB90C6CCA48940F1(bool p0) { return _i<Void>(0xDB90C6CCA48940F1, p0); }
	static Void _0xFD3151CD37EA2245(Any p0) { return _i<Void>(0xFD3151CD37EA2245, p0); }
	static Void _0x8BBACBF51DA047A8(Any p0) { return _i<Void>(0x8BBACBF51DA047A8, p0); }
	static Void _0x2AED6301F67007D5(Entity entity) { return _i<Void>(0x2AED6301F67007D5, entity); }
	static Void _0x0225778816FDC28C(float p0) { return _i<Void>(0x0225778816FDC28C, p0); }
	static Void custom_menu_coordinates(float p0) { return _i<Void>(0x487A82C650EB7799, p0); }
	static Void set_gameplay_cam_relative_heading(float heading) { return _i<Void>(0xB4EC2312F4E5B1F1, heading); }
	static Void set_gameplay_cam_relative_pitch(float x, float Value2) { return _i<Void>(0x6D0858B8EDFD2B7D, x, Value2); }
	static Void set_gameplay_cam_shake_amplitude(float amplitude) { return _i<Void>(0xA87E00932DB4D85D, amplitude); }
	static Void set_gameplay_coord_hint(float p0, float p1, float p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0xD51ADCD2D8BC0FB3, p0, p1, p2, p3, p4, p5, p6); }
	static Void set_gameplay_entity_hint(Entity entity, float xOffset, float yOffset, float zOffset, bool p4, int p5, int p6, int p7, Any p8) { return _i<Void>(0x189E955A8313E298, entity, xOffset, yOffset, zOffset, p4, p5, p6, p7, p8); }
	static Void _0xD1F8363DFAD03848(float p0) { return _i<Void>(0xD1F8363DFAD03848, p0); }
	static Void get_is_multiplayer_brief(bool p0) { return _i<Void>(0xE3433EADAAF7EE40, p0); }
	static Void _0x5D7B620DAE436138(float p0) { return _i<Void>(0x5D7B620DAE436138, p0); }
	static Void _0xC92717EF615B6704(float p0) { return _i<Void>(0xC92717EF615B6704, p0); }
	static Void _0xF8BDBF3D573049A1(float p0) { return _i<Void>(0xF8BDBF3D573049A1, p0); }
	static Void set_gameplay_hint_fov(float FOV) { return _i<Void>(0x513403FB9C56211F, FOV); }
	static Void set_gameplay_object_hint(Any p0, float p1, float p2, float p3, bool p4, Any p5, Any p6, Any p7) { return _i<Void>(0x83E87508A2CA2AC6, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void set_gameplay_ped_hint(Ped p0, float x1, float y1, float z1, bool p4, Any p5, Any p6, Any p7) { return _i<Void>(0x2B486269ACD548D3, p0, x1, y1, z1, p4, p5, p6, p7); }
	static Void set_gameplay_vehicle_hint(Any p0, float p1, float p2, float p3, bool p4, Any p5, Any p6, Any p7) { return _i<Void>(0xA2297E18F3E71C2E, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void _0xE9EA16D6E54CDCA4(Vehicle p0, int p1) { return _i<Void>(0xE9EA16D6E54CDCA4, p0, p1); }
	static Void _0x469F2ECDEC046337(bool p0) { return _i<Void>(0x469F2ECDEC046337, p0); }
	static Void _0x42156508606DE65E(float p0) { return _i<Void>(0x42156508606DE65E, p0); }
	static Void animate_gameplay_cam_zoom(float p0, float distance) { return _i<Void>(0xDF2E1F7742402E81, p0, distance); }
	static Void clamp_gameplay_cayaw(float minimum, float maximum) { return _i<Void>(0x8F993D26E0CA5E8E, minimum, maximum); }
	static Void clamp_gameplay_cam_pitch(float minimum, float maximum) { return _i<Void>(0xA516C198B7DCA1E1, minimum, maximum); }
	static Void set_use_hi_dof() { return _i<Void>(0xA13B0222F3D94A94); }
	static Void set_widescreen_borders(bool p0, int p1) { return _i<Void>(0xDCD4EA924F42D01A, p0, p1); }
	static Void shake_cam(Cam cam, const char* type, float amplitude) { return _i<Void>(0x6A25241C340D3822, cam, type, amplitude); }
	static Void shake_cinematic_cam(const char* p0, float p1) { return _i<Void>(0xDCE214D9ED58F3CF, p0, p1); }
	static Void shake_gameplay_cam(const char* shakeName, float intensity) { return _i<Void>(0xFD55E49555E017CF, shakeName, intensity); }
	static Void _0xF4C8CF9E353AFECA(const char* p0, float p1) { return _i<Void>(0xF4C8CF9E353AFECA, p0, p1); }
	static Void stop_cam_pointing(Cam cam) { return _i<Void>(0xF33AB75780BA57DE, cam); }
	static Void stop_cam_shaking(Cam cam, bool p1) { return _i<Void>(0xBDECF64367884AC3, cam, p1); }
	static Void stop_cinematic_cam_shaking(bool p0) { return _i<Void>(0x2238E588E588A6D7, p0); }
	static Void stop_cinematic_shot(Any p0) { return _i<Void>(0x7660C6E75D3A078E, p0); }
	static Void _0x247ACBC4ABBC9D1C(bool p0) { return _i<Void>(0x247ACBC4ABBC9D1C, p0); }
	static Void _0x324C5AA411DA7737(Any p0) { return _i<Void>(0x324C5AA411DA7737, p0); }
	static Void stop_gameplay_cam_shaking(bool p0) { return _i<Void>(0x0EF93E9F3D08C178, p0); }
	static Void stop_gameplay_hint(bool p0) { return _i<Void>(0xF46C581C61718916, p0); }
	static Void render_first_person_cam(bool render, Any p1, Any p2, Any p3) { return _i<Void>(0xC819F3CBB62BF692, render, p1, p2, p3); }
	static Void stop_script_global_shaking(bool p0) { return _i<Void>(0x1C9D7949FA533490, p0); }
	static Void _0x425A920FDB9A0DDA(Any p0) { return _i<Void>(0x425A920FDB9A0DDA, p0); }
	static Void _0x271401846BD26E92(bool p0, bool p1) { return _i<Void>(0x271401846BD26E92, p0, p1); }
	static Void _0x6493CF69859B116A() { return _i<Void>(0x6493CF69859B116A); }
	static bool _0x5C48A1D6E3B33179(Any p0) { return _i<bool>(0x5C48A1D6E3B33179, p0); }
	static Void set_cam_debug_name(Cam camera, const char* name) { return _i<Void>(0x1B93E0107865DD40, camera, name); }
	static Void _0xCCD078C2665D2973(bool p0) { return _i<Void>(0xCCD078C2665D2973, p0); }

	static Void add_to_clock_time(int hours, int minutes, int seconds) { return _i<Void>(0xD716F30D8C8980E2, hours, minutes, seconds); }
	static Void advance_clock_time_to(int hour, int minute, int second) { return _i<Void>(0xC8CA9670B9D83B3B, hour, minute, second); }
	static int get_clock_day_of_month() { return _i<int>(0x3D10BC92A4DB1D35); }
	static int get_clock_day_of_week() { return _i<int>(0xD972E4BD7AEB235F); }
	static int get_clock_hours() { return _i<int>(0x25223CA6B4D20B7F); }
	static int get_clock_minutes() { return _i<int>(0x13D2B8ADD79640F2); }
	static int get_clock_month() { return _i<int>(0xBBC72712E80257A1); }
	static int get_clock_seconds() { return _i<int>(0x494E97C2EF27C470); }
	static int get_clock_year() { return _i<int>(0x961777E64BDAF717); }
	static Void get_local_time(int* year, int* month, int* day, int* hour, int* minute, int* second) { return _i<Void>(0x50C7A99057A69748, year, month, day, hour, minute, second); }
	static int get_milliseconds_per_game_minute() { return _i<int>(0x2F8B4D1C595B11DB); }
	static Void get_posix_time(int* year, int* month, int* day, int* hour, int* minute, int* second) { return _i<Void>(0xDA488F299A5B164E, year, month, day, hour, minute, second); }
	static Void get_utc_time(int* year, int* month, int* day, int* hour, int* minute, int* second) { return _i<Void>(0x8117E09A19EEF4D3, year, month, day, hour, minute, second); }
	static Void pause_clock(bool toggle) { return _i<Void>(0x4055E40BD2DBEC1D, toggle); }
	static Void set_clock_date(int day, int month, int year) { return _i<Void>(0xB096419DF0D06CE7, day, month, year); }
	static Void set_clock_time(int hour, int minute, int second) { return _i<Void>(0x47C3B5848C3E45D8, hour, minute, second); }

	static bool _0xB56BBBCC2955D9CB() { return _i<bool>(0xB56BBBCC2955D9CB); }
	static bool can_set_enter_state_for_registered_entity(const char* cutsceneEntName, uint32_t modelHash) { return _i<bool>(0x645D0B458D8E17B5, cutsceneEntName, modelHash); }
	static bool can_set_exit_state_for_camera(bool p0) { return _i<bool>(0xB2CBCD0930DFB420, p0); }
	static bool can_set_exit_state_for_registered_entity(const char* cutsceneEntName, uint32_t modelHash) { return _i<bool>(0x4C6A6451C79E4662, cutsceneEntName, modelHash); }
	static Any _0x5EDEF0CF8C1DAB3C() { return _i<Any>(0x5EDEF0CF8C1DAB3C); }
	static bool does_cutscene_entity_exist(const char* cutsceneEntName, uint32_t modelHash) { return _i<bool>(0x499EF20C5DB25C59, cutsceneEntName, modelHash); }
	static int _0x583DF8E3D4AFBD98() { return _i<int>(0x583DF8E3D4AFBD98); }
	static int get_cutscene_section_playing() { return _i<int>(0x49010A6A396553D8); }
	static int get_cutscene_time() { return _i<int>(0xE625BEABBAFFDAB9); }
	static int get_cutscene_total_duration() { return _i<int>(0xEE53B14A19E480D4); }
	static Any _0x0ABC54DE641DC0FC(Any* p0) { return _i<Any>(0x0ABC54DE641DC0FC, p0); }
	static Entity get_entity_index_of_cutscene_entity(const char* cutsceneEntName, uint32_t modelHash) { return _i<Entity>(0x0A2E9FDB9A8C62F6, cutsceneEntName, modelHash); }
	static Entity get_entity_index_of_registered_entity(const char* cutsceneEntName, uint32_t modelHash) { return _i<Entity>(0xC0741A26499654CD, cutsceneEntName, modelHash); }
	static uint32_t* _0x708BDD8CD795B043() { return _i<uint32_t*>(0x708BDD8CD795B043); }
	static bool has_cutscene_finished() { return _i<bool>(0x7C0A893088881D57); }
	static bool has_cutscene_loaded() { return _i<bool>(0xC59F528E9AB9F339); }
	static bool _0xA1C996C2A744262E(Any* p0) { return _i<bool>(0xA1C996C2A744262E, p0); }
	static bool has_this_cutscene_loaded(const char* cutsceneName) { return _i<bool>(0x228D3D94F8A11C3C, cutsceneName); }
	static bool _0x4CEBC1ED31E8925E(const char* cutsceneName) { return _i<bool>(0x4CEBC1ED31E8925E, cutsceneName); }
	static bool is_cutscene_active() { return _i<bool>(0x991251AFC3981F84); }
	static bool _0x71B74D2AE19338D0(int p0) { return _i<bool>(0x71B74D2AE19338D0, p0); }
	static bool is_cutscene_playing() { return _i<bool>(0xD3C2E180A40F031E); }
	static int _0xA0FE76168A189DDB() { return _i<int>(0xA0FE76168A189DDB); }
	static Void _0x2F137B508DE238F2(bool p0) { return _i<Void>(0x2F137B508DE238F2, p0); }
	static Void register_entity_for_cutscene(Ped cutscenePed, const char* cutsceneEntName, int p2, uint32_t modelHash, int p4) { return _i<Void>(0xE40C1C56DF95C2E8, cutscenePed, cutsceneEntName, p2, modelHash, p4); }
	static Void remove_cutscene() { return _i<Void>(0x440AF51A3462B86F); }
	static Void _0xD00D76A7DFC9D852(Any* p0) { return _i<Void>(0xD00D76A7DFC9D852, p0); }
	static Void request_cutscene(const char* cutsceneName, int p1) { return _i<Void>(0x7A86743F475D9E09, cutsceneName, p1); }
	static Void request_cutscene_ex(const char* cutsceneName, int p1, int p2) { return _i<Void>(0xC23DE0E91C30B58C, cutsceneName, p1, p2); }
	static Void _0x06A3524161C502BA(Any* p0) { return _i<Void>(0x06A3524161C502BA, p0); }
	static Void register_synchronised_script_speech() { return _i<Void>(0x2131046957F31B04); }
	static Void _0xE36A98D8AB3D3C66(bool p0) { return _i<Void>(0xE36A98D8AB3D3C66, p0); }
	static Void _0x41FAA8FB2ECE8720(bool p0) { return _i<Void>(0x41FAA8FB2ECE8720, p0); }
	static Void _0x4C61C75BEE8184C2(const char* p0, Any p1, Any p2) { return _i<Void>(0x4C61C75BEE8184C2, p0, p1, p2); }
	static Void set_cutscene_fade_values(bool p0, bool p1, bool p2, bool p3) { return _i<Void>(0x8093F23ABACCC7D4, p0, p1, p2, p3); }
	static Void _0x20746F7B1032A3C7(bool p0, bool p1, bool p2, bool p3) { return _i<Void>(0x20746F7B1032A3C7, p0, p1, p2, p3); }
	static Void _0x06EE9048FD080382(bool p0) { return _i<Void>(0x06EE9048FD080382, p0); }
	static Void set_cutscene_origin(float x, float y, float z, float p3, int p4) { return _i<Void>(0xB812B3FD1C01CF27, x, y, z, p3, p4); }
	static Void _0x011883F41211432A(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x011883F41211432A, p0, p1, p2, p3, p4, p5, p6); }
	static Void set_cutscene_ped_component_variation(const char* cutsceneEntName, int p1, int p2, int p3, uint32_t modelHash) { return _i<Void>(0xBA01E7B6DEEFBBC9, cutsceneEntName, p1, p2, p3, modelHash); }
	static Void _0x2A56C06EBEF2B0D9(const char* cutsceneEntName, Ped ped, uint32_t modelHash) { return _i<Void>(0x2A56C06EBEF2B0D9, cutsceneEntName, ped, modelHash); }
	static Void set_cutscene_ped_prop_variation(const char* cutsceneEntName, int p1, int p2, int p3, uint32_t modelHash) { return _i<Void>(0x0546524ADE2E9723, cutsceneEntName, p1, p2, p3, modelHash); }
	static Void set_cutscene_trigger_area(float p0, float p1, float p2, float p3, float p4, float p5) { return _i<Void>(0x9896CE4721BE84BA, p0, p1, p2, p3, p4, p5); }
	static Void _0xC61B86C9F61EB404(bool toggle) { return _i<Void>(0xC61B86C9F61EB404, toggle); }
	static Void _0x8D9DF6ECA8768583(int p0) { return _i<Void>(0x8D9DF6ECA8768583, p0); }
	static Void _0x7F96F23FA9B73327(uint32_t modelHash) { return _i<Void>(0x7F96F23FA9B73327, modelHash); }
	static Void start_cutscene(int p0) { return _i<Void>(0x186D5CB5E7B0FF7B, p0); }
	static Void start_cutscene_at_coords(float x, float y, float z, int p3) { return _i<Void>(0x1C9ADDA3244A1FBF, x, y, z, p3); }
	static Void stop_cutscene(bool p0) { return _i<Void>(0xC7272775B4DC786E, p0); }
	static Void stop_cutscene_immediately() { return _i<Void>(0xD220BDD222AC4A1E); }
	static bool was_cutscene_skipped() { return _i<bool>(0x40C8656EDAEDD569); }

	static Void array_value_add_boolean(Any* arrayData, bool value) { return _i<Void>(0xF8B0F5A43E928C76, arrayData, value); }
	static Any* array_value_add_object(Any* arrayData) { return _i<Any*>(0x6889498B3E19C797, arrayData); }
	static Void array_value_add_float(Any* arrayData, float value) { return _i<Void>(0x57A995FD75D37F56, arrayData, value); }
	static Void array_value_add_integer(Any* arrayData, int value) { return _i<Void>(0xCABDB751D86FE93B, arrayData, value); }
	static Void array_value_add_string(Any* arrayData, const char* value) { return _i<Void>(0x2F0661C155AEEEAA, arrayData, value); }
	static Void array_value_add_vector3(Any* arrayData, float valueX, float valueY, float valueZ) { return _i<Void>(0x407F8D034F70F0C2, arrayData, valueX, valueY, valueZ); }
	static bool array_value_get_boolean(Any* arrayData, int arrayIndex) { return _i<bool>(0x50C1B2874E50C114, arrayData, arrayIndex); }
	static int array_value_get_size(Any* arrayData) { return _i<int>(0x065DB281590CEA2D, arrayData); }
	static Any* array_value_get_object(Any* arrayData, int arrayIndex) { return _i<Any*>(0x8B5FADCC4E3A145F, arrayData, arrayIndex); }
	static float array_value_get_float(Any* arrayData, int arrayIndex) { return _i<float>(0xC0C527B525D7CFB5, arrayData, arrayIndex); }
	static int array_value_get_integer(Any* arrayData, int arrayIndex) { return _i<int>(0x3E5AE19425CD74BE, arrayData, arrayIndex); }
	static const char* array_value_get_string(Any* arrayData, int arrayIndex) { return _i<const char*>(0xD3F2FFEB8D836F52, arrayData, arrayIndex); }
	static int array_value_get_type(Any* arrayData, int arrayIndex) { return _i<int>(0x3A0014ADB172A3C5, arrayData, arrayIndex); }
	static math::vector3<float> array_value_get_vector3(Any* arrayData, int arrayIndex) { return _i<math::vector3<float>>(0x8D2064E5B64A628A, arrayData, arrayIndex); }
	static Any* object_value_add_array(Any* objectData, const char* key) { return _i<Any*>(0x5B11728527CA6E5F, objectData, key); }
	static Any* object_value_add_object(Any* objectData, const char* key) { return _i<Any*>(0xA358F56F10732EE1, objectData, key); }
	static Any* object_value_get_array(Any* objectData, const char* key) { return _i<Any*>(0x7A983AA9DA2659ED, objectData, key); }
	static bool object_value_get_boolean(Any* objectData, const char* key) { return _i<bool>(0x1186940ED72FFEEC, objectData, key); }
	static Any* object_value_get_object(Any* objectData, const char* key) { return _i<Any*>(0xB6B9DDC412FCEEE2, objectData, key); }
	static float object_value_get_float(Any* objectData, const char* key) { return _i<float>(0x06610343E73B9727, objectData, key); }
	static int object_value_get_integer(Any* objectData, const char* key) { return _i<int>(0x78F06F6B1FB5A80C, objectData, key); }
	static const char* object_value_get_string(Any* objectData, const char* key) { return _i<const char*>(0x3D2FD9E763B24472, objectData, key); }
	static int object_value_get_type(Any* objectData, const char* key) { return _i<int>(0x031C55ED33227371, objectData, key); }
	static math::vector3<float> object_value_get_vector3(Any* objectData, const char* key) { return _i<math::vector3<float>>(0x46CD3CB66E0825CC, objectData, key); }
	static Void object_value_add_boolean(Any* objectData, const char* key, bool value) { return _i<Void>(0x35124302A556A325, objectData, key, value); }
	static Void object_value_add_float(Any* objectData, const char* key, float value) { return _i<Void>(0xC27E1CC2D795105E, objectData, key, value); }
	static Void object_value_add_integer(Any* objectData, const char* key, int value) { return _i<Void>(0xE7E035450A7948D5, objectData, key, value); }
	static Void object_value_add_string(Any* objectData, const char* key, const char* value) { return _i<Void>(0x8FF3847DADD8E30C, objectData, key, value); }
	static Void object_value_add_vector3(Any* objectData, const char* key, float valueX, float valueY, float valueZ) { return _i<Void>(0x4CD49B76338C7DEE, objectData, key, valueX, valueY, valueZ); }
	static Void _0x6CC86E78358D5119() { return _i<Void>(0x6CC86E78358D5119); }
	static Void datafile_create() { return _i<Void>(0xD27058A1CA2B13EE); }
	static Void datafile_delete() { return _i<Void>(0x9AB9C1CFC8862DFB); }
	static bool _0x8F5EA1C01D65A100(Any p0) { return _i<bool>(0x8F5EA1C01D65A100, p0); }
	static Void _0xC55854C7D7274882() { return _i<Void>(0xC55854C7D7274882); }
	static const char* datafile_get_file_dict() { return _i<const char*>(0x906B778CA1DC72B6); }
	static bool _0x15FF52B809DB2353(Any p0) { return _i<bool>(0x15FF52B809DB2353, p0); }
	static bool _0xF8CC1EBE0B62E29F(Any p0) { return _i<bool>(0xF8CC1EBE0B62E29F, p0); }
	static bool datafile_is_save_pending() { return _i<bool>(0xBEDB96A7584AA8CF); }
	static bool _0xFCCAE5B92A830878(Any p0) { return _i<bool>(0xFCCAE5B92A830878, p0); }
	static bool load_ugc_file(const char* filename) { return _i<bool>(0xC5238C011AF405E4, filename); }
	static bool _0x22DA66936E0FFF37(Any p0) { return _i<bool>(0x22DA66936E0FFF37, p0); }
	static bool _0x01095C95CD46B624(int p0) { return _i<bool>(0x01095C95CD46B624, p0); }
	static bool _0xA69AC4ADE82B57A4(int p0) { return _i<bool>(0xA69AC4ADE82B57A4, p0); }
	static bool _0x52818819057F2B40(int p0) { return _i<bool>(0x52818819057F2B40, p0); }
	static bool _0x9CB0BFA7A9342C3D(int p0, bool p1) { return _i<bool>(0x9CB0BFA7A9342C3D, p0, p1); }
	static bool _0x83BCCE3224735F05(const char* filename) { return _i<bool>(0x83BCCE3224735F05, filename); }
	static Void _0x2ED61456317B8178() { return _i<Void>(0x2ED61456317B8178); }
	static bool _0x4DFDD9EB705F8140(bool* p0) { return _i<bool>(0x4DFDD9EB705F8140, p0); }
	static Void _0xAD6875BBC0FC899C(Any p0) { return _i<Void>(0xAD6875BBC0FC899C, p0); }
	static bool _0xC84527E235FCA219(const char* p0, bool p1, const char* p2, Any* p3, Any* p4, const char* type, bool p6) { return _i<bool>(0xC84527E235FCA219, p0, p1, p2, p3, p4, type, p6); }
	static bool _0xA5EFC3E847D60507(const char* p0, const char* p1, const char* p2, const char* p3, bool p4) { return _i<bool>(0xA5EFC3E847D60507, p0, p1, p2, p3, p4); }
	static bool _0x692D808C34A82143(const char* p0, float p1, const char* type) { return _i<bool>(0x692D808C34A82143, p0, p1, type); }
	static bool _0x648E7A5434AF7969(const char* p0, Any* p1, bool p2, Any* p3, Any* p4, Any* p5, const char* type) { return _i<bool>(0x648E7A5434AF7969, p0, p1, p2, p3, p4, p5, type); }
	static bool _0x4645DE9980999E93(const char* p0, const char* p1, const char* p2, const char* p3, const char* type) { return _i<bool>(0x4645DE9980999E93, p0, p1, p2, p3, type); }

	static bool decor_exist_on(Entity entity, const char* propertyName) { return _i<bool>(0x05661B80A8C9165F, entity, propertyName); }
	static bool decor_get_bool(Entity entity, const char* propertyName) { return _i<bool>(0xDACE671663F2F5DB, entity, propertyName); }
	static float decor_get_float(Entity entity, const char* propertyName) { return _i<float>(0x6524A2F114706F43, entity, propertyName); }
	static int decor_get_int(Entity entity, const char* propertyName) { return _i<int>(0xA06C969B02A97298, entity, propertyName); }
	static bool decor_is_registered_as_type(const char* propertyName, int type) { return _i<bool>(0x4F14F9F870D6FBC8, propertyName, type); }
	static Void decor_register(const char* propertyName, int type) { return _i<Void>(0x9FD90732F56403CE, propertyName, type); }
	static Void decor_register_lock() { return _i<Void>(0xA9D14EEA259F9248); }
	static bool decor_remove(Entity entity, const char* propertyName) { return _i<bool>(0x00EE9F297C738720, entity, propertyName); }
	static bool decor_set_bool(Entity entity, const char* propertyName, bool value) { return _i<bool>(0x6B1E8E2ED1335B71, entity, propertyName, value); }
	static bool decor_set_float(Entity entity, const char* propertyName, float value) { return _i<bool>(0x211AB1DD8D0F363A, entity, propertyName, value); }
	static bool decor_set_int(Entity entity, const char* propertyName, int value) { return _i<bool>(0x0CE3AA5E1CA19E10, entity, propertyName, value); }
	static bool decor_set_time(Entity entity, const char* propertyName, int timestamp) { return _i<bool>(0x95AED7B8E39ECAA4, entity, propertyName, timestamp); }

	static bool _0x241FCA5B1AA14F75() { return _i<bool>(0x241FCA5B1AA14F75); }
	static Any _0x8D30F648014A92B5() { return _i<Any>(0x8D30F648014A92B5); }
	static bool get_is_loading_screen_active() { return _i<bool>(0x10D0A8F259E93EC9); }
	static bool nullify(Any* variable, Any unused) { return _i<bool>(0x46E2B844905BC5F0, variable, unused); }
	static bool _0xF2E07819EF1A5289() { return _i<bool>(0xF2E07819EF1A5289); }
	static Any _0xA213B11DFF526300() { return _i<Any>(0xA213B11DFF526300); }
	static bool is_dlc_present(uint32_t dlcHash) { return _i<bool>(0x812595A0644CE1DE, dlcHash); }
	static Void load_mp_dlc_maps() { return _i<Void>(0x0888C3502DBBEEF5); }
	static Void load_sp_dlc_maps() { return _i<Void>(0xD7C10C4A637992C9); }
	static Any _0x9489659372A81585() { return _i<Any>(0x9489659372A81585); }

	static Void apply_force_to_entity(Entity entity, int forceFlags, float x, float y, float z, float offX, float offY, float offZ, int p8, bool isLocal, bool p10, bool isMassRel, bool p12, bool p13) { return _i<Void>(0xC5F68BE9613E2D18, entity, forceFlags, x, y, z, offX, offY, offZ, p8, isLocal, p10, isMassRel, p12, p13); }
	static Void apply_force_to_entity_center_of_mass(Entity entity, int forceType, float x, float y, float z, bool p5, bool isRel, bool highForce, bool p8) { return _i<Void>(0x18FF00FC7EFF559E, entity, forceType, x, y, z, p5, isRel, highForce, p8); }
	static Void _0x5C48B75732C8456C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0x5C48B75732C8456C, p0, p1, p2, p3, p4, p5); }
	static Void _0xFD1695C5D3B05439(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0xFD1695C5D3B05439, p0, p1, p2, p3, p4, p5); }
	static Void attach_entity_to_entity(Entity entity1, Entity entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, bool p9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot) { return _i<Void>(0x6B9BBD38AB0796DF, entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, useSoftPinning, collision, isPed, vertexIndex, fixedRot); }
	static Void attach_entity_to_entity_physically(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, float xPos1, float yPos1, float zPos1, float xPos2, float yPos2, float zPos2, float xRot, float yRot, float zRot, float breakForce, bool fixedRot, bool p15, bool collision, bool p17, int p18) { return _i<Void>(0xC3675780C92F90F9, entity1, entity2, boneIndex1, boneIndex2, xPos1, yPos1, zPos1, xPos2, yPos2, zPos2, xRot, yRot, zRot, breakForce, fixedRot, p15, collision, p17, p18); }
	static Void clear_entity_last_damage_entity(Entity entity) { return _i<Void>(0xA72CD9CA74A5ECBA, entity); }
	static Void create_forced_object(float x, float y, float z, Any p3, uint32_t modelHash, bool p5) { return _i<Void>(0x150E808B375A385A, x, y, z, p3, modelHash, p5); }
	static Void create_model_hide(float x, float y, float z, float radius, uint32_t model, bool p5) { return _i<Void>(0x8A97BCA30A0CE478, x, y, z, radius, model, p5); }
	static Void create_model_hide_excluding_script_objects(float x, float y, float z, float radius, uint32_t model, bool p5) { return _i<Void>(0x3A52AE588830BF7F, x, y, z, radius, model, p5); }
	static Void create_model_swap(float x, float y, float z, float radius, uint32_t originalModel, uint32_t newModel, bool p6) { return _i<Void>(0x92C47782FDA8B2A3, x, y, z, radius, originalModel, newModel, p6); }
	static Void delete_entity(Entity* entity) { return _i<Void>(0xAE3CBE5BF394C9C9, entity); }
	static Void detach_entity(Entity entity, bool p1, bool collision) { return _i<Void>(0x961AC54BF0613F5D, entity, p1, collision); }
	static bool does_entity_belong_to_this_script(Entity entity, bool p1) { return _i<bool>(0xDDE6DF5AE89981D2, entity, p1); }
	static bool does_entity_exist(Entity entity) { return _i<bool>(0x7239B21A38F536BA, entity); }
	static bool does_entity_have_drawable(Entity entity) { return _i<bool>(0x060D6E96F8B8E48D, entity); }
	static bool does_entity_have_physics(Entity entity) { return _i<bool>(0xDA95EA3317CC5064, entity); }
	static Void _0x6CE177D014502E8A(Any p0) { return _i<Void>(0x6CE177D014502E8A, p0); }
	static bool find_anim_event_phase(const char* animDictionary, const char* animName, const char* p2, Any* p3, Any* p4) { return _i<bool>(0x07F1BE2BCCAA27A7, animDictionary, animName, p2, p3, p4); }
	static Void force_entity_ai_and_animation_update(Entity entity) { return _i<Void>(0x40FDEDB72F8293B2, entity); }
	static Void freeze_entity_position(Entity entity, bool toggle) { return _i<Void>(0x428CA6DBD1094446, entity, toggle); }
	static float get_anim_duration(const char* animDict, const char* animName) { return _i<float>(0xFEDDF04D62B8D790, animDict, animName); }
	static math::vector3<float> get_collision_normal_of_last_hit_for_entity(Entity entity) { return _i<math::vector3<float>>(0xE465D4AB7CA6AE72, entity); }
	static int get_entity_alpha(Entity entity) { return _i<int>(0x5A47B3B5E63E94C6, entity); }
	static float get_entity_anim_current_time(Entity entity, const char* animDict, const char* animName) { return _i<float>(0x346D81500D088F42, entity, animDict, animName); }
	static float get_entity_anim_total_time(Entity entity, const char* animDict, const char* animName) { return _i<float>(0x50BD2730B191E360, entity, animDict, animName); }
	static Entity get_entity_attached_to(Entity entity) { return _i<Entity>(0x48C2BED9180FE123, entity); }
	static Any _0xB328DCC3A3AA401B(Any p0) { return _i<Any>(0xB328DCC3A3AA401B, p0); }
	static int get_entity_bone_index_by_name(Entity entity, const char* boneName) { return _i<int>(0xFB71170B7E76ACBA, entity, boneName); }
	static math::vector3<float> _0x46F8696933A63C9B(Any p0, Any p1) { return _i<math::vector3<float>>(0x46F8696933A63C9B, p0, p1); }
	static math::vector3<float> _0xCE6294A232D03786(Any p0, Any p1) { return _i<math::vector3<float>>(0xCE6294A232D03786, p0, p1); }
	static Any _0xD95CC5D2AB15A09F(Any p0) { return _i<Any>(0xD95CC5D2AB15A09F, p0); }
	static bool get_entity_collision_disabled(Entity entity) { return _i<bool>(0xCCF1E97BEFDAE480, entity); }
	static math::vector3<float> get_entity_coords(Entity entity, bool alive) { return _i<math::vector3<float>>(0x3FEF770D40960D5A, entity, alive); }
	static math::vector3<float> get_entity_forward_vector(Entity entity) { return _i<math::vector3<float>>(0x0A794A5A57F8DF91, entity); }
	static float get_entity_forward_x(Entity entity) { return _i<float>(0x8BB4EF4214E0E6D5, entity); }
	static float get_entity_forward_y(Entity entity) { return _i<float>(0x866A4A5FAE349510, entity); }
	static float get_entity_heading(Entity entity) { return _i<float>(0xE83D4F9BA2A38914, entity); }
	static float get_entity_physics_heading(Entity entity) { return _i<float>(0x846BF6291198A71E, entity); }
	static int get_entity_health(Entity entity) { return _i<int>(0xEEF059FAD016D209, entity); }
	static float get_entity_height(Entity entity, float X, float Y, float Z, bool atTop, bool inWorldCoords) { return _i<float>(0x5A504562485944DD, entity, X, Y, Z, atTop, inWorldCoords); }
	static float get_entity_height_above_ground(Entity entity) { return _i<float>(0x1DD55701034110E5, entity); }
	static int get_entity_lod_dist(Entity entity) { return _i<int>(0x4159C2762B5791D6, entity); }
	static Void get_entity_matrix(Entity entity, math::vector3<float>* rightVector, math::vector3<float>* forwardVector, math::vector3<float>* upVector, math::vector3<float>* position) { return _i<Void>(0xECB2FC7235A7D137, entity, rightVector, forwardVector, upVector, position); }
	static int get_entity_max_health(Entity entity) { return _i<int>(0x15D757606D170C3C, entity); }
	static uint32_t get_entity_model(Entity entity) { return _i<uint32_t>(0x9F47B058362C84B5, entity); }
	static Any _0x1F922734E259BD26(Any p0, Any p1) { return _i<Any>(0x1F922734E259BD26, p0, p1); }
	static float get_entity_pitch(Entity entity) { return _i<float>(0xD45DC2893621E1FE, entity); }
	static int get_entity_population_type(Entity entity) { return _i<int>(0xF6F5161F4534EDFF, entity); }
	static Void get_entity_quaternion(Entity entity, float* x, float* y, float* z, float* w) { return _i<Void>(0x7B3703D2D32DFA18, entity, x, y, z, w); }
	static float get_entity_roll(Entity entity) { return _i<float>(0x831E0242595560DF, entity); }
	static math::vector3<float> get_entity_rotation(Entity entity, int rotationOrder) { return _i<math::vector3<float>>(0xAFBD61CC738D9EB9, entity, rotationOrder); }
	static math::vector3<float> get_entity_rotation_velocity(Entity entity) { return _i<math::vector3<float>>(0x213B91045D09B983, entity); }
	static const char* get_entity_script(Entity entity, ScrHandle* script) { return _i<const char*>(0xA6E9C38DB51D7748, entity, script); }
	static float get_entity_speed(Entity entity) { return _i<float>(0xD5037BA82E12416F, entity); }
	static math::vector3<float> get_entity_speed_vector(Entity entity, bool relative) { return _i<math::vector3<float>>(0x9A8D700A51CB7B0D, entity, relative); }
	static float get_entity_submerged_level(Entity entity) { return _i<float>(0xE81AFC1BC4CC41CE, entity); }
	static int get_entity_type(Entity entity) { return _i<int>(0x8ACD366038D14505, entity); }
	static float get_entity_upright_value(Entity entity) { return _i<float>(0x95EED5A694951F9F, entity); }
	static math::vector3<float> get_entity_velocity(Entity entity) { return _i<math::vector3<float>>(0x4805D2B1D8CF94A9, entity); }
	static uint32_t get_last_material_hit_by_entity(Entity entity) { return _i<uint32_t>(0x5C3D0A935F535C4C, entity); }
	static Player get_nearest_player_to_entity(Entity entity) { return _i<Player>(0x7196842CB375CDB3, entity); }
	static Player get_nearest_player_to_entity_on_team(Entity entity, int team) { return _i<Player>(0x4DC9A62F844D9337, entity, team); }
	static math::vector3<float> get_offset_from_entity_given_world_coords(Entity entity, float posX, float posY, float posZ) { return _i<math::vector3<float>>(0x2274BC1C4885E333, entity, posX, posY, posZ); }
	static math::vector3<float> get_offset_from_entity_in_world_coords(Entity entity, float offsetX, float offsetY, float offsetZ) { return _i<math::vector3<float>>(0x1899F328B0E12848, entity, offsetX, offsetY, offsetZ); }
	static Object get_object_index_from_entity_index(Entity entity) { return _i<Object>(0xD7E3B9735C0F89D6, entity); }
	static Ped get_ped_index_from_entity_index(Entity entity) { return _i<Ped>(0x04A2A40C73395041, entity); }
	static Vehicle get_vehicle_index_from_entity_index(Entity entity) { return _i<Vehicle>(0x4B53F92932ADFAC0, entity); }
	static math::vector3<float> get_world_position_of_entity_bone(Entity entity, int boneIndex) { return _i<math::vector3<float>>(0x44A8FCB8ED227738, entity, boneIndex); }
	static bool has_anim_event_fired(Entity entity, uint32_t actionHash) { return _i<bool>(0xEAF4CD9EA3E7E922, entity, actionHash); }
	static bool has_collision_loaded_around_entity(Entity entity) { return _i<bool>(0xE9676F61BC0B3321, entity); }
	static bool has_entity_anim_finished(Entity entity, const char* animDict, const char* animName, int p3) { return _i<bool>(0x20B711662962B472, entity, animDict, animName, p3); }
	static bool has_entity_been_damaged_by_any_object(Entity entity) { return _i<bool>(0x95EB9964FF5C5C65, entity); }
	static bool has_entity_been_damaged_by_any_ped(Entity entity) { return _i<bool>(0x605F5A140F202491, entity); }
	static bool has_entity_been_damaged_by_any_vehicle(Entity entity) { return _i<bool>(0xDFD5033FDBA0A9C8, entity); }
	static bool has_entity_been_damaged_by_entity(Entity entity1, Entity entity2, bool p2) { return _i<bool>(0xC86D67D52A707CF8, entity1, entity2, p2); }
	static bool has_entity_clear_los_to_entity(Entity entity1, Entity entity2, int traceType) { return _i<bool>(0xFCDFF7B72D23A1AC, entity1, entity2, traceType); }
	static bool has_entity_clear_los_to_entity_in_front(Entity entity1, Entity entity2) { return _i<bool>(0x0267D00AF114F17A, entity1, entity2); }
	static bool has_entity_collided_with_anything(Entity entity) { return _i<bool>(0x8BAD02F0368D9E14, entity); }
	static bool is_an_entity(int handle) { return _i<bool>(0x731EC8A916BD11A1, handle); }
	static bool is_entity_an_object(Entity entity) { return _i<bool>(0x8D68C8FD0FACA94E, entity); }
	static bool is_entity_attached(Entity entity) { return _i<bool>(0xB346476EF1A64897, entity); }
	static bool is_entity_attached_to_any_object(Entity entity) { return _i<bool>(0xCF511840CEEDE0CC, entity); }
	static bool is_entity_attached_to_any_ped(Entity entity) { return _i<bool>(0xB1632E9A5F988D11, entity); }
	static bool is_entity_attached_to_any_vehicle(Entity entity) { return _i<bool>(0x26AA915AD89BFB4B, entity); }
	static bool is_entity_attached_to_entity(Entity from, Entity to) { return _i<bool>(0xEFBE71898A993728, from, to); }
	static bool is_entity_at_coord(Entity entity, float xPos, float yPos, float zPos, float xSize, float ySize, float zSize, bool p7, bool p8, int p9) { return _i<bool>(0x20B60995556D004F, entity, xPos, yPos, zPos, xSize, ySize, zSize, p7, p8, p9); }
	static bool is_entity_at_entity(Entity entity1, Entity entity2, float xSize, float ySize, float zSize, bool p5, bool p6, int p7) { return _i<bool>(0x751B70C3D034E187, entity1, entity2, xSize, ySize, zSize, p5, p6, p7); }
	static bool is_entity_a_mission_entity(Entity entity) { return _i<bool>(0x0A7B270912999B3C, entity); }
	static bool is_entity_a_ped(Entity entity) { return _i<bool>(0x524AC5ECEA15343E, entity); }
	static bool is_entity_a_vehicle(Entity entity) { return _i<bool>(0x6AC7003FA6E5575E, entity); }
	static bool is_entity_dead(Entity entity, Any p1) { return _i<bool>(0x5F9532F3B5CC2551, entity, p1); }
	static bool is_entity_in_air(Entity entity) { return _i<bool>(0x886E37EC497200B6, entity); }
	static bool is_entity_in_angled_area(Entity entity, float originX, float originY, float originZ, float edgeX, float edgeY, float edgeZ, float angle, bool p8, bool p9, Any p10) { return _i<bool>(0x51210CED3DA1C78A, entity, originX, originY, originZ, edgeX, edgeY, edgeZ, angle, p8, p9, p10); }
	static bool is_entity_in_area(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8, Any p9) { return _i<bool>(0x54736AA40E271165, entity, x1, y1, z1, x2, y2, z2, p7, p8, p9); }
	static bool is_entity_in_water(Entity entity) { return _i<bool>(0xCFB0A0D8EDD145A3, entity); }
	static bool is_entity_in_zone(Entity entity, const char* zone) { return _i<bool>(0xB6463CF6AF527071, entity, zone); }
	static bool is_entity_occluded(Entity entity) { return _i<bool>(0xE31C2C72B8692B64, entity); }
	static bool is_entity_on_screen(Entity entity) { return _i<bool>(0xE659E47AF827484B, entity); }
	static bool is_entity_playing_anim(Entity entity, const char* animDict, const char* animName, int p4) { return _i<bool>(0x1F0B79228E461EC9, entity, animDict, animName, p4); }
	static bool is_entity_static(Entity entity) { return _i<bool>(0x1218E6886D3D8327, entity); }
	static bool is_entity_touching_entity(Entity entity, Entity targetEntity) { return _i<bool>(0x17FFC1B2BA35A494, entity, targetEntity); }
	static bool is_entity_touching_model(Entity entity, uint32_t modelHash) { return _i<bool>(0x0F42323798A58C8C, entity, modelHash); }
	static bool is_entity_upright(Entity entity, float angle) { return _i<bool>(0x5333F526F6AB19AA, entity, angle); }
	static bool is_entity_upsidedown(Entity entity) { return _i<bool>(0x1DBD58820FA61D71, entity); }
	static bool is_entity_visible(Entity entity) { return _i<bool>(0x47D6F43D77935C75, entity); }
	static bool is_entity_visible_to_script(Entity entity) { return _i<bool>(0xD796CB5BA8F20E32, entity); }
	static bool is_entity_waiting_for_world_collision(Entity entity) { return _i<bool>(0xD05BFF0C0A12C68F, entity); }
	static bool play_entity_anim(Entity entity, const char* animName, const char* animDict, float p3, bool loop, bool stayInAnim, bool p6, float delta, Any bitset) { return _i<bool>(0x7FB218262B810701, entity, animName, animDict, p3, loop, stayInAnim, p6, delta, bitset); }
	static bool play_synchronized_entity_anim(Entity entity, int syncedScene, const char* animation, const char* propName, float p4, float p5, Any p6, float p7) { return _i<bool>(0xC77720A12FE14A86, entity, syncedScene, animation, propName, p4, p5, p6, p7); }
	static bool play_synchronized_map_entity_anim(float p0, float p1, float p2, float p3, Any p4, Any p5, Any* p6, Any* p7, float p8, float p9, Any p10, float p11) { return _i<bool>(0xB9C54555ED30FBC4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static Void process_entity_attachments(Entity entity) { return _i<Void>(0xF4080490ADC51C6F, entity); }
	static Void remove_forced_object(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x61B6775E83C0DB6F, p0, p1, p2, p3, p4); }
	static Void remove_model_hide(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0xD9E3006FB3CBD765, p0, p1, p2, p3, p4, p5); }
	static Void remove_model_swap(float x, float y, float z, float radius, uint32_t originalModel, uint32_t newModel, bool p6) { return _i<Void>(0x033C0F9A64E229AE, x, y, z, radius, originalModel, newModel, p6); }
	static Void reset_entity_alpha(Entity entity) { return _i<Void>(0x9B1E824FFBB7027A, entity); }
	static Void _0x490861B88F4FD846(Any p0) { return _i<Void>(0x490861B88F4FD846, p0); }
	static Void _0x36F32DE87082343E(Any p0, Any p1) { return _i<Void>(0x36F32DE87082343E, p0, p1); }
	static Void _0xE12ABE5E3A389A6C(Entity entity, bool p1) { return _i<Void>(0xE12ABE5E3A389A6C, entity, p1); }
	static Void _0xA80AE305E0A3044F(Entity entity, bool p1) { return _i<Void>(0xA80AE305E0A3044F, entity, p1); }
	static Void set_entity_alpha(Entity entity, int alphaLevel, bool skin) { return _i<Void>(0x44A0870B7E92D7C0, entity, alphaLevel, skin); }
	static Void set_entity_always_prerender(Entity entity, bool toggle) { return _i<Void>(0xACAD101E1FB66689, entity, toggle); }
	static Void set_entity_anim_current_time(Entity entity, const char* animDictionary, const char* animName, float time) { return _i<Void>(0x4487C259F0F70977, entity, animDictionary, animName, time); }
	static Void set_entity_anim_speed(Entity entity, const char* animDictionary, const char* animName, float speedMultiplier) { return _i<Void>(0x28D1A16553C51776, entity, animDictionary, animName, speedMultiplier); }
	static Void set_entity_as_mission_entity(Entity entity, bool p1, bool p2) { return _i<Void>(0xAD738C3085FE7E11, entity, p1, p2); }
	static Void _0x68B562E124CC0AEF(Any p0, Any p1) { return _i<Void>(0x68B562E124CC0AEF, p0, p1); }
	static Void set_entity_can_be_damaged(Entity entity, bool toggle) { return _i<Void>(0x1760FFA8AB074D66, entity, toggle); }
	static Void set_entity_can_be_damaged_by_relationship_group(Entity entity, bool bCanBeDamaged, int relGroup) { return _i<Void>(0xE22D8FDE858B8119, entity, bCanBeDamaged, relGroup); }
	static Void set_entity_can_be_targeted_without_los(Entity entity, bool toggle) { return _i<Void>(0xD3997889736FD899, entity, toggle); }
	static Void _0xB17BC6453F6CF5AC(Any p0, Any p1) { return _i<Void>(0xB17BC6453F6CF5AC, p0, p1); }
	static Void _0x352E2B5CF420BF3B(Any p0, Any p1) { return _i<Void>(0x352E2B5CF420BF3B, p0, p1); }
	static Void set_entity_collision(Entity entity, bool toggle, bool keepPhysics) { return _i<Void>(0x1A9205C1B9EE827F, entity, toggle, keepPhysics); }
	static Void _0x9EBC85ED0FFFE51C(Entity entity, bool p1, bool p2) { return _i<Void>(0x9EBC85ED0FFFE51C, entity, p1, p2); }
	static Void set_entity_coords(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis, bool clearArea) { return _i<Void>(0x06843DA7060A026B, entity, xPos, yPos, zPos, xAxis, yAxis, zAxis, clearArea); }
	static Void set_entity_coords_no_offset(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis) { return _i<Void>(0x239A3351AC1DA385, entity, xPos, yPos, zPos, xAxis, yAxis, zAxis); }
	static Void set_entity_coords2(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis, bool clearArea) { return _i<Void>(0x621873ECE1178967, entity, xPos, yPos, zPos, xAxis, yAxis, zAxis, clearArea); }
	static Void set_entity_dynamic(Entity entity, bool toggle) { return _i<Void>(0x1718DE8E3F2823CA, entity, toggle); }
	static Void set_entity_has_gravity(Entity entity, bool toggle) { return _i<Void>(0x4A4722448F18EEF5, entity, toggle); }
	static Void set_entity_heading(Entity entity, float heading) { return _i<Void>(0x8E2530AA8ADA980E, entity, heading); }
	static Void set_entity_health(Entity entity, int health) { return _i<Void>(0x6B76DC1F3AE6E6A3, entity, health); }
	static Void set_entity_invincible(Entity entity, bool toggle) { return _i<Void>(0x3882114BDE571AD4, entity, toggle); }
	static Void _0x78E8E3A640178255(Entity entity) { return _i<Void>(0x78E8E3A640178255, entity); }
	static Void set_entity_is_target_priority(Entity entity, bool p1, float p2) { return _i<Void>(0xEA02E132F5C68722, entity, p1, p2); }
	static Void set_entity_lights(Entity entity, bool toggle) { return _i<Void>(0x7CFBA6A80BDF3874, entity, toggle); }
	static Void set_entity_load_collision_flag(Entity entity, bool toggle, Any p2) { return _i<Void>(0x0DC7CABAB1E9B67E, entity, toggle, p2); }
	static Void set_entity_lod_dist(Entity entity, int value) { return _i<Void>(0x5927F96A78577363, entity, value); }
	static Void set_entity_max_health(Entity entity, int value) { return _i<Void>(0x166E7CF68597D8B5, entity, value); }
	static Void set_entity_max_speed(Entity entity, float speed) { return _i<Void>(0x0E46A3FCBDE2A1B1, entity, speed); }
	static Void set_entity_motion_blur(Entity entity, bool toggle) { return _i<Void>(0x295D82A8559F9150, entity, toggle); }
	static Void _0x2C2E3DC128F44309(Entity entity, bool p1) { return _i<Void>(0x2C2E3DC128F44309, entity, p1); }
	static Void set_entity_no_collision_entity(Entity entity1, Entity entity2, bool unknown) { return _i<Void>(0xA53ED5520C07654A, entity1, entity2, unknown); }
	static Void set_entity_only_damaged_by_player(Entity entity, bool toggle) { return _i<Void>(0x79F020FF9EDC0748, entity, toggle); }
	static Void set_entity_only_damaged_by_relationship_group(Entity entity, bool p1, Any p2) { return _i<Void>(0x7022BD828FA0B082, entity, p1, p2); }
	static Void set_entity_proofs(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool p6, bool p7, bool drownProof) { return _i<Void>(0xFAEE099C6F890BB8, entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, p6, p7, drownProof); }
	static Void set_entity_quaternion(Entity entity, float x, float y, float z, float w) { return _i<Void>(0x77B21BE7AC540F07, entity, x, y, z, w); }
	static Void set_entity_records_collisions(Entity entity, bool toggle) { return _i<Void>(0x0A50A1EEDAD01E65, entity, toggle); }
	static Void set_entity_render_scorched(Entity entity, bool toggle) { return _i<Void>(0x730F5F8D3F0F2050, entity, toggle); }
	static Void _0x694E00132F2823ED(Entity entity, bool p1) { return _i<Void>(0x694E00132F2823ED, entity, p1); }
	static Void set_entity_rotation(Entity entity, float pitch, float roll, float yaw, int rotationOrder, bool p5) { return _i<Void>(0x8524A8B0171D5E07, entity, pitch, roll, yaw, rotationOrder, p5); }
	static Void set_entity_something(Entity entity, bool toggle) { return _i<Void>(0x3910051CCECDB00C, entity, toggle); }
	static Void _0x5C3B791D580E0BC2(Entity entity, float p1) { return _i<Void>(0x5C3B791D580E0BC2, entity, p1); }
	static Void set_entity_trafficlight_override(Entity entity, int state) { return _i<Void>(0x57C5DB656185EAC4, entity, state); }
	static Void _0x1A092BB0C3808B96(Entity entity, bool p1) { return _i<Void>(0x1A092BB0C3808B96, entity, p1); }
	static Void set_entity_velocity(Entity entity, float x, float y, float z) { return _i<Void>(0x1C99BB7B6E96D16F, entity, x, y, z); }
	static Void set_entity_visible(Entity entity, bool toggle, bool unk) { return _i<Void>(0xEA1C610A04DB6BBB, entity, toggle, unk); }
	static Void _0xC34BC448DA29F5E9(Any p0, Any p1) { return _i<Void>(0xC34BC448DA29F5E9, p0, p1); }
	static Void _0xCEA7C8E1B48FF68C(Any p0, Any p1) { return _i<Void>(0xCEA7C8E1B48FF68C, p0, p1); }
	static Void _0xD7B80E7C3BEFC396(Any p0, Any p1) { return _i<Void>(0xD7B80E7C3BEFC396, p0, p1); }
	static Void set_entity_as_no_longer_needed(Entity* entity) { return _i<Void>(0xB736A491E64A32CF, entity); }
	static Void set_ped_as_no_longer_needed(Ped* ped) { return _i<Void>(0x2595DD4236549CE3, ped); }
	static Void set_vehicle_as_no_longer_needed(Vehicle* vehicle) { return _i<Void>(0x629BFA74418D6239, vehicle); }
	static Void set_object_as_no_longer_needed(Object* object) { return _i<Void>(0x3AE22DEB5BA5A3E6, object); }
	static Void _0xDC6F8601FAF2E893(Entity entity, bool p1) { return _i<Void>(0xDC6F8601FAF2E893, entity, p1); }
	static Any stop_entity_anim(Entity entity, const char* animation, const char* animGroup, float p3) { return _i<Any>(0x28004F88151E03E0, entity, animation, animGroup, p3); }
	static bool stop_synchronized_entity_anim(Entity entity, float p1, bool p2) { return _i<bool>(0x43D3807C077261E3, entity, p1, p2); }
	static bool stop_synchronized_map_entity_anim(float p0, float p1, float p2, float p3, Any p4, float p5) { return _i<bool>(0x11E79CAB7183B6F5, p0, p1, p2, p3, p4, p5); }
	static bool would_entity_be_occluded(uint32_t entityModelHash, float x, float y, float z, bool p4) { return _i<bool>(0xEE5D2A122E09EC42, entityModelHash, x, y, z, p4); }

	static ScrHandle add_shocking_event_at_position(int type, float x, float y, float z, float duration) { return _i<ScrHandle>(0xD9F8455409B525E9, type, x, y, z, duration); }
	static ScrHandle add_shocking_event_for_entity(int type, Entity entity, float duration) { return _i<ScrHandle>(0x7FD8F3BE76F89422, type, entity, duration); }
	static Void block_decision_maker_event(uint32_t name, int type) { return _i<Void>(0xE42FCDFD0E4196F7, name, type); }
	static Void clear_decision_maker_event_response(uint32_t name, int type) { return _i<Void>(0x4FC9381A7AEE8968, name, type); }
	static bool is_shocking_event_in_sphere(int type, float x, float y, float z, float radius) { return _i<bool>(0x1374ABB7C15BAB92, type, x, y, z, radius); }
	static Void remove_all_shocking_events(bool p0) { return _i<Void>(0xEAABE8FDFA21274C, p0); }
	static bool remove_shocking_event(ScrHandle event) { return _i<bool>(0x2CDA538C44C6CCE5, event); }
	static Void remove_shocking_event_spawn_blocking_areas() { return _i<Void>(0x340F1415B68AEADE); }
	static Void set_decision_maker(Ped ped, uint32_t name) { return _i<Void>(0xB604A2942ADED0EE, ped, name); }
	static Void suppress_agitation_events_next_frame() { return _i<Void>(0x5F3B7749C112D552); }
	static Void suppress_shocking_events_next_frame() { return _i<Void>(0x2F9A292AD0A3BD89); }
	static Void suppress_shocking_event_type_next_frame(int type) { return _i<Void>(0x3FD2EC8BF1F1CF30, type); }
	static Void unblock_decision_maker_event(uint32_t name, int type) { return _i<Void>(0xD7CD9CF34F2C99E8, name, type); }

	static bool _0x341DE7ED1D2A1BFD(uint32_t componentHash, uint32_t drawableSlotHash, int componentId) { return _i<bool>(0x341DE7ED1D2A1BFD, componentHash, drawableSlotHash, componentId); }
	static bool get_dlc_vehicle_data(int dlcVehicleIndex, int* outData) { return _i<bool>(0x33468EDC08E371F6, dlcVehicleIndex, outData); }
	static int get_dlc_vehicle_flags(int dlcVehicleIndex) { return _i<int>(0x5549EE11FA22FCF2, dlcVehicleIndex); }
	static uint32_t get_dlc_vehicle_model(int dlcVehicleIndex) { return _i<uint32_t>(0xECC01B7C5763333C, dlcVehicleIndex); }
	static int _0xC098810437312FFF(int modData) { return _i<int>(0xC098810437312FFF, modData); }
	static bool get_dlc_weapon_component_data(int dlcWeaponIndex, int dlcWeapCompIndex, int* ComponentDataPtr) { return _i<bool>(0x6CF598A2957C2BF8, dlcWeaponIndex, dlcWeapCompIndex, ComponentDataPtr); }
	static bool get_dlc_weapon_data(int dlcWeaponIndex, int* outData) { return _i<bool>(0x79923CD21BECE14E, dlcWeaponIndex, outData); }
	static Void get_forced_component(uint32_t componentHash, int componentId, Any* p2, Any* p3, Any* p4) { return _i<Void>(0x6C93ED8C2F74859B, componentHash, componentId, p2, p3, p4); }
	static Void _0xE1CA84EBF72E691D(Any p0, Any p1, Any* p2, Any* p3, Any* p4) { return _i<Void>(0xE1CA84EBF72E691D, p0, p1, p2, p3, p4); }
	static uint32_t get_hash_name_for_component(Entity entity, int componentId, int drawableVariant, int textureVariant) { return _i<uint32_t>(0x0368B3A838070348, entity, componentId, drawableVariant, textureVariant); }
	static uint32_t get_hash_name_for_prop(Entity entity, int componentId, int propIndex, int propTextureIndex) { return _i<uint32_t>(0x5D6160275CAEC8DD, entity, componentId, propIndex, propTextureIndex); }
	static int get_num_dlc_vehicles() { return _i<int>(0xA7A866D21CD2329B); }
	static int get_num_dlc_weapons() { return _i<int>(0xEE47635F352DA367); }
	static int get_num_dlc_weapon_components(int dlcWeaponIndex) { return _i<int>(0x405425358A7D61FE, dlcWeaponIndex); }
	static int get_num_decorations(int character) { return _i<int>(0x278F76C3B0A8F109, character); }
	static int get_num_forced_components(uint32_t componentHash) { return _i<int>(0xC6B9DB42C04DD8C3, componentHash); }
	static Any _0x017568A8182D98A6(Any p0) { return _i<Any>(0x017568A8182D98A6, p0); }
	static int _0xC17AD0E5752BECDA(uint32_t componentHash) { return _i<int>(0xC17AD0E5752BECDA, componentHash); }
	static Any _0xD40AAC51E8E4C663(Any p0) { return _i<Any>(0xD40AAC51E8E4C663, p0); }
	static Void get_shop_ped_component(uint32_t p0, Any* p1) { return _i<Void>(0x74C0E2A57EC66760, p0, p1); }
	static Void get_shop_ped_outfit(Any p0, Any* p1) { return _i<Void>(0xB7952076E444979D, p0, p1); }
	static bool get_prop_from_outfit(Any outfit, int slot, Any* item) { return _i<bool>(0x19F2A026EDF0013F, outfit, slot, item); }
	static Any get_shop_ped_outfit_locate(Any p0) { return _i<Any>(0x073CA26B079F956E, p0); }
	static bool _0xA9F9C2E0FDE11CBB(Any p0, Any p1, Any* p2) { return _i<bool>(0xA9F9C2E0FDE11CBB, p0, p1, p2); }
	static Void _0x5D5CAFF661DDF6FC(Any p0, Any* p1) { return _i<Void>(0x5D5CAFF661DDF6FC, p0, p1); }
	static Void get_shop_ped_query_component(int componentId, int* outComponent) { return _i<Void>(0x249E310B2D920699, componentId, outComponent); }
	static Void get_shop_ped_query_outfit(Any p0, Any* outfit) { return _i<Void>(0x6D793F03A631FE56, p0, outfit); }
	static Void get_shop_ped_query_prop(Any p0, Any* p1) { return _i<Void>(0xDE44A00999B2837D, p0, p1); }
	static bool _0xFF56381874F82086(int p0, int p1, int* outComponent) { return _i<bool>(0xFF56381874F82086, p0, p1, outComponent); }
	static Void get_variant_component(uint32_t componentHash, int componentId, Any* p2, Any* p3, Any* p4) { return _i<Void>(0x6E11F282F11863B6, componentHash, componentId, p2, p3, p4); }
	static Void _0xD81B7F27BC773E66(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xD81B7F27BC773E66, p0, p1, p2, p3, p4); }
	static Void init_shop_ped_component(int* outComponent) { return _i<Void>(0x1E8C308FD312C036, outComponent); }
	static Void init_shop_ped_prop(int* outProp) { return _i<Void>(0xEB0A2B758F7B850F, outProp); }
	static bool is_dlc_data_empty(int dlcData) { return _i<bool>(0xD4D7B033C3AA243C, dlcData); }
	static bool is_dlc_vehicle_mod(int modData) { return _i<bool>(0x0564B9FF9631B82C, modData); }
	static int _0x50F457823CE6EB5F(int p0, int p1, int p2, int p3) { return _i<int>(0x50F457823CE6EB5F, p0, p1, p2, p3); }
	static int get_num_props_from_outfit(int character, int p1, int p2, bool p3, int p4, int componentId) { return _i<int>(0x9BDF59818B1E38C1, character, p1, p2, p3, p4, componentId); }
	static int _0xF3FBE2D50A6A8C28(int character, bool p1) { return _i<int>(0xF3FBE2D50A6A8C28, character, p1); }

	static void add_owned_explosion(Ped ped, float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake) { _i<Void>(0x172AA1B624FA1013, ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake); }
	static Void add_explosion(float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake, bool noDamage) { return _i<Void>(0xE3AD2BDBAEE269AC, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake, noDamage); }
	static Void add_explosion_with_user_vfx(float x, float y, float z, int explosionType, uint32_t explosionFx, float damageScale, bool isAudible, bool isInvisible, float cameraShake) { return _i<Void>(0x36DD3FE58B5E5212, x, y, z, explosionType, explosionFx, damageScale, isAudible, isInvisible, cameraShake); }
	static bool get_closest_fire_pos(math::vector3<float>* outPosition, float x, float y, float z) { return _i<bool>(0x352A9F6BCF90081F, outPosition, x, y, z); }
	static int get_number_of_fires_in_range(float x, float y, float z, float radius) { return _i<int>(0x50CAD495A460B305, x, y, z, radius); }
	static Entity get_ped_inside_explosion_area(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float radius) { return _i<Entity>(0x14BA4BA137AF6CEC, explosionType, x1, y1, z1, x2, y2, z2, radius); }
	static bool is_entity_on_fire(Entity entity) { return _i<bool>(0x28D3FED7190D3A0B, entity); }
	static Any _0x6070104B699B2EF4(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Any>(0x6070104B699B2EF4, p0, p1, p2, p3, p4, p5, p6); }
	static bool is_explosion_in_angled_area(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float angle) { return _i<bool>(0xA079A6C51525DC4B, explosionType, x1, y1, z1, x2, y2, z2, angle); }
	static bool is_explosion_in_area(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2) { return _i<bool>(0x2E2EBA0EE7CED0E0, explosionType, x1, y1, z1, x2, y2, z2); }
	static bool is_explosion_in_sphere(int explosionType, float x, float y, float z, float radius) { return _i<bool>(0xAB0F816885B0E483, explosionType, x, y, z, radius); }
	static Void remove_script_fire(int fireHandle) { return _i<Void>(0x7FF548385680673F, fireHandle); }
	static Any start_entity_fire(Entity entity) { return _i<Any>(0xF6A9D9708F6F23DF, entity); }
	static int start_script_fire(float X, float Y, float Z, int maxChildren, bool isGasFire) { return _i<int>(0x6B83617E04503888, X, Y, Z, maxChildren, isGasFire); }
	static Void stop_entity_fire(Entity entity) { return _i<Void>(0x7F0DD2EBBB651AFF, entity); }
	static Void stop_fire_in_range(float x, float y, float z, float radius) { return _i<Void>(0x056A8A219B8E829F, x, y, z, radius); }

	static Any _0x82ACC484FFA3B05F(Any p0) { return _i<Any>(0x82ACC484FFA3B05F, p0); }
	static int add_decal(int decalType, float posX, float posY, float posZ, float p4, float p5, float p6, float p7, float p8, float p9, float width, float height, float rCoef, float gCoef, float bCoef, float opacity, float timeout, bool p17, bool p18, bool p19) { return _i<int>(0xB302244A1839BDAD, decalType, posX, posY, posZ, p4, p5, p6, p7, p8, p9, width, height, rCoef, gCoef, bCoef, opacity, timeout, p17, p18, p19); }
	static Any add_entity_icon(Entity entity, const char* icon) { return _i<Any>(0x9CD43EEE12BF4DD0, entity, icon); }
	static Any add_petrol_decal(float x, float y, float z, float groundLvl, float width, float transparency) { return _i<Any>(0x4F5212C7AD880DF8, x, y, z, groundLvl, width, transparency); }
	static Void _0x967278682CB6967A(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x967278682CB6967A, p0, p1, p2, p3); }
	static Void _0x1A8E2C8B9CF4549C(Any* p0, Any* p1) { return _i<Void>(0x1A8E2C8B9CF4549C, p0, p1); }
	static bool add_clan_decal_to_vehicle(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, Any p13, int alpha) { return _i<bool>(0x428BDCB9DA58DA53, vehicle, ped, boneIndex, x1, x2, x3, y1, y2, y3, z1, z2, z3, scale, p13, alpha); }
	static Void _0xEFABC7722293DA7C() { return _i<Void>(0xEFABC7722293DA7C); }
	static Any _0xE35B38A27E8E7179(Any p0) { return _i<Any>(0xE35B38A27E8E7179, p0); }
	static bool get_screen_effect_is_active(const char* effectName) { return _i<bool>(0x36AD3E690DA5ACEB, effectName); }
	static Void start_screen_effect(const char* effectName, int duration, bool looped) { return _i<Void>(0x2206BF9A37B7F724, effectName, duration, looped); }
	static Void stop_screen_effect(const char* effectName) { return _i<Void>(0x068E835A1D0DC0E3, effectName); }
	static Void stop_all_screen_effects() { return _i<Void>(0xB4EDDC19532BFB85); }
	static Void _0xD2209BE128B5418C(const char* graphicsName) { return _i<Void>(0xD2209BE128B5418C, graphicsName); }
	static Void attach_tv_audio_to_entity(Entity entity) { return _i<Void>(0x845BAD77CC770633, entity); }
	static bool _0x759650634F07B6B4(Any p0) { return _i<bool>(0x759650634F07B6B4, p0); }
	static Any _0x7FA5D82B8F58EC06() { return _i<Any>(0x7FA5D82B8F58EC06); }
	static bool push_scaleform_movie_function(int scaleform, const char* functionName) { return _i<bool>(0xF6E48914C7A8694E, scaleform, functionName); }
	static bool push_scaleform_movie_function_n(const char* functionName) { return _i<bool>(0xAB58C27C2E6123C6, functionName); }
	static bool _0xB9449845F73F5E9C(const char* functionName) { return _i<bool>(0xB9449845F73F5E9C, functionName); }
	static bool push_scaleform_movie_function_from_hud_component(int hudComponent, const char* functionName) { return _i<bool>(0x98C494FD5BDFBFD5, hudComponent, functionName); }
	static Any _0xA67C35C56EB1BD9D() { return _i<Any>(0xA67C35C56EB1BD9D); }
	static Any _0x1DD2139A9A20DCE8() { return _i<Any>(0x1DD2139A9A20DCE8); }
	static Void begin_text_command_scaleform_string(const char* componentType) { return _i<Void>(0x80338406F3475E55, componentType); }
	static Void call_scaleform_movie_method(int scaleform, const char* method) { return _i<Void>(0xFBD96D87AC96D533, scaleform, method); }
	static Void call_scaleform_movie_function_float_params(int scaleform, const char* functionName, float param1, float param2, float param3, float param4, float param5) { return _i<Void>(0xD0837058AE2E4BEE, scaleform, functionName, param1, param2, param3, param4, param5); }
	static Void call_scaleform_movie_function_mixed_params(int scaleform, const char* functionName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, const char* stringParam1, const char* stringParam2, const char* stringParam3, const char* stringParam4, const char* stringParam5) { return _i<Void>(0xEF662D8D57E290B1, scaleform, functionName, floatParam1, floatParam2, floatParam3, floatParam4, floatParam5, stringParam1, stringParam2, stringParam3, stringParam4, stringParam5); }
	static Void call_scaleform_movie_function_string_params(int scaleform, const char* functionName, const char* param1, const char* param2, const char* param3, const char* param4, const char* param5) { return _i<Void>(0x51BC1ED3CC44E8F7, scaleform, functionName, param1, param2, param3, param4, param5); }
	static Void _0x27CB772218215325() { return _i<Void>(0x27CB772218215325); }
	static Void set_far_shadows_suppressed(bool toggle) { return _i<Void>(0x80ECBC0C856D3B0B, toggle); }
	static Void _0x0AE73D8DF3A762B2(bool p0) { return _i<Void>(0x0AE73D8DF3A762B2, p0); }
	static Void _0x03FC694AE06C5A20() { return _i<Void>(0x03FC694AE06C5A20); }
	static Void _0x6DDBF9DFFC4AC080(bool p0) { return _i<Void>(0x6DDBF9DFFC4AC080, p0); }
	static Void _0x259BA6D4E6F808F1(Any p0) { return _i<Void>(0x259BA6D4E6F808F1, p0); }
	static Void _0xD2936CAB8B58FCBD(Any p0, bool p1, float p2, float p3, float p4, float p5, bool p6, float p7) { return _i<Void>(0xD2936CAB8B58FCBD, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void _0x5F0F3F56635809EF(float p0) { return _i<Void>(0x5F0F3F56635809EF, p0); }
	static Void _0xD39D13C9FEBF0511(bool p0) { return _i<Void>(0xD39D13C9FEBF0511, p0); }
	static Void _0x02AC28F3A01FA04A(float p0) { return _i<Void>(0x02AC28F3A01FA04A, p0); }
	static Void _0x5E9DAF5A20F15908(float p0) { return _i<Void>(0x5E9DAF5A20F15908, p0); }
	static Void _0x25FC3E33A31AD0C9(bool p0) { return _i<Void>(0x25FC3E33A31AD0C9, p0); }
	static Void _0xB11D94BC55F41932(const char* p0) { return _i<Void>(0xB11D94BC55F41932, p0); }
	static Void _0x36F6626459D91457(float p0) { return _i<Void>(0x36F6626459D91457, p0); }
	static Void _0x15E33297C3E8DC60(Any p0) { return _i<Void>(0x15E33297C3E8DC60, p0); }
	static Void clear_draw_origin() { return _i<Void>(0xFF0B610F6BE0D7AF); }
	static Void _0x92CCC17A7A2285DA() { return _i<Void>(0x92CCC17A7A2285DA); }
	static Void _0x2A251AA48B2B46DB() { return _i<Void>(0x2A251AA48B2B46DB); }
	static Void _0x4AF92ACD3141D96C() { return _i<Void>(0x4AF92ACD3141D96C); }
	static Void clear_timecycle_modifier() { return _i<Void>(0x0F07E7745A236711); }
	static Void _0xBEB3D46BB7F043C0(Any p0) { return _i<Void>(0xBEB3D46BB7F043C0, p0); }
	static int create_checkpoint(int type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float radius, int red, int green, int blue, int alpha, int reserved) { return _i<int>(0x0134F0835AB6BFCB, type, posX1, posY1, posZ1, posX2, posY2, posZ2, radius, red, green, blue, alpha, reserved); }
	static Object create_tracked_point() { return _i<Object>(0xE2C9439ED45DEA60); }
	static Void delete_checkpoint(int checkpoint) { return _i<Void>(0xF5ED37F54CD4D52E, checkpoint); }
	static Void destroy_tracked_point(Object point) { return _i<Void>(0xB25DC90BAD56CA42, point); }
	static Void _0x0E4299C549F0D1F1(bool p0) { return _i<Void>(0x0E4299C549F0D1F1, p0); }
	static Void set_particle_fx_blood_scale(bool p0) { return _i<Void>(0x5F6DF3D92271E8A1, p0); }
	static Void _0xC35A6D07C93802B2() { return _i<Void>(0xC35A6D07C93802B2); }
	static Void _0x2BF72AD5B41AA739() { return _i<Void>(0x2BF72AD5B41AA739); }
	static Void _0x3669F1B198DCAA4F() { return _i<Void>(0x3669F1B198DCAA4F); }
	static Void _0x1612C45F9E3E0D44() { return _i<Void>(0x1612C45F9E3E0D44); }
	static Void _0xEFD97FF47B745B8D(Any p0) { return _i<Void>(0xEFD97FF47B745B8D, p0); }
	static Void _0xDE81239437E8C5A8() { return _i<Void>(0xDE81239437E8C5A8); }
	static Void _0x02369D5C8A51FDCF(bool p0) { return _i<Void>(0x02369D5C8A51FDCF, p0); }
	static Void disable_vehicle_distantlights(bool toggle) { return _i<Void>(0xC9F98AC1884E73A2, toggle); }
	static bool _0x5E657EF1099EDD65(Any p0) { return _i<bool>(0x5E657EF1099EDD65, p0); }
	static bool does_particle_fx_looped_exist(int ptfxHandle) { return _i<bool>(0x74AFEF0D2E1E409B, ptfxHandle); }
	static bool does_vehicle_have_decal(Vehicle vehicle, Any p1) { return _i<bool>(0x060D935D3981A275, vehicle, p1); }
	static Void _0x22A249A53034450A(bool p0) { return _i<Void>(0x22A249A53034450A, p0); }
	static Void draw_box(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha) { return _i<Void>(0xD3A9971CADAC7252, x1, y1, z1, x2, y2, z2, red, green, blue, alpha); }
	static Void draw_light_with_range(float posX, float posY, float posZ, int colorR, int colorG, int colorB, float range, float intensity) { return _i<Void>(0xF2A1B2771A01DBD4, posX, posY, posZ, colorR, colorG, colorB, range, intensity); }
	static Void draw_light_with_range_and_shadow(float x, float y, float z, int r, int g, int b, float range, float intensity, float shadow) { return _i<Void>(0xF49E9A9716A04595, x, y, z, r, g, b, range, intensity, shadow); }
	static Void draw_line(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha) { return _i<Void>(0x6B7256074AE34680, x1, y1, z1, x2, y2, z2, red, green, blue, alpha); }
	static Void _0x1072F115DAB0717E(bool p0, bool p1) { return _i<Void>(0x1072F115DAB0717E, p0, p1); }
	static Void draw_marker(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, bool bobUpAndDown, bool faceCamera, int p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts) { return _i<Void>(0x28477EC23D892089, type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts); }
	static Void _0xE82728F0DE75D13A(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17, Any p18, Any p19, Any p20, Any p21, Any p22, Any p23, Any p24) { return _i<Void>(0xE82728F0DE75D13A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24); }
	static Void _0x799017F9E3B10112(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return _i<Void>(0x799017F9E3B10112, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void draw_poly(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha) { return _i<Void>(0xAC26716048436851, x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha); }
	static Void draw_rect(float x, float y, float width, float height, int r, int g, int b, int a, Any p8) { return _i<Void>(0x3A618A217E5154F0, x, y, width, height, r, g, b, a, p8); }
	static Void draw_scaleform_movie(int scaleformHandle, float x, float y, float width, float height, int red, int green, int blue, int alpha, int unk) { return _i<Void>(0x54972ADAF0294A93, scaleformHandle, x, y, width, height, red, green, blue, alpha, unk); }
	static Void draw_scaleform_movie3_d(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, Any p13) { return _i<Void>(0x87D51D72255D4E78, scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, p13); }
	static Void draw_scaleform_movie3_d_non_additive(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, Any p13) { return _i<Void>(0x1CE592FDC749D6F5, scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, p13); }
	static Void draw_scaleform_movie_fullscreen(int scaleform, int red, int green, int blue, int alpha, int unk) { return _i<Void>(0x0DF606929C105BE1, scaleform, red, green, blue, alpha, unk); }
	static Void draw_scaleform_movie_fullscreen_masked(int scaleform1, int scaleform2, int red, int green, int blue, int alpha) { return _i<Void>(0xCF537FDE4FBD4CE5, scaleform1, scaleform2, red, green, blue, alpha); }
	static Void draw_spot_light_with_shadow(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float roundness, float radius, float falloff, float shadow) { return _i<Void>(0x5BCA583A583194DB, posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, roundness, radius, falloff, shadow); }
	static Void draw_spot_light(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float roundness, float radius, float falloff) { return _i<Void>(0xD0F64B265C8C8B33, posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, roundness, radius, falloff); }
	static Void draw_sprite(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, Any p11) { return _i<Void>(0xE7FFAE5EBF23D890, textureDict, textureName, screenX, screenY, width, height, heading, red, green, blue, alpha, p11); }
	static Void _0x2BC54A8188768488(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return _i<Void>(0x2BC54A8188768488, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static Void draw_sprite_poly(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, int p9, int p10, int p11, int p12, const char* p13, const char* p14, float p15, float p16, float p17, float p18, float p19, float p20, float p21, float p22, float p23) { return _i<Void>(0x29280002282F1928, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23); }
	static Void draw_sprite_poly2(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float red1, float green1, float blue1, int alpha1, float red2, float green2, float blue2, int alpha2, float red3, float green3, float blue3, int alpha3, const char* textureDict, const char* textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3) { return _i<Void>(0x736D7AA1B750856B, x1, y1, z1, x2, y2, z2, x3, y3, z3, red1, green1, blue1, alpha1, red2, green2, blue2, alpha2, red3, green3, blue3, alpha3, textureDict, textureName, u1, v1, w1, u2, v2, w2, u3, v3, w3); }
	static Void draw_tv_channel(float xPos, float yPos, float xScale, float yScale, float rotation, int red, int green, int blue, int alpha) { return _i<Void>(0xFDDC2B4ED3C69DF0, xPos, yPos, xScale, yScale, rotation, red, green, blue, alpha); }
	static Void enable_alien_blood_vfx(bool Toggle) { return _i<Void>(0x9DCE1F0F78260875, Toggle); }
	static Void enable_clown_blood_vfx(bool toggle) { return _i<Void>(0xD821490579791273, toggle); }
	static Void _0x2C328AF17210F009(float p0) { return _i<Void>(0x2C328AF17210F009, p0); }
	static Void _0x74C180030FDE4B69(bool p0) { return _i<Void>(0x74C180030FDE4B69, p0); }
	static Void enable_movie_subtitles(bool toggle) { return _i<Void>(0x873FA65C778AD970, toggle); }
	static Void _0x5DEBD9C4DC995692() { return _i<Void>(0x5DEBD9C4DC995692); }
	static Void _0x0A123435A26C36CD() { return _i<Void>(0x0A123435A26C36CD); }
	static Void pop_scaleform_movie_function_void() { return _i<Void>(0xC6796A8FFA375E53); }
	static int pop_scaleform_movie_function() { return _i<int>(0xC50AA39A577AF886); }
	static Void end_text_command_scaleform_string() { return _i<Void>(0x362E2D3FE93A9959); }
	static Void end_text_command_scaleform_string2() { return _i<Void>(0xAE4E8157D9ECF087); }
	static Void fade_decals_in_range(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xD77EDADB0420E6E0, p0, p1, p2, p3, p4); }
	static Void _0xC9B18B4619F48F7B(float p0) { return _i<Void>(0xC9B18B4619F48F7B, p0); }
	static Void _0x814AF7DCAACC597B(Any p0) { return _i<Void>(0x814AF7DCAACC597B, p0); }
	static Void _0xBA0127DA25FD54C9(Any p0, Any p1) { return _i<Void>(0xBA0127DA25FD54C9, p0, p1); }
	static Void _0x9B079E5221D984D3(bool p0) { return _i<Void>(0x9B079E5221D984D3, p0); }
	static Void _0xDC459CFA0CCE245B(bool p0) { return _i<Void>(0xDC459CFA0CCE245B, p0); }
	static Void _0xD801CC02177FA3F1() { return _i<Void>(0xD801CC02177FA3F1); }
	static Void _0x6A12D88881435DCA() { return _i<Void>(0x6A12D88881435DCA); }
	static Void _0x0A46AF8A78DC5E0A() { return _i<Void>(0x0A46AF8A78DC5E0A); }
	static Void _0x346EF3ECAAAB149E() { return _i<Void>(0x346EF3ECAAAB149E); }
	static Void get_active_screen_resolution(int* x, int* y) { return _i<Void>(0x873C9F3104101DD3, x, y); }
	static float get_aspect_ratio(bool b) { return _i<float>(0xF1307EF624A80D87, b); }
	static int _0x473151EBC762C6DA() { return _i<int>(0x473151EBC762C6DA); }
	static float get_decal_wash_level(int decal) { return _i<float>(0x323F647679A09103, decal); }
	static Any _0xBB0527EC6341496D() { return _i<Any>(0xBB0527EC6341496D); }
	static bool get_is_hidef() { return _i<bool>(0x84ED31191CC5D2C9); }
	static bool _0x2F09F7976C512404(float xCoord, float yCoord, float zCoord, float p3) { return _i<bool>(0x2F09F7976C512404, xCoord, yCoord, zCoord, p3); }
	static bool get_is_widescreen() { return _i<bool>(0x30CF4BDA4FCB1905); }
	static Any _0x393BD2275CEB7793() { return _i<Any>(0x393BD2275CEB7793); }
	static int return_two(Any p0) { return _i<int>(0x40AFB081F8ADD4EE, p0); }
	static Any _0xDC54A7AF8B3A14EF() { return _i<Any>(0xDC54A7AF8B3A14EF); }
	static Any _0xE59343E9E96529E7() { return _i<Any>(0xE59343E9E96529E7); }
	static Any _0x35FB78DC42B7BD21() { return _i<Any>(0x35FB78DC42B7BD21); }
	static float get_safe_zone_size() { return _i<float>(0xBAF107B6BB2C97F0); }
	static Any _0xD80A80346A45D761(Any p0) { return _i<Any>(0xD80A80346A45D761, p0); }
	static int _0x2DE7EFA66B906036(Any funcData) { return _i<int>(0x2DE7EFA66B906036, funcData); }
	static const char* sitting_tv(int scaleform) { return _i<const char*>(0xE1E258829A885245, scaleform); }
	static float is_particle_fx_delayed_blink() { return _i<float>(0x5CCABFFCA31DDE33); }
	static Any _0xB2EBE8CBC58B90E9() { return _i<Any>(0xB2EBE8CBC58B90E9); }
	static bool get_screen_coord_from_world_coord(float worldX, float worldY, float worldZ, float* screenX, float* screenY) { return _i<bool>(0x34E82F05DF2974F5, worldX, worldY, worldZ, screenX, screenY); }
	static Void get_screen_resolution(int* x, int* y) { return _i<Void>(0x888D57E407E63624, x, y); }
	static Void _0x6DD8F5AA635EB4B2(float p0, float p1, Any* p2, Any* p3) { return _i<Void>(0x6DD8F5AA635EB4B2, p0, p1, p2, p3); }
	static Any _0xCB82A0BF0E3E3265(Any p0) { return _i<Any>(0xCB82A0BF0E3E3265, p0); }
	static Any _0x5B0316762AFD4A64() { return _i<Any>(0x5B0316762AFD4A64); }
	static int _0x1670F8D05056F257(Any* p0) { return _i<int>(0x1670F8D05056F257, p0); }
	static Any _0x0C0C4E81E1AC60A0() { return _i<Any>(0x0C0C4E81E1AC60A0); }
	static Any _0xF5BED327CEA362B1(Any p0) { return _i<Any>(0xF5BED327CEA362B1, p0); }
	static Any _0x0D6CA79EEEBD8CA3() { return _i<Any>(0x0D6CA79EEEBD8CA3); }
	static Any _0x90A78ECAA4E78453() { return _i<Any>(0x90A78ECAA4E78453); }
	static math::vector3<float> get_texture_resolution(const char* textureDict, const char* textureName) { return _i<math::vector3<float>>(0x35736EE65BD00C11, textureDict, textureName); }
	static int get_timecycle_modifier_index() { return _i<int>(0xFDF3D97C674AFB66); }
	static Any _0x459FD2C8D0AB78BC() { return _i<Any>(0x459FD2C8D0AB78BC); }
	static bool _0xEB3DAC2C86001E5E() { return _i<bool>(0xEB3DAC2C86001E5E); }
	static int get_tv_channel() { return _i<int>(0xFC1E275A90D39995); }
	static float get_tv_volume() { return _i<float>(0x2170813D3DD8661B); }
	static bool is_nightvision_active() { return _i<bool>(0x2202A3F42C8E5F79); }
	static bool is_seethrough_active() { return _i<bool>(0x44B80ABAB9D80BD3); }
	static int _0xFE26117A5841B2FF(Vehicle vehicle, Any p1) { return _i<int>(0xFE26117A5841B2FF, vehicle, p1); }
	static Any _0xA4819F5E23E2FFAD() { return _i<Any>(0xA4819F5E23E2FFAD); }
	static math::vector3<float> _0xA4664972A9B8F8BA(Any p0) { return _i<math::vector3<float>>(0xA4664972A9B8F8BA, p0); }
	static Void _0x12995F2E53FFA601(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11) { return _i<Void>(0x12995F2E53FFA601, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static Void _0xA51C4B86B71652AE(bool p0) { return _i<Void>(0xA51C4B86B71652AE, p0); }
	static Void _0x06F761EA47C1D3ED(bool p0) { return _i<Void>(0x06F761EA47C1D3ED, p0); }
	static Void _0xB1BB03742917A5D6(int type, float xPos, float yPos, float zPos, float p4, int red, int green, int blue, int alpha) { return _i<Void>(0xB1BB03742917A5D6, type, xPos, yPos, zPos, p4, red, green, blue, alpha); }
	static Void _0xC0416B061F2B7E5E(bool p0) { return _i<Void>(0xC0416B061F2B7E5E, p0); }
	static Void _0x312342E1A4874F3F(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8) { return _i<Void>(0x312342E1A4874F3F, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Void _0x2485D34E50A22E84(float p0, float p1, float p2) { return _i<Void>(0x2485D34E50A22E84, p0, p1, p2); }
	static Void _0x9CFDD90B2B844BF7(float p0, float p1, float p2, float p3, float p4) { return _i<Void>(0x9CFDD90B2B844BF7, p0, p1, p2, p3, p4); }
	static Void _0xDBAA5EC848BA2D46(Any p0, Any p1) { return _i<Void>(0xDBAA5EC848BA2D46, p0, p1); }
	static Void _0x851CD923176EBA7C() { return _i<Void>(0x851CD923176EBA7C); }
	static Void _0x302C91AB2D477F7E() { return _i<Void>(0x302C91AB2D477F7E); }
	static Void _0x6D955F6A9E0295B1(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x6D955F6A9E0295B1, p0, p1, p2, p3, p4, p5, p6); }
	static bool has_scaleform_container_movie_loaded_into_parent(int scaleformHandle) { return _i<bool>(0x8217150E1217EBFD, scaleformHandle); }
	static bool has_named_scaleform_movie_loaded(const char* scaleformName) { return _i<bool>(0x0C1C5D756FB5F337, scaleformName); }
	static bool has_scaleform_movie_loaded(int scaleformHandle) { return _i<bool>(0x85F01B8D5B90570E, scaleformHandle); }
	static bool has_hud_scaleform_loaded(int hudComponent) { return _i<bool>(0xDF6E5987D2B4D140, hudComponent); }
	static bool has_streamed_texture_dict_loaded(const char* textureDict) { return _i<bool>(0x0145F696AAAAD2E4, textureDict); }
	static bool is_decal_alive(int decal) { return _i<bool>(0xC694D74949CAFD0C, decal); }
	static bool _0x768FF8961BA904D6(Any funcData) { return _i<bool>(0x768FF8961BA904D6, funcData); }
	static Any _0x7B226C785A52A0A9() { return _i<Any>(0x7B226C785A52A0A9); }
	static bool is_tracked_point_visible(Object point) { return _i<bool>(0xC45CCDAAC9221CA8, point); }
	static bool load_tv_channel(uint32_t tvChannel) { return _i<bool>(0x0AD973CA1E077B60, tvChannel); }
	static bool _0x4862437A486F91B0(Any* p0, Any p1, Any p2, Any p3) { return _i<bool>(0x4862437A486F91B0, p0, p1, p2, p3); }
	static int load_movie_mesh_set(const char* movieMeshSetName) { return _i<int>(0xB66064452270E8F1, movieMeshSetName); }
	static Void move_vehicle_decals(Any p0, Any p1) { return _i<Void>(0x84C8D7C2D30D3280, p0, p1); }
	static Void _0xEFB55E7C25D3B3BE() { return _i<Void>(0xEFB55E7C25D3B3BE); }
	static Void _0x1600FD8CF72EBC12(float p0) { return _i<Void>(0x1600FD8CF72EBC12, p0); }
	static Void _0x2A2A52824DB96700(Any* p0) { return _i<Void>(0x2A2A52824DB96700, p0); }
	static Any _0x95EB5E34F821BABE(Any p0, Any p1, Any p2) { return _i<Any>(0x95EB5E34F821BABE, p0, p1, p2); }
	static bool _0xD1C7CB175E012964(int scaleformHandle) { return _i<bool>(0xD1C7CB175E012964, scaleformHandle); }
	static Void _0x8A35C742130C6080(Any p0, Any* p1, Any* p2) { return _i<Void>(0x8A35C742130C6080, p0, p1, p2); }
	static Any _0xBCEDB009461DA156() { return _i<Any>(0xBCEDB009461DA156); }
	static bool _0x27FEB5254759CDE3(const char* textureDict, bool p1) { return _i<bool>(0x27FEB5254759CDE3, textureDict, p1); }
	static bool _0x7AC24EAB6D74118D(bool p0) { return _i<bool>(0x7AC24EAB6D74118D, p0); }
	static Void pop_timecycle_modifier() { return _i<Void>(0x3C8938D7D872211E); }
	static Void _0xD7021272EB0A451E(const char* p0) { return _i<Void>(0xD7021272EB0A451E, p0); }
	static Void _0x0218BA067D249DEA() { return _i<Void>(0x0218BA067D249DEA); }
	static Void _0x649C97D52332341A(Any p0) { return _i<Void>(0x649C97D52332341A, p0); }
	static Void _0x14FC5833464340A8() { return _i<Void>(0x14FC5833464340A8); }
	static Void _0xAE51BC858F32BA66(Any p0, float p1, float p2, float p3, float p4) { return _i<Void>(0xAE51BC858F32BA66, p0, p1, p2, p3, p4); }
	static Any _0x2C42340F916C5930(Any p0) { return _i<Any>(0x2C42340F916C5930, p0); }
	static Void push_timecycle_modifier() { return _i<Void>(0x58F735290861E6B4); }
	static Any _0x9B6E70C5CEEF4EEB(Any p0) { return _i<Any>(0x9B6E70C5CEEF4EEB, p0); }
	static Any _0x2A893980E96B659A(Any p0) { return _i<Any>(0x2A893980E96B659A, p0); }
	static Void _0xA44FF770DFBC5DAE() { return _i<Void>(0xA44FF770DFBC5DAE); }
	static Void release_movie_mesh_set(int movieMeshSet) { return _i<Void>(0xEB119AA014E89183, movieMeshSet); }
	static Void remove_decal(int decal) { return _i<Void>(0xED3F346429CCD659, decal); }
	static Void remove_decals_from_object(Object obj) { return _i<Void>(0xCCF71CBDDF5B6CB9, obj); }
	static Void remove_decals_from_object_facing(Object obj, float x, float y, float z) { return _i<Void>(0xA6F6F70FDC6D144C, obj, x, y, z); }
	static Void remove_decals_from_vehicle(Vehicle vehicle) { return _i<Void>(0xE91F1B65F2B48D57, vehicle); }
	static Void remove_decals_in_range(float x, float y, float z, float range) { return _i<Void>(0x5D6B2D4830A67C62, x, y, z, range); }
	static Void remove_particle_fx(int ptfxHandle, bool p1) { return _i<Void>(0xC401503DFE8D53CF, ptfxHandle, p1); }
	static Void remove_particle_fx_from_entity(Entity entity) { return _i<Void>(0xB8FEAEEBCC127425, entity); }
	static Void remove_particle_fx_in_range(float X, float Y, float Z, float radius) { return _i<Void>(0xDD19FA1C6D657305, X, Y, Z, radius); }
	static Void _0xF44A5456AC3F4F97(Any p0) { return _i<Void>(0xF44A5456AC3F4F97, p0); }
	static Void _0xD2300034310557E4(Vehicle vehicle, Any p1) { return _i<Void>(0xD2300034310557E4, vehicle, p1); }
	static Void _0x03300B57FCAC6DDB(bool p0) { return _i<Void>(0x03300B57FCAC6DDB, p0); }
	static Void _0x98EDF76A7271E4F2() { return _i<Void>(0x98EDF76A7271E4F2); }
	static int request_scaleform_movie(const char* scaleformName) { return _i<int>(0x11FE353CF9733E6F, scaleformName); }
	static int request_scaleform_movie_instance(const char* scaleformName) { return _i<int>(0xC514489CFB8AF806, scaleformName); }
	static int request_scaleform_movie_interactive(const char* scaleformName) { return _i<int>(0xBD06C611BB9048C2, scaleformName); }
	static Any request_scaleform_movie2(const char* scaleformName) { return _i<Any>(0x65E7E78842E74CDB, scaleformName); }
	static Void request_hud_scaleform(int hudComponent) { return _i<Void>(0x9304881D6F6537EA, hudComponent); }
	static Void request_streamed_texture_dict(const char* textureDict, bool p1) { return _i<Void>(0xDFA2EF8E04127DD5, textureDict, p1); }
	static Void _0xE3E2C1B4C59DBC77(int unk) { return _i<Void>(0xE3E2C1B4C59DBC77, unk); }
	static Void reset_particle_fx_asset_old_to_new(const char* name) { return _i<Void>(0x89C8553DD3274AAE, name); }
	static Void _0xE1C8709406F2C41C() { return _i<Void>(0xE1C8709406F2C41C); }
	static Void screen_draw_position_end() { return _i<Void>(0xE3A3DB414A373DAB); }
	static Any _0x3DEC726C25A11BAC(int p0) { return _i<Any>(0x3DEC726C25A11BAC, p0); }
	static Void push_scaleform_movie_function_parameter_bool(bool value) { return _i<Void>(0xC58424BA936EB458, value); }
	static Void push_scaleform_movie_function_parameter_float(float value) { return _i<Void>(0xD69736AAE04DB51A, value); }
	static Void push_scaleform_movie_function_parameter_int(int value) { return _i<Void>(0xC3D0841A0CC546A6, value); }
	static Void _0xEC52C631A1831C03(Any p0) { return _i<Void>(0xEC52C631A1831C03, p0); }
	static Void _0x77FE3402004CD1B0(Any p0) { return _i<Void>(0x77FE3402004CD1B0, p0); }
	static Void push_scaleform_movie_function_parameter_string(const char* value) { return _i<Void>(0xBA7148484BD90365, value); }
	static Void _0xE83A3E3557A56640(const char* button_option) { return _i<Void>(0xE83A3E3557A56640, button_option); }
	static Void _0x70A64C0234EF522C() { return _i<Void>(0x70A64C0234EF522C); }
	static Void _0x1086127B3A63505E(Any p0, Any p1, Any p2) { return _i<Void>(0x1086127B3A63505E, p0, p1, p2); }
	static Void _0x9D75795B9DC6EBBF(Any p0) { return _i<Void>(0x9D75795B9DC6EBBF, p0); }
	static Void _0xA78DE25577300BA1(Any p0) { return _i<Void>(0xA78DE25577300BA1, p0); }
	static Void _0xD7D0B00177485411(Any p0, float p1) { return _i<Void>(0xD7D0B00177485411, p0, p1); }
	static Void _0x1636D7FC127B10D2(Any p0) { return _i<Void>(0x1636D7FC127B10D2, p0); }
	static Void _0x19E50EB6E33E1D28(Any p0) { return _i<Void>(0x19E50EB6E33E1D28, p0); }
	static Void _0x0C8FAC83902A62DF(Any p0) { return _i<Void>(0x0C8FAC83902A62DF, p0); }
	static Void _0xFEBFBFDFB66039DE(Any p0) { return _i<Void>(0xFEBFBFDFB66039DE, p0); }
	static Void _0xFF5992E1C9E65D05(Any p0) { return _i<Void>(0xFF5992E1C9E65D05, p0); }
	static Void set_blackout(bool enable) { return _i<Void>(0x1268615ACE24D504, enable); }
	static Void _0x23BA6B0C2AD7B0D3(bool p0) { return _i<Void>(0x23BA6B0C2AD7B0D3, p0); }
	static Void _0xF51D36185993515D(int checkpoint, float posX, float posY, float posZ, float unkX, float unkY, float unkZ) { return _i<Void>(0xF51D36185993515D, checkpoint, posX, posY, posZ, unkX, unkY, unkZ); }
	static Void set_checkpoint_cylinder_height(int checkpoint, float nearHeight, float farHeight, float radius) { return _i<Void>(0x2707AAE9D9297D89, checkpoint, nearHeight, farHeight, radius); }
	static Void _0x615D3925E87A3B26(int checkpoint) { return _i<Void>(0x615D3925E87A3B26, checkpoint); }
	static Void _0x3C788E7F6438754D(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x3C788E7F6438754D, p0, p1, p2, p3); }
	static Void _0xDB1EA9411C8911EC(Any p0) { return _i<Void>(0xDB1EA9411C8911EC, p0); }
	static Void _0x4B5B4DA5D79F1943(int checkpoint, float p0) { return _i<Void>(0x4B5B4DA5D79F1943, checkpoint, p0); }
	static Void _0x44621483FF966526(Any p0, Any p1) { return _i<Void>(0x44621483FF966526, p0, p1); }
	static Void set_checkpoint_icon_rgba(int checkpoint, int red, int green, int blue, int alpha) { return _i<Void>(0xB9EA40907C680580, checkpoint, red, green, blue, alpha); }
	static Void set_checkpoint_rgba(int checkpoint, int red, int green, int blue, int alpha) { return _i<Void>(0x7167371E8AD747F7, checkpoint, red, green, blue, alpha); }
	static Void _0xBBF327DED94E4DEB(const char* p0) { return _i<Void>(0xBBF327DED94E4DEB, p0); }
	static Void _0x46D1A61A21F566FC(float p0) { return _i<Void>(0x46D1A61A21F566FC, p0); }
	static Void _0xC5C8F970D4EDFF71(Any p0) { return _i<Void>(0xC5C8F970D4EDFF71, p0); }
	static Void _0x4B5CFC83122DF602() { return _i<Void>(0x4B5CFC83122DF602); }
	static Void _0xD9454B5752C857DC() { return _i<Void>(0xD9454B5752C857DC); }
	static Void _0x27CFB1B1E078CB2D() { return _i<Void>(0x27CFB1B1E078CB2D); }
	static Void _0xE2892E7E55D7073A(float p0) { return _i<Void>(0xE2892E7E55D7073A, p0); }
	static Void set_draw_origin(float x, float y, float z, bool screen) { return _i<Void>(0xAA0008F3BBB8F416, x, y, z, screen); }
	static Void set_entity_icon_color(Entity entity, int red, int green, int blue, int alpha) { return _i<Void>(0x1D5F595CCAE2E238, entity, red, green, blue, alpha); }
	static Void set_entity_icon_visibility(Entity entity, bool toggle) { return _i<Void>(0xE0E8BEECCA96BA31, entity, toggle); }
	static Void _0xEF398BEEE4EF45F9(bool p0) { return _i<Void>(0xEF398BEEE4EF45F9, p0); }
	static Void _0x5096FD9CCB49056D(Any* p0) { return _i<Void>(0x5096FD9CCB49056D, p0); }
	static Void set_flash(float p0, float p1, float fadeIn, float duration, float fadeOut) { return _i<Void>(0x0AB84296FED9CFC6, p0, p1, fadeIn, duration, fadeOut); }
	static Void _0x6A51F78772175A51(Any p0) { return _i<Void>(0x6A51F78772175A51, p0); }
	static Void _0xBA3D65906822BED5(bool p0, bool p1, float p2, float p3, float p4, float p5) { return _i<Void>(0xBA3D65906822BED5, p0, p1, p2, p3, p4, p5); }
	static Void _0x9641588DAB93B4B5(Any p0) { return _i<Void>(0x9641588DAB93B4B5, p0); }
	static Void _0xB569F41F3E7E83A4(Any p0) { return _i<Void>(0xB569F41F3E7E83A4, p0); }
	static Void _0xB3C641F3630BF6DA(float p0) { return _i<Void>(0xB3C641F3630BF6DA, p0); }
	static Void _0xBF59707B3E5ED531(const char* p0) { return _i<Void>(0xBF59707B3E5ED531, p0); }
	static Void set_nightvision(bool toggle) { return _i<Void>(0x18F621F7A5B1F85D, toggle); }
	static Void set_noiseoveride(bool toggle) { return _i<Void>(0xE787BF1C5CF823C9, toggle); }
	static Void set_noisinessoveride(float value) { return _i<Void>(0xCB6A7C3BB17A0C67, value); }
	static Void _0x54E22EA2C1956A8D(float p0) { return _i<Void>(0x54E22EA2C1956A8D, p0); }
	static Void _0x908311265D42A820(Any p0) { return _i<Void>(0x908311265D42A820, p0); }
	static Void _0xBB90E12CAC1DAB25(float p0) { return _i<Void>(0xBB90E12CAC1DAB25, p0); }
	static Void _0x27E32866E9A5C416(float p0) { return _i<Void>(0x27E32866E9A5C416, p0); }
	static Void _0xCA4AE345A153D573(bool p0) { return _i<Void>(0xCA4AE345A153D573, p0); }
	static Void set_particle_fx_cam_inside_nonplayer_vehicle(Any p0, bool p1) { return _i<Void>(0xACEE6F360FC1F6B6, p0, p1); }
	static Void set_particle_fx_cam_inside_vehicle(bool p0) { return _i<Void>(0xEEC4047028426510, p0); }
	static Void _0x949F397A288B28B3(float p0) { return _i<Void>(0x949F397A288B28B3, p0); }
	static Void _0xBA3D194057C79A7B(Any p0) { return _i<Void>(0xBA3D194057C79A7B, p0); }
	static Void _0x8CDE909A0370BB3A(bool p0) { return _i<Void>(0x8CDE909A0370BB3A, p0); }
	static Void set_particle_fx_looped_alpha(int ptfxHandle, float alpha) { return _i<Void>(0x726845132380142E, ptfxHandle, alpha); }
	static Void set_particle_fx_looped_colour(int ptfxHandle, float r, float g, float b, bool p4) { return _i<Void>(0x7F8F65877F88783B, ptfxHandle, r, g, b, p4); }
	static Void set_particle_fx_looped_evolution(int ptfxHandle, const char* propertyName, float amount, bool Id) { return _i<Void>(0x5F0C4B5B1C393BE2, ptfxHandle, propertyName, amount, Id); }
	static Void set_particle_fx_looped_range(int ptfxHandle, float range) { return _i<Void>(0xDCB194B85EF7B541, ptfxHandle, range); }
	static Void set_particle_fx_looped_offsets(int ptfxHandle, float x, float y, float z, float rotX, float rotY, float rotZ) { return _i<Void>(0xF7DDEBEC43483C43, ptfxHandle, x, y, z, rotX, rotY, rotZ); }
	static Void set_particle_fx_looped_scale(int ptfxHandle, float scale) { return _i<Void>(0xB44250AAA456492D, ptfxHandle, scale); }
	static Void set_particle_fx_non_looped_alpha(float alpha) { return _i<Void>(0x77168D722C58B2FC, alpha); }
	static Void set_particle_fx_non_looped_colour(float r, float g, float b) { return _i<Void>(0x26143A59EF48B262, r, g, b); }
	static Void set_particle_fx_asset_old_to_new(const char* oldAsset, const char* newAsset) { return _i<Void>(0xEA1E2D93F6F75ED9, oldAsset, newAsset); }
	static Void set_particle_fx_shootout_boat(Any p0) { return _i<Void>(0x96EF97DAEB89BEF5, p0); }
	static Void _0x2B40A97646381508(Any p0) { return _i<Void>(0x2B40A97646381508, p0); }
	static Void _0xBDEB86F4D5809204(float p0) { return _i<Void>(0xBDEB86F4D5809204, p0); }
	static Void set_scaleform_movie_as_no_longer_needed(int* scaleformHandle) { return _i<Void>(0x1D132D614DD86811, scaleformHandle); }
	static Void _0x32F34FF7F617643B(Any p0, Any p1) { return _i<Void>(0x32F34FF7F617643B, p0, p1); }
	static Void _0xE6A9F00D4240B519(Any p0, Any p1) { return _i<Void>(0xE6A9F00D4240B519, p0, p1); }
	static Void set_scaleform_movie_to_use_system_time(int scaleform, bool toggle) { return _i<Void>(0x6D8EB211944DCE08, scaleform, toggle); }
	static Void screen_draw_position_begin(int x, int y) { return _i<Void>(0xB8A850F20A067EB6, x, y); }
	static Void screen_draw_position_ratio(float x, float y, float p2, float p3) { return _i<Void>(0xF5A2C681787E579D, x, y, p2, p3); }
	static Void _0xC6372ECD45D73BCD(bool p0) { return _i<Void>(0xC6372ECD45D73BCD, p0); }
	static Void set2_d_layer(int layer) { return _i<Void>(0x61BB1D9B3A95D802, layer); }
	static Void set_seethrough(bool toggle) { return _i<Void>(0x7E08924259E08CE0, toggle); }
	static Void _0x5DBF05DB5926D089(Any p0) { return _i<Void>(0x5DBF05DB5926D089, p0); }
	static Void set_streamed_texture_dict_as_no_longer_needed(const char* textureDict) { return _i<Void>(0xBE2CACCF5A8AA805, textureDict); }
	static Void _0x1BBC135A4D25EDDE(bool p0) { return _i<Void>(0x1BBC135A4D25EDDE, p0); }
	static Void set_timecycle_modifier(const char* modifierName) { return _i<Void>(0x2C933ABF17A1DF41, modifierName); }
	static Void set_timecycle_modifier_strength(float strength) { return _i<Void>(0x82E7FFCD5B2326B3, strength); }
	static Void set_tracked_point_info(Object point, float x, float y, float z, float radius) { return _i<Void>(0x164ECBB3CF750CB0, point, x, y, z, radius); }
	static Void _0x1CBA05AE7BD7EE05(float p0) { return _i<Void>(0x1CBA05AE7BD7EE05, p0); }
	static Void set_transition_timecycle_modifier(const char* modifierName, float transition) { return _i<Void>(0x3BCF567485E1971C, modifierName, transition); }
	static Void set_tv_audio_frontend(bool toggle) { return _i<Void>(0x113D2C5DC57E1774, toggle); }
	static Void set_tv_channel(int channel) { return _i<Void>(0xBAABBB23EB6E484E, channel); }
	static Void _0xF7B38B8305F1FE8B(int p0, const char* p1, bool p2) { return _i<Void>(0xF7B38B8305F1FE8B, p0, p1, p2); }
	static Void _0x2201C576FACAEBE8(Any p0, const char* p1, Any p2) { return _i<Void>(0x2201C576FACAEBE8, p0, p1, p2); }
	static Void _0xD1C55B110E4DF534(Any p0) { return _i<Void>(0xD1C55B110E4DF534, p0); }
	static Void set_tv_volume(float volume) { return _i<Void>(0x2982BF73F66E9DDC, volume); }
	static Void _0xF78B803082D4386F(float p0) { return _i<Void>(0xF78B803082D4386F, p0); }
	static Void _0xA46B73FAA3460AE1(bool p0) { return _i<Void>(0xA46B73FAA3460AE1, p0); }
	static int start_particle_fx_looped_on_entity2(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, Any p12, Any p13, Any p14) { return _i<int>(0x6F60E89A7B64EE1D, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p12, p13, p14); }
	static int start_particle_fx_looped_on_entity_bone2(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis, Any p13, Any p14, Any p15) { return _i<int>(0xDDE23F30CC5A0F03, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis, p13, p14, p15); }
	static bool start_particle_fx_non_looped_at_coord2(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis) { return _i<bool>(0xF56B8137DF10135D, effectName, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis); }
	static bool start_particle_fx_non_looped_on_entity2(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ) { return _i<bool>(0xC95EB1DB6E92113D, effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ); }
	static bool start_particle_fx_non_looped_on_ped_bone2(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ) { return _i<bool>(0xA41B6A43642AC2CF, effectName, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	static int start_particle_fx_looped_at_coord(const char* effectName, float x, float y, float z, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11) { return _i<int>(0xE184F4F0DC5910E7, effectName, x, y, z, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11); }
	static int start_particle_fx_looped_on_entity(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis) { return _i<int>(0x1AE42C1660FD6517, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis); }
	static int start_particle_fx_looped_on_entity_bone(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis) { return _i<int>(0xC6EB449E33977F0B, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis); }
	static int start_particle_fx_looped_on_ped_bone(const char* effectName, Ped ped, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis) { return _i<int>(0xF28DA9F38CD1787C, effectName, ped, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis); }
	static int start_particle_fx_non_looped_at_coord(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis) { return _i<int>(0x25129531F77B9ED3, effectName, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis); }
	static bool start_particle_fx_non_looped_on_entity(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ) { return _i<bool>(0x0D53A3B8DA0809D2, effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ); }
	static bool start_particle_fx_non_looped_on_ped_bone(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ) { return _i<bool>(0x0E7E72961BA18619, effectName, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	static Void _0x99AC7F0D8B9C893D(float p0) { return _i<Void>(0x99AC7F0D8B9C893D, p0); }
	static Void stop_particle_fx_looped(int ptfxHandle, bool p1) { return _i<Void>(0x8F75998877616996, ptfxHandle, p1); }
	static Void _0xA356990E161C9E65(bool p0) { return _i<Void>(0xA356990E161C9E65, p0); }
	static Void _0x5CE62918F8D703C7(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11) { return _i<Void>(0x5CE62918F8D703C7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static Void _0x1C4FC5752BCD8E48(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12) { return _i<Void>(0x1C4FC5752BCD8E48, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	static Void set_frozen_rendering_disabled(bool enabled) { return _i<Void>(0xDFC252D8A3E15AB7, enabled); }
	static Void _0xE63D7C6EECECB66B(bool p0) { return _i<Void>(0xE63D7C6EECECB66B, p0); }
	static bool transition_to_blurred(float transitionTime) { return _i<bool>(0xA328A24AAA6B7FDC, transitionTime); }
	static bool transition_from_blurred(float transitionTime) { return _i<bool>(0xEFACC8AEF94430D5, transitionTime); }
	static bool _0x98C4FE6EC34154CA(const char* p0, Ped ped, int p2, float posX, float posY, float posZ) { return _i<bool>(0x98C4FE6EC34154CA, p0, ped, p2, posX, posY, posZ); }
	static Void _0x7A42B2E236E71415() { return _i<Void>(0x7A42B2E236E71415); }
	static bool ui3dscene_is_available() { return _i<bool>(0xD3A10FC7FD8D98CD); }
	static Void _0x108BE26959A9D9BB(bool p0) { return _i<Void>(0x108BE26959A9D9BB, p0); }
	static bool _0xF1CEA8A4198D8E9A(const char* p0) { return _i<bool>(0xF1CEA8A4198D8E9A, p0); }
	static Void _0xB7ED70C49521A61D(Any p0) { return _i<Void>(0xB7ED70C49521A61D, p0); }
	static Void _0xDEADC0DEDEADC0DE(Object object) { return _i<Void>(0xDEADC0DEDEADC0DE, object); }
	static Void use_particle_fx_asset_next_call(const char* name) { return _i<Void>(0x6C38AF3693A69A91, name); }
	static Void set_force_ped_footsteps_tracks(bool toggle) { return _i<Void>(0xAEEDAD1420C65CC0, toggle); }
	static Void set_force_vehicle_trails(bool toggle) { return _i<Void>(0x4CC7F0FEA5283FE0, toggle); }
	static Void wash_decals_from_vehicle(Vehicle vehicle, float p1) { return _i<Void>(0x5B712761429DBC14, vehicle, p1); }
	static Void wash_decals_in_range(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x9C30613D50A6ADEF, p0, p1, p2, p3, p4); }
	static Void _0xCA465D9CC0D231BA(Any p0) { return _i<Void>(0xCA465D9CC0D231BA, p0); }
	static int get_maximum_number_of_photos() { return _i<int>(0x34D23450F028B0BF); }
	static Any _0xE791DF1F73ED2C8B(Any p0) { return _i<Any>(0xE791DF1F73ED2C8B, p0); }
	static Any _0xEC72C258667BE5EA(Any p0) { return _i<Any>(0xEC72C258667BE5EA, p0); }
	static Any _0xBE197EAA669238F4(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xBE197EAA669238F4, p0, p1, p2, p3); }
	static Void set_debug_lines_and_spheres_drawing_active(bool enabled) { return _i<Void>(0x175B6BFC15CDD0C5, enabled); }
	static Void _0x7FDFADE676AA3CB0(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Void>(0x7FDFADE676AA3CB0, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void draw_debug_line_with_two_colours(float x1, float y1, float z1, float x2, float y2, float z2, int r1, int g1, int b1, int r2, int g2, int b2, int alpha1, int alpha2) { return _i<Void>(0xD8B9A8AC5608FF94, x1, y1, z1, x2, y2, z2, r1, g1, b1, r2, g2, b2, alpha1, alpha2); }
	static Void draw_debug_sphere(float x, float y, float z, float radius, int red, int green, int blue, int alpha) { return _i<Void>(0xAAD68E1AB39DA632, x, y, z, radius, red, green, blue, alpha); }
	static Void draw_debug_box(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha) { return _i<Void>(0x083A2CA4F2E573BD, x1, y1, z1, x2, y2, z2, red, green, blue, alpha); }
	static Void draw_debug_cross(float x, float y, float z, float size, int red, int green, int blue, int alpha) { return _i<Void>(0x73B1189623049839, x, y, z, size, red, green, blue, alpha); }
	static Void draw_debug_text(const char* text, float x, float y, float z, int red, int green, int blue, int alpha) { return _i<Void>(0x3903E216620488E8, text, x, y, z, red, green, blue, alpha); }
	static Void draw_debug_text2_d(const char* text, float x, float y, float z, int red, int green, int blue, int alpha) { return _i<Void>(0xA3BB2E9555C05A8F, text, x, y, z, red, green, blue, alpha); }
	static Void _0x61F95E5BB3E0A8C6(Any p0) { return _i<Void>(0x61F95E5BB3E0A8C6, p0); }

	static Void activate_frontend_menu(uint32_t menuhash, bool Toggle_Pause, int component) { return _i<Void>(0xEF01D36B9C9D0C7B, menuhash, Toggle_Pause, component); }
	static Any _0xCE5D0E5E315DB238(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Any>(0xCE5D0E5E315DB238, p0, p1, p2, p3, p4); }
	static Blip add_blip_for_coord(float x, float y, float z) { return _i<Blip>(0x5A039BB0BCA604B6, x, y, z); }
	static Blip add_blip_for_entity(Entity entity) { return _i<Blip>(0x5CDE92C702A8FCE7, entity); }
	static Blip add_blip_for_pickup(Pickup pickup) { return _i<Blip>(0xBE339365C863BD36, pickup); }
	static Blip add_blip_for_radius(float posX, float posY, float posZ, float radius) { return _i<Blip>(0x46818D79B1F7499A, posX, posY, posZ, radius); }
	static Void add_next_message_to_previous_briefs(bool p0) { return _i<Void>(0x60296AF4BA14ABC5, p0); }
	static Void _0x311438A071DD9B1A(Any p0, Any p1, Any p2) { return _i<Void>(0x311438A071DD9B1A, p0, p1, p2); }
	static Void _0xA905192A6781C41B(float x, float y, float z) { return _i<Void>(0xA905192A6781C41B, x, y, z); }
	static Void add_text_component_float(float value, int decimalPlaces) { return _i<Void>(0xE7DCB5B874BCD96E, value, decimalPlaces); }
	static Void add_text_component_formatted_integer(int value, bool commaSeparated) { return _i<Void>(0x0E4C749FF9DE9CC4, value, commaSeparated); }
	static Void add_text_component_integer(int value) { return _i<Void>(0x03B504CF259931BC, value); }
	static Void add_text_component_substring_blip_name(Blip blip) { return _i<Void>(0x80EAD8E2E1D5D52E, blip); }
	static Void add_text_component_substring_player_name(const char* text) { return _i<Void>(0x6C188BE134E074AA, text); }
	static Void add_text_component_substring_website(const char* website) { return _i<Void>(0x94CF4AC034C9C986, website); }
	static Void add_text_component_scaleform(const char* p0) { return _i<Void>(0x5F68520888E69014, p0); }
	static Void add_text_component_app_title(const char* p0, int p1) { return _i<Void>(0x761B77454205A61D, p0, p1); }
	static Void add_text_component_substring_text_label(const char* labelName) { return _i<Void>(0xC63CD5D2920ACBE7, labelName); }
	static Void add_text_component_substring_text_label_hash_key(uint32_t gxtEntryHash) { return _i<Void>(0x17299B63C7683A2B, gxtEntryHash); }
	static Void add_text_component_substring_time(int timestamp, int flags) { return _i<Void>(0x1115F16B8AB9E8BF, timestamp, flags); }
	static Void _0xE67C6DFD386EA5E7(bool p0) { return _i<Void>(0xE67C6DFD386EA5E7, p0); }
	static Void _0xCC3FDDED67BCFC63() { return _i<Void>(0xCC3FDDED67BCFC63); }
	static Void _0x60734CC207C9833C(bool p0) { return _i<Void>(0x60734CC207C9833C, p0); }
	static Any _0xF13FE2A80C05C561() { return _i<Any>(0xF13FE2A80C05C561); }
	static Void begin_text_command_objective(const char* p0) { return _i<Void>(0x23D69E0465570028, p0); }
	static Void set_loading_prompt_text_entry(const char* string) { return _i<Void>(0xABA17D7CE615ADBF, string); }
	static Void begin_text_command_clear_print(const char* text) { return _i<Void>(0xE124FA80A759019C, text); }
	static Void begin_text_command_display_help(const char* inputType) { return _i<Void>(0x8509B634FBE7DA11, inputType); }
	static Void begin_text_command_display_text(const char* text) { return _i<Void>(0x25FBB336DF1804CB, text); }
	static Void begin_text_command_line_count(const char* entry) { return _i<Void>(0x521FB041D93DD0E4, entry); }
	static Void begin_text_command_width(const char* text) { return _i<Void>(0x54CE8AC98E120CAB, text); }
	static Void begin_text_command_is_message_displayed(const char* text) { return _i<Void>(0x853648FD1063A213, text); }
	static Void begin_text_command_is_this_help_message_being_displayed(const char* labelName) { return _i<Void>(0x0A24DA3A41B718F5, labelName); }
	static Void begin_text_command_timer(const char* p0) { return _i<Void>(0x8F9EE5687F8EECCD, p0); }
	static Void begin_text_command_print(const char* GxtEntry) { return _i<Void>(0xB87A37EEB7FAA67D, GxtEntry); }
	static Void begin_text_command_set_blip_name(const char* gxtentry) { return _i<Void>(0xF9113A30DE5C6670, gxtentry); }
	static Void begin_text_command_thefeed_post(const char* type) { return _i<Void>(0x202709F4C58A0424, type); }
	static Any _0xB2A592B04648A9CB() { return _i<Any>(0xB2A592B04648A9CB); }
	static bool is_loading_prompt_being_displayed() { return _i<bool>(0xD422FCC5F239A915); }
	static Void remove_loading_prompt() { return _i<Void>(0x10D373323E5B9C0D); }
	static Void set_player_cash_change(int cash, int bank) { return _i<Void>(0x0772DF77852C2E30, cash, bank); }
	static Void clear_additional_text(int p0, bool p1) { return _i<Void>(0x2A179DF17CCF04CD, p0, p1); }
	static Void _0xD12882D3FF82BF11() { return _i<Void>(0xD12882D3FF82BF11); }
	static Void clear_all_help_messages() { return _i<Void>(0x6178F68A87A4D3A0); }
	static Void clear_brief() { return _i<Void>(0x9D292F73ADBD9313); }
	static Void _0x7792424AA0EAC32E() { return _i<Void>(0x7792424AA0EAC32E); }
	static Void clear_floating_help(Any p0, bool p1) { return _i<Void>(0x50085246ABD3FEFA, p0, p1); }
	static Void _0xE6DE0561D9232A64() { return _i<Void>(0xE6DE0561D9232A64); }
	static Void clear_gps_flags() { return _i<Void>(0x21986729D6A3A830); }
	static Void _0x67EEDEA1B9BAFD94() { return _i<Void>(0x67EEDEA1B9BAFD94); }
	static Void clear_gps_player_waypoint() { return _i<Void>(0xFF4FB7C8CDFA3DA7); }
	static Void clear_gps_race_track() { return _i<Void>(0x7AA5B4CE533C858B); }
	static Void clear_help(bool toggle) { return _i<Void>(0x8DFCED7A656F8802, toggle); }
	static Void clear_ped_in_pause_menu() { return _i<Void>(0x5E62BE5DC58E9E06); }
	static Void clear_prints() { return _i<Void>(0xCC33FA791322B9D9); }
	static Void clear_small_prints() { return _i<Void>(0x2CEA2839313C09AC); }
	static Void clear_this_print(const char* p0) { return _i<Void>(0xCF708001E1E536DD, p0); }
	static Void abort_text_chat() { return _i<Void>(0x1AC8F4AD40E22127); }
	static Void _0xD2B32BE3FC1626C6() { return _i<Void>(0xD2B32BE3FC1626C6); }
	static Any _0x66E7CB63C97B7D20() { return _i<Any>(0x66E7CB63C97B7D20); }
	static int create_mp_gamer_tag(Ped ped, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, Any p5) { return _i<int>(0xBFEFE3321A3F5015, ped, username, pointedClanTag, isRockstarClan, clanTag, p5); }
	static Void set_mp_gamer_tag_color(int headDisplayId, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, Any p5, int r, int g, int b) { return _i<Void>(0x6DD05E9D83EFA4C9, headDisplayId, username, pointedClanTag, isRockstarClan, clanTag, p5, r, g, b); }
	static Void _0x2708FC083123F9FF() { return _i<Void>(0x2708FC083123F9FF); }
	static Any _0x551DF99658DB6EE8(float p0, float p1, float p2) { return _i<Any>(0x551DF99658DB6EE8, p0, p1, p2); }
	static Void set_map_full_screen(bool toggle) { return _i<Void>(0x5354C5BA2EA868A4, toggle); }
	static Void _0x1EAE6DD17B7A5EFA(Any p0) { return _i<Void>(0x1EAE6DD17B7A5EFA, p0); }
	static Void _0xD8E694757BCEA8E9() { return _i<Void>(0xD8E694757BCEA8E9); }
	static Void disable_frontend_this_frame() { return _i<Void>(0x6D3465A73092F0E6); }
	static Void _0x9245E81072704B8A(bool p0) { return _i<Void>(0x9245E81072704B8A, p0); }
	static Void display_ammo_this_frame(bool display) { return _i<Void>(0xA5E78BA2B1331C55, display); }
	static Void display_area_name(bool toggle) { return _i<Void>(0x276B6CE369C33678, toggle); }
	static Void display_cash(bool toggle) { return _i<Void>(0x96DEC8D5430208B7, toggle); }
	static Void display_help_text_this_frame(const char* message, bool p1) { return _i<Void>(0x960C9FF8F616E41C, message, p1); }
	static Void display_hud(bool toggle) { return _i<Void>(0xA6294919E56FF02A, toggle); }
	static Void _0x7669F9E39DC17063() { return _i<Void>(0x7669F9E39DC17063); }
	static Void _0x402F9ED62087E898() { return _i<Void>(0x402F9ED62087E898); }
	static Void _0x82CEDC33687E1F50(bool p0) { return _i<Void>(0x82CEDC33687E1F50, p0); }
	static Void display_radar(bool Toggle) { return _i<Void>(0xA0EBB943C300E693, Toggle); }
	static Void display_sniper_scope_this_frame() { return _i<Void>(0x73115226F4814E62); }
	static bool does_blip_exist(Blip blip) { return _i<bool>(0xA6DB27D19ECBB7DA, blip); }
	static bool _0xDD2238F57B977751(Any p0) { return _i<bool>(0xDD2238F57B977751, p0); }
	static bool does_ped_have_ai_blip(Ped ped) { return _i<bool>(0x15B8ECF844EE67ED, ped); }
	static bool does_text_block_exist(const char* gxt) { return _i<bool>(0x1C7302E725259789, gxt); }
	static bool does_text_label_exist(const char* gxt) { return _i<bool>(0xAC09CA973C564252, gxt); }
	static Void center_player_on_radar_this_frame() { return _i<Void>(0x6D14BFDC33B34F55); }
	static Void _0x55F5A5F07134DE60() { return _i<Void>(0x55F5A5F07134DE60); }
	static Void _0xBF4F34A85CA2970C() { return _i<Void>(0xBF4F34A85CA2970C); }
	static Void end_text_command_objective(bool p0) { return _i<Void>(0xCFDBDF5AE59BA0F4, p0); }
	static Void show_loading_prompt(int busySpinnerType) { return _i<Void>(0xBD12F8228410D9B4, busySpinnerType); }
	static Void end_text_command_clear_print() { return _i<Void>(0xFCC75460ABA29378); }
	static Void end_text_command_display_help(Any p0, bool loop, bool beep, int shape) { return _i<Void>(0x238FFE5C7B0498A6, p0, loop, beep, shape); }
	static Void end_text_command_display_text(float x, float y, Any p2) { return _i<Void>(0xCD015E5BB0D96A57, x, y, p2); }
	static int end_text_command_get_line_count(float x, float y) { return _i<int>(0x9040DFB09BE75706, x, y); }
	static float end_text_command_get_width(int font) { return _i<float>(0x85F061DA64ED2F67, font); }
	static bool end_text_command_is_message_displayed() { return _i<bool>(0x8A9BA1AB3E237613); }
	static bool end_text_command_is_this_help_message_being_displayed(int p0) { return _i<bool>(0x10BDDBFC529428DD, p0); }
	static Void end_text_command_timer(bool p0) { return _i<Void>(0xA86911979638106F, p0); }
	static Void end_text_command_print(int duration, bool drawImmediately) { return _i<Void>(0x9D77056A530643F6, duration, drawImmediately); }
	static Void end_text_command_set_blip_name(Blip blip) { return _i<Void>(0xBC38B49BCB83BC9B, blip); }
	static int draw_notification_award(const char* p0, const char* p1, int p2, int p3, const char* p4) { return _i<int>(0xAA295B6F28BD587D, p0, p1, p2, p3, p4); }
	static int draw_notification_apartment_invite(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, int R, int G, int B) { return _i<int>(0x97C9E4E7024A8F2C, p0, p1, p2, p3, isLeader, unk0, clanDesc, R, G, B); }
	static int end_text_command_thefeed_post_crewtag_with_game_name(bool p0, bool p1, int64_t* p2, int p3, bool isLeader, bool unk0, int clanDesc, const char* playerName, int R, int G, int B) { return _i<int>(0x137BC35589E34E1E, p0, p1, p2, p3, isLeader, unk0, clanDesc, playerName, R, G, B); }
	static Any _0x8EFCCF6EC66D85E4(Any* p0, Any* p1, Any* p2, bool p3, bool p4) { return _i<Any>(0x8EFCCF6EC66D85E4, p0, p1, p2, p3, p4); }
	static int set_notification_message2(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject) { return _i<int>(0x1CCD9A37359072CF, picName1, picName2, flash, iconType, sender, subject); }
	static int set_notification_message3(const char* picName1, const char* picName2, bool p2, Any p3, const char* p4, const char* p5) { return _i<int>(0xC6F580E4C94926AC, picName1, picName2, p2, p3, p4, p5); }
	static int set_notification_message4(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration) { return _i<int>(0x1E6611149DB3DB6B, picName1, picName2, flash, iconType, sender, subject, duration); }
	static int set_notification_message_clan_tag(const char* picName1, const char* picName2, bool flash, int iconType, const char* sender, const char* subject, float duration, const char* clanTag) { return _i<int>(0x5CBF7BADE20DB93E, picName1, picName2, flash, iconType, sender, subject, duration, clanTag); }
	static int set_notification_message_clan_tag2(const char* picName1, const char* picName2, bool flash, int iconType1, const char* sender, const char* subject, float duration, const char* clanTag, int iconType2, int p9) { return _i<int>(0x531B84E7DA981FB6, picName1, picName2, flash, iconType1, sender, subject, duration, clanTag, iconType2, p9); }
	static int draw_notification_with_icon(int type, int image, const char* text) { return _i<int>(0xD202B92CBF1D816F, type, image, text); }
	static int draw_notification_with_button(int type, const char* button_option, const char* text) { return _i<int>(0xDD6CB2CCE7C2735C, type, button_option, text); }
	static int set_notification_message(const char* p0, int p1, int p2, int p3, bool p4, const char* picName1, const char* picName2) { return _i<int>(0x2B7E9A4EAAA93C89, p0, p1, p2, p3, p4, picName1, picName2); }
	static int draw_notification(bool blink, bool p1) { return _i<int>(0x2ED7843F8F801023, blink, p1); }
	static int draw_notification4(bool blink, bool p1) { return _i<int>(0xF020C96915705B3A, blink, p1); }
	static int draw_notification2(bool blink, bool p1) { return _i<int>(0x44FA03975424A0EE, blink, p1); }
	static int draw_notification3(bool blink, bool p1) { return _i<int>(0x378E809BF61EC840, blink, p1); }
	static Any _0x33EE12743CCD6343(Any p0, Any p1, Any p2) { return _i<Any>(0x33EE12743CCD6343, p0, p1, p2); }
	static Any _0xC8F3AAF93D0600BF(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xC8F3AAF93D0600BF, p0, p1, p2, p3); }
	static Any _0x7AE0589093A2E088(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Any>(0x7AE0589093A2E088, p0, p1, p2, p3, p4, p5); }
	static Any _0xB6871B0555B02996(Any* p0, Any* p1, Any p2, Any* p3, Any* p4, Any p5, Any p6, Any p7) { return _i<Any>(0xB6871B0555B02996, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void _0xCEF214315D276FD1(bool p0) { return _i<Void>(0xCEF214315D276FD1, p0); }
	static Void flash_ability_bar(bool toggle) { return _i<Void>(0x02CFBA0C9E9275CE, toggle); }
	static Void flash_minimap_display() { return _i<Void>(0xF2DD778C22B15BDA); }
	static Void _0x6B1DE27EE78E6A19(Any p0) { return _i<Void>(0x6B1DE27EE78E6A19, p0); }
	static Void flash_wanted_display(bool p0) { return _i<Void>(0xA18AFB39081B6A1F, p0); }
	static Void _0xEE4C0E6DBC6F2C6F() { return _i<Void>(0xEE4C0E6DBC6F2C6F); }
	static Void _0x8817605C2BA76200() { return _i<Void>(0x8817605C2BA76200); }
	static Void _0x57D760D55F54E071(bool p0) { return _i<Void>(0x57D760D55F54E071, p0); }
	static Void _0xBA8D65C1C65702E5(bool p0) { return _i<Void>(0xBA8D65C1C65702E5, p0); }
	static Any _0x1121BFA1A1A522A8() { return _i<Any>(0x1121BFA1A1A522A8); }
	static Blip* _0x7CD934010E115C2C(Ped ped) { return _i<Blip*>(0x7CD934010E115C2C, ped); }
	static Blip _0x56176892826A4FE8(Ped ped) { return _i<Blip>(0x56176892826A4FE8, ped); }
	static int get_blip_alpha(Blip blip) { return _i<int>(0x970F608F0EE6C885, blip); }
	static int get_blip_colour(Blip blip) { return _i<int>(0xDF729E8D20CF7327, blip); }
	static Any _0x2C173AE2BDB9385E(Any p0) { return _i<Any>(0x2C173AE2BDB9385E, p0); }
	static Blip get_blip_from_entity(Entity entity) { return _i<Blip>(0xBC8DBDCA2436F7E8, entity); }
	static int get_blip_hud_colour(Blip blip) { return _i<int>(0x729B5F1EFBC0AAEE, blip); }
	static math::vector3<float> get_blip_info_id_coord(Blip blip) { return _i<math::vector3<float>>(0xFA7C7F0AADF25D09, blip); }
	static math::vector3<float> get_blip_coords(Blip blip) { return _i<math::vector3<float>>(0x586AFE3FF72D996E, blip); }
	static int get_blip_info_id_display(Blip blip) { return _i<int>(0x1E314167F701DC3B, blip); }
	static Entity get_blip_info_id_entity_index(Blip blip) { return _i<Entity>(0x4BA4E2553AFEDC2C, blip); }
	static int get_blip_info_id_type(Blip blip) { return _i<int>(0xBE9B0959FFD0779B, blip); }
	static int get_blip_sprite(Blip blip) { return _i<int>(0x1FC877464A04FC4F, blip); }
	static const char* get_text_substring(const char* text, int position, int length) { return _i<const char*>(0x169BD9382084C8C0, text, position, length); }
	static const char* get_text_substring_slice(const char* text, int startPosition, int endPosition) { return _i<const char*>(0xCE94AEBA5D82908A, text, startPosition, endPosition); }
	static const char* get_text_substring_safe(const char* text, int position, int length, int maxLength) { return _i<const char*>(0xB2798643312205C5, text, position, length, maxLength); }
	static bool _0x8F08017F9D7C47BD(Any p0, Any* p1, Any p2) { return _i<bool>(0x8F08017F9D7C47BD, p0, p1, p2); }
	static bool _0xCA6B2F7CE32AB653(Any p0, Any* p1, Any p2) { return _i<bool>(0xCA6B2F7CE32AB653, p0, p1, p2); }
	static bool _0x24A49BEAF468DC90(Any p0, Any* p1, Any p2, Any p3, Any p4) { return _i<bool>(0x24A49BEAF468DC90, p0, p1, p2, p3, p4); }
	static Any _0xD484BF71050CA1EE(Any p0) { return _i<Any>(0xD484BF71050CA1EE, p0); }
	static uint32_t get_current_frontend_menu() { return _i<uint32_t>(0x2309595AD6145265); }
	static Any _0x01A358D9128B7A86() { return _i<Any>(0x01A358D9128B7A86); }
	static int get_current_website_id() { return _i<int>(0x97D47996FC48CBAD); }
	static Any _0xC2D2AD9EAAE265B8() { return _i<Any>(0xC2D2AD9EAAE265B8); }

	static const char* get_label_text(const char* labelName) {
		const char* Return = _i<const char*>(0x7B5280EBA9840C72, labelName);
		return !Return ? "NULL" : Return;
	}

	static Blip get_first_blip_info_id(int blipSprite) { return _i<Blip>(0x1BEDE233E6CD2A1F, blipSprite); }
	static Any _0x98C3CF913D895111(Any p0, Any p1) { return _i<Any>(0x98C3CF913D895111, p0, p1); }
	static Any _0xE3B05614DCE1D014(Any p0) { return _i<Any>(0xE3B05614DCE1D014, p0); }
	static Void get_hud_colour(int hudColorIndex, int* r, int* g, int* b, int* a) { return _i<Void>(0x7C9C91AB74A0360F, hudColorIndex, r, g, b, a); }
	static math::vector3<int> get_hud_component_position(int id) { return _i<math::vector3<int>>(0x223CA69A8C4417FD, id); }
	static bool get_hud_screen_position_froworld_position(float worldX, float worldY, float worldZ, float* screenX, float* screenY) { return _i<bool>(0xF9904D11F1ACBEC3, worldX, worldY, worldZ, screenX, screenY); }
	static int get_length_of_literal_string(const char* string) { return _i<int>(0xF030907CCBB8A9FD, string); }
	static int get_length_of_string(const char* STRING) { return _i<int>(0x43E4111189E54F0E, STRING); }
	static int get_length_of_string_with_this_text_label(const char* gxt) { return _i<int>(0x801BD273D3A23F74, gxt); }
	static Blip get_main_player_blip_id() { return _i<Blip>(0xDCD4EC3F419D02FA); }
	static Void _0x7E17BE53E1AAABAF(Any* p0, Any* p1, Any* p2) { return _i<Void>(0x7E17BE53E1AAABAF, p0, p1, p2); }
	static bool _0x052991E59076E4E4(uint32_t p0, Any* p1) { return _i<bool>(0x052991E59076E4E4, p0, p1); }
	static bool _0x5FBD7095FE7AE57F(Any p0, float* p1) { return _i<bool>(0x5FBD7095FE7AE57F, p0, p1); }
	static bool set_userids_uihidden(Any p0, Any* p1) { return _i<bool>(0xEF4CED81CEBEDC6D, p0, p1); }
	static bool _0x90A6526CF0381030(Any p0, Any* p1, Any p2, Any p3) { return _i<bool>(0x90A6526CF0381030, p0, p1, p2, p3); }
	static Void _0x36C1451A88A09630(Any* p0, Any* p1) { return _i<Void>(0x36C1451A88A09630, p0, p1); }
	static bool is_minimap_area_revealed(float x, float y, float radius) { return _i<bool>(0x6E31B91145873922, x, y, radius); }
	static float _0xE0130B41D3CF4574() { return _i<float>(0xE0130B41D3CF4574); }
	static bool _0x632B2940C67F4EA9(int scaleformHandle, Any* p1, Any* p2, Any* p3) { return _i<bool>(0x632B2940C67F4EA9, scaleformHandle, p1, p2, p3); }
	static Any get_named_rendertarget_render_id(const char* p0) { return _i<Any>(0x1A6478B61C6BDC3B, p0); }
	static Blip disable_blip_name_for_var() { return _i<Blip>(0x5C90988E7C8E1AF4); }
	static Blip get_next_blip_info_id(int blipSprite) { return _i<Blip>(0x14F96AA50D6FBEA7, blipSprite); }
	static Any _0x3F0CF9CB7E589B88() { return _i<Any>(0x3F0CF9CB7E589B88); }
	static int get_number_of_active_blips() { return _i<int>(0x9A3FF3DE163034E8); }
	static math::vector3<float> _0x5BFF36D6ED83E0AE() { return _i<math::vector3<float>>(0x5BFF36D6ED83E0AE); }
	static int get_pause_menu_state() { return _i<int>(0x272ACD84970869C5); }
	static bool _0xA238192F33110615(int* p0, int* p1, int* p2) { return _i<bool>(0xA238192F33110615, p0, p1, p2); }
	static float get_text_scale_height(float size, int font) { return _i<float>(0xDB88A37483346780, size, font); }
	static Any _0x593FEAE1F73392D4() { return _i<Any>(0x593FEAE1F73392D4); }
	static const char* get_street_name_from_hash_key(uint32_t hash) { return _i<const char*>(0xD0EF8A959B8A4CB9, hash); }
	static int get_blip_info_id_iterator() { return _i<int>(0x186E5D252FA50E7D); }
	static Void give_ped_to_pause_menu(Ped ped, int p1) { return _i<Void>(0xAC0BFBDC3BE00E14, ped, p1); }
	static bool has_additional_text_loaded(int slot) { return _i<bool>(0x02245FE4BED318B8, slot); }
	static Any _0xA277800A9EAE340E() { return _i<Any>(0xA277800A9EAE340E); }
	static Any _0x2E22FEFA0100275E() { return _i<Any>(0x2E22FEFA0100275E); }
	static Any _0xF284AC67940C6812() { return _i<Any>(0xF284AC67940C6812); }
	static bool is_scripted_hud_component_active(int id) { return _i<bool>(0xDD100EB17A94FF65, id); }
	static bool _0x214CD562A939246A() { return _i<bool>(0x214CD562A939246A); }
	static bool has_this_additional_text_loaded(const char* gxt, int slot) { return _i<bool>(0xADBF060E2B30C5BC, gxt, slot); }
	static int get_default_script_rendertarget_render_id() { return _i<int>(0x52F0982D7FD156B6); }
	static bool _0x4A9923385BDB9DAD() { return _i<bool>(0x4A9923385BDB9DAD); }
	static Void hide_help_text_this_frame() { return _i<Void>(0xD46923FC481CA285); }
	static Void hide_hud_and_radar_this_frame() { return _i<Void>(0x719FF505F097FD20); }
	static Void hide_hud_component_this_frame(int id) { return _i<Void>(0x6806C51AD12B83B8, id); }
	static Void hide_loading_on_fade_this_frame() { return _i<Void>(0x4B0311D3CDC4648F); }
	static Void disable_radar_this_frame() { return _i<Void>(0x5FBAE526203990C9); }
	static Void _0x20FE7FDFEEAD38C0() { return _i<Void>(0x20FE7FDFEEAD38C0); }
	static Void hide_number_on_blip(Blip blip) { return _i<Void>(0x532CFF637EF80148, blip); }
	static Void hide_scripted_hud_component_this_frame(int id) { return _i<Void>(0xE374C498D8BADC14, id); }
	static Void _0xA4DEDE28B1814289() { return _i<Void>(0xA4DEDE28B1814289); }
	static Void _0x488043841BBE156F() { return _i<Void>(0x488043841BBE156F); }
	static Void show_weapon_wheel(bool forcedShow) { return _i<Void>(0xEB354E5376BC81A7, forcedShow); }
	static uint32_t _0xA48931185F0536FE() { return _i<uint32_t>(0xA48931185F0536FE); }
	static Any _0xA13E93403F26C812(Any p0) { return _i<Any>(0xA13E93403F26C812, p0); }
	static Void _0x72C1056D678BB7D8(uint32_t weaponHash) { return _i<Void>(0x72C1056D678BB7D8, weaponHash); }
	static Void _0x14C9FDCC41F81F63(bool p0) { return _i<Void>(0x14C9FDCC41F81F63, p0); }
	static Void _0x0AFC4AF510774B47() { return _i<Void>(0x0AFC4AF510774B47); }
	static bool is_blip_flashing(Blip blip) { return _i<bool>(0xA5E41FD83AD6CEF0, blip); }
	static bool is_blip_on_minimap(Blip blip) { return _i<bool>(0xE41CA53051197A27, blip); }
	static bool is_blip_short_range(Blip blip) { return _i<bool>(0xDA5F8727EB75B926, blip); }
	static bool _0x2432784ACA090DA4(Any p0) { return _i<bool>(0x2432784ACA090DA4, p0); }
	static Any _0x3BAB9A4E4F2FF5C7() { return _i<Any>(0x3BAB9A4E4F2FF5C7); }
	static bool is_help_message_being_displayed() { return _i<bool>(0x4D79439A6B55AC67); }
	static bool is_help_message_fading_out() { return _i<bool>(0x327EDEEEAC55C369); }
	static bool is_help_message_on_screen() { return _i<bool>(0xDAD37F45428801AE); }
	static bool _0x4167EFE0527D706E() { return _i<bool>(0x4167EFE0527D706E); }
	static bool is_hud_component_active(int id) { return _i<bool>(0xBC4C9EA5391ECC0D, id); }
	static bool is_hud_hidden() { return _i<bool>(0xA86478C6958735C5); }
	static bool is_hud_preference_switched_on() { return _i<bool>(0x1930DFA731813EC4); }
	static Any _0x801879A9B4F4B2FB() { return _i<Any>(0x801879A9B4F4B2FB); }
	static bool is_message_being_displayed() { return _i<bool>(0x7984C03AA5CC2F41); }
	static bool is_radar_enabled() { return _i<bool>(0xAF754F20EB5CD51A); }
	static bool is_mission_creator_blip(Blip blip) { return _i<bool>(0x26F49BF3381D933D, blip); }
	static Any _0x3D9ACB1EB139E702() { return _i<Any>(0x3D9ACB1EB139E702); }
	static bool is_mp_gamer_tag_active(int gamerTagId) { return _i<bool>(0x4E929E7A5796FD26, gamerTagId); }
	static bool add_trevor_random_modifier(int gamerTagId) { return _i<bool>(0x595B5178E412E199, gamerTagId); }
	static bool has_mp_gamer_tag() { return _i<bool>(0x6E0EB3EB47C8D7AA); }
	static bool is_text_chat_active() { return _i<bool>(0xB118AF58B5F332A1); }
	static bool is_named_rendertarget_linked(uint32_t hash) { return _i<bool>(0x113750538FA31298, hash); }
	static bool is_named_rendertarget_registered(const char* p0) { return _i<bool>(0x78DCDC15C9F116B4, p0); }
	static Any _0x4E3CD0EF8A489541() { return _i<Any>(0x4E3CD0EF8A489541); }
	static int _0x6F72CD94F7B5B68C() { return _i<int>(0x6F72CD94F7B5B68C); }
	static bool is_social_club_active() { return _i<bool>(0xC406BE343FC4B9AF); }
	static Any _0x9049FE339D5F6F6F() { return _i<Any>(0x9049FE339D5F6F6F); }
	static bool is_pause_menu_active() { return _i<bool>(0xB0034A223497FFCB); }
	static bool is_pause_menu_restarting() { return _i<bool>(0x1C491717107431C7); }
	static bool is_radar_hidden() { return _i<bool>(0x157F93B036700462); }
	static bool is_radar_preference_switched_on() { return _i<bool>(0x9EB6522EA68F22FE); }
	static Any _0x9135584D09A3437E() { return _i<Any>(0x9135584D09A3437E); }
	static bool _0x09C0403ED9A751C2(Any p0) { return _i<bool>(0x09C0403ED9A751C2, p0); }
	static Any _0x2F057596F2BD0061() { return _i<Any>(0x2F057596F2BD0061); }
	static bool is_streaming_additional_text(int p0) { return _i<bool>(0x8B6817B71B85EBF0, p0); }
	static bool is_subtitle_preference_switched_on() { return _i<bool>(0xAD6DACA4BA53E0A4); }
	static bool has_mp_gamer_tag2(int gamerTagId) { return _i<bool>(0xEB709A36958ABE0D, gamerTagId); }
	static bool is_warning_message_active() { return _i<bool>(0xE18B138FABC53103); }
	static Any _0xAF42195A42C63BBA() { return _i<Any>(0xAF42195A42C63BBA); }
	static bool is_waypoint_active() { return _i<bool>(0x1DD1F58F493F1DA5); }
	static Void link_named_rendertarget(uint32_t hash) { return _i<Void>(0xF6C09E276AEB3F2D, hash); }
	static Void lock_minimap_angle(int angle) { return _i<Void>(0x299FAEBB108AE05B, angle); }
	static Void lock_minimap_position(float x, float y) { return _i<Void>(0x1279E861A329E73F, x, y); }
	static Void set_text_chat_unk(bool p0) { return _i<Void>(0x1DB21A44B09E8BA3, p0); }
	static Void _0x7C226D5346D4D10A(Any p0) { return _i<Void>(0x7C226D5346D4D10A, p0); }
	static Void show_social_club_legal_screen() { return _i<Void>(0x805D7CBB36FD6C4C); }
	static Void _0x523A590C1A3CC0D3() { return _i<Void>(0x523A590C1A3CC0D3); }
	static Void _0x75D3691713C3B05A() { return _i<Void>(0x75D3691713C3B05A); }
	static Void override_multiplayer_chat_colour(Any p0, Any p1) { return _i<Void>(0xF47E567B3630DD12, p0, p1); }
	static Void _0x6A1738B4323FE2D9(Any p0) { return _i<Void>(0x6A1738B4323FE2D9, p0); }
	static Void _0x77F16B447824DA6C(Any p0) { return _i<Void>(0x77F16B447824DA6C, p0); }
	static Void _0xCDCA26E80FAECB8F() { return _i<Void>(0xCDCA26E80FAECB8F); }
	static Void add_frontend_menu_context(uint32_t hash) { return _i<Void>(0xDD564BDD0472C936, hash); }
	static Void object_decal_toggle(uint32_t hash) { return _i<Void>(0x444D8CF241EC25C5, hash); }
	static Any _0xDE03620F8703A9DF() { return _i<Any>(0xDE03620F8703A9DF); }
	static bool _0xC8E1071177A23BE5(Any* p0, Any* p1, Any* p2) { return _i<bool>(0xC8E1071177A23BE5, p0, p1, p2); }
	static Any _0x359AF31A4B52F5ED() { return _i<Any>(0x359AF31A4B52F5ED); }
	static Any _0x13C4B962653A5280() { return _i<Any>(0x13C4B962653A5280); }
	static bool _0x84698AB38D0C6636(uint32_t hash) { return _i<bool>(0x84698AB38D0C6636, hash); }
	static Any _0x2A25ADC48F87841F() { return _i<Any>(0x2A25ADC48F87841F); }
	static Void enable_deathblood_seethrough(bool p0) { return _i<Void>(0x4895BDEA16E7C080, p0); }
	static Void _0xC78E239AC5B2DDB9(bool p0, Any p1, Any p2) { return _i<Void>(0xC78E239AC5B2DDB9, p0, p1, p2); }
	static Void _0xF06EBB91A81E09E3(bool p0) { return _i<Void>(0xF06EBB91A81E09E3, p0); }
	static Void _0x2DE6C5E2E996F178(Any p0) { return _i<Void>(0x2DE6C5E2E996F178, p0); }
	static Void _0xC65AB383CD91DF98() { return _i<Void>(0xC65AB383CD91DF98); }
	static Void pulse_blip(Blip blip) { return _i<Void>(0x742D6FD43115AF73, blip); }
	static Void refresh_waypoint() { return _i<Void>(0x81FA173F170560D1); }
	static bool register_named_rendertarget(const char* p0, bool p1) { return _i<bool>(0x57D9C12635E25CE3, p0, p1); }
	static Void _0x14621BB1DF14E2B2() { return _i<Void>(0x14621BB1DF14E2B2); }
	static bool release_named_rendertarget(Any* p0) { return _i<bool>(0xE9F6FFE837354DD4, p0); }
	static Void _0x2916A928514C9827() { return _i<Void>(0x2916A928514C9827); }
	static Void remove_blip(Blip* blip) { return _i<Void>(0x86A652570E5F25DD, blip); }
	static Void _0xC594B315EDF2D4AF(Ped ped) { return _i<Void>(0xC594B315EDF2D4AF, ped); }
	static Void remove_mp_gamer_tag(int gamerTagId) { return _i<Void>(0x31698AA80E0223F8, gamerTagId); }
	static Void remove_multiplayer_bank_cash() { return _i<Void>(0xC7C6789AA1CFEDD0); }
	static Void remove_multiplayer_hud_cash() { return _i<Void>(0x968F270E39141ECA); }
	static Void _0x95CF81BD06EE1887() { return _i<Void>(0x95CF81BD06EE1887); }
	static Void _0x6EF54AB721DC6242() { return _i<Void>(0x6EF54AB721DC6242); }
	static Void set_hud_colours_switch(int hudColorIndex, int hudColorIndex2) { return _i<Void>(0x1CCC708F0F850613, hudColorIndex, hudColorIndex2); }
	static Void set_hud_colour(int hudColorIndex, int r, int g, int b, int a) { return _i<Void>(0xF314CF4F0211894E, hudColorIndex, r, g, b, a); }
	static Void request_additional_text(const char* gxt, int slot) { return _i<Void>(0x71A78003C8E71424, gxt, slot); }
	static Void request_additional_text2(const char* gxt, int slot) { return _i<Void>(0x6009F9F1AE90D8A6, gxt, slot); }
	static Void _0xB99C4E4D9499DF29(bool p0) { return _i<Void>(0xB99C4E4D9499DF29, p0); }
	static Void reset_hud_component_values(int id) { return _i<Void>(0x450930E616475D0D, id); }
	static Void reset_reticule_values() { return _i<Void>(0x12782CE0A636E9F0); }
	static Void restart_frontend_menu(uint32_t menuHash, int p1) { return _i<Void>(0x10706DC6AD2D49C0, menuHash, p1); }
	static Void set_ability_bar_value(float p0, float p1) { return _i<Void>(0x9969599CCFF5D85E, p0, p1); }
	static Void _0x577599CCED639CA2(Any p0) { return _i<Void>(0x577599CCED639CA2, p0); }
	static Void _0xEE76FF7E6A0166B0(int headDisplayId, bool p1) { return _i<Void>(0xEE76FF7E6A0166B0, headDisplayId, p1); }
	static Void set_radar_bigmap_enabled(bool toggleBigMap, bool showFullMap) { return _i<Void>(0x231C8F89D0539D8F, toggleBigMap, showFullMap); }
	static Void set_blip_alpha(Blip blip, int alpha) { return _i<Void>(0x45FF974EEE1C8734, blip, alpha); }
	static Void set_blip_as_friendly(Blip blip, bool toggle) { return _i<Void>(0x6F6F290102C02AB4, blip, toggle); }
	static Void set_blip_shrink(Blip blip, bool toggle) { return _i<Void>(0x2B6D467DAB714E8D, blip, toggle); }
	static Void set_blip_as_mission_creator_blip(Blip blip, bool toggle) { return _i<Void>(0x24AC0137444F9FD5, blip, toggle); }
	static Void set_blip_as_short_range(Blip blip, bool toggle) { return _i<Void>(0xBE8BE4FE60E27B72, blip, toggle); }
	static Void set_blip_bright(Blip blip, bool toggle) { return _i<Void>(0xB203913733F27884, blip, toggle); }
	static Void set_blip_category(Blip blip, int index) { return _i<Void>(0x234CDD44D996FD9A, blip, index); }
	static Void set_blip_colour(Blip blip, int color) { return _i<Void>(0x03D7FB09E75D6B7E, blip, color); }
	static Void set_blip_coords(Blip blip, float posX, float posY, float posZ) { return _i<Void>(0xAE2AF67E9D9AF65D, blip, posX, posY, posZ); }
	static Void set_blip_display(Blip blip, int displayId) { return _i<Void>(0x9029B2F3DA924928, blip, displayId); }
	static Void _0xC4278F70131BAA6D(Any p0, bool p1) { return _i<Void>(0xC4278F70131BAA6D, p0, p1); }
	static Void set_blip_fade(Blip blip, int opacity, int duration) { return _i<Void>(0x2AEE8F8390D2298C, blip, opacity, duration); }
	static Void set_blip_flashes(Blip blip, bool toggle) { return _i<Void>(0xB14552383D39CE3E, blip, toggle); }
	static Void set_blip_flashes_alternate(Blip blip, bool toggle) { return _i<Void>(0x2E8D9498C56DD0D1, blip, toggle); }
	static Void set_blip_flash_interval(Blip blip, Any p1) { return _i<Void>(0xAA51DB313C010A7E, blip, p1); }
	static Void set_blip_flash_timer(Blip blip, int duration) { return _i<Void>(0xD3CD6FD297AE87CC, blip, duration); }
	static Void _0x54318C915D27E4CE(Any p0, bool p1) { return _i<Void>(0x54318C915D27E4CE, p0, p1); }
	static Void set_blip_high_detail(Blip blip, bool toggle) { return _i<Void>(0xE2590BC29220CEBB, blip, toggle); }
	static Void _0xB552929B85FC27EC(Any p0, Any p1) { return _i<Void>(0xB552929B85FC27EC, p0, p1); }
	static Void set_blip_name_from_text_file(Blip blip, const char* gxtEntry) { return _i<Void>(0xEAA0FFE120D92784, blip, gxtEntry); }
	static Void set_blip_name_to_player_name(Blip blip, Player player) { return _i<Void>(0x127DE7B20C60A6A3, blip, player); }
	static Void set_blip_priority(Blip blip, int priority) { return _i<Void>(0xAE9FC9EF6A9FAC79, blip, priority); }
	static Void set_blip_rotation(Blip blip, int rotation) { return _i<Void>(0xF87683CDF73C3F6E, blip, rotation); }
	static Void _0xA8B6AFDAC320AC87(Any p0, Any p1) { return _i<Void>(0xA8B6AFDAC320AC87, p0, p1); }
	static Void set_blip_route(Blip blip, bool enabled) { return _i<Void>(0x4F7D8A9BFB0B43E9, blip, enabled); }
	static Void set_blip_route_colour(Blip blip, int colour) { return _i<Void>(0x837155CD2F63DA09, blip, colour); }
	static Void set_blip_scale(Blip blip, float scale) { return _i<Void>(0xD38744167B2FA257, blip, scale); }
	static Void set_blip_secondary_colour(Blip blip, float r, float g, float b) { return _i<Void>(0x14892474891E09EB, blip, r, g, b); }
	static Void _0x4B5B620C9B59ED34(Any p0, Any p1) { return _i<Void>(0x4B5B620C9B59ED34, p0, p1); }
	static Void set_blip_show_cone(Blip blip, bool toggle) { return _i<Void>(0x13127EC3665E8EE1, blip, toggle); }
	static Void set_blip_sprite(Blip blip, int spriteId) { return _i<Void>(0xDF735600A4696DAF, blip, spriteId); }
	static Void _0x2C9F302398E13141(Any p0, Any p1) { return _i<Void>(0x2C9F302398E13141, p0, p1); }
	static Void _0xD1942374085C8469(Any p0) { return _i<Void>(0xD1942374085C8469, p0); }
	static Void set_notification_color_next(int hudIndex) { return _i<Void>(0x39BBF623FC803EAC, hudIndex); }
	static Void _0x817B86108EB94E51(bool p0, Any* p1, Any* p2, Any* p3, Any* p4, Any* p5, Any* p6, Any* p7, Any* p8) { return _i<Void>(0x817B86108EB94E51, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Void _0x04655F9D075D0AE5(bool p0) { return _i<Void>(0x04655F9D075D0AE5, p0); }
	static Void _0x2632482FD6B9AB87() { return _i<Void>(0x2632482FD6B9AB87); }
	static Void _0xA17784FCA9548D15(Any p0, Any p1, Any p2) { return _i<Void>(0xA17784FCA9548D15, p0, p1, p2); }
	static Void set_minimap_attitude_indicator_level(float altitude, bool p1) { return _i<Void>(0xD201F3FF917A506D, altitude, p1); }
	static Void set_player_blip_position_this_frame(float x, float y) { return _i<Void>(0x77E2DD177910E1CF, x, y); }
	static Void _0xCD74233600C4EA6B(Any p0) { return _i<Void>(0xCD74233600C4EA6B, p0); }
	static Void _0x7679CC1BCEBE3D4C(Any p0, float p1, float p2) { return _i<Void>(0x7679CC1BCEBE3D4C, p0, p1, p2); }
	static Void _0x788E7FD431BD67F1(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0x788E7FD431BD67F1, p0, p1, p2, p3, p4, p5); }
	static Void _0xB094BC1DB4018240(Any p0, Any p1, float p2, float p3) { return _i<Void>(0xB094BC1DB4018240, p0, p1, p2, p3); }
	static Void _0x784BA7E0ECEB4178(Any p0, float x, float y, float z) { return _i<Void>(0x784BA7E0ECEB4178, p0, x, y, z); }
	static Void _0x2790F4B17D098E26(Any p0) { return _i<Void>(0x2790F4B17D098E26, p0); }
	static Void set_frontend_active(bool active) { return _i<Void>(0x745711A75AB09277, active); }
	static Void _0x900086F371220B6F(bool p0, Any p1, Any p2) { return _i<Void>(0x900086F371220B6F, p0, p1, p2); }
	static Void set_gps_flags(int p0, float p1) { return _i<Void>(0x5B440763A4C8D15B, p0, p1); }
	static Void set_gps_flashes(bool toggle) { return _i<Void>(0x320D0E0D936A0E9B, toggle); }
	static Void _0x3DDA37128DD1ACA8(bool p0) { return _i<Void>(0x3DDA37128DD1ACA8, p0); }
	static Void _0x3F5CC444DCAAA8F2(Any p0, Any p1, bool p2) { return _i<Void>(0x3F5CC444DCAAA8F2, p0, p1, p2); }
	static Void _0xB9C362BABECDDC7A(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xB9C362BABECDDC7A, p0, p1, p2, p3, p4); }
	static Void set_hud_component_position(int id, float x, float y) { return _i<Void>(0xAABB1F56E2A17CED, id, x, y); }
	static Void _0x06A320535F5F0248(Any p0) { return _i<Void>(0x06A320535F5F0248, p0); }
	static Void _0x975D66A0BC17064C(Any p0) { return _i<Void>(0x975D66A0BC17064C, p0); }
	static Void set_minimap_block_waypoint(bool toggle) { return _i<Void>(0x58FADDED207897DC, toggle); }
	static Any set_minimap_component(int p0, bool p1, int p2) { return _i<Any>(0x75A9A10948D1DEA6, p0, p1, p2); }
	static Void _0x62E849B7EB28E770(bool p0) { return _i<Void>(0x62E849B7EB28E770, p0); }
	static Void _0x0923DBF87DFF735E(float x, float y, float z) { return _i<Void>(0x0923DBF87DFF735E, x, y, z); }
	static Void _0x71BDB63DBAF8DA59(Any p0) { return _i<Void>(0x71BDB63DBAF8DA59, p0); }
	static Void _0x35EDD5B2E3FF01C0() { return _i<Void>(0x35EDD5B2E3FF01C0); }
	static Void set_minimap_revealed(bool toggle) { return _i<Void>(0xF8DEE0A5600CBB93, toggle); }
	static Void set_north_yankton_map(bool toggle) { return _i<Void>(0x9133955F1A2DA957, toggle); }
	static Void key_hud_colour(bool p0, Any p1) { return _i<Void>(0x1A5CD7752DD28CD3, p0, p1); }
	static Void set_mission_name(bool p0, const char* name) { return _i<Void>(0x5F28ECF5FC84772F, p0, name); }
	static Void _0xE45087D85F468BC2(bool p0, Any* p1) { return _i<Void>(0xE45087D85F468BC2, p0, p1); }
	static Void set_cursor_sprite(int spriteId) { return _i<Void>(0x8DB8CFFD58B62552, spriteId); }
	static Void show_cursor_this_frame() { return _i<Void>(0xAAE7CE1D63167423); }
	static Void _0x98215325A695E78A(bool p0) { return _i<Void>(0x98215325A695E78A, p0); }
	static Void set_mp_gamer_tag_icons(int headDisplayId, bool p1) { return _i<Void>(0xA67F9C46D612B6F1, headDisplayId, p1); }
	static Void set_mp_gamer_tag_alpha(int gamerTagId, int component, int alpha) { return _i<Void>(0xD48FE545CD46F857, gamerTagId, component, alpha); }
	static Void set_mp_gamer_tag_chatting(int gamerTagId, const char* string) { return _i<Void>(0x7B7723747CCB55B6, gamerTagId, string); }
	static Void set_mp_gamer_tag_colour(int gamerTagId, int flag, int color) { return _i<Void>(0x613ED644950626AE, gamerTagId, flag, color); }
	static Void set_mp_gamer_tag_health_bar_colour(int headDisplayId, int color) { return _i<Void>(0x3158C77A7E888AB4, headDisplayId, color); }
	static Void set_mp_gamer_tag_name(int gamerTagId, const char* string) { return _i<Void>(0xDEA2B8283BAA3944, gamerTagId, string); }
	static Void _0x9C16459B2324B2CF(Any p0, Any p1) { return _i<Void>(0x9C16459B2324B2CF, p0, p1); }
	static Void set_mp_gamer_tag_visibility(int gamerTagId, int component, bool toggle, Any p3) { return _i<Void>(0x63BB75ABEDC1F6A0, gamerTagId, component, toggle, p3); }
	static Void set_mp_gamer_tag_wanted_level(int gamerTagId, int wantedlvl) { return _i<Void>(0xCF228E2AA03099C3, gamerTagId, wantedlvl); }
	static Void set_multiplayer_bank_cash() { return _i<Void>(0xDD21B55DF695CD0A); }
	static Void _0xC2D15BEF167E27BC() { return _i<Void>(0xC2D15BEF167E27BC); }
	static Void set_new_waypoint(float x, float y) { return _i<Void>(0xFE43368D2AA4F2FC, x, y); }
	static Void set_pause_menu_active(bool toggle) { return _i<Void>(0xDF47FC56C71569CF, toggle); }
	static Void _0x3CA6050692BC61B0(bool p0) { return _i<Void>(0x3CA6050692BC61B0, p0); }
	static Void _0xECF128344E9FF9F1(bool p0) { return _i<Void>(0xECF128344E9FF9F1, p0); }
	static Void _0x0C4BBF625CA98C4E(Ped ped, bool p1) { return _i<Void>(0x0C4BBF625CA98C4E, ped, p1); }
	static Void _0xE52B8E7F85D39A08(Ped ped, int unk) { return _i<Void>(0xE52B8E7F85D39A08, ped, unk); }
	static Void hide_special_ability_lockon_operation(Any p0, bool p1) { return _i<Void>(0x3EED80DFF7325CAA, p0, p1); }
	static Void set_ai_blip_max_distance(Ped ped, float distance) { return _i<Void>(0x97C65887D4B37FA9, ped, distance); }
	static Void _0xFCFACD0DB9D7A57D(Any p0, Any p1) { return _i<Void>(0xFCFACD0DB9D7A57D, p0, p1); }
	static Void set_ped_enemy_ai_blip(int pedHandle, bool showViewCones) { return _i<Void>(0xD30C50DF888D58B5, pedHandle, showViewCones); }
	static Void _0xB13DCB4C6FAAD238(Any p0, Any p1, Any p2) { return _i<Void>(0xB13DCB4C6FAAD238, p0, p1, p2); }
	static Void _0x7B21E0BB01E8224A(Any p0) { return _i<Void>(0x7B21E0BB01E8224A, p0); }
	static Void set_director_mode(bool toggle) { return _i<Void>(0x808519373FD336A3, toggle); }
	static Void _0x41350B4FC28E3941(bool p0) { return _i<Void>(0x41350B4FC28E3941, p0); }
	static Void _0x1EAC5F91BCBC5073(bool p0) { return _i<Void>(0x1EAC5F91BCBC5073, p0); }
	static Void set_radar_as_exterior_this_frame() { return _i<Void>(0xE81B7D2A3DAB2D81); }
	static Void set_radar_as_interior_this_frame(uint32_t interior, float x, float y, int z, int zoom) { return _i<Void>(0x59E727A1C9D3E31A, interior, x, y, z, zoom); }
	static Void set_radar_zoom(int zoomLevel) { return _i<Void>(0x096EF57A0C999BBA, zoomLevel); }
	static Void responding_as_temp(float p0) { return _i<Void>(0xBD12C5EEE184C337, p0); }
	static Void _0xF98E4B3E56AFC7B1(Any p0, float p1) { return _i<Void>(0xF98E4B3E56AFC7B1, p0, p1); }
	static Void set_radar_zoom_level_this_frame(float zoomLevel) { return _i<Void>(0xCB7CC0D58405AD41, zoomLevel); }
	static Void _0x25615540D894B814(Any p0, bool p1) { return _i<Void>(0x25615540D894B814, p0, p1); }
	static Void _0x0CF54F20DE43879C(Any p0) { return _i<Void>(0x0CF54F20DE43879C, p0); }
	static Void _0xD68A5FF8A3A89874(int r, int g, int b, int a) { return _i<Void>(0xD68A5FF8A3A89874, r, g, b, a); }
	static Void _0x16A304E6CB2BFAB9(int r, int g, int b, int a) { return _i<Void>(0x16A304E6CB2BFAB9, r, g, b, a); }
	static Void _0x9E778248D6685FE0(const char* p0) { return _i<Void>(0x9E778248D6685FE0, p0); }
	static Void set_text_centre(bool align) { return _i<Void>(0xC02F4DBFB51D988B, align); }
	static Void set_text_colour(int red, int green, int blue, int alpha) { return _i<Void>(0xBE6B23FFA53FB442, red, green, blue, alpha); }
	static Void set_text_dropshadow(int distance, int r, int g, int b, int a) { return _i<Void>(0x465C84BC39F1C351, distance, r, g, b, a); }
	static Void set_text_drop_shadow() { return _i<Void>(0x1CA3E9EAC9D93E5E); }
	static Void set_text_font(int fontType) { return _i<Void>(0x66E0276CC5F6B9DA, fontType); }
	static Void _0x1185A8087587322C(bool p0) { return _i<Void>(0x1185A8087587322C, p0); }
	static Void set_text_justification(int justifyType) { return _i<Void>(0x4E096588B13FFECA, justifyType); }
	static Void set_text_leading(bool p0) { return _i<Void>(0xA50ABC31E3CDFAFF, p0); }
	static Void set_text_outline() { return _i<Void>(0x2513DFB0FB8400FE); }
	static Void set_text_render_id(int renderId) { return _i<Void>(0x5F15302936E07111, renderId); }
	static Void set_text_right_justify(bool toggle) { return _i<Void>(0x6B3C4650BC8BEE47, toggle); }
	static Void set_text_scale(float p0, float size) { return _i<Void>(0x07C837F9A01C34C9, p0, size); }
	static Void set_text_wrap(float start, float end) { return _i<Void>(0x63145D9C883A1A70, start, end); }
	static Void _0x6CDD58146A436083(Any p0) { return _i<Void>(0x6CDD58146A436083, p0); }
	static Void set_warning_message(const char* entryLine1, int instructionalKey, const char* entryLine2, bool p3, Any p4, Any* p5, Any* p6, bool background) { return _i<Void>(0x7B1776B3B53F8D74, entryLine1, instructionalKey, entryLine2, p3, p4, p5, p6, background); }
	static bool _0xDAF87174BE7454FF(Any p0) { return _i<bool>(0xDAF87174BE7454FF, p0); }
	static bool _0x0C5A80A9E096D529(Any p0, Any* p1, Any p2, Any p3, Any p4, Any p5) { return _i<bool>(0x0C5A80A9E096D529, p0, p1, p2, p3, p4, p5); }
	static Void set_warning_message2(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, Any p5, Any* p6, Any* p7, bool background) { return _i<Void>(0xDC38CC1E35B6A5D7, entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, p6, p7, background); }
	static Void set_warning_message3(const char* entryHeader, const char* entryLine1, Any instructionalKey, const char* entryLine2, bool p4, Any p5, Any p6, Any* p7, Any* p8, bool p9) { return _i<Void>(0x701919482C74B5AB, entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, p6, p7, p8, p9); }
	static Void _0x15803FEC3B9A872B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return _i<Void>(0x15803FEC3B9A872B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static Void set_waypoint_off() { return _i<Void>(0xA7E4E2D361C2627F); }
	static Void set_widescreen_format(Any p0) { return _i<Void>(0xC3B07BA00A83B0F1, p0); }
	static Void _0x60E892BA4F5BDCA4() { return _i<Void>(0x60E892BA4F5BDCA4); }
	static Void _0xDCFB5D4DB8BF367E(Any p0, bool p1) { return _i<Void>(0xDCFB5D4DB8BF367E, p0, p1); }
	static Void set_blip_friend(Blip blip, bool toggle) { return _i<Void>(0x23C3EB807312F01A, blip, toggle); }
	static Void show_heading_indicator_on_blip(Blip blip, bool toggle) { return _i<Void>(0x5FBCA48327B914DF, blip, toggle); }
	static Void _0x75A16C3DA34F1245(Any p0, bool p1) { return _i<Void>(0x75A16C3DA34F1245, p0, p1); }
	static Void show_hud_component_this_frame(int id) { return _i<Void>(0x0B4DF1FA60C0E664, id); }
	static Void show_number_on_blip(Blip blip, int number) { return _i<Void>(0xA3C0B359DCB848B6, blip, number); }
	static Void set_blip_friendly(Blip blip, bool toggle) { return _i<Void>(0xB81656BC81FE24D1, blip, toggle); }
	static Void _0xF1A6C18B35BCADE6(bool p0) { return _i<Void>(0xF1A6C18B35BCADE6, p0); }
	static Void set_blip_checked(Blip blip, bool toggle) { return _i<Void>(0x74513EA3E505181E, blip, toggle); }
	static Void _0xDB34E8D56FC13B08(Any p0, bool p1, bool p2) { return _i<Void>(0xDB34E8D56FC13B08, p0, p1, p2); }
	static Void _0x3D3D15AF7BCAAF83(Any p0, bool p1, bool p2) { return _i<Void>(0x3D3D15AF7BCAAF83, p0, p1, p2); }
	static Void _0xBA751764F0821256() { return _i<Void>(0xBA751764F0821256); }
	static Void _0xEC9264727EEC0F28() { return _i<Void>(0xEC9264727EEC0F28); }
	static Void _0xADED7F5748ACAFE6() { return _i<Void>(0xADED7F5748ACAFE6); }
	static Void _0x56C8B608CFD49854() { return _i<Void>(0x56C8B608CFD49854); }
	static Void _0x80FE4F3AB4E1B62A() { return _i<Void>(0x80FE4F3AB4E1B62A); }
	static Void _0xA8FDB297A8D25FBA() { return _i<Void>(0xA8FDB297A8D25FBA); }
	static Void _0x583049884A2EEE3C() { return _i<Void>(0x583049884A2EEE3C); }
	static Void _0xA13C11E1B5C06BFC() { return _i<Void>(0xA13C11E1B5C06BFC); }
	static Void _0xFDEC055AB549E328() { return _i<Void>(0xFDEC055AB549E328); }
	static int get_current_notification() { return _i<int>(0x82352748437638CA); }
	static Void _0x32888337579A5970() { return _i<Void>(0x32888337579A5970); }
	static Void _0x25F87B30C382FCA7() { return _i<Void>(0x25F87B30C382FCA7); }
	static Any _0xA9CBFD40B3FA3010() { return _i<Any>(0xA9CBFD40B3FA3010); }
	static Void _0x6F1554B0CC2089FA(bool p0) { return _i<Void>(0x6F1554B0CC2089FA, p0); }
	static Void _0xFDB423997FA30340() { return _i<Void>(0xFDB423997FA30340); }
	static Void remove_notification(int notificationId) { return _i<Void>(0xBE4390CB40B3E627, notificationId); }
	static Void _0xB695E2CD0A2DA9EE() { return _i<Void>(0xB695E2CD0A2DA9EE); }
	static Void _0xD4438C0564490E63() { return _i<Void>(0xD4438C0564490E63); }
	static Void _0xFDD85225B2DEA55E() { return _i<Void>(0xFDD85225B2DEA55E); }
	static Void _0xE1CD1E48E025E661() { return _i<Void>(0xE1CD1E48E025E661); }
	static Void set_notification_background_color(int hudIndex) { return _i<Void>(0x92F0DA1E27DB96DC, hudIndex); }
	static Void _0x17AD8C9706BDD88A(Any p0) { return _i<Void>(0x17AD8C9706BDD88A, p0); }
	static Void set_notification_flash_color(int red, int green, int blue, int alpha) { return _i<Void>(0x17430B918701C342, red, green, blue, alpha); }
	static Void clear_notifications_pos(float pos) { return _i<Void>(0x55598D21339CB998, pos); }
	static Void _0xBAE4F9B97CD43B30(bool p0) { return _i<Void>(0xBAE4F9B97CD43B30, p0); }
	static Void _0x4A0C7C9BB10ABB36(bool p0) { return _i<Void>(0x4A0C7C9BB10ABB36, p0); }
	static Void _0x15CFA549788D35EF() { return _i<Void>(0x15CFA549788D35EF); }
	static Void _0x317EBA71D7543F52(Any* p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0x317EBA71D7543F52, p0, p1, p2, p3); }
	static Void toggle_stealth_radar(bool toggle) { return _i<Void>(0x6AFDFB93754950C7, toggle); }
	static Void _0x72DD432F3CDFC0EE(float posX, float posY, float posZ, float radius, int p4) { return _i<Void>(0x72DD432F3CDFC0EE, posX, posY, posZ, radius, p4); }
	static Void unlock_minimap_angle() { return _i<Void>(0x8183455E16C42E3A); }
	static Void unlock_minimap_position() { return _i<Void>(0x3E93E06DB8EF1F30); }
	static Void _0x170F541E1CADD1DE(bool p0) { return _i<Void>(0x170F541E1CADD1DE, p0); }
	static Void _0x0C698D8F099174C7(Any p0) { return _i<Void>(0x0C698D8F099174C7, p0); }
	static Pickup get_blip_info_id_pickup_index(Blip blip) { return _i<Pickup>(0x9B6786E4C03DD382, blip); }
	static Void _0xD2049635DEB9C375() { return _i<Void>(0xD2049635DEB9C375); }
	static Void set_text_proportional(bool p0) { return _i<Void>(0x038C1F517D7FDCF8, p0); }
	static Void set_text_edge(int p0, int r, int g, int b, int a) { return _i<Void>(0x441603240D202FA6, p0, r, g, b, a); }
	static Void set_multiplayer_hud_cash(int p0, int p1) { return _i<Void>(0xFD1D220394BCB824, p0, p1); }
	static Void clear_reminder_message() { return _i<Void>(0xB57D8DD645CFA2CF); }
	static Void _0x211C4EF450086857() { return _i<Void>(0x211C4EF450086857); }
	static Void log_debug_info(const char* p0) { return _i<Void>(0x2162C446DFDF38FD, p0); }

	static Void enable_interior_prop(int interiorID, const char* propName) { return _i<Void>(0x55E86AF2712B36A1, interiorID, propName); }
	static Void _0x483ACA1176CA93F1() { return _i<Void>(0x483ACA1176CA93F1); }
	static Void add_pickup_to_interior_room_by_name(Pickup pickup, const char* roomName) { return _i<Void>(0x3F6167F351168730, pickup, roomName); }
	static Void cap_interior(int interiorID, bool toggle) { return _i<Void>(0xD9175F941610DB54, interiorID, toggle); }
	static Void clear_room_for_entity(Entity entity) { return _i<Void>(0xB365FC0C4E27FFA7, entity); }
	static Void _0x23B59D8912F94246() { return _i<Void>(0x23B59D8912F94246); }
	static Void disable_interior_prop(int interiorID, const char* propName) { return _i<Void>(0x420BD37289EEE162, interiorID, propName); }
	static Void disable_interior(int interiorID, bool toggle) { return _i<Void>(0x6170941419D7D8EC, interiorID, toggle); }
	static Void _0x9E6542F0CE8E70A3(bool toggle) { return _i<Void>(0x9E6542F0CE8E70A3, toggle); }
	static Void hide_map_object_this_frame(uint32_t mapObjectHash) { return _i<Void>(0xA97F257D0151A6AB, mapObjectHash); }
	static Void _0x50C375537449F369(Any p0) { return _i<Void>(0x50C375537449F369, p0); }
	static Void force_room_for_entity(Entity entity, int interiorID, uint32_t roomHashKey) { return _i<Void>(0x52923C4710DD9907, entity, interiorID, roomHashKey); }
	static Void _0x920D853F3E17F1DA(int interiorID, uint32_t roomHashKey) { return _i<Void>(0x920D853F3E17F1DA, interiorID, roomHashKey); }
	static int get_interior_at_coords(float x, float y, float z) { return _i<int>(0xB0F7F8663821D9C3, x, y, z); }
	static int get_interior_at_coords_with_type(float x, float y, float z, const char* interiorType) { return _i<int>(0x05B7A89BD78797FC, x, y, z, interiorType); }
	static int unk_get_interior_at_coords(float x, float y, float z, int unk) { return _i<int>(0xF0F77ADB9F67E79D, x, y, z, unk); }
	static int get_interior_from_collision(float x, float y, float z) { return _i<int>(0xEC4CF9FCB29A4424, x, y, z); }
	static int get_interior_from_entity(Entity entity) { return _i<int>(0x2107BA504071A6BB, entity); }
	static int get_interior_group_id(int interiorID) { return _i<int>(0xE4A84ABF135EF91A, interiorID); }
	static uint32_t get_key_for_entity_in_room(Entity entity) { return _i<uint32_t>(0x399685DB942336BC, entity); }
	static math::vector3<float> get_offset_from_interior_in_world_coords(int interiorID, float x, float y, float z) { return _i<math::vector3<float>>(0x9E3B3E6D66F6E22F, interiorID, x, y, z); }
	static uint32_t get_room_key_from_gameplay_cam() { return _i<uint32_t>(0xA6575914D2A0B450); }
	static uint32_t get_room_key_from_entity(Entity entity) { return _i<uint32_t>(0x47C2A06D4F5F424B, entity); }
	static bool are_coords_colliding_with_exterior(float x, float y, float z) { return _i<bool>(0xEEA5AC2EDA7C33E8, x, y, z); }
	static bool is_interior_capped(int interiorID) { return _i<bool>(0x92BAC8ACF88CEC26, interiorID); }
	static bool is_interior_disabled(int interiorID) { return _i<bool>(0xBC5115A5A939DD15, interiorID); }
	static bool is_interior_prop_enabled(int interiorID, const char* propName) { return _i<bool>(0x35F7DD45E8C0A16D, interiorID, propName); }
	static bool is_interior_ready(int interiorID) { return _i<bool>(0x6726BDCCC1932F0E, interiorID); }
	static bool is_interior_scene() { return _i<bool>(0xBC72B5D7A1CBD54D); }
	static bool is_valid_interior(int interiorID) { return _i<bool>(0x26B0E73D7EAAF4D3, interiorID); }
	static Void load_interior(int interiorID) { return _i<Void>(0x2CA429C029CCF247, interiorID); }
	static Void refresh_interior(int interiorID) { return _i<Void>(0x41F37C3427C75AE0, interiorID); }
	static Void _0x82EBB79E258FA2B7(Entity entity, int interiorID) { return _i<Void>(0x82EBB79E258FA2B7, entity, interiorID); }
	static Void set_interior_prop_color(int interiorID, const char* propName, int color) { return _i<Void>(0xC1F1920BAF281317, interiorID, propName, color); }
	static Any _0x4C2330E61D3DEB56(int interiorID) { return _i<Any>(0x4C2330E61D3DEB56, interiorID); }
	static Void _0x7241CCB7D020DB69(Any p0, Any p1) { return _i<Void>(0x7241CCB7D020DB69, p0, p1); }
	static Void _0x405DC2AEF6AF95B9(uint32_t roomHashKey) { return _i<Void>(0x405DC2AEF6AF95B9, roomHashKey); }
	static Void _0xAF348AFCB575A441(const char* roomName) { return _i<Void>(0xAF348AFCB575A441, roomName); }
	static Void unpin_interior(int interiorID) { return _i<Void>(0x261CCE7EED010641, interiorID); }

	static bool add_to_itemset(Any p0, Any p1) { return _i<bool>(0xE3945201F14637DD, p0, p1); }
	static Void clean_itemset(Any p0) { return _i<Void>(0x41BC0D722FC04221, p0); }
	static Any create_itemset(math::vector3<float>* distri) { return _i<Any>(0x35AD299F50D91B24, distri); }
	static Void destroy_itemset(Any p0) { return _i<Void>(0xDE18220B1C183EDA, p0); }
	static Any get_indexed_item_in_itemset(Any p0, Any p1) { return _i<Any>(0x7A197E2521EE2BAB, p0, p1); }
	static Any get_itemset_size(Any p0) { return _i<Any>(0xD9127E83ABF7C631, p0); }
	static bool is_in_itemset(Any p0, Any p1) { return _i<bool>(0x2D0FC594D1E9C107, p0, p1); }
	static bool is_itemset_valid(Any p0) { return _i<bool>(0xB1B1EA596344DFAB, p0); }
	static Void remove_from_itemset(Any p0, Any p1) { return _i<Void>(0x25E68244B0177686, p0, p1); }

	static Any _0x8AA464D4E0F6ACCD() { return _i<Any>(0x8AA464D4E0F6ACCD); }
	static bool _0xEF7D17BC6C85264C() { return _i<bool>(0xEF7D17BC6C85264C); }
	static bool is_ui_loading_multiplayer() { return _i<bool>(0xC6DC823253FBB366); }
	static Void _0xC7E7181C09F33B69(bool p0) { return _i<Void>(0xC7E7181C09F33B69, p0); }
	static Void _0xB0C56BD3D808D863(bool p0) { return _i<Void>(0xB0C56BD3D808D863, p0); }
	static Void is_in_loading_screen(bool p0) { return _i<Void>(0xFC309E94546FCDB5, p0); }
	static Void _0xFA1E0E893D915215(bool p0) { return _i<Void>(0xFA1E0E893D915215, p0); }
	static int _0xF2CA003F167E21D2() { return _i<int>(0xF2CA003F167E21D2); }

	static int get_current_language_id() { return _i<int>(0x2BDD44CC428A7EAE); }
	static int get_user_language_id() { return _i<int>(0xA8AE43AEC1A61314); }
	static Any _0x497420E022796B3F() { return _i<Any>(0x497420E022796B3F); }

	static float absf(float value) { return _i<float>(0x73D57CFFDD12C355, value); }
	static int absi(int value) { return _i<int>(0xF0D31AD191A74F87, value); }
	static float acos(float p0) { return _i<float>(0x1D08B970013C34B6, p0); }
	static Void _0xA6A12939F16D85BE(uint32_t hash, bool p1) { return _i<Void>(0xA6A12939F16D85BE, hash, p1); }
	static Any _0x918C7B2D2FF3928B(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return _i<Any>(0x918C7B2D2FF3928B, p0, p1, p2, p3, p4, p5, p6); }
	static Any _0x2D4259F1FEB81DA9(float p0, float p1, float p2, float p3) { return _i<Any>(0x2D4259F1FEB81DA9, p0, p1, p2, p3); }
	static int add_hospital_restart(float x, float y, float z, float p3, Any p4) { return _i<int>(0x1F464EF988465A81, x, y, z, p3, p4); }
	static Any add_police_restart(float p0, float p1, float p2, float p3, Any p4) { return _i<Any>(0x452736765B31FC4B, p0, p1, p2, p3, p4); }
	static Any _0x67F6413D3220E18D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Any>(0x67F6413D3220E18D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Any _0x32C7A7E8C43A1F80(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7) { return _i<Any>(0x32C7A7E8C43A1F80, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void _0x69FE6DC87BD2A5E9(Any p0) { return _i<Void>(0x69FE6DC87BD2A5E9, p0); }
	static int add_stunt_jump(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, Any p15, Any p16, Any p17) { return _i<int>(0x1A992DA297A4630C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); }
	static int add_stunt_jump_angled(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, float p15, float p16, Any p17, Any p18, Any p19) { return _i<int>(0xBBE5D803A5360CBF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); }
	static Void _0xB8721407EE9C3FF6(Any p0, Any p1, Any p2) { return _i<Void>(0xB8721407EE9C3FF6, p0, p1, p2); }
	static Void _0xDEA36202FC3382DF(bool p0) { return _i<Void>(0xDEA36202FC3382DF, p0); }
	static bool are_profile_settings_valid() { return _i<bool>(0x5AA3BEFA29F03AD4); }
	static bool are_strings_equal(const char* string1, const char* string2) { return _i<bool>(0x0C515FAB3FF9EA92, string1, string2); }
	static float asin(float p0) { return _i<float>(0xC843060B5765DCE7, p0); }
	static float atan2(float p0, float p1) { return _i<float>(0x8927CBF9D22261A4, p0, p1); }
	static float atan(float p0) { return _i<float>(0xA9D1795CD5043663, p0); }
	static Void begin_replay_stats(Any p0, Any p1) { return _i<Void>(0xE0E500246FF73D66, p0, p1); }
	static Void _0x9B2BD3773123EA2F(int type, bool toggle) { return _i<Void>(0x9B2BD3773123EA2F, type, toggle); }
	static Void _0x58A39BE597CE99CD() { return _i<Void>(0x58A39BE597CE99CD); }
	static Void cancel_stunt_jump() { return _i<Void>(0xE6B7B0ACD4E4B75E); }
	static Void _0xC79AE21974B01FB2() { return _i<Void>(0xC79AE21974B01FB2); }
	static Void clear_angled_area_of_vehicles(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, bool p8, bool p9, bool p10, bool p11, Any p12) { return _i<Void>(0x11DB3500F042A8AA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	static Void clear_area(float X, float Y, float Z, float radius, bool p4, bool ignoreCopCars, bool ignoreObjects, bool p7) { return _i<Void>(0xA56F01F3765B93A0, X, Y, Z, radius, p4, ignoreCopCars, ignoreObjects, p7); }
	static Void clear_area_of_everything(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7) { return _i<Void>(0x957838AAF91BD12D, x, y, z, radius, p4, p5, p6, p7); }
	static Void clear_area_of_cops(float x, float y, float z, float radius, int flags) { return _i<Void>(0x04F8FC8FCF58F88D, x, y, z, radius, flags); }
	static Void clear_area_of_objects(float x, float y, float z, float radius, int flags) { return _i<Void>(0xDD9B9B385AAC7F5B, x, y, z, radius, flags); }
	static Void clear_area_of_peds(float x, float y, float z, float radius, int flags) { return _i<Void>(0xBE31FD6CE464AC59, x, y, z, radius, flags); }
	static Void clear_area_of_projectiles(float x, float y, float z, float radius, int flags) { return _i<Void>(0x0A1CB9094635D1A6, x, y, z, radius, flags); }
	static Void clear_area_of_vehicles(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7, bool p8, Any p9) { return _i<Void>(0x01C7B9B38428AEB6, x, y, z, radius, p4, p5, p6, p7, p8, p9); }
	static Void clear_bit(int* address, int offset) { return _i<Void>(0xE80492A9AC099A93, address, offset); }
	static Void _0x06462A961E94B67C() { return _i<Void>(0x06462A961E94B67C); }
	static Void clear_override_weather() { return _i<Void>(0x338D2E3477711050); }
	static Void clear_replay_stats() { return _i<Void>(0x1B1AB132A16FDA55); }
	static Void set_next_respawn_to_custom() { return _i<Void>(0xA2716D40842EAF79); }
	static Void _0x7EC6F9A478A6A512() { return _i<Void>(0x7EC6F9A478A6A512); }
	static Void _0xB3CD58CCA6CDA852() { return _i<Void>(0xB3CD58CCA6CDA852); }
	static Void _0x0CF97F497FE7D048(Any p0) { return _i<Void>(0x0CF97F497FE7D048, p0); }
	static Void clear_weather_type_persist() { return _i<Void>(0xCCC39339BEF76CF5); }
	static int compare_strings(const char* str1, const char* str2, bool matchCase, int maxLength) { return _i<int>(0x1E34710ECD4AB0EB, str1, str2, matchCase, maxLength); }
	static Void _0x213AEB2B90CBA7AC(Any p0, Any p1, Any p2) { return _i<Void>(0x213AEB2B90CBA7AC, p0, p1, p2); }
	static bool create_incident(int incidentType, float x, float y, float z, int p5, float radius, int* outIncidentID, Any p7) { return _i<bool>(0x3F892CAF67444AE7, incidentType, x, y, z, p5, radius, outIncidentID, p7); }
	static bool create_incident_with_entity(int incidentType, Ped ped, int amountOfPeople, float radius, int* outIncidentID, Any p5) { return _i<bool>(0x05983472F0494E60, incidentType, ped, amountOfPeople, radius, outIncidentID, p5); }
	static Void delete_incident(int test) { return _i<Void>(0x556C1AA270D5A207, test); }
	static Void delete_stunt_jump(int p0) { return _i<Void>(0xDC518000E39DAE1F, p0); }
	static Void disable_hospital_restart(int hospitalIndex, bool toggle) { return _i<Void>(0xC8535819C450EBA8, hospitalIndex, toggle); }
	static Void disable_police_restart(int policeIndex, bool toggle) { return _i<Void>(0x23285DED6EBD7EA3, policeIndex, toggle); }
	static Void disable_stunt_jump_set(int p0) { return _i<Void>(0xA5272EBEDD4747F6, p0); }
	static Void display_onscreen_keyboard(int p0, const char* windowTitle, const char* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, int maxInputLength) { return _i<Void>(0x00DC833F2568DBF6, p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, maxInputLength); }
	static Void display_onscreen_keyboard2(int p0, const char* windowTitle, Any* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, const char* defaultConcat4, const char* defaultConcat5, const char* defaultConcat6, const char* defaultConcat7, int maxInputLength) { return _i<Void>(0xCA78CFA0366592FE, p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, defaultConcat4, defaultConcat5, defaultConcat6, defaultConcat7, maxInputLength); }
	static bool _0x1327E2FE9746BAEE(Any p0) { return _i<bool>(0x1327E2FE9746BAEE, p0); }
	static Any _0x171BAFB3C60389F4(Any p0) { return _i<Any>(0x171BAFB3C60389F4, p0); }
	static Void do_auto_save() { return _i<Void>(0x50EEAAD86232EE55); }
	static Void enable_dispatch_service(int dispatchService, bool toggle) { return _i<Void>(0xDC0F817884CDD856, dispatchService, toggle); }
	static Void enable_stunt_jump_set(int p0) { return _i<Void>(0xE369A5783B866016, p0); }
	static Void enable_tennis_mode(Ped ped, bool toggle, bool p2) { return _i<Void>(0x28A04B411933F8A6, ped, toggle, p2); }
	static Void end_replay_stats() { return _i<Void>(0xA23E821FBDF8A5F2); }
	static bool find_spawn_point_in_direction(float x1, float y1, float z1, float x2, float y2, float z2, float distance, math::vector3<float>* spawnPoint) { return _i<bool>(0x6874E2190B0C1972, x1, y1, z1, x2, y2, z2, distance, spawnPoint); }
	static Void reset_localplayer_state() { return _i<Void>(0xC0AA53F866B3134D); }
	static Void create_lightning_thunder() { return _i<Void>(0xF6062E089251C898); }
	static int get_allocated_stack_size() { return _i<int>(0x8B3CA62B1EF19B62); }
	static float get_angle_between2_d_vectors(float x1, float y1, float x2, float y2) { return _i<float>(0x186FC4BE848E1C92, x1, y1, x2, y2); }
	static bool _0xB335F761606DB47C(Any* p0, Any* p1, Any p2, bool p3) { return _i<bool>(0xB335F761606DB47C, p0, p1, p2, p3); }
	static Any _0x4750FC27570311EC() { return _i<Any>(0x4750FC27570311EC); }
	static Any _0x1B2366C3F2A5C8DF() { return _i<Any>(0x1B2366C3F2A5C8DF); }
	static int get_bits_in_range(int var, int rangeStart, int rangeEnd) { return _i<int>(0x53158863FCC0893A, var, rangeStart, rangeEnd); }
	static Any _0xD10282B6E3751BA0() { return _i<Any>(0xD10282B6E3751BA0); }
	static math::vector3<float> _0x21C235BC64831E5A(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9) { return _i<math::vector3<float>>(0x21C235BC64831E5A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static float get_cloud_hat_opacity() { return _i<float>(0x20AC25E781AE4A84); }
	static const char* get_global_char_buffer() { return _i<const char*>(0x24DA7D7667FD7B09); }
	static Any _0x8D7A43EC6A5FEA45(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return _i<Any>(0x8D7A43EC6A5FEA45, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static bool _0xDFB4138EEFED7B81(Ped ped, uint32_t weaponHash, float radius, Entity* entity, bool p4) { return _i<bool>(0xDFB4138EEFED7B81, ped, weaponHash, radius, entity, p4); }
	static Void get_weather_type_transition(Any* p0, Any* p1, float* progress_or_time) { return _i<Void>(0xF3BBE884A14BB413, p0, p1, progress_or_time); }
	static float get_distance_between_coords(float x1, float y1, float z1, float x2, float y2, float z2, bool useZ) { return _i<float>(0xF1B760881820C952, x1, y1, z1, x2, y2, z2, useZ); }
	static int get_fake_wanted_level() { return _i<int>(0x4C9296CBCD1B971E); }
	static int get_frame_count() { return _i<int>(0xFC8202EFC642E6F2); }
	static float get_frame_time() { return _i<float>(0x15C40837039FFAF7); }
	static int get_game_timer() { return _i<int>(0x9CD27B0045628463); }
	static bool get_ground_coords_while_in_air(float x, float y, float z, float* p3, math::vector3<float>* p4) { return _i<bool>(0x8BDC7BFC57A81E76, x, y, z, p3, p4); }
	static Any _0x9E82F0F362881B29(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Any>(0x9E82F0F362881B29, p0, p1, p2, p3, p4); }
	static bool get_ground_z_for_3d_coord(float x, float y, float z, float* groundZ, bool unk) { return _i<bool>(0xC906A7DAB05C8D2B, x, y, z, groundZ, unk); }
	static uint32_t get_hash_key(const char* model) { return _i<uint32_t>(0xD24D37CC275948CC, model); }
	static float get_heading_from_vector_2d(float dx, float dy) { return _i<float>(0x2FFB6B224F4B2926, dx, dy); }
	static int get_index_of_current_level() { return _i<int>(0xCBAD6729F7B1F4FC); }
	static Any _0x6E04F06094C87047() { return _i<Any>(0x6E04F06094C87047); }
	static bool _0x9689123E3F213AA5() { return _i<bool>(0x9689123E3F213AA5); }
	static bool _0xF56DFB7B61BE7276(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, Any* p12) { return _i<bool>(0xF56DFB7B61BE7276, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	static bool get_mission_flag() { return _i<bool>(0xA33CDCCDA663159E); }
	static Void get_model_dimensions(uint32_t modelHash, math::vector3<float>* minimum, math::vector3<float>* maximum) { return _i<Void>(0x03E8D3D5F549087A, modelHash, minimum, maximum); }
	static uint32_t get_next_weather_type_hash_name() { return _i<uint32_t>(0x711327CD09C8F162); }
	static int get_free_stack_slots_count(int stackSize) { return _i<int>(0xFEAD16FC8F9DFC0F, stackSize); }
	static int get_number_of_dispatched_units_for_player(int dispatchService) { return _i<int>(0xEB4A0C2D56441717, dispatchService); }
	static Any _0x996DD1E1E02F1008() { return _i<Any>(0x996DD1E1E02F1008); }
	static const char* get_onscreen_keyboard_result() { return _i<const char*>(0x8362B09B91893647); }
	static uint32_t get_prev_weather_type_hash_name() { return _i<uint32_t>(0x564B884A05EC45A3); }
	static int get_profile_setting(int profileSetting) { return _i<int>(0xC488FF2356EA7791, profileSetting); }
	static Any _0x82FDE6A57EE4EE44(Ped ped, uint32_t weaponhash, float p2, float p3, float p4, bool p5) { return _i<Any>(0x82FDE6A57EE4EE44, ped, weaponhash, p2, p3, p4, p5); }
	static Any get_rain_level() { return _i<Any>(0x96695E368AD855F3); }
	static Any get_random_event_flag() { return _i<Any>(0xD2D57F1D764117B1); }
	static float get_random_float_in_range(float startRange, float endRange) { return _i<float>(0x313CE5879CEB6FCD, startRange, endRange); }
	static int get_random_int_in_range(int startRange, int endRange) { return _i<int>(0xD53343AA4FB7DD28, startRange, endRange); }
	static float _0x7F8F6405F4777AF6(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9) { return _i<float>(0x7F8F6405F4777AF6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Any _0x8098C8D6597AAE18(Any p0) { return _i<Any>(0x8098C8D6597AAE18, p0); }
	static Any _0xDC9274A7EF6B2867() { return _i<Any>(0xDC9274A7EF6B2867); }
	static Any _0x5B1F2E327B6B6FE1() { return _i<Any>(0x5B1F2E327B6B6FE1); }
	static Any _0x2B626A0150E4D449() { return _i<Any>(0x2B626A0150E4D449); }
	static Any _0xA4A0065E39C9F25C(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xA4A0065E39C9F25C, p0, p1, p2, p3); }
	static Any _0xA09F896CE912481F(bool p0) { return _i<Any>(0xA09F896CE912481F, p0); }
	static Any get_snow_level() { return _i<Any>(0xC5868A966E5BE3AE); }
	static int _0x397BAA01068BAA96() { return _i<int>(0x397BAA01068BAA96); }
	static Any _0x2B5E102E4A42F2BF() { return _i<Any>(0x2B5E102E4A42F2BF); }
	static float _0xE599A503B3837E1B() { return _i<float>(0xE599A503B3837E1B); }
	static bool _0x19BFED045C647C49(Any p0) { return _i<bool>(0x19BFED045C647C49, p0); }
	static bool _0x17DF68D720AA77F8(Any p0) { return _i<bool>(0x17DF68D720AA77F8, p0); }
	static bool _0xE95B0C7D5BA3B96B(Any p0) { return _i<bool>(0xE95B0C7D5BA3B96B, p0); }
	static Any _0x6856EC3D35C81EA4() { return _i<Any>(0x6856EC3D35C81EA4); }
	static math::vector3<float> get_wind_direction() { return _i<math::vector3<float>>(0x1F400FEF721170DA); }
	static float get_wind_speed() { return _i<float>(0xA8CF1CC0AFCD3F12); }
	static Any _0x14832BF2ABA53FC5() { return _i<Any>(0x14832BF2ABA53FC5); }
	static bool has_bullet_impacted_in_area(float x, float y, float z, float p3, bool p4, bool p5) { return _i<bool>(0x9870ACFB89A90995, x, y, z, p3, p4, p5); }
	static bool has_bullet_impacted_in_box(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7) { return _i<bool>(0xDC8C5D7CFEAB8394, p0, p1, p2, p3, p4, p5, p6, p7); }
	static bool has_button_combination_just_been_entered(uint32_t hash, int amount) { return _i<bool>(0x071E2A839DE82D90, hash, amount); }
	static Any _0x2107A3773771186D() { return _i<Any>(0x2107A3773771186D); }
	static bool _0x6FDDF453C0C756EC() { return _i<bool>(0x6FDDF453C0C756EC); }
	static bool has_cheat_string_just_been_entered(uint32_t hash) { return _i<bool>(0x557E43C447E700A8, hash); }
	static Any _0xE8B9C0EC9E183F35() { return _i<Any>(0xE8B9C0EC9E183F35); }
	static bool is_pc_version() { return _i<bool>(0x48AF36444B965238); }
	static Any _0x075F1D57402C93BA() { return _i<Any>(0x075F1D57402C93BA); }
	static Any _0xD642319C54AADEB6() { return _i<Any>(0xD642319C54AADEB6); }
	static Void ignore_next_restart(bool toggle) { return _i<Void>(0x21FFB63D8C615361, toggle); }
	static Void _0x8D74E26F54B4E5C3(const char* p0) { return _i<Void>(0x8D74E26F54B4E5C3, p0); }
	static bool is_area_occupied(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9, bool p10, Any p11, bool p12) { return _i<bool>(0xA61B4DF533DCB56E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	static bool is_auto_save_in_progress() { return _i<bool>(0x69240733738C19A0); }
	static bool is_bit_set(int address, int offset) { return _i<bool>(0xA921AA820C25702F, address, offset); }
	static bool is_bullet_in_angled_area(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7) { return _i<bool>(0x1A8B5F3C01E2B477, p0, p1, p2, p3, p4, p5, p6, p7); }
	static bool is_bullet_in_area(float p0, float p1, float p2, float p3, bool p4) { return _i<bool>(0x3F2023999AD51C1F, p0, p1, p2, p3, p4); }
	static bool is_bullet_in_box(float p0, float p1, float p2, float p3, float p4, float p5, bool p6) { return _i<bool>(0xDE0F6D7450D37351, p0, p1, p2, p3, p4, p5, p6); }
	static Any _0xA049A5BE0F04F2F8() { return _i<Any>(0xA049A5BE0F04F2F8); }
	static bool is_incident_valid(int incidentId) { return _i<bool>(0xC8BC6461E629BEAA, incidentId); }
	static bool is_memory_card_in_use() { return _i<bool>(0x8A75CE2956274ADD); }
	static bool is_minigame_in_progress() { return _i<bool>(0x2B4A15E44DE0F478); }
	static bool is_next_weather_type(const char* weatherType) { return _i<bool>(0x2FAA3A30BEC0F25D, weatherType); }
	static bool is_point_obscured_by_a_mission_entity(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return _i<bool>(0xE54E209C35FFA18D, p0, p1, p2, p3, p4, p5, p6); }
	static bool is_position_occupied(float x, float y, float z, float range, bool p4, bool p5, bool p6, bool p7, bool p8, Any p9, bool p10) { return _i<bool>(0xADCDE75E1C60F32D, x, y, z, range, p4, p5, p6, p7, p8, p9, p10); }
	static bool is_prev_weather_type(const char* weatherType) { return _i<bool>(0x44F28F86433B10A9, weatherType); }
	static bool is_projectile_in_area(float x1, float y1, float z1, float x2, float y2, float z2, bool ownedByPlayer) { return _i<bool>(0x5270A8FBC098C3F8, x1, y1, z1, x2, y2, z2, ownedByPlayer); }
	static bool is_projectile_type_in_angled_area(float p0, float p1, float p2, float p3, float p4, float p5, float p6, Any p7, bool p8) { return _i<bool>(0xF0BC12401061DEA0, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static bool is_projectile_type_in_area(float x1, float y1, float z1, float x2, float y2, float z2, int type, bool p7) { return _i<bool>(0x2E0DC353342C4A6D, x1, y1, z1, x2, y2, z2, type, p7); }
	static bool _0x34318593248C8FB2(float p0, float p1, float p2, Any p3, float p4, bool p5) { return _i<bool>(0x34318593248C8FB2, p0, p1, p2, p3, p4, p5); }
	static bool is_sniper_bullet_in_area(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<bool>(0xFEFCF11B01287125, x1, y1, z1, x2, y2, z2); }
	static bool is_string_null(const char* string) { return _i<bool>(0xF22B6C47C6EAB066, string); }
	static bool is_string_null_or_empty(const char* string) { return _i<bool>(0xCA042B6957743895, string); }
	static bool is_stunt_jump_in_progress() { return _i<bool>(0x7A3F19700A4D0525); }
	static bool is_stunt_jump_message_showing() { return _i<bool>(0x2272B0A1343129F4); }
	static bool is_tennis_mode(Ped ped) { return _i<bool>(0x5D5479D115290C3F, ped); }
	static bool is_this_a_minigame_script() { return _i<bool>(0x7B30F65D7B710098); }
	static Any _0x3BBBD13E5041A79E() { return _i<Any>(0x3BBBD13E5041A79E); }
	static Void set_cloud_hat_transition(const char* type, float transitionTime) { return _i<Void>(0xFC4842A34657BFCB, type, transitionTime); }
	static Void network_set_script_is_safe_for_network_game() { return _i<Void>(0x9243BAC96D64C050); }
	static Void _0x3ED1438C1F5C6612(int p0) { return _i<Void>(0x3ED1438C1F5C6612, p0); }
	static bool override_save_house(bool p0, float p1, float p2, float p3, float p4, bool p5, float p6, float p7) { return _i<bool>(0x1162EA8AE9D24EEA, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void disable_automatic_respawn(bool disableRespawn) { return _i<Void>(0x2C2B3493FBF51C71, disableRespawn); }
	static Void _0x8FA9C42FC5D7C64B(Any p0, Any p1, float p2, float p3, float p4, bool p5) { return _i<Void>(0x8FA9C42FC5D7C64B, p0, p1, p2, p3, p4, p5); }
	static Void _0xE266ED23311F24D4(Any p0, Any* p1, Any* p2, float p3, float p4, bool p5) { return _i<Void>(0xE266ED23311F24D4, p0, p1, p2, p3, p4, p5); }
	static Any _0xABB2FA71C83A1B72() { return _i<Any>(0xABB2FA71C83A1B72); }
	static bool _0x684A41975F077262() { return _i<bool>(0x684A41975F077262); }
	static Void populate_now() { return _i<Void>(0x7472BB270D7B4F3E); }
	static Void _0x11B56FBBF7224868(const char* p0) { return _i<Void>(0x11B56FBBF7224868, p0); }
	static Void _0xE3D969D2785FFB5E() { return _i<Void>(0xE3D969D2785FFB5E); }
	static Any _0x72DE52178C291CB5() { return _i<Any>(0x72DE52178C291CB5); }
	static Any _0x44A0BDC559B35F6E() { return _i<Any>(0x44A0BDC559B35F6E); }
	static Any _0xEB2104E905C6F2E9() { return _i<Any>(0xEB2104E905C6F2E9); }
	static Void force_social_club_update() { return _i<Void>(0xEB6891F03362FB12); }
	static Void register_float_to_save(Any* p0, const char* name) { return _i<Void>(0x7CAEC29ECB5DFEBB, p0, name); }
	static Void _0xA735353C77334EA0(Any* p0, Any* p1) { return _i<Void>(0xA735353C77334EA0, p0, p1); }
	static Void register_int_to_save(Any* p0, const char* name) { return _i<Void>(0x34C9EE5986258415, p0, name); }
	static Void register_enum_to_save(Any* p0, const char* name) { return _i<Void>(0x10C2FA78D0E128A1, p0, name); }
	static Void register_bool_to_save(Any* p0, const char* name) { return _i<Void>(0xC8F4131414C835A1, p0, name); }
	static Any register_save_house(float p0, float p1, float p2, float p3, Any* p4, Any p5, Any p6) { return _i<Any>(0xC0714D0A7EEECA54, p0, p1, p2, p3, p4, p5, p6); }
	static Void register_text_label_to_save(Any* p0, const char* name) { return _i<Void>(0xEDB1232C5BEAE62F, p0, name); }
	static Void _0x6F7794F28C6B2535(Any* p0, const char* name) { return _i<Void>(0x6F7794F28C6B2535, p0, name); }
	static Void _0x48F069265A0E4BEC(Any* p0, const char* name) { return _i<Void>(0x48F069265A0E4BEC, p0, name); }
	static Void _0x8269816F6CFD40F8(Any* p0, const char* name) { return _i<Void>(0x8269816F6CFD40F8, p0, name); }
	static Void _0xFAA457EF263E8763(Any* p0, const char* name) { return _i<Void>(0xFAA457EF263E8763, p0, name); }
	static Void remove_dispatch_spawn_blocking_area(Any p0) { return _i<Void>(0x264AC28B01B353A5, p0); }
	static Void _0xB129E447A2EDA4BF(Any p0, bool p1) { return _i<Void>(0xB129E447A2EDA4BF, p0, p1); }
	static Void _0xE6869BECDD8F2403(Any p0, bool p1) { return _i<Void>(0xE6869BECDD8F2403, p0, p1); }
	static Void reset_dispatch_ideal_spawn_distance() { return _i<Void>(0x77A84429DD9F0A15); }
	static Void reset_dispatch_spawn_blocking_areas() { return _i<Void>(0xAC7BFD5C1D83EA75); }
	static Void _0xEB2DB0CAD13154B3(Any p0) { return _i<Void>(0xEB2DB0CAD13154B3, p0); }
	static Void _0x437138B6A830166A() { return _i<Void>(0x437138B6A830166A); }
	static Void _0xD9F692D349249528() { return _i<Void>(0xD9F692D349249528); }
	static Void _0xE574A662ACAEFBB1() { return _i<Void>(0xE574A662ACAEFBB1); }
	static Void _0x37DEB0AA183FB6D8() { return _i<Void>(0x37DEB0AA183FB6D8); }
	static bool _0x8EF5573A1F801A5C(Any p0, Any* p1, Any* p2) { return _i<bool>(0x8EF5573A1F801A5C, p0, p1, p2); }
	static Void _0x0A60017F841A54F2(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0A60017F841A54F2, p0, p1, p2, p3); }
	static Void _0x1BB299305C3E8C13(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x1BB299305C3E8C13, p0, p1, p2, p3); }
	static Void _0x1FF6BF9A63E5757F() { return _i<Void>(0x1FF6BF9A63E5757F); }
	static Void _0x438822C279B73B93(Any p0) { return _i<Void>(0x438822C279B73B93, p0); }
	static Void set_bit(int* address, int offset) { return _i<Void>(0x933D6A9EEC1BACD0, address, offset); }
	static Void set_bits_in_range(int* var, int rangeStart, int rangeEnd, int p3) { return _i<Void>(0x8EF07E15701D61ED, var, rangeStart, rangeEnd, p3); }
	static Void set_cloud_hat_opacity(float opacity) { return _i<Void>(0xF36199225D6D8C86, opacity); }
	static Void _0x02DEAAC8F8EA7FE7(const char* p0) { return _i<Void>(0x02DEAAC8F8EA7FE7, p0); }
	static Void set_credits_active(bool toggle) { return _i<Void>(0xB938B7E6D3C0620C, toggle); }
	static Void _0xB51B9AB9EF81868C(bool toggle) { return _i<Void>(0xB51B9AB9EF81868C, toggle); }
	static Void set_weather_type_transition(uint32_t weatherType1, uint32_t weatherType2, float percentWeather2) { return _i<Void>(0x578C752848ECFA0C, weatherType1, weatherType2, percentWeather2); }
	static Void set_dispatch_ideal_spawn_distance(float p0) { return _i<Void>(0x6FE601A64180D423, p0); }
	static Void _0xD10F442036302D50(Any p0, Any p1, Any p2) { return _i<Void>(0xD10F442036302D50, p0, p1, p2); }
	static Void set_dispatch_time_between_spawn_attempts(Any p0, float p1) { return _i<Void>(0x44F7CBC1BEB3327D, p0, p1); }
	static Void set_dispatch_time_between_spawn_attempts_multiplier(Any p0, float p1) { return _i<Void>(0x48838ED9937A15D1, p0, p1); }
	static Void set_explosive_ammo_this_frame(Player player) { return _i<Void>(0xA66C71C98D5F2CFB, player); }
	static Void set_explosive_melee_this_frame(Player player) { return _i<Void>(0xFF1BED81BFDC0FE0, player); }
	static Void set_fade_in_after_death_arrest(bool toggle) { return _i<Void>(0xDA66D2796BA33F12, toggle); }
	static Void set_fade_in_after_load(bool toggle) { return _i<Void>(0xF3D78F59DFE18D79, toggle); }
	static Void set_fade_out_after_arrest(bool toggle) { return _i<Void>(0x1E0B4DC0D990A4E7, toggle); }
	static Void set_fade_out_after_death(bool toggle) { return _i<Void>(0x4A18E01DF2C87B86, toggle); }
	static Void set_fake_wanted_level(int fakeWantedLevel) { return _i<Void>(0x1454F2448DE30163, fakeWantedLevel); }
	static Void set_fire_ammo_this_frame(Player player) { return _i<Void>(0x11879CDD803D30F4, player); }
	static Void _0xA1183BCFEE0F93D1(Any p0) { return _i<Void>(0xA1183BCFEE0F93D1, p0); }
	static Void set_game_paused(bool toggle) { return _i<Void>(0x577D1284D6873711, toggle); }
	static Void set_gravity_level(int level) { return _i<Void>(0x740E14FAD5842351, level); }
	static Void _0xD261BA3E7E998072(Any p0, float p1) { return _i<Void>(0xD261BA3E7E998072, p0, p1); }
	static Void _0xB08B85D860E7BA3C(Any p0, Any p1, Any p2) { return _i<Void>(0xB08B85D860E7BA3C, p0, p1, p2); }
	static Void set_unk_map_flag(int flag) { return _i<Void>(0xC5F0A8EBD3F361CE, flag); }
	static Void use_freemode_map_behavior(bool toggle) { return _i<Void>(0x9BAE5AD2508DF078, toggle); }
	static Void set_minigame_in_progress(bool toggle) { return _i<Void>(0x19E00D7322C6F85B, toggle); }
	static Void set_mission_flag(bool toggle) { return _i<Void>(0xC4301E5121A0ED73, toggle); }
	static Void set_override_weather(const char* weatherType) { return _i<Void>(0xA43D5C6FE51ADBEF, weatherType); }
	static Void show_ped_in_pause_menu(bool toggle) { return _i<Void>(0x4EBB7E87AA0DBED4, toggle); }
	static Void _0x9D8D44ADBBA61EF2(bool p0) { return _i<Void>(0x9D8D44ADBBA61EF2, p0); }
	static Void set_rain_fx_intensity(float intensity) { return _i<Void>(0x643E26EA6E024D92, intensity); }
	static Void set_random_event_flag(bool p0) { return _i<Void>(0x971927086CFD2158, p0); }
	static Void set_random_seed(int time) { return _i<Void>(0x444D98F98C11F3EC, time); }
	static Void set_randoweather_type() { return _i<Void>(0x8B05F884CF7E8020); }
	static Void set_custom_respawn_position(float x, float y, float z, float heading) { return _i<Void>(0x706B5EDCAA7FA663, x, y, z, heading); }
	static Void _0x2587A48BC88DFADF(bool p0) { return _i<Void>(0x2587A48BC88DFADF, p0); }
	static Void set_save_house(Any p0, bool p1, bool p2) { return _i<Void>(0x4F548CABEAE553BC, p0, p1, p2); }
	static Void set_save_menu_active(bool unk) { return _i<Void>(0xC9BF75D28165FF77, unk); }
	static Void _0x65D2EBB47E1CEC21(bool p0) { return _i<Void>(0x65D2EBB47E1CEC21, p0); }
	static Void _0xD79185689F8FD5DF(bool p0) { return _i<Void>(0xD79185689F8FD5DF, p0); }
	static Void set_super_jump_this_frame(Player player) { return _i<Void>(0x57FFF03E423A4C0B, player); }
	static Void _0x54F157E0336A3822(Any p0, const char* p1, float p2) { return _i<Void>(0x54F157E0336A3822, p0, p1, p2); }
	static Void _0x6F2135B6129620C1(bool p0) { return _i<Void>(0x6F2135B6129620C1, p0); }
	static Void set_this_script_can_be_paused(bool toggle) { return _i<Void>(0xAA391C728106F7AF, toggle); }
	static Void set_this_script_can_remove_blips_created_by_any_script(bool toggle) { return _i<Void>(0xB98236CAAECEF897, toggle); }
	static Void _0xFB00CA71DA386228() { return _i<Void>(0xFB00CA71DA386228); }
	static Void set_time_scale(float time) { return _i<Void>(0x1D408577D440E81E, time); }
	static Void _0xE532EC1A63231B4F(Any p0, Any p1) { return _i<Void>(0xE532EC1A63231B4F, p0, p1); }
	static Void set_weather_type_now(const char* weatherType) { return _i<Void>(0x29B487C359E19889, weatherType); }
	static Void set_weather_type_now_persist(const char* weatherType) { return _i<Void>(0xED712CA327900C8A, weatherType); }
	static Void set_weather_type_over_time(const char* weatherType, float time) { return _i<Void>(0xFB5045B7C42B75BF, weatherType, time); }
	static Void set_weather_type_persist(const char* weatherType) { return _i<Void>(0x704983DF373B198F, weatherType); }
	static Void set_wind(float speed) { return _i<Void>(0xAC3A74E8384A9919, speed); }
	static Void set_wind_direction(float direction) { return _i<Void>(0xEB0F4468467B4528, direction); }
	static Void set_wind_speed(float speed) { return _i<Void>(0xEE09ECEDBABE47FC, speed); }
	static Void shoot_single_bullet_between_coords(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, uint32_t weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed) { return _i<Void>(0x867654CBC7606F2C, x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed); }
	static Void shoot_single_bullet_between_coords_ignore_entity(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, uint32_t weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, Any p14) { return _i<Void>(0xE3A7742E0B7A2F8B, x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14); }
	static Void shoot_single_airstrike_bullet_between_coords(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, uint32_t weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, bool p14, bool p15, bool p16, bool p17, Any p18, Any p19) { return _i<Void>(0xBFE5756E7407064A, x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14, p15, p16, p17, p18, p19); }
	static Any _0xD3D15555431AB793() { return _i<Any>(0xD3D15555431AB793); }
	static Void _0xF2F6A2FA49278625(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, Any* p9, Any* p10, Any* p11, Any* p12) { return _i<Void>(0xF2F6A2FA49278625, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	static Void _0x92790862E36C2ADA() { return _i<Void>(0x92790862E36C2ADA); }
	static Void start_save_array(Any* p0, int p1, const char* arrayName) { return _i<Void>(0x60FE567DF1B1AF9D, p0, p1, arrayName); }
	static Void start_save_data(Any* p0, Any p1, bool p2) { return _i<Void>(0xA9575F812C6A7997, p0, p1, p2); }
	static Void start_save_struct(Any* p0, int p1, const char* structName) { return _i<Void>(0xBF737600CDDBEADD, p0, p1, structName); }
	static Void _0xC7DB36C24634F52B() { return _i<Void>(0xC7DB36C24634F52B); }
	static Void stop_save_data() { return _i<Void>(0x74E20C9145FB66FD); }
	static Void stop_save_struct() { return _i<Void>(0xEB1774DF12BB9F12); }
	static Void stop_save_array() { return _i<Void>(0x04456F95153C6BE4); }
	static bool string_to_int(const char* string, int* outInteger) { return _i<bool>(0x5A5F40FE637EB584, string, outInteger); }
	static Void _0x1EAE0A6E978894A2(int p0, bool p1) { return _i<Void>(0x1EAE0A6E978894A2, p0, p1); }
	static float tan(float p0) { return _i<float>(0x632106CC96E82E91, p0); }
	static Void terminate_all_scripts_with_this_name(const char* scriptName) { return _i<Void>(0x9DC711BC69C548DF, scriptName); }
	static Void _0xFB80AB299D2EE1BD(Any p0) { return _i<Void>(0xFB80AB299D2EE1BD, p0); }
	static Any _0xEA2F2061875EED90() { return _i<Any>(0xEA2F2061875EED90); }
	static Void clear_cloud_hat() { return _i<Void>(0x957E790EA1727B64); }
	static Void _0xA74802FB8D0B7814(const char* p0, float p1) { return _i<Void>(0xA74802FB8D0B7814, p0, p1); }
	static int update_onscreen_keyboard() { return _i<int>(0x0CF2B696BBF945AE); }
	static Void _0x693478ACBD7F18E7() { return _i<Void>(0x693478ACBD7F18E7); }
	static Void using_mission_creator(bool toggle) { return _i<Void>(0xF14878FC50BEC6EE, toggle); }
	static Void _0xA8434F1DFF41D6E7(float p0) { return _i<Void>(0xA8434F1DFF41D6E7, p0); }
	static Void _0xC3C221ADDDE31A11(float p0) { return _i<Void>(0xC3C221ADDDE31A11, p0); }
	static Void _0x31727907B2C43C55(float p0) { return _i<Void>(0x31727907B2C43C55, p0); }
	static Void _0x405591EC8FD9096D(float p0) { return _i<Void>(0x405591EC8FD9096D, p0); }
	static Void _0xB3E6360DDE733E82(float p0) { return _i<Void>(0xB3E6360DDE733E82, p0); }
	static Void _0xF751B16FB32ABC1D(float p0) { return _i<Void>(0xF751B16FB32ABC1D, p0); }
	static Void _0x7C9C0B1EEB1F9072(float p0) { return _i<Void>(0x7C9C0B1EEB1F9072, p0); }
	static Void _0xB9854DFDE0D833D6(float p0) { return _i<Void>(0xB9854DFDE0D833D6, p0); }
	static Void _0x9F5E6BB6B34540DA(float p0) { return _i<Void>(0x9F5E6BB6B34540DA, p0); }
	static Void _0x6216B116083A7CB4(float p0) { return _i<Void>(0x6216B116083A7CB4, p0); }
	static Void _0xB8F87EAD7533B176(float p0) { return _i<Void>(0xB8F87EAD7533B176, p0); }
	static Void _0xA7A1127490312C36(float p0) { return _i<Void>(0xA7A1127490312C36, p0); }
	static Void _0xC3EAD29AB273ECE8(float p0) { return _i<Void>(0xC3EAD29AB273ECE8, p0); }
	static Void _0xC54A08C85AE4D410(float p0) { return _i<Void>(0xC54A08C85AE4D410, p0); }
	static bool is_sniper_inverted() { return _i<bool>(0x61A23B7EDA9BDA24); }
	static bool is_orbis_version() { return _i<bool>(0xA72BC0B675B1519E); }
	static bool is_durango_version() { return _i<bool>(0x4D982ADB1978442D); }
	static bool is_xbox360_version() { return _i<bool>(0xF6201B4DAF662A9D); }
	static bool is_ps3_version() { return _i<bool>(0xCCA1072C29D096C2); }
	static bool is_aussie_version() { return _i<bool>(0x9F1935CA1F724008); }
	static bool is_frontend_fading() { return _i<bool>(0x7EA2B6AF97ECA6ED); }
	static Void _0x4DCDF92BF64236CD(Any p0, Any p1) { return _i<Void>(0x4DCDF92BF64236CD, p0, p1); }
	static Void _0x31125FD509D9043F(Any p0) { return _i<Void>(0x31125FD509D9043F, p0); }
	static Void _0xEBD3205A207939ED(Any p0) { return _i<Void>(0xEBD3205A207939ED, p0); }
	static Void _0x97E7E2C04245115B(Any p0) { return _i<Void>(0x97E7E2C04245115B, p0); }
	static Void _0xEB078CA2B5E82ADD(Any p0, Any p1) { return _i<Void>(0xEB078CA2B5E82ADD, p0, p1); }
	static Void _0x703CC7F60CBB2B57(Any p0) { return _i<Void>(0x703CC7F60CBB2B57, p0); }
	static Void _0x8951EB9C6906D3C8() { return _i<Void>(0x8951EB9C6906D3C8); }
	static Void _0xBA4B8D83BDC75551(Any p0) { return _i<Void>(0xBA4B8D83BDC75551, p0); }
	static Void _0x23227DF0B2115469() { return _i<Void>(0x23227DF0B2115469); }

	static Any _0x9777734DAD16992F() { return _i<Any>(0x9777734DAD16992F); }
	static bool _0xE260E0BB9CD995AC(Any p0) { return _i<bool>(0xE260E0BB9CD995AC, p0); }
	static Any _0xE154B48B68EF72BC(Any p0) { return _i<Any>(0xE154B48B68EF72BC, p0); }
	static Any _0x6FCF8DDEA146C45B(Any p0) { return _i<Any>(0x6FCF8DDEA146C45B, p0); }
	static Void network_buy_airstrike(int cost, bool p1, bool p2) { return _i<Void>(0x763B4BD305338F19, cost, p1, p2); }
	static Any _0xA3EDDAA42411D3B9() { return _i<Any>(0xA3EDDAA42411D3B9); }
	static Void network_buy_bounty(int amount, Player victim, bool p2, bool p3) { return _i<Void>(0x7B718E197453F2D9, amount, victim, p2, p3); }
	static Void _0x30FD873ECE50E9F6(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x30FD873ECE50E9F6, p0, p1, p2, p3, p4); }
	static Void network_buy_fairground_ride(int amountSpent, Any p1, bool p2, bool p3) { return _i<Void>(0x8A7B3952DD64D2B5, amountSpent, p1, p2, p3); }
	static Void network_buy_healthcare(int cost, bool p1, bool p2) { return _i<Void>(0xD9B067E55253E3DD, cost, p1, p2); }
	static Void network_buy_heli_strike(int cost, bool p1, bool p2) { return _i<Void>(0x81AA4610E3FD3A69, cost, p1, p2); }
	static Void network_buy_item(Ped player, uint32_t item, Any p2, Any p3, bool p4, const char* item_name, Any p6, Any p7, Any p8, bool p9) { return _i<Void>(0xF0077C797F66A355, player, item, p2, p3, p4, item_name, p6, p7, p8, p9); }
	static Any _0xD987F2489969668C() { return _i<Any>(0xD987F2489969668C); }
	static Void network_buy_property(float propertyCost, uint32_t propertyName, bool p2, bool p3) { return _i<Void>(0x650A08A280870AF6, propertyCost, propertyName, p2, p3); }
	static Any _0x75AF80E61248EEBD() { return _i<Any>(0x75AF80E61248EEBD); }
	static bool network_can_bet(Any p0) { return _i<bool>(0x3A54E33660DED67F, p0); }
	static Any _0xC62DD18375C99130() { return _i<Any>(0xC62DD18375C99130); }
	static bool network_can_receive_player_cash(Any p0, Any p1, Any p2, Any p3) { return _i<bool>(0x5D17BE59D2123284, p0, p1, p2, p3); }
	static Any _0x1C2473301B1C66BA() { return _i<Any>(0x1C2473301B1C66BA); }
	static bool _0x7303E27CC6532080(Any p0, bool p1, bool p2, bool p3, Any* p4, Any p5) { return _i<bool>(0x7303E27CC6532080, p0, p1, p2, p3, p4, p5); }
	static bool network_can_spend_money(Any p0, bool p1, bool p2, bool p3, Any p4) { return _i<bool>(0xAB3CAA6B422164DA, p0, p1, p2, p3, p4); }
	static Void network_clear_character_wallet(Any p0) { return _i<Void>(0xA921DED15FDF28F5, p0); }
	static Any _0x18B7AE224B087E26() { return _i<Any>(0x18B7AE224B087E26); }
	static Void network_delete_character(int characterIndex, bool p1, bool p2) { return _i<Void>(0x05A50AF38947EB8D, characterIndex, p1, p2); }
	static Void _0x0CB1BE0633C024A8(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0CB1BE0633C024A8, p0, p1, p2, p3); }
	static Void _0x08B0CA7A6AB3AC32(Any p0, Any p1, Any p2) { return _i<Void>(0x08B0CA7A6AB3AC32, p0, p1, p2); }
	static Void network_earn_from_ai_target_kill(Any p0, Any p1) { return _i<Void>(0x515B4A22E4D3C6D7, p0, p1); }
	static Void network_earn_from_ambient_job(int p0, const char* p1, Any* p2) { return _i<Void>(0xFB6DB092FBAE29E6, p0, p1, p2); }
	static Void network_earn_from_bend_job(int amount, const char* heistHash) { return _i<Void>(0x61326EE6DF15B0CA, amount, heistHash); }
	static Void network_earn_from_betting(int amount, const char* p1) { return _i<Void>(0x827A5BA1A44ACA6D, amount, p1); }
	static Void network_earn_from_bounty(int amount, int* network_handle, Any* p2, Any p3) { return _i<Void>(0x131BB5DA15453ACF, amount, network_handle, p2, p3); }
	static Void _0x8586789730B10CAF(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x8586789730B10CAF, p0, p1, p2, p3); }
	static Void network_earn_from_challenge_win(Any p0, Any* p1, bool p2) { return _i<Void>(0x2B171E6B2F64D8DF, p0, p1, p2); }
	static Void _0xECA658CE2A4E5A72(Any p0, Any p1) { return _i<Void>(0xECA658CE2A4E5A72, p0, p1); }
	static Void network_earn_from_crate_drop(int amount) { return _i<Void>(0xB1CC1B9EC3007A2A, amount); }
	static Void network_earn_from_daily_objectives(int p0, const char* p1, int p2) { return _i<Void>(0x6EA318C91C1A8786, p0, p1, p2); }
	static Void _0x84C0116D012E8FC2(Any p0) { return _i<Void>(0x84C0116D012E8FC2, p0); }
	static Void network_earn_from_gangattack_pickup(int amount) { return _i<Void>(0xA03D4ACE0A3284CE, amount); }
	static Void _0x31BA138F6304FB9F(Any p0, Any p1) { return _i<Void>(0x31BA138F6304FB9F, p0, p1); }
	static Void network_earn_from_holdups(int amount) { return _i<Void>(0x45B8154E077D9E4D, amount); }
	static Void network_earn_from_import_export(Any p0, Any p1) { return _i<Void>(0xF92A014A634442D6, p0, p1); }
	static Void network_earn_from_job(int amount, const char* p1) { return _i<Void>(0xB2CC4836834E8A98, amount, p1); }
	static Void network_earn_from_job_bonus(Any p0, Any* p1, Any* p2) { return _i<Void>(0x6816FB4416760775, p0, p1, p2); }
	static Void network_earn_from_not_badsport(int amount) { return _i<Void>(0x4337511FA8221D36, amount); }
	static Void network_earn_from_personal_vehicle(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return _i<Void>(0x3F4D00167E41E0AD, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Void network_earn_from_pickup(int amount) { return _i<Void>(0xED1517D3AF17C698, amount); }
	static Void _0xC8407624CEF2354B(Any p0, Any p1) { return _i<Void>(0xC8407624CEF2354B, p0, p1); }
	static Void network_earn_from_property(int amount, uint32_t propertyName) { return _i<Void>(0x849648349D77F5C5, amount, propertyName); }
	static Void network_earn_from_armour_truck(int amount) { return _i<Void>(0xF514621E8EA463D0, amount); }
	static Void network_earn_from_rockstar(int amount) { return _i<Void>(0x02CE1D6AC0FC73EA, amount); }
	static Void _0x9251B6ABF2D0A5B4(Any p0, Any p1) { return _i<Void>(0x9251B6ABF2D0A5B4, p0, p1); }
	static Void _0x6B7E4FB50D5F3D65(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x6B7E4FB50D5F3D65, p0, p1, p2, p3, p4); }
	static Void network_earn_from_vehicle(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return _i<Void>(0xB539BD8A4C1EECF8, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void _0xEDEAD9A91EC768B3(Any p0, Any p1, Any p2) { return _i<Void>(0xEDEAD9A91EC768B3, p0, p1, p2); }
	static Any _0x3E4ADAFF1830F146() { return _i<Any>(0x3E4ADAFF1830F146); }
	static Void _0xCDA1C62BE2777802(Any p0, Any p1, Any p2) { return _i<Void>(0xCDA1C62BE2777802, p0, p1, p2); }
	static Void _0x55A1E095DB052FA5(Any p0, Any p1) { return _i<Void>(0x55A1E095DB052FA5, p0, p1); }
	static Void _0xDEE612F2D71B0308(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xDEE612F2D71B0308, p0, p1, p2, p3); }
	static Void _0x35F8DA0E8A31EF1B(Any p0) { return _i<Void>(0x35F8DA0E8A31EF1B, p0); }
	static Void _0x005ACA7100BD101D(Any p0) { return _i<Void>(0x005ACA7100BD101D, p0); }
	static bool _0x7C4FCCD2E4DEB394() { return _i<bool>(0x7C4FCCD2E4DEB394); }
	static Any _0xA31FD6A0865B6D14() { return _i<Any>(0xA31FD6A0865B6D14); }
	static bool _0xDC18531D7019A535(Any p0, Any p1) { return _i<bool>(0xDC18531D7019A535, p0, p1); }
	static Any _0xED5AB8860415BABA() { return _i<Any>(0xED5AB8860415BABA); }
	static Any _0x08E8EEADFD0DC4A0() { return _i<Any>(0x08E8EEADFD0DC4A0); }
	static Any _0x5D1E75F91C07DEE5() { return _i<Any>(0x5D1E75F91C07DEE5); }
	static Any _0xFB2456B2040A6A67() { return _i<Any>(0xFB2456B2040A6A67); }
	static Any _0x4F54F3B6C202FB4E() { return _i<Any>(0x4F54F3B6C202FB4E); }
	static Any _0x13A8DE2FD77D04F3() { return _i<Any>(0x13A8DE2FD77D04F3); }
	static Any _0xEA560AC9EEB1E19B() { return _i<Any>(0xEA560AC9EEB1E19B); }
	static const char* network_get_bank_balance_string() { return _i<const char*>(0xA6FA3979BED01B81); }
	static Any _0x700AF71AE615E6DD() { return _i<Any>(0x700AF71AE615E6DD); }
	static Any _0xF9B10B529DCFB33B() { return _i<Any>(0xF9B10B529DCFB33B); }
	static int64_t network_get_vc_balance() { return _i<int>(0x5CBAD97E059E1B94); }
	static int64_t network_get_vc_bank_balance() { return _i<int>(0x76EF28DA05EA395A); }
	static int64_t network_get_vc_wallet_balance(int character) { return _i<int>(0xA40F9C2623F6A8B5, character); }
	static Void network_give_player_jobshare_cash(int amount, int* network_handle) { return _i<Void>(0xFB18DF9CB95E0105, amount, network_handle); }
	static Void network_initialize_cash(int p0, int p1) { return _i<Void>(0x3DA5ECD1A56CBA6D, p0, p1); }
	static Void _0x821418C727FCACD7(Any p0) { return _i<Void>(0x821418C727FCACD7, p0); }
	static bool network_money_can_bet(Any p0, bool p1, bool p2) { return _i<bool>(0x81404F3DC124FE5B, p0, p1, p2); }
	static Void network_pay_employee_wage(Any p0, bool p1, bool p2) { return _i<Void>(0x5FD5ED82CBBE9989, p0, p1, p2); }
	static Void network_pay_match_entry_fee(int value, int* p1, bool p2, bool p3) { return _i<Void>(0x9346E14F2AF74D46, value, p1, p2, p3); }
	static Void network_pay_utility_bill(Any p0, bool p1, bool p2) { return _i<Void>(0xAFE08B35EC0C9EAE, p0, p1, p2); }
	static Void network_receive_player_jobshare_cash(int value, int* network_handle) { return _i<Void>(0x56A3B51944C50598, value, network_handle); }
	static Void network_refund_cash(int index, const char* context, const char* reason, bool unk) { return _i<Void>(0xF9C812CD7C46E817, index, context, reason, unk); }
	static Void _0x08A1B82B91900682(Any p0, Any p1, Any p2) { return _i<Void>(0x08A1B82B91900682, p0, p1, p2); }
	static Void _0xDBC966A01C02BCA7(Any p0, Any p1, Any p2) { return _i<Void>(0xDBC966A01C02BCA7, p0, p1, p2); }
	static Void network_spent_ammo_drop(Any p0, bool p1, bool p2) { return _i<Void>(0xB162DC95C0A3317B, p0, p1, p2); }
	static Void network_spent_arrest_bail(Any p0, bool p1, bool p2) { return _i<Void>(0x812F5488B1B2A299, p0, p1, p2); }
	static Void _0x5D97630A8A0EF123(Any p0, Any p1, Any p2) { return _i<Void>(0x5D97630A8A0EF123, p0, p1, p2); }
	static Any network_spent_bank_interest() { return _i<Any>(0xCA230C9682556CF1); }
	static Void network_spent_betting(Any p0, Any p1, Any* p2, bool p3, bool p4) { return _i<Void>(0x1C436FD11FFA692F, p0, p1, p2, p3, p4); }
	static Void network_spent_boat_pickup(Any p0, bool p1, bool p2) { return _i<Void>(0x524EE43A37232C00, p0, p1, p2); }
	static Any _0xFFBE02CD385356BD() { return _i<Any>(0xFFBE02CD385356BD); }
	static Void network_spent_bounty(Any p0, bool p1, bool p2) { return _i<Void>(0x29B260B84947DFCC, p0, p1, p2); }
	static Void network_spent_bull_shark(Any p0, bool p1, bool p2) { return _i<Void>(0xA6DD8458CE24012C, p0, p1, p2); }
	static Void _0x12D148D26538D0F9(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x12D148D26538D0F9, p0, p1, p2, p3); }
	static Void network_spent_buy_offtheradar(Any p0, bool p1, bool p2) { return _i<Void>(0xA628A745E2275C5D, p0, p1, p2); }
	static Void network_spent_buy_passive_mode(Any p0, bool p1, bool p2) { return _i<Void>(0x6D3A430D1A809179, p0, p1, p2); }
	static Void network_spent_buy_reveal_players(Any p0, bool p1, bool p2) { return _i<Void>(0x6E176F1B18BC0637, p0, p1, p2); }
	static Void _0xAC272C0AE01B4BD8(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xAC272C0AE01B4BD8, p0, p1, p2, p3); }
	static Void network_spent_buy_wantedlevel(Any p0, Any* p1, bool p2, bool p3) { return _i<Void>(0xE1B13771A843C4F6, p0, p1, p2, p3); }
	static Void network_spent_call_player(Any p0, Any* p1, bool p2, bool p3) { return _i<Void>(0xACDE7185B374177C, p0, p1, p2, p3); }
	static Void network_spent_carwash(Any p0, Any p1, Any p2, bool p3, bool p4) { return _i<Void>(0xEC03C719DB2F4306, p0, p1, p2, p3, p4); }
	static Void network_spent_cash_drop(int amount, bool p1, bool p2) { return _i<Void>(0x289016EC778D60E0, amount, p1, p2); }
	static Void _0x5F456788B05FAEAC(Any p0, Any p1, Any p2) { return _i<Void>(0x5F456788B05FAEAC, p0, p1, p2); }
	static Void network_spent_cinema(Any p0, Any p1, bool p2, bool p3) { return _i<Void>(0x6B38ECB05A63A685, p0, p1, p2, p3); }
	static Void _0x5182A339A3474510(Any p0, Any p1, Any p2) { return _i<Void>(0x5182A339A3474510, p0, p1, p2); }
	static Void network_spent_from_rockstar(int bank, bool p1, bool p2) { return _i<Void>(0x6A445B64ED7ABEB5, bank, p1, p2); }
	static Any _0xB1F1346FD57685D7() { return _i<Any>(0xB1F1346FD57685D7); }
	static Any _0xB18AC2ECBB15CB6A() { return _i<Any>(0xB18AC2ECBB15CB6A); }
	static Void network_spent_heli_pickup(Any p0, bool p1, bool p2) { return _i<Void>(0x7BF1D73DB2ECA492, p0, p1, p2); }
	static Void network_spent_hire_mercenary(Any p0, bool p1, bool p2) { return _i<Void>(0xE7B80E2BF9D80BD6, p0, p1, p2); }
	static Void network_spent_hire_mugger(Any p0, bool p1, bool p2) { return _i<Void>(0xE404BFB981665BF0, p0, p1, p2); }
	static Void network_spent_holdups(Any p0, bool p1, bool p2) { return _i<Void>(0xD9B86B9872039763, p0, p1, p2); }
	static Void _0xC1952F3773BA18FE(Any p0, Any p1, Any p2) { return _i<Void>(0xC1952F3773BA18FE, p0, p1, p2); }
	static Void network_spent_in_stripclub(Any p0, bool p1, Any p2, bool p3) { return _i<Void>(0xEE99784E4467689C, p0, p1, p2, p3); }
	static Any _0x28F174A67B8D0C2F() { return _i<Any>(0x28F174A67B8D0C2F); }
	static Void _0x5BCDE0F640C773D2(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x5BCDE0F640C773D2, p0, p1, p2, p3); }
	static Void _0xD7CCCBA28C4ECAF0(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xD7CCCBA28C4ECAF0, p0, p1, p2, p3, p4); }
	static Void _0xE7DF4E0545DFB56E(Any p0, Any p1, Any p2) { return _i<Void>(0xE7DF4E0545DFB56E, p0, p1, p2); }
	static Void network_spent_no_cops(Any p0, bool p1, bool p2) { return _i<Void>(0xD5BB406F4E04019F, p0, p1, p2); }
	static Void _0xE8B0B270B6E7C76E(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xE8B0B270B6E7C76E, p0, p1, p2, p3); }
	static Void _0x05F04155A226FBBF(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x05F04155A226FBBF, p0, p1, p2, p3); }
	static Void _0x0035BB914316F1E3(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0035BB914316F1E3, p0, p1, p2, p3); }
	static Void network_spent_pay_vehicle_insurance_premium(int amount, uint32_t vehicleModel, int* network_handle, bool notBankrupt, bool hasTheMoney) { return _i<Void>(0x9FF28D88C766E3E8, amount, vehicleModel, network_handle, notBankrupt, hasTheMoney); }
	static Void _0x0FE8E1FCD2B86B33(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0FE8E1FCD2B86B33, p0, p1, p2, p3); }
	static Void _0xB49ECA122467D05F(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xB49ECA122467D05F, p0, p1, p2, p3); }
	static Void _0x112209CE0290C03A(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x112209CE0290C03A, p0, p1, p2, p3); }
	static Void _0xE23ADC6FCB1F29AE(Any p0, Any p1, Any p2) { return _i<Void>(0xE23ADC6FCB1F29AE, p0, p1, p2); }
	static Void _0x0D30EB83668E63C5(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0D30EB83668E63C5, p0, p1, p2, p3); }
	static Void _0xED5FD7AF10F5E262(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xED5FD7AF10F5E262, p0, p1, p2, p3); }
	static Void network_spent_player_healthcare(Any p0, Any p1, bool p2, bool p3) { return _i<Void>(0x7C99101F7FCE2EE5, p0, p1, p2, p3); }
	static Void network_spent_prostitutes(Any p0, bool p1, bool p2) { return _i<Void>(0xB21B89501CFAC79E, p0, p1, p2); }
	static Void _0x6FD97159FE3C971A(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x6FD97159FE3C971A, p0, p1, p2, p3); }
	static Void _0x998E18CEB44487FC(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x998E18CEB44487FC, p0, p1, p2, p3); }
	static Void _0xCCB339CC970452DA(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xCCB339CC970452DA, p0, p1, p2, p3); }
	static Void _0x33981D6804E62F49(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x33981D6804E62F49, p0, p1, p2, p3); }
	static Void _0xB4C2EC463672474E(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xB4C2EC463672474E, p0, p1, p2, p3); }
	static Void _0x69EF772B192614C1(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x69EF772B192614C1, p0, p1, p2, p3); }
	static Void _0xBD0EFB25CCA8F97A(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xBD0EFB25CCA8F97A, p0, p1, p2, p3); }
	static Void _0xFC4EE00A7B3BFB76(Any p0, Any p1, Any p2) { return _i<Void>(0xFC4EE00A7B3BFB76, p0, p1, p2); }
	static Void network_spent_request_heist(Any p0, bool p1, bool p2) { return _i<Void>(0x9D26502BB97BFE62, p0, p1, p2); }
	static Void network_spent_request_job(Any p0, bool p1, bool p2) { return _i<Void>(0x8204DA7934DF3155, p0, p1, p2); }
	static Void network_spent_robbed_by_mugger(int amount, bool p1, bool p2) { return _i<Void>(0x995A65F15F581359, amount, p1, p2); }
	static Void network_spent_taxi(int amount, bool p1, bool p2) { return _i<Void>(0x17C3A7D31EAE39F9, amount, p1, p2); }
	static Void network_spent_telescope(Any p0, bool p1, bool p2) { return _i<Void>(0x7FE61782AD94CC09, p0, p1, p2); }
	static Void _0xA51B086B0B2C0F7A(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xA51B086B0B2C0F7A, p0, p1, p2, p3); }
	static Void _0x2FAB6614CE22E196(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x2FAB6614CE22E196, p0, p1, p2, p3); }
	static Void _0x675D19C6067CAE08(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x675D19C6067CAE08, p0, p1, p2, p3); }
	static Void _0xFA07759E6FDDD7CF(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xFA07759E6FDDD7CF, p0, p1, p2, p3); }
	static Void _0x615EB504B0788DAF(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x615EB504B0788DAF, p0, p1, p2, p3); }
	static Void _0x4128464231E3CA0B(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x4128464231E3CA0B, p0, p1, p2, p3); }
	static Void _0x2AFC2D19B50797F2(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x2AFC2D19B50797F2, p0, p1, p2, p3); }
	static Void _0x8E243837643D9583(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x8E243837643D9583, p0, p1, p2, p3); }
	static Void _0x365E877C61D6988B(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x365E877C61D6988B, p0, p1, p2, p3); }
	static Void _0xA95F667A755725DA(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xA95F667A755725DA, p0, p1, p2, p3); }
	static Void _0x0C82D21A77C22D49(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0C82D21A77C22D49, p0, p1, p2, p3); }
	static Void _0xA75CCF58A60A5FD1(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Void>(0xA75CCF58A60A5FD1, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void _0xD99DB210089617FE(Any p0, Any p1, Any p2) { return _i<Void>(0xD99DB210089617FE, p0, p1, p2); }
	static const char* process_cash_gift(int* p0, int* p1, const char* p2) { return _i<const char*>(0x20194D48EAEC9A41, p0, p1, p2); }
	static Any _0xF70EFA14FE091429(Any p0) { return _i<Any>(0xF70EFA14FE091429, p0); }
	static Any _0x9B5016A6433A68C5() { return _i<Any>(0x9B5016A6433A68C5); }
	static Any _0xCD0F5B5D932AE473() { return _i<Any>(0xCD0F5B5D932AE473); }

	static bool can_phone_be_seen_on_screen() { return _i<bool>(0xC4E2813898C97A4B); }
	static Void cell_cam_activate(bool p0, bool p1) { return _i<Void>(0xFDE8F069C542D126, p0, p1); }
	static Void disable_phone_this_frame(bool toggle) { return _i<Void>(0x015C49A93E3E086E, toggle); }
	static Void _0xA2CCBE62CD4C91A4(int* toggle) { return _i<Void>(0xA2CCBE62CD4C91A4, toggle); }
	static bool cell_cam_is_char_visible_no_face_check(Entity entity) { return _i<bool>(0x439E9BC95B7E7FBE, entity); }
	static Void _0xAC2890471901861C(float p0) { return _i<Void>(0xAC2890471901861C, p0); }
	static Void _0x466DA42C89865553(float p0) { return _i<Void>(0x466DA42C89865553, p0); }
	static Void _0xF1E22DC13F5EEBAD(float p0) { return _i<Void>(0xF1E22DC13F5EEBAD, p0); }
	static Void _0xD6ADE981781FCA09(float p0) { return _i<Void>(0xD6ADE981781FCA09, p0); }
	static Void _0x53F4892D18EC90A4(float p0) { return _i<Void>(0x53F4892D18EC90A4, p0); }
	static Void _0x15E69E2802C24B8D(float p0) { return _i<Void>(0x15E69E2802C24B8D, p0); }
	static Void _0x1B0B4AEED5B9B41C(float p0) { return _i<Void>(0x1B0B4AEED5B9B41C, p0); }
	static Void _0x3117D84EFA60F77B(float p0) { return _i<Void>(0x3117D84EFA60F77B, p0); }
	static Void set_phone_lean(bool Toggle) { return _i<Void>(0x44E44169EF70138E, Toggle); }
	static Void move_finger(int direction) { return _i<Void>(0x95C9E72F3D7DEC9B, direction); }
	static Void create_mobile_phone(int phoneType) { return _i<Void>(0xA4E8E696C532FBC7, phoneType); }
	static Void destroy_mobile_phone() { return _i<Void>(0x3BC861DF703E5097); }
	static Void get_mobile_phone_position(math::vector3<float>* position) { return _i<Void>(0x584FDFDA48805B86, position); }
	static Void get_mobile_phone_render_id(int* renderId) { return _i<Void>(0xB4A53E05F68B6FA1, renderId); }
	static Void get_mobile_phone_rotation(math::vector3<float>* rotation, Any p1) { return _i<Void>(0x1CEFB61F193070AE, rotation, p1); }
	static Void script_is_moving_mobile_phone_offscreen(bool toggle) { return _i<Void>(0xF511F759238A5122, toggle); }
	static Void _0x375A706A5C2FD084(Any p0) { return _i<Void>(0x375A706A5C2FD084, p0); }
	static Void set_mobile_phone_position(float posX, float posY, float posZ) { return _i<Void>(0x693A5C6D6734085B, posX, posY, posZ); }
	static Void set_mobile_phone_rotation(float rotX, float rotY, float rotZ, Any p3) { return _i<Void>(0xBB779C0CA917E865, rotX, rotY, rotZ, p3); }
	static Void set_mobile_phone_scale(float scale) { return _i<Void>(0xCBDD322A73D6D932, scale); }

	static Any network_shop_basket_add_item(Any* p0, Any p1) { return _i<Any>(0xF30980718C8ED876, p0, p1); }
	static bool network_shop_basket_apply_server_data(Any p0, Any* p1) { return _i<bool>(0xE1A0450ED46A7812, p0, p1); }
	static Any network_shop_basket_end() { return _i<Any>(0xA65568121DF2EA26); }
	static Any _0xE547E9114277098F() { return _i<Any>(0xE547E9114277098F); }
	static Any network_shop_basket_is_full() { return _i<Any>(0x27F76CC6C55AD30E); }
	static bool network_shop_basket_start(Any* p0, Any p1, Any p2, Any p3) { return _i<bool>(0x279F08B1A4B29B7E, p0, p1, p2, p3); }
	static bool network_shop_begin_service(int* value, Any p1, Any p2, Any p3, Any p4, int p5) { return _i<bool>(0x3C5FD37B5499582E, value, p1, p2, p3, p4, p5); }
	static Any _0x3C4487461E9B0DCB() { return _i<Any>(0x3C4487461E9B0DCB); }
	static bool network_shop_does_item_exist(const char* name) { return _i<bool>(0xBD4D7EAF8A30F637, name); }
	static bool network_shop_does_item_exist_hash(uint32_t hash) { return _i<bool>(0x247F0F73A182EA0B, hash); }
	static bool network_shop_checkout_start(Any p0) { return _i<bool>(0x39BE7CEA8D9CC8E6, p0); }
	static bool _0x74A0FD0688F1EE45(Any p0) { return _i<bool>(0x74A0FD0688F1EE45, p0); }
	static bool _0x51F1A8E48C3D2F6D(Any p0, bool p1, Any p2) { return _i<bool>(0x51F1A8E48C3D2F6D, p0, p1, p2); }
	static Any _0x0A6D923DFFC9BD89() { return _i<Any>(0x0A6D923DFFC9BD89); }
	static Any network_shop_delete_set_telemetry_nonce_seed() { return _i<Any>(0x112CEF1615A1139F); }
	static bool network_shop_end_service(Any p0) { return _i<bool>(0xE2A99A9B524BEFFF, p0); }
	static Any _0x85F6C9ABA1DE2BCF() { return _i<Any>(0x85F6C9ABA1DE2BCF); }
	static int network_shop_get_price(int hash, int hash2, bool p2) { return _i<int>(0xC27009422FCCA88D, hash, hash2, p2); }
	static bool _0x897433D292B44130(Any* p0, Any* p1) { return _i<bool>(0x897433D292B44130, p0, p1); }
	static Any _0xE3E5A7C64CA2C6ED() { return _i<Any>(0xE3E5A7C64CA2C6ED); }
	static Any _0x2B949A1E6AEC8F6A() { return _i<Any>(0x2B949A1E6AEC8F6A); }
	static bool network_shop_get_transactions_disabled() { return _i<bool>(0x810E8431C0614BF9); }
	static bool network_shop_get_transactions_enabled_for_character(int mpChar) { return _i<bool>(0xB24F0944DA203D9E, mpChar); }
	static Any _0x357B152EF96C30B6() { return _i<Any>(0x357B152EF96C30B6); }
	static bool _0xCF38DAFBB49EDE5E(Any* p0) { return _i<bool>(0xCF38DAFBB49EDE5E, p0); }
	static bool _0x0395CB47B022E62C(Any* p0) { return _i<bool>(0x0395CB47B022E62C, p0); }
	static bool _0xC13C38E47EA5DF31(Any* p0) { return _i<bool>(0xC13C38E47EA5DF31, p0); }
	static bool _0x170910093218C8B9(Any* p0) { return _i<bool>(0x170910093218C8B9, p0); }
	static bool network_shop_session_apply_received_data(Any p0) { return _i<bool>(0x2F41D51BA3BCD1F1, p0); }
	static bool network_shop_set_telemetry_nonce_seed(Any p0) { return _i<bool>(0x9507D4271988E1AE, p0); }
	static bool network_shop_start_session(Any p0) { return _i<bool>(0xA135AC892A58FC07, p0); }
	static Any _0x72EB7BA9B69BF6AB() { return _i<Any>(0x72EB7BA9B69BF6AB); }
	static bool _0x35A1B3E1D1315CFA(bool p0, bool p1) { return _i<bool>(0x35A1B3E1D1315CFA, p0, p1); }
	static Any _0x613F125BA3BD2EB9() { return _i<Any>(0x613F125BA3BD2EB9); }
	static bool network_transfer_bank_to_wallet(int charStatInt, int amount) { return _i<bool>(0xD47A2C1BA117471D, charStatInt, amount); }
	static Any _0x23789E777D14CE44() { return _i<Any>(0x23789E777D14CE44); }
	static Any _0x350AA5EBC03D3BD2() { return _i<Any>(0x350AA5EBC03D3BD2); }
	static Any network_shop_cash_transfer_set_telemetry_nonce_seed() { return _i<Any>(0x498C1E05CE5F7877); }
	static bool network_transfer_wallet_to_bank(int charStatInt, int amount) { return _i<bool>(0xC2F7FE5309181C7D, charStatInt, amount); }

	static Void _0x1F7BC3539F9E0224() { return _i<Void>(0x1F7BC3539F9E0224); }
	static bool _0xBD545D44CCE70597() { return _i<bool>(0xBD545D44CCE70597); }
	static Any _0xEBCAB9E5048434F4() { return _i<Any>(0xEBCAB9E5048434F4); }
	static Any _0x7808619F31FF22DB() { return _i<Any>(0x7808619F31FF22DB); }
	static Void activate_damage_tracker_on_network_id(int netID, bool p1) { return _i<Void>(0xD45B1FFCCD52FF19, netID, p1); }
	static Void _0xBEC0816FF5ACBCDA(Any p0, Any p1) { return _i<Void>(0xBEC0816FF5ACBCDA, p0, p1); }
	static bool bad_sport_player_left_detected(int* network_handle, int event, int amountReceived) { return _i<bool>(0xEC5E3AF5289DCA81, network_handle, event, amountReceived); }
	static Any _0xE16AA70CE9BEEDC3(Any p0) { return _i<Any>(0xE16AA70CE9BEEDC3, p0); }
	static bool can_register_mission_entities(int p0, Any p1, Any p2, Any p3) { return _i<bool>(0x69778E7564BADE6D, p0, p1, p2, p3); }
	static bool can_register_mission_objects(int p0) { return _i<bool>(0x800DD4721A8B008B, p0); }
	static bool can_register_mission_peds(int p0) { return _i<bool>(0xBCBF4FEF9FA5D781, p0); }
	static bool can_register_mission_pickups(int p0) { return _i<bool>(0x0A49D1CB6E34AF72, p0); }
	static bool can_register_mission_vehicles(int p0) { return _i<bool>(0x7277F1F2E085EE74, p0); }
	static Void download_check() { return _i<Void>(0x4F18196C8D38768D); }
	static Any _0xC64DED7EF0D2FE37(Any* p0) { return _i<Any>(0xC64DED7EF0D2FE37, p0); }
	static bool _0x3A3D5568AF297CD5(Any p0) { return _i<bool>(0x3A3D5568AF297CD5, p0); }
	static Any network_enable_motion_drugged() { return _i<Any>(0x0B0CC10720653F3B); }
	static bool _0x4C61B39930D045DA(Any p0) { return _i<bool>(0x4C61B39930D045DA, p0); }
	static Any _0xC7ABAC5DE675EE3B() { return _i<Any>(0xC7ABAC5DE675EE3B); }
	static Void get_date_and_time_from_unix_epoch(int unixEpoch, Any* timeStructure) { return _i<Void>(0xAC97AF97FA68E5D5, unixEpoch, timeStructure); }
	static Void _0x265635150FB0D82E() { return _i<Void>(0x265635150FB0D82E); }
	static Any _0x43865688AE10F0D7() { return _i<Any>(0x43865688AE10F0D7); }
	static Any _0xA75E2B6733DA5142() { return _i<Any>(0xA75E2B6733DA5142); }
	static Any _0x62B9FEC9A11F10EF() { return _i<Any>(0x62B9FEC9A11F10EF); }
	static bool _0x098AB65B9ED9A9EC(Any* p0, Any p1, Any p2) { return _i<bool>(0x098AB65B9ED9A9EC, p0, p1, p2); }
	static bool _0x0AE1F1653B554AB9(Any p0) { return _i<bool>(0x0AE1F1653B554AB9, p0); }
	static Any _0xDC48473142545431() { return _i<Any>(0xDC48473142545431); }
	static Void fade_out_local_player(bool p0) { return _i<Void>(0x416DBD4CD6ED8DD2, p0); }
	static bool fillout_pm_player_list(int* network_handle, Any p1, Any p2) { return _i<bool>(0xCBBD7C4991B64809, network_handle, p1, p2); }
	static bool fillout_pm_player_list_with_names(Any* p0, Any* p1, Any p2, Any p3) { return _i<bool>(0x716B6DB9D1886106, p0, p1, p2, p3); }
	static int get_posix_time() { return _i<int>(0x9A73240B49945C76); }
	static Any _0xF12E6CD06C73D69E() { return _i<Any>(0xF12E6CD06C73D69E); }
	static Any _0x6F44CBF56D79FAC0(Any p0, Any p1) { return _i<Any>(0x6F44CBF56D79FAC0, p0, p1); }
	static Any _0x662635855957C411(Any p0) { return _i<Any>(0x662635855957C411, p0); }
	static Any _0xB4271092CA7EDF48(Any p0) { return _i<Any>(0xB4271092CA7EDF48, p0); }
	static Any _0x2A7776C709904AB0(Any p0) { return _i<Any>(0x2A7776C709904AB0, p0); }
	static Any _0x722F5D28B61C5EA8(Any p0) { return _i<Any>(0x722F5D28B61C5EA8, p0); }
	static Any _0xCA94551B50B4932C(Any p0) { return _i<Any>(0xCA94551B50B4932C, p0); }
	static Any _0x74FB3E29E6D10FA9() { return _i<Any>(0x74FB3E29E6D10FA9); }
	static Any _0xA0FA4EC6A05DA44E() { return _i<Any>(0xA0FA4EC6A05DA44E); }
	static Any _0x58CC181719256197(Any p0, Any p1, Any p2) { return _i<Any>(0x58CC181719256197, p0, p1, p2); }
	static Any network_is_pending_friend(Any p0) { return _i<Any>(0x0BE73DA6984A6E33, p0); }
	static Any _0x8B0C2964BA471961() { return _i<Any>(0x8B0C2964BA471961); }
	static Any _0x88B588B41FF7868E() { return _i<Any>(0x88B588B41FF7868E); }
	static Any _0x67FC09BC554A75E5() { return _i<Any>(0x67FC09BC554A75E5); }
	static Any _0x6FB7BB3607D27FA2() { return _i<Any>(0x6FB7BB3607D27FA2); }
	static Any _0xC7BE335216B5EC7C() { return _i<Any>(0xC7BE335216B5EC7C); }
	static Any _0x0C1F7D49C39D2289() { return _i<Any>(0x0C1F7D49C39D2289); }
	static Any _0xA72835064DD63E4C() { return _i<Any>(0xA72835064DD63E4C); }
	static Any _0x0AFCE529F69B21FF() { return _i<Any>(0x0AFCE529F69B21FF); }
	static int get_network_time() { return _i<int>(0x7A5487FE9FAA6B48); }
	static int _0x89023FBBF9200E9F() { return _i<int>(0x89023FBBF9200E9F); }
	static Any _0xF2EAC213D5EA0623() { return _i<Any>(0xF2EAC213D5EA0623); }
	static int _0x12B6281B6C6706C0(bool p0) { return _i<int>(0x12B6281B6C6706C0, p0); }
	static int _0xCB215C4B56A7FAE7(bool p0) { return _i<int>(0xCB215C4B56A7FAE7, p0); }
	static int _0x0CD9AB83489430EA(bool p0) { return _i<int>(0x0CD9AB83489430EA, p0); }
	static int get_num_reserved_mission_objects(bool p0, Any p1) { return _i<int>(0xAA81B5F10BC43AC2, p0, p1); }
	static int get_num_reserved_mission_peds(bool p0, Any p1) { return _i<int>(0x1F13D5AE5CB17E17, p0, p1); }
	static int get_num_reserved_mission_vehicles(bool p0, Any p1) { return _i<int>(0xCF3A965906452031, p0, p1); }
	static const char* get_online_version() { return _i<const char*>(0xFCA9373EF340AC0A); }
	static Any _0x8BD6C6DEA20E82C6(Any p0) { return _i<Any>(0x8BD6C6DEA20E82C6, p0); }
	static const char* get_time_as_string(int time) { return _i<const char*>(0x9E23B1777A927DAD, time); }
	static int get_time_difference(int timeA, int timeB) { return _i<int>(0xA2C6FC031D46FFF0, timeA, timeB); }
	static int get_time_offset(int timeA, int timeB) { return _i<int>(0x017008CCDAD48503, timeA, timeB); }
	static bool has_network_time_started() { return _i<bool>(0x46718ACEEDEAFC84); }
	static Any _0x1D4DC17C38FEAFF0() { return _i<Any>(0x1D4DC17C38FEAFF0); }
	static Any _0xEA14EEF5B7CD2C30() { return _i<Any>(0xEA14EEF5B7CD2C30); }
	static Any _0x2EAC52B4019E2782() { return _i<Any>(0x2EAC52B4019E2782); }
	static bool is_damage_tracker_active_on_network_id(int netID) { return _i<bool>(0x6E192E33AD436366, netID); }
	static Any _0xB2092A1EAA7FD45F(Any p0) { return _i<Any>(0xB2092A1EAA7FD45F, p0); }
	static bool _0x21D04D7BC538C146(Any p0) { return _i<bool>(0x21D04D7BC538C146, p0); }
	static Any _0x7EF7649B64D7FF10(Any p0) { return _i<Any>(0x7EF7649B64D7FF10, p0); }
	static bool _0xA1607996431332DF(int netId) { return _i<bool>(0xA1607996431332DF, netId); }
	static bool is_player_in_cutscene(Player player) { return _i<bool>(0xE73092F4157CD126, player); }
	static bool network_is_signed_online() { return _i<bool>(0x1077788E268557C2); }
	static bool is_sphere_visible_to_another_machine(float p0, float p1, float p2, float p3) { return _i<bool>(0xD82CF8E64C8729D8, p0, p1, p2, p3); }
	static bool is_sphere_visible_to_player(Any p0, float p1, float p2, float p3, float p4) { return _i<bool>(0xDC3A310219E5DA62, p0, p1, p2, p3, p4); }
	static Any _0x883D79C4071E18B3() { return _i<Any>(0x883D79C4071E18B3); }
	static bool is_time_equal_to(int timeA, int timeB) { return _i<bool>(0xF5BC95857BD6D512, timeA, timeB); }
	static bool is_time_less_than(int timeA, int timeB) { return _i<bool>(0xCB2CF5148012C8D0, timeA, timeB); }
	static bool is_time_more_than(int timeA, int timeB) { return _i<bool>(0xDE350F8651E4346C, timeA, timeB); }
	static Any _0x59328EB08C5CEB2B() { return _i<Any>(0x59328EB08C5CEB2B); }
	static bool network_accept_presence_invite(Any p0) { return _i<bool>(0xFA91550DF9318B22, p0); }
	static bool network_access_tunable_bool(const char* tunableContext, const char* tunableName) { return _i<bool>(0xAA6A47A573ABB75A, tunableContext, tunableName); }
	static bool network_access_tunable_bool_hash(uint32_t tunableContext, uint32_t tunableName) { return _i<bool>(0xEA16B69D93D71A45, tunableContext, tunableName); }
	static bool network_access_tunable_float(const char* tunableContext, const char* tunableName, float* value) { return _i<bool>(0xE5608CA7BC163A5F, tunableContext, tunableName, value); }
	static bool network_access_tunable_float_hash(uint32_t tunableContext, uint32_t tunableName, float* value) { return _i<bool>(0x972BC203BBC4C4D5, tunableContext, tunableName, value); }
	static Any _0x3A8B55FDA4C8DDEF(Any p0, Any p1, Any p2) { return _i<Any>(0x3A8B55FDA4C8DDEF, p0, p1, p2); }
	static Any _0x1950DAE9848A4739(Any p0, Any p1, Any p2) { return _i<Any>(0x1950DAE9848A4739, p0, p1, p2); }
	static Any _0x697F508861875B42(Any p0, Any p1, Any p2) { return _i<Any>(0x697F508861875B42, p0, p1, p2); }
	static bool network_access_tunable_int(const char* tunableContext, const char* tunableName, int* value) { return _i<bool>(0x8BE1146DFD5D4468, tunableContext, tunableName, value); }
	static bool network_access_tunable_int_hash(uint32_t tunableContext, uint32_t tunableName, int* value) { return _i<bool>(0x40FCE03E50E8DBE8, tunableContext, tunableName, value); }
	static Any _0xFAFC23AEE23868DB() { return _i<Any>(0xFAFC23AEE23868DB); }
	static Any network_action_follow_invite() { return _i<Any>(0xC88156EBB786F8D5); }
	static Any _0x2B1C623823DB0D9D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Any>(0x2B1C623823DB0D9D, p0, p1, p2, p3, p4, p5, p6); }
	static Any _0x25B99872D588A101(float p0, float p1, float p2, float p3, float p4, float p5) { return _i<Any>(0x25B99872D588A101, p0, p1, p2, p3, p4, p5); }
	static Any network_add_entity_angled_area(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return _i<Any>(0x376C6375BA60293A, p0, p1, p2, p3, p4, p5, p6); }
	static Any network_add_entity_area(float p0, float p1, float p2, float p3, float p4, float p5) { return _i<Any>(0x494C8FB299290269, p0, p1, p2, p3, p4, p5); }
	static Void network_add_entity_to_synchronised_scene(Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag) { return _i<Void>(0xF2404D68CBC855FA, entity, netScene, animDict, animName, speed, speedMulitiplier, flag); }
	static Void network_add_followers(int* p0, int p1) { return _i<Void>(0x236406F60CF216D6, p0, p1); }
	static bool network_add_friend(Any* p0, const char* p1) { return _i<bool>(0x8E02D73914064223, p0, p1); }
	static Void network_add_ped_to_synchronised_scene(Ped ped, int netScene, char* animDict, char* animName, float blendInSpeed, float blendOutSpeed, int duration, int flag, float playbackRate, Any p9) { return _i<Void>(0x742A637471BCECD9, ped, netScene, animDict, animName, blendInSpeed, blendOutSpeed, duration, flag, playbackRate, p9); }
	static Void network_force_local_use_of_synced_scene_camera(int netScene, const char* animDict, const char* animName) { return _i<Void>(0xCF8BD3B0BD6D42D7, netScene, animDict, animName); }
	static Void _0xFB680D403909DC70(Any p0, Any p1) { return _i<Void>(0xFB680D403909DC70, p0, p1); }
	static Void network_block_kicked_players(bool p0) { return _i<Void>(0x6B07B9CE4D390375, p0); }
	static Void _0x267C78C60E806B9A(Any p0, bool p1) { return _i<Void>(0x267C78C60E806B9A, p0, p1); }
	static Void _0x144DA052257AE7D8(Any p0) { return _i<Void>(0x144DA052257AE7D8, p0); }
	static bool network_am_i_blocked_by_gamer(Any* p0) { return _i<bool>(0x15337C7C268A27B2, p0); }
	static bool network_am_i_blocked_by_player(Player player) { return _i<bool>(0x87F395D957D4353D, player); }
	static bool network_am_i_muted_by_gamer(Any* p0) { return _i<bool>(0xDF02A2C93F1F26DA, p0); }
	static bool network_am_i_muted_by_player(Player player) { return _i<bool>(0x9D6981DFC91A8604, player); }
	static bool _0x99B72C7ABDE5C910(Ped ped, Player player) { return _i<bool>(0x99B72C7ABDE5C910, ped, player); }
	static Void _0xE66C690248F11150(Entity p0, Any p1) { return _i<Void>(0xE66C690248F11150, p0, p1); }
	static Void network_apply_transition_parameter(Any p0, Any p1) { return _i<Void>(0x521638ADA1BA0D18, p0, p1); }
	static Void _0xEBEFC2E77084F599(Any p0, const char* p1, bool p2) { return _i<Void>(0xEBEFC2E77084F599, p0, p1, p2); }
	static Void _0xDBD2056652689917(float x, float y, float z) { return _i<Void>(0xDBD2056652689917, x, y, z); }
	static bool network_are_handles_the_same(int* netHandle1, int* netHandle2) { return _i<bool>(0x57DBA049E110F217, netHandle1, netHandle2); }
	static bool network_is_player_equal_to_index(Player player, int index) { return _i<bool>(0x9DE986FC9A87C474, player, index); }
	static Any _0xBA9775570DB788CF() { return _i<Any>(0xBA9775570DB788CF); }
	static bool network_are_transition_details_valid(Any p0) { return _i<bool>(0x2615AA2A695930C1, p0); }
	static Void network_attach_synchronised_scene_to_entity(int netScene, Entity entity, int bone) { return _i<Void>(0x478DCBD2A98B705A, netScene, entity, bone); }
	static Void network_bail(Any p0, Any p1, Any p2) { return _i<Void>(0x95914459A87EBA28, p0, p1, p2); }
	static Void network_bail_transition(Any p0, Any p1, Any p2) { return _i<Void>(0xEAA572036990CD1B, p0, p1, p2); }
	static Void network_block_invites(bool toggle) { return _i<Void>(0x34F9E9049454A7A0, toggle); }
	static Void _0xCFEB8AF24FC1D0BB(bool p0) { return _i<Void>(0xCFEB8AF24FC1D0BB, p0); }
	static Void _0xBD0BE0BFC927EAC1() { return _i<Void>(0xBD0BE0BFC927EAC1); }
	static Void _0xFB8F2A6F3DF08CBE() { return _i<Void>(0xFB8F2A6F3DF08CBE); }
	static bool network_can_access_multiplayer(int* loadingState) { return _i<bool>(0xAF50DA1A3F8B1BA4, loadingState); }
	static bool network_can_bail() { return _i<bool>(0x580CE4438479CC61); }
	static Any _0x8F5D1AD832AEB06C(Any p0) { return _i<Any>(0x8F5D1AD832AEB06C, p0); }
	static bool network_can_enter_multiplayer() { return _i<bool>(0x7E782A910C362C25); }
	static bool _0x135F9B7B7ADD2185(Any* p0) { return _i<bool>(0x135F9B7B7ADD2185, p0); }
	static Any _0x2BF66D2E7414F686() { return _i<Any>(0x2BF66D2E7414F686); }
	static bool network_can_session_end() { return _i<bool>(0x4EEBC3694E49C572); }
	static bool network_can_set_waypoint() { return _i<bool>(0xC927EC229934AF60); }
	static bool network_can_communicate_with_gamer(int* player) { return _i<bool>(0xA150A4F065806B1F, player); }
	static Void network_change_transition_slots(Any p0, Any p1) { return _i<Void>(0xEEEDA5E6D7080987, p0, p1); }
	static bool _0x83F28CE49FBBFFBA(Any p0, Any p1, bool p2) { return _i<bool>(0x83F28CE49FBBFFBA, p0, p1, p2); }
	static Any _0x4AD490AE1536933B(Any p0, Any p1) { return _i<Any>(0x4AD490AE1536933B, p0, p1); }
	static bool _0x44B37CDCAE765AAE(Any p0, Any* p1) { return _i<bool>(0x44B37CDCAE765AAE, p0, p1); }
	static bool _0x78321BEA235FD8CD(Any p0, bool p1) { return _i<bool>(0x78321BEA235FD8CD, p0, p1); }
	static Any _0x0CF6CC51AA18F0F8(Any p0, Any p1, Any p2) { return _i<Any>(0x0CF6CC51AA18F0F8, p0, p1, p2); }
	static Any _0x60EDD13EB3AC1FF3() { return _i<Any>(0x60EDD13EB3AC1FF3); }
	static Any _0x07EAB372C8841D99(Any p0, Any p1, Any p2) { return _i<Any>(0x07EAB372C8841D99, p0, p1, p2); }
	static bool _0x595F028698072DD9(Any p0, Any p1, bool p2) { return _i<bool>(0x595F028698072DD9, p0, p1, p2); }
	static bool network_is_clan_membership_finished_downloading() { return _i<bool>(0xB3F64A6A91432477); }
	static bool _0x2B51EDBEFC301339(int p0, const char* p1) { return _i<bool>(0x2B51EDBEFC301339, p0, p1); }
	static bool network_clan_animation(const char* animDict, const char* animName) { return _i<bool>(0x729E3401F0430686, animDict, animName); }
	static bool network_clan_download_membership(int* network_handle) { return _i<bool>(0xA989044E70010ABE, network_handle); }
	static bool network_clan_download_membership_pending(Any* p0) { return _i<bool>(0x5B9E023DC6EBEDC0, p0); }
	static bool _0x5835D9CD92E83184(Any* p0, Any* p1) { return _i<bool>(0x5835D9CD92E83184, p0, p1); }
	static int get_num_membership_desc() { return _i<int>(0x1F471B79ACC90BEF); }
	static bool network_clan_get_membership(int* p0, int* clanMembership, int p2) { return _i<bool>(0xC8BC2011F67B3411, p0, clanMembership, p2); }
	static int network_clan_get_membership_count(int* p0) { return _i<int>(0xAAB11F6C4ADBC2C1, p0); }
	static bool network_clan_get_membership_desc(int* memberDesc, int p1) { return _i<bool>(0x48DE78AF2C8885B8, memberDesc, p1); }
	static bool network_clan_get_membership_valid(int* p0, Any p1) { return _i<bool>(0x48A59CF88D43DF0E, p0, p1); }
	static Void _0xF45352426FF3A4F0(int* clanDesc, int bufferSize, int* network_handle) { return _i<Void>(0xF45352426FF3A4F0, clanDesc, bufferSize, network_handle); }
	static Any _0xC32EA7A2F6CA7557() { return _i<Any>(0xC32EA7A2F6CA7557); }
	static bool _0xA134777FF7F33331(Any p0, Any* p1) { return _i<bool>(0xA134777FF7F33331, p0, p1); }
	static bool _0x7543BB439F63792B(int* clanDesc, int bufferSize) { return _i<bool>(0x7543BB439F63792B, clanDesc, bufferSize); }
	static bool network_clan_join(int clanDesc) { return _i<bool>(0x9FAAA4F4FC71F87F, clanDesc); }
	static bool network_clan_player_get_desc(int* clanDesc, int bufferSize, int* network_handle) { return _i<bool>(0xEEE6EACBE8874FBA, clanDesc, bufferSize, network_handle); }
	static bool network_clan_player_is_active(int* network_handle) { return _i<bool>(0xB124B57F571D8F18, network_handle); }
	static Void _0x113E6E3E50E286B0(Any p0) { return _i<Void>(0x113E6E3E50E286B0, p0); }
	static bool network_clan_remote_memberships_are_in_cache(int* p0) { return _i<bool>(0xBB6E6FEE99D866B2, p0); }
	static bool _0x13518FF1C6B28938(Any p0) { return _i<bool>(0x13518FF1C6B28938, p0); }
	static bool network_player_is_in_clan() { return _i<bool>(0x579CCED0265D4896); }
	static Void network_clear_clock_time_override() { return _i<Void>(0xD972DF67326F966E); }
	static Void network_clear_followers() { return _i<Void>(0x058F43EC59A8631A); }
	static Any network_clear_follow_invite() { return _i<Any>(0x439BFDE3CD0610F6); }
	static Void network_clear_found_gamers() { return _i<Void>(0x6D14CCEE1B40381A); }
	static Void clear_gamer_task_data() { return _i<Void>(0x86E0660E4F5C956D); }
	static Void _0x1888694923EF4591() { return _i<Void>(0x1888694923EF4591); }
	static Void _0x140E6A44870A11CE() { return _i<Void>(0x140E6A44870A11CE); }
	static Void network_clear_property_id() { return _i<Void>(0xC2B82527CA77053E); }
	static Void _0x6CE50E47F5543D0C() { return _i<Void>(0x6CE50E47F5543D0C); }
	static Void network_clear_transition_creator_handle() { return _i<Void>(0xFB3272229A82C759); }
	static Void network_clear_voice_channel() { return _i<Void>(0xE036A705F989E049); }
	static Void _0xF03755696450470C() { return _i<Void>(0xF03755696450470C); }
	static Void network_close_transition_matchmaking() { return _i<Void>(0x43F4DBA69710E01E); }
	static Void _0x1632BE0AC1E62876(Any p0, Any p1) { return _i<Void>(0x1632BE0AC1E62876, p0, p1); }
	static Void _0xBBDF066252829606(Any p0, bool p1, Any p2) { return _i<Void>(0xBBDF066252829606, p0, p1, p2); }
	static int network_create_synchronised_scene(float x, float y, float z, float xRot, float yRot, float zRot, int p6, int p7, int p8, float p9, Any p10, float p11) { return _i<int>(0x7CD6BC4C2BBDD526, x, y, z, xRot, yRot, zRot, p6, p7, p8, p9, p10, p11); }
	static Any _0xF9B83B77929D8863() { return _i<Any>(0xF9B83B77929D8863); }
	static Any _0x5AE17C6B0134B7F1() { return _i<Any>(0x5AE17C6B0134B7F1); }
	static Void network_disable_invincible_flashing(int player, bool p1) { return _i<Void>(0x9DD368BF06983221, player, p1); }
	static Void _0xC505036A35AFD01B(bool p0) { return _i<Void>(0xC505036A35AFD01B, p0); }
	static Void _0x407091CF6037118E(int netID) { return _i<Void>(0x407091CF6037118E, netID); }
	static Void _0xCA575C391FEA25CC(Any p0) { return _i<Void>(0xCA575C391FEA25CC, p0); }
	static bool network_does_network_id_exist(int netID) { return _i<bool>(0x38CE16C96BD11344, netID); }
	static bool network_does_entity_exist_with_network_id(Entity entity) { return _i<bool>(0x18A47D074708FD68, entity); }
	static bool network_does_tunable_exist(const char* tunableContext, const char* tunableName) { return _i<bool>(0x85E5F8B9B898B20A, tunableContext, tunableName); }
	static bool network_does_tunable_exist_hash(uint32_t tunbaleContext, uint32_t tunableName) { return _i<bool>(0xE4E53E1419D81127, tunbaleContext, tunableName); }
	static bool network_do_transition_quickmatch(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<bool>(0x71FB0EBCD4915D56, p0, p1, p2, p3, p4, p5); }
	static bool network_do_transition_quickmatch_async(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<bool>(0xA091A5E44F0072E5, p0, p1, p2, p3, p4, p5); }
	static bool network_do_transition_quickmatch_with_group(Any p0, Any p1, Any p2, Any p3, Any* p4, Any p5, Any p6, Any p7) { return _i<bool>(0x9C4AB58491FDC98A, p0, p1, p2, p3, p4, p5, p6, p7); }
	static bool network_do_transition_to_freemode(Any* p0, Any p1, bool p2, int players, bool p4) { return _i<bool>(0x3AAD8B2FCA1E289F, p0, p1, p2, players, p4); }
	static bool network_do_transition_to_game(bool p0, int maxPlayers) { return _i<bool>(0x3E9BB38102A589B0, p0, maxPlayers); }
	static bool network_do_transition_to_new_freemode(Any* p0, Any p1, int players, bool p3, bool p4, bool p5) { return _i<bool>(0x9E80A5BA8109F974, p0, p1, players, p3, p4, p5); }
	static bool network_do_transition_to_new_game(bool p0, int maxPlayers, bool p2) { return _i<bool>(0x4665F51EFED00034, p0, maxPlayers, p2); }
	static Void _0xE6717E652B8C8D8A(Any p0, Any p1) { return _i<Void>(0xE6717E652B8C8D8A, p0, p1); }
	static Void _0x5E3AA4CA2B6FB0EE(Any p0) { return _i<Void>(0x5E3AA4CA2B6FB0EE, p0); }
	static Void network_end_tutorial_session() { return _i<Void>(0xD0AFAFF5A51D72F7); }
	static bool _0xE64A3CA08DFA37A9(Any p0) { return _i<bool>(0xE64A3CA08DFA37A9, p0); }
	static bool _0x4DF7CFFF471A7FB1(Any p0) { return _i<bool>(0x4DF7CFFF471A7FB1, p0); }
	static bool _0x4A2D4E8BF4265B0F(Any p0) { return _i<bool>(0x4A2D4E8BF4265B0F, p0); }
	static Any _0x815F18AD865F057F(Any p0) { return _i<Any>(0x815F18AD865F057F, p0); }
	static Void _0x2A5E0621DD815A9A(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x2A5E0621DD815A9A, p0, p1, p2, p3); }
	static Any network_explode_vehicle(Vehicle vehicle, bool isAudible, bool isInvisible, bool p3) { return _i<Any>(0x301A42153C9AD707, vehicle, isAudible, isInvisible, p3); }
	static Void network_fade_in_entity(Entity entity, bool state, Any p2) { return _i<Void>(0x1F4ED342ACEFE62D, entity, state, p2); }
	static Void network_fade_out_entity(Entity entity, bool normal, bool slow) { return _i<Void>(0xDE564951F95E09ED, entity, normal, slow); }
	static bool network_x_affects_gamers(Any p0) { return _i<bool>(0xE532D6811B3A4D2A, p0); }
	static Any _0xFB1F9381E80FA13F(int p0, Any p1) { return _i<Any>(0xFB1F9381E80FA13F, p0, p1); }
	static bool network_find_matched_gamers(Any p0, float p1, float p2, float p3) { return _i<bool>(0xF7B2CFDE5C9F700D, p0, p1, p2, p3); }
	static Void _0x64F62AFB081E260D() { return _i<Void>(0x64F62AFB081E260D); }
	static Void _0xB7C7F6AD6424304B() { return _i<Void>(0xB7C7F6AD6424304B); }
	static Void _0xC9B43A33D09CADA7(Any p0) { return _i<Void>(0xC9B43A33D09CADA7, p0); }
	static bool network_gamertag_from_handle_pending() { return _i<bool>(0xB071E27958EF4CF0); }
	static bool network_gamertag_from_handle_start(int* network_handle) { return _i<bool>(0x9F0C0A981D73FA56, network_handle); }
	static bool network_gamertag_from_handle_succeeded() { return _i<bool>(0xFD00798DBA7523DD); }
	static bool network_gamer_has_headset(Any* p0) { return _i<bool>(0xF2FD55CB574BCC55, p0); }
	static int network_get_activity_player_num(bool p0) { return _i<int>(0x73E2B500410DA5A2, p0); }
	static Any _0x9614B71F8ADB982B() { return _i<Any>(0x9614B71F8ADB982B); }
	static bool network_get_desroyer_of_entity(Any p0, Any p1, uint32_t* p2) { return _i<bool>(0x4CACA84440FA26F6, p0, p1, p2); }
	static Any _0x83660B734994124D(Any p0, Any p1, Any p2) { return _i<Any>(0x83660B734994124D, p0, p1, p2); }
	static Any _0x350C23949E43686C() { return _i<Any>(0x350C23949E43686C); }
	static Any _0xD414BE129BB81B32() { return _i<Any>(0xD414BE129BB81B32); }
	static Any _0x0E3A041ED6AC2B45() { return _i<Any>(0x0E3A041ED6AC2B45); }
	static Any _0x7DB53B37A2F211A0() { return _i<Any>(0x7DB53B37A2F211A0); }
	static int get_tunables_content_modifier_id(uint32_t contentHash) { return _i<int>(0x187382F8A3E0A6C3, contentHash); }
	static bool network_get_currently_selected_gamer_handle_from_invite_menu(Any* p0) { return _i<bool>(0x74881E6BCAE2327C, p0); }
	static Any _0xC434133D9BA52777(Any p0, Any p1) { return _i<Any>(0xC434133D9BA52777, p0, p1); }
	static int network_get_destroyer_of_network_id(int netId, uint32_t* weaponHash) { return _i<int>(0x7A1ADEEF01740A24, netId, weaponHash); }
	static Entity network_get_entity_from_network_id(int netId) { return _i<Entity>(0xCE4E5D9B0A4FF560, netId); }
	static Vehicle net_to_veh(int netHandle) { return _i<Vehicle>(0x367B936610BA360C, netHandle); }
	static Ped net_to_ped(int netHandle) { return _i<Ped>(0xBDCD95FC216A8B3E, netHandle); }
	static Object net_to_obj(int netHandle) { return _i<Object>(0xD8515F5FEA14CB3F, netHandle); }
	static Entity net_to_ent(int netHandle) { return _i<Entity>(0xBFFEAB45A9A9094A, netHandle); }
	static Any _0x37D5F739FD494675(Any p0) { return _i<Any>(0x37D5F739FD494675, p0); }
	static bool network_get_entity_is_local(Entity entity) { return _i<bool>(0x0991549DE4D64762, entity); }
	static bool network_get_entity_is_networked(Entity entity) { return _i<bool>(0xC7827959479DCC78, entity); }
	static Entity network_get_entity_killer_of_player(Player player, uint32_t* weaponHash) { return _i<Entity>(0x42B2DAA6B596F5F8, player, weaponHash); }
	static bool network_get_found_gamer(Any* p0, Any p1) { return _i<bool>(0x9DCFF2AFB68B3476, p0, p1); }
	static int network_get_friend_count() { return _i<int>(0x203F1CFD823B27A4); }
	static const char* network_get_friend_name(Player player) { return _i<const char*>(0xE11EBBB2A783FE8B, player); }
	static const char* network_get_friend_name_from_index(int friendIndex) { return _i<const char*>(0x4164F227D052E293, friendIndex); }
	static const char* network_get_gamertag_from_handle(int* network_handle) { return _i<const char*>(0x426141162EBE5CDB, network_handle); }
	static Any _0x2CC848A861D01493() { return _i<Any>(0x2CC848A861D01493); }
	static bool _0x02A8BEC6FD9AF660(Any* p0, Any p1) { return _i<bool>(0x02A8BEC6FD9AF660, p0, p1); }
	static Void network_get_server_time(int* hours, int* minutes, int* seconds) { return _i<Void>(0x6D03BFBD643B2A02, hours, minutes, seconds); }
	static Any _0x52C1EADAF7B10302() { return _i<Any>(0x52C1EADAF7B10302); }
	static int network_get_host_of_script(const char* scriptName, int p1, int p2) { return _i<int>(0x1D6A14F1F9A736FC, scriptName, p1, p2); }
	static Any network_get_host_of_this_script() { return _i<Any>(0xC7B4D79B01FA7A5C); }
	static Any _0x638A3A81733086DB() { return _i<Any>(0x638A3A81733086DB); }
	static Any _0x3855FB5EB2C5E8B2(Any p0) { return _i<Any>(0x3855FB5EB2C5E8B2, p0); }
	static Any _0x2DA41ED6E1FCD7A5(Any p0, Any p1) { return _i<Any>(0x2DA41ED6E1FCD7A5, p0, p1); }
	static math::vector3<float> _0x64D779659BC37B19(Any p0) { return _i<math::vector3<float>>(0x64D779659BC37B19, p0); }
	static math::vector3<float> _0x125E6D638B8605D4(Any p0) { return _i<math::vector3<float>>(0x125E6D638B8605D4, p0); }
	static math::vector3<float> _0x33DE49EDF4DDE77A(Any p0) { return _i<math::vector3<float>>(0x33DE49EDF4DDE77A, p0); }
	static Void network_get_local_handle(int* network_handle, int bufferSize) { return _i<Void>(0xE86051786B66CD8E, network_handle, bufferSize); }
	static int network_unlink_networked_synchronised_scene(int netScene) { return _i<int>(0x02C40BF885C567B6, netScene); }
	static int network_get_max_friends() { return _i<int>(0xAFEBB0D5D8F687D2); }
	static int network_get_num_participants_host() { return _i<int>(0xA6C90FBC38E395EE); }
	static Void _0xADB57E5B663CCA8B(Player p0, float* p1, float* p2) { return _i<Void>(0xADB57E5B663CCA8B, p0, p1, p2); }
	static Any _0xD38C4A6D047C019D() { return _i<Any>(0xD38C4A6D047C019D); }
	static int network_get_num_connected_players() { return _i<int>(0xA4A79DD2D9600654); }
	static int network_get_num_found_gamers() { return _i<int>(0xA1B043EE79A916FB); }
	static int network_get_num_participants() { return _i<int>(0x18D0456E86604654); }
	static int network_get_num_presence_invites() { return _i<int>(0xCEFA968912D0F78D); }
	static int network_get_num_script_participants(Any* p0, Any p1, Any p2) { return _i<int>(0x3658E8CD94FC121A, p0, p1, p2); }
	static Any _0x617F49C2668E6155() { return _i<Any>(0x617F49C2668E6155); }
	static Any _0xFF8FCF9FFC458A1C() { return _i<Any>(0xFF8FCF9FFC458A1C); }
	static int network_get_participant_index(int index) { return _i<int>(0x1B84DF6AF2A46938, index); }
	static Any _0x120364DE2845DAF8(Any* p0, Any p1) { return _i<Any>(0x120364DE2845DAF8, p0, p1); }
	static Any _0x01ABCE5E7CBDA196() { return _i<Any>(0x01ABCE5E7CBDA196); }
	static Player network_get_player_from_gamer_handle(int* network_handle) { return _i<Player>(0xCE5F689CF5A0A49D, network_handle); }
	static int network_get_player_index(Player player) { return _i<int>(0x24FB80D107371267, player); }
	static Player network_get_player_index_from_ped(Ped ped) { return _i<Player>(0x6C0E2E0125610278, ped); }
	static float network_get_player_loudness(Any p0) { return _i<float>(0x21A1684A25C2867F, p0); }
	static bool _0x82377B65E943F72D(Any p0) { return _i<bool>(0x82377B65E943F72D, p0); }
	static Any _0x3B39236746714134(Any p0) { return _i<Any>(0x3B39236746714134, p0); }
	static Any _0xAA5FAFCD2C5F5E47() { return _i<Any>(0xAA5FAFCD2C5F5E47); }
	static Any _0x24409FC4C55CB22D(Any p0) { return _i<Any>(0x24409FC4C55CB22D, p0); }
	static bool _0x3DBF2DF0AEB7D289(Any p0) { return _i<bool>(0x3DBF2DF0AEB7D289, p0); }
	static bool network_get_presence_invite_handle(Any p0, Any* p1) { return _i<bool>(0x38D5B0FEBB086F75, p0, p1); }
	static Any network_get_presence_invite_id(Any p0) { return _i<Any>(0xDFF09646E12EC386, p0); }
	static Any _0x742B58F723233ED9(Any p0) { return _i<Any>(0x742B58F723233ED9, p0); }
	static Any network_get_presence_invite_inviter(Any p0) { return _i<Any>(0x4962CC4AA2F345B7, p0); }
	static bool _0x8806CEBFABD3CE05(Any p0) { return _i<bool>(0x8806CEBFABD3CE05, p0); }
	static Any _0x728C4CC7920CD102(Any p0) { return _i<Any>(0x728C4CC7920CD102, p0); }
	static Any _0xD39B3FFF8FFDD5BF(Any p0) { return _i<Any>(0xD39B3FFF8FFDD5BF, p0); }
	static Any network_get_presence_invite_session_id(Any p0) { return _i<Any>(0x26E1CD96B0903D60, p0); }
	static Void network_get_primary_clan_data_cancel() { return _i<Void>(0x042E4B70B93E6054); }
	static Any network_get_primary_clan_data_clear() { return _i<Any>(0x9AA46BADAD0E27ED); }
	static bool network_get_primary_clan_data_new(Any* p0, Any* p1) { return _i<bool>(0xC080FF658B2E41DA, p0, p1); }
	static Any network_get_primary_clan_data_pending() { return _i<Any>(0xB5074DB804E28CE7); }
	static bool network_get_primary_clan_data_start(Any* p0, Any p1) { return _i<bool>(0xCE86D8191B762107, p0, p1); }
	static Any network_get_primary_clan_data_success() { return _i<Any>(0x5B4F04F19376A0BA); }
	static int network_get_random_int() { return _i<int>(0x599E4FA1F87EB5FF); }
	static int network_get_random_int_in_range(int rangeStart, int rangeEnd) { return _i<int>(0xE30CF56F1EFA5F43, rangeStart, rangeEnd); }
	static Void network_get_respawn_result(int randomInt, math::vector3<float>* coordinates, float* heading) { return _i<Void>(0x371EA43692861CF1, randomInt, coordinates, heading); }
	static Any _0x6C34F1208B8923FD(Any p0) { return _i<Any>(0x6C34F1208B8923FD, p0); }
	static int network_get_script_status() { return _i<int>(0x57D158647A6BFABF); }
	static Any network_get_talker_proximity() { return _i<Any>(0x84F0F13120B4E098); }
	static bool network_get_this_script_is_network_script() { return _i<bool>(0x2910669969E9535E); }
	static int network_get_timeout_time() { return _i<int>(0x5ED0356A0CE3A34F); }
	static int _0xCF61D4B4702EE9EB() { return _i<int>(0xCF61D4B4702EE9EB); }
	static bool network_get_transition_host(int* network_handle) { return _i<bool>(0x65042B9774C4435E, network_handle); }
	static Any network_get_transition_members(Any* p0, Any p1) { return _i<Any>(0x73B000F7FBC55829, p0, p1); }
	static Any _0x10BD227A753B0D84() { return _i<Any>(0x10BD227A753B0D84); }
	static Any _0x3765C3A3E8192E10() { return _i<Any>(0x3765C3A3E8192E10); }
	static Void network_handle_from_friend(Player friendIndex, int* network_handle, int bufferSize) { return _i<Void>(0xD45CB817D7E177D2, friendIndex, network_handle, bufferSize); }
	static Void network_handle_from_member_id(const char* memberId, int* network_handle, int bufferSize) { return _i<Void>(0xA0FD21BED61E5C4C, memberId, network_handle, bufferSize); }
	static Void network_handle_from_player(Player player, int* network_handle, int bufferSize) { return _i<Void>(0x388EB2B86C73B6B3, player, network_handle, bufferSize); }
	static Void network_handle_from_user_id(const char* userId, int* network_handle, int bufferSize) { return _i<Void>(0xDCD51DD8F87AEC5C, userId, network_handle, bufferSize); }
	static uint32_t network_hash_from_gamer_handle(int* network_handle) { return _i<uint32_t>(0x58575AC3CF2CA8EC, network_handle); }
	static uint32_t network_hash_from_player_handle(Player player) { return _i<uint32_t>(0xBC1D768F2F5D6C05, player); }
	static bool _0x1353F87E89946207() { return _i<bool>(0x1353F87E89946207); }
	static Any _0x26F07DD83A5F7F98() { return _i<Any>(0x26F07DD83A5F7F98); }
	static bool _0x2E0BF682CC778D49(Any p0) { return _i<bool>(0x2E0BF682CC778D49, p0); }
	static bool _0x237D5336A9A54108(Any p0) { return _i<bool>(0x237D5336A9A54108, p0); }
	static Any _0xC42DD763159F3461() { return _i<Any>(0xC42DD763159F3461); }
	static bool network_has_control_of_door(int doorID) { return _i<bool>(0xCB3C68ADB06195DF, doorID); }
	static bool network_has_control_of_entity(Entity entity) { return _i<bool>(0x01BF60A500E28887, entity); }
	static bool network_has_control_of_network_id(int netId) { return _i<bool>(0x4D36070FE0215186, netId); }
	static bool network_has_control_of_pickup(Pickup pickup) { return _i<bool>(0x5BC9495F0B3B6FA6, pickup); }
	static bool _0xB07D3185E11657A5(Entity p0) { return _i<bool>(0xB07D3185E11657A5, p0); }
	static bool network_has_follow_invite() { return _i<bool>(0x76D9B976C4C09FDE); }
	static bool network_has_headset() { return _i<bool>(0xE870F9F1F7B4F1FA); }
	static bool network_has_invited_gamer(Any* p0) { return _i<bool>(0x4D86CD31E8976ECE, p0); }
	static bool network_has_invited_gamer_to_transition(Any* p0) { return _i<bool>(0x7284A47B3540E6CF, p0); }
	static Any _0x71DC455F5CD1C2B1(Any p0) { return _i<Any>(0x71DC455F5CD1C2B1, p0); }
	static bool network_has_pending_invite() { return _i<bool>(0xAC8C7B9B88C4A668); }
	static bool network_has_player_started_transition(Player player) { return _i<bool>(0x9AC9CCBFA8C29795, player); }
	static bool _0x5D10B3795F3FC886() { return _i<bool>(0x5D10B3795F3FC886); }
	static bool network_has_ros_privilege(int p0) { return _i<bool>(0xA699957E60D80214, p0); }
	static bool _0xC22912B1D85F26B1(Any p0, Any* p1, Any* p2) { return _i<bool>(0xC22912B1D85F26B1, p0, p1, p2); }
	static Any _0x593570C289A77688() { return _i<Any>(0x593570C289A77688); }
	static Any _0x91B87C55093DE351() { return _i<Any>(0x91B87C55093DE351); }
	static bool _0x67A5589628E0CFF6() { return _i<bool>(0x67A5589628E0CFF6); }
	static Any _0x76BF03FADBF154F5() { return _i<Any>(0x76BF03FADBF154F5); }
	static bool _0x3F9990BF5F22759C(Any* p0) { return _i<bool>(0x3F9990BF5F22759C, p0); }
	static bool network_are_ros_available() { return _i<bool>(0x85443FF4C328F53B); }
	static bool _0xB57A49545BA53CE7(Any* p0) { return _i<bool>(0xB57A49545BA53CE7, p0); }
	static bool _0xCCA4318E1AB03F1F(Any* p0) { return _i<bool>(0xCCA4318E1AB03F1F, p0); }
	static bool _0x07DD29D5E22763F1(Any* p0) { return _i<bool>(0x07DD29D5E22763F1, p0); }
	static bool _0xAEEF48CDF5B6CE7C(Any p0, Any p1) { return _i<bool>(0xAEEF48CDF5B6CE7C, p0, p1); }
	static bool network_have_online_privileges() { return _i<bool>(0x25CB5A9F37BFD063); }
	static Any _0x5EA784D197556507() { return _i<Any>(0x5EA784D197556507); }
	static bool is_rockstar_banned() { return _i<bool>(0x8020A73847E0CA7D); }
	static bool is_socialclub_banned() { return _i<bool>(0xA0AD7E2AF5349F61); }
	static Any _0x422D396F80A96547() { return _i<Any>(0x422D396F80A96547); }
	static bool can_play_online() { return _i<bool>(0x5F91D5D0B36AA310); }
	static Any _0x606E4D3E3CCCF3EB() { return _i<Any>(0x606E4D3E3CCCF3EB); }
	static Any _0x66B59CFFD78467AF() { return _i<Any>(0x66B59CFFD78467AF); }
	static bool _0x72D918C99BCACC54(Any p0) { return _i<bool>(0x72D918C99BCACC54, p0); }
	static Void _0xFAC18E7356BD3210() { return _i<Void>(0xFAC18E7356BD3210); }
	static Any network_host_transition(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Any>(0xA60BB5CE242BB254, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void _0x4C2A9FDC22377075() { return _i<Void>(0x4C2A9FDC22377075); }
	static bool network_invite_gamers(Any* p0, Any p1, Any* p2, Any* p3) { return _i<bool>(0x9D80CD1D0E6327DE, p0, p1, p2, p3); }
	static bool network_invite_gamers_to_transition(Any* p0, Any p1) { return _i<bool>(0x4A595C32F77DFF76, p0, p1); }
	static bool network_is_activity_session() { return _i<bool>(0x05095437424397FA); }
	static Any network_is_activity_spectator() { return _i<Any>(0x12103B9E0C9F92FB); }
	static bool network_is_activity_spectator_from_handle(int* network_handle) { return _i<bool>(0x2763BBAA72A7BCB9, network_handle); }
	static Any network_is_adding_friend() { return _i<Any>(0x6EA101606F6E4D81); }
	static Any _0x2E4C123D1C8A710E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Any>(0x2E4C123D1C8A710E, p0, p1, p2, p3, p4, p5, p6); }
	static bool network_is_cable_connected() { return _i<bool>(0xEFFB25453D8600F9); }
	static bool network_is_chatting_in_platform_party(int* network_handle) { return _i<bool>(0x8DE9945BCC9AEC52, network_handle); }
	static bool network_is_clock_time_overridden() { return _i<bool>(0xD7C95D322FF57522); }
	static bool network_is_cloud_available() { return _i<bool>(0x9A4CF4F48AD77302); }
	static bool has_bg_script_been_downloaded() { return _i<bool>(0x8132C0EB8B2B3293); }
	static Any _0x16D3D49902F697BB() { return _i<Any>(0x16D3D49902F697BB); }
	static bool network_has_control_of_pavement_stats(uint32_t hash) { return _i<bool>(0xC01E93FAC20C3346, hash); }
	static Any _0x71302EC70689052A(Any p0) { return _i<Any>(0x71302EC70689052A, p0); }
	static bool _0x422F32CC7E56ABAD(Any p0) { return _i<bool>(0x422F32CC7E56ABAD, p0); }
	static bool network_is_finding_gamers() { return _i<bool>(0xDDDF64C91BFCF0AA); }
	static bool network_is_friend(int* network_handle) { return _i<bool>(0x1A24A179F9B31654, network_handle); }
	static bool network_is_friend_online2(int* network_handle) { return _i<bool>(0x87EB7A3FFCB314DB, network_handle); }
	static bool network_is_friend_index_online(int friendIndex) { return _i<bool>(0xBAD8F2A42B844821, friendIndex); }
	static bool network_is_friend_in_multiplayer(const char* friendName) { return _i<bool>(0x57005C18827F3A28, friendName); }
	static bool network_is_friend_in_same_title(const char* friendName) { return _i<bool>(0x2EA9A3BEDF3F17B8, friendName); }
	static bool network_is_friend_online(const char* name) { return _i<bool>(0x425A44533437B64D, name); }
	static bool network_is_gamer_blocked_by_me(Any* p0) { return _i<bool>(0xE944C4F5AF1B5883, p0); }
	static bool network_is_gamer_in_my_session(int* network_handle) { return _i<bool>(0x0F10B05DDF8D16E9, network_handle); }
	static bool network_is_gamer_muted_by_me(int* p0) { return _i<bool>(0xCE60DE011B6C7978, p0); }
	static bool network_is_gamer_talking(int* p0) { return _i<bool>(0x71C33B22606CD88A, p0); }
	static bool network_is_game_in_progress() { return _i<bool>(0x10FAB35428CCC9D7); }
	static Any _0x94A8394D150B013A() { return _i<Any>(0x94A8394D150B013A); }
	static bool network_is_handle_valid(int* network_handle, int bufferSize) { return _i<bool>(0x6F79B93B0A8E4133, network_handle, bufferSize); }
	static bool network_is_host() { return _i<bool>(0x8DB296B814EDDA07); }
	static bool network_is_host_of_this_script() { return _i<bool>(0x83CD99A1E6061AB5); }
	static bool network_is_inactive_profile(Any* p0) { return _i<bool>(0x7E58745504313A2E, p0); }
	static bool network_is_in_mp_cutscene() { return _i<bool>(0x6CC27C9FA2040220); }
	static Any _0x2FC5650B0271CB57() { return _i<Any>(0x2FC5650B0271CB57); }
	static Any _0xFD8B834A8BA05048() { return _i<Any>(0xFD8B834A8BA05048); }
	static bool network_is_session_active() { return _i<bool>(0xD83C2B94E7508980); }
	static bool network_is_in_session() { return _i<bool>(0xCA97246103B63917); }
	static bool network_is_in_spectator_mode() { return _i<bool>(0x048746E388762E11); }
	static bool network_is_in_transition() { return _i<bool>(0x68049AEFF83D8F0A); }
	static Any network_is_in_tutorial_session() { return _i<Any>(0xADA24309FE08DACF); }
	static bool network_is_local_player_invincible() { return _i<bool>(0x8A8694B48715B000); }
	static bool network_is_multiplayer_disabled() { return _i<bool>(0x9747292807126EDA); }
	static Any _0x7242F8B741CE1086(Any p0) { return _i<Any>(0x7242F8B741CE1086, p0); }
	static Any _0x74698374C45701D2() { return _i<Any>(0x74698374C45701D2); }
	static bool network_is_participant_active(int p0) { return _i<bool>(0x6FF8FF40B6357D45, p0); }
	static Any _0xA8ACB6459542A8C8() { return _i<Any>(0xA8ACB6459542A8C8); }
	static bool network_is_player_active(Player player) { return _i<bool>(0xB8DFD30D6973E135, player); }
	static bool network_is_player_a_participant(Any p0) { return _i<bool>(0x3CA58F6CB7CBD784, p0); }
	static bool _0x1AD5B71586B94820(Player p0, Any* p1, Any p2) { return _i<bool>(0x1AD5B71586B94820, p0, p1, p2); }
	static bool network_is_player_blocked_by_me(Player player) { return _i<bool>(0x57AF1F8E27483721, player); }
	static bool _0x919B3C98ED8292F9(Any p0) { return _i<bool>(0x919B3C98ED8292F9, p0); }
	static bool network_is_player_connected(Player player) { return _i<bool>(0x93DC1BE4E1ABE9D1, player); }
	static bool _0x631DC5DFF4B110E3(Any p0) { return _i<bool>(0x631DC5DFF4B110E3, p0); }
	static bool network_is_player_in_mp_cutscene(Player player) { return _i<bool>(0x63F9EE203C3619F2, player); }
	static bool network_is_player_muted_by_me(Player player) { return _i<bool>(0x8C71288AE68EDE39, player); }
	static bool network_is_player_talking(Player player) { return _i<bool>(0x031E11F3D447647E, player); }
	static Any _0xC0D2AF00BCC234CA() { return _i<Any>(0xC0D2AF00BCC234CA); }
	static Any _0x14922ED3E38761F0() { return _i<Any>(0x14922ED3E38761F0); }
	static bool _0x8D11E61A4ABF49CC() { return _i<bool>(0x8D11E61A4ABF49CC); }
	static bool network_is_script_active(const char* scriptName, Any p1, bool p2, Any p3) { return _i<bool>(0x9D40DF90FAD26098, scriptName, p1, p2, p3); }
	static bool network_is_session_busy() { return _i<bool>(0xF4435D66A8E2905E); }
	static bool network_is_session_started() { return _i<bool>(0x9DE624D2FC4B603F); }
	static bool network_is_signed_in() { return _i<bool>(0x054354A99211EB96); }
	static Any network_is_transition_busy() { return _i<Any>(0x520F3282A53D26B7); }
	static Any _0x0DBD5D7E3C5BEC3B() { return _i<Any>(0x0DBD5D7E3C5BEC3B); }
	static Any _0x6512765E3BE78C50() { return _i<Any>(0x6512765E3BE78C50); }
	static Any network_is_transition_host() { return _i<Any>(0x0B824797C9BF2159); }
	static bool network_is_transition_host_from_handle(int* network_handle) { return _i<bool>(0x6B5C83BA3EFE6A10, network_handle); }
	static Any _0xC571D0E77D8BBC29() { return _i<Any>(0xC571D0E77D8BBC29); }
	static Any network_is_transition_matchmaking() { return _i<Any>(0x292564C735375EDF); }
	static Any _0x37A4494483B9F5C9() { return _i<Any>(0x37A4494483B9F5C9); }
	static bool _0x5A6AA44FF8E931E6() { return _i<bool>(0x5A6AA44FF8E931E6); }
	static bool _0x5DC577201723960A() { return _i<bool>(0x5DC577201723960A); }
	static bool network_is_transition_started() { return _i<bool>(0x53FA83401D9C07FE); }
	static Any network_is_transition_to_game() { return _i<Any>(0x9D7696D8F4FA6CB7); }
	static Any _0xD0A484CB2F829FBE() { return _i<Any>(0xD0A484CB2F829FBE); }
	static bool has_tunables_been_downloaded() { return _i<bool>(0x0467C11ED88B7D28); }
	static Any _0x35F0B98A8387274D() { return _i<Any>(0x35F0B98A8387274D); }
	static Any network_join_group_activity() { return _i<Any>(0xA06509A691D12BE4); }
	static Any _0x59DF79317F85A7E0() { return _i<Any>(0x59DF79317F85A7E0); }
	static Any _0xFFE1E5B792D92B34() { return _i<Any>(0xFFE1E5B792D92B34); }
	static bool network_join_transition(Player player) { return _i<bool>(0x9D060B08CD63321A, player); }
	static Any network_launch_transition() { return _i<Any>(0x2DCF46CB1A4F0884); }
	static Void _0xBF22E0F32968E967(Player player, bool p1) { return _i<Void>(0xBF22E0F32968E967, player, p1); }
	static Void network_respawn_coords(Player player, float x, float y, float z, bool p4, bool p5) { return _i<Void>(0x9769F811D1785B03, player, x, y, z, p4, p5); }
	static Any network_leave_transition() { return _i<Any>(0xD23A1A815D21DB19); }
	static Void _0x261E97AD7BCF3D40(bool p0) { return _i<Void>(0x261E97AD7BCF3D40, p0); }
	static Void _0x39917E1B4CB0F911(bool p0) { return _i<Void>(0x39917E1B4CB0F911, p0); }
	static bool network_mark_transition_gamer_as_fully_joined(Any* p0) { return _i<bool>(0x5728BB6D63E3FF1D, p0); }
	static const char* network_member_id_from_gamer_handle(int* network_handle) { return _i<const char*>(0xC82630132081BB6F, network_handle); }
	static Any _0x53C10C8BD774F2C9() { return _i<Any>(0x53C10C8BD774F2C9); }
	static Void _0x283B6062A2C01E9B() { return _i<Void>(0x283B6062A2C01E9B); }
	static Void network_open_transition_matchmaking() { return _i<Void>(0x2B3A8F7CA3A38FDE); }
	static Void network_override_chat_restrictions(Player player, bool toggle) { return _i<Void>(0x3039AE5AD2C9C0C4, player, toggle); }
	static Void network_override_clock_time(int Hours, int Minutes, int Seconds) { return _i<Void>(0xE679E3E06E363892, Hours, Minutes, Seconds); }
	static Void _0xA7E30DE9272B6D49(Ped ped, float x, float y, float z, float p4) { return _i<Void>(0xA7E30DE9272B6D49, ped, x, y, z, p4); }
	static Void network_override_receive_restrictions(Player player, bool toggle) { return _i<Void>(0xDDF73E2B1FEC5AB4, player, toggle); }
	static Void _0x0FF2862B61A58AF9(bool p0) { return _i<Void>(0x0FF2862B61A58AF9, p0); }
	static Void network_override_send_restrictions(Player player, bool toggle) { return _i<Void>(0x97DD4C5944CC2E6A, player, toggle); }
	static Void network_chat_mute(bool p0) { return _i<Void>(0x57B192B4D4AD23D5, p0); }
	static Void _0x6F697A66CE78674E(int team, bool toggle) { return _i<Void>(0x6F697A66CE78674E, team, toggle); }
	static Void network_override_transition_chat(bool p0) { return _i<Void>(0xAF66059A131AA269, p0); }
	static Any _0x172F75B6EE2233BA() { return _i<Any>(0x172F75B6EE2233BA); }
	static const char* network_player_get_name(Player player) { return _i<const char*>(0x7718D2E2060837D2, player); }
	static const char* network_player_get_userid(Player player, char* buffer) { return _i<const char*>(0x4927FC39CD0869A0, player, buffer); }
	static bool network_player_has_headset(Player player) { return _i<bool>(0x3FB99A8B08D18FD6, player); }
	static bool _0x565E430DB3B05BEC(Any p0) { return _i<bool>(0x565E430DB3B05BEC, p0); }
	static bool network_player_is_badsport() { return _i<bool>(0x19D8DA0E5A68045A); }
	static bool network_player_is_cheater() { return _i<bool>(0x655B91F1495A9090); }
	static bool network_player_is_rockstar_dev(Player player) { return _i<bool>(0x544ABDDA3B409B6D, player); }
	static Void _0x2302C0264EA58D31() { return _i<Void>(0x2302C0264EA58D31); }
	static Any _0x3C891A251567DFCE(Any* p0) { return _i<Any>(0x3C891A251567DFCE, p0); }
	static bool network_get_gamer_status(Any* p0) { return _i<bool>(0x85A0EF54A500882C, p0); }
	static Void _0x45A83257ED02D9BC() { return _i<Void>(0x45A83257ED02D9BC); }
	static Void network_register_entity_as_networked(Entity entity) { return _i<Void>(0x06FAACD625D80CAA, entity); }
	static Void network_register_host_broadcast_variables(int* vars, int numVars) { return _i<Void>(0x3E9B2F01C50DF595, vars, numVars); }
	static Void network_register_player_broadcast_variables(int* vars, int numVars) { return _i<Void>(0x3364AA97340CA215, vars, numVars); }
	static Void _0xCFEB46DCD7D8D5EB(bool p0) { return _i<Void>(0xCFEB46DCD7D8D5EB, p0); }
	static Void _0x25D990F8E0E3F13C() { return _i<Void>(0x25D990F8E0E3F13C); }
	static Void network_remove_all_transition_invite() { return _i<Void>(0x726E0375C7A26368); }
	static Void _0xEBF8284D8CADEB53() { return _i<Void>(0xEBF8284D8CADEB53); }
	static Void _0xF083835B70BA9BFE() { return _i<Void>(0xF083835B70BA9BFE); }
	static bool network_remove_entity_area(Any p0) { return _i<bool>(0x93CF869BAA0C4874, p0); }
	static bool network_remove_presence_invite(Any p0) { return _i<bool>(0xF0210268DB0974B1, p0); }
	static Void network_remove_transition_invite(Any* p0) { return _i<Void>(0x7524B431B2E6F7EE, p0); }
	static Any _0x5626D9D6810730D5() { return _i<Any>(0x5626D9D6810730D5); }
	static bool network_request_cloud_background_scripts() { return _i<bool>(0x924426BFFD82E915); }
	static Void network_request_cloud_tunables() { return _i<Void>(0x42FB3B532D526E6C); }
	static bool network_request_control_of_door(int doorID) { return _i<bool>(0x870DDFD5A4A796E4, doorID); }
	static bool network_request_control_of_entity(Entity entity) { return _i<bool>(0xB69317BF5E782347, entity); }
	static bool network_request_control_of_network_id(int netId) { return _i<bool>(0xA670B3662FAFFBD0, netId); }
	static Any _0x62A0296C1BB1CEB3() { return _i<Any>(0x62A0296C1BB1CEB3); }
	static Void _0x741A3D8380319A81() { return _i<Void>(0x741A3D8380319A81); }
	static Void network_reset_body_tracker() { return _i<Void>(0x72433699B4E6DD64); }
	static Void network_resurrect_local_player(float x, float y, float z, float heading, bool unk, bool changetime, Any p6) { return _i<Void>(0xEA23C49EAA83ACFB, x, y, z, heading, unk, changetime, p6); }
	static Void _0xB13E88E655E5A3BC() { return _i<Void>(0xB13E88E655E5A3BC); }
	static Void _0xF1B84178F8674195(Any p0) { return _i<Void>(0xF1B84178F8674195, p0); }
	static bool _0x1171A97A3D3981B6(Any* p0, Any* p1, Any p2, Any p3) { return _i<bool>(0x1171A97A3D3981B6, p0, p1, p2, p3); }
	static bool network_send_presence_invite(int* network_handle, const char* p1, Any p2, Any p3) { return _i<bool>(0xC3C7A6AFDB244624, network_handle, p1, p2, p3); }
	static Void _0xFA2888E3833C8E96() { return _i<Void>(0xFA2888E3833C8E96); }
	static bool network_send_text_message(const char* message, int* network_handle) { return _i<bool>(0x3A214F2EC889B100, message, network_handle); }
	static bool network_send_transition_gamer_instruction(int* network_handle, const char* p1, int p2, int p3, bool p4) { return _i<bool>(0x31D1D2B858D25E6B, network_handle, p1, p2, p3, p4); }
	static bool network_send_presence_transition_invite(Any* p0, const char* p1, Any p2, Any p3) { return _i<bool>(0xC116FF9B4D488291, p0, p1, p2, p3); }
	static bool network_session_activity_quickmatch(Any p0, Any p1, Any p2, Any p3) { return _i<bool>(0xBE3E347A87ACEB82, p0, p1, p2, p3); }
	static Void _0xCAE55F48D3D7875C(Any p0) { return _i<Void>(0xCAE55F48D3D7875C, p0); }
	static Void network_session_block_join_requests(bool p0) { return _i<Void>(0xA73667484D7037C3, p0); }
	static Void network_session_cancel_invite() { return _i<Void>(0x2FBF47B1B36D36F9); }
	static Void network_session_change_slots(int p0, bool p1) { return _i<Void>(0xB4AB419E0D86ACAE, p0, p1); }
	static bool network_session_crew_matchmaking(int p0, int p1, int p2, int maxPlayers, bool p4) { return _i<bool>(0x94BC51E9449D917F, p0, p1, p2, maxPlayers, p4); }
	static bool network_session_end(bool p0, bool p1) { return _i<bool>(0xA02E59562D711006, p0, p1); }
	static Any network_session_enter(Any p0, Any p1, Any p2, int maxPlayers, Any p4, Any p5) { return _i<Any>(0x330ED4D05491934F, p0, p1, p2, maxPlayers, p4, p5); }
	static Void network_session_force_cancel_invite() { return _i<Void>(0xA29177F7703B5644); }
	static bool network_session_friend_matchmaking(int p0, int p1, int maxPlayers, bool p3) { return _i<bool>(0x2CFC76E0D087C994, p0, p1, maxPlayers, p3); }
	static int _0xDFFA5BE8381C3314() { return _i<int>(0xDFFA5BE8381C3314); }
	static Void network_session_get_inviter(int* network_handle) { return _i<Void>(0xE57397B4A3429DD0, network_handle); }
	static bool network_session_is_player_voted_to_kick(Player player) { return _i<bool>(0xD6D09A6F32F49EF1, player); }
	static int network_session_get_unk(int p0) { return _i<int>(0x56CE820830EF040B, p0); }
	static Any _0x53AFD64C6758F2F9() { return _i<Any>(0x53AFD64C6758F2F9); }
	static bool network_session_host(int p0, int maxPlayers, bool p2) { return _i<bool>(0x6F3D4ED9BEE4E61D, p0, maxPlayers, p2); }
	static bool network_session_host_closed(int p0, int maxPlayers) { return _i<bool>(0xED34C0C02C098BB7, p0, maxPlayers); }
	static bool network_session_host_friends_only(int p0, int maxPlayers) { return _i<bool>(0xB9CFD27A5D578D83, p0, maxPlayers); }
	static Void network_session_host_single_player(int p0) { return _i<Void>(0xC74C33FCA52856D5, p0); }
	static Any _0xD313DE83394AF134() { return _i<Any>(0xD313DE83394AF134); }
	static bool network_session_is_closed_crew() { return _i<bool>(0x74732C6CA90DA2B4); }
	static bool network_session_is_closed_friends() { return _i<bool>(0xFBCFA2EA2E206890); }
	static Any _0xBDB6F89C729CF388() { return _i<Any>(0xBDB6F89C729CF388); }
	static bool _0x855BC38818F6F684() { return _i<bool>(0x855BC38818F6F684); }
	static bool network_session_is_private() { return _i<bool>(0xCEF70AA5B3F89BA1); }
	static bool network_session_is_solo() { return _i<bool>(0xF3929C2379B60CCE); }
	static Any network_session_is_visible() { return _i<Any>(0xBA416D68C631496A); }
	static Any _0xB5D3453C98456528() { return _i<Any>(0xB5D3453C98456528); }
	static bool _0xEF0912DDF7C4CB4B() { return _i<bool>(0xEF0912DDF7C4CB4B); }
	static Void _0xC6F8AB8A4189CF3A() { return _i<Void>(0xC6F8AB8A4189CF3A); }
	static Void network_session_kick_player(Player player) { return _i<Void>(0xFA8904DC5F304220, player); }
	static Void network_session_leave_single_player() { return _i<Void>(0x3442775428FD2DAA); }
	static Void network_session_mark_visible(bool p0) { return _i<Void>(0x271CC6AB59EBF9A5, p0); }
	static Any _0x041C7F2A6C9894E6(Any p0, Any p1, Any p2) { return _i<Any>(0x041C7F2A6C9894E6, p0, p1, p2); }
	static Void _0x702BC4D605522539(Any p0) { return _i<Void>(0x702BC4D605522539, p0); }
	static Void _0x5ECD378EE64450AB(Any p0) { return _i<Void>(0x5ECD378EE64450AB, p0); }
	static Void _0x600F8CB31C7AAB6E(Any p0) { return _i<Void>(0x600F8CB31C7AAB6E, p0); }
	static Void _0x49EC8030F5015F8B(int p0) { return _i<Void>(0x49EC8030F5015F8B, p0); }
	static Void network_session_set_max_players(int playerType, int playerCount) { return _i<Void>(0x8B6A4DD0AF9CE215, playerType, playerCount); }
	static Void _0xF1EEA2DDA9FFA69D(Any p0) { return _i<Void>(0xF1EEA2DDA9FFA69D, p0); }
	static Void _0x3F52E880AAF6C8CA(bool p0) { return _i<Void>(0x3F52E880AAF6C8CA, p0); }
	static Void _0x59D421683D31835A(Any p0) { return _i<Void>(0x59D421683D31835A, p0); }
	static Void _0x1153FA02A659051C() { return _i<Void>(0x1153FA02A659051C); }
	static Void _0xF49ABC20D8552257(Any p0) { return _i<Void>(0xF49ABC20D8552257, p0); }
	static Void _0x4811BBAC21C5FCD5(Any p0) { return _i<Void>(0x4811BBAC21C5FCD5, p0); }
	static Void _0x5539C3EBF104A53A(bool p0) { return _i<Void>(0x5539C3EBF104A53A, p0); }
	static Void network_session_hosted(bool p0) { return _i<Void>(0xC19F6C8E7865A6FF, p0); }
	static Void _0xABD5E88B8A2D3DB2(Any* globalPtr) { return _i<Void>(0xABD5E88B8A2D3DB2, globalPtr); }
	static Void network_session_voice_host() { return _i<Void>(0x9C1556705F864230); }
	static Void network_session_voice_leave() { return _i<Void>(0x6793E42BE02B575D); }
	static Void network_set_keep_focuspoint(bool p0, Any p1) { return _i<Void>(0x7F8413B7FC2AA6B9, p0, p1); }
	static Void _0x5B8ED3DB018927B1(Any p0) { return _i<Void>(0x5B8ED3DB018927B1, p0); }
	static bool network_session_was_invited() { return _i<bool>(0x23DFB504655D0CE4); }
	static Void _0x0E4F77F7B9D74D84(Any p0) { return _i<Void>(0x0E4F77F7B9D74D84, p0); }
	static Void network_set_activity_spectator(bool toggle) { return _i<Void>(0x75138790B4359A74, toggle); }
	static Void network_set_activity_spectator_max(int maxSpectators) { return _i<Void>(0x9D277B76D1D12222, maxSpectators); }
	static Void _0x5C707A667DF8B9FA(bool p0, Any p1) { return _i<Void>(0x5C707A667DF8B9FA, p0, p1); }
	static bool _0x0EDE326D47CD0F3E(Ped ped, Player player) { return _i<bool>(0x0EDE326D47CD0F3E, ped, player); }
	static bool network_set_currently_selected_gamer_handle_from_invite_menu(Any* p0) { return _i<bool>(0x7206F674F2A3B1BB, p0); }
	static bool _0x796A87B3B68D1F3D(Any* p0) { return _i<bool>(0x796A87B3B68D1F3D, p0); }
	static Void _0xA2E9C1AB8A92E8CD(bool p0) { return _i<Void>(0xA2E9C1AB8A92E8CD, p0); }
	static Void network_set_entity_can_blend(Entity entity, bool toggle) { return _i<Void>(0xD830567D88A1E873, entity, toggle); }
	static Void network_set_entity_invisible_to_network(Entity entity, bool toggle) { return _i<Void>(0xF1CA12B18AEF5298, entity, toggle); }
	static Void network_set_friendly_fire_option(bool toggle) { return _i<Void>(0xF808475FA571D823, toggle); }
	static Void network_set_gamer_invited_to_transition(int* network_handle) { return _i<Void>(0xCA2C8073411ECDB6, network_handle); }
	static Void _0x6A5D89D7769A40D8(bool p0) { return _i<Void>(0x6A5D89D7769A40D8, p0); }
	static Void _0x0D77A82DC2D0DA59(Any* p0, Any* p1) { return _i<Void>(0x0D77A82DC2D0DA59, p0, p1); }
	static Void _0x66F010A4B031A331(Any* p0) { return _i<Void>(0x66F010A4B031A331, p0); }
	static Void _0xFC18DB55AE19E046(bool p0) { return _i<Void>(0xFC18DB55AE19E046, p0); }
	static Void network_set_in_mp_cutscene(bool p0, bool p1) { return _i<Void>(0x9CA5DE655269FEC4, p0, p1); }
	static Void _0x2CE9D95E4051AECD(Any p0) { return _i<Void>(0x2CE9D95E4051AECD, p0); }
	static Void network_set_in_spectator_mode(bool toggle, Ped playerPed) { return _i<Void>(0x423DE3854BB50894, toggle, playerPed); }
	static Void _0x419594E137637120(bool p0, Any p1, bool p2) { return _i<Void>(0x419594E137637120, p0, p1, p2); }
	static Void network_set_local_player_invincible_time(int time) { return _i<Void>(0x2D95C7E2D7E07307, time); }
	static Void _0x524FF0AEFF9C3973(Any p0) { return _i<Void>(0x524FF0AEFF9C3973, p0); }
	static Void _0x7D395EA61622E116(bool p0) { return _i<Void>(0x7D395EA61622E116, p0); }
	static Void _0x94538037EE44F5CF(bool p0) { return _i<Void>(0x94538037EE44F5CF, p0); }
	static Void network_set_mission_finished() { return _i<Void>(0x3B3D11CD9FFCDFC9); }
	static Void _0xF46A1E03E8755980(bool p0) { return _i<Void>(0xF46A1E03E8755980, p0); }
	static Void _0x0379DAF89BA09AA5(Any p0, Any p1) { return _i<Void>(0x0379DAF89BA09AA5, p0, p1); }
	static Void _0xBA7F0B77D80A4EB7() { return _i<Void>(0xBA7F0B77D80A4EB7); }
	static Void network_set_override_spectator_mode(bool toggle) { return _i<Void>(0x70DA3BF8DACD3210, toggle); }
	static Void _0x3C5C1E2C2FF814B1(bool p0) { return _i<Void>(0x3C5C1E2C2FF814B1, p0); }
	static Void _0x1B857666604B1A74(bool p0) { return _i<Void>(0x1B857666604B1A74, p0); }
	static Void _0x367EF5E2F439B4C6(int p0) { return _i<Void>(0x367EF5E2F439B4C6, p0); }
	static Void network_set_property_id(Any p0) { return _i<Void>(0x1775961C2FBBCB5C, p0); }
	static Void _0x9D7AFCBF21C51712(bool p0) { return _i<Void>(0x9D7AFCBF21C51712, p0); }
	static Any _0x4348BFDA56023A2F(Any p0, Any p1) { return _i<Any>(0x4348BFDA56023A2F, p0, p1); }
	static Any _0xB309EBEA797E001F(Any p0) { return _i<Any>(0xB309EBEA797E001F, p0); }
	static Void _0x265559DA40B3F327(Any p0) { return _i<Void>(0x265559DA40B3F327, p0); }
	static Void _0x7AC752103856FB20(bool p0) { return _i<Void>(0x7AC752103856FB20, p0); }
	static Void network_set_talker_proximity(float p0) { return _i<Void>(0xCBF12D65F95AD686, p0); }
	static Void network_set_team_only_chat(bool toggle) { return _i<Void>(0xD5B4883AC32F24C3, toggle); }
	static Void network_set_this_script_is_network_script(int lobbySize, bool p1, int playerId) { return _i<Void>(0x1CA59E306ECB80A5, lobbySize, p1, playerId); }
	static Void network_set_transition_activity_id(Any p0) { return _i<Void>(0x30DE938B516F0AD2, p0); }
	static Void network_set_transition_creator_handle(Any* p0) { return _i<Void>(0xEF26739BCD9907D5, p0); }
	static Void _0x0C978FDA19692C2C(bool p0, bool p1) { return _i<Void>(0x0C978FDA19692C2C, p0, p1); }
	static Void network_set_voice_active(bool toggle) { return _i<Void>(0xBABEC9E69A91C57B, toggle); }
	static Void network_set_voice_channel(Any p0) { return _i<Void>(0xEF6212C2EFEF1A23, p0); }
	static Any _0x82A2B386716608F1() { return _i<Any>(0x82A2B386716608F1); }
	static Void _0x83FE8D7229593017() { return _i<Void>(0x83FE8D7229593017); }
	static Void network_show_profile_ui(int* network_handle) { return _i<Void>(0x859ED1CEA343FCA8, network_handle); }
	static Void _0x9465E683B12D3F6B() { return _i<Void>(0x9465E683B12D3F6B); }
	static Any _0x659CF2EF7F550C4F() { return _i<Any>(0x659CF2EF7F550C4F); }
	static bool _0x5A6FFA2433E2F14C(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, int flags) { return _i<bool>(0x5A6FFA2433E2F14C, player, p1, p2, p3, p4, p5, p6, p7, flags); }
	static bool _0x4BA92A18502BCA61(Player player, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, int flags) { return _i<bool>(0x4BA92A18502BCA61, player, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, flags); }
	static Void _0x17E0198B3882C2CB() { return _i<Void>(0x17E0198B3882C2CB); }
	static Void network_start_synchronised_scene(int netScene) { return _i<Void>(0x9A1B3FCDB36C8697, netScene); }
	static int _0xD66C9E72B3CC4982(Any* p0, Any p1) { return _i<int>(0xD66C9E72B3CC4982, p0, p1); }
	static Any _0x36391F397731595D(Any p0) { return _i<Any>(0x36391F397731595D, p0); }
	static Any _0xDEB2B99A1AF1A2A6(Any p0) { return _i<Any>(0xDEB2B99A1AF1A2A6, p0); }
	static Void network_stop_synchronised_scene(int netScene) { return _i<Void>(0xC254481A4574CB2F, netScene); }
	static Void _0xF814FEC6A19FD6E0() { return _i<Void>(0xF814FEC6A19FD6E0); }
	static Void network_suppress_invite(bool toggle) { return _i<Void>(0xA0682D67EF1FBA3D, toggle); }
	static bool network_is_text_chat_active() { return _i<bool>(0x5FCF4D7069B09026); }
	static Any _0xC3BFED92026A2AAD(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Any>(0xC3BFED92026A2AAD, p0, p1, p2, p3, p4); }
	static Void _0x973D76AA760A6CB6(bool p0) { return _i<Void>(0x973D76AA760A6CB6, p0); }
	static Any _0x04918A41BC9B8157(Any p0, Any p1, Any p2) { return _i<Any>(0x04918A41BC9B8157, p0, p1, p2); }
	static Void _0xF6F4383B7C92F11A(Any p0) { return _i<Void>(0xF6F4383B7C92F11A, p0); }
	static Void _0x1F8E00FB18239600(Any p0) { return _i<Void>(0x1F8E00FB18239600, p0); }
	static Void _0x1398582B7F72B3ED(Any p0) { return _i<Void>(0x1398582B7F72B3ED, p0); }
	static Any _0x8B4FFC790CA131EF(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0x8B4FFC790CA131EF, p0, p1, p2, p3); }
	static bool network_access_tunable_bool_hash_fail_val(uint32_t tunableContext, uint32_t tunableName, bool defaultValue) { return _i<bool>(0xC7420099936CE286, tunableContext, tunableName, defaultValue); }
	static bool network_set_this_script_marked(Any p0, bool p1, Any p2) { return _i<bool>(0xD1110739EEADB592, p0, p1, p2); }
	static Void network_unregister_networked_entity(Entity entity) { return _i<Void>(0x7368E683BB9038D6, entity); }
	static Void network_set_network_id_dynamic(int netID, bool toggle) { return _i<Void>(0x2B1813ABA29016C5, netID, toggle); }
	static Void _0xCD71A4ECAB22709E(Entity entity) { return _i<Void>(0xCD71A4ECAB22709E, entity); }
	static Any _0xB37E4E6A2388CA7B() { return _i<Any>(0xB37E4E6A2388CA7B); }
	static bool _0x4237E822315D8BA9() { return _i<bool>(0x4237E822315D8BA9); }
	static Void _0x58C21165F6545892(const char* p0, const char* p1, Any p2) { return _i<Void>(0x58C21165F6545892, p0, p1, p2); }
	static Player participant_id() { return _i<Player>(0x90986E8876CE0A83); }
	static int participant_id_to_int() { return _i<int>(0x57A3BDDAD8E5AA0A); }
	static bool _0xE26CCFF8094D8C74(Any p0) { return _i<bool>(0xE26CCFF8094D8C74, p0); }
	static Void _0x72D0706CD6CCDB58() { return _i<Void>(0x72D0706CD6CCDB58); }
	static Any _0x472841A026D26D8B() { return _i<Any>(0x472841A026D26D8B); }
	static Void _0x715135F4B82AC90D(Entity entity, Any p1) { return _i<Void>(0x715135F4B82AC90D, entity, p1); }
	static bool _0xA2F952104FC6DD4B(Any p0) { return _i<bool>(0xA2F952104FC6DD4B, p0); }
	static Void _0x42613035157E4208(Any p0) { return _i<Void>(0x42613035157E4208, p0); }
	static Void reserve_network_mission_objects(int p0) { return _i<Void>(0x4E5C93BD0C32FBF8, p0); }
	static Void reserve_network_mission_peds(int p0) { return _i<Void>(0xB60FEBA45333D36F, p0); }
	static Void reserve_network_mission_vehicles(int p0) { return _i<Void>(0x76B02E21ED27A469, p0); }
	static Void _0x17330EBF2F2124A8() { return _i<Void>(0x17330EBF2F2124A8); }
	static Void _0x444C4525ECE0A4B9() { return _i<Void>(0x444C4525ECE0A4B9); }
	static Void _0x4BA166079D658ED4(Any p0, Any p1) { return _i<Void>(0x4BA166079D658ED4, p0, p1); }
	static Void set_entity_locally_invisible(Entity entity) { return _i<Void>(0xE135A9FF3F5D05D8, entity); }
	static Void set_entity_locally_visible(Entity entity) { return _i<Void>(0x241E289B5C059EDC, entity); }
	static Void set_entity_visible_in_cutscene(Any p0, bool p1, bool p2) { return _i<Void>(0xE0031D3C8F36AB82, p0, p1, p2); }
	static Void _0x658500AE6D723A7E(Any p0) { return _i<Void>(0x658500AE6D723A7E, p0); }
	static Void _0xD7B6C73CAD419BCF(Any p0) { return _i<Void>(0xD7B6C73CAD419BCF, p0); }
	static Void _0xFAE628F1E9ADB239(Any p0, Any p1, Any p2) { return _i<Void>(0xFAE628F1E9ADB239, p0, p1, p2); }
	static Void use_player_colour_instead_of_team_colour(bool toggle, Any p1) { return _i<Void>(0x5FFE9B4144F9712F, toggle, p1); }
	static Void set_local_player_invisible_locally(bool p0) { return _i<Void>(0xE5F773C1A1D9D168, p0); }
	static Void set_local_player_visible_in_cutscene(bool p0, bool p1) { return _i<Void>(0xD1065D68947E7B6E, p0, p1); }
	static Void set_local_player_visible_locally(bool p0) { return _i<Void>(0x7619364C82D3BF14, p0); }
	static Void _0xAAA553E7DD28A457(bool p0) { return _i<Void>(0xAAA553E7DD28A457, p0); }
	static Void _0x838DA0936A24ED4D(Any p0, Any p1) { return _i<Void>(0x838DA0936A24ED4D, p0, p1); }
	static Void set_network_id_sync_to_player(int netId, Player player, bool toggle) { return _i<Void>(0xA8A024587329F36A, netId, player, toggle); }
	static Void set_network_id_can_migrate(int netId, bool toggle) { return _i<Void>(0x299EEB23175895FC, netId, toggle); }
	static Void set_network_id_exists_on_all_machines(int netId, bool toggle) { return _i<Void>(0xE05E81A888FA63C8, netId, toggle); }
	static Void _0x3FA36981311FA4FF(int netId, bool state) { return _i<Void>(0x3FA36981311FA4FF, netId, state); }
	static Void set_network_id_visible_in_cutscene(int netId, bool p1, bool p2) { return _i<Void>(0xA6928482543022B4, netId, p1, p2); }
	static Void _0x32EBD154CB6B8B99(Any p0, Any p1, Any p2) { return _i<Void>(0x32EBD154CB6B8B99, p0, p1, p2); }
	static Void set_network_vehicle_non_contact(Vehicle vehicle, bool toggle) { return _i<Void>(0x6274C4712850841E, vehicle, toggle); }
	static Void _0xA2A707979FE754DC(Any p0, Any p1) { return _i<Void>(0xA2A707979FE754DC, p0, p1); }
	static Void set_network_vehicle_respot_timer(int netId, int time, Any p2) { return _i<Void>(0xEC51713AB6EC36E8, netId, time, p2); }
	static Void _0x13F1FCB111B820B0(Any p0) { return _i<Void>(0x13F1FCB111B820B0, p0); }
	static Void set_player_invisible_locally(Player player, bool toggle) { return _i<Void>(0x12B37D54667DB0B8, player, toggle); }
	static Void set_player_visible_locally(Player player, bool toggle) { return _i<Void>(0xFAA10F1FAFB11AF2, player, toggle); }
	static Void _0xA7C511FA1C5BDA38(Any p0, Any p1) { return _i<Void>(0xA7C511FA1C5BDA38, p0, p1); }
	static Void set_store_enabled(bool toggle) { return _i<Void>(0x9641A9FF718E9C5E, toggle); }
	static Void shutdown_and_launch_single_player_game() { return _i<Void>(0x593850C16A36B692); }
	static Any _0x9ECA15ADFE141431() { return _i<Any>(0x9ECA15ADFE141431); }
	static const char* texture_download_get_name(int p0) { return _i<const char*>(0x3448505B6E35262D, p0); }
	static bool texture_download_has_failed(int p0) { return _i<bool>(0x5776ED562C134687, p0); }
	static Void texture_download_release(int p0) { return _i<Void>(0x487EB90B98E9FB19, p0); }
	static int texture_download_request(int* PlayerHandle, const char* FilePath, const char* Name, bool p3) { return _i<int>(0x16160DA74A8E74A2, PlayerHandle, FilePath, Name, p3); }
	static Any _0x0B203B4AFDE53A4F(Any* p0, Any* p1, bool p2) { return _i<Any>(0x0B203B4AFDE53A4F, p0, p1, p2); }
	static Any _0xF287F506767CC8A9(Player player, uint64_t unk) { return _i<Any>(0xF287F506767CC8A9, player, unk); }
	static bool _0x46FB3ED415C7641C(Player player, int p1, uint32_t scriptHash) { return _i<bool>(0x46FB3ED415C7641C, player, p1, scriptHash); }
	static Any _0xA12D3A5A3753CC23() { return _i<Any>(0xA12D3A5A3753CC23); }
	static Void _0xE9B99B6853181409() { return _i<Void>(0xE9B99B6853181409); }
	static Void _0x17440AA15D1D3739() { return _i<Void>(0x17440AA15D1D3739); }
	static Void _0xA1E5E0204A6FCC70() { return _i<Void>(0xA1E5E0204A6FCC70); }
	static Void _0x61A885D3F7CFEE9A() { return _i<Void>(0x61A885D3F7CFEE9A); }
	static Void _0xBA96394A0EECFA65() { return _i<Void>(0xBA96394A0EECFA65); }
	static bool _0x152D90E4C1B4738A(Any* p0, Any* p1) { return _i<bool>(0x152D90E4C1B4738A, p0, p1); }
	static Any _0x24E4E51FC16305F9() { return _i<Any>(0x24E4E51FC16305F9); }
	static bool _0x162C23CA83ED0A62(Any p0) { return _i<bool>(0x162C23CA83ED0A62, p0); }
	static Any _0x941E5306BCD7C2C7() { return _i<Any>(0x941E5306BCD7C2C7); }
	static Any _0x793FF272D5B365F4() { return _i<Any>(0x793FF272D5B365F4); }
	static Any _0x4D02279C83BE69FE() { return _i<Any>(0x4D02279C83BE69FE); }
	static bool _0xD5A4B59980401588(Any p0, Any p1, Any* p2, Any* p3) { return _i<bool>(0xD5A4B59980401588, p0, p1, p2, p3); }
	static Any _0x40F7E66472DF3E5C(Any p0, Any p1) { return _i<Any>(0x40F7E66472DF3E5C, p0, p1); }
	static int get_content_category(int p0) { return _i<int>(0xA7BAB11E7C9C6C5A, p0); }
	static bool _0x8C8D2739BA44AF0F(Any p0) { return _i<bool>(0x8C8D2739BA44AF0F, p0); }
	static bool _0x584770794D758C18(Any p0, Any* p1) { return _i<bool>(0x584770794D758C18, p0, p1); }
	static int get_content_description_hash(Any p0) { return _i<int>(0x7CF0448787B23758, p0); }
	static Any get_content_file_version(Any p0, Any p1) { return _i<Any>(0x37025B27D9B658B1, p0, p1); }
	static Any _0x3A17A27D75C74887() { return _i<Any>(0x3A17A27D75C74887); }
	static bool _0x7FCC39C46C3C03BD(Any p0) { return _i<bool>(0x7FCC39C46C3C03BD, p0); }
	static bool _0x1D610EB0FEA716D9(Any p0) { return _i<bool>(0x1D610EB0FEA716D9, p0); }
	static bool _0x993CBE59D350D225(Any p0) { return _i<bool>(0x993CBE59D350D225, p0); }
	static bool _0x70EA8DA57840F9BE(Any p0) { return _i<bool>(0x70EA8DA57840F9BE, p0); }
	static const char* get_content_id(Any p0) { return _i<const char*>(0x55AA95F481D694D2, p0); }
	static bool _0x3054F114121C21EA(Any p0) { return _i<bool>(0x3054F114121C21EA, p0); }
	static bool _0xAEAB987727C5A8A4(Any p0) { return _i<bool>(0xAEAB987727C5A8A4, p0); }
	static bool _0xA9240A96C74CCA13(Any p0) { return _i<bool>(0xA9240A96C74CCA13, p0); }
	static Any _0x32DD916F3F7C9672(Any p0) { return _i<Any>(0x32DD916F3F7C9672, p0); }
	static Any _0xBF09786A7FCAB582(Any p0) { return _i<Any>(0xBF09786A7FCAB582, p0); }
	static Any _0xE0A6138401BCB837() { return _i<Any>(0xE0A6138401BCB837); }
	static Any _0xBAF6BABF9E7CCC13(Any p0, Any p1) { return _i<Any>(0xBAF6BABF9E7CCC13, p0, p1); }
	static Any _0x1ACCFBA3D8DAB2EE(Any p0, Any p1) { return _i<Any>(0x1ACCFBA3D8DAB2EE, p0, p1); }
	static Any _0x759299C5BB31D2A9(Any p0, Any p1) { return _i<Any>(0x759299C5BB31D2A9, p0, p1); }
	static Any _0x4E548C0D7AE39FF9(Any p0, Any p1) { return _i<Any>(0x4E548C0D7AE39FF9, p0, p1); }
	static Any _0x87E5C46C187FE0AE(Any p0, Any p1) { return _i<Any>(0x87E5C46C187FE0AE, p0, p1); }
	static Any _0x769951E2455E2EB5() { return _i<Any>(0x769951E2455E2EB5); }
	static Void _0xCFD115B373C0DF63(Any p0, Any* p1) { return _i<Void>(0xCFD115B373C0DF63, p0, p1); }
	static const char* get_content_user_id(int p0) { return _i<const char*>(0xCD67AD041A394C9C, p0); }
	static Any _0x703F12425ECA8BF5(Any p0) { return _i<Any>(0x703F12425ECA8BF5, p0); }
	static Any _0xC55A0B40FFB1ED23() { return _i<Any>(0xC55A0B40FFB1ED23); }
	static Any _0xFBC5E768C7A77A6A() { return _i<Any>(0xFBC5E768C7A77A6A); }
	static bool _0xB746D20B17F2A229(Any* p0, Any* p1) { return _i<bool>(0xB746D20B17F2A229, p0, p1); }
	static Any _0x597F8DBA9B206FC7() { return _i<Any>(0x597F8DBA9B206FC7); }
	static bool _0x9F6E2821885CAEE2(Any p0, Any p1, Any p2, Any* p3, Any* p4) { return _i<bool>(0x9F6E2821885CAEE2, p0, p1, p2, p3, p4); }
	static bool _0xF9E1CCAE8BA4C281(Any p0, Any p1, Any* p2, Any* p3) { return _i<bool>(0xF9E1CCAE8BA4C281, p0, p1, p2, p3); }
	static bool _0x678BB03C1A3BD51E(Any p0, Any p1, Any p2, Any* p3, Any* p4) { return _i<bool>(0x678BB03C1A3BD51E, p0, p1, p2, p3, p4); }
	static bool set_balance_add_machine(Any* p0, Any* p1) { return _i<bool>(0x815E5E3073DA1D67, p0, p1); }
	static bool set_balance_add_machines(Any* p0, Any p1, Any* p2) { return _i<bool>(0xB8322EEB38BE7C26, p0, p1, p2); }
	static Any _0x5A0A3D1A186A5508() { return _i<Any>(0x5A0A3D1A186A5508); }
	static bool _0xA7862BC5ED1DFD7E(Any p0, Any p1, Any* p2, Any* p3) { return _i<bool>(0xA7862BC5ED1DFD7E, p0, p1, p2, p3); }
	static bool network_get_background_loading_recipients(Any p0, Any p1, Any* p2, Any* p3) { return _i<bool>(0x97A770BEEF227E2B, p0, p1, p2, p3); }
	static bool _0x3195F8DD0D531052(Any p0, Any p1, Any* p2, Any* p3) { return _i<bool>(0x3195F8DD0D531052, p0, p1, p2, p3); }
	static Any _0xEDF7F927136C224B() { return _i<Any>(0xEDF7F927136C224B); }
	static const char* get_root_content_id(Any p0) { return _i<const char*>(0xC0173D6BFF4E0348, p0); }
	static bool _0x5324A0E3E4CE3570(Any p0, Any p1, Any* p2, Any* p3) { return _i<bool>(0x5324A0E3E4CE3570, p0, p1, p2, p3); }
	static Any _0x5E24341A7F92A74B() { return _i<Any>(0x5E24341A7F92A74B); }
	static bool _0xEBFA8D50ADDC54C4(Any p0) { return _i<bool>(0xEBFA8D50ADDC54C4, p0); }
	static Any _0x02ADA21EA2F6918F() { return _i<Any>(0x02ADA21EA2F6918F); }
	static Any _0x299EF3C576773506() { return _i<Any>(0x299EF3C576773506); }
	static Any _0x63B406D7884BFA95() { return _i<Any>(0x63B406D7884BFA95); }
	static Any _0x9FEDF86898F100E9() { return _i<Any>(0x9FEDF86898F100E9); }
	static bool _0x2D5DC831176D0114(Any p0) { return _i<bool>(0x2D5DC831176D0114, p0); }
	static Any _0xD53ACDBEF24A46E8() { return _i<Any>(0xD53ACDBEF24A46E8); }
	static bool _0xF53E48461B71EECB(Any p0) { return _i<bool>(0xF53E48461B71EECB, p0); }
	static Any _0x45E816772E93A9DB() { return _i<Any>(0x45E816772E93A9DB); }
	static bool _0x5CAE833B0EE0C500(Any p0) { return _i<bool>(0x5CAE833B0EE0C500, p0); }
	static bool _0x1DE0F5F50D723CAA(Any* p0, Any* p1, Any* p2) { return _i<bool>(0x1DE0F5F50D723CAA, p0, p1, p2); }
	static bool _0x692D58DF40657E8C(Any p0, Any p1, Any p2, Any* p3, Any p4, bool p5) { return _i<bool>(0x692D58DF40657E8C, p0, p1, p2, p3, p4, p5); }
	static bool _0x158EC424F35EC469(Any* p0, bool p1, Any* p2) { return _i<bool>(0x158EC424F35EC469, p0, p1, p2); }
	static bool _0xC7397A83F7A2A462(Any* p0, Any p1, bool p2, Any* p3) { return _i<bool>(0xC7397A83F7A2A462, p0, p1, p2, p3); }
	static bool _0x6D4CB481FAC835E8(Any p0, Any p1, Any* p2, Any p3) { return _i<bool>(0x6D4CB481FAC835E8, p0, p1, p2, p3); }
	static bool _0x9BF438815F5D96EA(Any p0, Any p1, Any* p2, Any p3, Any p4, Any p5) { return _i<bool>(0x9BF438815F5D96EA, p0, p1, p2, p3, p4, p5); }
	static Void _0x68103E2247887242() { return _i<Void>(0x68103E2247887242); }
	static bool _0x5A34CD9C3C5BEC44(Any p0) { return _i<bool>(0x5A34CD9C3C5BEC44, p0); }
	static Any _0x5E0165278F6339EE(Any p0) { return _i<Any>(0x5E0165278F6339EE, p0); }
	static Any _0x171DF6A0C07FB3DC(Any p0, Any p1) { return _i<Any>(0x171DF6A0C07FB3DC, p0, p1); }
	static Any _0x7FD2990AF016795E(Any* p0, Any* p1, Any p2, Any p3, Any p4) { return _i<Any>(0x7FD2990AF016795E, p0, p1, p2, p3, p4); }
	static bool _0x274A1519DFC1094F(Any* p0, bool p1, Any* p2) { return _i<bool>(0x274A1519DFC1094F, p0, p1, p2); }
	static bool _0xD05D1A6C74DA3498(Any* p0, bool p1, Any* p2) { return _i<bool>(0xD05D1A6C74DA3498, p0, p1, p2); }
	static Void _0xF98DDE0A8ED09323(bool p0) { return _i<Void>(0xF98DDE0A8ED09323, p0); }
	static Void _0xFD75DABC0957BF33(bool p0) { return _i<Void>(0xFD75DABC0957BF33, p0); }
	static Any _0x308F96458B7087CC(Any* p0, Any p1, Any p2, Any p3, Any* p4, bool p5) { return _i<Any>(0x308F96458B7087CC, p0, p1, p2, p3, p4, p5); }
	static Any _0xC87E740D9F3872CC() { return _i<Any>(0xC87E740D9F3872CC); }
	static Void _0x77758139EC9B66C7(bool p0) { return _i<Void>(0x77758139EC9B66C7, p0); }
	static int network_get_network_id_from_entity(Entity entity) { return _i<int>(0xA11700682F3AD45C, entity); }
	static int veh_to_net(Vehicle vehicle) { return _i<int>(0xB4C94523F023419C, vehicle); }
	static int ped_to_net(Ped ped) { return _i<int>(0x0EDEC3C276198689, ped); }
	static int obj_to_net(Object object) { return _i<int>(0x99BFDC94A603E541, object); }
	static Void _0x4A9FDE3A5A6D0437(Any p0) { return _i<Void>(0x4A9FDE3A5A6D0437, p0); }
	static Void network_set_rich_presence(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x1DCCACDCFC569362, p0, p1, p2, p3); }
	static Void _0x3E200C2BCF4164EB(Any p0, Any p1) { return _i<Void>(0x3E200C2BCF4164EB, p0, p1); }
	static Void _0xB606E6CC59664972(Any p0) { return _i<Void>(0xB606E6CC59664972, p0); }
	static Void _0x966DD84FB6A46017() { return _i<Void>(0x966DD84FB6A46017); }
	static Void _0x6BFF5F84102DF80A(Any p0) { return _i<Void>(0x6BFF5F84102DF80A, p0); }
	static Void _0x5C497525F803486B() { return _i<Void>(0x5C497525F803486B); }
	static Any _0xAEDF1BC1C133D6E3() { return _i<Any>(0xAEDF1BC1C133D6E3); }
	static Any _0x2555CF7DA5473794() { return _i<Any>(0x2555CF7DA5473794); }
	static Any _0x6FD992C4A1C1B986() { return _i<Any>(0x6FD992C4A1C1B986); }

	static Void add_door_to_system(uint32_t doorHash, uint32_t modelHash, float x, float y, float z, bool p5, bool p6, bool p7) { return _i<Void>(0x6F8838D03D1DC226, doorHash, modelHash, x, y, z, p5, p6, p7); }
	static Void _0xAA059C615DE9DD03(Any p0, Any p1) { return _i<Void>(0xAA059C615DE9DD03, p0, p1); }
	static Void _0x641F272B52E2F0F8(Any p0, Any p1) { return _i<Void>(0x641F272B52E2F0F8, p0, p1); }
	static bool _0x85B6C850546FDDE2(Any p0, bool p1, bool p2, bool p3, Any p4) { return _i<bool>(0x85B6C850546FDDE2, p0, p1, p2, p3, p4); }
	static Void attach_portable_pickup_to_ped(Ped ped, Any p1) { return _i<Void>(0x8DC39368BDD57755, ped, p1); }
	static Void _0x1E3F1B1B891A2AAA(Any p0, Any p1) { return _i<Void>(0x1E3F1B1B891A2AAA, p0, p1); }
	static Void _0xE7E4C198B0185900(Object p0, Any p1, bool p2) { return _i<Void>(0xE7E4C198B0185900, p0, p1, p2); }
	static Void _0xA2C1F5E92AFE49ED() { return _i<Void>(0xA2C1F5E92AFE49ED); }
	static Void _0xDA05194260CDCDF9(Any p0, Any p1) { return _i<Void>(0xDA05194260CDCDF9, p0, p1); }
	static Void _0x190428512B240692(Any p0, bool p1, bool p2, bool p3, bool p4) { return _i<Void>(0x190428512B240692, p0, p1, p2, p3, p4); }
	static Void _0x762DB2D380B48D04(Any p0) { return _i<Void>(0x762DB2D380B48D04, p0); }
	static Void _0x701FDA1E82076BA4() { return _i<Void>(0x701FDA1E82076BA4); }
	static Void _0x66A49D021870FE88() { return _i<Void>(0x66A49D021870FE88); }
	static uint32_t get_pickup_hash(Pickup pickupHash) { return _i<uint32_t>(0x5EAAD83F8CFB4575, pickupHash); }
	static Pickup create_ambient_pickup(uint32_t pickupHash, float posX, float posY, float posZ, int p4, int value, uint32_t modelHash, bool p7, bool p8) { return _i<Pickup>(0x673966A0C0FD7171, pickupHash, posX, posY, posZ, p4, value, modelHash, p7, p8); }
	static Void create_money_pickups(float x, float y, float z, int value, int amount, uint32_t model) { return _i<Void>(0x0589B5E791CE9B2B, x, y, z, value, amount, model); }
	static Pickup create_portable_pickup2(uint32_t pickupHash, float x, float y, float z, bool placeOnGround, uint32_t modelHash) { return _i<Pickup>(0x125494B98A21AAF7, pickupHash, x, y, z, placeOnGround, modelHash); }
	static Object create_object(uint32_t modelHash, float x, float y, float z, bool isNetwork, bool p5, bool dynamic) { return _i<Object>(0x509D5878EB39E842, modelHash, x, y, z, isNetwork, p5, dynamic); }
	static Object create_object_no_offset(uint32_t modelHash, float x, float y, float z, bool isNetwork, bool p5, bool dynamic) { return _i<Object>(0x9A294B2138ABB884, modelHash, x, y, z, isNetwork, p5, dynamic); }
	static Pickup create_pickup(uint32_t pickupHash, float posX, float posY, float posZ, int p4, int value, bool p6, uint32_t modelHash) { return _i<Pickup>(0xFBA08C503DD5FA58, pickupHash, posX, posY, posZ, p4, value, p6, modelHash); }
	static Pickup create_pickup_rotate(uint32_t pickupHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, int flag, int amount, Any p9, bool p10, uint32_t modelHash) { return _i<Pickup>(0x891804727E0A98B7, pickupHash, posX, posY, posZ, rotX, rotY, rotZ, flag, amount, p9, p10, modelHash); }
	static Pickup create_portable_pickup(uint32_t pickupHash, float x, float y, float z, bool placeOnGround, uint32_t modelHash) { return _i<Pickup>(0x2EAF1FDB2FB55698, pickupHash, x, y, z, placeOnGround, modelHash); }
	static Void _0xE05F6AEEFEB0BB02(Any p0, Any p1, Any p2) { return _i<Void>(0xE05F6AEEFEB0BB02, p0, p1, p2); }
	static Void delete_object(Object* object) { return _i<Void>(0x539E0AE3E6634B9F, object); }
	static Void detach_portable_pickup_from_ped(Ped ped) { return _i<Void>(0xCF463D1E9A0AECB1, ped); }
	static bool does_object_of_type_exist_at_coords(float x, float y, float z, float radius, uint32_t hash, bool p5) { return _i<bool>(0xBFA48E2FF417213F, x, y, z, radius, hash, p5); }
	static bool does_pickup_exist(Pickup pickup) { return _i<bool>(0xAFC1CA75AD4074D1, pickup); }
	static bool does_pickup_object_exist(Object pickupObject) { return _i<bool>(0xD9EFB6DBF7DAAEA3, pickupObject); }
	static bool is_pickup_within_radius(uint32_t pickupHash, float x, float y, float z, float radius) { return _i<bool>(0xF9C36251F6E48E33, pickupHash, x, y, z, radius); }
	static bool does_des_object_exist(int handle) { return _i<bool>(0x52AF537A0C5B8AAD, handle); }
	static bool _0x589F80B325CC82C5(float p0, float p1, float p2, Any p3, Any* p4) { return _i<bool>(0x589F80B325CC82C5, p0, p1, p2, p3, p4); }
	static int _0x4BC2854478F3A749(uint32_t doorHash) { return _i<int>(0x4BC2854478F3A749, doorHash); }
	static int _0x160AA1B32F6139B8(uint32_t doorHash) { return _i<int>(0x160AA1B32F6139B8, doorHash); }
	static bool _0xDF97CDD4FC08FD34(Any p0) { return _i<bool>(0xDF97CDD4FC08FD34, p0); }
	static float _0x65499865FCA6E5EC(uint32_t doorHash) { return _i<float>(0x65499865FCA6E5EC, doorHash); }
	static Void _0x9BA001CB45CBF627(uint32_t doorHash, float heading, bool p2, bool p3) { return _i<Void>(0x9BA001CB45CBF627, doorHash, heading, p2, p3); }
	static Void _0x03C27E13B42A0E82(uint32_t doorHash, float p1, bool p2, bool p3) { return _i<Void>(0x03C27E13B42A0E82, doorHash, p1, p2, p3); }
	static Void _0xA85A21582451E951(uint32_t doorHash, bool p1) { return _i<Void>(0xA85A21582451E951, doorHash, p1); }
	static Void set_door_acceleration_limit(uint32_t doorHash, int limit, bool p2, bool p3) { return _i<Void>(0x6BAB9442830C7F53, doorHash, limit, p2, p3); }
	static Void _0xD9B71952F78A2640(uint32_t doorHash, bool p1) { return _i<Void>(0xD9B71952F78A2640, doorHash, p1); }
	static Void set_door_ajar_angle(uint32_t doorHash, float ajar, bool p2, bool p3) { return _i<Void>(0xB6E6FBA95C7324AC, doorHash, ajar, p2, p3); }
	static Void _0xC485E07E4F0B7958(uint32_t doorHash, bool p1, bool p2, bool p3) { return _i<Void>(0xC485E07E4F0B7958, doorHash, p1, p2, p3); }
	static Void _0xF2E1A7133DD356A6(uint32_t hash, bool toggle) { return _i<Void>(0xF2E1A7133DD356A6, hash, toggle); }
	static Void _0xF9C1681347C8BD15(Object object) { return _i<Void>(0xF9C1681347C8BD15, object); }
	static Void _0x4C134B4DF76025D0(Any p0, Any p1) { return _i<Void>(0x4C134B4DF76025D0, p0, p1); }
	static Void _0x758A5C1B3B1E1990(Any p0) { return _i<Void>(0x758A5C1B3B1E1990, p0); }
	static Void _0x394CD08E31313C28() { return _i<Void>(0x394CD08E31313C28); }
	static Object get_closest_object_of_type(float x, float y, float z, float radius, uint32_t modelHash, bool isMission, bool p6, bool p7) { return _i<Object>(0xE143FA2249364369, x, y, z, radius, modelHash, isMission, p6, p7); }
	static Any _0x163F8B586BC95F2A(Any coords, float radius, uint32_t modelHash, float x, float y, float z, math::vector3<float>* p6, int p7) { return _i<Any>(0x163F8B586BC95F2A, coords, radius, modelHash, x, y, z, p6, p7); }
	static Any _0xDB41D07A45A6D4B7(Any p0) { return _i<Any>(0xDB41D07A45A6D4B7, p0); }
	static Any _0x2542269291C6AC84(Any p0) { return _i<Any>(0x2542269291C6AC84, p0); }
	static float get_object_fragment_damage_health(Any p0, bool p1) { return _i<float>(0xB6FBFD079B8D0596, p0, p1); }
	static Any _0xE84EB93729C5F36A(Any p0) { return _i<Any>(0xE84EB93729C5F36A, p0); }
	static math::vector3<float> get_object_offset_from_coords(float xPos, float yPos, float zPos, float heading, float xOffset, float yOffset, float zOffset) { return _i<math::vector3<float>>(0x163E252DE035A133, xPos, yPos, zPos, heading, xOffset, yOffset, zOffset); }
	static math::vector3<float> get_pickup_coords(Pickup pickup) { return _i<math::vector3<float>>(0x225B8B35C88029B3, pickup); }
	static Any _0xB3ECA65C7317F174() { return _i<Any>(0xB3ECA65C7317F174); }
	static Object get_pickup_object(Pickup pickup) { return _i<Object>(0x5099BC55630B25AE, pickup); }
	static int get_des_object(float x, float y, float z, float rotation, const char* name) { return _i<int>(0xB48FCED898292E52, x, y, z, rotation, name); }
	static float _0x260EE4FDBDF4DB01(Any p0) { return _i<float>(0x260EE4FDBDF4DB01, p0); }
	static math::vector3<float> get_safe_pickup_coords(float x, float y, float z, Any p3, Any p4) { return _i<math::vector3<float>>(0x6E16BC2503FF1FF0, x, y, z, p3, p4); }
	static Void get_state_of_closest_door_of_type(uint32_t type, float x, float y, float z, bool* locked, float* heading) { return _i<Void>(0xEDC1A5B84AEF33FF, type, x, y, z, locked, heading); }
	static Any get_des_object_state(int handle) { return _i<Any>(0x899BA936634A322E, handle); }
	static uint32_t get_weapon_hash_from_pickup(Pickup pickupHash) { return _i<uint32_t>(0x08F96CA6C551AD51, pickupHash); }
	static bool has_closest_object_of_type_been_broken(float p0, float p1, float p2, float p3, uint32_t modelHash, Any p5) { return _i<bool>(0x761B0E69AC4D007E, p0, p1, p2, p3, modelHash, p5); }
	static bool _0x46494A2475701343(float p0, float p1, float p2, float p3, uint32_t modelHash, bool p5) { return _i<bool>(0x46494A2475701343, p0, p1, p2, p3, modelHash, p5); }
	static bool has_object_been_broken(Object object) { return _i<bool>(0x8ABFB70C49CC43E2, object); }
	static bool has_pickup_been_collected(Pickup pickup) { return _i<bool>(0x80EC48E6679313F9, pickup); }
	static Void _0x867458251D47CCB2(Any p0, Any p1) { return _i<Void>(0x867458251D47CCB2, p0, p1); }
	static bool _0x673ED815D6E323B7(Any p0, bool p1, bool p2, bool p3, Any p4) { return _i<bool>(0x673ED815D6E323B7, p0, p1, p2, p3, p4); }
	static bool is_any_object_near_point(float x, float y, float z, float range, bool p4) { return _i<bool>(0x397DC58FF00298D1, x, y, z, range, p4); }
	static bool is_door_closed(uint32_t door) { return _i<bool>(0xC531EE8A1145A149, door); }
	static bool does_door_exist(uint32_t doorHash) { return _i<bool>(0xC153C43EA202C8C1, doorHash); }
	static bool is_garage_empty(Any garage, bool p1, int p2) { return _i<bool>(0x90E47239EA1980B8, garage, p1, p2); }
	static bool _0x0378C08504160D0D(Any p0) { return _i<bool>(0x0378C08504160D0D, p0); }
	static bool _0x372EF6699146A1E4(Any p0, Entity entity, float p2, int p3) { return _i<bool>(0x372EF6699146A1E4, p0, entity, p2, p3); }
	static bool is_object_near_point(uint32_t objectHash, float x, float y, float z, float range) { return _i<bool>(0x8C90FE4B381BA60A, objectHash, x, y, z, range); }
	static bool _0xF0EED5A6BC7B237A(Any p0, Entity entity, int p2) { return _i<bool>(0xF0EED5A6BC7B237A, p0, entity, p2); }
	static bool is_object_visible(Object object) { return _i<bool>(0x8B32ACE6326A7546, object); }
	static bool _0x11D1E53A726891FE(Object object) { return _i<bool>(0x11D1E53A726891FE, object); }
	static bool _0x024A60DEB0EA69F0(Any p0, Player player, float p2, int p3) { return _i<bool>(0x024A60DEB0EA69F0, p0, player, p2, p3); }
	static bool _0x1761DC5D8471CBAA(Any p0, Player player, int p2) { return _i<bool>(0x1761DC5D8471CBAA, p0, player, p2); }
	static bool is_point_in_angled_area(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, bool p10, bool p11) { return _i<bool>(0x2A70BAE8883E4C81, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static Void mark_object_for_deletion(Object object) { return _i<Void>(0xADBE4809F19F927A, object); }
	static Void _0xC7F29CA00F46350E(bool p0) { return _i<Void>(0xC7F29CA00F46350E, p0); }
	static Any _0xD76EEEF746057FD6(Any p0) { return _i<Any>(0xD76EEEF746057FD6, p0); }
	static bool place_object_on_ground_properly(Object object) { return _i<bool>(0x58A850EAEE20FAA3, object); }
	static Void _0x92AEFB5F6E294023(Object object, bool p1, bool p2) { return _i<Void>(0x92AEFB5F6E294023, object, p1, p2); }
	static Void remove_all_pickups_of_type(uint32_t pickupHash) { return _i<Void>(0x27F9D613092159CF, pickupHash); }
	static Void remove_door_from_system(uint32_t doorHash) { return _i<Void>(0x464D8E1427156FE4, doorHash); }
	static Void _0x4A39DB43E47CF3AA(Any p0) { return _i<Void>(0x4A39DB43E47CF3AA, p0); }
	static Void remove_pickup(Pickup pickup) { return _i<Void>(0x3288D8ACAECD2AB2, pickup); }
	static Void highlight_placement_coords(float x, float y, float z, int colorIndex) { return _i<Void>(0x3430676B11CDF21D, x, y, z, colorIndex); }
	static Void set_activate_object_physics_as_soon_as_it_is_unfrozen(Object object, bool toggle) { return _i<Void>(0x406137F8EF90EAF5, object, toggle); }
	static Void _0x826D1EE4D1CAFC78(Any p0, Any p1) { return _i<Void>(0x826D1EE4D1CAFC78, p0, p1); }
	static Void _0xBCE595371A5FBAAF(Any p0, bool p1) { return _i<Void>(0xBCE595371A5FBAAF, p0, p1); }
	static Void _0x8CAAB2BD3EA58BD4(Any p0) { return _i<Void>(0x8CAAB2BD3EA58BD4, p0); }
	static Void _0xB2D0BDE54F0E8E5A(Object object, bool toggle) { return _i<Void>(0xB2D0BDE54F0E8E5A, object, toggle); }
	static Void _0xD05A3241B9A86F19(Any p0, Any p1) { return _i<Void>(0xD05A3241B9A86F19, p0, p1); }
	static Void set_force_object_this_frame(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xF538081986E49E9D, p0, p1, p2, p3); }
	static Void _0x78857FC65CADB909(bool p0) { return _i<Void>(0x78857FC65CADB909, p0); }
	static Void _0x88EAEC617CD26926(uint32_t p0, bool p1) { return _i<Void>(0x88EAEC617CD26926, p0, p1); }
	static Void door_control(uint32_t doorHash, float x, float y, float z, bool locked, float p5, float p6, float p7) { return _i<Void>(0x9B12F9A24FABEDB0, doorHash, x, y, z, locked, p5, p6, p7); }
	static Void _0x0BF3B3BD47D79C08(Any p0, int p1) { return _i<Void>(0x0BF3B3BD47D79C08, p0, p1); }
	static Void _0x4D89D607CB3DD1D2(Object object, bool toggle) { return _i<Void>(0x4D89D607CB3DD1D2, object, toggle); }
	static Void _0x77F33F2CCF64B3AA(Object object, bool p1) { return _i<Void>(0x77F33F2CCF64B3AA, object, p1); }
	static Void _0x62454A641B41F3C5(Any p0) { return _i<Void>(0x62454A641B41F3C5, p0); }
	static Void _0xC6033D32241F6FB5(Any p0, bool p1) { return _i<Void>(0xC6033D32241F6FB5, p0, p1); }
	static Void _0x3B2FD68DB5F8331C(Any p0, Any p1) { return _i<Void>(0x3B2FD68DB5F8331C, p0, p1); }
	static Void set_object_physics_params(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy) { return _i<Void>(0xF6DF6E90DE7DF90F, object, weight, p2, p3, p4, p5, gravity, p7, p8, p9, p10, buoyancy); }
	static Void _0x96EE0EBA0163DF80(Any p0, Any p1) { return _i<Void>(0x96EE0EBA0163DF80, p0, p1); }
	static Void _0xDF6CA0330F2E737B(Any p0, Any p1) { return _i<Void>(0xDF6CA0330F2E737B, p0, p1); }
	static Void _0xEB6F1A9B5510A5D2(Any p0, bool p1) { return _i<Void>(0xEB6F1A9B5510A5D2, p0, p1); }
	static Void set_object_targettable(Object object, bool targettable) { return _i<Void>(0x8A7391690F5AFD81, object, targettable); }
	static Void set_object_texture_variant(Object object, int paintIndex) { return _i<Void>(0x971DA0055324D033, object, paintIndex); }
	static Void _0x31F924B53EADDF65(bool p0) { return _i<Void>(0x31F924B53EADDF65, p0); }
	static Void _0x318516E02DE3ECE2(float p0) { return _i<Void>(0x318516E02DE3ECE2, p0); }
	static Void _0x0596843B34B95CE5(Any p0, Any p1) { return _i<Void>(0x0596843B34B95CE5, p0, p1); }
	static Void _0x3ED2B83AB2E82799(Any p0, Any p1) { return _i<Void>(0x3ED2B83AB2E82799, p0, p1); }
	static Void _0x8881C98A31117998(Any p0) { return _i<Void>(0x8881C98A31117998, p0); }
	static Void _0x39A5FB7EAF150840(Any p0, Any p1) { return _i<Void>(0x39A5FB7EAF150840, p0, p1); }
	static Void _0xA08FE5E49BDC39DD(Any p0, float p1, bool p2) { return _i<Void>(0xA08FE5E49BDC39DD, p0, p1, p2); }
	static Void _0xA90E7227A9303FA9(Any p0, Any p1) { return _i<Void>(0xA90E7227A9303FA9, p0, p1); }
	static Void set_pickup_regeneration_time(Pickup pickup, int time) { return _i<Void>(0x78015C9B4B3ECC9D, pickup, time); }
	static Void _0x858EC9FD25DE04AA(Any p0, Any p1) { return _i<Void>(0x858EC9FD25DE04AA, p0, p1); }
	static Void _0x1C1B69FAE509BA97(Any p0, Any p1) { return _i<Void>(0x1C1B69FAE509BA97, p0, p1); }
	static Void _0x616093EC6B139DD9(Player player, uint32_t pickupHash, bool p2) { return _i<Void>(0x616093EC6B139DD9, player, pickupHash, p2); }
	static Void _0x46F3ADD1E2D5BAF2(Any p0, Any p1) { return _i<Void>(0x46F3ADD1E2D5BAF2, p0, p1); }
	static Void set_state_of_closest_door_of_type(uint32_t type, float x, float y, float z, bool locked, float heading, bool p6) { return _i<Void>(0xF82D8F1926A02C3D, type, x, y, z, locked, heading, p6); }
	static Void set_des_object_state(int handle, int state) { return _i<Void>(0x5C29F698D404C5E1, handle, state); }
	static Void set_team_pickup_object(Object object, Any p1, bool p2) { return _i<Void>(0x53E0DF1A2A3CF0CA, object, p1, p2); }
	static Any _0xF12E33034D887F66(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Any>(0xF12E33034D887F66, p0, p1, p2, p3, p4, p5); }
	static bool slide_object(Object object, float toX, float toY, float toZ, float speedX, float speedY, float speedZ, bool collision) { return _i<bool>(0x2FDFF4107B8C1147, object, toX, toY, toZ, speedX, speedY, speedZ, collision); }
	static Void _0xF92099527DB8E2A7(Any p0, Any p1) { return _i<Void>(0xF92099527DB8E2A7, p0, p1); }
	static Void _0x8DCA505A5C196F05(Any p0, Any p1) { return _i<Void>(0x8DCA505A5C196F05, p0, p1); }
	static Void track_object_visibility(Any p0) { return _i<Void>(0xB252BC036B525623, p0); }

	static Void disable_input_group(int inputGroup) { return _i<Void>(0x7F4724035FDCA1DD, inputGroup); }
	static Void _0xCB0360EFEFB2580D(Any p0) { return _i<Void>(0xCB0360EFEFB2580D, p0); }
	static Void _0xA0CEFCEA390AAB9B(Any p0) { return _i<Void>(0xA0CEFCEA390AAB9B, p0); }
	static Void disable_all_control_actions(int inputGroup) { return _i<Void>(0x5F4B6931816E599B, inputGroup); }
	static Void disable_control_action(int inputGroup, int control, bool disable) { return _i<Void>(0xFE99B66D079CF6BC, inputGroup, control, disable); }
	static Void enable_all_control_actions(int inputGroup) { return _i<Void>(0xA5FFE9B05F199DE7, inputGroup); }
	static Void enable_control_action(int inputGroup, int control, bool enable) { return _i<Void>(0x351220255D64C155, inputGroup, control, enable); }
	static bool _0xFC859E2374407556() { return _i<bool>(0xFC859E2374407556); }
	static const char* _0x80C2FD58D720C801(int inputGroup, int control, bool p2) { return _i<const char*>(0x80C2FD58D720C801, inputGroup, control, p2); }
	static int _0xD7D22F5592AED8BA(int p0) { return _i<int>(0xD7D22F5592AED8BA, p0); }
	static const char* get_control_instructional_button(int inputGroup, int control, bool p2) { return _i<const char*>(0x499D7B09FC9B407, inputGroup, control, p2); }
	static float get_control_normal(int inputGroup, int control) { return _i<float>(0xEC3C9B8D5327B563, inputGroup, control); }
	static float _0x5B84D09CEC5209C5(int inputGroup, int control) { return _i<float>(0x5B84D09CEC5209C5, inputGroup, control); }
	static int get_control_value(int inputGroup, int control) { return _i<int>(0xD95E79E8686D2C27, inputGroup, control); }
	static float get_disabled_control_normal(int inputGroup, int control) { return _i<float>(0x11E65974A982637C, inputGroup, control); }
	static float _0x4F8A26A890FD62FB(int inputGroup, int control) { return _i<float>(0x4F8A26A890FD62FB, inputGroup, control); }
	static bool _0x0F70731BACCFBB96() { return _i<bool>(0x0F70731BACCFBB96); }
	static int get_local_player_aim_state() { return _i<int>(0xBB41AFBBBC0A0287); }
	static Any _0x59B9A7AF4C95133C() { return _i<Any>(0x59B9A7AF4C95133C); }
	static bool _0x6CD79468A1E595C6(int inputGroup) { return _i<bool>(0x6CD79468A1E595C6, inputGroup); }
	static bool is_control_enabled(int inputGroup, int control) { return _i<bool>(0x1CEA6BFDF248E5D9, inputGroup, control); }
	static bool is_control_just_pressed(int inputGroup, int control) { return _i<bool>(0x580417101DDB492F, inputGroup, control); }
	static bool is_control_just_released(int inputGroup, int control) { return _i<bool>(0x50F940259D3841E6, inputGroup, control); }
	static bool is_control_pressed(int inputGroup, int control) { return _i<bool>(0xF3A21BCD95725A4A, inputGroup, control); }
	static bool is_control_released(int inputGroup, int control) { return _i<bool>(0x648EE3E7F38877DD, inputGroup, control); }
	static bool is_disabled_control_just_pressed(int inputGroup, int control) { return _i<bool>(0x91AEF906BCA88877, inputGroup, control); }
	static bool is_disabled_control_just_released(int inputGroup, int control) { return _i<bool>(0x305C8DCD79DA8B0F, inputGroup, control); }
	static bool is_disabled_control_pressed(int inputGroup, int control) { return _i<bool>(0xE2587F8CBBD87B1D, inputGroup, control); }
	static Any _0xFB6C4072E9A32E92(Any p0, Any p1) { return _i<Any>(0xFB6C4072E9A32E92, p0, p1); }
	static bool is_look_inverted() { return _i<bool>(0x77B612531280010D); }
	static bool _0xE1615EC03B3BB4FD() { return _i<bool>(0xE1615EC03B3BB4FD); }
	static bool is_input_just_disabled(int inputGroup) { return _i<bool>(0x13337B38DB572509, inputGroup); }
	static bool is_input_disabled(int inputGroup) { return _i<bool>(0xA571D46727E2B718, inputGroup); }
	static bool _0x23F09EADC01449D6(bool p0) { return _i<bool>(0x23F09EADC01449D6, p0); }
	static Void _0x8290252FFF36ACB5(int p0, int red, int green, int blue) { return _i<Void>(0x8290252FFF36ACB5, p0, red, green, blue); }
	static Void set_pad_shake(int p0, int duration, int frequency) { return _i<Void>(0x48B3886C1358D0D5, p0, duration, frequency); }
	static Void _0xF239400E16C23E08(Any p0, Any p1) { return _i<Void>(0xF239400E16C23E08, p0, p1); }
	static bool set_control_normal(int inputGroup, int control, float amount) { return _i<bool>(0xE8A25867FBA3B05E, inputGroup, control, amount); }
	static bool set_cursor_location(float x, float y) { return _i<bool>(0xFC695459D4D0E219, x, y); }
	static Void set_input_exclusive(int inputGroup, int control) { return _i<Void>(0xEDE476E5EE29EDB1, inputGroup, control); }
	static Void set_playerpad_shakes_when_controller_disabled(bool toggle) { return _i<Void>(0x798FDEB5B1575088, toggle); }
	static Void _0x5B73C77D9EB66E24(bool p0) { return _i<Void>(0x5B73C77D9EB66E24, p0); }
	static Void _0x643ED62D5EA3BEBD() { return _i<Void>(0x643ED62D5EA3BEBD); }
	static Void stop_pad_shake(Any p0) { return _i<Void>(0x38C16A305E8CDC8D, p0); }
	static bool _0x3D42B92563939375(const char* p0) { return _i<bool>(0x3D42B92563939375, p0); }
	static bool _0x4683149ED1DDE7A1(const char* p0) { return _i<bool>(0x4683149ED1DDE7A1, p0); }
	static Void _0x14D29BB12D47F68C(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x14D29BB12D47F68C, p0, p1, p2, p3, p4); }

	static Any add_navmesh_blocking_object(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, Any p8) { return _i<Any>(0xFCD5C8E06E502F5A, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Void add_navmesh_required_region(float x, float y, float radius) { return _i<Void>(0x387EAD7EE42F6685, x, y, radius); }
	static Void _0xAA76052DDA9BFC3E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0xAA76052DDA9BFC3E, p0, p1, p2, p3, p4, p5, p6); }
	static bool are_all_navmesh_regions_loaded() { return _i<bool>(0x8415D95B194A3AEA); }
	static bool _0xF7B79A50B905A30D(float p0, float p1, float p2, float p3) { return _i<bool>(0xF7B79A50B905A30D, p0, p1, p2, p3); }
	static float calculate_travel_distance_between_points(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<float>(0xADD95C7005C4A197, x1, y1, z1, x2, y2, z2); }
	static Void _0x2801D0012266DF07(Any p0) { return _i<Void>(0x2801D0012266DF07, p0); }
	static Void disable_navmesh_in_area(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x4C8872D8CDBE1B8B, p0, p1, p2, p3, p4, p5, p6); }
	static bool does_navmesh_blocking_object_exist(Any p0) { return _i<bool>(0x0EAEB0DB4B132399, p0); }
	static int generate_directions_to_coord(float x, float y, float z, bool p3, float* direction, float* p5, float* distToNxJunction) { return _i<int>(0xF90125F1F79ECDF8, x, y, z, p3, direction, p5, distToNxJunction); }
	static float _0x3599D741C9AC6310(float p0, float p1, float p2, float p3) { return _i<float>(0x3599D741C9AC6310, p0, p1, p2, p3); }
	static float _0x336511A34F2E5185(float left, float right) { return _i<float>(0x336511A34F2E5185, left, right); }
	static float _0x8ABE8608576D9CE3(float p0, float p1, float p2, float p3) { return _i<float>(0x8ABE8608576D9CE3, p0, p1, p2, p3); }
	static float _0x29C24BFBED8AB8FB(float p0, float p1) { return _i<float>(0x29C24BFBED8AB8FB, p0, p1); }
	static bool get_closest_major_vehicle_node(float x, float y, float z, math::vector3<float>* outPosition, float unknown1, int unknown2) { return _i<bool>(0x2EABE3B06F58C1BE, x, y, z, outPosition, unknown1, unknown2); }
	static Any get_closest_road(float x, float y, float z, float p3, int p4, math::vector3<float>* p5, math::vector3<float>* p6, Any* p7, Any* p8, float* p9, bool p10) { return _i<Any>(0x132F52BBA570FE92, x, y, z, p3, p4, p5, p6, p7, p8, p9, p10); }
	static bool get_closest_vehicle_node(float x, float y, float z, math::vector3<float>* outPosition, int nodeType, float p5, float p6) { return _i<bool>(0x240A18690AE96513, x, y, z, outPosition, nodeType, p5, p6); }
	static bool get_closest_vehicle_node_with_heading(float x, float y, float z, math::vector3<float>* outPosition, float* outHeading, int nodeType, float p6, int p7) { return _i<bool>(0xFF071FB798B803B0, x, y, z, outPosition, outHeading, nodeType, p6, p7); }
	static Any _0x869DAACBBE9FA006() { return _i<Any>(0x869DAACBBE9FA006); }
	static Any _0xBBB45C3CF5C8AA85() { return _i<Any>(0xBBB45C3CF5C8AA85); }
	static Any _0xD3A6A0EF48823A8C() { return _i<Any>(0xD3A6A0EF48823A8C); }
	static bool get_nth_closest_vehicle_node(float x, float y, float z, int nthClosest, math::vector3<float>* outPosition, Any unknown1, Any unknown2, Any unknown3) { return _i<bool>(0xE50E52416CCF948B, x, y, z, nthClosest, outPosition, unknown1, unknown2, unknown3); }
	static bool get_nth_closest_vehicle_node_favour_direction(float x, float y, float z, float desiredX, float desiredY, float desiredZ, int nthClosest, math::vector3<float>* outPosition, float* outHeading, int nodetype, Any p10, Any p11) { return _i<bool>(0x45905BE8654AE067, x, y, z, desiredX, desiredY, desiredZ, nthClosest, outPosition, outHeading, nodetype, p10, p11); }
	static int get_nth_closest_vehicle_node_id(float x, float y, float z, int nth, int nodetype, float p5, float p6) { return _i<int>(0x22D7275A79FE8215, x, y, z, nth, nodetype, p5, p6); }
	static Any get_nth_closest_vehicle_node_id_with_heading(float x, float y, float z, int nthClosest, math::vector3<float>* outPosition, float outHeading, Any p6, float p7, float p8) { return _i<Any>(0x6448050E9C2A7207, x, y, z, nthClosest, outPosition, outHeading, p6, p7, p8); }
	static bool get_nth_closest_vehicle_node_with_heading(float x, float y, float z, int nthClosest, math::vector3<float>* outPosition, float* heading, Any* unknown1, int unknown2, float unknown3, float unknown4) { return _i<bool>(0x80CA6A8B6C094CC4, x, y, z, nthClosest, outPosition, heading, unknown1, unknown2, unknown3, unknown4); }
	static Any _0x01708E8DD3FF8C65(float p0, float p1, float p2, float p3, float p4, float p5) { return _i<Any>(0x01708E8DD3FF8C65, p0, p1, p2, p3, p4, p5); }
	static Any _0x16F46FB18C8009E4(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Any>(0x16F46FB18C8009E4, p0, p1, p2, p3, p4); }
	static Any _0xF3162836C28F9DA5(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xF3162836C28F9DA5, p0, p1, p2, p3); }
	static bool get_random_vehicle_node(float x, float y, float z, float radius, bool p4, bool p5, bool p6, math::vector3<float>* outPosition, int* nodeId) { return _i<bool>(0x93E0DB8440B73A7D, x, y, z, radius, p4, p5, p6, outPosition, nodeId); }
	static Any _0xA0F8A7517A273C05(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Any>(0xA0F8A7517A273C05, p0, p1, p2, p3, p4); }
	static bool get_safe_coord_for_ped(float x, float y, float z, bool onGround, math::vector3<float>* outPosition, int flags) { return _i<bool>(0xB61C8E878A4199CA, x, y, z, onGround, outPosition, flags); }
	static Void get_street_name_at_coord(float x, float y, float z, uint32_t* streetName, uint32_t* crossingRoad) { return _i<Void>(0x2EB41072B4C1E4C0, x, y, z, streetName, crossingRoad); }
	static bool get_supports_gps_route_flag(int nodeID) { return _i<bool>(0xA2AE5C478B96E3B6, nodeID); }
	static bool get_is_slow_road_flag(int nodeID) { return _i<bool>(0x4F5070AA58F69279, nodeID); }
	static Void get_vehicle_node_position(int nodeId, math::vector3<float>* outPosition) { return _i<Void>(0x703123E5E7D429C2, nodeId, outPosition); }
	static bool get_vehicle_node_properties(float x, float y, float z, int* density, int* flags) { return _i<bool>(0x0568566ACBB5DEDC, x, y, z, density, flags); }
	static bool is_navmesh_loaded_in_area(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<bool>(0xF813C7E63F9062A5, x1, y1, z1, x2, y2, z2); }
	static Any _0x705A844002B39DC0() { return _i<Any>(0x705A844002B39DC0); }
	static bool is_point_on_road(float x, float y, float z, Vehicle vehicle) { return _i<bool>(0x125BF4ABFC536B09, x, y, z, vehicle); }
	static bool is_vehicle_node_id_valid(int vehicleNodeId) { return _i<bool>(0x1EAF30FCFBF5AF74, vehicleNodeId); }
	static Void remove_navmesh_blocking_object(Any p0) { return _i<Void>(0x46399A7895957C0E, p0); }
	static Void remove_navmesh_required_regions() { return _i<Void>(0x916F0A3CDEC3445E); }
	static bool _0x07FB139B592FA687(float p0, float p1, float p2, float p3) { return _i<bool>(0x07FB139B592FA687, p0, p1, p2, p3); }
	static Void _0x228E5C6AD4D74BFD(bool p0) { return _i<Void>(0x228E5C6AD4D74BFD, p0); }
	static Void _0x0B919E1FB47CC4E0(float p0) { return _i<Void>(0x0B919E1FB47CC4E0, p0); }
	static Void set_gps_disabled_zone(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0xDC20483CD3DD5201, p0, p1, p2, p3, p4, p5); }
	static Void _0xD0BC1C6FB18EE154(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0xD0BC1C6FB18EE154, p0, p1, p2, p3, p4, p5, p6); }
	static Void set_ignore_no_gps_flag(bool ignore) { return _i<Void>(0x72751156E7678833, ignore); }
	static Void _0x1FC289A0C3FF470F(bool p0) { return _i<Void>(0x1FC289A0C3FF470F, p0); }
	static Void set_ped_paths_back_to_original(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0xE04B48F2CC926253, p0, p1, p2, p3, p4, p5, p6); }
	static Void set_ped_paths_in_area(float x1, float y1, float z1, float x2, float y2, float z2, bool unknown, Any p7) { return _i<Void>(0x34F060F4BF92E018, x1, y1, z1, x2, y2, z2, unknown, p7); }
	static Void set_roads_back_to_original(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return _i<Void>(0x1EE7063B80FFC77C, p0, p1, p2, p3, p4, p5, p6); }
	static Void set_roads_back_to_original_in_angled_area(float x1, float y1, float z1, float x2, float y2, float z2, float p6, Any p7) { return _i<Void>(0x0027501B9F3B407E, x1, y1, z1, x2, y2, z2, p6, p7); }
	static Void set_roads_in_angled_area(float x1, float y1, float z1, float x2, float y2, float z2, float angle, bool unknown1, bool unknown2, bool unknown3) { return _i<Void>(0x1A5AA1208AF5DB59, x1, y1, z1, x2, y2, z2, angle, unknown1, unknown2, unknown3); }
	static Void set_roads_in_area(float x1, float y1, float z1, float x2, float y2, float z2, bool unknown1, bool unknown2) { return _i<Void>(0xBF1A602B5BA52FEE, x1, y1, z1, x2, y2, z2, unknown1, unknown2); }
	static Void update_navmesh_blocking_object(Any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, Any p8) { return _i<Void>(0x109E99373F290687, p0, p1, p2, p3, p4, p5, p6, p7, p8); }

	static Void add_armour_to_ped(Ped ped, int amount) { return _i<Void>(0x5BA652A0CD14DF2F, ped, amount); }
	static Void set_ped_decoration(Ped ped, uint32_t collection, uint32_t overlay) { return _i<Void>(0x5F5D1665E352A839, ped, collection, overlay); }
	static Void set_ped_facial_decoration(Ped ped, uint32_t collection, uint32_t overlay) { return _i<Void>(0x5619BFA07CFD7833, ped, collection, overlay); }
	static Any add_relationship_group(const char* name, uint32_t* groupHash) { return _i<Any>(0xF372BC22FCB88606, name, groupHash); }
	static Any add_scenario_blocking_area(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9) { return _i<Any>(0x1B5C85C612E5256E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void apply_damage_to_ped(Ped ped, int damageAmount, bool p2) { return _i<Void>(0x697157CED63F18D4, ped, damageAmount, p2); }
	static Void apply_ped_blood(Ped ped, int boneIndex, float xRot, float yRot, float zRot, const char* woundType) { return _i<Void>(0x83F7E01C7B769A26, ped, boneIndex, xRot, yRot, zRot, woundType); }
	static Void apply_ped_blood_by_zone(Ped ped, Any p1, float p2, float p3, Any* p4) { return _i<Void>(0x3311E47B91EDCBBC, ped, p1, p2, p3, p4); }
	static Void apply_ped_blood_damage_by_zone(Ped ped, Any p1, float p2, float p3, Any p4) { return _i<Void>(0x816F6981C60BF53B, ped, p1, p2, p3, p4); }
	static Void apply_ped_blood_specific(Ped ped, Any p1, float p2, float p3, float p4, float p5, Any p6, float p7, Any* p8) { return _i<Void>(0xEF0D582CBF2D9B0F, ped, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Void apply_ped_damage_decal(Ped ped, int p1, float p2, float p3, float p4, float p5, float p6, int p7, bool p8, const char* p9) { return _i<Void>(0x397C38AA7B4A5F83, ped, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void apply_ped_damage_pack(Ped ped, const char* damagePack, float damage, float mult) { return _i<Void>(0x46DF918788CB093F, ped, damagePack, damage, mult); }
	static Void attach_synchronized_scene_to_entity(int sceneID, Entity entity, int boneIndex) { return _i<Void>(0x272E4723B56A3B96, sceneID, entity, boneIndex); }
	static Void _0xE43A13C9E4CCCBCF(Ped ped, bool p1) { return _i<Void>(0xE43A13C9E4CCCBCF, ped, p1); }
	static bool can_create_random_bike_rider() { return _i<bool>(0xEACEEDA81751915C); }
	static bool can_create_random_cops() { return _i<bool>(0x5EE2CAFF7F17770D); }
	static bool can_create_random_driver() { return _i<bool>(0xB8EB95E5B4E56978); }
	static bool can_create_random_ped(bool unk) { return _i<bool>(0x3E8349C08E4B82E4, unk); }
	static bool can_knock_ped_off_vehicle(Ped ped) { return _i<bool>(0x51AC07A44D4F5B8A, ped); }
	static bool can_ped_in_combat_see_target(Ped ped, Ped target) { return _i<bool>(0xEAD42DE3610D0721, ped, target); }
	static bool can_ped_ragdoll(Ped ped) { return _i<bool>(0x128F79EDCECE4FD5, ped); }
	static bool can_ped_see_ped(Ped ped1, Ped ped2) { return _i<bool>(0x6CD5A433374D4CFB, ped1, ped2); }
	static Any _0x2DFC81C9B9608549(Any p0, Any p1) { return _i<Any>(0x2DFC81C9B9608549, p0, p1); }
	static bool _0x9C6A6C19B6C0C496(Ped p0, Any* p1) { return _i<bool>(0x9C6A6C19B6C0C496, p0, p1); }
	static Void clear_all_ped_props(Ped ped) { return _i<Void>(0xCD8A7537A9B52F06, ped); }
	static Void _0xE6CA85E7259CE16B(Any p0) { return _i<Void>(0xE6CA85E7259CE16B, p0); }
	static Void clear_facial_idle_anim_override(Ped ped) { return _i<Void>(0x726256CC1EEB182F, ped); }
	static Void clear_ped_alternate_movement_anim(Ped ped, int stance, float p2) { return _i<Void>(0xD8D19675ED5FBDCE, ped, stance, p2); }
	static Void clear_ped_alternate_walk_anim(Ped ped, float p1) { return _i<Void>(0x8844BBFCE30AA9E9, ped, p1); }
	static Void clear_ped_blood_damage_by_zone(Ped ped, int p1) { return _i<Void>(0x56E3B78C5408D9F4, ped, p1); }
	static Void clear_ped_damage_decal_by_zone(Ped ped, int p1, const char* p2) { return _i<Void>(0x523C79AEEFCC4A2A, ped, p1, p2); }
	static Void clear_ped_decorations(Ped ped) { return _i<Void>(0x0E5173C163976E38, ped); }
	static Void clear_ped_facial_decorations(Ped ped) { return _i<Void>(0xE3B27E70CEAB9F0C, ped); }
	static Void clear_ped_drive_by_clipset_override(Ped ped) { return _i<Void>(0x4AFE3690D7E0B5AC, ped); }
	static Void _0x6585D955A68452A5(Ped ped) { return _i<Void>(0x6585D955A68452A5, ped); }
	static Void _0x80054D7FCC70EEC6(Any p0) { return _i<Void>(0x80054D7FCC70EEC6, p0); }
	static Void clear_ped_last_damage_bone(Ped ped) { return _i<Void>(0x8EF6B7AC68E2F01B, ped); }
	static Void _0xC79196DCB36F6121(Any p0) { return _i<Void>(0xC79196DCB36F6121, p0); }
	static Void clear_ped_non_creation_area() { return _i<Void>(0x2E05208086BA0651); }
	static Void _0x1280804F7CFD2D6C(Any p0) { return _i<Void>(0x1280804F7CFD2D6C, p0); }
	static Void clear_ped_prop(Ped ped, int propId) { return _i<Void>(0x0943E5B8E078E76E, ped, propId); }
	static Void _0xB50EB4CCB29704AC(Any p0) { return _i<Void>(0xB50EB4CCB29704AC, p0); }
	static Void _0x687C0B594907D2E8(Ped ped) { return _i<Void>(0x687C0B594907D2E8, ped); }
	static Void clear_ped_wetness(Ped ped) { return _i<Void>(0x9C720776DAA43E7E, ped); }
	static Void reset_ped_ragdoll_blocking_flags(Ped ped, int flags) { return _i<Void>(0xD86D101FCFD00A4B, ped, flags); }
	static Void clear_relationship_between_groups(int relationship, uint32_t group1, uint32_t group2) { return _i<Void>(0x5E29243FB56FC6D4, relationship, group1, group2); }
	static Ped clone_ped(Ped ped, float heading, bool isNetwork, bool p3) { return _i<Ped>(0xEF29A16337FACADB, ped, heading, isNetwork, p3); }
	static Any _0x668FD40BCBA5DE48(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Any>(0x668FD40BCBA5DE48, p0, p1, p2, p3, p4); }
	static Void clone_ped_to_target(Ped ped, Ped targetPed) { return _i<Void>(0xE952D6431689AD9A, ped, targetPed); }
	static Void _0x148B08C2D2ACB884(Any p0, Any p1, Any p2) { return _i<Void>(0x148B08C2D2ACB884, p0, p1, p2); }
	static int _0x5407B7288D0478B7(Any p0) { return _i<int>(0x5407B7288D0478B7, p0); }
	static Any _0x336B3D200AB007CB(Any p0, float p1, float p2, float p3, float p4) { return _i<Any>(0x336B3D200AB007CB, p0, p1, p2, p3, p4); }
	static int create_group(int unused) { return _i<int>(0x90370EBE0FEE1A3D, unused); }
	static Void create_nm_message(bool startImmediately, int messageId) { return _i<Void>(0x418EF2A1BCE56685, startImmediately, messageId); }
	static Entity _0x8C4F3BF23B6237DB(Ped ped, bool p1, bool p2) { return _i<Entity>(0x8C4F3BF23B6237DB, ped, p1, p2); }
	static Ped create_ped(int pedType, uint32_t modelHash, float x, float y, float z, float heading, bool isNetwork, bool p7) { return _i<Ped>(0xD49F9B0955C367DE, pedType, modelHash, x, y, z, heading, isNetwork, p7); }
	static Ped create_ped_inside_vehicle(Vehicle vehicle, int pedType, uint32_t modelHash, int seat, bool isNetwork, bool p5) { return _i<Ped>(0x7DD959874C1FD534, vehicle, pedType, modelHash, seat, isNetwork, p5); }
	static Ped create_random_ped(float posX, float posY, float posZ) { return _i<Ped>(0xB4AC7D0CF06BFE8F, posX, posY, posZ); }
	static Ped create_random_ped_as_driver(Vehicle vehicle, bool returnHandle) { return _i<Ped>(0x9B62392B474F44A0, vehicle, returnHandle); }
	static int create_synchronized_scene(float x, float y, float z, float roll, float pitch, float yaw, int p6) { return _i<int>(0x8C18E0F9080ADD73, x, y, z, roll, pitch, yaw, p6); }
	static int create_synchronized_scene2(float x, float y, float z, float radius, uint32_t object) { return _i<int>(0x62EC273D00187DCA, x, y, z, radius, object); }
	static Void delete_ped(Ped* ped) { return _i<Void>(0x9614299DCB53E54B, ped); }
	static Void detach_synchronized_scene(int sceneID) { return _i<Void>(0x6D38F1F04CBB37EA, sceneID); }
	static Void _0xA21C118553BBDF02(Any p0) { return _i<Void>(0xA21C118553BBDF02, p0); }
	static Void _0x600048C60D5C2C51(Any p0) { return _i<Void>(0x600048C60D5C2C51, p0); }
	static Void _0x733C87D4CE22BEA2(Any p0) { return _i<Void>(0x733C87D4CE22BEA2, p0); }
	static bool does_group_exist(int groupId) { return _i<bool>(0x7C6B0C22F9F40BBE, groupId); }
	static Any _0xCC6E3B6BB69501F1(Any p0) { return _i<Any>(0xCC6E3B6BB69501F1, p0); }
	static Any _0x8A24B067D175A7BD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Any>(0x8A24B067D175A7BD, p0, p1, p2, p3, p4, p5); }
	static Void _0xAFF4710E2A0A6C12(Ped ped) { return _i<Void>(0xAFF4710E2A0A6C12, ped); }
	static Void explode_ped_head(Ped ped, uint32_t weaponHash) { return _i<Void>(0x2D05CED3A38D0F3A, ped, weaponHash); }
	static Void _0x4668D80430D6C299(Ped ped) { return _i<Void>(0x4668D80430D6C299, ped); }
	static Void freeze_ped_camera_rotation(Ped ped) { return _i<Void>(0xFF287323B0E2C69A, ped); }
	static Void _0xED3C76ADFA6D07C4(Any p0) { return _i<Void>(0xED3C76ADFA6D07C4, p0); }
	static Void _0x2208438012482A1A(Ped ped, bool p1, bool p2) { return _i<Void>(0x2208438012482A1A, ped, p1, p2); }
	static bool force_ped_motion_state(Ped ped, uint32_t motionStateHash, bool p2, bool p3, bool p4) { return _i<bool>(0xF28965D04F570DCA, ped, motionStateHash, p2, p3, p4); }
	static Void force_ped_to_open_parachute(Ped ped) { return _i<Void>(0x16E42E800B472221, ped); }
	static Void _0xD33DAA36272177C4(Ped ped) { return _i<Void>(0xD33DAA36272177C4, ped); }
	static math::vector3<float> get_anim_initial_offset_position(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9) { return _i<math::vector3<float>>(0xBE22B26DD764C040, animDict, animName, x, y, z, xRot, yRot, zRot, p8, p9); }
	static math::vector3<float> get_anim_initial_offset_rotation(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9) { return _i<math::vector3<float>>(0x4B805E6046EE9E47, animDict, animName, x, y, z, xRot, yRot, zRot, p8, p9); }
	static bool _0x03EA03AF85A85CB7(Ped ped, bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, Any p8) { return _i<bool>(0x03EA03AF85A85CB7, ped, p1, p2, p3, p4, p5, p6, p7, p8); }
	static bool get_closest_ped(float x, float y, float z, float radius, bool p4, bool p5, Ped* outPed, bool p7, bool p8, int pedType) { return _i<bool>(0xC33AB876A77F8164, x, y, z, radius, p4, p5, outPed, p7, p8, pedType); }
	static float get_combat_float(Ped ped, int p1) { return _i<float>(0x52DFF8A10508090A, ped, p1); }
	static math::vector3<float> get_dead_ped_pickup_coords(Ped ped, float p1, float p2) { return _i<math::vector3<float>>(0xCD5003B097200F36, ped, p1, p2); }
	static Any _0xAAA6A3698A69E048(Any p0) { return _i<Any>(0xAAA6A3698A69E048, p0); }
	static int _0xEA9960D07DADCF10(Any p0) { return _i<int>(0xEA9960D07DADCF10, p0); }
	static Any _0xF033419D1B81FAE8(Any p0) { return _i<Any>(0xF033419D1B81FAE8, p0); }
	static Any _0x1E77FA7A62EE6C4C(Any p0) { return _i<Any>(0x1E77FA7A62EE6C4C, p0); }
	static Void get_group_size(int groupID, Any* unknown, int* sizeInMembers) { return _i<Void>(0x8DE69FE35CA09A45, groupID, unknown, sizeInMembers); }
	static Any _0x76BBA2CEE66D47E9(Any p0) { return _i<Any>(0x76BBA2CEE66D47E9, p0); }
	static Ped get_jack_target(Ped ped) { return _i<Ped>(0x5486A79D9FBD342D, ped); }
	static Ped get_melee_target_for_ped(Ped ped) { return _i<Ped>(0x18A3E9EE1297FD39, ped); }
	static bool is_ped_on_mount(Ped ped) { return _i<bool>(0x460BC76A0E10655E, ped); }
	static Ped get_mount(Ped ped) { return _i<Ped>(0xE7E11B8DCBED1058, ped); }
	static bool _0x9E30E91FB03A2CAF(Any* p0, Any* p1) { return _i<bool>(0x9E30E91FB03A2CAF, p0, p1); }
	static int get_number_of_ped_drawable_variations(Ped ped, int componentId) { return _i<int>(0x27561561732A7842, ped, componentId); }
	static int get_number_of_ped_prop_drawable_variations(Ped ped, int propId) { return _i<int>(0x5FAF9754E789FB47, ped, propId); }
	static int get_number_of_ped_prop_texture_variations(Ped ped, int propId, int drawableId) { return _i<int>(0xA6E7F1CEB523E171, ped, propId, drawableId); }
	static int get_number_of_ped_texture_variations(Ped ped, int componentId, int drawableId) { return _i<int>(0x8F7156A3142A6BAD, ped, componentId, drawableId); }
	static int get_num_hair_colors() { return _i<int>(0xE5C0CF872C2AD150); }
	static int get_num_makeup_colors() { return _i<int>(0xD1F7CA1535D22818); }
	static const char* get_pedheadshot_txd_string(int handle) { return _i<const char*>(0xDB4EACD4AD0A5D6B, handle); }
	static Ped get_peds_jacker(Ped ped) { return _i<Ped>(0x9B128DC36C1E04CF, ped); }
	static int get_ped_accuracy(Ped ped) { return _i<int>(0x37F4AD56ECBC0CD6, ped); }
	static int get_ped_alertness(Ped ped) { return _i<int>(0xF6AA118530443FD2, ped); }
	static int get_ped_armour(Ped ped) { return _i<int>(0x9483AF821605B1D8, ped); }
	static Ped get_ped_as_group_leader(int groupID) { return _i<Ped>(0x5CCE68DBD5FE93EC, groupID); }
	static Ped get_ped_as_group_member(int groupID, int memberNumber) { return _i<Ped>(0x51455483CF23ED97, groupID, memberNumber); }
	static math::vector3<float> get_ped_bone_coords(Ped ped, int boneId, float offsetX, float offsetY, float offsetZ) { return _i<math::vector3<float>>(0x17C07FC640E86B4E, ped, boneId, offsetX, offsetY, offsetZ); }
	static int get_ped_bone_index(Ped ped, int boneId) { return _i<int>(0x3F428D08BE5AAE31, ped, boneId); }
	static uint32_t get_ped_cause_of_death(Ped ped) { return _i<uint32_t>(0x16FFE42AB2D2DC59, ped); }
	static int get_ped_combat_movement(Ped ped) { return _i<int>(0xDEA92412FCAEB3F5, ped); }
	static Any get_ped_combat_range(Ped ped) { return _i<Any>(0xF9D9F7F2DB8E2FA0, ped); }
	static bool get_ped_config_flag(Ped ped, int flagId, bool p2) { return _i<bool>(0x7EE53118C892B513, ped, flagId, p2); }
	static bool _0xF60165E1D2C5370B(Ped ped, Any* p1, Any* p2) { return _i<bool>(0xF60165E1D2C5370B, ped, p1, p2); }
	static Any get_ped_decorations_state(Ped ped) { return _i<Any>(0x71EAB450D86954A1, ped); }
	static int get_tattoo_zone(uint32_t collection, uint32_t overlay) { return _i<int>(0x9FD452BFBE7A7A8B, collection, overlay); }
	static math::vector3<float> get_ped_defensive_area_position(Ped ped, bool p1) { return _i<math::vector3<float>>(0x3C06B8786DD94CD1, ped, p1); }
	static int get_ped_drawable_variation(Ped ped, int componentId) { return _i<int>(0x67F3780DD425D4FC, ped, componentId); }
	static Any _0x1461B28A06717D68(Any p0) { return _i<Any>(0x1461B28A06717D68, p0); }
	static float get_ped_enveff_scale(Ped ped) { return _i<float>(0x9C14D30395A51A3C, ped); }
	static math::vector3<float> get_ped_extracted_displacement(Ped ped, bool worldSpace) { return _i<math::vector3<float>>(0xE0AF41401ADF87E3, ped, worldSpace); }
	static int get_ped_group_index(Ped ped) { return _i<int>(0xF162E133B4E7A675, ped); }
	static Void _0x4852FC386E2E1BB5(Any p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0x4852FC386E2E1BB5, p0, p1, p2, p3); }
	static bool get_ped_head_blend_data(Ped ped, Any* headBlendData) { return _i<bool>(0x2746BD9D88C5C5D0, ped, headBlendData); }
	static int get_first_parent_id_for_ped_type(int type) { return _i<int>(0x68D353AB88B97E0C, type); }
	static int get_num_parent_peds_of_type(int type) { return _i<int>(0x5EF37013A6539C9D, type); }
	static int get_ped_head_overlay_value(Ped ped, int overlayID) { return _i<int>(0xA60EF3B6461A4D43, ped, overlayID); }
	static int get_num_head_overlay_values(int overlayID) { return _i<int>(0xCF1CE768BB43480E, overlayID); }
	static Any _0x451294E859ECC018(Any p0) { return _i<Any>(0x451294E859ECC018, p0); }
	static Any _0x9D728C1E12BF5518(Any p0) { return _i<Any>(0x9D728C1E12BF5518, p0); }
	static bool get_ped_last_damage_bone(Ped ped, int* outBone) { return _i<bool>(0xD75960F6BD9EA49C, ped, outBone); }
	static Void _0x013E5CFC38CD5387(Any p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0x013E5CFC38CD5387, p0, p1, p2, p3); }
	static int get_ped_max_health(Ped ped) { return _i<int>(0x4700A416E8324EF3, ped); }
	static int get_ped_money(Ped ped) { return _i<int>(0x3F69145BBA87BAE7, ped); }
	static int get_ped_nearby_peds(Ped ped, int* sizeAndPeds, int ignore) { return _i<int>(0x23F8F5FC7E8C4A6B, ped, sizeAndPeds, ignore); }
	static int get_ped_nearby_vehicles(Ped ped, int* sizeAndVehs) { return _i<int>(0xCFF869CBFA210D82, ped, sizeAndVehs); }
	static int get_ped_palette_variation(Ped ped, int componentId) { return _i<int>(0xE3DD5F2A84B42281, ped, componentId); }
	static int get_ped_parachute_landing_type(Ped ped) { return _i<int>(0x8B9F1FC6AE8166C0, ped); }
	static int get_ped_parachute_state(Ped ped) { return _i<int>(0x79CFD9827CC979B6, ped); }
	static Void get_ped_parachute_tint_index(Ped ped, int* outTintIndex) { return _i<Void>(0xEAF5F7E5AE7C6C9D, ped, outTintIndex); }
	static int get_ped_prop_index(Ped ped, int componentId) { return _i<int>(0x898CC20EA75BACD8, ped, componentId); }
	static int get_ped_prop_texture_index(Ped ped, int componentId) { return _i<int>(0xE131A28626F81AB2, ped, componentId); }
	static int get_ped_ragdoll_bone_index(Ped ped, int bone) { return _i<int>(0x2057EF813397A772, ped, bone); }
	static uint32_t get_ped_relationship_group_default_hash(Ped ped) { return _i<uint32_t>(0x42FDD0F017B1E38E, ped); }
	static uint32_t get_ped_relationship_group_hash(Ped ped) { return _i<uint32_t>(0x7DBDD04862D95F04, ped); }
	static bool get_ped_reset_flag(Ped ped, int flagId) { return _i<bool>(0xAF9E59B1B1FBF2A0, ped, flagId); }
	static Entity get_ped_source_of_death(Ped ped) { return _i<Entity>(0x93C8B64DEB84728C, ped); }
	static bool get_ped_stealth_movement(Ped ped) { return _i<bool>(0x7C2AC9CA66575FBF, ped); }
	static int get_ped_texture_variation(Ped ped, int componentId) { return _i<int>(0x04A355E041E004E6, ped, componentId); }
	static int get_ped_time_of_death(Ped ped) { return _i<int>(0x1E98817B311AE98A, ped); }
	static int get_ped_type(Ped ped) { return _i<int>(0xFF059E1E4C01E63C, ped); }
	static Player get_player_ped_is_following(Ped ped) { return _i<Player>(0x6A3975DEA89F9A17, ped); }
	static Ped get_random_ped_at_coord(float x, float y, float z, float xRadius, float yRadius, float zRadius, int pedType) { return _i<Ped>(0x876046A8E3A4B71C, x, y, z, xRadius, yRadius, zRadius, pedType); }
	static int get_relationship_between_groups(uint32_t group1, uint32_t group2) { return _i<int>(0x9E6B70061662AE5C, group1, group2); }
	static int get_relationship_between_peds(Ped ped1, Ped ped2) { return _i<int>(0xEBA5AD3A0EAF7121, ped1, ped2); }
	static int get_seat_ped_is_trying_to_enter(Ped ped) { return _i<int>(0x6F4C85ACD641BCD2, ped); }
	static float get_synchronized_scene_phase(int sceneID) { return _i<float>(0xE4A310B1D7FA73CC, sceneID); }
	static float get_synchronized_scene_rate(int sceneID) { return _i<float>(0xD80932D577274D40, sceneID); }
	static Any _0x36B77BB84687C318(Ped ped, Any p1) { return _i<Any>(0x36B77BB84687C318, ped, p1); }
	static Any _0xC56FBF2F228E1DAC(Any p0, Any p1, Any p2) { return _i<Any>(0xC56FBF2F228E1DAC, p0, p1, p2); }
	static Any _0x511F1A683387C7E2(Any p0) { return _i<Any>(0x511F1A683387C7E2, p0); }
	static Vehicle get_vehicle_ped_is_entering(Ped ped) { return _i<Vehicle>(0xF92691AED837A5FC, ped); }
	static Vehicle get_vehicle_ped_is_in(Ped ped, bool lastVehicle) { return _i<Vehicle>(0x9A9112A0FE9A4713, ped, lastVehicle); }
	static Vehicle get_vehicle_ped_is_trying_to_enter(Ped ped) { return _i<Vehicle>(0x814FA8BE5449445D, ped); }
	static Vehicle get_vehicle_ped_is_using(Ped ped) { return _i<Vehicle>(0x6094AD011A2EA87D, ped); }
	static Void give_ped_helmet(Ped ped, bool cannotRemove, int helmetFlag, int textureIndex) { return _i<Void>(0x54C7C4A94367717E, ped, cannotRemove, helmetFlag, textureIndex); }
	static Void give_ped_nm_message(Ped ped) { return _i<Void>(0xB158DFCCC56E5C5B, ped); }
	static bool has_action_mode_asset_loaded(const char* asset) { return _i<bool>(0xE4B5F4BF2CB24E65, asset); }
	static Any _0x876928DDDFCCC9CD() { return _i<Any>(0x876928DDDFCCC9CD); }
	static Any _0xE8A169E666CBC541() { return _i<Any>(0xE8A169E666CBC541); }
	static bool has_ped_head_blend_finished(Ped ped) { return _i<bool>(0x654CD0A825161131, ped); }
	static bool _0x784002A632822099(Ped ped) { return _i<bool>(0x784002A632822099, ped); }
	static bool _0x66680A92700F43DF(Ped p0) { return _i<bool>(0x66680A92700F43DF, p0); }
	static bool has_ped_received_event(Any p0, Any p1) { return _i<bool>(0x8507BCB710FA6DC0, p0, p1); }
	static bool has_stealth_mode_asset_loaded(const char* asset) { return _i<bool>(0xE977FC5B08AF3441, asset); }
	static bool _0x7350823473013C02(Ped ped) { return _i<bool>(0x7350823473013C02, ped); }
	static Void hide_ped_blood_damage_by_zone(Ped ped, Any p1, bool p2) { return _i<Void>(0x62AB793144DE75DC, ped, p1, p2); }
	static Void _0x4759CC730F947C81() { return _i<Void>(0x4759CC730F947C81); }
	static bool _0x68772DB2B2526F9F(Ped ped, float x, float y, float z, float range) { return _i<bool>(0x68772DB2B2526F9F, ped, x, y, z, range); }
	static bool is_any_ped_near_point(float x, float y, float z, float radius) { return _i<bool>(0x083961498679DC9F, x, y, z, radius); }
	static bool is_any_ped_shooting_in_area(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7) { return _i<bool>(0xA0D3D71EA1086C55, x1, y1, z1, x2, y2, z2, p6, p7); }
	static bool is_conversation_ped_dead(Ped ped) { return _i<bool>(0xE0A0AEC214B1FABA, ped); }
	static bool is_cop_ped_in_area3_d(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<bool>(0x16EC4839969F9F5E, x1, y1, z1, x2, y2, z2); }
	static bool _0xF2385935BFFD4D92(Any p0) { return _i<bool>(0xF2385935BFFD4D92, p0); }
	static bool _0xA3F3564A5B3646C0(Ped ped) { return _i<bool>(0xA3F3564A5B3646C0, ped); }
	static Any _0xEBB376779A760AA8() { return _i<Any>(0xEBB376779A760AA8); }
	static bool is_pedheadshot_ready(int handle) { return _i<bool>(0x7085228842B13A67, handle); }
	static bool is_pedheadshot_valid(int handle) { return _i<bool>(0xA0A9668F158129A2, handle); }
	static bool is_ped_aiming_from_cover(Ped ped) { return _i<bool>(0x3998B1276A3300E5, ped); }
	static bool is_ped_a_player(Ped ped) { return _i<bool>(0x12534C348C6CB68B, ped); }
	static bool is_ped_being_jacked(Ped ped) { return _i<bool>(0x9A497FE2DF198913, ped); }
	static bool is_ped_being_stealth_killed(Ped ped) { return _i<bool>(0x863B23EFDE9C5DF2, ped); }
	static bool is_ped_being_stunned(Ped ped, int p1) { return _i<bool>(0x4FBACCE3B4138EE8, ped, p1); }
	static bool is_ped_blush_color_valid(int colorID) { return _i<bool>(0x604E810189EE3A59, colorID); }
	static bool _0xF41B5D290C99A3D6(Any p0) { return _i<bool>(0xF41B5D290C99A3D6, p0); }
	static bool is_ped_climbing(Ped ped) { return _i<bool>(0x53E8CB4F48BFE623, ped); }
	static bool is_ped_component_variation_valid(Ped ped, int componentId, int drawableId, int textureId) { return _i<bool>(0xE825F6B6CEA7671D, ped, componentId, drawableId, textureId); }
	static bool is_ped_dead_or_dying(Ped ped, bool p1) { return _i<bool>(0x3317DEDB88C95038, ped, p1); }
	static bool _0xBA63D9FE45412247(Ped ped, bool p1) { return _i<bool>(0xBA63D9FE45412247, ped, p1); }
	static bool is_ped_diving(Ped ped) { return _i<bool>(0x5527B8246FEF9B11, ped); }
	static Any _0x451D05012CCEC234(Any p0) { return _i<Any>(0x451D05012CCEC234, p0); }
	static bool is_ped_doing_driveby(Ped ped) { return _i<bool>(0xB2C086CC1BF8F2BF, ped); }
	static bool is_ped_ducking(Ped ped) { return _i<bool>(0xD125AE748725C6BC, ped); }
	static bool is_ped_evasive_diving(Ped ped, Entity* evadingEntity) { return _i<bool>(0x414641C26E105898, ped, evadingEntity); }
	static bool is_ped_facing_ped(Ped ped, Ped otherPed, float angle) { return _i<bool>(0xD71649DB0A545AA3, ped, otherPed, angle); }
	static bool is_ped_falling(Ped ped) { return _i<bool>(0xFB92A102F1C4DFA3, ped); }
	static bool is_ped_fatally_injured(Ped ped) { return _i<bool>(0xD839450756ED5A80, ped); }
	static bool is_ped_fleeing(Ped ped) { return _i<bool>(0xBBCCE00B381F8482, ped); }
	static bool is_ped_getting_into_a_vehicle(Ped ped) { return _i<bool>(0xBB062B2B5722478E, ped); }
	static bool is_ped_going_into_cover(Ped ped) { return _i<bool>(0x9F65DBC537E59AD5, ped); }
	static bool is_ped_group_member(Ped ped, int groupId) { return _i<bool>(0x9BB01E3834671191, ped, groupId); }
	static bool is_ped_hair_color_valid(int colorID) { return _i<bool>(0xE0D36E5D9E99CC21, colorID); }
	static bool _0xED6D8E27A43B8CDE(Any p0) { return _i<bool>(0xED6D8E27A43B8CDE, p0); }
	static bool is_ped_hanging_on_to_vehicle(Ped ped) { return _i<bool>(0x1C86D8AEF8254B78, ped); }
	static bool _0xFCF37A457CB96DC0(Any p0, float p1, float p2, float p3, float p4) { return _i<bool>(0xFCF37A457CB96DC0, p0, p1, p2, p3, p4); }
	static bool is_ped_headtracking_entity(Ped ped, Entity entity) { return _i<bool>(0x813A0A7C9D2E831F, ped, entity); }
	static bool is_ped_headtracking_ped(Ped ped1, Ped ped2) { return _i<bool>(0x5CD3CB88A7F8850D, ped1, ped2); }
	static Any _0xB9496CE47546DB2C(Any p0) { return _i<Any>(0xB9496CE47546DB2C, p0); }
	static bool is_ped_human(Ped ped) { return _i<bool>(0xB980061DA992779D, ped); }
	static bool is_ped_hurt(Ped ped) { return _i<bool>(0x5983BB449D7FDB12, ped); }
	static bool is_ped_injured(Ped ped) { return _i<bool>(0x84A2DD9AC37C35C1, ped); }
	static bool is_ped_in_any_boat(Ped ped) { return _i<bool>(0x2E0E1C2B4F6CB339, ped); }
	static bool is_ped_in_any_heli(Ped ped) { return _i<bool>(0x298B91AE825E5705, ped); }
	static bool is_ped_in_any_plane(Ped ped) { return _i<bool>(0x5FFF4CFC74D8FB80, ped); }
	static bool is_ped_in_any_police_vehicle(Ped ped) { return _i<bool>(0x0BD04E29640C9C12, ped); }
	static bool is_ped_in_any_sub(Ped ped) { return _i<bool>(0xFBFC01CCFB35D99E, ped); }
	static bool is_ped_in_any_taxi(Ped ped) { return _i<bool>(0x6E575D6A898AB852, ped); }
	static bool is_ped_in_any_train(Ped ped) { return _i<bool>(0x6F972C1AB75A1ED0, ped); }
	static bool is_ped_in_any_vehicle(Ped ped, bool atGetIn) { return _i<bool>(0x997ABD671D25CA0B, ped, atGetIn); }
	static bool is_ped_in_combat(Ped ped, Ped target) { return _i<bool>(0x4859F1FC66A6278E, ped, target); }
	static bool is_ped_in_cover(Ped ped, bool p1) { return _i<bool>(0x60DFD0691A170B88, ped, p1); }
	static bool is_ped_in_cover_facing_left(Ped ped) { return _i<bool>(0x845333B3150583AB, ped); }
	static bool is_ped_in_flying_vehicle(Ped ped) { return _i<bool>(0x9134873537FA419C, ped); }
	static bool is_ped_in_group(Ped ped) { return _i<bool>(0x5891CAC5D4ACFF74, ped); }
	static bool is_ped_standing_in_cover(Ped ped) { return _i<bool>(0x6A03BF943D767C93, ped); }
	static bool is_ped_in_melee_combat(Ped ped) { return _i<bool>(0x4E209B2C1EAD5159, ped); }
	static bool is_ped_in_model(Ped ped, uint32_t modelHash) { return _i<bool>(0x796D90EFB19AA332, ped, modelHash); }
	static bool is_ped_in_parachute_free_fall(Ped ped) { return _i<bool>(0x7DCE8BDA0F1C1200, ped); }
	static bool is_ped_in_vehicle(Ped ped, Vehicle vehicle, bool atGetIn) { return _i<bool>(0xA3EE4A07279BB9DB, ped, vehicle, atGetIn); }
	static bool is_ped_jacking(Ped ped) { return _i<bool>(0x4AE4FF911DFB61DA, ped); }
	static bool is_ped_jumping(Ped ped) { return _i<bool>(0xCEDABC5900A0BF97, ped); }
	static bool is_ped_jumping_out_of_vehicle(Ped ped) { return _i<bool>(0x433DDFFE2044B636, ped); }
	static Any _0x412F1364FA066CFB(Any p0) { return _i<Any>(0x412F1364FA066CFB, p0); }
	static bool is_ped_lipstick_color_valid(int colorID) { return _i<bool>(0x0525A2C2562F3CD4, colorID); }
	static bool _0x3E802F11FBE27674(Any p0) { return _i<bool>(0x3E802F11FBE27674, p0); }
	static bool is_ped_male(Ped ped) { return _i<bool>(0x6D9F5FAA7488BA46, ped); }
	static bool is_ped_model(Ped ped, uint32_t modelHash) { return _i<bool>(0xC9D55B1A358A5BF7, ped, modelHash); }
	static bool is_ped_on_any_bike(Ped ped) { return _i<bool>(0x94495889E22C6479, ped); }
	static bool is_ped_on_foot(Ped ped) { return _i<bool>(0x01FEE67DB37F59B2, ped); }
	static bool is_ped_on_specific_vehicle(Ped ped, Vehicle vehicle) { return _i<bool>(0xEC5F66E459AF3BB2, ped, vehicle); }
	static bool is_ped_on_vehicle(Ped ped) { return _i<bool>(0x67722AEB798E5FAB, ped); }
	static bool _0x26AF0E8E30BD2A2C(Ped ped) { return _i<bool>(0x26AF0E8E30BD2A2C, ped); }
	static bool _0xEBD0EDBA5BE957CF(Ped ped) { return _i<bool>(0xEBD0EDBA5BE957CF, ped); }
	static bool _0xDCCA191DF9980FD7(Ped ped) { return _i<bool>(0xDCCA191DF9980FD7, ped); }
	static bool is_ped_performing_stealth_kill(Ped ped) { return _i<bool>(0xFD4CCDBCC59941B7, ped); }
	static bool is_ped_planting_bomb(Ped ped) { return _i<bool>(0xC70B5FAE151982D8, ped); }
	static bool is_ped_prone(Ped ped) { return _i<bool>(0xD6A86331A537A7B9, ped); }
	static bool is_ped_ragdoll(Ped ped) { return _i<bool>(0x47E4E977581C5B55, ped); }
	static bool is_ped_reloading(Ped ped) { return _i<bool>(0x24B100C68C645951, ped); }
	static bool is_ped_responding_to_event(Ped ped, Any event) { return _i<bool>(0x625B774D75C87068, ped, event); }
	static bool _0xD1871251F3B5ACD7(Ped ped) { return _i<bool>(0xD1871251F3B5ACD7, ped); }
	static bool is_ped_running_mobile_phone_task(Ped ped) { return _i<bool>(0x2AFE52F782F25775, ped); }
	static bool is_ped_running_ragdoll_task(Ped ped) { return _i<bool>(0xE3B6097CC25AA69E, ped); }
	static Any _0x81AA517FBBA05D39(Any p0) { return _i<Any>(0x81AA517FBBA05D39, p0); }
	static bool _0xB8B52E498014F5B0(Ped ped) { return _i<bool>(0xB8B52E498014F5B0, ped); }
	static bool is_ped_shooting(Ped ped) { return _i<bool>(0x34616828CD07F1A1, ped); }
	static bool is_ped_shooting_in_area(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8) { return _i<bool>(0x7E9DFE24AC1E58EF, ped, x1, y1, z1, x2, y2, z2, p7, p8); }
	static bool is_ped_sitting_in_any_vehicle(Ped ped) { return _i<bool>(0x826AA586EDB9FEF8, ped); }
	static bool is_ped_sitting_in_vehicle(Ped ped, Vehicle vehicle) { return _i<bool>(0xA808AA1D79230FC2, ped, vehicle); }
	static bool is_ped_stopped(Ped ped) { return _i<bool>(0x530944F6F4B8A214, ped); }
	static bool is_ped_swimming(Ped ped) { return _i<bool>(0x9DE327631295B4C2, ped); }
	static bool is_ped_swimming_under_water(Ped ped) { return _i<bool>(0xC024869A53992F34, ped); }
	static Any _0x3795688A307E1EB6(Any p0) { return _i<Any>(0x3795688A307E1EB6, p0); }
	static bool _0x14590DDBEDB1EC85(Ped ped) { return _i<bool>(0x14590DDBEDB1EC85, ped); }
	static bool is_ped_tracked(Ped ped) { return _i<bool>(0x4C5E1F087CD10BB7, ped); }
	static bool is_ped_trying_to_enter_a_locked_vehicle(Ped ped) { return _i<bool>(0x44D28D5DDFE5F68C, ped); }
	static bool is_ped_using_action_mode(Ped ped) { return _i<bool>(0x00E73468D085F745, ped); }
	static bool is_ped_using_any_scenario(Ped ped) { return _i<bool>(0x57AB4A3080F85143, ped); }
	static bool is_ped_using_scenario(Ped ped, const char* scenario) { return _i<bool>(0x1BF094736DD62C2E, ped, scenario); }
	static bool is_ped_vaulting(Ped ped) { return _i<bool>(0x117C70D1F5730B5E, ped); }
	static bool is_ped_wearing_helmet(Ped ped) { return _i<bool>(0xF33BDFE19B309B19, ped); }
	static bool is_scripted_scenario_ped_using_conditional_anim(Ped ped, const char* animDict, const char* anim) { return _i<bool>(0x6EC47A344923E1ED, ped, animDict, anim); }
	static bool _0x7F2F4F13AC5257EF(Any p0) { return _i<bool>(0x7F2F4F13AC5257EF, p0); }
	static bool is_synchronized_scene_looped(int sceneID) { return _i<bool>(0x62522002E0C391BA, sceneID); }
	static bool is_synchronized_scene_running(int sceneId) { return _i<bool>(0x25D39B935A038A26, sceneId); }
	static bool _0x06087579E7AA85A9(Any p0, Any p1, float p2, float p3, float p4, float p5) { return _i<bool>(0x06087579E7AA85A9, p0, p1, p2, p3, p4, p5); }
	static bool is_tracked_ped_visible(Ped ped) { return _i<bool>(0x91C8E617F64188AC, ped); }
	static bool _0xFEC9A3B1820F3331(Any p0) { return _i<bool>(0xFEC9A3B1820F3331, p0); }
	static Void knock_off_ped_prop(Ped ped, bool p1, bool p2, bool p3, bool p4) { return _i<Void>(0x6FD7816A36615F48, ped, p1, p2, p3, p4); }
	static Void knock_ped_off_vehicle(Ped ped) { return _i<Void>(0x45BBCBA77C29A841, ped); }
	static Void _0x2B694AFCF64E6994(Ped ped, bool p1) { return _i<Void>(0x2B694AFCF64E6994, ped, p1); }
	static bool _0x46B05BCAE43856B0(Ped ped, int flag) { return _i<bool>(0x46B05BCAE43856B0, ped, flag); }
	static Void play_facial_anim(Ped ped, const char* animName, const char* animDict) { return _i<Void>(0xE1E65CA8AC9C00ED, ped, animName, animDict); }
	static Void register_hated_targets_around_ped(Ped ped, float radius) { return _i<Void>(0x9222F300BF8354FE, ped, radius); }
	static int register_pedheadshot(Ped ped) { return _i<int>(0x4462658788425076, ped); }
	static Any _0xBA8805A1108A2515(Any p0) { return _i<Any>(0xBA8805A1108A2515, p0); }
	static Any _0x953563CE563143AF(Any p0) { return _i<Any>(0x953563CE563143AF, p0); }
	static Void register_target(Ped ped, Ped target) { return _i<Void>(0x2F25D9AEFA34FBA2, ped, target); }
	static Void _0x5D517B27CF6ECD04(Any p0) { return _i<Void>(0x5D517B27CF6ECD04, p0); }
	static Void _0xF79F9DEF0AADE61A(Ped ped) { return _i<Void>(0xF79F9DEF0AADE61A, ped); }
	static Void _0x5AAB586FFEC0FD96(Any p0) { return _i<Void>(0x5AAB586FFEC0FD96, p0); }
	static Void remove_action_mode_asset(const char* asset) { return _i<Void>(0x13E940F88470FA51, asset); }
	static Void remove_group(int groupId) { return _i<Void>(0x8EB2F69076AF7053, groupId); }
	static Void remove_ped_defensive_area(Ped ped, bool toggle) { return _i<Void>(0x74D4E028107450A9, ped, toggle); }
	static Void remove_ped_elegantly(Ped* ped) { return _i<Void>(0xAC6D445B994DF95E, ped); }
	static Void remove_ped_from_group(Ped ped) { return _i<Void>(0xED74007FFB146BC2, ped); }
	static Void remove_ped_helmet(Ped ped, bool instantly) { return _i<Void>(0xA7B2458D0AD6DED8, ped, instantly); }
	static Void remove_ped_preferred_cover_set(Ped ped) { return _i<Void>(0xFDDB234CF74073D9, ped); }
	static Void remove_relationship_group(uint32_t groupHash) { return _i<Void>(0xB6BA2444AB393DA2, groupHash); }
	static Void remove_scenario_blocking_area(Any p0, bool p1) { return _i<Void>(0x31D16B74C6E29D66, p0, p1); }
	static Void remove_scenario_blocking_areas() { return _i<Void>(0xD37401D78A929A49); }
	static Void remove_stealth_mode_asset(const char* asset) { return _i<Void>(0x9219857D21F0E842, asset); }
	static Void request_action_mode_asset(const char* asset) { return _i<Void>(0x290E2780BB7AA598, asset); }
	static bool _0xF0DAEF2F545BEE25(Any p0) { return _i<bool>(0xF0DAEF2F545BEE25, p0); }
	static Void _0xCD018C591F94CB43(Any p0, bool p1) { return _i<Void>(0xCD018C591F94CB43, p0, p1); }
	static Void _0x75BA1CB3B7D40CAF(Ped ped, bool p1) { return _i<Void>(0x75BA1CB3B7D40CAF, ped, p1); }
	static Void _0x2BC338A7B21F4608(Ped ped, bool p1) { return _i<Void>(0x2BC338A7B21F4608, ped, p1); }
	static Void _0x7D7A2E43E74E2EB8(Any p0) { return _i<Void>(0x7D7A2E43E74E2EB8, p0); }
	static Void request_stealth_mode_asset(const char* asset) { return _i<Void>(0x2A0A62FCDEE16D4F, asset); }
	static Void reset_ai_melee_weapon_damage_modifier() { return _i<Void>(0x46E56A7CD1D63C3F); }
	static Void reset_ai_weapon_damage_modifier() { return _i<Void>(0xEA16670E7BA4743C); }
	static Void reset_group_formation_default_spacing(int groupHandle) { return _i<Void>(0x63DAB4CCB3273205, groupHandle); }
	static Void reset_ped_in_vehicle_context(Ped ped) { return _i<Void>(0x22EF8FF8778030EB, ped); }
	static Void reset_ped_last_vehicle(Ped ped) { return _i<Void>(0xBB8DE8CF6A8DD8BB, ped); }
	static Void reset_ped_movement_clipset(Ped ped, float p1) { return _i<Void>(0xAA74EC0CB0AAEA2C, ped, p1); }
	static Void reset_ped_ragdoll_timer(Ped ped) { return _i<Void>(0x9FA4664CF62E47E8, ped); }
	static Void reset_ped_strafe_clipset(Ped ped) { return _i<Void>(0x20510814175EA477, ped); }
	static Void reset_ped_visible_damage(Ped ped) { return _i<Void>(0x3AC1F7B898F30C05, ped); }
	static Void clear_ped_blood_damage(Ped ped) { return _i<Void>(0x8FE22675A5A45817, ped); }
	static Void reset_ped_weapon_movement_clipset(Ped ped) { return _i<Void>(0x97B0DB5B4AA74E77, ped); }
	static Void resurrect_ped(Ped ped) { return _i<Void>(0x71BC8E838B9C6035, ped); }
	static Void revive_injured_ped(Ped ped) { return _i<Void>(0x8D8ACD8388CD99CE, ped); }
	static Void set_ai_melee_weapon_damage_modifier(float modifier) { return _i<Void>(0x66460DEDDD417254, modifier); }
	static Void set_ai_weapon_damage_modifier(float value) { return _i<Void>(0x1B1E2A40A65B8521, value); }
	static Void _0x061CB768363D6424(Any p0, bool p1) { return _i<Void>(0x061CB768363D6424, p0, p1); }
	static Void _0x87DDEB611B329A9C(Any p0) { return _i<Void>(0x87DDEB611B329A9C, p0); }
	static Void _0x6B0E6172C9A4D902(bool p0) { return _i<Void>(0x6B0E6172C9A4D902, p0); }
	static Void set_blocking_of_non_temporary_events(Ped ped, bool toggle) { return _i<Void>(0x9F8AA94D6D97DBF4, ped, toggle); }
	static Void _0x9911F4A24485F653(bool p0) { return _i<Void>(0x9911F4A24485F653, p0); }
	static Void set_can_attack_friendly(Ped ped, bool toggle, bool p2) { return _i<Void>(0xB3B1CB349FF9C75D, ped, toggle, p2); }
	static Void set_combat_float(Ped ped, int combatType, float p2) { return _i<Void>(0xFF41B4B141ED981C, ped, combatType, p2); }
	static Void _0x2F074C904D85129E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x2F074C904D85129E, p0, p1, p2, p3, p4, p5, p6); }
	static Void _0x2735233A786B1BEF(Ped ped, float p1) { return _i<Void>(0x2735233A786B1BEF, ped, p1); }
	static Void set_create_random_cops(bool toggle) { return _i<Void>(0x102E68B2024D536D, toggle); }
	static Void set_create_random_cops_not_on_scenarios(bool toggle) { return _i<Void>(0x8A4986851C4EF6E7, toggle); }
	static Void set_create_random_cops_on_scenarios(bool toggle) { return _i<Void>(0x444CB7D7DBE6973D, toggle); }
	static Void _0x711794453CFD692B(Any p0, Any p1) { return _i<Void>(0x711794453CFD692B, p0, p1); }
	static Any _0xDFE68C4B787E1BFB() { return _i<Any>(0xDFE68C4B787E1BFB); }
	static Void set_driver_ability(Ped driver, float ability) { return _i<Void>(0xB195FFA8042FC5C3, driver, ability); }
	static Void set_driver_aggressiveness(Ped driver, float aggressiveness) { return _i<Void>(0xA731F608CA104E3C, driver, aggressiveness); }
	static Void _0xDED5AF5A0EA4B297(Ped driver, float p1) { return _i<Void>(0xDED5AF5A0EA4B297, driver, p1); }
	static Void set_enable_bound_ankles(Ped ped, bool toggle) { return _i<Void>(0xC52E0F855C58FC2E, ped, toggle); }
	static Void set_enable_handcuffs(Ped ped, bool toggle) { return _i<Void>(0xDF1AF8B5D56542FA, ped, toggle); }
	static Void set_enable_ped_enveff_scale(Ped ped, bool toggle) { return _i<Void>(0xD2C5AA0C0E8D0F1E, ped, toggle); }
	static Void set_enable_scuba(Ped ped, bool toggle) { return _i<Void>(0xF99F62004024D506, ped, toggle); }
	static Void set_facial_idle_anim_override(Ped ped, const char* animName, const char* animDict) { return _i<Void>(0xFFC24B988B938B38, ped, animName, animDict); }
	static Void _0x129466ED55140F8D(Ped ped, bool toggle) { return _i<Void>(0x129466ED55140F8D, ped, toggle); }
	static Void _0xCB968B53FC7F916D(Any p0, bool p1, Any p2, Any p3) { return _i<Void>(0xCB968B53FC7F916D, p0, p1, p2, p3); }
	static Void set_group_formation(int groupId, int formationType) { return _i<Void>(0xCE2F5FC3AF7E8C1E, groupId, formationType); }
	static Void set_group_formation_spacing(int groupId, float p1, float p2, float p3) { return _i<Void>(0x1D9D45004C28C916, groupId, p1, p2, p3); }
	static Void set_group_separation_range(int groupHandle, float separationRange) { return _i<Void>(0x4102C7858CFEE4E4, groupHandle, separationRange); }
	static Void set_ped_eye_color(Ped ped, int index) { return _i<Void>(0x50B56988B170AFDF, ped, index); }
	static Void _0xCC9682B8951C5229(Ped ped, int r, int g, int b, int p4) { return _i<Void>(0xCC9682B8951C5229, ped, r, g, b, p4); }
	static Void _0xFF4803BC019852D9(float p0, Any p1) { return _i<Void>(0xFF4803BC019852D9, p0, p1); }
	static Void set_ik_target(Ped ped, int p1, Ped targetPed, int boneLookAt, float x, float y, float z, Any p7, int duration, int duration1) { return _i<Void>(0xC32779C16FCEECD9, ped, p1, targetPed, boneLookAt, x, y, z, p7, duration, duration1); }
	static Void _0x1A330D297AAC6BC1(Ped ped, int p1) { return _i<Void>(0x1A330D297AAC6BC1, ped, p1); }
	static Void _0x781DE8FA214E87D2(Ped ped, const char* p1) { return _i<Void>(0x781DE8FA214E87D2, ped, p1); }
	static Void set_ped_accuracy(Ped ped, int accuracy) { return _i<Void>(0x7AEFB85C1D49DEB6, ped, accuracy); }
	static Void set_ped_alertness(Ped ped, int value) { return _i<Void>(0xDBA71115ED9941A6, ped, value); }
	static Void set_ped_allowed_to_duck(Ped ped, bool toggle) { return _i<Void>(0xDA1F1B7BE1A8766F, ped, toggle); }
	static Void _0xF2BEBCDFAFDAA19E(bool toggle) { return _i<Void>(0xF2BEBCDFAFDAA19E, toggle); }
	static Void _0x49E50BDB8BA4DAB2(Ped ped, bool p1) { return _i<Void>(0x49E50BDB8BA4DAB2, ped, p1); }
	static Void set_ped_allow_vehicles_override(Ped ped, bool toggle) { return _i<Void>(0x3C028C636A414ED9, ped, toggle); }
	static Void set_ped_alternate_movement_anim(Ped ped, int stance, const char* animDictionary, const char* animationName, float p4, bool p5) { return _i<Void>(0x90A43CC281FFAB46, ped, stance, animDictionary, animationName, p4, p5); }
	static Void set_ped_alternate_walk_anim(Ped ped, const char* animDict, const char* animName, float p3, bool p4) { return _i<Void>(0x6C60394CB4F75E9A, ped, animDict, animName, p3, p4); }
	static Void set_ped_angled_defensive_area(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8, bool p9) { return _i<Void>(0xC7F76DF27A5045A1, ped, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void _0x2B5AA717A181FB4C(Any p0, bool p1) { return _i<Void>(0x2B5AA717A181FB4C, p0, p1); }
	static Void set_ped_armour(Ped ped, int amount) { return _i<Void>(0xCEA04D83135264CC, ped, amount); }
	static Void set_ped_as_cop(Ped ped, bool toggle) { return _i<Void>(0xBB03C38DD3FB7FFD, ped, toggle); }
	static Void set_ped_as_enemy(Ped ped, bool toggle) { return _i<Void>(0x02A0C9720B854BFA, ped, toggle); }
	static Void set_ped_as_group_leader(Ped ped, int groupId) { return _i<Void>(0x2A7819605465FBCE, ped, groupId); }
	static Void set_ped_as_group_member(Ped ped, int groupId) { return _i<Void>(0x9F3480FE65DB31B5, ped, groupId); }
	static Void set_ped_blend_from_parents(Ped ped, Any p1, Any p2, float p3, float p4) { return _i<Void>(0x137BBD05230DB22D, ped, p1, p2, p3, p4); }
	static Void _0x576594E8D64375E2(Any p0, bool p1) { return _i<Void>(0x576594E8D64375E2, p0, p1); }
	static Void set_ped_bounds_orientation(Ped ped, float p1, float p2, float p3, float p4, float p5) { return _i<Void>(0x4F5F651ACCC9C4CF, ped, p1, p2, p3, p4, p5); }
	static Void set_ped_can_arm_ik(Ped ped, bool toggle) { return _i<Void>(0x6C3B4D6D13B4C841, ped, toggle); }
	static Void set_ped_can_be_dragged_out(Ped ped, bool toggle) { return _i<Void>(0xC1670E958EEE24E5, ped, toggle); }
	static Void set_ped_can_be_knocked_off_vehicle(Ped ped, int state) { return _i<Void>(0x7A6535691B477C48, ped, state); }
	static Void set_ped_can_be_shot_in_vehicle(Ped ped, bool toggle) { return _i<Void>(0xC7EF1BA83230BA07, ped, toggle); }
	static Void set_ped_can_be_targeted_when_injured(Ped ped, bool toggle) { return _i<Void>(0x638C03B0F9878F57, ped, toggle); }
	static Void set_ped_can_be_targeted_without_los(Ped ped, bool toggle) { return _i<Void>(0x4328652AE5769C71, ped, toggle); }
	static Void set_ped_can_be_targetted(Ped ped, bool toggle) { return _i<Void>(0x63F58F7C80513AAD, ped, toggle); }
	static Void set_ped_can_be_targetted_by_player(Ped ped, Player player, bool toggle) { return _i<Void>(0x66B57B72E0836A76, ped, player, toggle); }
	static Void set_ped_can_be_targetted_by_team(Ped ped, int team, bool toggle) { return _i<Void>(0xBF1CA77833E58F2C, ped, team, toggle); }
	static Void set_ped_can_cower_in_cover(Ped ped, bool toggle) { return _i<Void>(0xCB7553CDCEF4A735, ped, toggle); }
	static Void set_ped_can_evasive_dive(Ped ped, bool toggle) { return _i<Void>(0x6B7A646C242A7059, ped, toggle); }
	static Void set_ped_can_head_ik(Ped ped, bool toggle) { return _i<Void>(0xC11C18092C5530DC, ped, toggle); }
	static Void set_ped_can_leg_ik(Ped ped, bool toggle) { return _i<Void>(0x73518ECE2485412B, ped, toggle); }
	static Void _0xE861D0B05C7662B8(Any p0, bool p1, Any p2) { return _i<Void>(0xE861D0B05C7662B8, p0, p1, p2); }
	static Void set_ped_can_peek_in_cover(Ped ped, bool toggle) { return _i<Void>(0xC514825C507E3736, ped, toggle); }
	static Void set_ped_can_play_ambient_anims(Ped ped, bool toggle) { return _i<Void>(0x6373D1349925A70E, ped, toggle); }
	static Void set_ped_can_play_ambient_base_anims(Ped ped, bool toggle) { return _i<Void>(0x0EB0585D15254740, ped, toggle); }
	static Void set_ped_can_play_gesture_anims(Ped ped, bool toggle) { return _i<Void>(0xBAF20C5432058024, ped, toggle); }
	static Void _0x820E9892A77E97CD(Any p0, Any p1) { return _i<Void>(0x820E9892A77E97CD, p0, p1); }
	static Void set_ped_can_play_viseme_anims(Ped ped, bool toggle, bool p2) { return _i<Void>(0xF833DDBA3B104D43, ped, toggle, p2); }
	static Void set_ped_can_ragdoll(Ped ped, bool toggle) { return _i<Void>(0xB128377056A54E2A, ped, toggle); }
	static Void set_ped_can_ragdoll_from_player_impact(Ped ped, bool toggle) { return _i<Void>(0xDF993EE5E90ABA25, ped, toggle); }
	static Void set_ped_can_smash_glass(Ped ped, bool p1, bool p2) { return _i<Void>(0x1CCE141467FF42A2, ped, p1, p2); }
	static Void set_ped_can_switch_weapon(Ped ped, bool toggle) { return _i<Void>(0xED7F7EFE9FABF340, ped, toggle); }
	static Void set_ped_can_teleport_to_group_leader(Ped pedHandle, int groupHandle, bool toggle) { return _i<Void>(0x2E2F4240B3F24647, pedHandle, groupHandle, toggle); }
	static Void set_ped_can_torso_ik(Ped ped, bool toggle) { return _i<Void>(0xF2B7106D37947CE0, ped, toggle); }
	static Void _0xF5846EDB26A98A24(Ped ped, bool p1) { return _i<Void>(0xF5846EDB26A98A24, ped, p1); }
	static Void _0x6647C5F6F5792496(Ped ped, bool p1) { return _i<Void>(0x6647C5F6F5792496, ped, p1); }
	static Void set_ped_can_use_auto_conversation_lookat(Ped ped, bool toggle) { return _i<Void>(0xEC4686EC06434678, ped, toggle); }
	static Void set_ped_capsule(Ped ped, float value) { return _i<Void>(0x364DF566EC833DE2, ped, value); }
	static Void set_ped_cloth_prone(Any p0, Any p1) { return _i<Void>(0x82A3D6D9CC2CB8E3, p0, p1); }
	static Void _0x78C4E9961DB3EB5B(Any p0, Any p1) { return _i<Void>(0x78C4E9961DB3EB5B, p0, p1); }
	static Void _0xA660FAF550EB37E5(Any p0, bool p1) { return _i<Void>(0xA660FAF550EB37E5, p0, p1); }
	static Void set_ped_combat_ability(Ped ped, int p1) { return _i<Void>(0xC7622C0D36B2FDA8, ped, p1); }
	static Void set_ped_combat_attributes(Ped ped, int attributeIndex, bool enabled) { return _i<Void>(0x9F7794730795E019, ped, attributeIndex, enabled); }
	static Void set_ped_combat_movement(Ped ped, int combatMovement) { return _i<Void>(0x4D9CA1009AFBD057, ped, combatMovement); }
	static Void set_ped_combat_range(Ped ped, int p1) { return _i<Void>(0x3C606747B23E497B, ped, p1); }
	static Void set_ped_component_variation(Ped ped, int componentId, int drawableId, int textureId, int paletteId) { return _i<Void>(0x262B14F48D29DE80, ped, componentId, drawableId, textureId, paletteId); }
	static Void set_ped_config_flag(Ped ped, int flagId, bool value) { return _i<Void>(0x1913FE4CBF41C463, ped, flagId, value); }
	static Void set_ped_coords_keep_vehicle(Ped ped, float posX, float posY, float posZ) { return _i<Void>(0x9AFEFF481A85AB2E, ped, posX, posY, posZ); }
	static Void set_ped_coords_no_gang(Ped ped, float posX, float posY, float posZ) { return _i<Void>(0x87052FE446E07247, ped, posX, posY, posZ); }
	static Void set_ped_cower_hash(Ped ped, const char* p1) { return _i<Void>(0xA549131166868ED3, ped, p1); }
	static Void set_ped_default_component_variation(Ped ped) { return _i<Void>(0x45EEE61580806D63, ped); }
	static Void set_ped_defensive_area_attached_to_ped(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9, bool p10) { return _i<Void>(0x4EF47FE21698A8B6, ped, attachPed, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static Void set_ped_defensive_area_direction(Ped ped, float p1, float p2, float p3, bool p4) { return _i<Void>(0x413C6C763A4AFFAD, ped, p1, p2, p3, p4); }
	static Void set_ped_defensive_sphere_attached_to_ped(Ped ped, Ped target, float xOffset, float yOffset, float zOffset, float radius, bool p6) { return _i<Void>(0xF9B8F91AAD3B953E, ped, target, xOffset, yOffset, zOffset, radius, p6); }
	static Void _0xE4723DB6E736CCFF(Ped ped, Any p1, float p2, float p3, float p4, float p5, bool p6) { return _i<Void>(0xE4723DB6E736CCFF, ped, p1, p2, p3, p4, p5, p6); }
	static Void set_ped_density_multiplier_this_frame(float multiplier) { return _i<Void>(0x95E3D6257B166CF2, multiplier); }
	static Void set_ped_desired_heading(Ped ped, float heading) { return _i<Void>(0xAA5A7ECE2AA8FE70, ped, heading); }
	static Void set_ped_dies_instantly_in_water(Ped ped, bool toggle) { return _i<Void>(0xEEB64139BA29A7CF, ped, toggle); }
	static Void set_ped_dies_in_sinking_vehicle(Ped ped, bool toggle) { return _i<Void>(0xD718A22995E2B4BC, ped, toggle); }
	static Void set_ped_dies_in_vehicle(Ped ped, bool toggle) { return _i<Void>(0x2A30922C90C9B42C, ped, toggle); }
	static Void set_ped_dies_in_water(Ped ped, bool toggle) { return _i<Void>(0x56CEF0AC79073BDE, ped, toggle); }
	static Void set_ped_dies_when_injured(Ped ped, bool toggle) { return _i<Void>(0x5BA7919BED300023, ped, toggle); }
	static Void set_ped_drive_by_clipset_override(Ped ped, const char* clipset) { return _i<Void>(0xED34AB6C5CB36520, ped, clipset); }
	static Void set_ped_ducking(Ped ped, bool toggle) { return _i<Void>(0x030983CA930B692D, ped, toggle); }
	static Void _0x4E90D746056E273D(Any p0, Any p1) { return _i<Void>(0x4E90D746056E273D, p0, p1); }
	static Void _0xE906EC930F5FE7C8(Any p0, Any p1) { return _i<Void>(0xE906EC930F5FE7C8, p0, p1); }
	static Void set_ped_enable_weapon_blocking(Ped ped, bool toggle) { return _i<Void>(0x97A790315D3831FD, ped, toggle); }
	static Void _0xD69411AA0CEBF9E9(Ped ped, int p1, int p2, int p3) { return _i<Void>(0xD69411AA0CEBF9E9, ped, p1, p2, p3); }
	static Void _0x110F526AB784111F(Ped ped, float p1) { return _i<Void>(0x110F526AB784111F, ped, p1); }
	static Void set_ped_enveff_scale(Ped ped, float value) { return _i<Void>(0xBF29516833893561, ped, value); }
	static Void set_ped_firing_pattern(Ped ped, uint32_t patternHash) { return _i<Void>(0x9AC577F5A12AD8A9, ped, patternHash); }
	static Void set_ped_flee_attributes(Ped ped, int attributes, bool p2) { return _i<Void>(0x70A2D1137C8ED7C9, ped, attributes, p2); }
	static Void set_ped_generates_dead_body_events(Ped ped, bool toggle) { return _i<Void>(0x7FB17BA2E7DECA5B, ped, toggle); }
	static Void set_ped_gesture_group(Ped ped, const char* animGroupGesture) { return _i<Void>(0xDDF803377F94AAA8, ped, animGroupGesture); }
	static Void set_ped_get_out_upside_down_vehicle(Ped ped, bool toggle) { return _i<Void>(0xBC0ED94165A48BC2, ped, toggle); }
	static Void set_ped_gravity(Ped ped, bool toggle) { return _i<Void>(0x9FF447B6B6AD960A, ped, toggle); }
	static Void set_ped_group_member_passenger_index(Ped ped, int index) { return _i<Void>(0x0BDDB8D9EC6BCF3C, ped, index); }
	static Void set_ped_hair_color(Ped ped, int colorID, int highlightColorID) { return _i<Void>(0x4CFFC65454C93A49, ped, colorID, highlightColorID); }
	static Void set_ped_head_blend_data(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, bool isParent) { return _i<Void>(0x9414E18B9434C2FE, ped, shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix, isParent); }
	static Void set_ped_head_overlay(Ped ped, int overlayID, int index, float opacity) { return _i<Void>(0x48F44967FA05CC1E, ped, overlayID, index, opacity); }
	static Void set_ped_head_overlay_color(Ped ped, int overlayID, int colorType, int colorID, int secondColorID) { return _i<Void>(0x497BF74A7B9CB952, ped, overlayID, colorType, colorID, secondColorID); }
	static Void set_ped_hearing_range(Ped ped, float value) { return _i<Void>(0x33A8F7F7D5F7F33C, ped, value); }
	static Void _0xC1F6EBF9A3D55538(Any p0, Any p1) { return _i<Void>(0xC1F6EBF9A3D55538, p0, p1); }
	static Void set_ped_helmet(Ped ped, bool canWearHelmet) { return _i<Void>(0x560A43136EB58105, ped, canWearHelmet); }
	static Void set_ped_helmet_flag(Ped ped, int helmetFlag) { return _i<Void>(0xC0E78D5C2CE3EB25, ped, helmetFlag); }
	static Void set_ped_helmet_prop_index(Ped ped, int propIndex, Any p2) { return _i<Void>(0x26D83693ED99291C, ped, propIndex, p2); }
	static Void set_ped_helmet_texture_index(Ped ped, int textureIndex) { return _i<Void>(0xF1550C4BD22582E2, ped, textureIndex); }
	static Void _0x3F7325574E41B44D(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x3F7325574E41B44D, p0, p1, p2, p3); }
	static Void _0x52D59AB61DDC05DD(Ped ped, bool p1) { return _i<Void>(0x52D59AB61DDC05DD, ped, p1); }
	static Void set_ped_id_range(Ped ped, float value) { return _i<Void>(0xF107E836A70DCE05, ped, value); }
	static Void _0x570389D1C3DE3C6B(Any p0) { return _i<Void>(0x570389D1C3DE3C6B, p0); }
	static Void _0xEC4B4B3B9908052A(Ped ped, float unk) { return _i<Void>(0xEC4B4B3B9908052A, ped, unk); }
	static Void set_ped_into_vehicle(Ped ped, Vehicle vehicle, int seatIndex) { return _i<Void>(0xF75B0D629E1C063D, ped, vehicle, seatIndex); }
	static Void set_ped_in_vehicle_context(Ped ped, uint32_t context) { return _i<Void>(0x530071295899A8C6, ped, context); }
	static Void _0xA9B61A329BFDCBEA(Any p0, bool p1) { return _i<Void>(0xA9B61A329BFDCBEA, p0, p1); }
	static Void _0x33A60D8BDD6E508C(Ped ped, bool p1) { return _i<Void>(0x33A60D8BDD6E508C, ped, p1); }
	static Void set_ped_keep_task(Ped ped, bool toggle) { return _i<Void>(0x971D38760FBC02EF, ped, toggle); }
	static Void set_ped_leg_ik_mode(Ped ped, int mode) { return _i<Void>(0xC396F5B86FF9FEBD, ped, mode); }
	static Void set_ped_lod_multiplier(Ped ped, float multiplier) { return _i<Void>(0xDC2C5C242AAC342B, ped, multiplier); }
	static Void set_ped_max_health(Ped ped, int value) { return _i<Void>(0xF5F6378C4F3419D3, ped, value); }
	static Void set_ped_max_move_blend_ratio(Ped ped, float value) { return _i<Void>(0x433083750C5E064A, ped, value); }
	static Void set_ped_max_time_in_water(Ped ped, float value) { return _i<Void>(0x43C851690662113D, ped, value); }
	static Void set_ped_max_time_underwater(Ped ped, float value) { return _i<Void>(0x6BA428C528D9E522, ped, value); }
	static Void set_ped_face_feature(Ped ped, int index, float scale) { return _i<Void>(0x71A5C1DBA060049E, ped, index, scale); }
	static Void set_ped_min_ground_time_for_stungun(Ped ped, int ms) { return _i<Void>(0xFA0675AB151073FA, ped, ms); }
	static Void set_ped_min_move_blend_ratio(Ped ped, float value) { return _i<Void>(0x01A898D26E2333DD, ped, value); }
	static Void set_ped_model_is_suppressed(Ped ped, bool toggle) { return _i<Void>(0xE163A4BCE4DE6F11, ped, toggle); }
	static Void set_ped_money(Ped ped, int amount) { return _i<Void>(0xA9C8960E8684C1B5, ped, amount); }
	static Void set_ped_motion_blur(Ped ped, bool toggle) { return _i<Void>(0x0A986918B102B448, ped, toggle); }
	static Void _0x9DBA107B4937F809(Any p0, const char* p1) { return _i<Void>(0x9DBA107B4937F809, p0, p1); }
	static Void set_ped_movement_clipset(Ped ped, const char* clipSet, float p2) { return _i<Void>(0xAF8A94EDE7712BEF, ped, clipSet, p2); }
	static Void set_ped_move_anims_blend_out(Ped ped) { return _i<Void>(0x9E8C908F41584ECD, ped); }
	static Void _0x0B3E35AC043707D9(Any p0, Any p1) { return _i<Void>(0x0B3E35AC043707D9, p0, p1); }
	static Void set_ped_move_rate_override(Ped ped, float value) { return _i<Void>(0x085BF80FA50A39D1, ped, value); }
	static Void set_ped_never_leaves_group(Ped ped, bool toggle) { return _i<Void>(0x3DBFC55D5C9BB447, ped, toggle); }
	static Void set_ped_non_creation_area(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<Void>(0xEE01041D559983EA, x1, y1, z1, x2, y2, z2); }
	static Void _0xA52D5247A4227E14(Any p0) { return _i<Void>(0xA52D5247A4227E14, p0); }
	static Any _0xFE07FF6495D52E2A(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xFE07FF6495D52E2A, p0, p1, p2, p3); }
	static Void set_ped_parachute_tint_index(Ped ped, int tintIndex) { return _i<Void>(0x333FC8DB079B7186, ped, tintIndex); }
	static Void _0x83A169EABCDB10A2(Any p0, Any p1) { return _i<Void>(0x83A169EABCDB10A2, p0, p1); }
	static Any set_ped_pinned_down(Ped ped, bool pinned, int i) { return _i<Any>(0xAAD6D1ACF08F4612, ped, pinned, i); }
	static Void set_ped_preferred_cover_set(Ped ped, Any itemSet) { return _i<Void>(0x8421EB4DA7E391B9, ped, itemSet); }
	static bool is_ped_prop_valid(Ped ped, int componentId, int drawableId, int TextureId) { return _i<bool>(0x2B16A3BFF1FBCE49, ped, componentId, drawableId, TextureId); }
	static Any _0x39D55A620FCB6A3A(Ped ped, int p1, int drawableId, int textureId) { return _i<Any>(0x39D55A620FCB6A3A, ped, p1, drawableId, textureId); }
	static Void set_ped_primary_lookat(Ped ped, Ped lookAt) { return _i<Void>(0xCD17B554996A8D9E, ped, lookAt); }
	static Void set_ped_prop_index(Ped ped, int componentId, int drawableId, int TextureId, bool attach) { return _i<Void>(0x93376B65A266EB5F, ped, componentId, drawableId, TextureId, attach); }
	static Void set_ped_ragdoll_force_fall(Ped ped) { return _i<Void>(0x01F6594B923B9251, ped); }
	static Void set_ped_ragdoll_on_collision(Ped ped, bool toggle) { return _i<Void>(0xF0A4F1BBF4FA7497, ped, toggle); }
	static Void set_ped_random_component_variation(Ped ped, bool p1) { return _i<Void>(0xC8A9481A01E63C28, ped, p1); }
	static Void set_ped_random_props(Ped ped) { return _i<Void>(0xC44AA05345C992C6, ped); }
	static Void set_ped_relationship_group_default_hash(Ped ped, uint32_t hash) { return _i<Void>(0xADB3F206518799E8, ped, hash); }
	static Void set_ped_relationship_group_hash(Ped ped, uint32_t hash) { return _i<Void>(0xC80A74AC829DDD92, ped, hash); }
	static Void set_ped_reserve_parachute_tint_index(Ped ped, Any p1) { return _i<Void>(0xE88DA0751C22A2AD, ped, p1); }
	static Void set_ped_reset_flag(Ped ped, int flagId, bool doReset) { return _i<Void>(0xC1E8A365BF3B29F2, ped, flagId, doReset); }
	static Void _0x36C6984C3ED0C911(Any p0) { return _i<Void>(0x36C6984C3ED0C911, p0); }
	static Void set_ped_seeing_range(Ped ped, float value) { return _i<Void>(0xF29CF591C4BF6CEE, ped, value); }
	static Void set_ped_shoots_at_coord(Ped ped, float x, float y, float z, bool toggle) { return _i<Void>(0x96A05E4FB321B1BA, ped, x, y, z, toggle); }
	static Void set_ped_shoot_rate(Ped ped, int shootRate) { return _i<Void>(0x614DA022990752DC, ped, shootRate); }
	static Void _0x425AECF167663F48(Ped ped, bool p1) { return _i<Void>(0x425AECF167663F48, ped, p1); }
	static Void _0x5B6010B3CBC29095(Any p0, bool p1) { return _i<Void>(0x5B6010B3CBC29095, p0, p1); }
	static Any _0xEC6935EBE0847B90(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xEC6935EBE0847B90, p0, p1, p2, p3); }
	static Any _0xEEED8FAFEC331A70(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0xEEED8FAFEC331A70, p0, p1, p2, p3); }
	static Void _0xF1C03A5352243A30(Any p0) { return _i<Void>(0xF1C03A5352243A30, p0); }
	static Void _0xA3A9299C4F2ADB98(Any p0) { return _i<Void>(0xA3A9299C4F2ADB98, p0); }
	static Void _0xCEDA60A74219D064(Any p0, bool p1) { return _i<Void>(0xCEDA60A74219D064, p0, p1); }
	static Void set_ped_sphere_defensive_area(Ped ped, float x, float y, float z, float radius, bool p5, bool p6) { return _i<Void>(0x9D3151A373974804, ped, x, y, z, radius, p5, p6); }
	static Void set_ped_stay_in_vehicle_when_jacked(Ped ped, bool toggle) { return _i<Void>(0xEDF4079F9D54C9A1, ped, toggle); }
	static Void set_ped_stealth_movement(Ped ped, bool p1, const char* action) { return _i<Void>(0x88CBB5CEB96B7BD2, ped, p1, action); }
	static Void _0x2016C603D6B8987C(Any p0, bool p1) { return _i<Void>(0x2016C603D6B8987C, p0, p1); }
	static Void set_ped_steers_around_objects(Ped ped, bool toggle) { return _i<Void>(0x1509C089ADC208BF, ped, toggle); }
	static Void set_ped_steers_around_peds(Ped ped, bool toggle) { return _i<Void>(0x46F2193B3AD1D891, ped, toggle); }
	static Void set_ped_steers_around_vehicles(Ped ped, bool toggle) { return _i<Void>(0xEB6FB9D48DDE23EC, ped, toggle); }
	static Void _0x288DF530C92DAD6F(Any p0, float p1) { return _i<Void>(0x288DF530C92DAD6F, p0, p1); }
	static Void set_ped_strafe_clipset(Ped ped, const char* clipSet) { return _i<Void>(0x29A28F3F8CF6D854, ped, clipSet); }
	static Void set_ped_suffers_critical_hits(Ped ped, bool toggle) { return _i<Void>(0xEBD76F2359F190AC, ped, toggle); }
	static Void set_ped_sweat(Ped ped, float sweat) { return _i<Void>(0x27B0405F59637D1F, ped, sweat); }
	static Void set_ped_target_loss_response(Ped ped, int responseType) { return _i<Void>(0x0703B9079823DA4A, ped, responseType); }
	static Void set_ped_to_inform_respected_friends(Ped ped, float radius, int maxFriends) { return _i<Void>(0x112942C6E708F70B, ped, radius, maxFriends); }
	static Void set_ped_to_load_cover(Ped ped, bool toggle) { return _i<Void>(0x332B562EEDA62399, ped, toggle); }
	static bool set_ped_to_ragdoll(Ped ped, int time1, int time2, int ragdollType, bool p4, bool p5, bool p6) { return _i<bool>(0xAE99FB955581844A, ped, time1, time2, ragdollType, p4, p5, p6); }
	static bool set_ped_to_ragdoll_with_fall(Ped ped, int time, int p2, int ragdollType, float x, float y, float z, float p7, float p8, float p9, float p10, float p11, float p12, float p13) { return _i<bool>(0xD76632D99E4966C8, ped, time, p2, ragdollType, x, y, z, p7, p8, p9, p10, p11, p12, p13); }
	static Void _0x0F62619393661D6E(Any p0, Any p1, Any p2) { return _i<Void>(0x0F62619393661D6E, p0, p1, p2); }
	static Void _0xAFC976FD0580C7B3(Ped ped, bool toggle) { return _i<Void>(0xAFC976FD0580C7B3, ped, toggle); }
	static Void set_ped_using_action_mode(Ped ped, bool p1, Any p2, const char* action) { return _i<Void>(0xD75ACCF5E0FB5367, ped, p1, p2, action); }
	static Void _0x952F06BEECD775CC(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x952F06BEECD775CC, p0, p1, p2, p3); }
	static Void set_ped_visual_field_center_angle(Ped ped, float angle) { return _i<Void>(0x3B6405E8AB34A907, ped, angle); }
	static Void set_ped_visual_field_max_angle(Ped ped, float value) { return _i<Void>(0x70793BDCA1E854D4, ped, value); }
	static Void set_ped_visual_field_max_elevation_angle(Ped ped, float angle) { return _i<Void>(0x78D0B67629D75856, ped, angle); }
	static Void set_ped_visual_field_min_angle(Ped ped, float value) { return _i<Void>(0x2DB492222FB21E26, ped, value); }
	static Void set_ped_visual_field_min_elevation_angle(Ped ped, float angle) { return _i<Void>(0x7A276EB2C224D70F, ped, angle); }
	static Void set_ped_visual_field_peripheral_range(Ped ped, float range) { return _i<Void>(0x9C74B0BC831B753A, ped, range); }
	static Void set_ped_weapon_movement_clipset(Ped ped, const char* clipSet) { return _i<Void>(0x2622E35B77D3ACA2, ped, clipSet); }
	static Void set_ped_wetness_enabled_this_frame(Ped ped) { return _i<Void>(0xB5485E4907B53019, ped); }
	static Void set_ped_wetness_height(Ped ped, float height) { return _i<Void>(0x44CB6447D2571AA0, ped, height); }
	static Void _0x3E9679C1DFCF422C(Any p0, Any p1) { return _i<Void>(0x3E9679C1DFCF422C, p0, p1); }
	static Void _0xD8C3BE3EE94CAF2D(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xD8C3BE3EE94CAF2D, p0, p1, p2, p3, p4); }
	static Void set_ped_ragdoll_blocking_flags(Ped ped, int flags) { return _i<Void>(0x26695EC767728D84, ped, flags); }
	static Void set_relationship_between_groups(int relationship, uint32_t group1, uint32_t group2) { return _i<Void>(0xBF25EB89375A37AD, relationship, group1, group2); }
	static Void _0x5615E0C5EB2BC6E2(Any p0, Any p1) { return _i<Void>(0x5615E0C5EB2BC6E2, p0, p1); }
	static Void set_scenario_peds_spawn_in_sphere_area(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x28157D43CF600981, p0, p1, p2, p3, p4); }
	static Void set_scenario_peds_to_be_returned_by_next_command(bool value) { return _i<Void>(0x14F19A8782C8071E, value); }
	static Void set_scenario_ped_density_multiplier_this_frame(float p0, float p1) { return _i<Void>(0x7A556143A1C03898, p0, p1); }
	static Void set_scripted_anim_seat_offset(Ped ped, float p1) { return _i<Void>(0x5917BBA32D06C230, ped, p1); }
	static Void set_scripted_conversion_coord_this_frame(float x, float y, float z) { return _i<Void>(0x5086C7843552CF85, x, y, z); }
	static Void set_synchronized_scene_occlusion_portal(Any sceneID, bool p1) { return _i<Void>(0x394B9CD12435C981, sceneID, p1); }
	static Void set_synchronized_scene_looped(int sceneID, bool toggle) { return _i<Void>(0xD9A897A4C6C2974F, sceneID, toggle); }
	static Void set_synchronized_scene_origin(int sceneID, float x, float y, float z, float roll, float pitch, float yaw, bool p7) { return _i<Void>(0x6ACF6B7225801CD7, sceneID, x, y, z, roll, pitch, yaw, p7); }
	static Void set_synchronized_scene_phase(int sceneID, float phase) { return _i<Void>(0x734292F4F0ABF6D0, sceneID, phase); }
	static Void set_synchronized_scene_rate(int sceneID, float rate) { return _i<Void>(0xB6C49F8A5E295A5D, sceneID, rate); }
	static Void _0x2F3C3D9F50681DE4(Any p0, bool p1) { return _i<Void>(0x2F3C3D9F50681DE4, p0, p1); }
	static Void _0xFD325494792302D7(Any p0, bool p1) { return _i<Void>(0xFD325494792302D7, p0, p1); }
	static Void _0xFEE4A5459472A9F8() { return _i<Void>(0xFEE4A5459472A9F8); }
	static Any _0xA635C11B8C44AFC2() { return _i<Any>(0xA635C11B8C44AFC2); }
	static Void _0x280C7E3AC7F56E90(Any p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0x280C7E3AC7F56E90, p0, p1, p2, p3); }
	static Void _0xB782F8238512BAD5(Any p0, Any* p1) { return _i<Void>(0xB782F8238512BAD5, p0, p1); }
	static Any _0x3C67506996001F5E() { return _i<Any>(0x3C67506996001F5E); }
	static Any _0xA586FBEB32A53DBB() { return _i<Any>(0xA586FBEB32A53DBB); }
	static Any _0xF445DE8DA80A1792() { return _i<Any>(0xF445DE8DA80A1792); }
	static Void _0x2DF9038C90AD5264(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration) { return _i<Void>(0x2DF9038C90AD5264, p0, p1, p2, p3, p4, interiorFlags, scale, duration); }
	static Void _0xB2AFF10216DEFA2F(float x, float y, float z, float p3, float p4, float p5, float p6, int interiorFlags, float scale, int duration) { return _i<Void>(0xB2AFF10216DEFA2F, x, y, z, p3, p4, p5, p6, interiorFlags, scale, duration); }
	static Void _0xF9ACF4A08098EA25(Ped ped, bool p1) { return _i<Void>(0xF9ACF4A08098EA25, ped, p1); }
	static Void stop_any_ped_model_being_suppressed() { return _i<Void>(0xB47BD05FA66B40CF); }
	static Void stop_ped_weapon_firing_when_dropped(Ped ped) { return _i<Void>(0xC158D28142A34608, ped); }
	static Void _0x5A7F62FDA59759BD() { return _i<Void>(0x5A7F62FDA59759BD); }
	static Void dispose_synchronized_scene(int scene) { return _i<Void>(0xCD9CC7E200A52A6F, scene); }
	static Void _0x9A77DFD295E29B09(Any p0, bool p1) { return _i<Void>(0x9A77DFD295E29B09, p0, p1); }
	static Void _0xC2EE020F5FB4DB53(Ped ped) { return _i<Void>(0xC2EE020F5FB4DB53, ped); }
	static Any _0x25361A96E0F7E419(Any p0, Any p1, Any p2, Any p3) { return _i<Any>(0x25361A96E0F7E419, p0, p1, p2, p3); }
	static Void unregister_pedheadshot(int handle) { return _i<Void>(0x96B1361D9B24C2FF, handle); }
	static Void update_ped_head_blend_data(Ped ped, float shapeMix, float skinMix, float thirdMix) { return _i<Void>(0x723538F61C647C5A, ped, shapeMix, skinMix, thirdMix); }
	static bool was_ped_killed_by_stealth(Ped ped) { return _i<bool>(0xF9800AA1A771B000, ped); }
	static bool was_ped_killed_by_takedown(Ped ped) { return _i<bool>(0x7F08E26039C7347C, ped); }
	static bool _0x61767F73EACEED21(Ped ped) { return _i<bool>(0x61767F73EACEED21, ped); }
	static bool was_ped_skeleton_updated(Ped ped) { return _i<bool>(0x11B499C1E0FF8559, ped); }
	static Void _0xB282749D5E028163(Any p0, Any p1) { return _i<Void>(0xB282749D5E028163, p0, p1); }
	static Void set_ped_name_debug(Ped ped, const char* name) { return _i<Void>(0x98EFA132A4117BE1, ped, name); }
	static Void set_ped_plays_head_on_horn_aniwhen_dies_in_vehicle(Ped ped, bool toggle) { return _i<Void>(0x94D94BF1A75AED3D, ped, toggle); }
	static Void _0x1216E0BFA72CC703(Any p0, Any p1) { return _i<Void>(0x1216E0BFA72CC703, p0, p1); }

	static Void activate_physics(Entity entity) { return _i<Void>(0x710311ADF0E20730, entity); }
	static Object add_rope(float x, float y, float z, float rotX, float rotY, float rotZ, float length, int ropeType, float maxLength, float minLength, float p10, bool p11, bool p12, bool rigid, float p14, bool breakWhenShot, Any* unkPtr) { return _i<Object>(0xE832D760399EB220, x, y, z, rotX, rotY, rotZ, length, ropeType, maxLength, minLength, p10, p11, p12, rigid, p14, breakWhenShot, unkPtr); }
	static Void apply_impulse_to_cloth(float posX, float posY, float posZ, float vecX, float vecY, float vecZ, float impulse) { return _i<Void>(0xE37F721824571784, posX, posY, posZ, vecX, vecY, vecZ, impulse); }
	static Void attach_entities_to_rope(Object rope, Entity ent1, Entity ent2, float ent1_x, float ent1_y, float ent1_z, float ent2_x, float ent2_y, float ent2_z, float length, bool p10, bool p11, Any* p12, Any* p13) { return _i<Void>(0x3D95EC8B6D940AC3, rope, ent1, ent2, ent1_x, ent1_y, ent1_z, ent2_x, ent2_y, ent2_z, length, p10, p11, p12, p13); }
	static Void attach_rope_to_entity(Object rope, Entity entity, float x, float y, float z, bool p5) { return _i<Void>(0x4B490A6832559A65, rope, entity, x, y, z, p5); }
	static Void break_entity_glass(Any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, Any p9, bool p10) { return _i<Void>(0x2E648D16F6E308F3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static Void delete_child_rope(Object rope) { return _i<Void>(0xAA5D6B1888E4DB20, rope); }
	static Void delete_rope(Object* rope) { return _i<Void>(0x52B4829281364649, rope); }
	static Void detach_rope_from_entity(Object rope, Entity entity) { return _i<Void>(0xBCF3026912A8647D, rope, entity); }
	static bool does_rope_exist(Object* rope) { return _i<bool>(0xFD5448BE3111ED96, rope); }
	static bool _0x271C9D3ACA5D6409(Object rope) { return _i<bool>(0x271C9D3ACA5D6409, rope); }
	static math::vector3<float> get_cgoffset(Object rope) { return _i<math::vector3<float>>(0x8214A4B5A7A33612, rope); }
	static Any _0x0C112765300C7E1E(Any p0) { return _i<Any>(0x0C112765300C7E1E, p0); }
	static math::vector3<float> get_rope_last_vertex_coord(Object rope) { return _i<math::vector3<float>>(0x21BB0FBD3E217C2D, rope); }
	static math::vector3<float> get_rope_vertex_coord(Object rope, int vertex) { return _i<math::vector3<float>>(0xEA61CA8E80F09E4D, rope, vertex); }
	static int get_rope_vertex_count(Object rope) { return _i<int>(0x3655F544CD30F0B5, rope); }
	static bool _0x84DE3B5FB3E666F0(Any* p0) { return _i<bool>(0x84DE3B5FB3E666F0, p0); }
	static Void load_rope_data(Object rope, const char* rope_preset) { return _i<Void>(0xCBB203C04D1ABD27, rope, rope_preset); }
	static Void pin_rope_vertex(Object rope, int vertex, float x, float y, float z) { return _i<Void>(0x2B320CF14146B69A, rope, vertex, x, y, z); }
	static Void _0xCC6E963682533882(Any p0) { return _i<Void>(0xCC6E963682533882, p0); }
	static bool rope_are_textures_loaded() { return _i<bool>(0xF2D0E6A75CC05597); }
	static Void _0xBC0CE682D4D05650(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { return _i<Void>(0xBC0CE682D4D05650, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	static Void _0xB1B6216CA2E7B55E(Any p0, bool p1, bool p2) { return _i<Void>(0xB1B6216CA2E7B55E, p0, p1, p2); }
	static Void rope_convert_to_simple(Object rope) { return _i<Void>(0x5389D48EFA2F079A, rope); }
	static Void rope_draw_shadow_enabled(Object* rope, bool toggle) { return _i<Void>(0xF159A63806BB5BA8, rope, toggle); }
	static Void rope_force_length(Object rope, float length) { return _i<Void>(0xD009F759A723DB1B, rope, length); }
	static float get_rope_length(Object rope) { return _i<float>(0x73040398DFF9A4A6, rope); }
	static Void rope_load_textures() { return _i<Void>(0x9B9039DBF2D258C1); }
	static Void rope_reset_length(Object rope, bool length) { return _i<Void>(0xC16DE94D9BEA14A0, rope, length); }
	static Void _0xB743F735C03D7810(Any p0, Any p1) { return _i<Void>(0xB743F735C03D7810, p0, p1); }
	static Void _0x36CCB9BE67B970FD(Any p0, bool p1) { return _i<Void>(0x36CCB9BE67B970FD, p0, p1); }
	static Void _0xDC57A637A20006ED(Any p0, Any p1) { return _i<Void>(0xDC57A637A20006ED, p0, p1); }
	static Void rope_set_update_pinverts(Object rope) { return _i<Void>(0xC8D667EE52114ABA, rope); }
	static Void rope_unload_textures() { return _i<Void>(0x6CE36C35C1AC8163); }
	static Void set_cgoffset(Object rope, float x, float y, float z) { return _i<Void>(0xD8FA3908D7B86904, rope, x, y, z); }
	static Void set_cg_at_boundcenter(Object rope) { return _i<Void>(0xBE520D9761FF811F, rope); }
	static Void set_damping(Object rope, int vertex, float value) { return _i<Void>(0xEEA3B200A6FEB65B, rope, vertex, value); }
	static Void set_disable_breaking(Object rope, bool enabled) { return _i<Void>(0x5CEC1A84620E7D5B, rope, enabled); }
	static Void set_disable_frag_damage(Object object, bool toggle) { return _i<Void>(0x01BA3AED21C16CFB, object, toggle); }
	static Void _0x9EBD751E5787BAF2(Any p0) { return _i<Void>(0x9EBD751E5787BAF2, p0); }
	static Void _0x15F944730C832252(Any p0, Any p1) { return _i<Void>(0x15F944730C832252, p0, p1); }
	static Void start_rope_unwinding_front(Object rope) { return _i<Void>(0x538D1179EC1AA9A9, rope); }
	static Void start_rope_winding(Object rope) { return _i<Void>(0x1461C72C889E343E, rope); }
	static Void stop_rope_unwinding_front(Object rope) { return _i<Void>(0xFFF3A50779EFBBB3, rope); }
	static Void stop_rope_winding(Object rope) { return _i<Void>(0xCB2D4AB84A19AA7C, rope); }
	static Void unpin_rope_vertex(Object rope, int vertex) { return _i<Void>(0x4B5AE2EEE4A8F180, rope, vertex); }

	static Player int_to_playerindex(int value) { return _i<Player>(0x41BD2A6B006AF756, value); }
	static int int_to_participantindex(int value) { return _i<int>(0x9EC6603812C24710, value); }
	static Void _0x2F41A3BAE005E5FA(Any p0, Any p1) { return _i<Void>(0x2F41A3BAE005E5FA, p0, p1); }
	static bool are_player_flashing_stars_about_to_drop(Player player) { return _i<bool>(0xAFAF86043E5874E9, player); }
	static bool are_player_stars_greyed_out(Player player) { return _i<bool>(0x0A6EB355EE14A2DB, player); }
	static Void assisted_movement_close_route() { return _i<Void>(0xAEBF081FFC0A0E5E); }
	static Void assisted_movement_flush_route() { return _i<Void>(0x8621390F0CDCFE1F); }
	static bool can_ped_hear_player(Player player, Ped ped) { return _i<bool>(0xF297383AA91DCA29, player, ped); }
	static bool can_player_start_mission(Player player) { return _i<bool>(0xDE7465A27D403C06, player); }
	static Void change_player_ped(Player player, Ped ped, bool b2, bool b3) { return _i<Void>(0x048189FAC643DEEE, player, ped, b2, b3); }
	static Void clear_player_has_damaged_at_least_one_non_animal_ped(Player player) { return _i<Void>(0x4AACB96203D11A31, player); }
	static Void clear_player_has_damaged_at_least_one_ped(Player player) { return _i<Void>(0xF0B67A4DE6AB5F98, player); }
	static Void clear_player_parachute_model_override(Player player) { return _i<Void>(0x8753997EB5F6EE3F, player); }
	static Void clear_player_parachute_pack_model_override(Player player) { return _i<Void>(0x10C54E4389C12B42, player); }
	static Void clear_player_parachute_variation_override(Player player) { return _i<Void>(0x0F4CC924CF8C7B21, player); }
	static Void clear_player_wanted_level(Player player) { return _i<Void>(0xB302540597885499, player); }
	static Void _0x5501B7A5CDB79D37(Any p0) { return _i<Void>(0x5501B7A5CDB79D37, p0); }
	static Void disable_player_firing(Player player, bool toggle) { return _i<Void>(0x5E6CC07646BBEAB8, player, toggle); }
	static Void _0xB885852C39CC265D() { return _i<Void>(0xB885852C39CC265D); }
	static Void disable_player_vehicle_rewards(Player player) { return _i<Void>(0xC142BE3BB9CE125F, player); }
	static Void display_system_signin_ui(bool unk) { return _i<Void>(0x94DD7888C10A979E, unk); }
	static Void enable_special_ability(Player player, bool toggle) { return _i<Void>(0x181EC197DAEFE121, player, toggle); }
	static Void expand_world_limits(float x, float y, float z) { return _i<Void>(0x5006D96C995A5827, x, y, z); }
	static Void force_cleanup(int cleanupFlags) { return _i<Void>(0xBC8983F38F78ED51, cleanupFlags); }
	static Void force_cleanup_for_all_threads_with_this_name(const char* name, int cleanupFlags) { return _i<Void>(0x4C68DDDDF0097317, name, cleanupFlags); }
	static Void force_cleanup_for_thread_with_this_id(int id, int cleanupFlags) { return _i<Void>(0xF745B37630DF176B, id, cleanupFlags); }
	static Void _0xAD73CE5A09E42D12(Player player) { return _i<Void>(0xAD73CE5A09E42D12, player); }
	static Cam _0x1C186837D0619335(Any p0) { return _i<Cam>(0x1C186837D0619335, p0); }
	static bool is_player_cam_control_disabled() { return _i<bool>(0x7C814D2FB49F40C0); }
	static int get_cause_of_most_recent_force_cleanup() { return _i<int>(0x9A41CF4674A12272); }
	static bool get_entity_player_is_free_aiming_at(Player player, Entity* entity) { return _i<bool>(0x2975C866E6713290, player, entity); }
	static bool is_player_logging_in_np() { return _i<bool>(0x74556E1420867ECA); }
	static bool _0xDD2620B7B9D16FF1(Player player, float p1) { return _i<bool>(0xDD2620B7B9D16FF1, player, p1); }
	static bool _0x5FC472C501CCADB3(Player player) { return _i<bool>(0x5FC472C501CCADB3, player); }
	static bool _0xF10B44FD479D69F3(Player player, int p1) { return _i<bool>(0xF10B44FD479D69F3, player, p1); }
	static Any _0xB9CF1F793A9F1BF1() { return _i<Any>(0xB9CF1F793A9F1BF1); }
	static Any _0xCB645E85E97EA48B() { return _i<Any>(0xCB645E85E97EA48B); }
	static int get_max_wanted_level() { return _i<int>(0x462E0DB9B137DC5F); }
	static int get_number_of_players() { return _i<int>(0x407C7F91DDB46C16); }
	static Any _0x1FC200409F10E6F1(Any p0) { return _i<Any>(0x1FC200409F10E6F1, p0); }
	static Vehicle get_players_last_vehicle() { return _i<Vehicle>(0xB6997A7EB3F5C8C0); }
	static float get_player_current_stealth_noise(Player player) { return _i<float>(0x2F395D61F3A1F877, player); }
	static Player _0x56105E599CAB0EFA(int* p0) { return _i<Player>(0x56105E599CAB0EFA, p0); }
	static int get_player_group(Player player) { return _i<int>(0x0D127585F77030AF, player); }
	static bool get_player_has_reserve_parachute(Player player) { return _i<bool>(0x5DDFE2FF727F3CA3, player); }
	static Any _0x8BC515BAE4AAF8FF(Any p0) { return _i<Any>(0x8BC515BAE4AAF8FF, p0); }
	static bool get_player_invincible(Player player) { return _i<bool>(0xB721981B2B939E07, player); }
	static int get_player_max_armour(Player player) { return _i<int>(0x92659B4CE1863CB3, player); }
	static const char* get_player_name(Player player) { return _i<const char*>(0x6D0DE6A7B5DA71F8, player); }
	static Void get_player_parachute_pack_tint_index(Player player, int* tintIndex) { return _i<Void>(0x6E9C742F340CE5A2, player, tintIndex); }
	static Void get_player_parachute_smoke_trail_color(Player player, int* r, int* g, int* b) { return _i<Void>(0xEF56DBABD3CD4887, player, r, g, b); }
	static Void get_player_parachute_tint_index(Player player, int* tintIndex) { return _i<Void>(0x75D3F7A1B0D9B145, player, tintIndex); }
	static Ped get_player_ped(Player player) { return _i<Ped>(0x43A66C31C68491C0, player); }
	static Entity get_player_ped_script_index(Player player) { return _i<Entity>(0x50FAC3A3E030A6E1, player); }
	static bool _0xBC0753C9CA14B506(Player player, int p1, bool p2) { return _i<bool>(0xBC0753C9CA14B506, player, p1, p2); }
	static Void get_player_reserve_parachute_tint_index(Player player, int* index) { return _i<Void>(0xD5A016BC3C09CF40, player, index); }
	static Void get_player_rgb_colour(Player player, int* r, int* g, int* b) { return _i<Void>(0xE902EF951DCE178F, player, r, g, b); }
	static float get_player_sprint_stamina_remaining(Player player) { return _i<float>(0x3F9F16F8E65A7ED7, player); }
	static float get_player_sprint_time_remaining(Player player) { return _i<float>(0x1885BC9B108B4C99, player); }
	static bool get_player_target_entity(Player player, Entity* entity) { return _i<bool>(0x13EDE1A5DBF797C9, player, entity); }
	static int get_player_team(Player player) { return _i<int>(0x37039302F4E0A008, player); }
	static float get_player_underwater_time_remaining(Player player) { return _i<float>(0xA1FCF8E6AF40B731, player); }
	static math::vector3<float> get_player_wanted_centre_position(Player player) { return _i<math::vector3<float>>(0x0C92BA89F1AF26F8, player); }
	static int get_player_wanted_level(Player player) { return _i<int>(0xE28E54788CE8F12D, player); }
	static int get_time_since_last_arrest() { return _i<int>(0x5063F92F07C2A316); }
	static int get_time_since_last_death() { return _i<int>(0xC7034807558DDFCA); }
	static int get_time_since_player_drove_against_traffic(Player player) { return _i<int>(0xDB89591E290D9182, player); }
	static int get_time_since_player_drove_on_pavement(Player player) { return _i<int>(0xD559D2BE9E37853B, player); }
	static int get_time_since_player_hit_ped(Player player) { return _i<int>(0xE36A25322DC35F42, player); }
	static int get_time_since_player_hit_vehicle(Player player) { return _i<int>(0x5D35ECF3A81A0EE0, player); }
	static float get_wanted_level_radius(Player player) { return _i<float>(0x085DEB493BE80812, player); }
	static int get_wanted_level_threshold(int wantedLevel) { return _i<int>(0xFDD179EAF45B556C, wantedLevel); }
	static bool give_achievement_to_player(int achievement) { return _i<bool>(0xBEC7076D64130195, achievement); }
	static Void give_player_ragdoll_control(Player player, bool toggle) { return _i<Void>(0x3C49C870E66F0A28, player, toggle); }
	static bool has_achievement_been_passed(int achievement) { return _i<bool>(0x867365E111A3B6EB, achievement); }
	static bool has_force_cleanup_occurred(int cleanupFlags) { return _i<bool>(0xC968670BFACE42D9, cleanupFlags); }
	static bool has_player_been_spotted_in_stolen_vehicle(Player player) { return _i<bool>(0xD705740BB0A1CF4C, player); }
	static bool has_player_damaged_at_least_one_non_animal_ped(Player player) { return _i<bool>(0xE4B90F367BD81752, player); }
	static bool has_player_damaged_at_least_one_ped(Player player) { return _i<bool>(0x20CE80B0C2BF4ACC, player); }
	static bool has_player_left_the_world(Player player) { return _i<bool>(0xD55DDFB47991A294, player); }
	static Void _0x9EDD76E87D5D51BA(Player player) { return _i<Void>(0x9EDD76E87D5D51BA, player); }
	static bool _0x38D28DA81E4E9BF9(Player player) { return _i<bool>(0x38D28DA81E4E9BF9, player); }
	static bool is_player_being_arrested(Player player, bool atArresting) { return _i<bool>(0x388A47C51ABDAC8E, player, atArresting); }
	static bool _0x65FAEE425DE637B0(Player p0) { return _i<bool>(0x65FAEE425DE637B0, p0); }
	static bool is_player_climbing(Player player) { return _i<bool>(0x95E8F73DC65EFB9C, player); }
	static bool is_player_control_on(Player player) { return _i<bool>(0x49C32D60007AFA47, player); }
	static bool is_player_dead(Player player) { return _i<bool>(0x424D4687FA1E5652, player); }
	static bool is_player_free_aiming(Player player) { return _i<bool>(0x2E397FD2ECD37C87, player); }
	static bool is_player_free_aiming_at_entity(Player player, Entity entity) { return _i<bool>(0x3C06B5C839B38F7B, player, entity); }
	static bool is_player_free_for_ambient_task(Player player) { return _i<bool>(0xDCCFD3F106C36AB4, player); }
	static bool is_player_online() { return _i<bool>(0xF25D331DC2627BBC); }
	static bool is_player_playing(Player player) { return _i<bool>(0x5E9564D8246B909A, player); }
	static bool is_player_pressing_horn(Player player) { return _i<bool>(0xFA1E2BF8B10598F9, player); }
	static bool is_player_ready_for_cutscene(Player player) { return _i<bool>(0x908CBECC2CAA3690, player); }
	static bool is_player_riding_train(Player player) { return _i<bool>(0x4EC12697209F2196, player); }
	static bool is_player_script_control_on(Player player) { return _i<bool>(0x8A876A65283DD7D7, player); }
	static bool is_player_targetting_anything(Player player) { return _i<bool>(0x78CFE51896B6B8A4, player); }
	static bool is_player_targetting_entity(Player player, Entity entity) { return _i<bool>(0x7912F7FC4F6264B6, player, entity); }
	static bool is_player_teleport_active() { return _i<bool>(0x02B15662D7F8886F); }
	static Any _0x6E4361FF3E8CD7CA(Any p0) { return _i<Any>(0x6E4361FF3E8CD7CA, p0); }
	static bool is_player_wanted_level_greater(Player player, int wantedLevel) { return _i<bool>(0x238DB2A2C23EE9EF, player, wantedLevel); }
	static bool _0x690A61A6D13583F6(Any p0) { return _i<bool>(0x690A61A6D13583F6, p0); }
	static bool is_special_ability_active(Player player) { return _i<bool>(0x3E5F7FC85D854E15, player); }
	static bool is_special_ability_enabled(Player player) { return _i<bool>(0xB1D200FE26AEF3CB, player); }
	static bool is_special_ability_meter_full(Player player) { return _i<bool>(0x05A1FE504B7F2587, player); }
	static bool is_special_ability_unlocked(uint32_t playerModel) { return _i<bool>(0xC6017F6A6CDFA694, playerModel); }
	static bool is_system_ui_being_displayed() { return _i<bool>(0x5D511E3867C87139); }
	static Any _0x7E07C78925D5FD96(Any p0) { return _i<Any>(0x7E07C78925D5FD96, p0); }
	static Player get_player_index() { return _i<Player>(0xA5EDC40EF369B48D); }
	static Player player_id() { return _i<Player>(0x4F8644AF03D0E0D6); }
	static int network_player_id_to_int() { return _i<int>(0xEE68096F9F37341E); }
	static Void player_attach_virtual_bound(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7) { return _i<Void>(0xED51733DC73AED51, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Void player_detach_virtual_bound() { return _i<Void>(0x1DD5897E2FA6E7C9); }
	static Ped player_ped_id() { return _i<Ped>(0xD80958FC74E988A6); }
	static Void remove_player_helmet(Player player, bool p2) { return _i<Void>(0xF3AC26D3CC576528, player, p2); }
	static Void report_crime(Player player, int crimeType, int wantedLvlThresh) { return _i<Void>(0xE9B09589827545E7, player, crimeType, wantedLvlThresh); }
	static Void _0xDC64D2C53493ED12(Player player) { return _i<Void>(0xDC64D2C53493ED12, player); }
	static Void _0x0032A6DBA562C518() { return _i<Void>(0x0032A6DBA562C518); }
	static Void reset_player_arrest_state(Player player) { return _i<Void>(0x2D03E13C460760D6, player); }
	static Void reset_player_input_gait(Player player) { return _i<Void>(0x19531C47A2ABD691, player); }
	static Void reset_player_stamina(Player player) { return _i<Void>(0xA6F312FCCE9C1DFE, player); }
	static Void reset_wanted_level_difficulty(Player player) { return _i<Void>(0xB9D0DD990DC141DD, player); }
	static Void _0xDA1DF03D5A315F4E() { return _i<Void>(0xDA1DF03D5A315F4E); }
	static Void restore_player_stamina(Player player, float p1) { return _i<Void>(0xA352C1B864CAFD33, player, p1); }
	static bool _0xC2AFFFDABBDC2C5C(Any p0, Any p1) { return _i<bool>(0xC2AFFFDABBDC2C5C, p0, p1); }
	static Void set_air_drag_multiplier_for_players_vehicle(Player player, float multiplier) { return _i<Void>(0xCA7DC8329F0A1E9E, player, multiplier); }
	static Void _0xDE45D1A1EF45EE61(Player player, bool toggle) { return _i<Void>(0xDE45D1A1EF45EE61, player, toggle); }
	static Void _0xC3376F42B1FACCC6(Player player) { return _i<Void>(0xC3376F42B1FACCC6, player); }
	static Void set_all_random_peds_flee(Player player, bool toggle) { return _i<Void>(0x056E0FE8534C2949, player, toggle); }
	static Void set_all_random_peds_flee_this_frame(Player player) { return _i<Void>(0x471D2FF42A94B4F2, player); }
	static Void _0x2382AB11450AE7BA(Any p0, Any p1) { return _i<Void>(0x2382AB11450AE7BA, p0, p1); }
	static Void set_auto_give_parachute_when_enter_plane(Player player, bool toggle) { return _i<Void>(0x9F343285A00B4BB6, player, toggle); }
	static Void _0xD2B315B6689D537D(Player player, bool p1) { return _i<Void>(0xD2B315B6689D537D, player, p1); }
	static Void set_disable_ambient_melee_move(Player player, bool toggle) { return _i<Void>(0x2E8AABFA40A84F8C, player, toggle); }
	static Void set_dispatch_cops_for_player(Player player, bool toggle) { return _i<Void>(0xDB172424876553F4, player, toggle); }
	static Void set_everyone_ignore_player(Player player, bool toggle) { return _i<Void>(0x8EEDA153AD141BA4, player, toggle); }
	static Void set_ignore_low_priority_shocking_events(Player player, bool toggle) { return _i<Void>(0x596976B02B6B5700, player, toggle); }
	static Void _0xFAC75988A7D078D3(Any p0) { return _i<Void>(0xFAC75988A7D078D3, p0); }
	static Void _0xB45EFF719D8427A6(float p0) { return _i<Void>(0xB45EFF719D8427A6, p0); }
	static Void set_max_wanted_level(int maxWantedLevel) { return _i<Void>(0xAA5F02DB48D704B9, maxWantedLevel); }
	static Void _0x5DC40A8869C22141(bool p0, ScrHandle p1) { return _i<Void>(0x5DC40A8869C22141, p0, p1); }
	static Void set_player_can_be_hassled_by_gangs(Player player, bool toggle) { return _i<Void>(0xD5E460AD7020A246, player, toggle); }
	static Void _0xCAC57395B151135F(Player player, bool p1) { return _i<Void>(0xCAC57395B151135F, player, p1); }
	static Void _0x55FCC0C390620314(Any p0, Any p1, Any p2) { return _i<Void>(0x55FCC0C390620314, p0, p1, p2); }
	static Void set_player_can_do_drive_by(Player player, bool toggle) { return _i<Void>(0x6E8834B52EC20C77, player, toggle); }
	static Void set_player_can_leave_parachute_smoke_trail(Player player, bool enabled) { return _i<Void>(0xF401B182DBA8AF53, player, enabled); }
	static Void set_player_can_use_cover(Player player, bool toggle) { return _i<Void>(0xD465A8599DFF6814, player, toggle); }
	static Void set_player_cloth_lock_counter(int value) { return _i<Void>(0x14D913B777DFF5DA, value); }
	static Void set_player_cloth_package_index(int index) { return _i<Void>(0x9F7BBA2EA6372500, index); }
	static Void set_player_cloth_pin_frames(Player player, bool toggle) { return _i<Void>(0x749FADDF97DFE930, player, toggle); }
	static Void set_player_control(Player player, bool toggle, int possiblyFlags) { return _i<Void>(0x8D32347D6D4C40A2, player, toggle, possiblyFlags); }
	static Void _0xD821056B9ACF8052(Any p0, Any p1) { return _i<Void>(0xD821056B9ACF8052, p0, p1); }
	static Void _0xEFD79FA81DFBA9CB(Any p0, Any p1) { return _i<Void>(0xEFD79FA81DFBA9CB, p0, p1); }
	static Void set_player_forced_aim(Player player, bool toggle) { return _i<Void>(0x0FEE4F80AC44A726, player, toggle); }
	static Void set_player_forced_zoom(Player player, bool toggle) { return _i<Void>(0x75E7D505F2B15902, player, toggle); }
	static Void set_player_force_skip_aim_intro(Player player, bool toggle) { return _i<Void>(0x7651BC64AE59E128, player, toggle); }
	static Void set_player_has_reserve_parachute(Player player) { return _i<Void>(0x7DDAB28D31FAC363, player); }
	static Void _0xC388A0F065F5BC34(Any p0, Any p1) { return _i<Void>(0xC388A0F065F5BC34, p0, p1); }
	static Void set_player_health_recharge_multiplier(Player player, float regenRate) { return _i<Void>(0x5DB660B38DD98A31, player, regenRate); }
	static Void _0xEE4EBDD2593BA844(Any p0, Any p1) { return _i<Void>(0xEE4EBDD2593BA844, p0, p1); }
	static Void set_player_invincible(Player player, bool toggle) { return _i<Void>(0x239528EACDC3E7DE, player, toggle); }
	static Void _0x6BC97F4F4BB3C04B(Any p0, Any p1) { return _i<Void>(0x6BC97F4F4BB3C04B, p0, p1); }
	static Void _0xFF300C7649724A0B(Player player, bool p1) { return _i<Void>(0xFF300C7649724A0B, player, p1); }
	static Void set_player_lockon(Player player, bool toggle) { return _i<Void>(0x5C8B2F450EE4328E, player, toggle); }
	static Void set_player_lockon_range_override(Player player, float range) { return _i<Void>(0x29961D490E5814FD, player, range); }
	static Void set_player_max_armour(Player player, int value) { return _i<Void>(0x77DFCCF5948B8C71, player, value); }
	static Void _0x8D768602ADEF2245(Any p0, Any p1) { return _i<Void>(0x8D768602ADEF2245, p0, p1); }
	static Void set_player_may_not_enter_any_vehicle(Player player) { return _i<Void>(0x1DE37BBF9E9CC14A, player); }
	static Void set_player_may_only_enter_this_vehicle(Player player, Vehicle vehicle) { return _i<Void>(0x8026FF78F208978A, player, vehicle); }
	static Void set_player_melee_weapon_damage_modifier(Player player, float modifier, Any p2) { return _i<Void>(0x4A3DC7ECCC321032, player, modifier, p2); }
	static Void set_player_melee_weapon_defense_modifier(Player player, float modifier) { return _i<Void>(0xAE540335B4ABC4E2, player, modifier); }
	static Void set_player_model(Player player, uint32_t model) { return _i<Void>(0xA1CADD00108836, player, model); }
	static Void set_player_noise_multiplier(Player player, float multiplier) { return _i<Void>(0xDB89EF50FF25FCE9, player, multiplier); }
	static Void set_player_parachute_model_override(Player player, uint32_t model) { return _i<Void>(0x977DB4641F6FC3DB, player, model); }
	static Void set_player_parachute_pack_model_override(Player player, uint32_t model) { return _i<Void>(0xDC80A4C2F18A2B64, player, model); }
	static Void set_player_parachute_pack_tint_index(Player player, int tintIndex) { return _i<Void>(0x93B0FB27C9A04060, player, tintIndex); }
	static Void set_player_parachute_smoke_trail_color(Player player, int r, int g, int b) { return _i<Void>(0x8217FD371A4625CF, player, r, g, b); }
	static Void set_player_parachute_tint_index(Player player, int tintIndex) { return _i<Void>(0xA3D0E54541D9A5E5, player, tintIndex); }
	static Void set_player_parachute_variation_override(Player player, int p1, Any p2, Any p3, bool p4) { return _i<Void>(0xD9284A8C0D48352C, player, p1, p2, p3, p4); }
	static Void set_player_reset_flag_prefer_rear_seats(Player player, int flags) { return _i<Void>(0x11D5F725F0E780E0, player, flags); }
	static Void set_player_reserve_parachute_tint_index(Player player, int index) { return _i<Void>(0xAF04C87F5DC1DF38, player, index); }
	static Void set_player_simulate_aiming(Player player, bool toggle) { return _i<Void>(0xC54C95DA968EC5B5, player, toggle); }
	static Void set_player_sneaking_noise_multiplier(Player player, float multiplier) { return _i<Void>(0xB2C1A29588A9F47C, player, multiplier); }
	static Void _0x2F7CEB6520288061(bool p0) { return _i<Void>(0x2F7CEB6520288061, p0); }
	static Void set_player_sprint(Player player, bool toggle) { return _i<Void>(0xA01B8075D8B92DF4, player, toggle); }
	static Void set_player_stealth_perception_modifier(Player player, float value) { return _i<Void>(0x4E9021C1FCDD507A, player, value); }
	static Void set_player_targeting_mode(int targetMode) { return _i<Void>(0xB1906895227793F3, targetMode); }
	static Void _0x5702B917B99DB1CD(Any p0) { return _i<Void>(0x5702B917B99DB1CD, p0); }
	static Void set_player_team(Player player, int team) { return _i<Void>(0x0299FA38396A4940, player, team); }
	static Any _0xA0D3E4F7AAFB7E78(Any p0, Any p1) { return _i<Any>(0xA0D3E4F7AAFB7E78, p0, p1); }
	static Void set_player_vehicle_damage_modifier(Player player, float damageAmount) { return _i<Void>(0xA50E117CDDF82F0C, player, damageAmount); }
	static Void set_player_vehicle_defense_modifier(Player player, float modifier) { return _i<Void>(0x4C60E6EFDAFF2462, player, modifier); }
	static Void set_player_wanted_centre_position(Player player, float x, float y, float z) { return _i<Void>(0x520E541A97A13354, player, x, y, z); }
	static Void set_player_wanted_level(Player player, int wantedLevel, bool disableNoMission) { return _i<Void>(0x39FF19C64EF7DA5B, player, wantedLevel, disableNoMission); }
	static Void set_player_wanted_level_now(Player player, bool p1) { return _i<Void>(0xE0A7D1E497FFCD6F, player, p1); }
	static Void set_player_wanted_level_no_drop(Player player, int wantedLevel, bool p2) { return _i<Void>(0x340E61DE7F471565, player, wantedLevel, p2); }
	static Void set_player_weapon_damage_modifier(Player player, float damageAmount) { return _i<Void>(0xCE07B9F7817AADA3, player, damageAmount); }
	static Void set_player_weapon_defense_modifier(Player player, float modifier) { return _i<Void>(0x2D83BC011CA14A3C, player, modifier); }
	static Void _0xBCFDE9EDE4CF27DC(Any p0, Any p1) { return _i<Void>(0xBCFDE9EDE4CF27DC, p0, p1); }
	static Void _0x31E90B8873A4CD3B(Any p0, Any p1) { return _i<Void>(0x31E90B8873A4CD3B, p0, p1); }
	static Void set_police_ignore_player(Player player, bool toggle) { return _i<Void>(0x32C62AA929C2DA6A, player, toggle); }
	static Void set_police_radar_blips(bool toggle) { return _i<Void>(0x43286D561B72B8BF, toggle); }
	static Void set_run_sprint_multiplier_for_player(Player player, float multiplier) { return _i<Void>(0x6DB47AA77FD94E09, player, multiplier); }
	static Void _0xB214D570EAD7F81A(Any p0, Any p1) { return _i<Void>(0xB214D570EAD7F81A, p0, p1); }
	static Void set_special_ability_multiplier(float multiplier) { return _i<Void>(0xA49C426ED0CA4AB7, multiplier); }
	static Void set_swim_multiplier_for_player(Player player, float multiplier) { return _i<Void>(0xA91C6F0FF7D16A13, player, multiplier); }
	static Void set_wanted_level_difficulty(Player player, float difficulty) { return _i<Void>(0x9B0BB33B04405E7A, player, difficulty); }
	static Void set_wanted_level_multiplier(float multiplier) { return _i<Void>(0x020E5F00CDA207BA, multiplier); }
	static Void simulate_player_input_gait(Player player, float amount, int gaitType, float speed, bool p4, bool p5) { return _i<Void>(0x477D5D63E63ECA5D, player, amount, gaitType, speed, p4, p5); }
	static Void _0x821FDC827D6F4090(Any p0) { return _i<Void>(0x821FDC827D6F4090, p0); }
	static Void special_ability_charge_absolute(Player player, int p1, bool p2) { return _i<Void>(0xB7B0870EB531D08D, player, p1, p2); }
	static Void special_ability_charge_continuous(Player player, Ped p2) { return _i<Void>(0xED481732DFF7E997, player, p2); }
	static Void special_ability_charge_large(Player player, bool p1, bool p2) { return _i<Void>(0xF733F45FA4497D93, player, p1, p2); }
	static Void special_ability_charge_medium(Player player, bool p1, bool p2) { return _i<Void>(0xF113E3AA9BC54613, player, p1, p2); }
	static Void special_ability_charge_normalized(Player player, float normalizedValue, bool p2) { return _i<Void>(0xA0696A65F009EE18, player, normalizedValue, p2); }
	static Void _0xC9A763D8FE87436A(Player player) { return _i<Void>(0xC9A763D8FE87436A, player); }
	static Void special_ability_charge_small(Player player, bool p1, bool p2) { return _i<Void>(0x2E7B9B683481687D, player, p1, p2); }
	static Void special_ability_deactivate(Player player) { return _i<Void>(0xD6A953C6D1492057, player); }
	static Void special_ability_deactivate_fast(Player player) { return _i<Void>(0x9CB5CE07A3968D5A, player); }
	static Void _0x17F7471EACA78290(Any p0) { return _i<Void>(0x17F7471EACA78290, p0); }
	static Void special_ability_deplete_meter(Player player, bool p1) { return _i<Void>(0x1D506DBBBC51E64B, player, p1); }
	static Void special_ability_fill_meter(Player player, bool p1) { return _i<Void>(0x3DACA8DDC6FD4980, player, p1); }
	static Void special_ability_lock(uint32_t playerModel) { return _i<Void>(0x6A09D0D590A47D13, playerModel); }
	static Void special_ability_reset(Player player) { return _i<Void>(0x375F0E738F861A94, player); }
	static Void special_ability_unlock(uint32_t playerModel) { return _i<Void>(0xF145F3BE2EFA9A3B, playerModel); }
	static Void start_firing_amnesty(int duration) { return _i<Void>(0xBF9BD71691857E48, duration); }
	static Void start_player_teleport(Player player, float x, float y, float z, float heading, bool p5, bool p6, bool p7) { return _i<Void>(0xAD15F075A4DA0FDE, player, x, y, z, heading, p5, p6, p7); }
	static Void stop_player_teleport() { return _i<Void>(0xC449EDED9D73009C); }
	static Void switch_crime_type(Player player, int p1) { return _i<Void>(0x9A987297ED8BD838, player, p1); }
	static Void _0x4669B3ED80F24B4E(Player player) { return _i<Void>(0x4669B3ED80F24B4E, player); }
	static Void _0x36F1B38855F2A8DF(Player player) { return _i<Void>(0x36F1B38855F2A8DF, player); }
	static bool has_player_teleport_finished(Player player) { return _i<bool>(0xE23D5873C2394C61, player); }
	static Void _0xFFEE8FA29AB9A18E(Player player) { return _i<Void>(0xFFEE8FA29AB9A18E, player); }
	static Void _0xBC9490CA15AEA8FB(Player player) { return _i<Void>(0xBC9490CA15AEA8FB, player); }

	static Void stop_recording_and_discard_clip() { return _i<Void>(0x88BB3507ED41A240); }
	static Any _0x4282E08174868BE3() { return _i<Any>(0x4282E08174868BE3); }
	static Any _0xDF4B952F7D381B95() { return _i<Any>(0xDF4B952F7D381B95); }
	static bool is_recording() { return _i<bool>(0x1897CA71995A90B4); }
	static bool _0x33D47E85B476ABCD(bool p0) { return _i<bool>(0x33D47E85B476ABCD, p0); }
	static Void _0x13B350B8AD0EEE10() { return _i<Void>(0x13B350B8AD0EEE10); }
	static Void _0xAF66DCEE6609B148() { return _i<Void>(0xAF66DCEE6609B148); }
	static Void _0xEB2D525B57F42B40() { return _i<Void>(0xEB2D525B57F42B40); }
	static Void _0x293220DA1B46CEBC(float p0, float p1, bool p2) { return _i<Void>(0x293220DA1B46CEBC, p0, p1, p2); }
	static Void _0xF854439EFBB3B583() { return _i<Void>(0xF854439EFBB3B583); }
	static Void _0x48621C9FCA3EBD28(bool p0) { return _i<Void>(0x48621C9FCA3EBD28, p0); }
	static Void _0x81CBAE94390F9F89() { return _i<Void>(0x81CBAE94390F9F89); }
	static bool _0x644546EC5287471B() { return _i<bool>(0x644546EC5287471B); }
	static Void start_recording(int mode) { return _i<Void>(0xC3AC2FFF9612AC81, mode); }
	static Void stop_recording_and_save_clip() { return _i<Void>(0x071A5197D6AFC8B3); }
	static Void _0x208784099002BC30(const char* missionNameLabel, Any p1) { return _i<Void>(0x208784099002BC30, missionNameLabel, p1); }
	static Void _0x66972397E0757E7A(Any p0, Any p1, Any p2) { return _i<Void>(0x66972397E0757E7A, p0, p1, p2); }

	static Void activate_rockstar_editor() { return _i<Void>(0x49DA8145672B2725); }
	static Void reset_editor_values() { return _i<Void>(0x3353D13F09307691); }
	static bool is_interior_rendering_disabled() { return _i<bool>(0x95AB8B5C992C7B58); }
	static Void _0xE058175F8EAFE79A(bool p0) { return _i<Void>(0xE058175F8EAFE79A, p0); }
	static Void _0x5AD3932DAEB1E5D3() { return _i<Void>(0x5AD3932DAEB1E5D3); }
	static Void _0x7E2BD3EF6C205F09(Any p0, Any p1) { return _i<Void>(0x7E2BD3EF6C205F09, p0, p1); }

	static Any _0x0F6F1EBBC4E1D5E6() { return _i<Any>(0x0F6F1EBBC4E1D5E6); }
	static Any _0xDC2BACD920D0A0DD() { return _i<Any>(0xDC2BACD920D0A0DD); }
	static Any _0x107E5CC7CA942BC1() { return _i<Any>(0x107E5CC7CA942BC1); }
	static Any _0x22E21FBCFC88C149() { return _i<Any>(0x22E21FBCFC88C149); }
	static Any _0x829CD22E043A2577() { return _i<Any>(0x829CD22E043A2577); }
	static Any _0x836B62713E0534CA() { return _i<Any>(0x836B62713E0534CA); }
	static Any _0x760910B49D2B98EA() { return _i<Any>(0x760910B49D2B98EA); }
	static Any _0x9D5A25BADB742ACD() { return _i<Any>(0x9D5A25BADB742ACD); }
	static Any _0x75B18E49607874C7() { return _i<Any>(0x75B18E49607874C7); }
	static Void _0xB1577667C3708F9B() { return _i<Void>(0xB1577667C3708F9B); }
	static bool does_script_exist(const char* scriptName) { return _i<bool>(0xFC04745FBE67C19A, scriptName); }
	static bool does_script_with_name_hash_exist(uint32_t scriptHash) { return _i<bool>(0xF86AA3C56BA31381, scriptHash); }
	static int get_event_at_index(bool p0, int eventNum) { return _i<int>(0xD8F66A3A60C62153, p0, eventNum); }
	static bool get_event_data(bool p0, int eventNum, int* argStruct, int argStructSize) { return _i<bool>(0x2902843FCD2B2D79, p0, eventNum, argStruct, argStructSize); }
	static bool get_event_exists(bool p0, int p1) { return _i<bool>(0x936E6168A9BCEDB5, p0, p1); }
	static uint32_t get_hash_of_this_script_name() { return _i<uint32_t>(0x8A1C8B1738FFE87E); }
	static int get_id_of_this_thread() { return _i<int>(0xC30338E8088E2E21); }
	static const char* get_name_of_thread(int threadId) { return _i<const char*>(0x05A42BA9FC8DA96B, threadId); }
	static bool get_no_loading_screen() { return _i<bool>(0x18C1270EA7F199BC); }
	static int get_number_of_events(bool p0) { return _i<int>(0x5F92A689A06620AA, p0); }
	static int get_number_of_instances_of_script_with_name_hash(uint32_t scriptHash) { return _i<int>(0x2C83A9DA6BFFC4F9, scriptHash); }
	static const char* get_this_script_name() { return _i<const char*>(0x442E0A7EDE4A738A); }
	static bool has_script_loaded(const char* scriptName) { return _i<bool>(0xE6CC9F3BA0FB9EF1, scriptName); }
	static bool has_script_with_name_hash_loaded(uint32_t scriptHash) { return _i<bool>(0x5F0F0C783EB16C04, scriptHash); }
	static bool is_thread_active(int threadId) { return _i<bool>(0x46E9AE36D8FA6417, threadId); }
	static Void request_script(const char* scriptName) { return _i<Void>(0x6EB5F71AA68F2E8E, scriptName); }
	static Void request_script_with_name_hash(uint32_t scriptHash) { return _i<Void>(0xD62A67D26D9653E6, scriptHash); }
	static int get_id_of_next_thread_in_enumeration() { return _i<int>(0x30B4FA1C82DD4B9F); }
	static Void begin_enumerating_threads() { return _i<Void>(0xDADFADA5A20143A8); }
	static Void trigger_script_event(bool p0, int64_t* args, int argCount, int bit) { return _i<Void>(0x5AE99C571D5BBE5D, p0, args, argCount, bit); }
	static Void set_no_loading_screen(bool toggle) { return _i<Void>(0x5262CC1995D07E09, toggle); }
	static Void set_script_as_no_longer_needed(const char* scriptName) { return _i<Void>(0xC90D2DCACD56184C, scriptName); }
	static Void set_script_with_name_hash_as_no_longer_needed(uint32_t scriptHash) { return _i<Void>(0xC5BC038960E9DB27, scriptHash); }
	static Void shutdown_loading_screen() { return _i<Void>(0x078EBE9809CCD637); }
	static Void terminate_this_thread() { return _i<Void>(0x1090044AD1DA76FA); }
	static Void terminate_thread_(int threadId) { return _i<Void>(0xC8B189ED9138BCD4, threadId); }

	static int get_shape_test_result(int rayHandle, bool* hit, math::vector3<float>* endCoords, math::vector3<float>* surfaceNormal, Entity* entityHit) { return _i<int>(0x3D87450E15D98694, rayHandle, hit, endCoords, surfaceNormal, entityHit); }
	static int get_shape_test_result_ex(int rayHandle, bool* hit, math::vector3<float>* endCoords, math::vector3<float>* surfaceNormal, uint32_t* materialHash, Entity* entityHit) { return _i<int>(0x65287525D951F6BE, rayHandle, hit, endCoords, surfaceNormal, materialHash, entityHit); }
	static Void _0x2B3334BCA57CD799(Entity p0) { return _i<Void>(0x2B3334BCA57CD799, p0); }
	static int start_shape_test_ray(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8) { return _i<int>(0x377906D8A31E5586, x1, y1, z1, x2, y2, z2, flags, entity, p8); }
	static int start_shape_test_bound(Entity entity, int flags1, int flags2) { return _i<int>(0x37181417CE7C8900, entity, flags1, flags2); }
	static int start_shape_test_bounding_box(Entity entity, int flags1, int flags2) { return _i<int>(0x052837721A854EC7, entity, flags1, flags2); }
	static int start_shape_test_box(float x, float y, float z, float x1, float y2, float z2, float rotX, float rotY, float rotZ, Any p9, Any p10, Any entity, Any p12) { return _i<int>(0xFE466162C4401D18, x, y, z, x1, y2, z2, rotX, rotY, rotZ, p9, p10, entity, p12); }
	static int start_shape_test_capsule(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, int p9) { return _i<int>(0x28579D1B8F8AAC80, x1, y1, z1, x2, y2, z2, radius, flags, entity, p9); }
	static int start_shape_test_los_probe(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8) { return _i<int>(0x7EE9F5D83DD4F90E, x1, y1, z1, x2, y2, z2, flags, entity, p8); }
	static int _0xFF6BE494C7987F34(math::vector3<float>* pVec1, math::vector3<float>* pVec2, int flag, Entity entity, int flag2) { return _i<int>(0xFF6BE494C7987F34, pVec1, pVec2, flag, entity, flag2); }
	static int _0xE6AC6C45FBE83004(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, Any p9) { return _i<int>(0xE6AC6C45FBE83004, x1, y1, z1, x2, y2, z2, radius, flags, entity, p9); }

	static const char* sc_get_nickname() { return _i<const char*>(0x198D161F458ECC7F); }
	static bool _0x225798743970412B(int* p0) { return _i<bool>(0x225798743970412B, p0); }
	static Void _0xBFA0A56A817C6C7D(bool p0) { return _i<Void>(0xBFA0A56A817C6C7D, p0); }
	static Any _0xC2C97EA97711D1AE() { return _i<Any>(0xC2C97EA97711D1AE); }
	static bool _0x19853B5B17D77BCA(Any p0, Any* p1) { return _i<bool>(0x19853B5B17D77BCA, p0, p1); }
	static Any _0x33DF47CC0642061B() { return _i<Any>(0x33DF47CC0642061B); }
	static Any _0x4ED9C8D6DA297639() { return _i<Any>(0x4ED9C8D6DA297639); }
	static Any _0x4A7D6E727F941747(Any* p0) { return _i<Any>(0x4A7D6E727F941747, p0); }
	static Any _0x50A8A36201DBF83E() { return _i<Any>(0x50A8A36201DBF83E); }
	static Any _0xC5A35C73B68F3C49() { return _i<Any>(0xC5A35C73B68F3C49); }
	static Any _0x2570E26BE63964E3() { return _i<Any>(0x2570E26BE63964E3); }
	static Any _0x710BCDA8071EDED1() { return _i<Any>(0x710BCDA8071EDED1); }
	static bool _0x8CC469AB4D349B7C(int p0, const char* p1, Any* p2) { return _i<bool>(0x8CC469AB4D349B7C, p0, p1, p2); }
	static Any _0xE75A4A2E5E316D86() { return _i<Any>(0xE75A4A2E5E316D86); }
	static Any _0x9DE5D2F723575ED0() { return _i<Any>(0x9DE5D2F723575ED0); }
	static bool _0x699E4A5C8C893A18(int p0, const char* p1, Any* p2) { return _i<bool>(0x699E4A5C8C893A18, p0, p1, p2); }
	static Any _0x1D12A56FC95BE92E() { return _i<Any>(0x1D12A56FC95BE92E); }
	static Any _0xFF8F3A92B75ED67A() { return _i<Any>(0xFF8F3A92B75ED67A); }
	static Any _0xA468E0BE12B12C70() { return _i<Any>(0xA468E0BE12B12C70); }
	static Any _0x450819D8CF90C416() { return _i<Any>(0x450819D8CF90C416); }
	static Void _0x44ACA259D67651DB(Any* p0, Any p1) { return _i<Void>(0x44ACA259D67651DB, p0, p1); }
	static bool _0x4737980E8A283806(int p0, Any* p1) { return _i<bool>(0x4737980E8A283806, p0, p1); }
	static Any _0x7DB18CA8CAD5B098() { return _i<Any>(0x7DB18CA8CAD5B098); }
	static Any _0x16DA8172459434AA() { return _i<Any>(0x16DA8172459434AA); }
	static Void sc_email_message_clear_recip_list() { return _i<Void>(0x55DF6DB45179236E); }
	static Void sc_email_message_push_gamer_to_recip_list(Player* player) { return _i<Void>(0x2330C12A7A605D16, player); }
	static Void sc_inbox_get_emails(int offset, int limit) { return _i<Void>(0x040ADDCBAFA1018A, offset, limit); }
	static Void _0x116FB94DC4B79F17(const char* p0) { return _i<Void>(0x116FB94DC4B79F17, p0); }
	static Any _0x07DBD622D9533857(Any p0) { return _i<Any>(0x07DBD622D9533857, p0); }
	static Any _0x2D874D4AE612A65F() { return _i<Any>(0x2D874D4AE612A65F); }
	static bool _0x8416FE4E4629D7D7(const char* p0) { return _i<bool>(0x8416FE4E4629D7D7, p0); }
	static Any _0xA770C8EEC6FB2AC5() { return _i<Any>(0xA770C8EEC6FB2AC5); }
	static Any _0xC85A7127E7AD02AA() { return _i<Any>(0xC85A7127E7AD02AA); }
	static Any _0x7FFCBFEE44ECFABF() { return _i<Any>(0x7FFCBFEE44ECFABF); }
	static Any _0xDF649C4E9AFDD788() { return _i<Any>(0xDF649C4E9AFDD788); }
	static bool _0x418DC16FAE452C1C(int p0) { return _i<bool>(0x418DC16FAE452C1C, p0); }
	static Any _0xBC1CC91205EC8D6E() { return _i<Any>(0xBC1CC91205EC8D6E); }
	static bool _0x87E0052F08BD64E6(Any p0, int* p1) { return _i<bool>(0x87E0052F08BD64E6, p0, p1); }
	static bool is_sc_inbox_valid(int p0) { return _i<bool>(0x93028F1DB42BFD08, p0); }
	static uint32_t sc_inbox_message_init(int p0) { return _i<uint32_t>(0xBB8EA16ECBC976C4, p0); }
	static int get_total_sc_inbox_ids() { return _i<int>(0x03A93FF1A2CA0864); }
	static bool sc_inbox_message_push(int p0) { return _i<bool>(0x9A2C8064B6C1E41A, p0); }
	static bool sc_inbox_message_get_data_bool(int p0, const char* p1) { return _i<bool>(0xFFE5C16F402D851D, p0, p1); }
	static bool sc_inbox_message_get_data_int(int p0, const char* context, int* out) { return _i<bool>(0xA00EFE4082C4056E, p0, context, out); }
	static bool sc_inbox_message_get_data_string(int p0, const char* context, const char* out) { return _i<bool>(0x7572EF42FC6A9B6D, p0, context, out); }
	static const char* sc_inbox_message_get_string(int p0) { return _i<const char*>(0xF3E31D16CBDCB304, p0); }
	static bool sc_inbox_message_get_ugcdata(Any p0, Any* p1) { return _i<bool>(0x69D82604A1A5A254, p0, p1); }
	static Void _0xDA024BDBD600F44A(int* p0) { return _i<Void>(0xDA024BDBD600F44A, p0); }
	static bool _0x6AFD2CD753FEEF83(const char* p0) { return _i<bool>(0x6AFD2CD753FEEF83, p0); }
	static Void _0xA68D3D229F4F3B06(const char* p0) { return _i<Void>(0xA68D3D229F4F3B06, p0); }
	static bool sc_inbox_message_pop(int p0) { return _i<bool>(0x2C015348CF19CA1D, p0); }
	static bool _0x1989C6E6F67E76A8(Any* p0, Any* p1, Any* p2) { return _i<bool>(0x1989C6E6F67E76A8, p0, p1, p2); }
	static bool _0xF6BAAAF762E1BF40(const char* p0, int* p1) { return _i<bool>(0xF6BAAAF762E1BF40, p0, p1); }
	static Any _0x07C61676E5BB52CD(Any p0) { return _i<Any>(0x07C61676E5BB52CD, p0); }
	static Any _0x8147FFF6A718E1AD(Any p0) { return _i<Any>(0x8147FFF6A718E1AD, p0); }
	static Any _0x9237E334F6E43156(Any p0) { return _i<Any>(0x9237E334F6E43156, p0); }
	static bool _0xF22CA0FD74B80E7A(Any p0) { return _i<bool>(0xF22CA0FD74B80E7A, p0); }
	static Any _0x700569DBA175A77C(Any p0) { return _i<Any>(0x700569DBA175A77C, p0); }
	static Any _0xD302E99EDF0449CF(Any p0) { return _i<Any>(0xD302E99EDF0449CF, p0); }
	static Any _0x5C4EBFFA98BDB41C(Any p0) { return _i<Any>(0x5C4EBFFA98BDB41C, p0); }
	static Any _0x1D4446A62D35B0D0(Any p0, Any p1) { return _i<Any>(0x1D4446A62D35B0D0, p0, p1); }
	static Any _0x2E89990DDFF670C3(Any p0, Any p1) { return _i<Any>(0x2E89990DDFF670C3, p0, p1); }
	static bool _0x0F73393BAC7E6730(Any* p0, int* p1) { return _i<bool>(0x0F73393BAC7E6730, p0, p1); }
	static bool _0xD0EE05FE193646EA(Any* p0, Any* p1, Any* p2) { return _i<bool>(0xD0EE05FE193646EA, p0, p1, p2); }
	static Any _0xC4C4575F62534A24() { return _i<Any>(0xC4C4575F62534A24); }
	static bool _0x1F1E9682483697C7(Any p0, Any p1) { return _i<bool>(0x1F1E9682483697C7, p0, p1); }
	static bool _0x287F1F75D2803595(Any p0, Any* p1) { return _i<bool>(0x287F1F75D2803595, p0, p1); }
	static bool _0x487912FD248EFDDF(Any p0, float p1) { return _i<bool>(0x487912FD248EFDDF, p0, p1); }
	static bool sc_profanity_check_string(const char* string, int* taskHandle) { return _i<bool>(0x75632C5ECD7ED843, string, taskHandle); }
	static Any _0xEB2BF817463DFA28(Any p0, Any p1) { return _i<Any>(0xEB2BF817463DFA28, p0, p1); }
	static int sc_profanity_get_check_is_pending(int taskHandle) { return _i<int>(0x82E4A58BABC15AE7, taskHandle); }
	static bool sc_has_check_string_task_completed(int taskHandle) { return _i<bool>(0x1753344C770358AE, taskHandle); }
	static Any _0x85535ACF97FC0969(Any p0) { return _i<Any>(0x85535ACF97FC0969, p0); }
	static int sc_profanity_get_string_status(int p0) { return _i<int>(0x930DE22F07B1CCE3, p0); }
	static Void _0x675721C9F644D161() { return _i<Void>(0x675721C9F644D161); }
	static bool _0x92DA6E70EF249BD1(const char* p0, int* p1) { return _i<bool>(0x92DA6E70EF249BD1, p0, p1); }
	static bool _0x3001BEF2FECA3680() { return _i<bool>(0x3001BEF2FECA3680); }
	static bool _0x6BFB12CE158E3DD4(Any p0) { return _i<bool>(0x6BFB12CE158E3DD4, p0); }
	static Any _0xD8122C407663B995() { return _i<Any>(0xD8122C407663B995); }
	static bool _0xFE4C1D0D3B9CC17E(Any p0, Any p1) { return _i<bool>(0xFE4C1D0D3B9CC17E, p0, p1); }

	static Any _0xB3DA2606774A8E2D() { return _i<Any>(0xB3DA2606774A8E2D); }
	static Void _0x44919CC079BB60BF(Any p0) { return _i<Void>(0x44919CC079BB60BF, p0); }
	static Void _0xD1C9B92BDD3F151D(Any p0, Any p1, Any p2) { return _i<Void>(0xD1C9B92BDD3F151D, p0, p1, p2); }
	static Void _0xA3C53804BDB68ED2(Any p0, Any p1) { return _i<Void>(0xA3C53804BDB68ED2, p0, p1); }
	static Void _0x6BCCF9948492FD85(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x6BCCF9948492FD85, p0, p1, p2, p3, p4); }
	static Void _0x6F361B8889A792A3() { return _i<Void>(0x6F361B8889A792A3); }
	static Void _0x6BC0ACD0673ACEBE(Any p0, Any p1, Any p2) { return _i<Void>(0x6BC0ACD0673ACEBE, p0, p1, p2); }
	static uint32_t get_pstat_bool_hash(int index, bool spStat, bool charStat, int character) { return _i<uint32_t>(0x80C75307B1C42837, index, spStat, charStat, character); }
	static uint32_t get_pstat_int_hash(int index, bool spStat, bool charStat, int character) { return _i<uint32_t>(0x61E111E323419E07, index, spStat, charStat, character); }
	static uint32_t get_ngstat_bool_hash(int index, bool spStat, bool charStat, int character, const char* section) { return _i<uint32_t>(0xBA52FF538ED2BC71, index, spStat, charStat, character, section); }
	static uint32_t get_ngstat_int_hash(int index, bool spStat, bool charStat, int character, const char* section) { return _i<uint32_t>(0x2B4CDCA6F07FF3DA, index, spStat, charStat, character, section); }
	static uint32_t get_tupstat_bool_hash(int index, bool spStat, bool charStat, int character) { return _i<uint32_t>(0xC4BB08EE7907471E, index, spStat, charStat, character); }
	static uint32_t get_tupstat_int_hash(int index, bool spStat, bool charStat, int character) { return _i<uint32_t>(0xD16C2AD6B8E32854, index, spStat, charStat, character); }
	static bool _0x5EAD2BF6484852E4() { return _i<bool>(0x5EAD2BF6484852E4); }
	static Void _0x792271AB35C356A4(Any p0, Any p1) { return _i<Void>(0x792271AB35C356A4, p0, p1); }
	static bool leaderboards2_read_by_handle(Any* p0, Any* p1) { return _i<bool>(0xC30713A383BFBF0E, p0, p1); }
	static bool _0xF1AE5DCDBFCA2721(Any* p0, Any* p1, Any* p2) { return _i<bool>(0xF1AE5DCDBFCA2721, p0, p1, p2); }
	static bool leaderboards2_read_by_radius(Any* p0, Any p1, Any* p2) { return _i<bool>(0x5CE587FB5A42C8C4, p0, p1, p2); }
	static bool leaderboards2_read_by_rank(Any* p0, Any p1, Any p2) { return _i<bool>(0xBA2C7DB0C129449A, p0, p1, p2); }
	static bool leaderboards2_read_by_row(Any* p0, Any* p1, Any p2, Any* p3, Any p4, Any* p5, Any p6) { return _i<bool>(0xA9CDB1E3F0A49883, p0, p1, p2, p3, p4, p5, p6); }
	static bool leaderboards2_read_by_score_float(Any* p0, float p1, Any p2) { return _i<bool>(0xE662C8B759D08F3C, p0, p1, p2); }
	static bool leaderboards2_read_by_score_int(Any* p0, Any p1, Any p2) { return _i<bool>(0x7EEC7E4F6984A16A, p0, p1, p2); }
	static bool leaderboards2_read_friends_by_row(Any* p0, Any* p1, Any p2, bool p3, Any p4, Any p5) { return _i<bool>(0x918B101666F9CB83, p0, p1, p2, p3, p4, p5); }
	static Void _0x71B008056E5692D6() { return _i<Void>(0x71B008056E5692D6); }
	static float _0x38491439B6BA7F7D(Any p0, Any p1) { return _i<float>(0x38491439B6BA7F7D, p0, p1); }
	static bool _0x34770B9CE0E03B91(Any p0, Any* p1) { return _i<bool>(0x34770B9CE0E03B91, p0, p1); }
	static Any _0x88578F6EC36B4A3A(Any p0, Any p1) { return _i<Any>(0x88578F6EC36B4A3A, p0, p1); }
	static bool _0xA0F93D5465B3094D(Any* p0) { return _i<bool>(0xA0F93D5465B3094D, p0); }
	static bool _0xC38DC1E90D22547C(Any* p0, Any* p1, Any* p2) { return _i<bool>(0xC38DC1E90D22547C, p0, p1, p2); }
	static bool leaderboards2_write_data(Any* p0) { return _i<bool>(0xAE2206545888AE49, p0); }
	static bool _0xC980E62E33DF1D5C(Any* p0, Any* p1) { return _i<bool>(0xC980E62E33DF1D5C, p0, p1); }
	static bool leaderboards_cache_data_row(Any* p0) { return _i<bool>(0xB9BB18E2C40142ED, p0); }
	static Void leaderboards_clear_cache_data() { return _i<Void>(0xD4B02A6B476E1FDC); }
	static Void _0x8EC74CEB042E7CFF(Any p0) { return _i<Void>(0x8EC74CEB042E7CFF, p0); }
	static bool leaderboards_get_cache_data_row(Any p0, Any p1, Any* p2) { return _i<bool>(0x9120E8DBA3D69273, p0, p1, p2); }
	static bool leaderboards_get_cache_exists(Any p0) { return _i<bool>(0x9C51349BE6CDFE2C, p0); }
	static Any _0x58A651CD201D89AD(Any p0) { return _i<Any>(0x58A651CD201D89AD, p0); }
	static Any leaderboards_get_cache_time(Any p0) { return _i<Any>(0xF04C1C27DA35F6C8, p0); }
	static Any leaderboards_get_column_id(Any p0, Any p1, Any p2) { return _i<Any>(0xC4B5467A1886EA7E, p0, p1, p2); }
	static Any leaderboards_get_column_type(Any p0, Any p1, Any p2) { return _i<Any>(0xBF4FEF46DB7894D3, p0, p1, p2); }
	static Any leaderboards_get_number_of_columns(Any p0, Any p1) { return _i<Any>(0x117B45156D7EFF2E, p0, p1); }
	static Any _0xA31FD15197B192BD() { return _i<Any>(0xA31FD15197B192BD); }
	static Any leaderboards_read_clear(Any p0, Any p1, Any p2) { return _i<Any>(0x7CCE5C737A665701, p0, p1, p2); }
	static Any leaderboards_read_clear_all() { return _i<Any>(0xA34CB6E6F0DF4A0B); }
	static bool leaderboards_read_pending(Any p0, Any p1, Any p2) { return _i<bool>(0xAC392C8483342AC2, p0, p1, p2); }
	static bool leaderboards_read_successful(Any p0, Any p1, Any p2) { return _i<bool>(0x2FB19228983E832C, p0, p1, p2); }
	static Void _0x0BCA1D2C47B0D269(Any p0, Any p1, float p2) { return _i<Void>(0x0BCA1D2C47B0D269, p0, p1, p2); }
	static Void _0x2E65248609523599(Any p0, Any p1, Any p2) { return _i<Void>(0x2E65248609523599, p0, p1, p2); }
	static Void _0xCEA553E35C2246E1(Any p0, Any p1, Any p2) { return _i<Void>(0xCEA553E35C2246E1, p0, p1, p2); }
	static int _0xF4D8E7AC2A27758C(int p0) { return _i<int>(0xF4D8E7AC2A27758C, p0); }
	static int _0x94F12ABF9C79E339(int p0) { return _i<int>(0x94F12ABF9C79E339, p0); }
	static Void _0xD558BEC0BBA7E8D2(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xD558BEC0BBA7E8D2, p0, p1, p2, p3, p4); }
	static Void _0x79AB33F0FBFAC40C(Any p0) { return _i<Void>(0x79AB33F0FBFAC40C, p0); }
	static Void _0xA071E0ED98F91286(Any p0, Any p1) { return _i<Void>(0xA071E0ED98F91286, p0, p1); }
	static Void _0x46326E13DA4E0546(Any* p0) { return _i<Void>(0x46326E13DA4E0546, p0); }
	static Void _0x47B32F5611E6E483(Any p0) { return _i<Void>(0x47B32F5611E6E483, p0); }
	static Void playstats_award_xp(Any p0, Any p1, Any p2) { return _i<Void>(0x46F917F6B4128FE4, p0, p1, p2); }
	static Void _0x5009DFD741329729(const char* p0, Any p1) { return _i<Void>(0x5009DFD741329729, p0, p1); }
	static Void _0x516FC96EB88EEFE5(Any p0) { return _i<Void>(0x516FC96EB88EEFE5, p0); }
	static Void _0x7B18DA61F6BAE9D5(Any p0) { return _i<Void>(0x7B18DA61F6BAE9D5, p0); }
	static Void _0x53CAE13E9B426993(Any p0) { return _i<Void>(0x53CAE13E9B426993, p0); }
	static Void _0xE3261D791EB44ACB(Any p0) { return _i<Void>(0xE3261D791EB44ACB, p0); }
	static Void _0x930F504203F561C9(Any p0) { return _i<Void>(0x930F504203F561C9, p0); }
	static Void _0x73001E34F85137F8(Any p0) { return _i<Void>(0x73001E34F85137F8, p0); }
	static Void _0x14EDA9EE27BD1626(Any p0) { return _i<Void>(0x14EDA9EE27BD1626, p0); }
	static Void _0x7D36291161859389(Any p0) { return _i<Void>(0x7D36291161859389, p0); }
	static Void _0x06EAF70AE066441E(Any p0) { return _i<Void>(0x06EAF70AE066441E, p0); }
	static Void _0xD6781E42755531F7(Any p0) { return _i<Void>(0xD6781E42755531F7, p0); }
	static Void _0xF06A6F41CB445443(Any p0) { return _i<Void>(0xF06A6F41CB445443, p0); }
	static Void _0x678F86D8FC040BDB(Any p0) { return _i<Void>(0x678F86D8FC040BDB, p0); }
	static Void _0xA6F54BB2FFCA35EA(Any p0) { return _i<Void>(0xA6F54BB2FFCA35EA, p0); }
	static Void _0x8D8ADB562F09A245(Any p0) { return _i<Void>(0x8D8ADB562F09A245, p0); }
	static Void _0x282B6739644F4347(Any p0) { return _i<Void>(0x282B6739644F4347, p0); }
	static Void _0x5FF2C33B13A02A11(Any p0) { return _i<Void>(0x5FF2C33B13A02A11, p0); }
	static Void _0x88087EE1F28024AE(Any p0) { return _i<Void>(0x88087EE1F28024AE, p0); }
	static Void _0xFCC228E07217FCAC(Any p0) { return _i<Void>(0xFCC228E07217FCAC, p0); }
	static Void _0xD1A1EE3B4FA8E760(Any p0) { return _i<Void>(0xD1A1EE3B4FA8E760, p0); }
	static Void _0x28ECB8AC2F607DB2(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x28ECB8AC2F607DB2, p0, p1, p2, p3, p4); }
	static Void _0x0B565B0AAE56A0E8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x0B565B0AAE56A0E8, p0, p1, p2, p3, p4, p5, p6); }
	static Void playstats_cheat_applied(const char* cheat) { return _i<Void>(0x6058665D72302D3F, cheat); }
	static Void playstats_cloth_change(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x34B973047A2268B9, p0, p1, p2, p3, p4); }
	static Void _0xB7257BA2550EA10A(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0xB7257BA2550EA10A, p0, p1, p2, p3, p4, p5, p6); }
	static Void playstats_ambient_mission_crate_created(float p0, float p1, float p2) { return _i<Void>(0xAFC7E5E075A96F46, p0, p1, p2); }
	static Void _0x1CAE5D2E3F9A07F0(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return _i<Void>(0x1CAE5D2E3F9A07F0, p0, p1, p2, p3, p4, p5, p6, p7); }
	static bool _0x6DEE77AFF8C21BD1(Any* p0, Any* p1) { return _i<bool>(0x6DEE77AFF8C21BD1, p0, p1); }
	static Void _0x2605663BD4F23B5D(Any p0) { return _i<Void>(0x2605663BD4F23B5D, p0); }
	static Void _0x848B66100EE33B05(Any p0) { return _i<Void>(0x848B66100EE33B05, p0); }
	static Void _0x501478855A6074CE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0x501478855A6074CE, p0, p1, p2, p3, p4, p5); }
	static Void _0xBAA2F0490E146BE8(Any p0) { return _i<Void>(0xBAA2F0490E146BE8, p0); }
	static Void _0x6A60E43998228229(Any p0) { return _i<Void>(0x6A60E43998228229, p0); }
	static Void _0x3DE3AA516FB126A4(Any p0) { return _i<Void>(0x3DE3AA516FB126A4, p0); }
	static Void _0x6551B1F7F6CD46EA(Any p0) { return _i<Void>(0x6551B1F7F6CD46EA, p0); }
	static Void _0xEDBF6C9B0D2C65C8(Any p0) { return _i<Void>(0xEDBF6C9B0D2C65C8, p0); }
	static Void _0x0A9C7F36E5D7B683(Any p0) { return _i<Void>(0x0A9C7F36E5D7B683, p0); }
	static Void _0x84DFC579C2FC214C(Any p0) { return _i<Void>(0x84DFC579C2FC214C, p0); }
	static Void _0x2CD90358F67D0AA8(Any p0) { return _i<Void>(0x2CD90358F67D0AA8, p0); }
	static Void _0x164C5FF663790845(Any p0) { return _i<Void>(0x164C5FF663790845, p0); }
	static Void _0x419615486BBF1956(Any p0) { return _i<Void>(0x419615486BBF1956, p0); }
	static Void _0x1A7CE7CD3E653485(Any p0) { return _i<Void>(0x1A7CE7CD3E653485, p0); }
	static Void _0x8C9D11605E59D955(Any p0) { return _i<Void>(0x8C9D11605E59D955, p0); }
	static Void _0xBFAFDB5FAAA5C5AB(Any p0) { return _i<Void>(0xBFAFDB5FAAA5C5AB, p0); }
	static Void playstats_friend_activity(Any p0, Any p1) { return _i<Void>(0x0F71DE29AB2258F1, p0, p1); }
	static Void _0x0EACDF8487D5155A(Any p0) { return _i<Void>(0x0EACDF8487D5155A, p0); }
	static Void _0xDAF80797FC534BEC(Any p0) { return _i<Void>(0xDAF80797FC534BEC, p0); }
	static Void _0xF4FF020A08BC8863(Any p0, Any p1) { return _i<Void>(0xF4FF020A08BC8863, p0, p1); }
	static Void _0x60EEDC12AF66E846(Any p0) { return _i<Void>(0x60EEDC12AF66E846, p0); }
	static Void _0xCB00196B31C39EB1(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xCB00196B31C39EB1, p0, p1, p2, p3); }
	static Void _0x5DA3A8DE8CB6226F(int time) { return _i<Void>(0x5DA3A8DE8CB6226F, time); }
	static Void _0x7D8BA05688AD64C7(Any p0) { return _i<Void>(0x7D8BA05688AD64C7, p0); }
	static Void _0x2B69F5074C894811(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x2B69F5074C894811, p0, p1, p2, p3); }
	static Void _0xF8C54A461C3E11DC(Any* p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0xF8C54A461C3E11DC, p0, p1, p2, p3); }
	static Void _0xF5BB8DAC426A52C0(Any* p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0xF5BB8DAC426A52C0, p0, p1, p2, p3); }
	static Void _0xA736CF7FB7C5BFF4(Any* p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0xA736CF7FB7C5BFF4, p0, p1, p2, p3); }
	static Void _0x14E0B2D1AD1044E0(Any* p0, Any* p1, Any* p2, Any* p3) { return _i<Void>(0x14E0B2D1AD1044E0, p0, p1, p2, p3); }
	static Void _0xC5BE134EC7BA96A0(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xC5BE134EC7BA96A0, p0, p1, p2, p3, p4); }
	static Void playstats_match_started(Any p0, Any p1, Any p2) { return _i<Void>(0xBC80E22DED931E3D, p0, p1, p2); }
	static Void _0x8989CBD7B4E82534(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x8989CBD7B4E82534, p0, p1, p2, p3, p4, p5, p6); }
	static Void _0x03C2EEBB04B3FB72(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<Void>(0x03C2EEBB04B3FB72, p0, p1, p2, p3, p4, p5, p6); }
	static Void _0xF534D94DFA2EAD26(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xF534D94DFA2EAD26, p0, p1, p2, p3, p4); }
	static Void _0xCC25A4553DFBF9EA(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xCC25A4553DFBF9EA, p0, p1, p2, p3, p4); }
	static Void playstats_mission_checkpoint(Any* p0, Any p1, Any p2, Any p3) { return _i<Void>(0xC900596A63978C1D, p0, p1, p2, p3); }
	static Void _0xBF371CD2B64212FD(Any p0) { return _i<Void>(0xBF371CD2B64212FD, p0); }
	static Void playstats_mission_over(Any* p0, Any p1, Any p2, bool p3, bool p4, bool p5) { return _i<Void>(0x7C4BB33A8CED7324, p0, p1, p2, p3, p4, p5); }
	static Void playstats_mission_started(Any* p0, Any p1, Any p2, bool p3) { return _i<Void>(0xC19A2925C34D2231, p0, p1, p2, p3); }
	static Void playstats_npc_invite(Any* p0) { return _i<Void>(0x93054C88E6AA7C44, p0); }
	static Void _0x9572BD4DD6B72122(Any p0) { return _i<Void>(0x9572BD4DD6B72122, p0); }
	static Void _0x203B381133817079(Any p0) { return _i<Void>(0x203B381133817079, p0); }
	static Void playstats_prop_change(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xBA739D6D5A05D6E7, p0, p1, p2, p3); }
	static Void _0x90D0622866E80445(int p0, const char* p1) { return _i<Void>(0x90D0622866E80445, p0, p1); }
	static Void playstats_race_checkpoint(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x9C375C315099DDE4, p0, p1, p2, p3, p4); }
	static Void _0xADDD1C754E2E2914(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Void>(0xADDD1C754E2E2914, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void _0x71862B1D855F32E1(Any* p0, Any p1, Any p2, Any p3) { return _i<Void>(0x71862B1D855F32E1, p0, p1, p2, p3); }
	static Void playstats_rank_up(Any p0) { return _i<Void>(0xC7F2DE41D102BFB4, p0); }
	static Void _0x04D90BA8207ADA2D(Any p0) { return _i<Void>(0x04D90BA8207ADA2D, p0); }
	static Void _0x27AA1C973CACFE63(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return _i<Void>(0x27AA1C973CACFE63, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static Void _0x121FB4DDDC2D5291(Any p0, Any p1, Any p2, float p3) { return _i<Void>(0x121FB4DDDC2D5291, p0, p1, p2, p3); }
	static Void _0xC729991A9065376E(Any p0) { return _i<Void>(0xC729991A9065376E, p0); }
	static Void _0xD1032E482629049E(bool p0) { return _i<Void>(0xD1032E482629049E, p0); }
	static Void playstats_shop_item(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x176852ACAAC173D1, p0, p1, p2, p3, p4); }
	static Void _0x320C35147D5B5DDD(Any p0) { return _i<Void>(0x320C35147D5B5DDD, p0); }
	static Void _0xBE509B0A3693DE8B(Any p0) { return _i<Void>(0xBE509B0A3693DE8B, p0); }
	static Void _0x098760C7461724CD() { return _i<Void>(0x098760C7461724CD); }
	static Void _0x928DBFB892638EF3() { return _i<Void>(0x928DBFB892638EF3); }
	static Void _0x8A800DACCC0DA55D() { return _i<Void>(0x8A800DACCC0DA55D); }
	static Void _0x0A50D2604E05CB94(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x0A50D2604E05CB94, p0, p1, p2, p3, p4); }
	static Void _0xE95C8A1875A02CA4(Any p0, Any p1, Any p2) { return _i<Void>(0xE95C8A1875A02CA4, p0, p1, p2); }
	static Void playstats_website_visited(uint32_t scaleformHash, int p1) { return _i<Void>(0xDDF24D535060F811, scaleformHash, p1); }
	static Void _0x30A6614C1F7799B8(Any p0, float p1, Any p2) { return _i<Void>(0x30A6614C1F7799B8, p0, p1, p2); }
	//STATS::_0x11FF1C80276097ED(joaat("num_hidden_packages_0"), 50, 0);
	static Void _0x11FF1C80276097ED(Any p0, Any p1, Any p2) { return _i<Void>(0x11FF1C80276097ED, p0, p1, p2); }
	static Void _0x6483C25849031C4F(Any p0, Any p1, Any p2, Any* p3) { return _i<Void>(0x6483C25849031C4F, p0, p1, p2, p3); }
	static Void _0x7033EEFD9B28088E(Any p0) { return _i<Void>(0x7033EEFD9B28088E, p0); }
	static Void _0x015B03EE1C43E6EC(Any p0) { return _i<Void>(0x015B03EE1C43E6EC, p0); }
	static Void _0xAA525DFF66BB82F5(Any p0, Any p1, Any p2) { return _i<Void>(0xAA525DFF66BB82F5, p0, p1, p2); }
	static Void _0x0D01D20616FC73FB(Any p0, Any p1) { return _i<Void>(0x0D01D20616FC73FB, p0, p1); }
	static Void _0xC141B8917E0017EC() { return _i<Void>(0xC141B8917E0017EC); }
	static Void set_has_content_unlocks_flags(Any p0) { return _i<Void>(0xDAC073C7901F9E15, p0); }
	static Void _0x723C1CE13FBFDB67(Any p0, Any p1) { return _i<Void>(0x723C1CE13FBFDB67, p0, p1); }
	static Void _0x55384438FC55AD8E(int value) { return _i<Void>(0x55384438FC55AD8E, value); }
	static Void _0x38BAAA5DD4C9D19F(int value) { return _i<Void>(0x38BAAA5DD4C9D19F, value); }
	static Void _0xF1A1803D3476F215(int value) { return _i<Void>(0xF1A1803D3476F215, value); }
	static Void _0xB475F27C6A994D65() { return _i<Void>(0xB475F27C6A994D65); }
	static Void _0xF6792800AC95350D(Any p0) { return _i<Void>(0xF6792800AC95350D, p0); }
	static Void _0x3EBEAC6C3F81F6BD(Any p0) { return _i<Void>(0x3EBEAC6C3F81F6BD, p0); }
	static Void _0x96E6D5150DBF1C09(Any p0, Any p1, Any p2) { return _i<Void>(0x96E6D5150DBF1C09, p0, p1, p2); }
	static Void _0x9B4BD21D69B1E609() { return _i<Void>(0x9B4BD21D69B1E609); }
	static Void _0xA8733668D1047B51(Any p0) { return _i<Void>(0xA8733668D1047B51, p0); }
	static Any stat_clear_slot_for_reload(int statSlot) { return _i<Any>(0xEB0A72181D4AA4AD, statSlot); }
	static bool _0x7F2C4CDF2E82DF4C(Any p0) { return _i<bool>(0x7F2C4CDF2E82DF4C, p0); }
	static Any _0xE496A53BA5F50A56(Any p0) { return _i<Any>(0xE496A53BA5F50A56, p0); }
	static bool _0x7E6946F68A38B74F(Any p0) { return _i<bool>(0x7E6946F68A38B74F, p0); }
	static bool _0xBED9F5693F34ED17(uint32_t statName, int p1, float* outValue) { return _i<bool>(0xBED9F5693F34ED17, statName, p1, outValue); }
	static bool _0x5A556B229A169402() { return _i<bool>(0x5A556B229A169402); }
	static bool _0xB1D2BB1E1631F5B1() { return _i<bool>(0xB1D2BB1E1631F5B1); }
	static Any stat_delete_slot(Any p0) { return _i<Any>(0x49A49BED12794D70, p0); }
	static Void _0x629526ABA383BCAA() { return _i<Void>(0x629526ABA383BCAA); }
	static Void _0x98E2BC1CA26287C3() { return _i<Void>(0x98E2BC1CA26287C3); }
	static bool stat_get_bool(uint32_t statHash, bool* outValue, int p2) { return _i<bool>(0x11B5E6D2AE73F48E, statHash, outValue, p2); }
	static bool stat_get_bool_masked(uint32_t statName, int mask, int p2) { return _i<bool>(0x10FE3F1B79F9B071, statName, mask, p2); }
	static Any _0x567384DFA67029E6() { return _i<Any>(0x567384DFA67029E6); }
	static Any _0x6E0A5253375C4584() { return _i<Any>(0x6E0A5253375C4584); }
	static Any _0xBA9749CC94C1FD85() { return _i<Any>(0xBA9749CC94C1FD85); }
	static Any _0x32CAC93C9DE73D32() { return _i<Any>(0x32CAC93C9DE73D32); }
	static Any _0x84A810B375E69C0E() { return _i<Any>(0x84A810B375E69C0E); }
	static Any _0x9EC8858184CD253A() { return _i<Any>(0x9EC8858184CD253A); }
	static Any _0xE8853FBCE7D8D0D6() { return _i<Any>(0xE8853FBCE7D8D0D6); }
	static Any _0xA943FD1722E11EFD() { return _i<Any>(0xA943FD1722E11EFD); }
	static Any _0xAFF47709F1D5DCCE() { return _i<Any>(0xAFF47709F1D5DCCE); }
	static Any _0x55A8BECAF28A4EB7() { return _i<Any>(0x55A8BECAF28A4EB7); }
	static bool stat_get_date(uint32_t statHash, Any* p1, Any p2, Any p3) { return _i<bool>(0x8B0FACEFC36C824B, statHash, p1, p2, p3); }
	static bool stat_get_float(uint32_t statHash, float* outValue, int p2) { return _i<bool>(0xD7AE6C9C9C6AC54C, statHash, outValue, p2); }
	static Any _0x1A8EA222F9C67DBB(Any p0) { return _i<Any>(0x1A8EA222F9C67DBB, p0); }
	static int stat_get_int(uint32_t statHash, int* outValue, int p2) { return _i<bool>(0x767FBC2AC802EF3D, statHash, outValue, p2); }
	static const char* stat_get_license_plate(uint32_t statName) { return _i<const char*>(0x5473D4195058B2E4, statName); }
	static Any _0xC0E0D686DDFC6EAE() { return _i<Any>(0xC0E0D686DDFC6EAE); }
	static bool stat_get_masked_int(Any p0, Any* p1, Any p2, Any p3, Any p4) { return _i<bool>(0x655185A06D9EEAAB, p0, p1, p2, p3, p4); }
	static int stat_get_number_of_days(uint32_t statName) { return _i<int>(0xE0E854F5280FB769, statName); }
	static int stat_get_number_of_hours(uint32_t statName) { return _i<int>(0xF2D4B2FE415AAFC3, statName); }
	static int stat_get_number_of_minutes(uint32_t statName) { return _i<int>(0x7583B4BE4C5A41B5, statName); }
	static int stat_get_number_of_seconds(uint32_t statName) { return _i<int>(0x2CE056FF3723F00B, statName); }
	static bool stat_get_pos(Any p0, Any* p1, Any* p2, Any* p3, Any p4) { return _i<bool>(0x350F82CCB186AA1B, p0, p1, p2, p3, p4); }
	static Any _0xF11F01D98113536A(Any p0) { return _i<Any>(0xF11F01D98113536A, p0); }
	static Any _0xCE5AA445ABA8DEE0(Any* p0) { return _i<Any>(0xCE5AA445ABA8DEE0, p0); }
	static Any _0x886913BBEACA68C1(Any* p0) { return _i<Any>(0x886913BBEACA68C1, p0); }
	static const char* stat_get_string(uint32_t statHash, int p1) { return _i<const char*>(0xE50384ACC2C3DB74, statHash, p1); }
	static const char* stat_get_user_id(Any p0) { return _i<const char*>(0x2365C388E393BBE2, p0); }
	static Any _0x0B8B7F74BF061C6D() { return _i<Any>(0x0B8B7F74BF061C6D); }
	static Void stat_increment(uint32_t statName, float value) { return _i<Void>(0x9B5A68C6489E9909, statName, value); }
	static Any _0xF9F2922717B819EC() { return _i<Any>(0xF9F2922717B819EC); }
	static Any _0x8B9CDBD6C566C38C() { return _i<Any>(0x8B9CDBD6C566C38C); }
	static Any _0xBE3DB208333D9844() { return _i<Any>(0xBE3DB208333D9844); }
	static bool stat_load(int p0) { return _i<bool>(0xA651443F437B1CE6, p0); }
	static bool _0xECB41AC6AB754401() { return _i<bool>(0xECB41AC6AB754401); }
	static bool stat_load_pending(Any p0) { return _i<bool>(0xA1750FFAFA181661, p0); }
	static Void _0xA78B8FA58200DA56(int p0) { return _i<Void>(0xA78B8FA58200DA56, p0); }
	static Any _0x4C89FE2BDEB3F169() { return _i<Any>(0x4C89FE2BDEB3F169); }
	static Any _0x5BD5F255321C4AAF(Any p0) { return _i<Any>(0x5BD5F255321C4AAF, p0); }
	static Any _0xDEAAF77EB3687E97(Any p0, Any* p1) { return _i<Any>(0xDEAAF77EB3687E97, p0, p1); }
	static Any _0xC6E0E2616A7576BB() { return _i<Any>(0xC6E0E2616A7576BB); }
	static Void _0xC847B43F369AC0B5() { return _i<Void>(0xC847B43F369AC0B5); }
	static Any _0x9A62EC95AE10E011() { return _i<Any>(0x9A62EC95AE10E011); }
	static bool _0xA5C80D8E768A9E66(Any* p0) { return _i<bool>(0xA5C80D8E768A9E66, p0); }
	static Void _0x428EAF89E24F6C36(Any p0, float p1) { return _i<Void>(0x428EAF89E24F6C36, p0, p1); }
	static Void _0x26D7399B9587FE89(int p0) { return _i<Void>(0x26D7399B9587FE89, p0); }
	static bool stat_save(int p0, bool p1, int p2) { return _i<bool>(0xE07BCA305B82D2FD, p0, p1, p2); }
	static Any _0x4FEF53183C3C6414() { return _i<Any>(0x4FEF53183C3C6414); }
	static bool _0x3270F67EED31FBC1(Any p0, Any* p1, Any* p2) { return _i<bool>(0x3270F67EED31FBC1, p0, p1, p2); }
	static Any _0xC70DDCE56D0D3A99() { return _i<Any>(0xC70DDCE56D0D3A99); }
	static Any stat_save_pending() { return _i<Any>(0x7D3A583856F2C5AC); }
	static Any stat_save_pending_or_requested() { return _i<Any>(0xBBB6AD006F1BBEA3); }
	static Void _0xF434A10BA01C37D0(bool p0) { return _i<Void>(0xF434A10BA01C37D0, p0); }
	static bool stat_set_bool(uint32_t statName, bool value, bool save) { return _i<bool>(0x4B33C4243DE0C432, statName, value, save); }
	static bool stat_set_bool_masked(uint32_t statName, bool value, int mask, bool save) { return _i<bool>(0x5BC62EC1937B9E5B, statName, value, mask, save); }
	static Void _0x047CBED6F6F8B63C() { return _i<Void>(0x047CBED6F6F8B63C); }
	static bool stat_set_current_posix_time(uint32_t statName, bool p1) { return _i<bool>(0xC2F84B7F9C4D0C61, statName, p1); }
	static bool stat_set_date(uint32_t statName, Any* value, int numFields, bool save) { return _i<bool>(0x2C29BFB64F4FCBE4, statName, value, numFields, save); }
	static bool stat_set_float(uint32_t statName, float value, bool save) { return _i<bool>(0x4851997F37FE9B3C, statName, value, save); }
	static bool stat_set_gxt_label(uint32_t statName, const char* value, bool save) { return _i<bool>(0x17695002FD8B2AE0, statName, value, save); }
	static bool stat_set_int(uint32_t statName, int value, bool save) { return _i<bool>(0xB3271D7AB655B441, statName, value, save); }
	static bool stat_set_license_plate(uint32_t statName, const char* str) { return _i<bool>(0x69FF13266D7296DA, statName, str); }
	static bool stat_set_masked_int(uint32_t statName, Any p1, Any p2, int p3, bool save) { return _i<bool>(0x7BBB1B54583ED410, statName, p1, p2, p3, save); }
	static Void _0x5688585E6D563CD8(Any p0) { return _i<Void>(0x5688585E6D563CD8, p0); }
	static bool stat_set_pos(uint32_t statName, float x, float y, float z, bool save) { return _i<bool>(0xDB283FDE680FE72E, statName, x, y, z, save); }
	static Void stat_set_profile_setting(int profileSetting, int value) { return _i<Void>(0x68F01422BE1D838F, profileSetting, value); }
	static bool stat_set_string(uint32_t statName, const char* value, bool save) { return _i<bool>(0xA87B2335D12531D7, statName, value, save); }
	static bool stat_set_user_id(uint32_t statName, const char* value, bool save) { return _i<bool>(0x8CDDF1E452BABE11, statName, value, save); }
	static bool stat_slot_is_loaded(Any p0) { return _i<bool>(0x0D0A9F0E7BD91E3C, p0); }
	static Any _0x33D72899E24C3365(Any p0, Any p1) { return _i<Any>(0x33D72899E24C3365, p0, p1); }
	static Any _0xA761D4AC6115623D() { return _i<Any>(0xA761D4AC6115623D); }
	static Void playstats_oddjob_done(Any p0, Any p1, Any p2) { return _i<Void>(0x69DEA3E9DB727B4C, p0, p1, p2); }

	static bool _0x0BC3144DEB678666(uint32_t modelHash) { return _i<bool>(0x0BC3144DEB678666, modelHash); }
	static Void _0x8E2A065ABDAE6994() { return _i<Void>(0x8E2A065ABDAE6994); }
	static Void _0xAD5FDF34B81BFE79() { return _i<Void>(0xAD5FDF34B81BFE79); }
	static Void _0x74DE2E8739086740() { return _i<Void>(0x74DE2E8739086740); }
	static Void _0x43D1680C6D19A8E9() { return _i<Void>(0x43D1680C6D19A8E9); }
	static Void begin_srl() { return _i<Void>(0x9BADDC94EF83B823); }
	static Void clear_focus() { return _i<Void>(0x31B73D1EA9F01DA2); }
	static Void clear_hd_area() { return _i<Void>(0xCE58B1CFB9290813); }
	static Void _0xBD605B8E0E18B3BB() { return _i<Void>(0xBD605B8E0E18B3BB); }
	static bool does_anim_dict_exist(const char* animDict) { return _i<bool>(0x2DA49C3B79856961, animDict); }
	static Void _0xD4793DFF3AF2ABCD() { return _i<Void>(0xD4793DFF3AF2ABCD); }
	static Void end_srl() { return _i<Void>(0x0A41540E63C9EE17); }
	static Void _0x03F1A106BDA7DD3E() { return _i<Void>(0x03F1A106BDA7DD3E); }
	static int get_ideal_player_switch_type(float x1, float y1, float z1, float x2, float y2, float z2) { return _i<int>(0xB5D7B26B45720E05, x1, y1, z1, x2, y2, z2); }
	static Any _0x0C15B0E443B2349D() { return _i<Any>(0x0C15B0E443B2349D); }
	static int get_number_of_streaming_requests() { return _i<int>(0x4060057271CEBC89); }
	static int get_player_short_switch_state() { return _i<int>(0x20F898A5D9782800); }
	static Any _0x5B48A06DD0E792A5() { return _i<Any>(0x5B48A06DD0E792A5); }
	static int _0x08C2D6C52A3104BB() { return _i<int>(0x08C2D6C52A3104BB); }
	static Any _0x78C0D93253149435() { return _i<Any>(0x78C0D93253149435); }
	static int get_player_switch_state() { return _i<int>(0x470555300D10B2A5); }
	static int get_player_switch_type() { return _i<int>(0xB3C94A90D9FC9E62); }
	static Any _0x3D3D8B3BE5A83D35() { return _i<Any>(0x3D3D8B3BE5A83D35); }
	static bool has_anim_dict_loaded(const char* animDict) { return _i<bool>(0xD031A9162D01088C, animDict); }
	static bool has_anim_set_loaded(const char* animSet) { return _i<bool>(0xC4EA073D86FB29B0, animSet); }
	static bool has_clipset_loaded(const char* clipSet) { return _i<bool>(0x318234F4F3738AF3, clipSet); }
	static bool has_collision_for_model_loaded(uint32_t model) { return _i<bool>(0x22CCA434E368F03A, model); }
	static bool has_model_loaded(uint32_t model) { return _i<bool>(0x98A4EB5D89A0C952, model); }
	static bool has_named_ptfx_asset_loaded(const char* fxName) { return _i<bool>(0x8702416E512EC454, fxName); }
	static bool has_ptfx_asset_loaded() { return _i<bool>(0xCA7D9B86ECA7481B); }
	static Void _0xB5A4DB34FE89B88A() { return _i<Void>(0xB5A4DB34FE89B88A); }
	static Void _0x63EB2B972A218CAC() { return _i<Void>(0x63EB2B972A218CAC); }
	static Void _0xF4A0DADB70F57FA6() { return _i<Void>(0xF4A0DADB70F57FA6); }
	static Any _0x5068F488DDB54DD8() { return _i<Any>(0x5068F488DDB54DD8); }
	static Any _0xFB199266061F820A() { return _i<Any>(0xFB199266061F820A); }
	static Void _0x95A7DABDDBB78AE7(Any* p0, Any* p1) { return _i<Void>(0x95A7DABDDBB78AE7, p0, p1); }
	static bool is_entity_focus(Entity entity) { return _i<bool>(0x2DDFF3FB9075D747, entity); }
	static bool is_ipl_active(const char* iplName) { return _i<bool>(0x88A741E44A2B3495, iplName); }
	static bool is_model_a_ped(uint32_t modelHash) { return _i<bool>(0x75816577FEA6DAD5, modelHash); }
	static bool is_model_a_vehicle(uint32_t model) { return _i<bool>(0x19AAC8F07BFEC53E, model); }
	static bool is_model_in_cdimage(uint32_t model) { return _i<bool>(0x35B9E0803292B641, model); }
	static bool is_model_valid(uint32_t model) { return _i<bool>(0xC0296A2EDF545E92, model); }
	static bool is_network_loading_scene() { return _i<bool>(0x41CA5A33160EA4AB); }
	static bool is_new_load_scene_active() { return _i<bool>(0xA41A05B6CB741B85); }
	static bool is_new_load_scene_loaded() { return _i<bool>(0x01B8247A7A8B9AD1); }
	static bool is_player_switch_in_progress() { return _i<bool>(0xD9D2CFFF49FAB35F); }
	static Any _0x71E7B2E657449AAD() { return _i<Any>(0x71E7B2E657449AAD); }
	static bool is_srl_loaded() { return _i<bool>(0xD0263801A4C5B0BB); }
	static Any _0x07C313F94746702C(Any p0) { return _i<Any>(0x07C313F94746702C, p0); }
	static Any _0xBC9823AB80A3DCAC() { return _i<Any>(0xBC9823AB80A3DCAC); }
	static Any _0xDFA80CB25D0A19B3() { return _i<Any>(0xDFA80CB25D0A19B3); }
	static Any _0x5B74EA8CFD5E3E7E() { return _i<Any>(0x5B74EA8CFD5E3E7E); }
	static Any _0x933BBEEB8C61B5F4() { return _i<Any>(0x933BBEEB8C61B5F4); }
	static Void load_all_objects_now() { return _i<Void>(0xBD6E84632DD4CB3F); }
	static Void load_scene(float x, float y, float z) { return _i<Void>(0x4448EB75B4904BDB, x, y, z); }
	static Any network_update_load_scene() { return _i<Any>(0xC4582015556D1C46); }
	static bool new_load_scene_start(float p0, float p1, float p2, float p3, float p4, float p5, float p6, Any p7) { return _i<bool>(0x212A8D0D2BABFAC2, p0, p1, p2, p3, p4, p5, p6, p7); }
	static bool new_load_scene_start_sphere(float x, float y, float z, float radius, Any p4) { return _i<bool>(0xACCFB4ACF53551B0, x, y, z, radius, p4); }
	static Void new_load_scene_stop() { return _i<Void>(0xC197616D221FF4A4); }
	static Void _0xA76359FC80B2438E(float p0) { return _i<Void>(0xA76359FC80B2438E, p0); }
	static Void prefetch_srl(const char* srl) { return _i<Void>(0x3D245789CE12982C, srl); }
	static Void _0xBED8CA5FF5E04113(float p0, float p1, float p2, float p3) { return _i<Void>(0xBED8CA5FF5E04113, p0, p1, p2, p3); }
	static Void remove_anim_dict(const char* animDict) { return _i<Void>(0xF66A602F829E2A06, animDict); }
	static Void remove_anim_set(const char* animSet) { return _i<Void>(0x16350528F93024B3, animSet); }
	static Void remove_clip_set(const char* clipSet) { return _i<Void>(0x01F73A131C18CD94, clipSet); }
	static Void remove_ipl(const char* iplName) { return _i<Void>(0xEE6C5AD3ECE0A82D, iplName); }
	static Void _0xF086AD9354FAC3A3(Any p0) { return _i<Void>(0xF086AD9354FAC3A3, p0); }
	static Void remove_named_ptfx_asset(const char* fxName) { return _i<Void>(0x5F61EBBE1A00F96D, fxName); }
	static Void remove_ptfx_asset() { return _i<Void>(0x88C6814073DD4A73); }
	static Void request_collision_at_coord(float x, float y, float z) { return _i<Void>(0x07503F7948F491A7, x, y, z); }
	static Void request_additional_collision_at_coord(float p0, float p1, float p2) { return _i<Void>(0xC9156DC11411A9EA, p0, p1, p2); }
	static Void request_anim_dict(const char* animDict) { return _i<Void>(0xD3BD40951412FEF6, animDict); }
	static Void request_anim_set(const char* animSet) { return _i<Void>(0x6EA47DAE7FAD0EED, animSet); }
	static Void request_clipset(const char* clipSet) { return _i<Void>(0xD2A71E1A77418A49, clipSet); }
	static Void request_ipl(const char* iplName) { return _i<Void>(0x41B4893843BBDB74, iplName); }
	static Void request_menu_ped_model(uint32_t model) { return _i<Void>(0xA0261AEF7ACFC51E, model); }
	static Void request_model(uint32_t model) { return _i<Void>(0x963D27A58DF860AC, model); }
	static Void request_collision_for_model(uint32_t model) { return _i<Void>(0x923CB32A3B874FCB, model); }
	static Void request_interior_room_by_name(int interiorID, const char* roomName) { return _i<Void>(0x8A7A40100EDFEC58, interiorID, roomName); }
	static Void request_named_ptfx_asset(const char* fxName) { return _i<Void>(0xB80D8756B4668AB6, fxName); }
	static Void request_ptfx_asset() { return _i<Void>(0x944955FB2A3935C8); }
	static Void set_focus_entity(Entity entity) { return _i<Void>(0x198F77705FA0931D, entity); }
	static Void set_focus_area(float x, float y, float z, float offsetX, float offsetY, float offsetZ) { return _i<Void>(0xBB7454BAFF08FE25, x, y, z, offsetX, offsetY, offsetZ); }
	static Void set_game_pauses_for_streaming(bool toggle) { return _i<Void>(0x717CD6E6FAEBBEDC, toggle); }
	static Void set_hd_area(float x, float y, float z, float ground) { return _i<Void>(0xB85F26619073E775, x, y, z, ground); }
	static Void set_interior_active(int interiorID, bool toggle) { return _i<Void>(0xE37B76C387BE28ED, interiorID, toggle); }
	static Void _0xAF12610C644A35C9(const char* p0, bool p1) { return _i<Void>(0xAF12610C644A35C9, p0, p1); }
	static Void set_model_as_no_longer_needed(uint32_t model) { return _i<Void>(0xE532F5D78798DAAB, model); }
	static Void set_ped_population_budget(int p0) { return _i<Void>(0x8C95333CFC3340F3, p0); }
	static Void _0x5F2013F8BC24EE69(int p0) { return _i<Void>(0x5F2013F8BC24EE69, p0); }
	static Void _0x0FDE9DBFC0A6BC65(Any* p0) { return _i<Void>(0x0FDE9DBFC0A6BC65, p0); }
	static Void set_player_switch_outro(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, Any p8) { return _i<Void>(0xC208B673CE446B61, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Void set_reduce_ped_model_budget(bool toggle) { return _i<Void>(0x77B5F9A36BF96710, toggle); }
	static Void set_reduce_vehicle_model_budget(bool toggle) { return _i<Void>(0x80C527893080CCF3, toggle); }
	static Void _0x40AEFD1A244741F2(bool p0) { return _i<Void>(0x40AEFD1A244741F2, p0); }
	static Void _0x0811381EF5062FEC(Entity p0) { return _i<Void>(0x0811381EF5062FEC, p0); }
	static Void _0x1E9057A74FD73E23() { return _i<Void>(0x1E9057A74FD73E23); }
	static Void _0xF8155A7F03DDFC8E(Any p0) { return _i<Void>(0xF8155A7F03DDFC8E, p0); }
	static Void _0x20C6C7E4EB082A7F(bool p0) { return _i<Void>(0x20C6C7E4EB082A7F, p0); }
	static Void _0xEF39EE20C537E98C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0xEF39EE20C537E98C, p0, p1, p2, p3, p4, p5); }
	static Void _0xBEB2D9A1D9A8F55A(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0xBEB2D9A1D9A8F55A, p0, p1, p2, p3); }
	static Void set_srl_time(float p0) { return _i<Void>(0xA74A541C6884E7B8, p0); }
	static Void set_streaming(bool toggle) { return _i<Void>(0x6E0C692677008888, toggle); }
	static Void set_vehicle_population_budget(int p0) { return _i<Void>(0xCB9E1EB3BE2AF4E9, p0); }
	static Void shutdown_creator_budget() { return _i<Void>(0xCCE26000E9A6FAD7); }
	static Void start_player_switch(Ped from, Ped to, int flags, int switchType) { return _i<Void>(0xFAA23F2CBA159D67, from, to, flags, switchType); }
	static Void stop_player_switch() { return _i<Void>(0x95C0A5BBDC189AA1); }
	static Any _0x1F3F018BC3AFA77C(float p0, float p1, float p2, float p3, float p4, float p5, float p6, Any p7, Any p8) { return _i<Any>(0x1F3F018BC3AFA77C, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Any _0x0AD9710CEE2F590F(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return _i<Any>(0x0AD9710CEE2F590F, p0, p1, p2, p3, p4, p5, p6); }
	static Any format_focus_heading(float x, float y, float z, float rad, Any p4, Any p5) { return _i<Any>(0x219C7B8D53E429FD, x, y, z, rad, p4, p5); }
	static Void _0x1EE7D8DF4425F053(Any p0) { return _i<Void>(0x1EE7D8DF4425F053, p0); }
	static Any _0x7D41E9D2D17C5B2D(Any p0) { return _i<Any>(0x7D41E9D2D17C5B2D, p0); }
	static Void _0x472397322E92A856() { return _i<Void>(0x472397322E92A856); }
	static Void switch_out_player(Ped ped, int flags, int unknown) { return _i<Void>(0xAAB3200ED59016BC, ped, flags, unknown); }
	static Void _0xD8295AF639FD9CB8(Any p0) { return _i<Void>(0xD8295AF639FD9CB8, p0); }
	static Void set_ditch_police_models(bool toggle) { return _i<Void>(0x42CBE54462D92634, toggle); }
	static Void _0x4E52E752C76E7E7A(Any p0) { return _i<Void>(0x4E52E752C76E7E7A, p0); }

	static Void add_script_to_random_ped(const char* name, uint32_t model, float p2, float p3) { return _i<Void>(0x4EE5367468A65CCC, name, model, p2, p3); }
	static Void disable_script_brain_set(int brainSet) { return _i<Void>(0x14D8518E9760F08F, brainSet); }
	static Void enable_script_brain_set(int brainSet) { return _i<Void>(0x67AA4D73F0CFA86B, brainSet); }
	static bool is_object_within_brain_activation_range(Object object) { return _i<bool>(0xCCBA154209823057, object); }
	static bool is_world_point_within_brain_activation_range() { return _i<bool>(0xC5042CC6F5E3D450); }
	static Void _0x4D953DF78EBF8158() { return _i<Void>(0x4D953DF78EBF8158); }
	static Void _0x0B40ED49D7D6FF84() { return _i<Void>(0x0B40ED49D7D6FF84); }
	static Void _0x6E91B04E08773030(const char* action) { return _i<Void>(0x6E91B04E08773030, action); }
	static Void _0x6D6840CEE8845831(const char* action) { return _i<Void>(0x6D6840CEE8845831, action); }
	static Void register_object_script_brain(const char* scriptName, uint32_t objectName, int p2, float p3, int p4, int p5) { return _i<Void>(0x0BE84C318BA6EC22, scriptName, objectName, p2, p3, p4, p5); }
	static Void register_world_point_script_brain(Any* p0, float p1, Any p2) { return _i<Void>(0x3CDC7136613284BD, p0, p1, p2); }

	static Any _0x0419B167EE128F33(Any p0, Any p1) { return _i<Any>(0x0419B167EE128F33, p0, p1); }
	static Any _0xF3B0E0AED097A3F5(Any p0, Any p1) { return _i<Any>(0xF3B0E0AED097A3F5, p0, p1); }
	static Any _0xD3E51C0AB8C26EEE(Any p0, Any p1) { return _i<Any>(0xD3E51C0AB8C26EEE, p0, p1); }
	static Any _0x2CE544C68FB812A0(float p0, float p1, float p2, float p3, float p4, bool p5) { return _i<Any>(0x2CE544C68FB812A0, p0, p1, p2, p3, p4, p5); }
	static Any _0x54B0F614960F4A5F(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return _i<Any>(0x54B0F614960F4A5F, p0, p1, p2, p3, p4, p5, p6); }
	static Void _0x99AD4CCCB128CBC9(Vehicle vehicle) { return _i<Void>(0x99AD4CCCB128CBC9, vehicle); }
	static Void add_vehicle_stuck_check_with_warp(Any p0, float p1, Any p2, bool p3, bool p4, bool p5, Any p6) { return _i<Void>(0x2FA9923062DD396C, p0, p1, p2, p3, p4, p5, p6); }
	static Void add_vehicle_upsidedown_check(Vehicle vehicle) { return _i<Void>(0xB72E26D81006005B, vehicle); }
	static Void _0xC1F981A6F74F0C23(Any p0, bool p1) { return _i<Void>(0xC1F981A6F74F0C23, p0, p1); }
	static Void _0x0F3B4D4E43177236(Any p0, bool p1) { return _i<Void>(0x0F3B4D4E43177236, p0, p1); }
	static bool are_all_vehicle_windows_intact(Vehicle vehicle) { return _i<bool>(0x11D862A3E977A9EF, vehicle); }
	static bool are_any_vehicle_seats_free(Vehicle vehicle) { return _i<bool>(0x2D34FC3BC4ADB780, vehicle); }
	static bool _0xF78F94D60248C737(Any p0, bool p1) { return _i<bool>(0xF78F94D60248C737, p0, p1); }
	static bool are_propellers_undamaged(Vehicle vehicle) { return _i<bool>(0x755D6D5267CBBD7E, vehicle); }
	static bool are_vehicle_wings_intact(Vehicle vehicle) { return _i<bool>(0x5991A01434CE9677, vehicle); }
	static Void _0x6A98C2ECF57FA5D4(Vehicle vehicle, Entity entity) { return _i<Void>(0x6A98C2ECF57FA5D4, vehicle, entity); }
	static Void _0xA1DD82F3CCF9A01E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0xA1DD82F3CCF9A01E, p0, p1, p2, p3, p4, p5); }
	static Void _0x16B5E274BDE402F8(Vehicle vehicle, Vehicle trailer, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11) { return _i<Void>(0x16B5E274BDE402F8, vehicle, trailer, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static Void attach_vehicle_to_cargobob(Vehicle vehicle, Vehicle cargobob, int p2, float x, float y, float z) { return _i<Void>(0x4127F1D84E347769, vehicle, cargobob, p2, x, y, z); }
	static Void attach_vehicle_to_tow_truck(Vehicle towTruck, Vehicle vehicle, bool rear, float hookOffsetX, float hookOffsetY, float hookOffsetZ) { return _i<Void>(0x29A16F8D621C4508, towTruck, vehicle, rear, hookOffsetX, hookOffsetY, hookOffsetZ); }
	static Void attach_vehicle_to_trailer(Vehicle vehicle, Vehicle trailer, float radius) { return _i<Void>(0x3C7D42D58F770B54, vehicle, trailer, radius); }
	static Void set_vehicle_halt(Vehicle vehicle, float distance, int killEngine, bool unknown) { return _i<Void>(0x260BE8F09E326A20, vehicle, distance, killEngine, unknown); }
	static Any _0x2467A2D807D37CA3(Any p0) { return _i<Any>(0x2467A2D807D37CA3, p0); }
	static bool get_boat_anchor(Vehicle vehicle) { return _i<bool>(0x26C10ECBDA5D043B, vehicle); }
	static Any _0x2C1D8B3B19E517CC(Any p0, Any p1) { return _i<Any>(0x2C1D8B3B19E517CC, p0, p1); }
	static bool can_shuffle_seat(Vehicle vehicle, Any p1) { return _i<bool>(0x30785D90C956BF35, vehicle, p1); }
	static Void _0xE01903C47C7AC89E() { return _i<Void>(0xE01903C47C7AC89E); }
	static Void clear_vehicle_custom_primary_colour(Vehicle vehicle) { return _i<Void>(0x55E1D2758F34E437, vehicle); }
	static Void clear_vehicle_custom_secondary_colour(Vehicle vehicle) { return _i<Void>(0x5FFBDEEC3E8E2009, vehicle); }
	static Void _0x0A436B8643716D14() { return _i<Void>(0x0A436B8643716D14); }
	static Void _0x4419966C9936071A(Any p0) { return _i<Void>(0x4419966C9936071A, p0); }
	static Void _0xAA3F739ABDDCF21F() { return _i<Void>(0xAA3F739ABDDCF21F); }
	static Void _0x6D6AF961B72728AE(Vehicle vehicle) { return _i<Void>(0x6D6AF961B72728AE, vehicle); }
	static Void close_bomb_bay_doors(Vehicle vehicle) { return _i<Void>(0x3556041742A0DC74, vehicle); }
	static Void control_landing_gear(Vehicle vehicle, int state) { return _i<Void>(0xCFC8BE9A5E1FE575, vehicle, state); }
	static Void _0xE44A982368A4AF23(Vehicle vehicle, Vehicle vehicle2) { return _i<Void>(0xE44A982368A4AF23, vehicle, vehicle2); }
	static Vehicle create_mission_train(int variation, float x, float y, float z, bool direction) { return _i<Vehicle>(0x63C6CCA8E68AE8C8, variation, x, y, z, direction); }
	static Void create_pick_up_rope_for_cargobob(Vehicle cargobob, int state) { return _i<Void>(0x7BEB0C7A235F6F3B, cargobob, state); }
	static int create_script_vehicle_generator(float x, float y, float z, float heading, float p4, float p5, uint32_t modelHash, int p7, int p8, int p9, int p10, bool p11, bool p12, bool p13, bool p14, bool p15, int p16) { return _i<int>(0x9DEF883114668116, x, y, z, heading, p4, p5, modelHash, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); }
	static Vehicle create_vehicle(uint32_t modelHash, float x, float y, float z, float heading, bool isNetwork, bool p6, Any p7) { return _i<Vehicle>(0xAF35D0D2583051B0, modelHash, x, y, z, heading, isNetwork, p6, p7); }
	static Void delete_all_trains() { return _i<Void>(0x736A718577F39C7D); }
	static Void delete_mission_train(Vehicle* train) { return _i<Void>(0x5B76B14AE875C795, train); }
	static Void delete_script_vehicle_generator(int vehicleGenerator) { return _i<Void>(0x22102C9ABFCF125D, vehicleGenerator); }
	static Void delete_vehicle(Vehicle* vehicle) { return _i<Void>(0xEA386986E786A54F, vehicle); }
	static Void _0x7C0043FDFF6436BC(Vehicle vehicle) { return _i<Void>(0x7C0043FDFF6436BC, vehicle); }
	static Any _0xAF03011701811146(Any p0, Any p1) { return _i<Any>(0xAF03011701811146, p0, p1); }
	static bool detach_vehicle_from_any_cargobob(Vehicle vehicle) { return _i<bool>(0xADF7BE450512C12F, vehicle); }
	static bool detach_vehicle_from_any_tow_truck(Vehicle vehicle) { return _i<bool>(0xD0E9CE05A1E68CD8, vehicle); }
	static Void detach_vehicle_from_cargobob(Vehicle vehicle, Vehicle cargobob) { return _i<Void>(0x0E21D3DF1051399D, vehicle, cargobob); }
	static Void detach_vehicle_from_tow_truck(Vehicle towTruck, Vehicle vehicle) { return _i<Void>(0xC2DB6B6708350ED8, towTruck, vehicle); }
	static Void detach_vehicle_from_trailer(Vehicle vehicle) { return _i<Void>(0x90532EDF0D2BDD86, vehicle); }
	static Void _0xEF49CF0270307CBE() { return _i<Void>(0xEF49CF0270307CBE); }
	static Void _0x500873A45724C863(Vehicle vehicle, Any p1) { return _i<Void>(0x500873A45724C863, vehicle, p1); }
	static Void disable_plane_aileron(Vehicle vehicle, bool p1, bool p2) { return _i<Void>(0x23428FC53C60919C, vehicle, p1, p2); }
	static Void _0xF0E4BA16D1DB546C(Vehicle vehicle, int p1, int p2) { return _i<Void>(0xF0E4BA16D1DB546C, vehicle, p1, p2); }
	static Void _0xF25E02CB9C5818F8() { return _i<Void>(0xF25E02CB9C5818F8); }
	static Void _0x32CAEDF24A583345(Any p0) { return _i<Void>(0x32CAEDF24A583345, p0); }
	static Void disable_vehicle_weapon(bool disabled, uint32_t weaponHash, Vehicle vehicle, Ped owner) { return _i<Void>(0xF4FC6A6F67D8D856, disabled, weaponHash, vehicle, owner); }
	static bool does_cargobob_have_pickup_magnet(Vehicle cargobob) { return _i<bool>(0x6E08BF5B3722BAC9, cargobob); }
	static bool does_cargobob_have_pick_up_rope(Vehicle cargobob) { return _i<bool>(0x1821D91AD4B56108, cargobob); }
	static bool does_extra_exist(Vehicle vehicle, int extraId) { return _i<bool>(0x1262D55792428154, vehicle, extraId); }
	static bool does_script_vehicle_generator_exist(int vehicleGenerator) { return _i<bool>(0xF6086BC836400876, vehicleGenerator); }
	static Any _0x4E417C547182C84D(Any p0) { return _i<Any>(0x4E417C547182C84D, p0); }
	static bool does_vehicle_exist_with_decorator(const char* decorator) { return _i<bool>(0x956B409B984D9BF7, decorator); }
	static bool does_vehicle_have_roof(Vehicle vehicle) { return _i<bool>(0x8AC862B0B32C5B80, vehicle); }
	static bool does_vehicle_have_stuck_vehicle_check(Vehicle vehicle) { return _i<bool>(0x57E4C39DE5EE8470, vehicle); }
	static bool does_vehicle_have_weapons(Vehicle vehicle) { return _i<bool>(0x25ECB9F8017D98E0, vehicle); }
	static Void _0xF87D9F2301F7D206(Any p0) { return _i<Void>(0xF87D9F2301F7D206, p0); }
	static Void explode_vehicle(Vehicle vehicle, bool isAudible, bool isInvisible) { return _i<Void>(0xBA71116ADF5B514C, vehicle, isAudible, isInvisible); }
	static Void explode_vehicle_in_cutscene(Vehicle vehicle, bool p1) { return _i<Void>(0x786A4EB67B01BF0B, vehicle, p1); }
	static Vehicle get_vehicle_attached_to_entity(Object object) { return _i<Vehicle>(0x375E7FC44F21C8AB, object); }
	static Void fix_vehicle_window(Vehicle vehicle, int index) { return _i<Void>(0x772282EBEB95E682, vehicle, index); }
	static Void _0x1F2E4E06DEA8992B(Any p0, bool p1) { return _i<Void>(0x1F2E4E06DEA8992B, p0, p1); }
	static Void _0x33506883545AC0DF(Vehicle vehicle, bool p1) { return _i<Void>(0x33506883545AC0DF, vehicle, p1); }
	static Void _0x99CAD8E7AFDB60FA(Vehicle vehicle, float p1, float p2) { return _i<Void>(0x99CAD8E7AFDB60FA, vehicle, p1, p2); }
	static bool _0xA4822F1CF23F4810(math::vector3<float>* outVec, Any p1, math::vector3<float>* outVec1, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return _i<bool>(0xA4822F1CF23F4810, outVec, p1, outVec1, p3, p4, p5, p6, p7, p8); }
	static int get_all_vehicles(Any* vehArray) { return _i<int>(0x9B8E1BF04B51F2E8, vehArray); }
	static Any get_are_bomb_bay_doors_open(Any p0) { return _i<Any>(0xD0917A423314BBA8, p0); }
	static math::vector3<float> get_cargobob_hook_position(Vehicle cargobob) { return _i<math::vector3<float>>(0xCBDB9B923CACC92D, cargobob); }
	static float _0x6636C535F6CC2725(Vehicle vehicle) { return _i<float>(0x6636C535F6CC2725, vehicle); }
	static float _0x5AA3F878A178C4FC(uint32_t modelHash) { return _i<float>(0x5AA3F878A178C4FC, modelHash); }
	static Any _0xEC69ADF931AAE0C3(Any p0) { return _i<Any>(0xEC69ADF931AAE0C3, p0); }
	static Any _0x51F30DB60626A20E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return _i<Any>(0x51F30DB60626A20E, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static Any has_vehicle_jumping_ability(Vehicle vehicle) { return _i<Any>(0x9078C0C5EF8C19E9, vehicle); }
	static Vehicle get_closest_vehicle(float x, float y, float z, float radius, uint32_t modelHash, int flags) { return _i<Vehicle>(0xF73EB622C4F1689B, x, y, z, radius, modelHash, flags); }
	static int get_convertible_roof_state(Vehicle vehicle) { return _i<int>(0xF8C397922FC03F41, vehicle); }
	static Any get_current_playback_for_vehicle(Any p0) { return _i<Any>(0x42BC05C27A946054, p0); }
	static const char* get_display_name_from_vehicle_model(uint32_t modelHash) { return _i<const char*>(0xB215AAC32D25D019, modelHash); }
	static bool is_vehicle_damaged(Vehicle vehicle) { return _i<bool>(0xBCDC5017D3CE1E9E, vehicle); }
	static Any _0x99093F60746708CA(Any p0) { return _i<Any>(0x99093F60746708CA, p0); }
	static Entity get_entity_attached_to_tow_truck(Vehicle towTruck) { return _i<Entity>(0xEFEA18DCF10F8F75, towTruck); }
	static math::vector3<float> get_entry_position_of_door(Vehicle vehicle, int doorIndex) { return _i<math::vector3<float>>(0xC0572928C0ABFDA3, vehicle, doorIndex); }
	static float get_vehicle_suspension_height(Vehicle vehicle) { return _i<float>(0x53952FD2BAA19F17, vehicle); }
	static float _0xC6AD107DDC9054CC(uint32_t modelHash) { return _i<float>(0xC6AD107DDC9054CC, modelHash); }
	static Any get_has_lowerable_wheels(Vehicle vehicle) { return _i<Any>(0xDCA174A42133F08C, vehicle); }
	static bool has_vehicle_rocket_boost(Vehicle vehicle) { return _i<bool>(0x36D782F68B309BDA, vehicle); }
	static float get_heli_main_rotor_health(Vehicle vehicle) { return _i<float>(0xE4CB7541F413D2C5, vehicle); }
	static float get_heli_engine_health(Vehicle vehicle) { return _i<float>(0xAC51915D27E4A5F7, vehicle); }
	static float get_heli_tail_rotor_health(Vehicle vehicle) { return _i<float>(0xAE8CE82A4219AC8C, vehicle); }
	static Any _0xA01BC64DD4BFBBAC(Vehicle vehicle, int p1) { return _i<Any>(0xA01BC64DD4BFBBAC, vehicle, p1); }
	static Any _0xBA91D045575699AD(Any p0) { return _i<Any>(0xBA91D045575699AD, p0); }
	static Any does_vehicle_have_door(Vehicle vehicle, int doorIndex) { return _i<Any>(0x645F4B6E8499F632, vehicle, doorIndex); }
	static bool get_is_left_vehicle_headlight_damaged(Vehicle vehicle) { return _i<bool>(0x5EF77C9ADD3B11A3, vehicle); }
	static bool get_is_right_vehicle_headlight_damaged(Vehicle vehicle) { return _i<bool>(0xA7ECB73355EB2F20, vehicle); }
	static bool get_is_vehicle_engine_running(Vehicle vehicle) { return _i<bool>(0xAE31E7DF9B5B132E, vehicle); }
	static bool get_is_vehicle_primary_colour_custom(Vehicle vehicle) { return _i<bool>(0xF095C0405307B21B, vehicle); }
	static bool get_is_vehicle_secondary_colour_custom(Vehicle vehicle) { return _i<bool>(0x910A32E7AAD2656C, vehicle); }
	static Any _0x1DA0DA9CB3F0C8BF(Any p0) { return _i<Any>(0x1DA0DA9CB3F0C8BF, p0); }
	static int get_landing_gear_state(Vehicle vehicle) { return _i<int>(0x9B0F3DCA3DB0F4CD, vehicle); }
	static Vehicle get_last_driven_vehicle() { return _i<Vehicle>(0xB2D06FAEDE65B577); }
	static Ped get_last_ped_in_vehicle_seat(Vehicle vehicle, int seatIndex) { return _i<Ped>(0x83F969AA1EE2A664, vehicle, seatIndex); }
	static const char* get_livery_name(Vehicle vehicle, int liveryIndex) { return _i<const char*>(0xB4C7A93837C91A1F, vehicle, liveryIndex); }
	static const char* get_mod_slot_name(Vehicle vehicle, int modType) { return _i<const char*>(0x51F0FEB9F6AE98C0, vehicle, modType); }
	static const char* get_mod_text_label(Vehicle vehicle, int modType, int modValue) { return _i<const char*>(0x8935624F8C5592CC, vehicle, modType, modValue); }
	static int get_number_of_vehicle_colours(Vehicle vehicle) { return _i<int>(0x3B963160CD65D41E, vehicle); }
	static Any get_number_of_vehicle_doors(Vehicle vehicle) { return _i<Any>(0x92922A607497B14D, vehicle); }
	static int get_number_of_vehicle_number_plates() { return _i<int>(0x4C4D6B2644F458CB); }
	static int get_num_mod_colors(int p0, bool p1) { return _i<int>(0xA551BE18C11A476D, p0, p1); }
	static int get_num_mod_kits(Vehicle vehicle) { return _i<int>(0x33F2E3FE70EAAE1D, vehicle); }
	static int get_num_vehicle_mods(Vehicle vehicle, int modType) { return _i<int>(0xE38E9162A2500646, vehicle, modType); }
	static int get_num_vehicle_window_tints() { return _i<int>(0x9D1224004B3A6707); }
	static Ped get_ped_in_vehicle_seat(Vehicle vehicle, int index, Any p2) { return _i<Ped>(0xBB40DD2270B65366, vehicle, index, p2); }
	static Ped get_ped_using_vehicle_door(Vehicle vehicle, int doorIndex) { return _i<Ped>(0x218297BF0CFD853B, vehicle, doorIndex); }
	static float get_position_in_recording(Any p0) { return _i<float>(0x2DACD605FC681475, p0); }
	static math::vector3<float> get_position_of_vehicle_recording_at_time(int p0, float p1, const char* p2) { return _i<math::vector3<float>>(0xD242728AA6F0FBA2, p0, p1, p2); }
	static math::vector3<float> _0x92523B76657A517D(Any p0, float p1) { return _i<math::vector3<float>>(0x92523B76657A517D, p0, p1); }
	static Vehicle get_random_vehicle_back_bumper_in_sphere(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return _i<Vehicle>(0xB50807EABE20A8DC, p0, p1, p2, p3, p4, p5, p6); }
	static Vehicle get_random_vehicle_front_bumper_in_sphere(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return _i<Vehicle>(0xC5574E0AEB86BA68, p0, p1, p2, p3, p4, p5, p6); }
	static Vehicle get_random_vehicle_in_sphere(float x, float y, float z, float radius, uint32_t modelHash, int flags) { return _i<Vehicle>(0x386F6CE5BAF6091C, x, y, z, radius, modelHash, flags); }
	static math::vector3<float> get_rotation_of_vehicle_recording_at_time(Any p0, float p1, Any* p2) { return _i<math::vector3<float>>(0x2058206FBE79A8AD, p0, p1, p2); }
	static math::vector3<float> _0xF0F2103EFAF8CBA7(Any p0, float p1) { return _i<math::vector3<float>>(0xF0F2103EFAF8CBA7, p0, p1); }
	static float get_time_position_in_recording(Any p0) { return _i<float>(0x5746F3A7AB7FE544, p0); }
	static Any get_total_duration_of_vehicle_recording(Any p0, Any p1) { return _i<Any>(0x0E48D1C262390950, p0, p1); }
	static float get_total_duration_of_vehicle_recording_id(Any p0) { return _i<float>(0x102D125411A7B6E6, p0); }
	static Entity get_train_carriage(Vehicle train, int trailerNumber) { return _i<Entity>(0x08AAFD0814722BC3, train, trailerNumber); }
	static float get_vehicle_acceleration(Vehicle vehicle) { return _i<float>(0x5DD35C8D074E57AE, vehicle); }
	static Vehicle get_vehicle_attached_to_cargobob(Vehicle cargobob) { return _i<Vehicle>(0x873B82D42AC2B9E5, cargobob); }
	static float get_vehicle_body_health(Vehicle vehicle) { return _i<float>(0xF271147EB7B40F12, vehicle); }
	static Any set_vehicle_bombs(Any p0) { return _i<Any>(0xEA12BD130D7569A1, p0); }
	static Any can_vehicle_parachute_be_activated(Vehicle vehicle) { return _i<Any>(0xA916396DF4154EE3, vehicle); }
	static uint32_t get_vehicle_cause_of_destruction(Vehicle vehicle) { return _i<uint32_t>(0xE495D1EF4C91FD20, vehicle); }
	static int get_vehicle_class(Vehicle vehicle) { return _i<int>(0x29439776AAA00A62, vehicle); }
	static float get_vehicle_class_estimated_speed(int vehicleClass) { return _i<float>(0x00C09F246ABEDD82, vehicleClass); }
	static int get_vehicle_class_from_name(uint32_t modelHash) { return _i<int>(0xDEDF1C8BD47C2200, modelHash); }
	static float get_vehicle_class_max_acceleration(int vehicleClass) { return _i<float>(0x2F83E7E45D9EA7AE, vehicleClass); }
	static float get_vehicle_class_max_agility(int vehicleClass) { return _i<float>(0x4F930AD022D6DE3B, vehicleClass); }
	static float get_vehicle_class_max_braking(int vehicleClass) { return _i<float>(0x4BF54C16EC8FEC03, vehicleClass); }
	static float get_vehicle_class_max_traction(int vehicleClass) { return _i<float>(0xDBC86D85C5059461, vehicleClass); }
	static Void get_vehicle_color(Vehicle vehicle, int* r, int* g, int* b) { return _i<Void>(0xF3CC740D36221548, vehicle, r, g, b); }
	static Void get_vehicle_colours(Vehicle vehicle, int* colorPrimary, int* colorSecondary) { return _i<Void>(0xA19435F193E081AC, vehicle, colorPrimary, colorSecondary); }
	static int _0xEEBFC7A7EFDC35B4(Vehicle vehicle) { return _i<int>(0xEEBFC7A7EFDC35B4, vehicle); }
	static int get_vehicle_colour_combination(Vehicle vehicle) { return _i<int>(0x6A842D197F845D56, vehicle); }
	static Any get_vehicle_countermeasures(Any p0) { return _i<Any>(0xF846AA63DF56B804, p0); }
	static Any _0x36492C2F0D134C56(Any p0) { return _i<Any>(0x36492C2F0D134C56, p0); }
	static Void get_vehicle_custom_primary_colour(Vehicle vehicle, int* r, int* g, int* b) { return _i<Void>(0xB64CF2CCA9D95F52, vehicle, r, g, b); }
	static Void get_vehicle_custom_secondary_colour(Vehicle vehicle, int* r, int* g, int* b) { return _i<Void>(0x8389CD56CA8072DC, vehicle, r, g, b); }
	static math::vector3<float> get_vehicle_deformation_at_pos(Vehicle vehicle, float offsetX, float offsetY, float offsetZ) { return _i<math::vector3<float>>(0x4EC6CFBC7B2E9536, vehicle, offsetX, offsetY, offsetZ); }
	static float get_vehicle_dirt_level(Vehicle vehicle) { return _i<float>(0x8F17BC8BA08DA62B, vehicle); }
	static bool get_vehicle_doors_locked_for_player(Vehicle vehicle, Player player) { return _i<bool>(0xF6AF6CB341349015, vehicle, player); }
	static float get_vehicle_door_angle_ratio(Vehicle vehicle, int door) { return _i<float>(0xFE3F9C29F7B32BD5, vehicle, door); }
	static int get_vehicle_door_lock_status(Vehicle vehicle) { return _i<int>(0x25BC98A59C2EA962, vehicle); }
	static float get_vehicle_engine_health(Vehicle vehicle) { return _i<float>(0xC45D23BAF168AAB8, vehicle); }
	static float get_vehicle_enveff_scale(Vehicle vehicle) { return _i<float>(0xA82819CAC9C4C403, vehicle); }
	static float get_vehicle_estimated_max_speed(Vehicle vehicle) { return _i<float>(0x53AF99BAA671CA47, vehicle); }
	static Void get_vehicle_extra_colours(Vehicle vehicle, int* pearlescentColor, int* wheelColor) { return _i<Void>(0x3BC4245933A166F7, vehicle, pearlescentColor, wheelColor); }
	static Void get_vehicle_interior_colour(Vehicle vehicle, int* color) { return _i<Void>(0x7D1464D472D32136, vehicle, color); }
	static Void get_vehicle_dashboard_colour(Vehicle vehicle, int* color) { return _i<Void>(0xB7635E80A5C31BFF, vehicle, color); }
	static Any get_vehicle_hover_mode_percentage(Any p0) { return _i<Any>(0xDA62027C8BDB326E, p0); }
	static Any _0x50634E348C8D44EF(Any p0) { return _i<Any>(0x50634E348C8D44EF, p0); }
	static Any _0xE43701C36CAFF1A4(Any p0) { return _i<Any>(0xE43701C36CAFF1A4, p0); }
	static Any has_vehicle_parachute(Vehicle vehicle) { return _i<Any>(0xBC9CFF381338CB4F, vehicle); }
	static float get_vehicle_body_health2(Vehicle vehicle, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return _i<float>(0xB8EF61207C2393A9, vehicle, p1, p2, p3, p4, p5, p6); }
	static Any _0x6EAAEFC76ACC311F(Any p0) { return _i<Any>(0x6EAAEFC76ACC311F, p0); }
	static int _0xE6B0E8CFC3633BF0(Vehicle vehicle) { return _i<int>(0xE6B0E8CFC3633BF0, vehicle); }
	static Any _0xCA4AC3EAAE46EC7B(Any p0, Any p1) { return _i<Any>(0xCA4AC3EAAE46EC7B, p0, p1); }
	static Any _0x8533CAFDE1F0F336(Any p0) { return _i<Any>(0x8533CAFDE1F0F336, p0); }
	static bool _0xD4C4642CB7F50B5D(Vehicle vehicle) { return _i<bool>(0xD4C4642CB7F50B5D, vehicle); }
	static uint32_t get_vehicle_layout_hash(Vehicle vehicle) { return _i<uint32_t>(0x28D37D4F71AC5C58, vehicle); }
	static bool get_vehicle_lights_state(Vehicle vehicle, bool* lightsOn, bool* highbeamsOn) { return _i<bool>(0xB91B4C20085BD12F, vehicle, lightsOn, highbeamsOn); }
	static Any _0x60190048C0764A26(Any p0) { return _i<Any>(0x60190048C0764A26, p0); }
	static Any _0x5ECB40269053C0D4(Any p0) { return _i<Any>(0x5ECB40269053C0D4, p0); }
	static int get_vehicle_livery(Vehicle vehicle) { return _i<int>(0x2BB9230590DA5E8A, vehicle); }
	static int get_vehicle_livery_count(Vehicle vehicle) { return _i<int>(0x87B63E25A529D526, vehicle); }
	static bool get_vehicle_owner(Vehicle vehicle, Entity* entity) { return _i<bool>(0x8F5EBAB1F260CFCE, vehicle, entity); }
	static float get_vehicle_max_braking(Vehicle vehicle) { return _i<float>(0xAD7E85FC227197C4, vehicle); }
	static int get_vehicle_max_number_of_passengers(Vehicle vehicle) { return _i<int>(0xA7C4F2C6E744A550, vehicle); }
	static float get_vehicle_max_traction(Vehicle vehicle) { return _i<float>(0xA132FB5370554DB0, vehicle); }
	static int get_vehicle_mod(Vehicle vehicle, int modType) { return _i<int>(0x772960298DA26FDB, vehicle, modType); }
	static float get_vehicle_model_acceleration(uint32_t modelHash) { return _i<float>(0x8C044C5C84505B6A, modelHash); }
	static float _0x53409B5163D5B846(uint32_t modelHash) { return _i<float>(0x53409B5163D5B846, modelHash); }
	static float get_vehicle_model_max_speed(uint32_t modelHash) { return _i<float>(0xF417C2502FFFED43, modelHash); }
	static float get_vehicle_model_max_braking(uint32_t modelHash) { return _i<float>(0xDC53FD41B4ED944C, modelHash); }
	static float _0xBFBA3BA79CFF7EBF(uint32_t modelHash) { return _i<float>(0xBFBA3BA79CFF7EBF, modelHash); }
	static float get_vehicle_model_max_traction(uint32_t modelHash) { return _i<float>(0x539DE94D44FDFD0D, modelHash); }
	static int get_vehicle_model_number_of_seats(uint32_t modelHash) { return _i<int>(0x2AD93716F184EDA4, modelHash); }
	static Any _0x5873C14A52D74236(Any p0) { return _i<Any>(0x5873C14A52D74236, p0); }
	static Void get_vehicle_mod_color1(Vehicle vehicle, int* paintType, int* color, int* p3) { return _i<Void>(0xE8D65CA700C9A693, vehicle, paintType, color, p3); }
	static const char* get_vehicle_mod_color1_name(Vehicle vehicle, bool p1) { return _i<const char*>(0xB45085B721EFD38C, vehicle, p1); }
	static Void get_vehicle_mod_color2(Vehicle vehicle, int* paintType, int* color) { return _i<Void>(0x81592BE4E3878728, vehicle, paintType, color); }
	static const char* get_vehicle_mod_color2_name(Vehicle vehicle) { return _i<const char*>(0x4967A516ED23A5A1, vehicle); }
	static Any get_vehicle_mod_data(Vehicle vehicle, int modType, int modIndex) { return _i<Any>(0x4593CF82AA179706, vehicle, modType, modIndex); }
	static int get_vehicle_mod_kit(Vehicle vehicle) { return _i<int>(0x6325D1A044AE510D, vehicle); }
	static int get_vehicle_mod_kit_type(Vehicle vehicle) { return _i<int>(0xFC058F5121E54C32, vehicle); }
	static Any get_vehicle_mod_modifier_value(Vehicle vehicle, int modType, int modIndex) { return _i<Any>(0x90A38E9838E0A8C1, vehicle, modType, modIndex); }
	static bool get_vehicle_mod_variation(Vehicle vehicle, int modType) { return _i<bool>(0xB3924ECD70E095DC, vehicle, modType); }
	static Void get_vehicle_neon_lights_colour(Vehicle vehicle, int* r, int* g, int* b) { return _i<Void>(0x7619EEE8C886757F, vehicle, r, g, b); }
	static bool is_vehicle_neon_light_enabled(Vehicle vehicle, int index) { return _i<bool>(0x8C4B92553E4766A5, vehicle, index); }
	static int get_vehicle_number_of_passengers(Vehicle vehicle) { return _i<int>(0x24CB2137731FFE89, vehicle); }
	static const char* get_vehicle_number_plate_text(Vehicle vehicle) { return _i<const char*>(0x7CE1CCB9B293020E, vehicle); }
	static int get_vehicle_number_plate_text_index(Vehicle vehicle) { return _i<int>(0xF11BC2DD9A3E7195, vehicle); }
	static Any _0x2C8CBFE1EA5FC631(Any p0) { return _i<Any>(0x2C8CBFE1EA5FC631, p0); }
	static Any _0x42A4BEB35D372407(Any p0) { return _i<Any>(0x42A4BEB35D372407, p0); }
	static float get_vehicle_petrol_tank_health(Vehicle vehicle) { return _i<float>(0x7D5DABE888D2D074, vehicle); }
	static int get_vehicle_plate_type(Vehicle vehicle) { return _i<int>(0x9CCC9525BF2408E0, vehicle); }
	static Any get_vehicle_recording_id(int p0, const char* p1) { return _i<Any>(0x21543C612379DB3C, p0, p1); }
	static Void _0xDF7E3EEB29642C38(Vehicle vehicle, math::vector3<float>* out1, math::vector3<float>* out2) { return _i<Void>(0xDF7E3EEB29642C38, vehicle, out1, out2); }
	static bool get_vehicle_trailer_vehicle(Vehicle vehicle, Vehicle* trailer) { return _i<bool>(0x1CDD6BADC297830D, vehicle, trailer); }
	static bool get_vehicle_tyres_can_burst(Vehicle vehicle) { return _i<bool>(0x678B9BB8C3F58FEB, vehicle); }
	static bool get_vehicle_tyres_are_low_grip(Vehicle vehicle) { return _i<bool>(0x2F5A72430E78C8D3, vehicle); }
	static Void get_vehicle_tyre_smoke_color(Vehicle vehicle, int* r, int* g, int* b) { return _i<Void>(0xB635392A4938B3C3, vehicle, r, g, b); }
	static Any _0x8181CE2F25CB9BB7(Any p0, Any p1) { return _i<Any>(0x8181CE2F25CB9BB7, p0, p1); }
	static int get_vehicle_wheel_type(Vehicle vehicle) { return _i<int>(0xB3ED1BFB4BE636DC, vehicle); }
	static int get_vehicle_window_tint(Vehicle vehicle) { return _i<int>(0x0EE21293DAD47C95, vehicle); }
	static bool _0x91D6DD290888CBAB() { return _i<bool>(0x91D6DD290888CBAB); }
	static bool has_preload_mods_finished(Any p0) { return _i<bool>(0x06F43E5175EB6D96, p0); }
	static bool has_vehicle_asset_loaded(int vehicleAsset) { return _i<bool>(0x1BBE0523B8DB9A21, vehicleAsset); }
	static Any _0x5BA68A0840D546AC(Any p0, Any p1) { return _i<Any>(0x5BA68A0840D546AC, p0, p1); }
	static Any _0x6ADAABD3068C5235() { return _i<Any>(0x6ADAABD3068C5235); }
	static bool has_vehicle_recording_been_loaded(Any p0, Any* p1) { return _i<bool>(0x300D614A4C785FC4, p0, p1); }
	static bool is_vehicle_mod_load_done(Vehicle vehicle) { return _i<bool>(0x9A83F5F9963775EF, vehicle); }
	static Void _0x48ADC8A773564670() { return _i<Void>(0x48ADC8A773564670); }
	static bool _0x62CA17B74C435651(Vehicle vehicle) { return _i<bool>(0x62CA17B74C435651, vehicle); }
	static bool any_passengers_rappeling(Vehicle vehicle) { return _i<bool>(0x291E373D483E7EE7, vehicle); }
	static bool is_any_vehicle_near_point(float x, float y, float z, float radius) { return _i<bool>(0x61E1DD6125A3EEE6, x, y, z, radius); }
	static bool is_big_vehicle(Vehicle vehicle) { return _i<bool>(0x9F243D3919F442FE, vehicle); }
	static Any _0xB0AD1238A709B1A2(Any p0) { return _i<Any>(0xB0AD1238A709B1A2, p0); }
	static bool is_cop_vehicle_in_area3_d(float x1, float x2, float y1, float y2, float z1, float z2) { return _i<bool>(0x7EEF65D5F153E26A, x1, x2, y1, y2, z1, z2); }
	static bool is_vehicle_near_entity(Vehicle vehicle, Entity entity) { return _i<bool>(0x57715966069157AD, vehicle, entity); }
	static bool _0x639431E895B9AA57(Ped ped, Vehicle vehicle, bool p2, bool p3, bool p4) { return _i<bool>(0x639431E895B9AA57, ped, vehicle, p2, p3, p4); }
	static bool _0x89D630CF5EA96D23(Vehicle vehicle, Entity entity) { return _i<bool>(0x89D630CF5EA96D23, vehicle, entity); }
	static bool _0x634148744F385576(Vehicle vehicle) { return _i<bool>(0x634148744F385576, vehicle); }
	static bool is_heli_part_broken(Vehicle vehicle, bool p1, bool p2, bool p3) { return _i<bool>(0xBC74B4BE25EB6C8A, vehicle, p1, p2, p3); }
	static Any _0xB09D25E77C33EB3F(Any p0, Any p1, Any p2) { return _i<Any>(0xB09D25E77C33EB3F, p0, p1, p2); }
	static bool vehicle_has_landing_gear(Vehicle vehicle) { return _i<bool>(0x4198AB0022B15F87, vehicle); }
	static bool is_playback_going_on_for_vehicle(Any p0) { return _i<bool>(0x1C8A4C2C19E68EEC, p0); }
	static bool is_playback_using_ai_going_on_for_vehicle(Any p0) { return _i<bool>(0xAEA8FD591FAD4106, p0); }
	static bool is_vehicle_rocket_boost_active(Vehicle vehicle) { return _i<bool>(0x3D34E80EED4AE3BE, vehicle); }
	static bool _0xF7F203E31F96F6A1(Vehicle vehicle, bool flag) { return _i<bool>(0xF7F203E31F96F6A1, vehicle, flag); }
	static bool is_taxi_light_on(Vehicle vehicle) { return _i<bool>(0x7504C0F113AB50FC, vehicle); }
	static Any is_this_model_an_amphibious_car(uint32_t model) { return _i<Any>(0x633F6F44A537EBB6, model); }
	static Any _0xA1A9FC1C76A6730D(Any p0) { return _i<Any>(0xA1A9FC1C76A6730D, p0); }
	static bool is_this_model_a_bicycle(uint32_t model) { return _i<bool>(0xBF94DD42F63BDED2, model); }
	static bool is_this_model_a_bike(uint32_t model) { return _i<bool>(0xB50C0B0CEDC6CE84, model); }
	static bool is_this_model_a_boat(uint32_t model) { return _i<bool>(0x45A9187928F4B9E3, model); }
	static bool is_this_model_a_car(uint32_t model) { return _i<bool>(0x7F6DB52EEFC96DF8, model); }
	static bool is_this_model_a_heli(uint32_t model) { return _i<bool>(0xDCE4334788AF94EA, model); }
	static bool is_this_model_an_emergency_boat(uint32_t model) { return _i<bool>(0x9537097412CF75FE, model); }
	static bool is_this_model_a_plane(uint32_t model) { return _i<bool>(0xA0948AB42D7BA0DE, model); }
	static bool is_this_model_a_quadbike(uint32_t model) { return _i<bool>(0x39DAC362EE65FA28, model); }
	static bool is_this_model_a_train(uint32_t model) { return _i<bool>(0xAB935175B22E822B, model); }
	static bool is_toggle_mod_on(Vehicle vehicle, int modType) { return _i<bool>(0x84B233A8C8FC8AE7, vehicle, modType); }
	static bool _0xE33FFA906CE74880(Vehicle vehicle, Any p1) { return _i<bool>(0xE33FFA906CE74880, vehicle, p1); }
	static bool is_vehicle_alarm_activated(Vehicle vehicle) { return _i<bool>(0x4319E335B71FFF34, vehicle); }
	static bool is_vehicle_attached_to_cargobob(Vehicle cargobob, Vehicle vehicleAttached) { return _i<bool>(0xD40148F22E81A1D9, cargobob, vehicleAttached); }
	static bool is_vehicle_attached_to_tow_truck(Vehicle towTruck, Vehicle vehicle) { return _i<bool>(0x146DF9EC4C4B9FD4, towTruck, vehicle); }
	static bool is_vehicle_attached_to_trailer(Vehicle vehicle) { return _i<bool>(0xE7CF3C4F9F489F0C, vehicle); }
	static bool is_vehicle_a_convertible(Vehicle vehicle, bool p1) { return _i<bool>(0x52F357A30698BCCE, vehicle, p1); }
	static bool _0x27B926779DEB502D(Vehicle vehicle, bool p1) { return _i<bool>(0x27B926779DEB502D, vehicle, p1); }
	static bool is_vehicle_bumper_broken_off(Vehicle vehicle, bool front) { return _i<bool>(0x468056A6BB6F3846, vehicle, front); }
	static bool is_vehicle_door_damaged(Vehicle veh, int doorID) { return _i<bool>(0xB8E181E559464527, veh, doorID); }
	static bool is_vehicle_door_fully_open(Vehicle vehicle, int doorIndex) { return _i<bool>(0x3E933CFF7B111C22, vehicle, doorIndex); }
	static bool is_vehicle_driveable(Vehicle vehicle, bool isOnFireCheck) { return _i<bool>(0x4C241E39B23DF959, vehicle, isOnFireCheck); }
	static bool is_vehicle_extra_turned_on(Vehicle vehicle, int extraId) { return _i<bool>(0xD2E6822DBFD6C8BD, vehicle, extraId); }
	static bool is_vehicle_high_detail(Vehicle vehicle) { return _i<bool>(0x1F25887F3C104278, vehicle); }
	static bool is_vehicle_in_burnout(Vehicle vehicle) { return _i<bool>(0x1297A88E081430EB, vehicle); }
	static bool is_vehicle_in_garage_area(const char* garageName, Vehicle vehicle) { return _i<bool>(0xCEE4490CD57BB3C2, garageName, vehicle); }
	static bool is_vehicle_model(Vehicle vehicle, uint32_t model) { return _i<bool>(0x423E8DE37D934D89, vehicle, model); }
	static bool is_vehicle_on_all_wheels(Vehicle vehicle) { return _i<bool>(0xB104CD1BABF302E2, vehicle); }
	static Any _0x3DE51E9C80B116CF(Any p0) { return _i<Any>(0x3DE51E9C80B116CF, p0); }
	static Any _0x48C633E94A8142A7(Any p0) { return _i<Any>(0x48C633E94A8142A7, p0); }
	static bool is_vehicle_searchlight_on(Vehicle vehicle) { return _i<bool>(0xC0F97FCE55094987, vehicle); }
	static bool is_vehicle_seat_free(Vehicle vehicle, int seatIndex, Any p2) { return _i<bool>(0x22AC59A870E6A669, vehicle, seatIndex, p2); }
	static bool is_vehicle_siren_sound_on(Vehicle vehicle) { return _i<bool>(0xB5CC40FBCB586380, vehicle); }
	static bool is_vehicle_siren_on(Vehicle vehicle) { return _i<bool>(0x4C9BF537BE2634B2, vehicle); }
	static bool is_vehicle_shop_respray_allowed(Vehicle vehicle) { return _i<bool>(0x8D474C8FAEFF6CDE, vehicle); }
	static bool is_vehicle_stolen(Vehicle vehicle) { return _i<bool>(0x4AF9BD80EEBEB453, vehicle); }
	static bool is_vehicle_stopped(Vehicle vehicle) { return _i<bool>(0x5721B434AD84D57A, vehicle); }
	static bool is_vehicle_stopped_at_traffic_lights(Vehicle vehicle) { return _i<bool>(0x2959F696AE390A99, vehicle); }
	static bool is_vehicle_stuck_on_roof(Vehicle vehicle) { return _i<bool>(0xB497F06B288DCFDF, vehicle); }
	static bool is_vehicle_stuck_timer_up(Vehicle vehicle, int p1, int p2) { return _i<bool>(0x679BE1DAF71DA874, vehicle, p1, p2); }
	static bool is_vehicle_tyre_burst(Vehicle vehicle, int wheelID, bool completely) { return _i<bool>(0xBA291848A0815CA9, vehicle, wheelID, completely); }
	static bool is_vehicle_visible(Vehicle vehicle) { return _i<bool>(0xAA0A52D24FB98293, vehicle); }
	static Any _0x563B65A643ED072E(Any p0, Any p1, Any p2) { return _i<Any>(0x563B65A643ED072E, p0, p1, p2); }
	static bool is_vehicle_window_intact(Vehicle vehicle, int windowIndex) { return _i<bool>(0x46E571A0E20D01F1, vehicle, windowIndex); }
	static Void _0xCFD778E7904C255E(Vehicle vehicle) { return _i<Void>(0xCFD778E7904C255E, vehicle); }
	static Void lower_convertible_roof(Vehicle vehicle, bool instantlyLower) { return _i<Void>(0xDED51F703D0FA83D, vehicle, instantlyLower); }
	static Void set_vehicle_engine_power_multiplier(Vehicle vehicle, float value) { return _i<Void>(0x93A3996368C94158, vehicle, value); }
	static Void _0x51DB102F4A3BA5E0(bool p0) { return _i<Void>(0x51DB102F4A3BA5E0, p0); }
	static Void open_bomb_bay_doors(Vehicle vehicle) { return _i<Void>(0x87E7F24270732CB1, vehicle); }
	static Void _0x5EE5632F47AE9695(Any p0, Any p1) { return _i<Void>(0x5EE5632F47AE9695, p0, p1); }
	static Void pause_playback_recorded_vehicle(Any p0) { return _i<Void>(0x632A689BF42301B1, p0); }
	static Void eject_jb700_roof(Vehicle vehicle, float x, float y, float z) { return _i<Void>(0xE38CB9D7D39FDBCC, vehicle, x, y, z); }
	static Void detach_vehicle_windscreen(Vehicle vehicle) { return _i<Void>(0x6D645D59FB5F5AD3, vehicle); }
	static Void preload_vehicle_mod(Any p0, Any p1, Any p2) { return _i<Void>(0x758F49C24925568A, p0, p1, p2); }
	static Void raise_convertible_roof(Vehicle vehicle, bool instantlyRaise) { return _i<Void>(0x8F5FB35D7E88FC70, vehicle, instantlyRaise); }
	static Void release_preload_mods(Vehicle vehicle) { return _i<Void>(0x445D79F995508307, vehicle); }
	static Void remove_pick_up_rope_for_cargobob(Vehicle cargobob) { return _i<Void>(0x9768CF648F54C804, cargobob); }
	static bool _0x1033371FC8E842A7(Any p0) { return _i<bool>(0x1033371FC8E842A7, p0); }
	static Void remove_vehicles_from_generators_in_area(float x1, float y1, float z1, float x2, float y2, float z2, Any unk) { return _i<Void>(0x46A1E1A299EC4BBA, x1, y1, z1, x2, y2, z2, unk); }
	static Void remove_vehicle_asset(int vehicleAsset) { return _i<Void>(0xACE699C71AB9DEB5, vehicleAsset); }
	static Void _0xE30524E1871F481D(Any p0) { return _i<Void>(0xE30524E1871F481D, p0); }
	static Void remove_vehicle_high_detail_model(Vehicle vehicle) { return _i<Void>(0x00689CDE5F7C6787, vehicle); }
	static Void remove_vehicle_mod(Vehicle vehicle, int modType) { return _i<Void>(0x92D619E420858204, vehicle, modType); }
	static Void remove_vehicle_recording(Any p0, Any* p1) { return _i<Void>(0xF1160ACCF98A3FC8, p0, p1); }
	static Void remove_vehicle_stuck_check(Vehicle vehicle) { return _i<Void>(0x8386BFB614D06749, vehicle); }
	static Void remove_vehicle_upsidedown_check(Vehicle vehicle) { return _i<Void>(0xC53EB42A499A7E90, vehicle); }
	static Void remove_vehicle_window(Vehicle vehicle, int windowIndex) { return _i<Void>(0xA711568EEDB43069, vehicle, windowIndex); }
	static Void request_vehicle_asset(uint32_t vehicleHash, int vehicleAsset) { return _i<Void>(0x81A15811460FAB3A, vehicleHash, vehicleAsset); }
	static Void _0xDBA3C090E3D74690(Vehicle vehicle) { return _i<Void>(0xDBA3C090E3D74690, vehicle); }
	static Void request_vehicle_high_detail_model(Vehicle vehicle) { return _i<Void>(0xA6E9FDCB2C76785E, vehicle); }
	static Void request_vehicle_recording(Any p0, Any* p1) { return _i<Void>(0xAF514CABE74CBF15, p0, p1); }
	static Void _0xE2F53F172B45EDE1() { return _i<Void>(0xE2F53F172B45EDE1); }
	static Void reset_vehicle_stuck_timer(Vehicle vehicle, int nullAttributes) { return _i<Void>(0xD7591B0065AFAA7A, vehicle, nullAttributes); }
	static Void reset_vehicle_wheels(Vehicle vehicle, bool toggle) { return _i<Void>(0x21D2E5662C1F6FED, vehicle, toggle); }
	static Void roll_down_window(Vehicle vehicle, int windowIndex) { return _i<Void>(0x7AD9E6CE657D69E3, vehicle, windowIndex); }
	static Void roll_down_windows(Vehicle vehicle) { return _i<Void>(0x85796B0549DDE156, vehicle); }
	static Void roll_up_window(Vehicle vehicle, int windowIndex) { return _i<Void>(0x602E548F46E24D59, vehicle, windowIndex); }
	static Void _0x5845066D8A1EA7F7(Vehicle vehicle, float x, float y, float z, Any p4) { return _i<Void>(0x5845066D8A1EA7F7, vehicle, x, y, z, p4); }
	static Void _0xE5810AC70602F2F5(Vehicle vehicle, float p1) { return _i<Void>(0xE5810AC70602F2F5, vehicle, p1); }
	static Void _0x80E3357FDEF45C21(Any p0, Any p1) { return _i<Void>(0x80E3357FDEF45C21, p0, p1); }
	static Void _0x3441CAD2F2231923(Vehicle vehicle, bool p1) { return _i<Void>(0x3441CAD2F2231923, vehicle, p1); }
	static Void set_all_low_priority_vehicle_generators_active(bool active) { return _i<Void>(0x608207E7A8FB787C, active); }
	static Void set_all_vehicle_generators_active() { return _i<Void>(0x34AD89078831A4BC); }
	static Void set_all_vehicle_generators_active_in_area(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7) { return _i<Void>(0xC12321827687FE4D, x1, y1, z1, x2, y2, z2, p6, p7); }
	static Void _0x35E0654F4BAD7971(bool p0) { return _i<Void>(0x35E0654F4BAD7971, p0); }
	static Void set_some_vehicle_density_multiplier_this_frame(float value) { return _i<Void>(0x90B6DA738A9A25DA, value); }
	static Void _0x73561D4425A021A2(Any p0, Any p1) { return _i<Void>(0x73561D4425A021A2, p0, p1); }
	static Void set_bike_lean_angle(Vehicle vehicle, float x, float y) { return _i<Void>(0x9CFA4896C3A53CBB, vehicle, x, y); }
	static Void set_boat_anchor(Vehicle vehicle, bool toggle) { return _i<Void>(0x75DBEC174AEEAD10, vehicle, toggle); }
	static Void _0x0A6A279F3AA4FD70(Vehicle vehicle, bool p1) { return _i<Void>(0x0A6A279F3AA4FD70, vehicle, p1); }
	static Void _0xED5EDE9E676643C9(Any p0, Any p1) { return _i<Void>(0xED5EDE9E676643C9, p0, p1); }
	static Void _0xE842A9398079BD82(Vehicle vehicle, float p1) { return _i<Void>(0xE842A9398079BD82, vehicle, p1); }
	static Void _0xE3EBAAE484798530(Vehicle vehicle, bool p1) { return _i<Void>(0xE3EBAAE484798530, vehicle, p1); }
	static Void _0x8F719973E1445BA2(Vehicle vehicle, bool p1) { return _i<Void>(0x8F719973E1445BA2, vehicle, p1); }
	static Void _0xBD32E46AA95C1DD2(Any p0) { return _i<Void>(0xBD32E46AA95C1DD2, p0); }
	static Void _0xA7DCDF4DED40A8F4(Vehicle vehicle, bool p1) { return _i<Void>(0xA7DCDF4DED40A8F4, vehicle, p1); }
	static Void set_can_respray_vehicle(Vehicle vehicle, bool state) { return _i<Void>(0x52BBA29D5EC69356, vehicle, state); }
	static Void _0x1201E8A3290A3B98(Any p0, Any p1) { return _i<Void>(0x1201E8A3290A3B98, p0, p1); }
	static Void _0x1F34B0626C594380(Any p0, Any p1) { return _i<Void>(0x1F34B0626C594380, p0, p1); }
	static Void _0x72BECCF4B829522E(Any p0, Any p1) { return _i<Void>(0x72BECCF4B829522E, p0, p1); }
	static Void _0x571FEB383F629926(Vehicle cargobob, bool p1) { return _i<Void>(0x571FEB383F629926, cargobob, p1); }
	static Void set_cargobob_pickup_magnet_active(Vehicle cargobob, bool isActive) { return _i<Void>(0x9A665550F8DA349B, cargobob, isActive); }
	static Void _0x56EB5E94318D3FB6(Vehicle vehicle, bool p1) { return _i<Void>(0x56EB5E94318D3FB6, vehicle, p1); }
	static Void _0xA17BAD153B51547E(Vehicle cargobob, float p1) { return _i<Void>(0xA17BAD153B51547E, cargobob, p1); }
	static Void _0x685D5561680D088B(Vehicle vehicle, float p1) { return _i<Void>(0x685D5561680D088B, vehicle, p1); }
	static Void _0xED8286F71A819BAA(Vehicle cargobob, float p1) { return _i<Void>(0xED8286F71A819BAA, cargobob, p1); }
	static Void _0x6D8EAC07506291FB(Vehicle cargobob, float p1) { return _i<Void>(0x6D8EAC07506291FB, cargobob, p1); }
	static Void _0x66979ACF5102FD2F(Vehicle cargobob, float p1) { return _i<Void>(0x66979ACF5102FD2F, cargobob, p1); }
	static Void _0x9BDDC73CC6A115D4(Vehicle vehicle, bool p1, bool p2) { return _i<Void>(0x9BDDC73CC6A115D4, vehicle, p1, p2); }
	static Void _0xE301BD63E9E13CF0(Vehicle vehicle, Vehicle cargobob) { return _i<Void>(0xE301BD63E9E13CF0, vehicle, cargobob); }
	static Void set_cargobob_pickup_magnet_strength(Vehicle cargobob, float strength) { return _i<Void>(0xBCBFCD9D1DAC19E2, cargobob, strength); }
	static Void _0xCF1182F682F65307(Any p0, float p1) { return _i<Void>(0xCF1182F682F65307, p0, p1); }
	static Void _0x0D5F65A8F4EBDAB5(Any p0, Any p1) { return _i<Void>(0x0D5F65A8F4EBDAB5, p0, p1); }
	static Void _0xB9562064627FF9DB(Any p0, Any p1) { return _i<Void>(0xB9562064627FF9DB, p0, p1); }
	static Void _0xFC40CBF7B90CA77C(Any p0) { return _i<Void>(0xFC40CBF7B90CA77C, p0); }
	static Void set_car_high_speed_bump_severity_multiplier(float multiplier) { return _i<Void>(0x84FD40F56075E816, multiplier); }
	static Void _0xB2E0C0D6922D31F2(Any p0, Any p1) { return _i<Void>(0xB2E0C0D6922D31F2, p0, p1); }
	static Void set_convertible_roof(Vehicle vehicle, bool p1) { return _i<Void>(0xF39C4F538B5124C2, vehicle, p1); }
	static Void _0x1A78AD3D8240536F(Vehicle vehicle, bool p1) { return _i<Void>(0x1A78AD3D8240536F, vehicle, p1); }
	static Void _0x97841634EF7DF1D6(Any p0, Any p1) { return _i<Void>(0x97841634EF7DF1D6, p0, p1); }
	static Void _0x26D99D5A82FD18E8(Any p0) { return _i<Void>(0x26D99D5A82FD18E8, p0); }
	static Any _0xD4196117AF7BB974(Any p0, Any p1) { return _i<Any>(0xD4196117AF7BB974, p0, p1); }
	static Void _0xEDBC8405B3895CC9(Any p0, Any p1) { return _i<Void>(0xEDBC8405B3895CC9, p0, p1); }
	static Any _0x75627043C6AA90AD() { return _i<Any>(0x75627043C6AA90AD); }
	static Void _0x8235F1BEAD557629(Any p0, Any p1) { return _i<Void>(0x8235F1BEAD557629, p0, p1); }
	static Void _0x25367DE49D64CF16(Vehicle vehicle, bool p1) { return _i<Void>(0x25367DE49D64CF16, vehicle, p1); }
	static Void _0xD4B8E3D1917BC86B(bool toggle) { return _i<Void>(0xD4B8E3D1917BC86B, toggle); }
	static Void _0xB088E9A47AE6EDD5(Vehicle vehicle, bool p1) { return _i<Void>(0xB088E9A47AE6EDD5, vehicle, p1); }
	static Void _0x91A0BD635321F145(Vehicle vehicle, bool p1) { return _i<Void>(0x91A0BD635321F145, vehicle, p1); }
	static Void set_disable_vehicle_petrol_tank_damage(Vehicle vehicle, bool toggle) { return _i<Void>(0x37C8252A7C92D017, vehicle, toggle); }
	static Void set_disable_vehicle_petrol_tank_fires(Vehicle vehicle, bool toggle) { return _i<Void>(0x465BF26AB9684352, vehicle, toggle); }
	static Void display_distant_vehicles(bool toggle) { return _i<Void>(0xF796359A959DF65D, toggle); }
	static Void _0xDBC631F109350B8C(Vehicle vehicle, bool p1) { return _i<Void>(0xDBC631F109350B8C, vehicle, p1); }
	static Void _0x1087BC8EC540DAEB(Any p0, Any p1) { return _i<Void>(0x1087BC8EC540DAEB, p0, p1); }
	static Void set_vehicle_door_can_break(Vehicle vehicle, int doorIndex, bool isBreakable) { return _i<Void>(0x2FA133A4A9D37ED8, vehicle, doorIndex, isBreakable); }
	static Void _0xE6C0C80B8C867537(bool p0) { return _i<Void>(0xE6C0C80B8C867537, p0); }
	static Void set_far_draw_vehicles(bool toggle) { return _i<Void>(0x26324F33423F3CC3, toggle); }
	static Void _0xA247F9EF01D8082E(Any p0) { return _i<Void>(0xA247F9EF01D8082E, p0); }
	static Void set_force_hd_vehicle(Vehicle vehicle, bool toggle) { return _i<Void>(0x97CE68CB032583F0, vehicle, toggle); }
	static Void _0xB28B1FE5BFADD7F5(Vehicle vehicle, bool p1) { return _i<Void>(0xB28B1FE5BFADD7F5, vehicle, p1); }
	static Void _0x4D9D109F63FEE1D4(Any p0, bool p1) { return _i<Void>(0x4D9D109F63FEE1D4, p0, p1); }
	static Void _0x37EBBF3117BD6A25(Vehicle vehicle, float height) { return _i<Void>(0x37EBBF3117BD6A25, vehicle, height); }
	static Void _0x428AD3E26C8D9EB0(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0x428AD3E26C8D9EB0, p0, p1, p2, p3, p4); }
	static Void set_garbage_trucks(bool toggle) { return _i<Void>(0x2AFD795EEAC8D30D, toggle); }
	static Void _0x544996C0081ABDEB(Any p0, Any p1) { return _i<Void>(0x544996C0081ABDEB, p0, p1); }
	static Void _0xFAF2A78061FD9EF4(Any p0, float p1, float p2, float p3) { return _i<Void>(0xFAF2A78061FD9EF4, p0, p1, p2, p3); }
	static Void _0xAB31EF4DE6800CE9(Any p0, Any p1) { return _i<Void>(0xAB31EF4DE6800CE9, p0, p1); }
	static Void _0x430A7631A84C9BE7(Any p0) { return _i<Void>(0x430A7631A84C9BE7, p0); }
	static Void set_heli_blades_full_speed(Vehicle vehicle) { return _i<Void>(0xA178472EBB8AE60D, vehicle); }
	static Void set_heli_blades_speed(Vehicle vehicle, float speed) { return _i<Void>(0xFD280B4D7F3ABC4D, vehicle, speed); }
	static Void _0x94A68DA412C4007D(Any p0, Any p1) { return _i<Void>(0x94A68DA412C4007D, p0, p1); }
	static Void _0x0A3F820A9A9A9AC5(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x0A3F820A9A9A9AC5, p0, p1, p2, p3); }
	static Void set_helicopter_roll_pitch_yaw_mult(Vehicle helicopter, float multiplier) { return _i<Void>(0x6E0859B530A365CC, helicopter, multiplier); }
	static Void _0x4056EA1105F5ABD7(Any p0, Any p1) { return _i<Void>(0x4056EA1105F5ABD7, p0, p1); }
	static bool _0x3EC8BF18AA453FE9(Vehicle vehicle, Any p1) { return _i<bool>(0x3EC8BF18AA453FE9, vehicle, p1); }
	static Void _0xFE205F38AAA58E5B(Any p0, Any p1) { return _i<Void>(0xFE205F38AAA58E5B, p0, p1); }
	static Void _0xE6F13851780394DA(Vehicle vehicle, float p1) { return _i<Void>(0xE6F13851780394DA, vehicle, p1); }
	static Void _0x28B18377EB6E25F6(Any p0, Any p1) { return _i<Void>(0x28B18377EB6E25F6, p0, p1); }
	static Void _0x84EA99C62CB3EF0C(Any p0, Any p1, Any p2) { return _i<Void>(0x84EA99C62CB3EF0C, p0, p1, p2); }
	static Void _0x8EA86DF356801C7D(Any p0, Any p1) { return _i<Void>(0x8EA86DF356801C7D, p0, p1); }
	static Void _0xC24075310A8B9CD1(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Void>(0xC24075310A8B9CD1, p0, p1, p2, p3, p4); }
	static Void _0x5B91B229243351A8(Any p0, Any p1) { return _i<Void>(0x5B91B229243351A8, p0, p1); }
	static Void set_last_driven_vehicle(Vehicle vehicle) { return _i<Void>(0xACFB2463CC22BED2, vehicle); }
	static Void _0xBC3CCA5844452B06(float p0) { return _i<Void>(0xBC3CCA5844452B06, p0); }
	static Void set_mission_train_as_no_longer_needed(Vehicle* train, bool p1) { return _i<Void>(0xBBE7648349B49BE8, train, p1); }
	static Void set_mission_train_coords(Vehicle train, float x, float y, float z) { return _i<Void>(0x591CA673AA6AB736, train, x, y, z); }
	static Void set_number_of_parked_vehicles(int value) { return _i<Void>(0xCAA15F13EBD417FF, value); }
	static Void _0x1B212B26DD3C04DF(Any p0, Any p1) { return _i<Void>(0x1B212B26DD3C04DF, p0, p1); }
	static Void _0x66E3AAFACE2D1EB8(Any p0, Any p1, Any p2) { return _i<Void>(0x66E3AAFACE2D1EB8, p0, p1, p2); }
	static Void set_parked_vehicle_density_multiplier_this_frame(float multiplier) { return _i<Void>(0xEAE6DCC7EEE3DB1D, multiplier); }
	static Void set_cargobob_hook_position(Any p0, float p1, float p2, int state) { return _i<Void>(0x877C1EAEAC531023, p0, p1, p2, state); }
	static Void _0xC0ED6438E6D39BA8(Any p0, Any p1, Any p2) { return _i<Void>(0xC0ED6438E6D39BA8, p0, p1, p2); }
	static Void _0x2A86A0475B6A1434(Any p0, Any p1) { return _i<Void>(0x2A86A0475B6A1434, p0, p1); }
	static Any _0x4C815EB175086F84(Any p0, Any p1) { return _i<Any>(0x4C815EB175086F84, p0, p1); }
	static Void _0xE16142B94664DEFD(Vehicle vehicle, bool p1) { return _i<Void>(0xE16142B94664DEFD, vehicle, p1); }
	static Void _0xAD2D28A1AFDFF131(Vehicle vehicle, float value) { return _i<Void>(0xAD2D28A1AFDFF131, vehicle, value); }
	static Void set_playback_speed(Vehicle vehicle, float speed) { return _i<Void>(0x6683AB880E427778, vehicle, speed); }
	static Void set_playback_to_use_ai(Vehicle vehicle, int flag) { return _i<Void>(0xA549C3B37EA28131, vehicle, flag); }
	static Void set_playback_to_use_ai_try_to_revert_back_later(Any p0, Any p1, Any p2, bool p3) { return _i<Void>(0x6E63860BBB190730, p0, p1, p2, p3); }
	static Void set_players_last_vehicle(Vehicle vehicle) { return _i<Void>(0xBCDF8BAF56C87B6A, vehicle); }
	static Void _0x4E74E62E0A97E901(Vehicle vehicle, bool p1) { return _i<Void>(0x4E74E62E0A97E901, vehicle, p1); }
	static Void _0x796A877E459B99EA(Any p0, float p1, float p2, float p3) { return _i<Void>(0x796A877E459B99EA, p0, p1, p2, p3); }
	static Void set_random_boats(bool toggle) { return _i<Void>(0x84436EC293B1415F, toggle); }
	static Void set_random_trains(bool toggle) { return _i<Void>(0x80D9F74197EA47D9, toggle); }
	static Void set_random_vehicle_density_multiplier_this_frame(float multiplier) { return _i<Void>(0xB3B3359379FE77D3, multiplier); }
	static Void set_render_train_as_derailed(Vehicle train, bool toggle) { return _i<Void>(0x317B11A312DF5534, train, toggle); }
	static Void set_vehicle_rocket_boost_active(Vehicle vehicle, bool active) { return _i<Void>(0x81E1552E35DC3839, vehicle, active); }
	static Void set_vehicle_rocket_boost_percentage(Vehicle vehicle, float percentage) { return _i<Void>(0xFEB2DDED3509562E, vehicle, percentage); }
	static Void _0xEFC13B1CE30D755D(Any p0, Any p1) { return _i<Void>(0xEFC13B1CE30D755D, p0, p1); }
	static Void set_vehicle_rocket_boost_refill_time(Vehicle vehicle, float time) { return _i<Void>(0xE00F2AB100B76E89, vehicle, time); }
	static Void set_script_vehicle_generator(Any vehicleGenerator, bool enabled) { return _i<Void>(0xD9D620E0AC6DC4B0, vehicleGenerator, enabled); }
	static Void _0x063AE2B2CC273588(Any p0, bool p1) { return _i<Void>(0x063AE2B2CC273588, p0, p1); }
	static Void _0x78CEEE41F49F421F(Any p0, Any p1) { return _i<Void>(0x78CEEE41F49F421F, p0, p1); }
	static Void _0x65B080555EA48149(Any p0) { return _i<Void>(0x65B080555EA48149, p0); }
	static Void _0x7BBE7FF626A591FE(Any p0) { return _i<Void>(0x7BBE7FF626A591FE, p0); }
	static Void jitter_vehicle(Vehicle vehicle, bool p1, float yaw, float pitch, float roll) { return _i<Void>(0xC59872A5134879C7, vehicle, p1, yaw, pitch, roll); }
	static Void set_plane_min_height_above_ground(Vehicle plane, int height) { return _i<Void>(0xB893215D8D4C015B, plane, height); }
	static Void set_taxi_lights(Vehicle vehicle, bool state) { return _i<Void>(0x598803E85E8448D9, vehicle, state); }
	static Void _0x2FA2494B47FDD009(Any p0, Any p1) { return _i<Void>(0x2FA2494B47FDD009, p0, p1); }
	static Void _0x2A8F319B392E7B3F(Vehicle vehicle, float p1) { return _i<Void>(0x2A8F319B392E7B3F, vehicle, p1); }
	static Any _0x878C75C09FBDB942() { return _i<Any>(0x878C75C09FBDB942); }
	static Void _0x95CF53B3D687F9FA(Vehicle vehicle) { return _i<Void>(0x95CF53B3D687F9FA, vehicle); }
	static Void set_train_cruise_speed(Vehicle train, float speed) { return _i<Void>(0x16469284DB8C62B5, train, speed); }
	static Void set_train_speed(Vehicle train, float speed) { return _i<Void>(0xAA0BC91BE0B796E3, train, speed); }
	static Void _0x21973BBF8D17EDFA(Any p0, Any p1) { return _i<Void>(0x21973BBF8D17EDFA, p0, p1); }
	static Void _0xF06A16CA55D138D8(Any p0, Any p1) { return _i<Void>(0xF06A16CA55D138D8, p0, p1); }
	static Void _0xDFFCEF48E511DB48(Any p0, bool p1) { return _i<Void>(0xDFFCEF48E511DB48, p0, p1); }
	static Void _0x21115BCD6E44656A(Any p0, bool p1) { return _i<Void>(0x21115BCD6E44656A, p0, p1); }
	static Void _0x9BECD4B9FEF3F8A6(Vehicle vehicle, bool p1) { return _i<Void>(0x9BECD4B9FEF3F8A6, vehicle, p1); }
	static Void _0x1F9FB66F3A3842D2(Vehicle vehicle, bool p1) { return _i<Void>(0x1F9FB66F3A3842D2, vehicle, p1); }
	static Void set_vehicle_exclusive_driver(Vehicle vehicle, bool p1) { return _i<Void>(0x41062318F23ED854, vehicle, p1); }
	static Void set_vehicle_alarm(Vehicle vehicle, bool state) { return _i<Void>(0xCDE5E70C1DDB954C, vehicle, state); }
	static Void _0x7D6F9A3EF26136A0(Vehicle vehicle, bool p1, bool p2) { return _i<Void>(0x7D6F9A3EF26136A0, vehicle, p1, p2); }
	static Void _0x1DDA078D12879EEE(Any p0, Any p1, Any p2) { return _i<Void>(0x1DDA078D12879EEE, p0, p1, p2); }
	static Void set_vehicle_allow_no_passengers_lockon(Vehicle veh, bool toggle) { return _i<Void>(0x5D14D4154BFE7B2C, veh, toggle); }
	static Any set_vehicle_automatically_attaches(Vehicle vehicle, Any p1, Any p2) { return _i<Any>(0x8BA6F76BC53A1493, vehicle, p1, p2); }
	static Void _0xD3301660A57C9272(Any p0) { return _i<Void>(0xD3301660A57C9272, p0); }
	static Void _0x9F3F689B814F2599(Vehicle vehicle, bool p1) { return _i<Void>(0x9F3F689B814F2599, vehicle, p1); }
	static Void _0x870B8B7A766615C8(Any p0, Any p1, Any p2) { return _i<Void>(0x870B8B7A766615C8, p0, p1, p2); }
	static Void set_vehicle_body_health(Vehicle vehicle, float value) { return _i<Void>(0xB77D05AC8C78AADB, vehicle, value); }
	static Void set_vehicle_bombs(Vehicle vehicle, int amount) { return _i<Void>(0xF4B2ED59DEB5D774, vehicle, amount); }
	static Void _0xE4E2FD323574965C(Any p0, Any p1) { return _i<Void>(0xE4E2FD323574965C, p0, p1); }
	static Void set_vehicle_brake_lights(Vehicle vehicle, bool toggle) { return _i<Void>(0x92B35082E0B42F66, vehicle, toggle); }
	static Void _0xC361AA040D6637A8(Vehicle vehicle, bool p1) { return _i<Void>(0xC361AA040D6637A8, vehicle, p1); }
	static Void _0xF8EBCCC96ADB9FB7(Any p0, float p1, bool p2) { return _i<Void>(0xF8EBCCC96ADB9FB7, p0, p1, p2); }
	static Void set_vehicle_burnout(Vehicle vehicle, bool toggle) { return _i<Void>(0xFB8794444A7D60FB, vehicle, toggle); }
	static Void set_vehicle_can_be_targetted(Vehicle vehicle, bool state) { return _i<Void>(0x3750146A28097A82, vehicle, state); }
	static Void set_vehicle_can_be_used_by_fleeing_peds(Vehicle vehicle, bool toggle) { return _i<Void>(0x300504B23BD3B711, vehicle, toggle); }
	static Void set_vehicle_can_be_visibly_damaged(Vehicle vehicle, bool state) { return _i<Void>(0x4C7028F78FFD3681, vehicle, state); }
	static Void set_vehicle_can_break(Vehicle vehicle, bool toggle) { return _i<Void>(0x59BF8C3D52C92F66, vehicle, toggle); }
	static Void _0x0CDDA42F9E360CA6(Vehicle vehicle, bool p1) { return _i<Void>(0x0CDDA42F9E360CA6, vehicle, p1); }
	static Void _0x065D03A9D6B2C6B5(Any p0, Any p1) { return _i<Void>(0x065D03A9D6B2C6B5, p0, p1); }
	static Void _0x206BC5DC9D1AC70A(Vehicle vehicle, bool p1) { return _i<Void>(0x206BC5DC9D1AC70A, vehicle, p1); }
	static Void _0x51BB2D88D31A914B(Vehicle vehicle, bool p1) { return _i<Void>(0x51BB2D88D31A914B, vehicle, p1); }
	static Void _0x192547247864DFDD(Vehicle vehicle, bool p1) { return _i<Void>(0x192547247864DFDD, vehicle, p1); }
	static Void _0x428BACCDF5E26EAD(Vehicle vehicle, bool p1) { return _i<Void>(0x428BACCDF5E26EAD, vehicle, p1); }
	static Void set_vehicle_ceiling_height(Vehicle vehicle, float p1) { return _i<Void>(0xA46413066687A328, vehicle, p1); }
	static Void set_vehicle_engine_torque_multiplier(Vehicle vehicle, float value) { return _i<Void>(0xB59E4BD37AE292DB, vehicle, value); }
	static Void set_vehicle_colours(Vehicle vehicle, int colorPrimary, int colorSecondary) { return _i<Void>(0x4F1D4BE3A7F24601, vehicle, colorPrimary, colorSecondary); }
	static Void set_vehicle_colour_combination(Vehicle vehicle, int colorCombination) { return _i<Void>(0x33E8CD3322E2FE31, vehicle, colorCombination); }
	static Void set_vehicle_countermeasures(Vehicle vehicle, int amount) { return _i<Void>(0x9BDA23BF666F0855, vehicle, amount); }
	static Void _0x182F266C2D9E2BEB(Vehicle vehicle, float p1) { return _i<Void>(0x182F266C2D9E2BEB, vehicle, p1); }
	static Void set_vehicle_custom_primary_colour(Vehicle vehicle, int r, int g, int b) { return _i<Void>(0x7141766F91D15BEA, vehicle, r, g, b); }
	static Void set_vehicle_custom_secondary_colour(Vehicle vehicle, int r, int g, int b) { return _i<Void>(0x36CED73BFED89754, vehicle, r, g, b); }
	static Void set_vehicle_damage(Vehicle vehicle, float xOffset, float yOffset, float zOffset, float damage, float radius, bool p6) { return _i<Void>(0xA1DD317EA8FD4F29, vehicle, xOffset, yOffset, zOffset, damage, radius, p6); }
	static Any _0x4E20D2A627011E8E(Any p0, Any p1) { return _i<Any>(0x4E20D2A627011E8E, p0, p1); }
	static Void set_vehicle_deformation_fixed(Vehicle vehicle) { return _i<Void>(0x953DA1E1B12C0491, vehicle); }
	static Void set_vehicle_density_multiplier_this_frame(float multiplier) { return _i<Void>(0x245A6883D966D537, multiplier); }
	static Void set_vehicle_dirt_level(Vehicle vehicle, float dirtLevel) { return _i<Void>(0x79D3B596FE44EE8B, vehicle, dirtLevel); }
	static Void _0xAF60E6A2936F982A(Any p0, Any p1) { return _i<Void>(0xAF60E6A2936F982A, p0, p1); }
	static Void _0x8AA9180DE2FEDD45(Vehicle vehicle, bool p1) { return _i<Void>(0x8AA9180DE2FEDD45, vehicle, p1); }
	static Void _0x2B6747FAA9DB9D6B(Vehicle vehicle, bool p1) { return _i<Void>(0x2B6747FAA9DB9D6B, vehicle, p1); }
	static Void _0x76D26A22750E849E(Any p0) { return _i<Void>(0x76D26A22750E849E, p0); }
	static Void set_vehicle_doors_locked(Vehicle vehicle, int doorLockStatus) { return _i<Void>(0xB664292EAECF7FA6, vehicle, doorLockStatus); }
	static Void set_vehicle_doors_locked_for_all_players(Vehicle vehicle, bool toggle) { return _i<Void>(0xA2F80B8D040727CC, vehicle, toggle); }
	static Void _0x9737A37136F07E75(Vehicle vehicle, bool toggle) { return _i<Void>(0x9737A37136F07E75, vehicle, toggle); }
	static Void set_vehicle_doors_locked_for_player(Vehicle vehicle, Player player, bool toggle) { return _i<Void>(0x517AAF684BB50CD1, vehicle, player, toggle); }
	static Void set_vehicle_doors_locked_for_team(Vehicle vehicle, int team, bool toggle) { return _i<Void>(0xB81F6D4A8F5EEBA8, vehicle, team, toggle); }
	static Void set_vehicle_doors_shut(Vehicle vehicle, bool closeInstantly) { return _i<Void>(0x781B3D62BB013EF5, vehicle, closeInstantly); }
	static Void _0x3B458DDB57038F08(Any p0, Any p1, Any p2) { return _i<Void>(0x3B458DDB57038F08, p0, p1, p2); }
	static Void set_vehicle_door_broken(Vehicle vehicle, int doorIndex, bool deleteDoor) { return _i<Void>(0xD4D4F6A4AB575A33, vehicle, doorIndex, deleteDoor); }
	static Void set_vehicle_door_control(Vehicle vehicle, int doorIndex, int speed, float angle) { return _i<Void>(0xF2BFA0430F0A0FCB, vehicle, doorIndex, speed, angle); }
	static Void set_vehicle_door_latched(Vehicle vehicle, int doorIndex, bool p2, bool p3, bool p4) { return _i<Void>(0xA5A9653A8D2CAF48, vehicle, doorIndex, p2, p3, p4); }
	static Void set_vehicle_door_open(Vehicle vehicle, int doorIndex, bool loose, bool openInstantly) { return _i<Void>(0x7C65DAC73C35C862, vehicle, doorIndex, loose, openInstantly); }
	static Void set_vehicle_door_shut(Vehicle vehicle, int doorIndex, bool closeInstantly) { return _i<Void>(0x93D9BD300D7789E5, vehicle, doorIndex, closeInstantly); }
	static Void set_vehicle_creates_money_pickups_when_exploded(Vehicle vehicle, bool toggle) { return _i<Void>(0x068F64F2470F9656, vehicle, toggle); }
	static Void set_vehicle_engine_can_degrade(Vehicle vehicle, bool toggle) { return _i<Void>(0x983765856F2564F9, vehicle, toggle); }
	static Void set_vehicle_engine_health(Vehicle vehicle, float health) { return _i<Void>(0x45F6D8EEF34ABEF1, vehicle, health); }
	static Void set_vehicle_engine_on(Vehicle vehicle, bool value, bool instantly, bool otherwise) { return _i<Void>(0x2497C4717C8B881E, vehicle, value, instantly, otherwise); }
	static Void set_vehicle_enveff_scale(Vehicle vehicle, float fade) { return _i<Void>(0x3AFDC536C3D01674, vehicle, fade); }
	static Void set_vehicle_exclusive_driver2(Vehicle vehicle, Ped ped, int p2) { return _i<Void>(0xB5C51B5502E85E83, vehicle, ped, p2); }
	static Void _0xD565F438137F0E10(Any p0, Any p1) { return _i<Void>(0xD565F438137F0E10, p0, p1); }
	static Void set_vehicle_explodes_on_high_explosion_damage(Vehicle vehicle, bool toggle) { return _i<Void>(0x71B0892EC081D60A, vehicle, toggle); }
	static Void _0x79DF7E806202CE01(Any p0, Any p1) { return _i<Void>(0x79DF7E806202CE01, p0, p1); }
	static Void set_vehicle_extra(Vehicle vehicle, int extraId, bool toggle) { return _i<Void>(0x7EE3A3C5E4A40CC9, vehicle, extraId, toggle); }
	static Void set_vehicle_extra_colours(Vehicle vehicle, int pearlescentColor, int wheelColor) { return _i<Void>(0x2036F561ADD12E33, vehicle, pearlescentColor, wheelColor); }
	static Void set_vehicle_interior_colour(Vehicle vehicle, int color) { return _i<Void>(0xF40DD601A65F7F19, vehicle, color); }
	static Void set_vehicle_dashboard_colour(Vehicle vehicle, int color) { return _i<Void>(0x6089CDF6A57F326C, vehicle, color); }
	static Void set_vehicle_fixed(Vehicle vehicle) { return _i<Void>(0x115722B1B9C14C1C, vehicle); }
	static Void _0x30D779DE7C4F6DD3(Any p0, float p1) { return _i<Void>(0x30D779DE7C4F6DD3, p0, p1); }
	static Void _0x9AA47FFF660CB932(Any p0, float p1) { return _i<Void>(0x9AA47FFF660CB932, p0, p1); }
	static Void _0xB055A34527CB8FD7(Vehicle vehicle, bool p1) { return _i<Void>(0xB055A34527CB8FD7, vehicle, p1); }
	static Void set_vehicle_forward_speed(Vehicle vehicle, float speed) { return _i<Void>(0xAB54A438726D25D5, vehicle, speed); }
	static Void _0x6501129C9E0FFA05(Any p0, Any p1) { return _i<Void>(0x6501129C9E0FFA05, p0, p1); }
	static Void set_vehicle_friction_override(Vehicle vehicle, float friction) { return _i<Void>(0x1837AF7C627009BA, vehicle, friction); }
	static Void set_vehicle_fullbeam(Vehicle vehicle, bool toggle) { return _i<Void>(0x8B7FD87F0DDB421E, vehicle, toggle); }
	static Void _0x279D50DE5652D935(Any p0, bool p1) { return _i<Void>(0x279D50DE5652D935, p0, p1); }
	static Void _0x9A75585FB2E54FAD(float p0, float p1, float p2, float p3) { return _i<Void>(0x9A75585FB2E54FAD, p0, p1, p2, p3); }
	static Void set_vehicle_gravity(Vehicle vehicle, bool toggle) { return _i<Void>(0x89F149B6131E57DA, vehicle, toggle); }
	static Void set_vehicle_handbrake(Vehicle vehicle, bool toggle) { return _i<Void>(0x684785568EF26A22, vehicle, toggle); }
	static Void _0x02398B627547189C(Vehicle p0, bool p1) { return _i<Void>(0x02398B627547189C, p0, p1); }
	static Void set_vehicle_has_been_owned_by_player(Vehicle vehicle, bool owned) { return _i<Void>(0x2B5F9D2AF1F1722D, vehicle, owned); }
	static Void set_vehicle_siren_sound(Vehicle vehicle, bool toggle) { return _i<Void>(0xD8050E0EB60CF274, vehicle, toggle); }
	static Void set_vehicle_has_strong_axles(Vehicle vehicle, bool toggle) { return _i<Void>(0x92F0CF722BC4202F, vehicle, toggle); }
	static Void _0x1AA8A837D2169D94(Vehicle vehicle, bool p1) { return _i<Void>(0x1AA8A837D2169D94, vehicle, p1); }
	static Void set_vehicle_lights_mode(Vehicle vehicle, int p1) { return _i<Void>(0x1FD09E7390A74D54, vehicle, p1); }
	static Void _0x10655FAB9915623D(Any p0, Any p1) { return _i<Void>(0x10655FAB9915623D, p0, p1); }
	static Void _0x06582AFF74894C75(Any p0, bool p1) { return _i<Void>(0x06582AFF74894C75, p0, p1); }
	static Void set_vehicle_indicator_lights(Vehicle vehicle, int turnSignal, bool toggle) { return _i<Void>(0xB5D45264751B7DF0, vehicle, turnSignal, toggle); }
	static Void set_ped_targettable_vehicle_destroy(Vehicle vehicle, int vehicleComponent, int destroyType) { return _i<Void>(0xBE70724027F85BCD, vehicle, vehicleComponent, destroyType); }
	static Void _0x0AD9E8F87FF7C16F(Any p0, bool p1) { return _i<Void>(0x0AD9E8F87FF7C16F, p0, p1); }
	static Void set_vehicle_interiorlight(Vehicle vehicle, bool toggle) { return _i<Void>(0xBC2042F090AF6AD3, vehicle, toggle); }
	static Void set_vehicle_silent(Vehicle vehicle, bool toggle) { return _i<Void>(0x9D44FCCE98450843, vehicle, toggle); }
	static Void set_vehicle_is_considered_by_player(Vehicle vehicle, bool toggle) { return _i<Void>(0x31B927BBC44156CD, vehicle, toggle); }
	static Void _0x07116E24E9D1929D(Vehicle vehicle, bool toggle) { return _i<Void>(0x07116E24E9D1929D, vehicle, toggle); }
	static Void set_vehicle_is_stolen(Vehicle vehicle, bool isStolen) { return _i<Void>(0x67B2C79AA7FF5738, vehicle, isStolen); }
	static Void set_vehicle_is_wanted(Vehicle vehicle, bool state) { return _i<Void>(0xF7EC25A3EBEEC726, vehicle, state); }
	static Void set_vehicle_jet_engine_on(Vehicle vehicle, bool toggle) { return _i<Void>(0xB8FBC8B1330CA9B4, vehicle, toggle); }
	static Void set_vehicle_hud_special_ability_bar_active(Vehicle vehicle, bool active) { return _i<Void>(0x99C82F8A139F3E4E, vehicle, active); }
	static Void set_vehicle_lights(Vehicle vehicle, int state) { return _i<Void>(0x34E710FF01247C5A, vehicle, state); }
	static Void set_vehicle_light_multiplier(Vehicle vehicle, float multiplier) { return _i<Void>(0xB385454F8791F57C, vehicle, multiplier); }
	static Void _0xC50CE861B55EAB8B(Vehicle vehicle, bool p1) { return _i<Void>(0xC50CE861B55EAB8B, vehicle, p1); }
	static Void _0xA6D3A8750DC73270(Any p0, Any p1) { return _i<Void>(0xA6D3A8750DC73270, p0, p1); }
	static Void set_vehicle_livery(Vehicle vehicle, int livery) { return _i<Void>(0x60BF608F1B8CD1B6, vehicle, livery); }
	static Void set_vehicle_lod_multiplier(Vehicle vehicle, float multiplier) { return _i<Void>(0x93AE6A61BE015BF1, vehicle, multiplier); }
	static Void _0xBAA045B4E42F3C06(Any p0, Any p1) { return _i<Void>(0xBAA045B4E42F3C06, p0, p1); }
	static Void _0xE851E480B814D4BA(Vehicle vehicle, bool p1) { return _i<Void>(0xE851E480B814D4BA, vehicle, p1); }
	static Void set_vehicle_xenon_lights_colour(Vehicle vehicle, int color) { return _i<Void>(0xE41033B25D003A07, vehicle, color); }
	static int get_vehicle_xenon_lights_colour(Vehicle vehicle) { return _i<Void>(0x3DFF319A831E0CDB, vehicle); }
	static Void set_vehicle_mod(Vehicle vehicle, int modType, int modIndex, bool customTires) { return _i<Void>(0x6AF0636DDEDCB6DD, vehicle, modType, modIndex, customTires); }
	static Void set_vehicle_model_is_suppressed(uint32_t model, bool suppressed) { return _i<Void>(0x0FC2D89AC25A5814, model, suppressed); }
	static Void set_vehicle_mod_color1(Vehicle vehicle, int paintType, int color, int p3) { return _i<Void>(0x43FEB945EE7F85B8, vehicle, paintType, color, p3); }
	static Void set_vehicle_mod_color2(Vehicle vehicle, int paintType, int color) { return _i<Void>(0x816562BADFDEC83E, vehicle, paintType, color); }
	static Void set_vehicle_mod_kit(Vehicle vehicle, int modKit) { return _i<Void>(0x1F2AA07F00B3217A, vehicle, modKit); }
	static Void set_vehicle_needs_to_be_hotwired(Vehicle vehicle, bool toggle) { return _i<Void>(0xFBA550EA44404EE6, vehicle, toggle); }
	static Void set_vehicle_neon_lights_colour(Vehicle vehicle, int r, int g, int b) { return _i<Void>(0x8E0A582209A62695, vehicle, r, g, b); }
	static Void set_vehicle_neon_light_enabled(Vehicle vehicle, int index, bool toggle) { return _i<Void>(0x2AA720E4287BF269, vehicle, index, toggle); }
	static Void _0xAB04325045427AAE(Vehicle vehicle, bool p1) { return _i<Void>(0xAB04325045427AAE, vehicle, p1); }
	static Void _0x5E569EC46EC21CAE(Vehicle vehicle, bool toggle) { return _i<Void>(0x5E569EC46EC21CAE, vehicle, toggle); }
	static Void set_vehicle_number_plate_text(Vehicle vehicle, const char* plateText) { return _i<Void>(0x95A88F0B409CDA47, vehicle, plateText); }
	static Void set_vehicle_number_plate_text_index(Vehicle vehicle, int plateIndex) { return _i<Void>(0x9088EB5A43FFB0A1, vehicle, plateIndex); }
	static Void _0x35BB21DE06784373(Any p0, Any p1) { return _i<Void>(0x35BB21DE06784373, p0, p1); }
	static bool set_vehicle_on_ground_properly(Vehicle vehicle, Any p1) { return _i<bool>(0x49733E92263139D1, vehicle, p1); }
	static Void set_vehicle_out_of_control(Vehicle vehicle, bool killDriver, bool explodeOnImpact) { return _i<Void>(0xF19D095E42D430CC, vehicle, killDriver, explodeOnImpact); }
	static Void set_vehicle_petrol_tank_health(Vehicle vehicle, float health) { return _i<Void>(0x70DB57649FA8D0D8, vehicle, health); }
	static Void set_vehicle_provides_cover(Vehicle vehicle, bool toggle) { return _i<Void>(0x5AFEEDD9BB2899D7, vehicle, toggle); }
	static Void _0xCF9159024555488C(Any p0) { return _i<Void>(0xCF9159024555488C, p0); }
	static Void set_vehicle_reduce_grip(Vehicle vehicle, bool toggle) { return _i<Void>(0x222FF6A823D122E2, vehicle, toggle); }
	static Void _0xC4B3347BD68BD609(Any p0) { return _i<Void>(0xC4B3347BD68BD609, p0); }
	static Void _0x2311DD7159F00582(Vehicle vehicle, bool p1) { return _i<Void>(0x2311DD7159F00582, vehicle, p1); }
	static Void set_vehicle_rudder_broken(Vehicle vehicle, bool p1) { return _i<Void>(0x09606148B6C71DEF, vehicle, p1); }
	static Void set_vehicle_searchlight(Vehicle heli, bool toggle, bool canBeUsedByAI) { return _i<Void>(0x14E85C5EE7A4D542, heli, toggle, canBeUsedByAI); }
	static Void set_vehicle_shoot_at_target(Ped driver, Entity entity, float xTarget, float yTarget, float zTarget) { return _i<Void>(0x74CD9A9327A282EA, driver, entity, xTarget, yTarget, zTarget); }
	static Void set_vehicle_siren(Vehicle vehicle, bool toggle) { return _i<Void>(0xF4924635A19EB37D, vehicle, toggle); }
	static Void _0xF051D9BFB6BA39C0(Any p0) { return _i<Void>(0xF051D9BFB6BA39C0, p0); }
	static Void _0x1CF38D529D7441D9(Vehicle vehicle, bool toggle) { return _i<Void>(0x1CF38D529D7441D9, vehicle, toggle); }
	static Void _0x9007A2F21DC108D4(Any p0, float p1) { return _i<Void>(0x9007A2F21DC108D4, p0, p1); }
	static Void set_vehicle_steer_bias(Vehicle vehicle, float value) { return _i<Void>(0x42A8EC77D5150CBE, vehicle, value); }
	static Any _0xDCE97BDF8A0EABC8() { return _i<Any>(0xDCE97BDF8A0EABC8); }
	static Void _0x6EBFB22D646FFC18(Vehicle vehicle, bool p1) { return _i<Void>(0x6EBFB22D646FFC18, vehicle, p1); }
	static Void set_vehicle_strong(Vehicle vehicle, bool toggle) { return _i<Void>(0x3E8C8727991A8A0B, vehicle, toggle); }
	static Void _0x737E398138550FFF(Any p0, Any p1) { return _i<Void>(0x737E398138550FFF, p0, p1); }
	static Void _0x56B94C6D7127DFBA(Any p0, float p1, bool p2) { return _i<Void>(0x56B94C6D7127DFBA, p0, p1, p2); }
	static Void set_vehicle_timed_explosion(Vehicle vehicle, Ped ped, bool toggle) { return _i<Void>(0x2E0A74E1002380B1, vehicle, ped, toggle); }
	static Void set_tow_truck_crane_height(Vehicle towTruck, float height) { return _i<Void>(0xFE54B92A344583CA, towTruck, height); }
	static Void _0x1093408B4B9D1146(Any p0, float p1) { return _i<Void>(0x1093408B4B9D1146, p0, p1); }
	static Void _0x0581730AB9380412(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return _i<Void>(0x0581730AB9380412, p0, p1, p2, p3, p4, p5); }
	static Void set_vehicle_tyres_can_burst(Vehicle vehicle, bool toggle) { return _i<Void>(0xEB9DC3C7D8596C46, vehicle, toggle); }
	static Void set_vehicle_tyres_low_grip(Vehicle vehicle, bool toggle) { return _i<Void>(0x5AC79C98C5C17F05, vehicle, toggle); }
	static Void set_vehicle_tyre_burst(Vehicle vehicle, int index, bool onRim, float p3) { return _i<Void>(0xEC6A202EE4960385, vehicle, index, onRim, p3); }
	static Void set_vehicle_tyre_fixed(Vehicle vehicle, int tyreIndex) { return _i<Void>(0x6E13FC662B882D1D, vehicle, tyreIndex); }
	static Void set_vehicle_tyre_smoke_color(Vehicle vehicle, int r, int g, int b) { return _i<Void>(0xB5BA80F839791C0F, vehicle, r, g, b); }
	static Void set_vehicle_undriveable(Vehicle vehicle, bool toggle) { return _i<Void>(0x8ABA6AF54B942B95, vehicle, toggle); }
	static Void _0xE05DD0E9707003A3(Any p0, bool p1) { return _i<Void>(0xE05DD0E9707003A3, p0, p1); }
	static Void _0xCAC66558B944DA67(Vehicle vehicle, bool p1) { return _i<Void>(0xCAC66558B944DA67, vehicle, p1); }
	static Void _0xBB2333BB87DDD87F(Any p0, Any p1) { return _i<Void>(0xBB2333BB87DDD87F, p0, p1); }
	static Void _0x1D97D1E3A70A649F(Vehicle vehicle, bool p1) { return _i<Void>(0x1D97D1E3A70A649F, vehicle, p1); }
	static Void _0x41290B40FA63E6DA(Any p0) { return _i<Void>(0x41290B40FA63E6DA, p0); }
	static Any _0xE023E8AC4EF7C117(Vehicle p0, bool p1, bool p2, bool p3) { return _i<Any>(0xE023E8AC4EF7C117, p0, p1, p2, p3); }
	static Void _0x88BC673CA9E0AE99(Vehicle vehicle, bool p1) { return _i<Void>(0x88BC673CA9E0AE99, vehicle, p1); }
	static Void _0xC45C27EF50F36ADC(Vehicle vehicle, bool p1) { return _i<Void>(0xC45C27EF50F36ADC, vehicle, p1); }
	static Void _0x86B4B6212CB8B627(Any p0, Any p1) { return _i<Void>(0x86B4B6212CB8B627, p0, p1); }
	static Any _0x45A561A9421AB6AD(Any p0, Any p1) { return _i<Any>(0x45A561A9421AB6AD, p0, p1); }
	static Void _0x44CD1F493DB2A0A6(Any p0, Any p1, Any p2) { return _i<Void>(0x44CD1F493DB2A0A6, p0, p1, p2); }
	static Void set_vehicle_wheels_can_break(Vehicle vehicle, bool enabled) { return _i<Void>(0x29B18B4FD460CA8F, vehicle, enabled); }
	static Void set_vehicle_wheels_can_break_off_when_blow_up(Vehicle vehicle, bool toggle) { return _i<Void>(0xA37B9A517B133349, vehicle, toggle); }
	static Void set_vehicle_wheel_type(Vehicle vehicle, int WheelType) { return _i<Void>(0x487EB21CC7295BA1, vehicle, WheelType); }
	static Void _0xBE5C1255A1830FF5(Vehicle vehicle, bool toggle) { return _i<Void>(0xBE5C1255A1830FF5, vehicle, toggle); }
	static Void _0x2C4A1590ABF43E8B(Vehicle vehicle, bool p1) { return _i<Void>(0x2C4A1590ABF43E8B, vehicle, p1); }
	static Void set_vehicle_window_tint(Vehicle vehicle, int tint) { return _i<Void>(0x57C51E6BAD752696, vehicle, tint); }
	static Void _0x1312DDD8385AEE4E(Any p0, Any p1) { return _i<Void>(0x1312DDD8385AEE4E, p0, p1); }
	static Void raise_lowerable_wheels(Vehicle vehicle) { return _i<Void>(0xF660602546D27BA8, vehicle); }
	static Void _0x5335BE58C083E74E(Any p0) { return _i<Void>(0x5335BE58C083E74E, p0); }
	static Void skip_time_in_playback_recorded_vehicle(Any p0, float p1) { return _i<Void>(0x9438F7AD68771A20, p0, p1); }
	static Void skip_to_end_and_stop_playback_recorded_vehicle(Any p0) { return _i<Void>(0xAB8E2EDA0C0A5883, p0); }
	static Void smash_vehicle_window(Vehicle vehicle, int index) { return _i<Void>(0x9E5B5E4D2CCD2259, vehicle, index); }
	static Void _0x374706271354CB18(Vehicle vehicle, Entity p1, float p2) { return _i<Void>(0x374706271354CB18, vehicle, p1, p2); }
	static Void start_playback_recorded_vehicle(Vehicle vehicle, int p1, const char* playback, bool p3) { return _i<Void>(0x3F878F92B3A7A071, vehicle, p1, playback, p3); }
	static Void start_playback_recorded_vehicle_using_ai(Any p0, Any p1, Any* p2, float p3, Any p4) { return _i<Void>(0x29DE5FA52D00428C, p0, p1, p2, p3, p4); }
	static Void start_playback_recorded_vehicle_with_flags(Vehicle vehicle, Any p1, const char* playback, Any p3, Any p4, Any p5) { return _i<Void>(0x7D80FD645D4DA346, vehicle, p1, playback, p3, p4, p5); }
	static Void start_vehicle_alarm(Vehicle vehicle) { return _i<Void>(0xB8FF7AB45305C345, vehicle); }
	static Void start_vehicle_horn(Vehicle vehicle, int duration, uint32_t mode, bool forever) { return _i<Void>(0x9C8C6504B5B63D2C, vehicle, duration, mode, forever); }
	static Void stop_all_garage_activity() { return _i<Void>(0x0F87E938BDF29D66); }
	static Void _0x7C06330BFDDA182E(Any p0) { return _i<Void>(0x7C06330BFDDA182E, p0); }
	static Void stop_playback_recorded_vehicle(Any p0) { return _i<Void>(0x54833611C17ABDEA, p0); }
	static Void _0x83F813570FF519DE(Any p0, Any p1) { return _i<Void>(0x83F813570FF519DE, p0, p1); }
	static Void _0xF488C566413B4232(Any p0, float p1) { return _i<Void>(0xF488C566413B4232, p0, p1); }
	static Void switch_train_track(int intersectionId, bool state) { return _i<Void>(0xFD813BB7DB977F20, intersectionId, state); }
	static Void toggle_vehicle_mod(Vehicle vehicle, int modType, bool toggle) { return _i<Void>(0x2A1F4F37F95BAD08, vehicle, modType, toggle); }
	static Void track_vehicle_visibility(Vehicle vehicle) { return _i<Void>(0x64473AEFDCF47DCA, vehicle); }
	static Void unpause_playback_recorded_vehicle(Any p0) { return _i<Void>(0x8879EE09268305D5, p0); }
	static Void _0x756AE6E962168A04(Any p0, Any p1) { return _i<Void>(0x756AE6E962168A04, p0, p1); }
	static Void _0x1BBAC99C0BC53656(Any p0, Any p1) { return _i<Void>(0x1BBAC99C0BC53656, p0, p1); }
	static Void _0x9D30687C57BAA0BB(Any p0) { return _i<Void>(0x9D30687C57BAA0BB, p0); }
	static Void set_vehicle_parachute_model(Vehicle vehicle, uint32_t parachuteModel) { return _i<Void>(0x4D610C6B56031351, vehicle, parachuteModel); }
	static Void set_vehicle_parachute_texture(Vehicle vehicle, int colorIndex) { return _i<Void>(0xA74AD2439468C883, vehicle, colorIndex); }
	static Void set_ramp_vehicle_receives_ramp_damage(Vehicle vehicle, bool receivesDamage) { return _i<Void>(0x28D034A93FE31BF5, vehicle, receivesDamage); }
	static Void set_vehicle_parachute_active(Vehicle vehicle, bool active) { return _i<Void>(0x0BFFB028B3DD0A97, vehicle, active); }
	static Void get_random_vehicle_model_in_memory(bool p0, uint32_t* modelHash, int* p2) { return _i<Void>(0x055BF0AC0C34F4FD, p0, modelHash, p2); }
	static Void set_vehicle_name_debug(Vehicle vehicle, const char* name) { return _i<Void>(0xBFDF984E2C22B94F, vehicle, name); }
	static Void _0xB264C4D2F2B0A78B(Vehicle vehicle) { return _i<Void>(0xB264C4D2F2B0A78B, vehicle); }

	static int _0xFDBF4CDBC07E1706(float x, float y, float z, float radius, float unk) { return _i<int>(0xFDBF4CDBC07E1706, x, y, z, radius, unk); }
	static float get_waves_intensity() { return _i<float>(0x2B2A2CC86778B619); }
	static bool get_water_height(float x, float y, float z, float* height) { return _i<bool>(0xF6829842C06AE524, x, y, z, height); }
	static bool get_water_height_no_waves(float x, float y, float z, float* height) { return _i<bool>(0x8EE6B53CE13A9794, x, y, z, height); }
	static Void modify_water(float x, float y, float radius, float height) { return _i<Void>(0xC443FD757C3BA637, x, y, radius, height); }
	static Void _0xB1252E3E59A82AAF(int p0) { return _i<Void>(0xB1252E3E59A82AAF, p0); }
	static Void reset_waves_intensity() { return _i<Void>(0x5E5E99285AE812DB); }
	static Void _0x547237AA71AB44DE(Any p0) { return _i<Void>(0x547237AA71AB44DE, p0); }
	static Void set_waves_intensity(float intensity) { return _i<Void>(0xB96B00E976BE977F, intensity); }
	static bool test_probe_against_all_water(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return _i<bool>(0x8974647ED222EA5F, p0, p1, p2, p3, p4, p5, p6, p7); }
	static bool test_probe_against_water(float x1, float y1, float z1, float x2, float y2, float z2, math::vector3<float>* result) { return _i<bool>(0xFFA5D878809819DB, x1, y1, z1, x2, y2, z2, result); }
	static bool test_vertical_probe_against_all_water(float x, float y, float z, Any p3, Any* p4) { return _i<bool>(0x2B3451FA1E3142E2, x, y, z, p3, p4); }

	static Void add_ammo_to_ped(Ped ped, uint32_t weaponHash, int ammo) { return _i<Void>(0x78F0424C34306220, ped, weaponHash, ammo); }
	static Void _0x2472622CE1F2D45F(Any p0, Any p1, Any p2) { return _i<Void>(0x2472622CE1F2D45F, p0, p1, p2); }
	static bool can_use_weapon_on_parachute(uint32_t weaponHash) { return _i<bool>(0xBC7BE5ABC0879F74, weaponHash); }
	static Void clear_entity_last_weapon_damage(Entity entity) { return _i<Void>(0xAC678E40BE7C74D2, entity); }
	static Void clear_ped_last_weapon_damage(Ped ped) { return _i<Void>(0x0E98F88A24C5F4B8, ped); }
	static Any _0x9DA58CDBF6BDBC08(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return _i<Any>(0x9DA58CDBF6BDBC08, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static Any _0x91EF34584710BE99(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return _i<Any>(0x91EF34584710BE99, p0, p1, p2, p3, p4, p5, p6, p7); }
	static Object create_weapon_object(uint32_t weaponHash, int ammoCount, float x, float y, float z, bool showWorldModel, float heading, Any p7, Any p8, Any p9) { return _i<Object>(0x9541D3CF0D398F36, weaponHash, ammoCount, x, y, z, showWorldModel, heading, p7, p8, p9); }
	static Any _0xCD79A550999D7D4F(Any p0) { return _i<Any>(0xCD79A550999D7D4F, p0); }
	static bool does_weapon_take_weapon_component(uint32_t weaponHash, uint32_t componentHash) { return _i<bool>(0x5CEE3DF569CECAB0, weaponHash, componentHash); }
	static Void enable_laser_sight_rendering(bool toggle) { return _i<Void>(0xC8B46D7727D864AA, toggle); }
	static Void explode_projectiles(Ped ped, uint32_t weaponHash, bool p2) { return _i<Void>(0xFC4BD125DE7611E4, ped, weaponHash, p2); }
	static Void _0x44F1012B69313374(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x44F1012B69313374, p0, p1, p2, p3); }
	static bool get_ammo_in_clip(Ped ped, uint32_t weaponHash, int* ammo) { return _i<bool>(0x2E1202248937775C, ped, weaponHash, ammo); }
	static int get_ammo_in_ped_weapon(Ped ped, uint32_t weaponhash) { return _i<int>(0x015A522136D7F951, ped, weaponhash); }
	static uint32_t get_best_ped_weapon(Ped ped, bool p1) { return _i<uint32_t>(0x8483E98E8B888AE2, ped, p1); }
	static bool get_current_ped_vehicle_weapon(Ped ped, uint32_t* weaponHash) { return _i<bool>(0x1017582BCD3832DC, ped, weaponHash); }
	static bool get_current_ped_weapon(Ped ped, uint32_t* weaponHash, bool p2) { return _i<bool>(0x3A87E44BB9A01D54, ped, weaponHash, p2); }
	static Entity get_current_ped_weapon_entity_index(Ped ped) { return _i<Entity>(0x3B390A939AF0B5FC, ped); }
	static bool get_is_ped_gadget_equipped(Ped ped, uint32_t gadgetHash) { return _i<bool>(0xF731332072F5156C, ped, gadgetHash); }
	static float get_lockon_range_of_current_ped_weapon(Ped ped) { return _i<float>(0x840F03E9041E2C9C, ped); }
	static bool get_max_ammo(Ped ped, uint32_t weaponHash, int* ammo) { return _i<bool>(0xDC16122C7A20C933, ped, weaponHash, ammo); }
	static bool get_max_ammo_by_type(Ped p0, int p1, int* p2) { return _i<Any>(0x585847C5E4E11709, p0, p1, p2); }
	static int get_max_ammo_in_clip(Ped ped, uint32_t weaponHash, bool p2) { return _i<int>(0xA38DCFFCEA8962FA, ped, weaponHash, p2); }
	static float get_max_range_of_current_ped_weapon(Ped ped) { return _i<float>(0x814C9D19DFD69679, ped); }
	static int get_ped_ammo_by_type(Ped ped, Any ammoType) { return _i<int>(0x39D22031557946C1, ped, ammoType); }
	static uint32_t get_ped_ammo_type_froweapon(Ped ped, uint32_t weaponHash) { return _i<uint32_t>(0x7FEAD38B326B9F74, ped, weaponHash); }
	static bool get_ped_last_weapon_impact_coord(Ped ped, math::vector3<float>* coords) { return _i<bool>(0x6C4D0409BA1A2BC2, ped, coords); }
	static uint32_t get_ped_ammo_type_from_weapon2(Ped ped, uint32_t weaponHash) { return _i<uint32_t>(0xF489B44DD5AF4BD9, ped, weaponHash); }
	static uint32_t get_ped_weapontype_in_slot(Ped ped, uint32_t weaponSlot) { return _i<uint32_t>(0xEFFED78E9011134D, ped, weaponSlot); }
	static Any _0xA2C9AC24B4061285(Any p0, Any p1) { return _i<Any>(0xA2C9AC24B4061285, p0, p1); }
	static Any _0xF0A60040BE558F2D(Any p0, Any p1, Any p2) { return _i<Any>(0xF0A60040BE558F2D, p0, p1, p2); }
	static int get_ped_weapon_tint_index(Ped ped, uint32_t weaponHash) { return _i<int>(0x2B9EEDC07BD06B9F, ped, weaponHash); }
	static uint32_t get_selected_ped_weapon(Ped ped) { return _i<uint32_t>(0x0A6DB4965674D243, ped); }
	static uint32_t get_weapontype_group(uint32_t weaponHash) { return _i<uint32_t>(0xC3287EE3050FB74C, weaponHash); }
	static uint32_t get_weapontype_model(uint32_t weaponHash) { return _i<uint32_t>(0xF46CDC33180FDA94, weaponHash); }
	static uint32_t get_weapontype_slot(uint32_t weaponHash) { return _i<uint32_t>(0x4215460B9B8B7FA0, weaponHash); }
	static int get_weapon_clip_size(uint32_t weaponHash) { return _i<int>(0x583BE370B1EC6EB4, weaponHash); }
	static bool get_weapon_component_hud_stats(uint32_t componentHash, int* outData) { return _i<bool>(0xB3CAF387AE12E9F8, componentHash, outData); }
	static uint32_t get_weapon_component_type_model(uint32_t componentHash) { return _i<uint32_t>(0x0DB57B41EC1DB083, componentHash); }
	static Any _0x6558AC7C17BFEF58(Any p0) { return _i<Any>(0x6558AC7C17BFEF58, p0); }
	static Any _0x4D1CB8DC40208A17(Any p0, Any p1) { return _i<Any>(0x4D1CB8DC40208A17, p0, p1); }
	static float _0x3133B907D8B32053(Any p0, Any p1) { return _i<float>(0x3133B907D8B32053, p0, p1); }
	static int get_weapon_damage_type(uint32_t weaponHash) { return _i<int>(0x3BE0BB12D25FB305, weaponHash); }
	static bool get_weapon_hud_stats(uint32_t weaponHash, int* outData) { return _i<bool>(0xD92C739EE34C9EBA, weaponHash, outData); }
	static Any _0xB3EA4FEABF41464B(Any p0, Any p1) { return _i<Any>(0xB3EA4FEABF41464B, p0, p1); }
	static Object get_weapon_object_from_ped(Ped ped, bool p1) { return _i<Object>(0xCAE1DC9A0E22A16D, ped, p1); }
	static int get_weapon_object_tint_index(Object weapon) { return _i<int>(0xCD183314F7CD2E57, weapon); }
	static int get_weapon_tint_count(uint32_t weaponHash) { return _i<int>(0x5DCF6C5CAB2E9BF7, weaponHash); }
	static Void give_delayed_weapon_to_ped(Ped ped, uint32_t weaponHash, int time, bool equipNow) { return _i<Void>(0xB282DC6EBD803C75, ped, weaponHash, time, equipNow); }
	static Void _0x68F8BE6AF5CDF8A6(Any p0, Any p1) { return _i<Void>(0x68F8BE6AF5CDF8A6, p0, p1); }
	static Void give_weapon_component_to_ped(Ped ped, uint32_t weaponHash, uint32_t componentHash) { return _i<Void>(0xD966D51AA5B28BB9, ped, weaponHash, componentHash); }
	static Void give_weapon_component_to_weapon_object(Object weaponObject, uint32_t addonHash) { return _i<Void>(0x33E179436C0B31DB, weaponObject, addonHash); }
	static Void give_weapon_object_to_ped(Object weaponObject, Ped ped) { return _i<Void>(0xB1FA61371AF7C4B7, weaponObject, ped); }
	static Void give_weapon_to_ped(Ped ped, uint32_t weaponHash, int ammoCount, bool isHidden, bool equipNow) { return _i<Void>(0xBF0FD6E56C964FCB, ped, weaponHash, ammoCount, isHidden, equipNow); }
	static bool has_entity_been_damaged_by_weapon(Entity entity, uint32_t weaponHash, int weaponType) { return _i<bool>(0x131D401334815E94, entity, weaponHash, weaponType); }
	static bool has_ped_been_damaged_by_weapon(Ped ped, uint32_t weaponHash, int weaponType) { return _i<bool>(0x2D343D2219CD027A, ped, weaponHash, weaponType); }
	static bool has_ped_got_weapon(Ped ped, uint32_t weaponHash, bool p2) { return _i<bool>(0x8DECB02F88F428BC, ped, weaponHash, p2); }
	static bool has_ped_got_weapon_component(Ped ped, uint32_t weaponHash, uint32_t componentHash) { return _i<bool>(0xC593212475FAE340, ped, weaponHash, componentHash); }
	static bool has_vehicle_got_projectile_attached(Ped driver, Vehicle vehicle, uint32_t weaponHash, Any p3) { return _i<bool>(0x717C8481234E3B88, driver, vehicle, weaponHash, p3); }
	static bool has_weapon_asset_loaded(uint32_t weaponHash) { return _i<bool>(0x36E353271F0E90EE, weaponHash); }
	static bool has_weapon_got_weapon_component(Object weapon, uint32_t addonHash) { return _i<bool>(0x76A18844E743BF91, weapon, addonHash); }
	static Void hide_ped_weapon_for_scripted_cutscene(Ped ped, bool toggle) { return _i<Void>(0x6F6981D2253C208F, ped, toggle); }
	static Any _0xDAB963831DBFD3F4(Any p0, Any p1, Any p2, Any p3, Any p4) { return _i<Any>(0xDAB963831DBFD3F4, p0, p1, p2, p3, p4); }
	static bool is_flash_light_on(Ped ped) { return _i<bool>(0x4B7620C47217126C, ped); }
	static bool is_ped_armed(Ped ped, int p1) { return _i<bool>(0x475768A975D5AD17, ped, p1); }
	static bool is_ped_current_weapon_silenced(Ped ped) { return _i<bool>(0x65F0C5AE05943EC7, ped); }
	static bool is_ped_weapon_component_active(Ped ped, uint32_t weaponHash, uint32_t componentHash) { return _i<bool>(0x0D78DE0572D3969E, ped, weaponHash, componentHash); }
	static bool is_ped_weapon_ready_to_shoot(Ped ped) { return _i<bool>(0xB80CA294F2F26749, ped); }
	static bool is_weapon_valid(uint32_t weaponHash) { return _i<bool>(0x937C71165CF334B3, weaponHash); }
	static bool make_ped_reload(Ped ped) { return _i<bool>(0x20AE33F3AC9C0033, ped); }
	static bool ped_skip_next_reloading(Ped ped) { return _i<bool>(0x8C0D57EA686FAD87, ped); }
	static Any _0x0ABF535877897560(Any p0) { return _i<Any>(0x0ABF535877897560, p0); }
	static Void _0x1E45B34ADEBEE48E() { return _i<Void>(0x1E45B34ADEBEE48E); }
	static Void remove_all_ped_weapons(Ped ped, bool p1) { return _i<Void>(0xF25DF915FA38C5F3, ped, p1); }
	static Void remove_all_projectiles_of_type(uint32_t weaponHash, bool p1) { return _i<Void>(0xFC52E0F37E446528, weaponHash, p1); }
	static Void remove_weapon_asset(uint32_t weaponHash) { return _i<Void>(0xAA08EF13F341C8FC, weaponHash); }
	static Void remove_weapon_component_from_ped(Ped ped, uint32_t weaponHash, uint32_t componentHash) { return _i<Void>(0x1E8BE90C74FB4C09, ped, weaponHash, componentHash); }
	static Void remove_weapon_component_froweapon_object(Any p0, Any p1) { return _i<Void>(0xF7D82B0D66777611, p0, p1); }
	static Void remove_weapon_from_ped(Ped ped, uint32_t weaponHash) { return _i<Void>(0x4899CB088EDF59B8, ped, weaponHash); }
	static Void request_weapon_asset(uint32_t weaponHash, int p1, int p2) { return _i<Void>(0x5443438F033E29C3, weaponHash, p1, p2); }
	static Void request_weapon_high_detail_model(Entity weaponObject) { return _i<Void>(0x48164DBB970AC3F0, weaponObject); }
	static bool set_ammo_in_clip(Ped ped, uint32_t weaponHash, int ammo) { return _i<bool>(0xDCD2A934D65CB497, ped, weaponHash, ammo); }
	static Void _0xEFF296097FF1E509(Any p0, Any p1) { return _i<Void>(0xEFF296097FF1E509, p0, p1); }
	static Void _0xB4771B9AAF4E68E4(Any p0, Any p1, Any p2) { return _i<Void>(0xB4771B9AAF4E68E4, p0, p1, p2); }
	static bool set_current_ped_vehicle_weapon(Ped ped, uint32_t weaponHash) { return _i<bool>(0x75C55983C2C39DAA, ped, weaponHash); }
	static Void set_current_ped_weapon(Ped ped, uint32_t weaponHash, bool equipNow) { return _i<Void>(0xADF692B254977C0C, ped, weaponHash, equipNow); }
	static Void _0xE4DCEC7FD5B739A5(Ped ped) { return _i<Void>(0xE4DCEC7FD5B739A5, ped); }
	static Any set_flash_light_fade_distance(float distance) { return _i<Any>(0xCEA66DAD478CD39B, distance); }
	static Void set_ped_ammo(Ped ped, uint32_t weaponHash, int ammo, Any p3) { return _i<Void>(0x14E56BC5B5DB6A19, ped, weaponHash, ammo, p3); }
	static Void set_ped_ammo_by_type(Ped ped, Any ammoType, int ammo) { return _i<Void>(0x5FD1E1F011E76D7E, ped, ammoType, ammo); }
	static Void set_ped_ammo_to_drop(Any p0, Any p1) { return _i<Void>(0xA4EFEF9440A5B0EF, p0, p1); }
	static Void set_ped_chance_of_firing_blanks(Ped ped, float xBias, float yBias) { return _i<Void>(0x8378627201D5497D, ped, xBias, yBias); }
	static Void set_ped_current_weapon_visible(Ped ped, bool visible, bool deselectWeapon, bool p3, bool p4) { return _i<Void>(0x0725A4CCFDED9A70, ped, visible, deselectWeapon, p3, p4); }
	static Void set_ped_drops_inventory_weapon(Ped ped, uint32_t weaponHash, float xOffset, float yOffset, float zOffset, Any p5) { return _i<Void>(0x208A1888007FC0E6, ped, weaponHash, xOffset, yOffset, zOffset, p5); }
	static Void set_ped_drops_weapon(Ped ped) { return _i<Void>(0x6B7513D9966FBEC0, ped); }
	static Void set_ped_drops_weapons_when_dead(Ped ped, bool toggle) { return _i<Void>(0x476AE72C1D19D1A8, ped, toggle); }
	static Void set_ped_gadget(Ped ped, uint32_t gadgetHash, bool p2) { return _i<Void>(0xD0D7B1E680ED4A1A, ped, gadgetHash, p2); }
	static Void set_ped_infinite_ammo(Ped ped, bool toggle, uint32_t weaponHash) { return _i<Void>(0x3EDCB0505123623B, ped, toggle, weaponHash); }
	static Void set_ped_infinite_ammo_clip(Ped ped, bool toggle) { return _i<Void>(0x183DADC6AA953186, ped, toggle); }
	static Entity _0xB4C8D77C80C0421E(Ped ped, float p1) { return _i<Entity>(0xB4C8D77C80C0421E, ped, p1); }
	static Void _0x9FE5633880ECD8ED(Any p0, Any p1, Any p2, Any p3) { return _i<Void>(0x9FE5633880ECD8ED, p0, p1, p2, p3); }
	static Void set_ped_weapon_tint_index(Ped ped, uint32_t weaponHash, int tintIndex) { return _i<Void>(0x50969B9B89ED5738, ped, weaponHash, tintIndex); }
	static Void _0xE620FD3512A04F18(float p0) { return _i<Void>(0xE620FD3512A04F18, p0); }
	static Void _0xECDC202B25E5CF48(Any p0, Any p1, Any p2) { return _i<Void>(0xECDC202B25E5CF48, p0, p1, p2); }
	static Void set_weapon_animation_override(Ped ped, uint32_t animStyle) { return _i<Void>(0x1055AC3A667F09D9, ped, animStyle); }
	static Void _0x4757F00BC6323CFE(Any p0, Any p1) { return _i<Void>(0x4757F00BC6323CFE, p0, p1); }
	static Void _0x977CA98939E82E4B(Any p0, Any p1) { return _i<Void>(0x977CA98939E82E4B, p0, p1); }
	static Void _0x5DA825A85D0EA6E6(Any p0, Any p1, Any p2) { return _i<Void>(0x5DA825A85D0EA6E6, p0, p1, p2); }
	static Void set_weapon_object_tint_index(Object weapon, int tintIndex) { return _i<Void>(0xF827589017D4E4A9, weapon, tintIndex); }

	static Void clear_popschedule_override_vehicle_model(int scheduleId) { return _i<Void>(0x5C0DE367AA0D911C, scheduleId); }
	static uint32_t get_hash_of_map_area_at_coords(float x, float y, float z) { return _i<uint32_t>(0x7EE64D51E8498728, x, y, z); }
	static const char* get_name_of_zone(float x, float y, float z) { return _i<const char*>(0xCD90657D4C30E1CA, x, y, z); }
	static int get_zone_at_coords(float x, float y, float z) { return _i<int>(0x27040C25DE6CB2F4, x, y, z); }
	static int get_zone_from_name_id(const char* zoneName) { return _i<int>(0x98CD1D2934B76CC1, zoneName); }
	static int get_zone_popschedule(int zoneId) { return _i<int>(0x4334BC40AA0CB4BB, zoneId); }
	static int get_zone_scumminess(int zoneId) { return _i<int>(0x5F7B268D15BA0739, zoneId); }
	static Void override_popschedule_vehicle_model(int scheduleId, uint32_t vehicleHash) { return _i<Void>(0x5F7D596BAC2E7777, scheduleId, vehicleHash); }
	static Void set_zone_enabled(int zoneId, bool toggle) { return _i<Void>(0xBA5ECEEA120E5611, zoneId, toggle); }
}
