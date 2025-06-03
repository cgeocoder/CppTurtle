#pragma once

#ifndef __CPLOTLIB_LINE_H__
#define __CPLOTLIB_LINE_H__

#include "../cpl_math.h"
#include "base_primitive.h"

#include <vector>
#include <SFML/Graphics/Shader.hpp>

namespace cpl {
	static constexpr const float DEFAULT_LINE_WIDTH = 0.1f;

	// Class of the Line primitive
	class Line : public PrimitiveBase {
	private:
		float m_Width;

	public:
		friend class Window;
		friend class Plot;

		// Line coordinates
		Vec2f a, b;

		Line();
		Line(Vec2f a, Vec2f b);
		Line(Vec2f a, Vec2f b, const char* color);
		Line(Vec2f a, Vec2f b, float width);
		Line(Vec2f a, Vec2f b, float width, const char* color);

		// Set new color.
		// 
		// If the color doesn't exist, it won't change.
		// @param color - new color
		virtual void set_color(const char* color) override;

		// Set new width.
		// 
		// If the set_width <= 0, it won't change.
		// 
		// Default width = 0.1f
		// @param width - new width
		void set_width(float width);

		// Get Line vector
		inline Vec2f vec() const {
			return Vec2f{ b.x - a.x, b.y - a.y };
		}

		// Get Line length
		inline float len() const {
			return vec().len(); 
		}

	private:
		Line(Vec2f a, Vec2f b, float width, sf::Color color);
	};
}

#endif // 