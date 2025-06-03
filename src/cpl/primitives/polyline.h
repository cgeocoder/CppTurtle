#pragma once

#ifndef __CPLOTLIB_POLYLINE_H__
#define __CPLOTLIB_POLYLINE_H__

#include "base_primitive.h"
#include <vector>
#include <SFML/Graphics/Shader.hpp>
#include "../cpl_math.h"

namespace cpl {

	// Class of the Polyline primitive
	class Polyline : public PrimitiveBase {
	private:
		float m_Width;
		std::vector<Vec2f> m_Points;

	public:
		friend class Window;
		friend class Plot;

		Polyline();
		Polyline(const Vec2f& start_point);

		// Add new point
		// @param coords - cpl::Vec2f point
		void add_point(const Vec2f& coords);

		// Set new color.
		// 
		// If the color doesn't exist, it won't change.
		// @param color - new color
		void set_color(const char* color) override;

		// Set new width.
		// 
		// If the set_width <= 0, it won't change.
		// 
		// Default width = 0.1f
		// @param width - new width
		void set_width(float width);

		inline Vec2f& operator[] (size_t index) {
			return m_Points.at(index);
		}
	};
}

#endif // !__CPLOTLIB_POLYLINE_H__