#include "polyline.h"
#include "../colors.h"

#include <iostream>

namespace cpl {
	Polyline::Polyline() : m_Width{ 0.1f } {
		m_Color = sf::Color::Black;
	}

	Polyline::Polyline(const Vec2f& start_point) : m_Width{ 0.1f } {
		m_Color = sf::Color::Black;
		m_Points.push_back(start_point);
	}

	void Polyline::add_point(const Vec2f& coords) {
		m_Points.push_back(coords);
	}

	void Polyline::set_width(float width) {
		if (width > 0.0)
			m_Width = width;
	}

	void Polyline::set_color(const char* color) {
		try {
			m_Color = ColorMap.at(color);
		}
		catch (std::exception ex) {
			std::cout << "Polyline::set_color() failed: " << ex.what() << '\n';
		}
	}

}
