#include "rainbow.h"

namespace menu {
	rainbow::rainbow(int min, int max, int steps) {
		m_min = min;
		m_max = max;
		m_steps = steps;
	}

	void rainbow::add(color_rgba* color) {
		m_colors.push_back(color);
		m_default_colors.push_back({ color, *color });
	}

	void rainbow::remove(color_rgba* color) {
		auto vit = std::find(begin(m_colors), end(m_colors), color);
		if (vit != end(m_colors)) {
			*color = get_default(color);
			m_colors.erase(vit);

			auto vit2 = std::find_if(begin(m_default_colors), end(m_default_colors), [=] (std::pair<color_rgba*, color_rgba> elem) {
				return elem.first == color;
			});

			if (vit2 != end(m_default_colors)) {
				m_default_colors.erase(vit2);
			}
		}
	}

	void rainbow::run() {
		if (m_enabled) {
			int step = (m_max - m_min) / (m_steps == 0 ? 1 : m_steps);

			switch (m_increment) {
				case 0:
					m_color.g += step;
					if (m_color.g >= m_max) {
						m_color.g = m_max;
						m_increment++;
					}

					break;

				case 1:
					m_color.r -= step;
					if (m_color.r <= m_min) {
						m_color.r = m_min;
						m_increment++;
					}

					break;

				case 2:
					m_color.b += step;
					if (m_color.b >= m_max) {
						m_color.b = m_max;
						m_increment++;
					}

					break;

				case 3:
					m_color.g -= step;
					if (m_color.g <= m_min) {
						m_color.g = m_min;
						m_increment++;
					}

					break;

				case 4:
					m_color.r += step;
					if (m_color.r >= m_max) {
						m_color.r = m_max;
						m_increment++;
					}

					break;

				case 5:
					m_color.b -= step;
					if (m_color.b <= m_min) {
						m_color.b = m_min;
						m_increment = 0;
					}

					break;
			}

			m_color.a = 255;

			for (color_rgba* color : m_colors) {
				*color = m_color;
			}
		}
	}

	void rainbow::start() {
		m_enabled = true;
	}

	void rainbow::stop() {
		m_enabled = false;

		for (color_rgba* color : m_colors) {
			*color = get_default(color);
		}
	}

	void rainbow::toggle(bool toggle) {
		if (toggle) {
			start();
		} else stop();
	}

	color_rgba rainbow::get_default(color_rgba* color) {
		for (auto [ptr, col] : m_default_colors) {
			if (ptr == color) {
				return col;
			}
		}

		return {};
	}
}