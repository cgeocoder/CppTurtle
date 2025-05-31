#pragma once

#ifndef __CPLOTLIB_PLOT_BASE_H__
#define __CPLOTLIB_PLOT_BASE_H__

#define _CRT_SECURE_NO_WARNINGS

#include "../function.h"
#include "../primitives/line.h"
#include "../primitives/point.h"
#include <vector>

namespace cpl {
	// The quality of entity rendering
	class Quality {
	public:
		static const float Low;
		static const float Medium;
		static const float High;
		static const float UltraHigh;
	};

	// The basic class of Plot
	class ChartBase {
	protected:
		Vec2f m_Center;
		sf::Text* m_Title;
		sf::Font* m_Font;

	public:
		virtual void set_title(const std::string&) = 0;
		virtual void set_center(float, float) = 0;
		virtual void set_center(const Vec2f&) = 0;
	};
}

#endif // !__CPLOTLIB_PLOT_BASE_H__