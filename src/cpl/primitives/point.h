#pragma once

#ifndef __CPLOTLIB_POINT_H__
#define __CPLOTLIB_POINT_H__

#include "base_primitive.h"
#include "../cpl_math.h"
#include <vector>
#include <SFML/Graphics/Shader.hpp>

namespace cpl {
	static constexpr const float DEFAULT_POINT_RADIUS = 0.15f;

	class Point : public PrimitiveBase {
	private:
		float m_Radius;

	public:
		friend class Window;
		friend class Plot;

		Vec2f coords;

		Point();
		Point(Vec2f coords);
		Point(Vec2f coords, const char* color);
		Point(Vec2f coords, float radius);
		Point(Vec2f coords, float radius, const char* color);

		void set_color(const char* color) override;
		void set_radius(float radius);

	private:
		Point(Vec2f coords, float radius, sf::Color color);
	};
}

#endif // !__CPLOTLIB_POINT_H__