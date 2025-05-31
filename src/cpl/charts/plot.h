#pragma once

#ifndef __CPLOTLIB_PLOT_H__
#define __CPLOTLIB_PLOT_H__

#include "chart_base.h"
#include "../function.h"
#include "../primitives/line.h"
#include "../primitives/point.h"

#include <vector>
#include "../primitives/polyline.h"

namespace cpl {
	static const sf::Vector2f DEFAULT_FONT_SCALE = { 0.025f, 0.025f };
	static const sf::Color DEFAULT_FONT_COLOR = sf::Color::Black;

	static constexpr const unsigned int DEFAULT_FONT_CHAR_SIZE = 20;
	static constexpr const sf::Text::Style DEFAULT_FONT_STYLE = sf::Text::Regular;

	// 
	class Plot : public ChartBase {
	private:
		// redraw all entities
		void redraw();

		// draw all Function entities
		void draw_static_function(const Function& f);

		/*
			Crop the line extending beyond the boundaries 
			of the square with a side of 2 m_Radius
		*/
		void check_line_boundaries(Line& line) const;

	public:
		friend class Window;

		Plot(float radius, float step);
		Plot(float radius, float step, const Vec2f& center);

		// Set new Plot radius
		void set_radius(float radius);

		// Set new Plot drawing step
		void set_step(float step);

		// Set new Plot center
		void set_center(float x, float y) override;
		// Set new Plot center
		void set_center(const Vec2f& xy) override;

		// Set drawing entities (Function, Point, Line) rendering quality
		// @param quality - from cpl::Quality
		void set_quality(float quality);

		// Add a static function to the Plot
		// @param func - cpl::Function object
		void add_function(const Function& func);

		// Add a static point to the Plot
		// @param point - cpl::Point object
		void add_point(const Point& point);

		// Add a static line to the Plot
		// @param line - cpl::Line object
		void add_line(Line& line);

		void add_polyline(const Polyline& polyline);
		
		// Set the title for the Plot
		void set_title(const std::string& title) override;

	private:
		float m_Radius, m_Step, m_FuncQuality;

		std::vector<Line> m_Lines;
		std::vector<Line> m_StaticLines;
		std::vector<Line> m_StaticFuncLines;
		std::vector<Point> m_StaticPoints;
		std::vector<Function> m_StaticFunctions;
	};
}

#endif // !__CPLOTLIB_PLOT_H__