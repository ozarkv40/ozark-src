#include "translation.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"
#include "translation/translation_selected.h"
#include "menu/base/util/notify.h"
#include "util/fiber_pool.h"
#include "util/dirs.h"
#include "util/log.h"
#include <fstream>

using namespace settings::translation::vars;

namespace settings::translation::vars {
	variables m_vars;

	void create_template_translation() {
		try {
			std::ofstream output(util::va::va("%sTemplate.json", util::dirs::get_path(translation)));
			if (output.good()) {
				nlohmann::json json;

				for (menu::submenu::submenu* submenu : menu::submenu::handler::get_submenus()) {
					if (submenu) {
						std::string submenu_name = submenu->get_name().get_original();
						for (std::shared_ptr<base_option> option : submenu->get_options()) {
							if (option->get_name().has_translation() && !option->get_name().get_original().empty()) {
								json["options"][option->get_name().get_original()] = option->get_name().get_original();
							}

							if (option->get_tooltip().has_translation() && !option->get_tooltip().get_original().empty()) {
								json["options"][option->get_tooltip().get_original()] = option->get_tooltip().get_original();
							}

							option->write_translation(json["options"]);
						}

						if (submenu->get_name().has_translation() && !submenu->get_name().get_original().empty()) {
							json["options"][submenu->get_name().get_original()] = submenu->get_name().get_original();
						}

						for (localization string : submenu->get_strings()) {
							if (string.has_translation() && !string.get_original().empty()) {
								json["options"][string.get_original()] = string.get_original();
							}
						}
					}

					for (localization* string : global::vars::g_localization_table) {
						json["global"][string->get_original()] = string->get_original();
					}
				}

				output << json.dump(4);
				output.close();
			}
		} catch (std::exception& e) {
			LOG_WARN("[json] %s", e.what());
		}

		// recache list to include template
		translation_menu::get()->update_once();
	}

	void reset() {
		for (menu::submenu::submenu* submenu : menu::submenu::handler::get_submenus()) {
			for (std::shared_ptr<base_option> option : submenu->get_options()) {
				if (option->get_name().has_translation()) option->get_name().reset();
				if (option->get_tooltip().has_translation()) option->get_tooltip().reset();
			}

			if (submenu->get_name().has_translation()) {
				submenu->get_name().reset();
			}

			for (auto& string : submenu->get_strings()) {
				if (string.has_translation()) string.reset();
			}
		}

		for (localization* string : global::vars::g_localization_table) {
			string->reset();
		}
	}

	void load_translation(std::string file) {
		try {
			std::ifstream input(util::va::va("%s%s.json", util::dirs::get_path(translation), file.c_str()));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				for (menu::submenu::submenu* submenu : menu::submenu::handler::get_submenus()) {
					std::string submenu_name = submenu->get_name().get_original();
					for (std::shared_ptr<base_option> option : submenu->get_options()) {
						if (option->get_name().has_translation() && !option->get_name().get_original().empty()) {
							option->get_name().set_mapped(JsonGet<std::string>(json["options"], option->get_name().get_original(), option->get_name().get_original()).c_str());
						}

						if (option->get_tooltip().has_translation() && !option->get_tooltip().get_original().empty()) {
							option->get_tooltip().set_mapped(JsonGet<std::string>(json["options"], option->get_tooltip().get_original(), option->get_tooltip().get_original()).c_str());
						}

						option->read_translation(json["options"]);
					}

					if (submenu->get_name().has_translation() && !submenu->get_name().get_original().empty()) {
						if (!json["options"][submenu_name].is_null()) {
							if (strcmp(json["options"][submenu_name].get<std::string>().c_str(), "Ozark")) {
								submenu->get_name().set_mapped(json["options"][submenu_name].get<std::string>().c_str());
							}
						}
					}

					for (localization& string : submenu->get_strings()) {
						if (string.has_translation() && !string.get_original().empty()) {
							string.set_mapped(JsonGet<std::string>(json["options"], string.get_original(), string.get_original()).c_str());
						}
					}
				}

				for (localization* string : global::vars::g_localization_table) {
					string->set_mapped(JsonGet<std::string>(json["global"], string->get_original(), string->get_original()).c_str());
				}
			} else {
				menu::notify::stacked(translation_menu::get()->get_string("Translation"), translation_menu::get()->get_string("Failed to open translation file!"), global::ui::g_error);
			}
		} catch (nlohmann::json::parse_error& error) {
			if (error.id == 101) {
				// encoding is wack
				menu::notify::stacked(translation_menu::get()->get_string("Translation"), translation_menu::get()->get_string("Failed to verify translation encoding. Ensure encoding is UTF-8!"), global::ui::g_error);
			} else {
				// failed
				menu::notify::stacked(translation_menu::get()->get_string("Translation"), util::va::va("%s: %i", translation_menu::get()->get_string("Failed to load translation").c_str(), error.id), global::ui::g_error);
			}
		} catch (std::exception& exception) {
			// error
			menu::notify::stacked(translation_menu::get()->get_string("Translation"), util::va::va("%s: %s", translation_menu::get()->get_string("Failed to load translation. exception").c_str(), exception.what()), global::ui::g_error);
		}
	}

	void update_existing_translation(std::string file) {
		try {
			std::ifstream input(util::va::va("%s%s.json", util::dirs::get_path(translation), file.c_str()));
			if (input.good()) {
				nlohmann::json json = nlohmann::json::parse(input);
				input.close();

				for (menu::submenu::submenu* submenu : menu::submenu::handler::get_submenus()) {
					std::string submenu_name = submenu->get_name().get_original();
					for (std::shared_ptr<base_option> option : submenu->get_options()) {
						if (option->get_name().has_translation() && !option->get_name().get_original().empty()) {
							if (json["options"][option->get_name().get_original()].is_null()) {
								json["options"][option->get_name().get_original()] = option->get_name().get_original();
							}
						}

						if (option->get_tooltip().has_translation() && !option->get_tooltip().get_original().empty()) {
							if (json["options"][option->get_tooltip().get_original()].is_null()) {
								json["options"][option->get_tooltip().get_original()] = option->get_tooltip().get_original();
							}
						}

						option->write_translation(json["options"]);
					}

					if (submenu->get_name().has_translation() && !submenu->get_name().get_original().empty()) {
						if (json["options"][submenu_name].is_null()) {
							json["options"][submenu_name] = submenu_name;
						}
					}

					for (localization& string : submenu->get_strings()) {
						if (string.has_translation() && !string.get_original().empty()) {
							if (json["options"][string.get_original()].is_null()) {
								json["options"][string.get_original()] = string.get_original();
							}
						}
					}
				}

				for (localization* string : global::vars::g_localization_table) {
					if (json["global"][string->get_original()].is_null()) {
						json["global"][string->get_original()] = string->get_original();
					}
				}

				std::ofstream output(util::va::va("%s%s.json", util::dirs::get_path(translation), file.c_str()));
				if (output.good()) {
					output << json.dump(4);
					output.close();
				}
			} else {
				menu::notify::stacked(translation_menu::get()->get_string("Translation"), translation_menu::get()->get_string("Failed to open translation file!"), global::ui::g_error);
			}
		} catch (nlohmann::json::parse_error& error) {
			if (error.id == 101) {
				// encoding is wack
				menu::notify::stacked(translation_menu::get()->get_string("Translation"), translation_menu::get()->get_string("Failed to verify translation encoding. Ensure encoding is UTF-8!"), global::ui::g_error);
			} else {
				// failed
				menu::notify::stacked(translation_menu::get()->get_string("Translation"), util::va::va("%s: %i", translation_menu::get()->get_string("Failed to load translation").c_str(), error.id), global::ui::g_error);
			}
		} catch (std::exception& exception) {
			// error
			menu::notify::stacked(translation_menu::get()->get_string("Translation"), util::va::va("%s: %s", translation_menu::get()->get_string("Failed to load translation. exception").c_str(), exception.what()), global::ui::g_error);
		}

		translation_menu::get()->update_once();
	}
}

void translation_menu::load() {
	set_name("Translation");
	set_parent<settings_menu>();

	add_option(button_option("Create Template")
		.add_translate()
		.add_click([] { util::fiber::pool::add(create_template_translation); }));

	add_option(scroll_option<int>(SCROLLSELECT, "Update Existing")
		.add_translate()
		.add_scroll(m_vars.m_update_translation, 0, NUMOF(m_vars.m_translation_list), m_vars.m_translation_list)
		.add_update([](scroll_option<int>* option, int position) { option->add_scroll(m_vars.m_update_translation, 0, m_vars.m_list_size, m_vars.m_translation_list); })
		.add_click([] { update_existing_translation(m_vars.m_translation_list[m_vars.m_update_translation].m_name.get_original()); })
		.add_requirement([] { return m_vars.m_list_size > 0; }));

	add_option(button_option("Reset to English")
		.add_translate().add_hotkey()
		.add_click([] { util::fiber::pool::add(reset); }));

	add_option(break_option("Translations")
		.add_translate());

	add_string("~m~None");
	add_string("Translation");
	add_string("Failed to open translation file");
	add_string("Failed to verify translation encoding. Ensure encoding is UTF-8");
	add_string("Failed to load translation");
	add_string("Failed to load translation. exception");

	translation_selected_menu::get();
}

void translation_menu::update() {}

void translation_menu::update_once() {
	clear_options(4);

	m_vars.m_cached_translations.clear();
	int size = 0;

	std::vector<std::string> translations = util::dirs::get_files_in_directory(util::dirs::get_path(translation), ".json");
	if (translations.size()) {
		for (std::string translation : translations) {
			m_vars.m_translation_list[size].m_name = translation;
			m_vars.m_translation_list[size].m_result = size++;

			std::pair<std::string, struct stat> Info;
			Info.first = translation;

			if (stat(util::va::va("%s%s.json", util::dirs::get_path(translation), translation.c_str()), &Info.second) == 0) {
				std::size_t index = m_vars.m_cached_translations.size();
				if (index < 0) index = 0;
				m_vars.m_cached_translations.push_back(Info);

				add_option(submenu_option(translation)
					.add_submenu<translation_selected_menu>()
					.add_click([=] { settings::translation::selected::vars::m_vars.m_selected = index; }));
			}
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}

	m_vars.m_list_size = size;
}

void translation_menu::feature_update() {}

translation_menu* g_instance;
translation_menu* translation_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new translation_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}