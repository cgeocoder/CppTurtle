#pragma once

#ifndef __CPLOTLIB_FUNCTION_H__
#define __CPLOTLIB_FUNCTION_H__

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

namespace cpl {

	// Function class for rendering on the cpl::Plot
	class Function {
	public:
		friend class Plot;
		friend class Window;

		Function();
		Function(const std::function<float(float)>& func);
		Function(const std::function<float(float)>& func, float width);
		Function(const std::function<float(float)>& func, const char* color);
		Function(const std::function<float(float)>& func, const char* color, float width);

		// Set new color.
		// 
		// If the color doesn't exist, it won't change.
		// @param color - new color
		void set_color(const char* color);

		// Set new width.
		// 
		// If the set_width <= 0, it won't change.
		// @param width - new width
		void set_width(float width);

		// Set function.
		// @param func - new function
		inline void set_function(const std::function<float(float)>& func) {
			m_Func = func;
		}

	private:
		float m_Width;
		sf::Color m_Color;
		std::function<float(float)> m_Func;
	};
}

#endif // 