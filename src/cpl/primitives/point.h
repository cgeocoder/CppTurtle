#pragma once

#ifndef __CPLOTLIB_POINT_H__
#define __CPLOTLIB_POINT_H__

#include "../cpl_math.h"
#include "base_primitive.h"

#include <vector>
#include <SFML/Graphics/Shader.hpp>

namespace cpl {
	static constexpr const float DEFAULT_POINT_RADIUS = 0.15f;

	// Class of the Point primitive
	class Point : public PrimitiveBase {
	private:
		float m_Radius;

	public:
		friend class Window;
		friend class Plot;

		// Point coordinates
		Vec2f coords;

		Point();
		Point(Vec2f coords);
		Point(Vec2f coords, const char* color);
		Point(Vec2f coords, float radius);
		Point(Vec2f coords, float radius, const char* color);

		// Set new color.
		// 
		// If the color doesn't exist, it won't change.
		// @param color - new color
		void set_color(const char* color) override;

		// Set new radius.
		// 
		// If the set_width <= 0, it won't change.
		// 
		// Default radius = 0.15f
		// @param radius - new radius
		void set_radius(float radius);

	private:
		Point(Vec2f coords, float radius, sf::Color color);
	};
}

#endif // !__CPLOTLIB_POINT_H__