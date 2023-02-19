#include "panels.h"
#include "util/localization.h"
#include "util/va.h"
#include "menu/base/renderer.h"
#include "global/ui_vars.h"
#include "global/vars.h"
#include "global/lists.h"
#include "menu/base/base.h"
#include "menu/base/util/player_manager.h"
#include "menu/base/util/global.h"
#include "menu/base/util/textures.h"
#include "menu/base/util/helpers.h"
#include "rage/invoker/natives.h"
#include "rage/engine.h"
#include "menu/base/util/on_screen_ped.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_ip.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_rid.h"
#include "menu/base/submenus/main/network/network_spoofing.h"
#include "menu/base/submenus/main/settings/hide_info.h"
#include "rage/types/global_types.h"
#include <algorithm>
#include <sstream>

namespace menu::panels {
#undef DrawText
	localization t_name("Name", true, true);
	localization t_rank("Rank", true, true);
	localization t_health("Health", true, true);
	localization t_invalid("Invalid", true, true);
	localization t_dead("Dead", true, true);
	localization t_full("Full", true, true);
	localization t_cash("Cash", true, true);
	localization t_armor("Armor", true, true);
	localization t_bank("Bank", true, true);
	localization t_wanted_level("Wanted Level", true, true);
	localization t_kd_ratio("K/D Ratio", true, true);
	localization t_ammo("Ammo", true, true);
	localization t_none("None", true, true);
	localization t_weapon("Weapon", true, true);
	localization t_unarmed("Unarmed", true, true);
	localization t_unknown("Unknown", true, true);
	localization t_zone("Zone", true, true);
	localization t_street("Street", true, true);
	localization t_coords("Coords", true, true);
	localization t_heading("Heading", true, true);
	localization t_north("North", true, true);
	localization t_east("East", true, true);
	localization t_south("South", true, true);
	localization t_west("West", true, true);
	localization t_distance("Distance", true, true);
	localization t_speed("Speed", true, true);
	localization t_passive("Passive", true, true);
	localization t_invisible("Invisible", true, true);
	localization t_yes("Yes", true, true);
	localization t_no("No", true, true);
	localization t_rid("Rockstar ID", true, true);
	localization t_hidden("Hidden", true, true);
	localization t_ip("IP", true, true);
	localization t_vehicle("Vehicle", true, true);
	localization t_crew("Crew", true, true);
	localization t_crew_tag("Crew Tag", true, true);
	localization t_crew_id("Crew ID", true, true);
	localization t_crew_rank("Crew Rank", true, true);
	localization t_using_controller("Using Controller", true, true);
	localization t_using_keyboard("Using Keyboard", true, true);
	localization t_badsport("Badsport", true, true);
	localization t_cheater("Cheater", true, true);
	localization t_toxic("Toxic", true, true);
	localization t_muted_me("Muted Me", true, true);
	localization t_off_the_radar("Off the Radar", true, true);
	localization t_reveal_players("Reveal Players", true, true);
	localization t_rdeveloper("R* Developer", true, true);
	localization t_rqa_developer("R* QA Tester", true, true);
	localization t_property("Property", true, true);
	localization t_properties("Properties", true, true);
	localization t_office_garage("Office Garage", true, true);
	localization t_clubhouse("Clubhouse", true, true);
	localization t_office("Office", true, true);
	localization t_races_won("Races Won", true, true);
	localization t_deathmatches_won("Deathmatches Won", true, true);
	localization t_darts_won("Darts Won", true, true);
	localization t_arm_wrestling_won("Arm Wrestling Won", true, true);
	localization t_tennis_won("Tennis Won", true, true);
	localization t_golf_won("Golf Won", true, true);
	localization t_shooting_range_won("Shooting Range Won", true, true);
	localization t_deaths("Deaths", true, true);
	localization t_kills("Kills", true, true);
	localization t_missions_created("Missions Created", true, true);
	localization t_zip("Zip", true, true);
	localization t_region("Region", true, true);
	localization t_city("City", true, true);
	localization t_country("Country", true, true);
	localization t_timezone("Timezone", true, true);
	localization t_isp("ISP", true, true);
	localization t_org("Org", true, true);
	localization t_station("Station", true, true);
	localization t_song("Song", true, true);
	localization t_artist("Artist", true, true);
	localization t_placeholder("Placeholder", true, true);
	localization t_some_time_ago("Some Time Ago", true, true);
	localization t_online("Online", true, true);
	localization t_in_session("In My Session?", true, true);
	localization t_first_encountered("First Encounter", true, true);
	localization t_last_encountered("Last Encounter", true, true);
	localization t_session_type("Session Type", true, true);
	localization t_preview("Preview", true, true);
	localization t_enabled("Enabled", true, true);
	localization t_manufacturer("Manufacturer", true, true);
	localization t_max_speed("Max Speed", true, true);
	localization t_max_braking("Max Braking", true, true);
	localization t_max_traction("Max Traction", true, true);
	localization t_max_seats("Max Seats", true, true);
	localization t_blacklisted_players("Blacklisted Players", true, true);
	localization t_clock("Clock", true, true);
	localization t_outfit_preview("Outfit Preview", true, true);
	localization t_outfit_preview_info("Outfit Preview", true, true);
	localization t_clock_info("Clock Info", true, true);
	localization t_next_session_host_queue("Next Session Host Queue", true, true);
	localization t_peer("Peer", true, true);
	localization t_second("Second", true, true);
	localization t_minute("Minute", true, true);
	localization t_hour("Hour", true, true);
	localization t_ago("Ago", true, true);
	localization t_added("Added", true, true);
	localization t_generic("Generic", true, true);
	localization t_geo("Geo", true, true);
	localization t_flags("Flags", true, true);
	localization t_kick_queue("Kick Queue", true, true);
	localization t_stats("Stats", true, true);
	localization t_radio("Radio", true, true);
	localization t_station_info("Station Info", true, true);
	localization t_recent_player("Recent Player", true, true);
	localization t_player_info("Player Info", true, true);
	localization t_friend("Friend", true, true);
	localization t_friend_info("Friend Info", true, true);
	localization t_overseer("Overseer", true, true);
	localization t_overseer_info("Overseer Info", true, true);
	localization t_vehicle_preview("Vehicle Preview", true, true);
	localization t_vehicle_preview_info("Vehicle Preview Info", true, true);
	localization t_session("Session", true, true);
	localization t_host_queue_info("Host Queue Info", true, true);
	localization t_blacklist_info("Blacklist Info", true, true);
	localization t_session_browser("Session Browser", true, true);
	localization t_player_search("Player Search", true, true);
	localization t_session_browser_info("Session Browser Info", true, true);
	localization t_player_search_info("Player Search Info", true, true);
	localization t_blacklisted_players_info("Blacklisted Players Info", true, true);
	localization t_local_ip("Local IP", true, true);

	math::vector2<float> panel::get_rendering_position() {
		math::vector2<float> _return;

		if (m_child->m_column == 0) {
			// base
			if (global::ui::g_position.x >= 0.40f) {
				_return.x = global::ui::g_position.x - 0.283f;

				if (!m_child->m_double_sided) {
					_return.x += 0.14f; // size of half panel
				}
			} else {
				_return.x = global::ui::g_position.x + global::ui::g_scale.x + 0.003f;
			}
		} else {
			// Calculate x offsets
			float calculated_offset = 0.f;

			for (int i = 0; i < m_child->m_column; i++) {
				if (m_child->m_parent->m_column_offset.find(i) != m_child->m_parent->m_column_offset.end()) {
					calculated_offset += m_child->m_parent->m_column_offset[i].x;
				}
			}

			if (global::ui::g_position.x >= 0.40f) {
				_return.x = global::ui::g_position.x - 0.283f;
				_return.x -= calculated_offset;

				if (m_child->m_double_sided && m_child->m_parent->m_column_offset[m_child->m_column - 1].x == 0.14f) {
					_return.x -= 0.14f;
				}

				if (!m_child->m_double_sided) {
					_return.x += 0.14f; // size of half panel
				}
			} else {
				_return.x = global::ui::g_position.x + global::ui::g_scale.x + 0.003f;
				_return.x += calculated_offset;
			}
		}

		if (m_child->m_column != 0) {
			if (global::ui::g_position.x >= 0.40f) _return.x -= (m_child->m_column * 0.002f);
			else _return.x += (m_child->m_column * 0.002f);
		}

		return _return;
	}

	panel::panel(panel_child& child, color_rgba header_color) {
		m_child = &child;

		int max_count = child.m_panel_option_count_left;
		if (child.m_panel_option_count_right > max_count) {
			max_count = child.m_panel_option_count_right;
		}

		child.m_panel_option_count_left = child.m_panel_tick_left - 1;
		child.m_panel_option_count_right = child.m_panel_option_count_right - 1;

		if (m_child->m_parent->m_column_offset.find(child.m_column) == m_child->m_parent->m_column_offset.end()) {
			m_column_offset = 0.f;
		} else {
			m_column_offset = (m_child->m_parent->m_column_offset[child.m_column].y);
		}

		// render bar & bg
		m_column_adjustment = get_rendering_position();

		float x = m_column_adjustment.x;
		float width = child.m_double_sided ? 0.28f : 0.14f;

		// header
		menu::renderer::draw_rect({ x, (global::ui::g_position.y - 0.08f) + m_column_offset }, { width, (0.007875f / 2.f) }, header_color);

		// bg
		std::pair<std::string, std::string> texture = menu::renderer::get_texture(global::ui::m_panel_background);
		menu::renderer::draw_sprite_aligned(texture, { x, (global::ui::g_position.y - 0.08f) + (0.007875f / 2.f) + m_column_offset }, { width, (0.03f * max_count) }, 0.f, global::ui::g_panel_background);

		m_width = width;
		m_height = (0.03f * max_count) + (0.007875f / 2.f) + 0.004f;

		child.m_panel_tick_left = 1;
		child.m_panel_tick_right = 1;
	}

	void panel::item(std::string name, std::string value, int font, float font_scale, color_rgba color) {
		if (!m_child->m_double_sided) {
			panel_left_item(name, value, font, font_scale, color);
			return;
		}

		if (m_child->m_panel_tick_left > m_child->m_panel_tick_right) {
			panel_right_item(name, value, font, font_scale, color);
		} else {
			panel_left_item(name, value, font, font_scale, color);
		}
	}

	void panel::item(std::string name, std::string sprite_left, std::string sprite_right, int font, float font_scale, color_rgba color, math::vector2<float> scale) {
		if (!m_child->m_double_sided) {
			panel_left_sprite_item(name, sprite_left, sprite_right, font, font_scale, color, scale);
			return;
		}

		if (m_child->m_panel_tick_left > m_child->m_panel_tick_right) {
			panel_right_sprite_item(name, sprite_left, sprite_right, font, font_scale, color, scale);
		} else {
			panel_left_sprite_item(name, sprite_left, sprite_right, font, font_scale, color, scale);
		}
	}

	void panel::item_full(std::string name, std::string value, int font, float font_scale, color_rgba color) {
		if (font == 0) {
			if (global::ui::g_panel_font != 0) {
				font = global::ui::g_panel_font;
				font_scale = menu::renderer::get_normalized_font_scale(font, font_scale);
			}
		}

		if (m_child->m_panel_tick_left != m_child->m_panel_tick_right) {
			if (m_child->m_panel_tick_left > m_child->m_panel_tick_right) {
				m_child->m_panel_tick_right = m_child->m_panel_tick_left;
			} else {
				m_child->m_panel_tick_left = m_child->m_panel_tick_right;
			}
		}

		float adjustment = m_column_adjustment.x;
		float wrap = (adjustment + 0.28f - 0.004f);;
		float x = adjustment + 0.003f;

		// draw name
		menu::renderer::draw_text(name.c_str(), { x, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_left - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color);

		// draw value
		menu::renderer::draw_text(value.c_str(), { 0.f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_left - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color, JUSTIFY_RIGHT, { 0.f, wrap });

		m_child->m_panel_tick_left++;
		m_child->m_panel_tick_right++;
	}

	void panel::item_full(std::string name, std::string sprite_left, std::string sprite_right, int font, float font_scale, color_rgba color, math::vector2<float> scale) {
		if (font == 0) {
			if (global::ui::g_panel_font != 0) {
				font = global::ui::g_panel_font;
				font_scale = menu::renderer::get_normalized_font_scale(font, font_scale);
			}
		}

		if (m_child->m_panel_tick_left != m_child->m_panel_tick_right) {
			if (m_child->m_panel_tick_left > m_child->m_panel_tick_right) {
				m_child->m_panel_tick_right = m_child->m_panel_tick_left;
			} else {
				m_child->m_panel_tick_left = m_child->m_panel_tick_right;
			}
		}

		float adjustment = m_column_adjustment.x;
		float wrap = (adjustment + 0.28f - 0.004f);;
		float x = adjustment + 0.003f;

		// sprite
		menu::renderer::draw_sprite({ sprite_left, sprite_right }, { x + 0.006f, (global::ui::g_position.y - 0.08f) + 0.017f + ((m_child->m_panel_tick_left - 1) * 0.03f) + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, scale, 0.f, color);

		// draw name
		menu::renderer::draw_text(name.c_str(), { x + 0.014f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_left - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color);

		m_child->m_panel_tick_left++;
		m_child->m_panel_tick_right++;
	}

	void panel::panel_left_item(std::string name, std::string value, int font, float font_scale, color_rgba color) {
		if (font == 0) {
			if (global::ui::g_panel_font != 0) {
				font = global::ui::g_panel_font;
				font_scale = menu::renderer::get_normalized_font_scale(font, font_scale);
			}
		}

		float x = m_column_adjustment.x;
		float x2 = x + 0.003f;
		float wrap = (x + 0.14f - 0.004f);

		// draw name
		menu::renderer::draw_text(name.c_str(), { x2, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_left - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color);

		// draw value
		menu::renderer::draw_text(value.c_str(), { 0.f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_left - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color, JUSTIFY_RIGHT, { 0.f, wrap });

		m_child->m_panel_tick_left++;
	}

	void panel::panel_right_item(std::string name, std::string value, int font, float font_scale, color_rgba color) {
		if (font == 0) {
			if (global::ui::g_panel_font != 0) {
				font = global::ui::g_panel_font;
				font_scale = menu::renderer::get_normalized_font_scale(font, font_scale);
			}
		}

		float adjustment = m_column_adjustment.x;
		float x = m_column_adjustment.x;
		float wrap = (x + 0.28f - 0.004f);

		// draw divider
		menu::renderer::draw_rect({ x + 0.14f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_right - 1) * 0.03f) + (0.007875f / 2.f) + m_column_offset + 0.00525f }, { 0.001f, 0.021f }, { 255, 255, 255, 255 });

		// draw name
		menu::renderer::draw_text(name.c_str(), { x + 0.14f + 0.004f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_right - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color);

		// draw value
		menu::renderer::draw_text(value.c_str(), { 0.f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_right - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color, JUSTIFY_RIGHT, { 0.f, wrap });

		m_child->m_panel_tick_right++;
	}

	void panel::panel_left_sprite_item(std::string name, std::string sprite_left, std::string sprite_right, int font, float font_scale, color_rgba color, math::vector2<float> scale) {
		if (font == 0) {
			if (global::ui::g_panel_font != 0) {
				font = global::ui::g_panel_font;
				font_scale = menu::renderer::get_normalized_font_scale(font, font_scale);
			}
		}

		float x = m_column_adjustment.x;
		float x2 = x + 0.003f;

		if (m_child->m_double_sided) {
			// draw divider
			menu::renderer::draw_rect({ x + 0.14f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_left - 1) * 0.03f) + (0.007875f / 2.f) + m_column_offset + 0.00525f }, { 0.001f, 0.021f }, { 255, 255, 255, 255 });
		}

		// sprite
		menu::renderer::draw_sprite({ sprite_left, sprite_right }, { x2 + 0.006f, (global::ui::g_position.y - 0.08f) + 0.017f + ((m_child->m_panel_tick_left - 1) * 0.03f) + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, scale, 0.f, color);

		// draw name
		menu::renderer::draw_text(name.c_str(), { x2 + 0.014f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_left - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color);

		m_child->m_panel_tick_left++;
	}

	void panel::panel_right_sprite_item(std::string name, std::string sprite_left, std::string sprite_right, int font, float font_scale, color_rgba color, math::vector2<float> scale) {
		if (font == 0) {
			if (global::ui::g_panel_font != 0) {
				font = global::ui::g_panel_font;
				font_scale = menu::renderer::get_normalized_font_scale(font, font_scale);
			}
		}

		float adjustment = m_column_adjustment.x;
		float x = m_column_adjustment.x;
		float x2 = x + 0.14f + 0.003f;

		// sprite
		menu::renderer::draw_sprite({ sprite_left, sprite_right }, { x2 + 0.009f, (global::ui::g_position.y - 0.08f) + 0.017f + ((m_child->m_panel_tick_right - 1) * 0.03f) + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, scale, 0.f, color);

		// draw name
		menu::renderer::draw_text(name.c_str(), { x + 0.14f + 0.004f + 0.018f, (global::ui::g_position.y - 0.08f) + ((m_child->m_panel_tick_right - 1) * 0.03f) + 0.006f + ((0.007875f / 2.f) - 0.0017875f) + m_column_offset }, font_scale, font, color);

		m_child->m_panel_tick_right++;
	}

	void panel_manager::update() {
		if (global::vars::g_unloading || m_rearranging || !menu::base::is_open() || global::ui::g_input_open) return;

		for (panel_parent* panel : m_panels) {
			if (global::vars::g_unloading || m_rearranging) return;
			for (std::pair<const int, math::vector2<float>>& e : panel->m_column_offset) e.second = math::vector2<float>(0.f, 0.f);

			if (panel->m_render) {
				if (!panel->m_children_panels.empty()) {
					for (int j = 0; j < 20; j++) {
						for (std::size_t i = 0; i < panel->m_children_panels.size(); i++) {
							if (global::vars::g_unloading || m_rearranging) return;

							auto& child = panel->m_children_panels[i];
							if (child.m_column == j) {
								if (child.m_render) {
									math::vector2<float> scale = child.m_update(child);

									if (panel->m_column_offset[child.m_column].x < scale.x) {
										panel->m_column_offset[child.m_column].x = scale.x;
									}

									panel->m_column_offset[child.m_column].y += scale.y;
								}
							}
						}
					}
				}
			}
		}
	}

	void panel_manager::cleanup() {
		for (panel_parent* panel : m_panels) {
			if (panel) delete panel;
		}
	}

	panel_parent* panel_manager::get_parent(std::string ID) {
		auto Search = std::find_if(m_panels.begin(), m_panels.end(), [=](panel_parent* Element) { return Element->m_id == ID; });
		if (Search != m_panels.end()) {
			return *(Search);
		}

		return nullptr;
	}

	panel_child& panel_manager::get_child(panel_parent* parent, std::string ID) {
		static panel_child _static;
		if (!parent) return _static;

		auto Search = std::find_if(parent->m_children_panels.begin(), parent->m_children_panels.end(), [=](panel_child& Element) { return Element.m_id == ID; });
		if (Search != parent->m_children_panels.end()) {
			return *(Search);
		}

		return _static;
	}

	void panel_manager::toggle_panel_render(std::string parent_id, bool toggle) {
		panel_parent* parent = get_parent(parent_id);
		if (parent) {
			parent->m_render = toggle;
		}
	}

	void panel_manager::rearrange(panel_parent* parent, std::string ID, int Column, int Position) {
		if (!parent) return;
		m_rearranging = true;

		panel_child& child = get_child(parent, ID);

		if (child.m_index != Position) {
			child.m_index = Position;
		}

		if (Column != child.m_column) {
			int index = 0;
			for (auto& Elem : parent->m_children_panels) {
				if (Elem.m_column == Column) {
					if (Elem.m_index > index) {
						index = Elem.m_index;
					}
				}
			}

			child.m_index = index + 1;
			child.m_column = Column;
		}

		std::sort(parent->m_children_panels.begin(), parent->m_children_panels.end(), [=](panel_child& left, panel_child& right) {
			return left.m_index < right.m_index;
		});

		m_rearranging = false;
	}

	void panel_manager::null_structure(panel_child& _this) {
		memset(_this.m_custom_ptr, 0, sizeof(_this.m_custom_ptr));
	}

	void panel_manager::set_structure(panel_child& _this, void* data, int Size) {
		memcpy(_this.m_custom_ptr, data, Size);
	}

	math::vector2<float> panel_manager::render_panel_player_info_name(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);
		if (menu::player::get_selected_player().m_name.empty()) return math::vector2<float>(0.f, 0.f);

		panel panel(_this, global::ui::g_panel_bar);

		const char* name = menu::player::get_selected_player().m_name.c_str();
		if (menu::player::get_local_player().m_id == menu::player::get_selected_player().m_id) {
			/*if (!NetworkSpoofingNameMenuVars::m_vars.m_SpoofedName.empty()) {
				name = NetworkSpoofingNameMenuVars::m_vars.m_SpoofedName.c_str();
			}*/
		}

		if (native::is_pedheadshot_valid(menu::player::get_selected_player().m_ped_headshot)) {
			const char* texture = native::get_pedheadshot_txd_string(menu::player::get_selected_player().m_ped_headshot);
			panel.item_full(std::string(util::va::va("%s", name)), texture, texture, 1, 0.41f, { 255,255,255,255 }, { 0.0192f * 0.8f, 0.0336f * 0.8f });
		} else panel.item_full(std::string(util::va::va("%s", name)), "", 1, 0.41f);

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_player_info_generic(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);

		static char buffers[11][50];
		memset(buffers, 0, sizeof(buffers));

		panel panel(_this, global::ui::g_panel_bar);
		menu::player::player_context& selected = menu::player::get_selected_player();

		panel.item(TRANSLATE(t_rank), std::string(util::va::vap(buffers[0], "%i", script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(6).as<int>()))); // 1.55 done

		int health = native::get_entity_health(selected.m_ped);
		int max_health = native::get_entity_max_health(selected.m_ped);

		if (health == 0 && max_health == 0) {
			panel.item(TRANSLATE(t_health), "~m~" + std::string(TRANSLATE(t_invalid)));
		} else if (health == 0 && max_health != 0) {
			panel.item(TRANSLATE(t_health), "~r~" + std::string(TRANSLATE(t_dead)));
		} else if (health == max_health) {
			panel.item(TRANSLATE(t_health), "~g~" + std::string(TRANSLATE(t_full)));
		} else {
			panel.item(TRANSLATE(t_health), std::string(util::va::vap(buffers[1], "~o~%i%%", ((health * 100) / max_health))).c_str());
		}

		panel.item(TRANSLATE(t_cash), std::string(util::va::vap(buffers[2], "%i", script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>())));// 1.55 done
		panel.item(TRANSLATE(t_armor), std::string(util::va::vap(buffers[3], "%i", native::get_ped_armour(selected.m_ped))));
		panel.item(TRANSLATE(t_bank), std::string(util::va::vap(buffers[4], "%i", script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(56).as<int>() - script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>())));// 1.55 done
		panel.item(TRANSLATE(t_wanted_level), std::string(util::va::vap(buffers[5], "%i/5", native::get_player_wanted_level(selected.m_id))));
		panel.item(TRANSLATE(t_kd_ratio), std::string(util::va::vap(buffers[6], "%.2f", script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(26).as<float>())));// 1.55 done

		int ammo = native::get_ammo_in_ped_weapon(selected.m_ped, selected.m_weapon_hash);
		panel.item(TRANSLATE(t_ammo), ammo > 0 ? std::to_string(ammo) : "~m~" + std::string(TRANSLATE(t_none)));

		bool rendered = false;
		for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
			if (selected.m_weapon_hash == weapon.m_result) {
				rendered = true;
				panel.item_full(TRANSLATE(t_weapon), weapon.m_name.get());
				break;
			}
		}

		if (!rendered) {
			panel.item_full(TRANSLATE(t_weapon), "~m~" + std::string(TRANSLATE(t_unarmed)));
		}

		panel.item_full(TRANSLATE(t_zone), native::get_label_text(native::get_name_of_zone(selected.m_coords.x, selected.m_coords.y, selected.m_coords.z)));

		uint32_t street, crossing;
		native::get_street_name_at_coord(selected.m_coords.x, selected.m_coords.y, selected.m_coords.z, &street, &crossing);

		const char* street_label = native::get_street_name_from_hash_key(street);
		const char* crossing_label = native::get_street_name_from_hash_key(crossing);

		const char* street_output = "";
		if (strlen(street_label) > 0) {
			street_output = street_label;
		} else if (strlen(crossing_label) > 0) {
			street_output = crossing_label;
		} else street_output = ("~m~" + std::string(TRANSLATE(t_unknown))).c_str();

		panel.item_full(TRANSLATE(t_street), street_output);
		panel.item(TRANSLATE(t_coords), std::string(util::va::vap(buffers[7], "[%.0f,%.0f,%.0f]", selected.m_coords.x, selected.m_coords.y, selected.m_coords.z)));

		float heading = selected.m_heading;
		if (heading >= 0.f && heading <= 90.f) {
			panel.item(TRANSLATE(t_heading), std::string(util::va::vap(buffers[8], "%s (%.0f)", TRANSLATE(t_north), heading)).c_str());
		} else if (heading >= 90.f && heading <= 180.f) {
			panel.item(TRANSLATE(t_heading), std::string(util::va::vap(buffers[8], "%s (%.0f)", TRANSLATE(t_east), heading)).c_str());
		} else if (heading >= 180.f && heading <= 270.f) {
			panel.item(TRANSLATE(t_heading), std::string(util::va::vap(buffers[8], "%s (%.0f)", TRANSLATE(t_south), heading)).c_str());
		} else if (heading >= 270.f && heading <= 360.f) {
			panel.item(TRANSLATE(t_heading), std::string(util::va::vap(buffers[8], "%s (%.0f)", TRANSLATE(t_west), heading)).c_str());
		} else panel.item(TRANSLATE(t_heading), "~m~" + std::string(TRANSLATE(t_invalid)));

		panel.item(TRANSLATE(t_distance), std::string(util::va::vap(buffers[9], "%.2f", selected.m_coords.get_distance(menu::player::get_local_player().m_coords))));
		panel.item(TRANSLATE(t_speed), std::string(util::va::vap(buffers[10], "%.0f %s", native::get_entity_speed(selected.m_entity) * global::vars::g_selected_metric_system.first, global::vars::g_selected_metric_system.second.c_str())));
		panel.item(TRANSLATE(t_passive), native::get_blip_sprite(native::get_blip_from_entity(selected.m_ped)) == 163 ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));
		panel.item(TRANSLATE(t_invisible), !native::is_entity_visible_to_script(selected.m_ped) ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));

		rendered = false;
		if (is_valid_ptr(selected.m_net_player)) {
			if (selected.m_net_player->m_player_info) {
				if (!settings::hide::vars::m_vars.m_hide_rockstar_ids) {
					uint64_t rockstar_id = selected.m_net_player->m_player_info->m_identifier.m_rockstar_id;

					if (selected.m_id == menu::player::get_local_player().m_id) {
						if (network::spoofing::rid::vars::m_vars.m_spoofing_rid != rockstar_id) {
							rockstar_id = network::spoofing::rid::vars::m_vars.m_spoofing_rid;
						}
					}

					panel.item(TRANSLATE(t_rid), std::to_string(rockstar_id));
				} else {
					panel.item(TRANSLATE(t_rid), "~m~" + std::string(TRANSLATE(t_hidden)));
				}

				rendered = true;
			}
		}

		if (!rendered) {
			panel.item(TRANSLATE(t_rid), "~m~" + std::string(TRANSLATE(t_unknown)));
		}

		rendered = false;
		if (is_valid_ptr(selected.m_net_player)) {
			if (selected.m_net_player->m_player_info) {
				uint32_t IP = selected.m_net_player->m_player_info->m_external_ip;

				auto vit = std::find_if(global::vars::g_relay_usage.begin(), global::vars::g_relay_usage.end(), [=](relay_usage& Usage) {
					return !strcmp(Usage.m_name, selected.m_name.c_str()) && Usage.m_rockstar_id == selected.m_net_player->m_player_info->m_identifier.m_rockstar_id;
				});

				if (vit != global::vars::g_relay_usage.end()) {
					IP = vit->m_external_ip;
				}

				char buffer[16];
				sprintf_s(buffer, "%i.%i.%i.%i", ((IP & 0xFF000000) >> 24), ((IP & 0xFF0000) >> 16), ((IP & 0xFF00) >> 8), (IP & 0xFF));

				if (selected.m_id == menu::player::get_local_player().m_id) {
					if (!network::spoofing::ip::vars::m_vars.m_spoofing_ip.empty() && network::spoofing::ip::vars::m_vars.m_spoofing_ip.compare(buffer)) {
						strcpy(buffer, network::spoofing::ip::vars::m_vars.m_spoofing_ip.c_str());
					}
				}

				if (!settings::hide::vars::m_vars.m_hide_ips) {
					panel.item(TRANSLATE(t_ip), buffer);
				} else {
					panel.item(TRANSLATE(t_ip), "~m~" + std::string(TRANSLATE(t_hidden)));
				}

				rendered = true;
			}
		}

		if (!rendered) {
			panel.item("IP", "~m~" + std::string(TRANSLATE(t_unknown)));
		}

		rendered = false;
		if (is_valid_ptr(selected.m_net_player)) {
			if (selected.m_net_player->m_player_info) {
				std::stringstream stream;
				stream << std::hex << selected.m_net_player->m_player_info->m_host_token;

				if (selected.m_id == menu::player::get_local_player().m_id) {
					if (network::spoofing::vars::m_vars.m_spoofed_peer != network::spoofing::vars::m_vars.m_original_peer) {
						stream = std::stringstream();
						stream << std::hex << network::spoofing::vars::m_vars.m_spoofed_peer;
					}
				}

				panel.item(TRANSLATE(t_peer), stream.str());
				rendered = true;
			}
		}

		if (!rendered) {
			panel.item(TRANSLATE(t_peer), "~m~" + std::string(TRANSLATE(t_unknown)));
		}

		panel.item("Device", script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(96).at(29).as<int>() == 2 ? TRANSLATE(t_using_controller) : TRANSLATE(t_using_keyboard)); // 1.55 good

		if (selected.m_in_vehicle) {
			panel.item_full(TRANSLATE(t_vehicle), native::get_label_text(native::get_display_name_from_vehicle_model(native::get_entity_model(selected.m_vehicle))));
		}

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_player_info_crew(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);

		menu::player::player_context& selected = menu::player::get_selected_player();
		if (selected.m_net_player && strlen(selected.m_net_player->get_crew_name()) > 0) {
			panel panel(_this, global::ui::g_panel_bar);

			panel.item_full(TRANSLATE(t_crew), selected.m_net_player->get_crew_name());
			panel.item(TRANSLATE(t_crew_tag), selected.m_net_player->get_crew_tag());
			panel.item(TRANSLATE(t_crew_id), std::to_string(selected.m_net_player->get_crew_id()));
			panel.item_full(TRANSLATE(t_crew_rank), selected.m_net_player->get_crew_rank());

			return panel.get_render_scale();
		}

		return math::vector2<float>(0.f, 0.f);
	}

	math::vector2<float> panel_manager::render_panel_player_info_flags(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);

		_this.m_double_sided = false;
		menu::player::player_context& selected = menu::player::get_selected_player();

		bool rockstar_developer = false;
		bool rockstar_qa_tester = false;

		if (is_valid_ptr(selected.m_net_player)) {
			if (selected.m_net_player) {
				rockstar_developer = selected.m_net_player->m_is_rockstar_developer;
				rockstar_qa_tester = selected.m_net_player->m_is_rockstar_qa;
			}
		}

		if (!(rockstar_developer
			|| rockstar_qa_tester
			|| native::is_bit_set(script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(51).as<int>(), 1) // 1.55 done
			|| native::is_bit_set(script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(51).as<int>(), 4) // 1.55 done
			|| native::is_bit_set(script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(51).as<int>(), 3) // 1.55 done
			|| native::network_am_i_muted_by_player(selected.m_id)
			|| script_global(rage::global::_155_property_base2).at(selected.m_id, rage::global::_155_property_base2_size).at(200).as<int>() == 1// 1.55 done
			|| selected.m_is_modder)) {
			return math::vector2<float>(0.f, 0.f);
		}

		panel panel(_this, global::ui::g_panel_bar);

		if (native::is_bit_set(script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(51).as<int>(), 1)) {// 1.55 done
			panel.item(TRANSLATE(t_badsport), "mpleaderboard", "leaderboard_deaths_icon");
		}

		if (native::is_bit_set(script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(51).as<int>(), 4)) {// 1.55 done
			panel.item(TRANSLATE(t_cheater), "mpleaderboard", "leaderboard_globe_icon");
		}

		if (native::is_bit_set(script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(51).as<int>(), 3)) {// 1.55 done
			panel.item(TRANSLATE(t_toxic), "mpleaderboard", "leaderboard_globe_icon");
		}

		if (native::network_am_i_muted_by_player(selected.m_id)) {
			panel.item(TRANSLATE(t_muted_me), "mpleaderboard", "leaderboard_audio_3");
		}

		if (script_global(rage::global::_155_property_base2).at(selected.m_id, rage::global::_155_property_base2_size).at(200).as<int>() == 1) {// 1.55 done
			panel.item(TRANSLATE(t_off_the_radar), "mpleaderboard", "leaderboard_kd_icon");
		}

		if (script_global(rage::global::_155_property_base2).at(selected.m_id, rage::global::_155_property_base2_size).at(212).as<int>() == 1) {// 1.55 done
			panel.item(TRANSLATE(t_reveal_players), "mpleaderboard", "leaderboard_kd_icon");
		}

		if (rockstar_developer) {
			panel.item(TRANSLATE(t_rdeveloper), "mpleaderboard", "leaderboard_star_icon");
		}

		if (rockstar_qa_tester) {
			panel.item(TRANSLATE(t_rqa_developer), "mpleaderboard", "leaderboard_star_icon");
		}

		for (std::size_t i = 0; i < menu::player::REASON_END; i++) {
			if (selected.m_modder_flags[(menu::player::ePlayerReportReasons)i]) {
				panel.item("~r~" + menu::player::get_report_reason((menu::player::ePlayerReportReasons)i), "mpleaderboard", "leaderboard_players_icon");
			}
		}

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_player_info_vote_kick_queue(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);

		menu::player::player_context& selected = menu::player::get_selected_player();

		std::vector<std::string> voting_to_kick;
		menu::player::for_each([&](menu::player::player_context& Player) {
			if (script_global(1619390).at(Player.m_id, 100).at(selected.m_id + 1).as<int>() == 1) { // 1.55 done
				voting_to_kick.push_back(Player.m_name);
			}
		}, true);

		if (voting_to_kick.size()) {
			_this.m_double_sided = false;
			panel panel(_this, global::ui::g_panel_bar);

			for (std::string client : voting_to_kick) {
				panel.item(client, "mpleaderboard", "leaderboard_kick_icon");
			}

			return panel.get_render_scale();
		}

		return math::vector2<float>(0.f, 0.f);
	}

	math::vector2<float> panel_manager::render_panel_player_info_properties(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);

		menu::player::player_context& selected = menu::player::get_selected_player();

		std::vector<std::pair<int, bool>> apartments;

		for (int i = 0; i < 4; i++) {
			int Val = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(267 + 7 + i).as<int>();
			apartments.push_back({ Val, Val != 0 });
		}

		std::vector<std::pair<int, bool>> garages;
		for (int i = 0; i < 3; i++) {
			int Val = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(275 + 7 + i).as<int>();
			garages.push_back({ Val, Val != 0 });
		}

		std::pair<int, bool> office;
		office.first = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(272 + 7).as<int>();
		office.second = office.first != 0;

		std::pair<int, bool> clubhouse;
		clubhouse.first = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(273 + 7).as<int>();
		clubhouse.second = clubhouse.first != 0;

		bool owns_property =
			apartments[0].second || apartments[1].second || apartments[2].second || apartments[3].second
			|| office.second || clubhouse.second;

		int property_count =
			(int)apartments[0].second + (int)apartments[1].second + (int)apartments[2].second + (int)apartments[3].second
			+ (int)clubhouse.second + (int)clubhouse.second;

		if (owns_property) {
			static char buffers[4][50];

			panel panel(_this, global::ui::g_panel_bar);

			int count = 0;
			for (std::pair<int, bool> e : garages) {
				if (e.second) count++;
			}

			if (property_count == 1) {
				if (office.second && count > 0) {
					panel.item("1 " + std::string(TRANSLATE(t_property)), "mpleaderboard", "leaderboard_rankshield_icon");
				} else {
					panel.item_full("1 " + std::string(TRANSLATE(t_property)), "mpleaderboard", "leaderboard_rankshield_icon");
				}
			} else {
				if (office.second && count > 0) {
					panel.item(std::string(util::va::vap(buffers[0], "%i %s", property_count, TRANSLATE(t_properties))), "mpleaderboard", "leaderboard_rankshield_icon");
				} else {
					panel.item_full(std::string(util::va::vap(buffers[1], "%i %s", property_count, TRANSLATE(t_properties))), "mpleaderboard", "leaderboard_rankshield_icon");
				}
			}

			if (office.second && count > 0) {
				panel.item(std::string(util::va::vap(buffers[2], "%i %s%c", count, TRANSLATE(t_office_garage), count > 1 ? 's' : ' ')), "mpinventory", "mp_specitem_car", 0, 0.3f, { 255,255,255,255 }, { 0.0192f * 0.8f, 0.0336f * 0.8f });
			}

			for (int i = 0; i < 4; i++) {
				if (apartments[i].second) {
					panel.item_full(std::string(util::va::vap(buffers[3], "%s #%i", TRANSLATE(t_property), i + 1)), menu::helpers::get_location_from_id(apartments[i].first));
				}
			}

			if (clubhouse.second) {
				panel.item_full(TRANSLATE(t_clubhouse), menu::helpers::get_location_from_id(clubhouse.first));
			}

			if (office.second) {
				panel.item_full(TRANSLATE(t_office), menu::helpers::get_location_from_id(office.first));
			}

			return panel.get_render_scale();
		}

		return math::vector2<float>(0.f, 0.f);
	}

	math::vector2<float> panel_manager::render_panel_player_info_stats(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);

		_this.m_double_sided = false;

		menu::player::player_context& selected = menu::player::get_selected_player();
		panel panel(_this, global::ui::g_panel_bar);

		int races_won = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(15).as<int>();	// 1.55 done
		int races_lost = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(16).as<int>();// 1.55 done

		int deathmatches_won = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(20).as<int>();// 1.55 done
		int deathmatches_lost = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(21).as<int>();// 1.55 done

		int darts_won = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(32).as<int>();// 1.55 done
		int darts_total = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(33).as<int>();// 1.55 done

		int arm_wrestling_won = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(34).as<int>();// 1.55 done
		int arm_wrestling_total = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(35).as<int>();// 1.55 done

		int tennis_won = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(36).as<int>();// 1.55 done
		int tennis_lost = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(37).as<int>();// 1.55 done

		int golf_won = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(40).as<int>();// 1.55 done
		int golf_lost = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(41).as<int>();// 1.55 done

		int shooting_range_won = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(42).as<int>();// 1.55 done
		int shooting_range_lost = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(43).as<int>();// 1.55 done

		int deaths = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(29).as<int>();// 1.55 done
		int missions_created = script_global(rage::global::_155_player_stats_struct).at(selected.m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(50).as<int>();// 1.55 done

		static char buffers[9][50];

		panel.item(TRANSLATE(t_races_won), std::string(util::va::vap(buffers[0], "%i/%i", races_won, races_won + races_lost)));
		panel.item(TRANSLATE(t_deathmatches_won), std::string(util::va::vap(buffers[1], "%i/%i", deathmatches_won, deathmatches_won + deathmatches_lost)));
		panel.item(TRANSLATE(t_darts_won), std::string(util::va::vap(buffers[2], "%i/%i", darts_won, darts_total)));
		panel.item(TRANSLATE(t_arm_wrestling_won), std::string(util::va::vap(buffers[3], "%i/%i", arm_wrestling_won, arm_wrestling_total)));
		panel.item(TRANSLATE(t_tennis_won), std::string(util::va::vap(buffers[4], "%i/%i", tennis_won, tennis_won + tennis_lost)));
		panel.item(TRANSLATE(t_golf_won), std::string(util::va::vap(buffers[5], "%i/%i", golf_won, golf_won + golf_lost)));
		panel.item(TRANSLATE(t_shooting_range_won), std::string(util::va::vap(buffers[6], "%i/%i", shooting_range_won, shooting_range_won + shooting_range_lost)));
		panel.item(TRANSLATE(t_deaths), std::string(util::va::vap(buffers[7], "%i", deaths)));
		panel.item(TRANSLATE(t_missions_created), std::string(util::va::vap(buffers[8], "%i", missions_created)));

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_player_info_geo(panel_child& _this) {
		if (!menu::player::get_selected_player().m_connected) return math::vector2<float>(0.f, 0.f);
		menu::player::player_context& selected = menu::player::get_selected_player();

		if (is_valid_ptr(selected.m_net_player)) {
			if (selected.m_net_player && selected.m_net_player->m_player_info) {
				auto vit = global::vars::g_geo.find(selected.m_net_player->m_player_info->m_external_ip);
				if (vit != global::vars::g_geo.end()) {
					panel panel(_this, global::ui::g_panel_bar);

					if (!vit->second.m_zip.empty()) panel.item(TRANSLATE(t_zip), vit->second.m_zip);
					if (!vit->second.m_region_name.empty()) panel.item(TRANSLATE(t_region), vit->second.m_region_name);
					if (!vit->second.m_city.empty()) panel.item(TRANSLATE(t_city), vit->second.m_city);
					if (!vit->second.m_country.empty()) panel.item(TRANSLATE(t_country), vit->second.m_country);
					if (!vit->second.m_timezone.empty()) panel.item_full(TRANSLATE(t_timezone), vit->second.m_timezone);
					if (!vit->second.m_isp.empty()) panel.item_full(TRANSLATE(t_isp), vit->second.m_isp);
					if (!vit->second.m_org.empty()) panel.item_full(TRANSLATE(t_org), vit->second.m_org);

					return panel.get_render_scale();
				}
			}
		}

		return math::vector2<float>(0.f, 0.f);
	}

	math::vector2<float> panel_manager::render_panel_radio(panel_child& _this) {
		if (native::get_player_radio_station_index() != 255) {
			panel panel(_this, global::ui::g_panel_bar);

			char local_20[500];
			int local_26 = native::get_audible_music_track_text_id();

			strncpy_s(local_20, "", 64);
			strncat_s(local_20, std::to_string(local_26).c_str(), 64);
			strncat_s(local_20, "S", 64);
			strncpy(&(local_20[16]), "", 32);
			strncat(&(local_20[16]), std::to_string(local_26).c_str(), 32);
			strncat(&(local_20[16]), "A", 32);
			strncpy(&(local_20[25]), native::get_player_radio_station_name(), 24);

			panel.item_full(TRANSLATE(t_station), native::get_label_text(native::get_player_radio_station_name()));
			if (native::get_hash_key(native::get_label_text(local_20)) != joaat("NULL")) {
				panel.item_full(TRANSLATE(t_song), native::get_label_text(local_20));
				panel.item_full(TRANSLATE(t_artist), native::get_label_text(&local_20[16]));
			}

			return panel.get_render_scale();
		}

		return math::vector2<float>(0.f, 0.f);
	}

	math::vector2<float> panel_manager::render_panel_recent_player(panel_child& _this) {
		panel_custom_recent_player* data = (panel_custom_recent_player*)_this.m_custom_ptr;

		if (*(uint8_t*)(&data->m_name) == 0 || data->m_name[0] == 0) {
			// Preview
			data->m_has_stats = false;
			data->m_in_session = false;
			data->m_online = false;
			data->m_rockstar_id = 0;
			data->m_session_type = -1;
			strcpy_s(data->m_name, TRANSLATE(t_placeholder));
			strcpy_s(data->m_ip, "1.1.1.1");
			strcpy_s(data->m_first_encountered, TRANSLATE(t_some_time_ago));
			strcpy_s(data->m_last_encountered, TRANSLATE(t_some_time_ago));
		}

		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		panel.item(TRANSLATE(t_name), settings::hide::vars::m_vars.m_hide_names ? TRANSLATE(t_hidden) : data->m_name);
		panel.item(TRANSLATE(t_rid), settings::hide::vars::m_vars.m_hide_rockstar_ids ? TRANSLATE(t_hidden) : std::string(util::va::va("%i", data->m_rockstar_id)));
		panel.item(TRANSLATE(t_ip), settings::hide::vars::m_vars.m_hide_ips ? TRANSLATE(t_hidden) : data->m_ip);

		if (data->m_rockstar_id == 0) {
			panel.item(TRANSLATE(t_online), "~r~" + std::string(TRANSLATE(t_no)));
		} else panel.item(TRANSLATE(t_online), (data->m_online || data->m_in_session) ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));

		panel.item(TRANSLATE(t_in_session), data->m_in_session ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));
		panel.item(TRANSLATE(t_session_type), menu::helpers::get_gs_type(data->m_session_type));

		if (data->m_has_stats) {
			float kd = 0.f;
			if (data->m_stats.m_deaths == 0) {
				kd = (float)data->m_stats.m_kills;
			} else {
				kd = (float)data->m_stats.m_kills / (float)data->m_stats.m_deaths;
			}

			panel.item(TRANSLATE(t_rank), (data->m_stats.m_rank > 2500 ? "~y~" : "") + std::to_string(data->m_stats.m_rank));
			panel.item(TRANSLATE(t_cash), (data->m_stats.m_wallet_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_wallet_balance));
			panel.item(TRANSLATE(t_bank), (data->m_stats.m_bank_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_bank_balance));
			panel.item(TRANSLATE(t_kills), std::to_string(data->m_stats.m_kills));
			panel.item(TRANSLATE(t_deaths), std::to_string(data->m_stats.m_deaths));
			panel.item(TRANSLATE(t_kd_ratio), util::va::va("%.2f", kd));
		}

		panel.item(TRANSLATE(t_first_encountered), data->m_first_encountered);
		panel.item(TRANSLATE(t_last_encountered), data->m_last_encountered);
		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_friend(panel_child& _this) {
		panel_custom_friend* data = (panel_custom_friend*)_this.m_custom_ptr;

		if (*(uint8_t*)(&data->m_name) == 0 || data->m_name[0] == 0) {
			// Preview
			strcpy_s(data->m_name, TRANSLATE(t_preview));
			data->m_rockstar_id = 1337;
			data->m_has_stats = false;
			data->m_online = false;
			data->m_in_session = false;
			data->m_session_type = -1;
		}

		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		panel.item(TRANSLATE(t_name), settings::hide::vars::m_vars.m_hide_names ? TRANSLATE(t_hidden) : data->m_name);
		panel.item(TRANSLATE(t_rid), settings::hide::vars::m_vars.m_hide_rockstar_ids ? TRANSLATE(t_hidden) : std::to_string(data->m_rockstar_id));

		if (data->m_rockstar_id == 0) {
			panel.item(TRANSLATE(t_online), "~r~" + std::string(TRANSLATE(t_no)));
		} else panel.item(TRANSLATE(t_online), data->m_online ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));

		panel.item(TRANSLATE(t_in_session), data->m_in_session ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));
		panel.item(TRANSLATE(t_session_type), menu::helpers::get_gs_type(data->m_session_type));

		if (data->m_has_stats) {
			float kd = 0.f;
			if (data->m_stats.m_deaths == 0) {
				kd = (float)data->m_stats.m_kills;
			} else {
				kd = (float)data->m_stats.m_kills / (float)data->m_stats.m_deaths;
			}

			panel.item(TRANSLATE(t_rank), (data->m_stats.m_rank > 2500 ? "~y~" : "") + std::to_string(data->m_stats.m_rank));
			panel.item(TRANSLATE(t_cash), (data->m_stats.m_wallet_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_wallet_balance));
			panel.item(TRANSLATE(t_bank), (data->m_stats.m_bank_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_bank_balance));
			panel.item(TRANSLATE(t_kills), std::to_string(data->m_stats.m_kills));
			panel.item(TRANSLATE(t_deaths), std::to_string(data->m_stats.m_deaths));
			panel.item(TRANSLATE(t_kd_ratio), util::va::va("%.2f", kd));
		}

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_overseer(panel_child& _this) {
		panel_custom_overseer* data = (panel_custom_overseer*)_this.m_custom_ptr;

		if (data->m_name[0] == 0) {
			strcpy_s(data->m_name, TRANSLATE(t_preview));
			data->m_flags = 0;
			data->m_rockstar_id = 1337;
			data->m_has_stats = false;
			data->m_online = false;
			data->m_in_session = false;
			data->m_session_type = -1;
		}

		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		panel.item(TRANSLATE(t_name), settings::hide::vars::m_vars.m_hide_names ? TRANSLATE(t_hidden) : data->m_name);
		panel.item(TRANSLATE(t_rid), settings::hide::vars::m_vars.m_hide_rockstar_ids ? TRANSLATE(t_hidden) : std::string(util::va::va("%i", data->m_rockstar_id)));

		if (global::vars::g_online_rockstar_ids.find(data->m_rockstar_id) == global::vars::g_online_rockstar_ids.end()) {
			panel.item(TRANSLATE(t_online), "~r~" + std::string(TRANSLATE(t_no)));
		} else panel.item(TRANSLATE(t_online), global::vars::g_online_rockstar_ids[data->m_rockstar_id].first ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));
		
		panel.item(TRANSLATE(t_in_session), data->m_in_session ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));
		panel.item(TRANSLATE(t_session_type), menu::helpers::get_gs_type(data->m_session_type));
		panel.item(TRANSLATE(t_enabled), (data->m_flags & 1) ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));

		if (data->m_has_stats) {
			float kd = 0.f;
			if (data->m_stats.m_deaths == 0) {
				kd = (float)data->m_stats.m_kills;
			} else {
				kd = (float)data->m_stats.m_kills / (float)data->m_stats.m_deaths;
			}

			panel.item(TRANSLATE(t_rank), (data->m_stats.m_rank > 2500 ? "~y~" : "") + std::to_string(data->m_stats.m_rank));
			panel.item(TRANSLATE(t_cash), (data->m_stats.m_wallet_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_wallet_balance));
			panel.item(TRANSLATE(t_bank), (data->m_stats.m_bank_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_bank_balance));
			panel.item(TRANSLATE(t_kills), std::to_string(data->m_stats.m_kills));
			panel.item(TRANSLATE(t_deaths), std::to_string(data->m_stats.m_deaths));
			panel.item(TRANSLATE(t_kd_ratio), util::va::va("%.2f", kd));
		}

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_vehicle_preview(panel_child& _this) {
		panel_custom_vehicle_preview* data = (panel_custom_vehicle_preview*)_this.m_custom_ptr;

		if (*(uint8_t*)(&data->m_name) == 0 || data->m_name[0] == 0) {
			strcpy_s(data->m_name, TRANSLATE(t_preview));
			strcpy_s(data->m_dict, "");
			strcpy_s(data->m_name, "");

			strcpy_s(data->m_manufacturer, TRANSLATE(t_preview));
			data->m_max_speed = 0.f;
			data->m_max_braking = 0.f;
			data->m_max_traction = 0.f;
			data->m_seats = 0;
		}

		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		float adjustment = panel.get_column_adjustment().x;
		float x = adjustment;

		math::vector2<float> s = { 0.14f, 0.24f };
		float _x = x + (s.x * 0.5f);
		float _y = ((global::ui::g_position.y - 0.08f) + (0.007875f / 2.f) + panel.get_column_offset()) + (s.y * 0.5f) - 0.011f;

		menu::renderer::draw_sprite({ data->m_dict, data->m_name }, { _x, _y }, { 0.12f, 0.18f }, 0.f, { 255, 255, 255, 255 });

		panel.get_panel_child()->m_panel_tick_left = 8;
		panel.get_panel_child()->m_panel_tick_right = 8;

		static char buffers[3][50];
		memset(buffers, 0, sizeof(buffers));

		panel.item(TRANSLATE(t_manufacturer), data->m_manufacturer);
		panel.item(TRANSLATE(t_max_speed), util::va::vap(buffers[0], "%.0f %s", data->m_max_speed, global::vars::g_selected_metric_system.second.c_str()));
		panel.item(TRANSLATE(t_max_braking), util::va::vap(buffers[1], "%.2f", data->m_max_braking));
		panel.item(TRANSLATE(t_max_traction), util::va::vap(buffers[2], "%.2f", data->m_max_traction));
		panel.item(TRANSLATE(t_max_seats), std::to_string(data->m_seats));

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_blacklist(panel_child& _this) {
		_this.m_double_sided = false;

		std::vector<rage::network::blacklisted_player> players;

		if (global::vars::g_network_base_config) {
			rage::network::network_base_config* real_config = global::vars::g_network_base_config;
			if (global::vars::g_steam) {
				real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
			}

			rage::network::blacklisted_player* blacklisted_players = real_config->m_first_blacklisted_player;
			if (is_valid_ptr(blacklisted_players)) {
				for (; blacklisted_players; blacklisted_players = blacklisted_players->m_next) {
					players.push_back(*blacklisted_players);
				}
			}
		}

		if (players.size()) {
			panel panel(_this, global::ui::g_panel_bar);
			panel.item(TRANSLATE(t_blacklisted_players), "", 1, 0.41f);

			if (players.size() > 20) {
				std::sort(players.begin(), players.end(), [](rage::network::blacklisted_player& left, rage::network::blacklisted_player& right) {
					return left.m_timestamp > right.m_timestamp;
				});
			}

			for (rage::network::blacklisted_player player : players) {
				panel.item(std::to_string(player.m_player.m_rockstar_id), "");
			}

			return panel.get_render_scale();
		}

		return math::vector2<float>(0.f, 0.f);
	}

	math::vector2<float> panel_manager::render_panel_host_queue(panel_child& _this) {
		_this.m_double_sided = false;

		std::vector<std::pair<uint64_t, int>> host_queue;

		menu::player::for_each([&](menu::player::player_context& Player) {
			if (rage::engine::get_host_net_game_player() == Player.m_net_player) return;

			if (is_valid_ptr(Player.m_net_player)) {
				if (is_valid_ptr(Player.m_net_player->m_player_info)) {
					host_queue.push_back({ Player.m_net_player->m_player_info->m_host_token, Player.m_id });
				}
			}
		}, true, true);

		if (!host_queue.size()) {
			return math::vector2<float>(0.f, 0.f);
		}

		std::sort(host_queue.begin(), host_queue.end(), [](std::pair<uint64_t, int> a, std::pair<uint64_t, int> b) { return a.first < b.first; });

		panel panel(_this, global::ui::g_panel_bar);
		panel.item(TRANSLATE(t_next_session_host_queue), "", 1, 0.41f);

		for (std::pair<uint64_t, int> user : host_queue) {
			if (!menu::player::get_player(user.second).m_name.empty()) {
				panel.item(menu::player::get_player(user.second).m_name.c_str(), "");
			} else panel.item("~m~" + std::string(TRANSLATE(t_unknown)), "");
		}

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_session_browser(panel_child& _this) {
		panel_custom_session_browser* data = (panel_custom_session_browser*)_this.m_custom_ptr;

		if (data->m_name[0] == 0) {
			strcpy_s(data->m_name, TRANSLATE(t_placeholder));
		}

		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		panel.item(TRANSLATE(t_name), settings::hide::vars::m_vars.m_hide_names ? TRANSLATE(t_hidden) : data->m_name);

		std::stringstream stream;
		stream << std::hex << data->m_peer_token;

		char buffer[16];
		sprintf_s(buffer, "%i.%i.%i.%i", ((data->m_local_ip & 0xFF000000) >> 24), ((data->m_local_ip & 0xFF0000) >> 16), ((data->m_local_ip & 0xFF00) >> 8), (data->m_local_ip & 0xFF));

		panel.item(TRANSLATE(t_rid), settings::hide::vars::m_vars.m_hide_rockstar_ids ? TRANSLATE(t_hidden) : std::to_string(data->m_rockstar_id));
		panel.item(TRANSLATE(t_peer), stream.str());
		panel.item(TRANSLATE(t_local_ip), buffer);

		if (data->m_has_stats) {
			float kd = 0.f;
			if (data->m_stats.m_deaths == 0) {
				kd = (float)data->m_stats.m_kills;
			} else {
				kd = (float)data->m_stats.m_kills / (float)data->m_stats.m_deaths;
			}

			panel.item(TRANSLATE(t_rank), (data->m_stats.m_rank > 2500 ? "~y~" : "") + std::to_string(data->m_stats.m_rank));
			panel.item(TRANSLATE(t_cash), (data->m_stats.m_wallet_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_wallet_balance));
			panel.item(TRANSLATE(t_bank), (data->m_stats.m_bank_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_bank_balance));
			panel.item(TRANSLATE(t_kills), std::to_string(data->m_stats.m_kills));
			panel.item(TRANSLATE(t_deaths), std::to_string(data->m_stats.m_deaths));
			panel.item(TRANSLATE(t_kd_ratio), util::va::va("%.2f", kd));
		}

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_player_search(panel_child& _this) {
		panel_custom_player_search* data = (panel_custom_player_search*)_this.m_custom_ptr;

		if (data->m_name[0] == 0) {
			strcpy_s(data->m_name, TRANSLATE(t_placeholder));
			data->m_rockstar_id = 0;
		}

		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		panel.item(TRANSLATE(t_name), settings::hide::vars::m_vars.m_hide_names ? TRANSLATE(t_hidden) : data->m_name);
		panel.item(TRANSLATE(t_rid), settings::hide::vars::m_vars.m_hide_rockstar_ids ? TRANSLATE(t_hidden) : std::to_string(data->m_rockstar_id));

		if (data->m_rockstar_id == 0) {
			panel.item(TRANSLATE(t_online), "~r~" + std::string(TRANSLATE(t_no)));
		} else panel.item(TRANSLATE(t_online), data->m_online ? "~g~" + std::string(TRANSLATE(t_yes)) : "~r~" + std::string(TRANSLATE(t_no)));

		if (data->m_has_stats) {
			float kd = 0.f;
			if (data->m_stats.m_deaths == 0) {
				kd = (float)data->m_stats.m_kills;
			} else {
				kd = (float)data->m_stats.m_kills / (float)data->m_stats.m_deaths;
			}

			panel.item(TRANSLATE(t_rank), (data->m_stats.m_rank > 2500 ? "~y~" : "") + std::to_string(data->m_stats.m_rank));
			panel.item(TRANSLATE(t_cash), (data->m_stats.m_wallet_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_wallet_balance));
			panel.item(TRANSLATE(t_bank), (data->m_stats.m_bank_balance > 1000000000 ? "~y~" : "") + std::to_string(data->m_stats.m_bank_balance));
			panel.item(TRANSLATE(t_kills), std::to_string(data->m_stats.m_kills));
			panel.item(TRANSLATE(t_deaths), std::to_string(data->m_stats.m_deaths));
			panel.item(TRANSLATE(t_kd_ratio), util::va::va("%.2f", kd));
		}

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_blacklisted_player(panel_child& _this) {
		panel_custom_blacklisted_player* data = (panel_custom_blacklisted_player*)_this.m_custom_ptr;

		if (*(uint8_t*)(&data->m_name) == 0 || data->m_name[0] == 0) {
			strcpy_s(data->m_name, TRANSLATE(t_placeholder));
			data->m_blacklisted_time = timeGetTime();
			data->m_rockstar_id = 0;
		}

		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		panel.item(TRANSLATE(t_rid), settings::hide::vars::m_vars.m_hide_rockstar_ids ? TRANSLATE(t_hidden) : std::to_string(data->m_rockstar_id));
		panel.item(TRANSLATE(t_name), settings::hide::vars::m_vars.m_hide_names ? TRANSLATE(t_hidden) : data->m_name);

		std::string added = TRANSLATE(t_some_time_ago);

		uint32_t elapsed = (GetTickCount() - data->m_blacklisted_time) / 1000;
		if (elapsed > 0) {
			uint32_t minutes = elapsed / 60;
			uint32_t hours = minutes / 60;
			uint32_t days = hours / 24;
			uint32_t weeks = days / 7;
			uint32_t months = weeks / 4;
			uint32_t years = months / 12;

			if (elapsed < 60) {
				added = std::string(util::va::va("%u %s%s Ago", elapsed, TRANSLATE(t_second), elapsed == 1 ? "" : "s"));
			} else if (minutes < 60) {
				added = std::string(util::va::va("%u %s%s Ago", minutes, TRANSLATE(t_minute), minutes == 1 ? "" : "s"));
			} else if (hours < 24) {
				added = std::string(util::va::va("%u %s%s Ago", hours, TRANSLATE(t_hour), hours == 1 ? "" : "s"));
			}
		}

		panel.item(TRANSLATE(t_added), added);
		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_clock(panel_child& _this) {
		_this.m_double_sided = false;
		panel panel(_this, global::ui::g_panel_bar);

		int hour = native::get_clock_hours();
		int minute = native::get_clock_minutes();
		int second = native::get_clock_seconds();

		float max_rotation = 360.f;
		float hour_rotation = ((float)hour / 12.f) * max_rotation;
		float minute_rotation = ((float)minute / 60.f) * max_rotation;
		float second_rotation = ((float)second / 60.f) * max_rotation;

		float hour_bar_width = 0.06f;
		float minute_bar_width = 0.065f;
		float second_bar_width = 0.04f;

		float adjustment = panel.get_column_adjustment().x;
		float x = adjustment;

		math::vector2<float> s = { 0.14f, 0.24f };
		float _x = x + (s.x * 0.5f);
		float _y = ((global::ui::g_position.y - 0.08f) + (0.007875f / 2.f) + panel.get_column_offset()) + (s.y * 0.5f) - 0.011f;

		menu::renderer::draw_sprite({ "ozarktextures", "clock_hand.png" }, { _x, _y }, { second_bar_width, second_bar_width * 2.f }, second_rotation, { 255, 0, 0, 255 });
		menu::renderer::draw_sprite({ "ozarktextures", "clock_hand.png" }, { _x, _y }, { minute_bar_width, minute_bar_width * 2.f }, minute_rotation, { 255, 255, 255, 255 });
		menu::renderer::draw_sprite({ "ozarktextures", "clock_hand.png" }, { _x, _y }, { hour_bar_width, hour_bar_width * 2.f }, hour_rotation, { 255, 255, 255, 255 });
		menu::renderer::draw_sprite({ "ozarktextures", "clock.png" }, { _x, _y }, { 0.1f, 0.18f }, 0.f, { 255, 255, 255, 255 });

		panel.get_panel_child()->m_panel_tick_left = 8;
		panel.get_panel_child()->m_panel_tick_right = 8;

		panel.item("Hour", std::to_string(hour));
		panel.item("Minute", std::to_string(minute));
		panel.item("Second", std::to_string(second));

		return panel.get_render_scale();
	}

	math::vector2<float> panel_manager::render_panel_outfit_preview(panel_child& _this) {
		if (!native::is_pause_menu_active()) {
			if (native::ui3dscene_is_available()) {
				panel_custom_screen_ped_preview* data = (panel_custom_screen_ped_preview*)_this.m_custom_ptr;

				if (is_valid_ptr(data->m_ped) || data->m_is_player) {
					if (data->m_is_player) {
						data->m_ped = nullptr;
						if (menu::player::get_player(data->m_player).m_connected) {
							if (menu::player::get_player(data->m_player).m_ped_ptr) {
								data->m_ped = menu::player::get_player(data->m_player).m_ped_ptr;
							}
						}
					}

					if (!is_valid_ptr(data->m_ped)) return { 0.f, 0.f };

					_this.m_double_sided = false;
					panel panel(_this, global::ui::g_panel_bar);

					math::vector2<float> pos;
					pos.x = panel.get_column_adjustment().x;
					pos.y = ((global::ui::g_position.y - 0.08f) + (0.007875f / 2.f) + panel.get_column_offset());

					menu::screen::ped::draw_on_screen_ped(data->m_ped, pos, { 0.14f, 0.45f }, data->m_screen_offset);

					panel.get_panel_child()->m_panel_tick_left = 16;
					panel.get_panel_child()->m_panel_tick_right = 16;

					return panel.get_render_scale();
				}
			}
		}

		return { 0.f, 0.f };
	}

	void panel_manager::load() {
#pragma region player_info
		panel_parent* player_info = new panel_parent();
		player_info->m_render = false;
		player_info->m_id = "PANEL_PLAYER_INFO";
		player_info->m_name = TRANSLATE(t_player_info);

		std::unordered_map<int, int> index;

		/*panel_child player_info_name;
		player_info_name.m_parent = player_info;
		player_info_name.m_id = "PANEL_PLAYER_INFO_NAME";
		player_info_name.m_name = TRANSLATE(t_name);
		player_info_name.m_column = 0;
		player_info_name.m_index = index[player_info_name.m_column]++;
		player_info_name.m_render = true; // render this child by default
		player_info_name.m_update = render_panel_player_info_name;*/

		panel_child player_info_generic;
		player_info_generic.m_parent = player_info;
		player_info_generic.m_id = "PANEL_PLAYER_INFO_GENERIC";
		player_info_generic.m_name = TRANSLATE(t_generic);
		player_info_generic.m_column = 0;
		player_info_generic.m_index = index[player_info_generic.m_column]++;
		player_info_generic.m_render = true; // render this child by default
		player_info_generic.m_update = render_panel_player_info_generic;

		panel_child player_info_crew;
		player_info_crew.m_parent = player_info;
		player_info_crew.m_id = "PANEL_PLAYER_INFO_CREW";
		player_info_crew.m_name = TRANSLATE(t_crew);
		player_info_crew.m_column = 0;
		player_info_crew.m_index = index[player_info_crew.m_column]++;
		player_info_crew.m_render = true; // render this child by default
		player_info_crew.m_update = render_panel_player_info_crew;

		panel_child player_info_properties;
		player_info_properties.m_parent = player_info;
		player_info_properties.m_id = "PANEL_PLAYER_INFO_PROPERTIES";
		player_info_properties.m_name = TRANSLATE(t_properties);
		player_info_properties.m_column = 0;
		player_info_properties.m_index = index[player_info_properties.m_column]++;
		player_info_properties.m_render = false; // render this child by default
		player_info_properties.m_update = render_panel_player_info_properties;

		panel_child player_info_flags;
		player_info_flags.m_parent = player_info;
		player_info_flags.m_id = "PANEL_PLAYER_INFO_FLAGS";
		player_info_flags.m_name = TRANSLATE(t_flags);
		player_info_flags.m_column = 1;
		player_info_flags.m_index = index[player_info_flags.m_column]++;
		player_info_flags.m_render = true;
		player_info_flags.m_update = render_panel_player_info_flags;

		panel_child player_info_vote_kick_queue;
		player_info_vote_kick_queue.m_parent = player_info;
		player_info_vote_kick_queue.m_id = "PANEL_PLAYER_INFO_VOTE_KICK_QUEUE";
		player_info_vote_kick_queue.m_name = TRANSLATE(t_kick_queue);
		player_info_vote_kick_queue.m_column = 1;
		player_info_vote_kick_queue.m_index = index[player_info_vote_kick_queue.m_column]++;
		player_info_vote_kick_queue.m_render = true;
		player_info_vote_kick_queue.m_update = render_panel_player_info_vote_kick_queue;

		panel_child player_info_screen_ped;
		player_info_screen_ped.m_parent = player_info;
		player_info_screen_ped.m_id = "PANEL_PLAYER_INFO_OUTFIT_PREVIEW";
		player_info_screen_ped.m_name = TRANSLATE(t_outfit_preview_info);
		player_info_screen_ped.m_column = 1; // was 1
		player_info_screen_ped.m_index = index[player_info_screen_ped.m_column]++;
		player_info_screen_ped.m_render = true;
		player_info_screen_ped.m_update = render_panel_outfit_preview;

		panel_child player_info_stats;
		player_info_stats.m_parent = player_info;
		player_info_stats.m_id = "PANEL_PLAYER_INFO_STATS";
		player_info_stats.m_name = TRANSLATE(t_stats);
		player_info_stats.m_column = 1;
		player_info_stats.m_index = index[player_info_stats.m_column]++;
		player_info_stats.m_render = false;
		player_info_stats.m_update = render_panel_player_info_stats;

		panel_child player_info_geo;
		player_info_geo.m_parent = player_info;
		player_info_geo.m_id = "PANEL_PLAYER_INFO_GEO";
		player_info_geo.m_name = TRANSLATE(t_geo);
		player_info_geo.m_column = 0;
		player_info_geo.m_index = index[player_info_geo.m_column]++;
		player_info_geo.m_render = true;
		player_info_geo.m_update = render_panel_player_info_geo;

		// player_info->m_children_panels.push_back(player_info_name);
		player_info->m_children_panels.push_back(player_info_generic);
		player_info->m_children_panels.push_back(player_info_crew);
		player_info->m_children_panels.push_back(player_info_properties);
		player_info->m_children_panels.push_back(player_info_geo);
		player_info->m_children_panels.push_back(player_info_screen_ped);
		player_info->m_children_panels.push_back(player_info_flags);
		player_info->m_children_panels.push_back(player_info_vote_kick_queue);
		player_info->m_children_panels.push_back(player_info_stats);

		m_panels.push_back(player_info);
#pragma endregion

#pragma region Radio
		panel_parent* radio = new panel_parent();
		radio->m_render = false;
		radio->m_id = "PANEL_RADIO";
		radio->m_name = TRANSLATE(t_radio);

		panel_child player_radio;
		player_radio.m_parent = radio;
		player_radio.m_id = "PANEL_RADIO_INFO";
		player_radio.m_name = TRANSLATE(t_station_info);
		player_radio.m_column = 0;
		player_radio.m_index = 0;
		player_radio.m_render = true; // render this child by default
		player_radio.m_update = render_panel_radio;

		radio->m_children_panels.push_back(player_radio);

		m_panels.push_back(radio);
#pragma endregion

#pragma region Recent
		panel_parent* recent_player = new panel_parent();
		recent_player->m_render = false;
		recent_player->m_id = "PANEL_RECENT_PLAYER";
		recent_player->m_name = TRANSLATE(t_recent_player);

		panel_child recent_player_info;
		recent_player_info.m_parent = recent_player;
		recent_player_info.m_id = "PANEL_RECENT_PLAYER_INFO";
		recent_player_info.m_name = TRANSLATE(t_player_info);
		recent_player_info.m_column = 0;
		recent_player_info.m_index = 0;
		recent_player_info.m_render = true; // render this child by default
		recent_player_info.m_update = render_panel_recent_player;

		recent_player->m_children_panels.push_back(recent_player_info);

		m_panels.push_back(recent_player);
#pragma endregion

#pragma region Friend
		panel_parent* friend_ = new panel_parent();
		friend_->m_render = false;
		friend_->m_id = "PANEL_FRIEND";
		friend_->m_name = TRANSLATE(t_friend);

		panel_child recent_friend_info;
		recent_friend_info.m_parent = friend_;
		recent_friend_info.m_id = "PANEL_FRIEND_INFO";
		recent_friend_info.m_name = TRANSLATE(t_friend_info);
		recent_friend_info.m_column = 0;
		recent_friend_info.m_index = 0;
		recent_friend_info.m_render = true; // render this child by default
		recent_friend_info.m_update = render_panel_friend;

		friend_->m_children_panels.push_back(recent_friend_info);

		m_panels.push_back(friend_);
#pragma endregion

#pragma region Overseer
		panel_parent* overseer = new panel_parent();
		overseer->m_render = false;
		overseer->m_id = "PANEL_OVERSEER";
		overseer->m_name = TRANSLATE(t_overseer);

		panel_child overseer_info;
		overseer_info.m_parent = overseer;
		overseer_info.m_id = "PANEL_OVERSEER_INFO";
		overseer_info.m_name = TRANSLATE(t_overseer_info);
		overseer_info.m_column = 0;
		overseer_info.m_index = 0;
		overseer_info.m_render = true; // render this child by default
		overseer_info.m_update = render_panel_overseer;

		overseer->m_children_panels.push_back(overseer_info);

		m_panels.push_back(overseer);
#pragma endregion

#pragma region Vehicle Preview
		panel_parent* vehicle_preview = new panel_parent();
		vehicle_preview->m_render = false;
		vehicle_preview->m_id = "PANEL_VEHICLE_PREVIEW";
		vehicle_preview->m_name = TRANSLATE(t_vehicle_preview);

		panel_child vehicle_preview_info;
		vehicle_preview_info.m_parent = vehicle_preview;
		vehicle_preview_info.m_id = "PANEL_VEHICLE_PREVIEW_INFO";
		vehicle_preview_info.m_name = TRANSLATE(t_vehicle_preview_info);
		vehicle_preview_info.m_column = 0;
		vehicle_preview_info.m_index = 0;
		vehicle_preview_info.m_render = true; // render this child by default
		vehicle_preview_info.m_update = render_panel_vehicle_preview;

		vehicle_preview->m_children_panels.push_back(vehicle_preview_info);

		m_panels.push_back(vehicle_preview);
#pragma endregion

#pragma region Host Queue
		panel_parent* session = new panel_parent();
		session->m_render = false;
		session->m_id = "PANEL_SESSION";
		session->m_name = TRANSLATE(t_session);

		panel_child host_queue_info;
		host_queue_info.m_parent = session;
		host_queue_info.m_id = "PANEL_HOST_QUEUE_INFO";
		host_queue_info.m_name = TRANSLATE(t_host_queue_info);
		host_queue_info.m_column = 0;
		host_queue_info.m_index = 0;
		host_queue_info.m_render = true; // render this child by default
		host_queue_info.m_update = render_panel_host_queue;

		panel_child blacklist_info;
		blacklist_info.m_parent = session;
		blacklist_info.m_id = "PANEL_BLACKLIST_INFO";
		blacklist_info.m_name = TRANSLATE(t_blacklist_info);
		blacklist_info.m_column = 1;
		blacklist_info.m_index = 0;
		blacklist_info.m_render = true; // render this child by default
		blacklist_info.m_update = render_panel_blacklist;

		session->m_children_panels.push_back(host_queue_info);
		session->m_children_panels.push_back(blacklist_info);

		m_panels.push_back(session);
#pragma endregion

#pragma region Session Browser
		panel_parent* session_browser = new panel_parent();
		session_browser->m_render = false;
		session_browser->m_id = "PANEL_SESSION_BROWSER";
		session_browser->m_name = TRANSLATE(t_session_browser);

		panel_child session_browser_info;
		session_browser_info.m_parent = session_browser;
		session_browser_info.m_id = "PANEL_SESSION_BROWSER_INFO";
		session_browser_info.m_name = TRANSLATE(t_session_browser_info);
		session_browser_info.m_column = 0;
		session_browser_info.m_index = 0;
		session_browser_info.m_render = true; // render this child by default
		session_browser_info.m_update = render_panel_session_browser;

		session_browser->m_children_panels.push_back(session_browser_info);

		m_panels.push_back(session_browser);
#pragma endregion

#pragma region Player Search
		panel_parent* player_search = new panel_parent();
		player_search->m_render = false;
		player_search->m_id = "PANEL_PLAYER_SEARCH";
		player_search->m_name = TRANSLATE(t_player_search);

		panel_child player_search_info;
		player_search_info.m_parent = player_search;
		player_search_info.m_id = "PANEL_PLAYER_SEARCH_INFO";
		player_search_info.m_name = TRANSLATE(t_player_search_info);
		player_search_info.m_column = 0;
		player_search_info.m_index = 0;
		player_search_info.m_render = true; // render this child by default
		player_search_info.m_update = render_panel_player_search;

		player_search->m_children_panels.push_back(player_search_info);

		m_panels.push_back(player_search);
#pragma endregion

#pragma region Blacklisted players
		panel_parent* host_blacklist = new panel_parent();
		host_blacklist->m_render = false;
		host_blacklist->m_id = "PANEL_BLACKLISTED_PLAYERS";
		host_blacklist->m_name = TRANSLATE(t_blacklisted_players);

		panel_child host_blacklist_info;
		host_blacklist_info.m_parent = host_blacklist;
		host_blacklist_info.m_id = "PANEL_BLACKLISTED_PLAYERS_INFO";
		host_blacklist_info.m_name = TRANSLATE(t_blacklisted_players_info);
		host_blacklist_info.m_column = 0;
		host_blacklist_info.m_index = 0;
		host_blacklist_info.m_render = true; // render this child by default
		host_blacklist_info.m_update = render_panel_blacklisted_player;

		host_blacklist->m_children_panels.push_back(host_blacklist_info);

		m_panels.push_back(host_blacklist);
#pragma endregion

#pragma region Clock
		panel_parent* clock = new panel_parent();
		clock->m_render = false;
		clock->m_id = "PANEL_CLOCK";
		clock->m_name = TRANSLATE(t_clock);

		panel_child clock_info;
		clock_info.m_parent = clock;
		clock_info.m_id = "PANEL_CLOCK_INFO";
		clock_info.m_name = TRANSLATE(t_clock_info);
		clock_info.m_column = 0;
		clock_info.m_index = 0;
		clock_info.m_render = true; // render this child by default
		clock_info.m_update = render_panel_clock;

		clock->m_children_panels.push_back(clock_info);
		m_panels.push_back(clock);
#pragma endregion

#pragma region Outfit Preview
		panel_parent* outfit_preview = new panel_parent();
		outfit_preview->m_render = false;
		outfit_preview->m_id = "PANEL_OUTFIT";
		outfit_preview->m_name = TRANSLATE(t_outfit_preview);

		panel_child outfit_preview_info;
		outfit_preview_info.m_parent = outfit_preview;
		outfit_preview_info.m_id = "PANEL_OUTFIT_INFO";
		outfit_preview_info.m_name = TRANSLATE(t_outfit_preview_info);
		outfit_preview_info.m_column = 0;
		outfit_preview_info.m_index = 0;
		outfit_preview_info.m_render = true; // render this child by default
		outfit_preview_info.m_update = render_panel_outfit_preview;

		outfit_preview->m_children_panels.push_back(outfit_preview_info);
		m_panels.push_back(outfit_preview);
#pragma endregion
	}

	panel_manager* get_panel_manager() {
		static panel_manager Instance;
		return &Instance;
	}
}