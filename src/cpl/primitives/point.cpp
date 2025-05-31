#include "point.h"
#include "../colors.h"
#include <iostream>

namespace cpl {
	Point::Point() : coords{ 0.0f, 0.0f }, m_Radius{ DEFAULT_POINT_RADIUS } { m_Color = sf::Color::Black; }
	Point::Point(Vec2f coords) : coords{ coords }, m_Radius{ DEFAULT_POINT_RADIUS } { m_Color = sf::Color::Black; }
	Point::Point(Vec2f coords, float radius) : coords{ coords }, m_Radius{ radius } { m_Color = sf::Color::Black; }

	Point::Point(Vec2f coords, const char* color) : coords{ coords }, m_Radius{ DEFAULT_POINT_RADIUS } {
		set_color(color);
	}

	Point::Point(Vec2f coords, float radius, const char* color) : coords{ coords }, m_Radius{ radius } {
		set_color(color);
	}

	Point::Point(Vec2f coords, float radius, sf::Color color) : coords{ coords }, m_Radius{ radius } { m_Color = color; }

	void Point::set_color(const char* color) {
		try {
			m_Color = ColorMap.at(color);
		}
		catch (std::exception ex) {
			std::cout << "Point::set_color() failed: " << ex.what() << '\n';
		}
	}

	void Point::set_radius(float radius) {
		if (radius < 0.0f) {
			std::cout << "Point::set_radius() failed: radius < 0\n";
			return;
		}

		m_Radius = radius;
	}
}

