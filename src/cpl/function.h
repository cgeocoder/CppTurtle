#pragma once

#ifndef __CPLOTLIB_FUNCTION_H__
#define __CPLOTLIB_FUNCTION_H__

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

namespace cpl {
	class Function {
	public:
		friend class Plot;
		friend class Window;

		Function();
		Function(const std::function<float(float)>& func, float width = 0.1f);

		void set_color(const char* color);
		inline void set_width(float width) { m_Width = width; }
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