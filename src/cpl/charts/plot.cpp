#define _CRT_SECURE_NO_WARNINGS

#include "Plot.h"
#include "../cpl_math.h"
#include "../function.h"
#include "../paths.h"
#include "../primitives/line.h"
#include "../primitives/point.h"

#include <corecrt_math_defines.h>

namespace cpl {
	const float Quality::Low = 1.0f;
	const float Quality::Medium = 0.1f;
	const float Quality::High = 0.05f;
	const float Quality::UltraHigh = 0.01f;

	Plot::Plot(float radius, float step) : 
		m_Radius{ radius }, m_Step{ step }, 
		m_FuncQuality{ cpl::Quality::Medium } {

		m_Center = { 0.0f, 0.0f };
		m_Title = { nullptr };

		m_Font = new sf::Font;

		if (!m_Font->loadFromFile(DEFAULT_FONT)) {
			std::cout << "Plot::Plot(): sf::Font::loadFromFile() failed\n";
			return;
		}

		m_Font->setSmooth(true);
	}

	Plot::Plot(float radius, float step, const Vec2f& center) : 
		m_Radius{ radius }, m_Step{ step },
		m_FuncQuality{ cpl::Quality::Medium } {

		m_Center = center;
		m_Title = { nullptr };
		m_Font = new sf::Font;

		if (!m_Font->loadFromFile(DEFAULT_FONT)) {
			std::cout << "Plot::Plot(): sf::Font::loadFromFile() failed\n";
			return;
		}

		m_Font->setSmooth(true);
	}

	void Plot::draw_static_function(const Function& f) {
		rangef_t rng = range(-m_Radius, m_Radius + m_FuncQuality, m_FuncQuality);
		Vec2f last_point = { *rng.begin() + m_Center.x, f.m_Func(*rng.begin()) + m_Center.y };

		for (float x : rng) {
			Vec2f new_point = { x + m_Center.x, f.m_Func(x) + m_Center.y };

			Line ln = { last_point, new_point, f.m_Width, f.m_Color };
			check_line_boundaries(ln);
			m_StaticFuncLines.push_back(make_line(ln));

			last_point = new_point;
		}
	}
	
	void Plot::add_function(const Function& f) {
		// draw_static_function(f);
		m_StaticFunctions.push_back(f);
	}

	void Plot::set_radius(float radius) { 
		m_Radius = radius; 
	}

	void Plot::set_step(float step) {
		m_Step = step;
	}

	void Plot::set_center(const Vec2f& xy) {
		m_Center = xy;
	}

	void Plot::set_center(float x, float y) {
		m_Center = Vec2f{ x, y };
	}

	void Plot::set_quality(float quality) {
		m_FuncQuality = quality;
	}

	void Plot::draw() {
		// Draw plot lines

		for (float i : cpl::range(-m_Radius, m_Radius + m_Step, m_Step)) {
			m_PlotLines.push_back(make_line(
				{ { i + m_Center.x, -m_Radius + m_Center.y }, { i + m_Center.x, m_Radius + m_Center.y }, 0.05f }
			));
			m_PlotLines.push_back(make_line(
				{ { -m_Radius + m_Center.x, i + m_Center.y }, { m_Radius + m_Center.x, i + m_Center.y }, 0.05f }
			));
		}

		m_PlotLines.push_back(make_line(
			{ { -m_Radius + m_Center.x, m_Center.y }, { m_Radius + m_Center.x, m_Center.y }, 0.1f }
		));
		m_PlotLines.push_back(make_line(
			{ { m_Center.x, -m_Radius + m_Center.y }, { m_Center.x, m_Radius + m_Center.y }, 0.1f }
		));

		// Draw function lines

		for (Function& f : m_StaticFunctions) {
			draw_static_function(f);
		}

		// Draw lines

		for (Line& line : m_Lines) {
			check_line_boundaries(line);
			m_StaticLines.push_back(make_line(line));
		}

		// Draw points

		for (Point& point : m_Points) {
			if ((point.coords.x > -m_Radius) && (point.coords.x < m_Radius)
				&& (point.coords.y > -m_Radius) && (point.coords.y < m_Radius)) {

				m_StaticPoints.push_back(make_point({
					{ point.coords.x + m_Center.x, point.coords.y + m_Center.y }, 
					point.m_Radius, point.m_Color
				}));
			}
		}
	}

	void Plot::add_point(const Point& point) {
		m_Points.push_back(point);
	}

	void Plot::check_line_boundaries(Line& line) const {
		Vec2f line_vec = line.vec();

		// y = k1 * x + k2
		float k1 = line_vec.y / line_vec.x;
		float k2 = line.a.y - k1 * line.a.x;

		// Check B vector

		float max_r_x = m_Radius + m_Center.x;
		float max_r_y = m_Radius + m_Center.y;
		float min_r_x = -m_Radius + m_Center.x;
		float min_r_y = -m_Radius + m_Center.y;

		Vec2f vec_b = { (line.b.x), (line.b.y) };

		if (vec_b.y > max_r_y) {
			vec_b.y = max_r_y;
			vec_b.x = (max_r_y - k2) / k1;
		}
		else if (vec_b.y < min_r_y) {
			vec_b.y = min_r_y;
			vec_b.x = (min_r_y - k2) / k1;
		}

		if (vec_b.x > max_r_x) {
			vec_b.x = max_r_x;
			vec_b.y = k1 * max_r_x + k2;
		}
		else if (vec_b.x < min_r_x) {
			vec_b.x = min_r_x;
			vec_b.y = k1 * min_r_x + k2;
		}

		// Check A vector

		Vec2f vec_a = { (line.a.x), (line.a.y) };

		if (vec_a.y > max_r_y) {
			vec_a.y = max_r_y;
			vec_a.x = (max_r_y - k2) / k1;
		}
		else if (vec_a.y < min_r_y) {
			vec_a.y = min_r_y;
			vec_a.x = (min_r_y - k2) / k1;
		}

		if (vec_a.x > max_r_x) {
			vec_a.x = max_r_x;
			vec_a.y = k1 * max_r_x + k2;
		}
		else if (vec_a.x < min_r_x) {
			vec_a.x = min_r_x;
			vec_a.y = k1 * min_r_x + k2;
		}

		line.a = vec_a;
		line.b = vec_b;
	}

	void Plot::add_line(const Line& line) {
		m_Lines.push_back(line);
	}

	void Plot::add_polyline(const Polyline& polyline) {
		if (!polyline.m_Points.empty()) {
			Vec2f last_coord = polyline.m_Points.at(0);
			last_coord = { last_coord.x + m_Center.x, last_coord.y + m_Center.y };

			for (size_t i = 1; i < polyline.m_Points.size(); ++i) {
				Vec2f new_coord = polyline.m_Points.at(i);
				new_coord = { new_coord.x + m_Center.x, new_coord.y + m_Center.y };

				Line line{ last_coord, new_coord, polyline.m_Width, polyline.m_Color };
				m_Lines.push_back(line);

				last_coord = new_coord;
			}
		}
	}

	void Plot::set_title(const std::string& title) {
		if (m_Title == nullptr) {
			m_Title = new sf::Text;
			m_Title->setFont(*m_Font);
			m_Title->setStyle(DEFAULT_FONT_STYLE);
			m_Title->setScale(DEFAULT_FONT_SCALE);
			m_Title->setFillColor(sf::Color::Black);
			m_Title->setCharacterSize(50);
		}

		m_Title->setString(title);
		sf::FloatRect title_rect = m_Title->getLocalBounds();
		m_Title->setOrigin(title_rect.width / 2.0f, title_rect.height / 2.0f);
		m_Title->setPosition({ m_Center.x, m_Radius + m_Center.y + 1.5f * m_Step });
	}

	sf::RectangleShape Plot::make_line(const Line& ln) {
		Vec2f last_pos_point = ln.a;
		Vec2f new_pos_point = ln.b;
		Vec2f vec{ new_pos_point.x - last_pos_point.x, new_pos_point.y - last_pos_point.y };

		float vec_len = sqrt(vec.x * vec.x + vec.y * vec.y);

		float cos_a = vec.x / vec_len;
		float alpha = std::copysignf(acos(cos_a), vec.y);
		float ang_degrees = (180.f / (float)M_PI) * alpha;

		sf::RectangleShape line(sf::Vector2f(vec_len, ln.m_Width));
		line.setFillColor(sf::Color::Black);
		line.setOrigin(sf::Vector2f(0.0f, ln.m_Width / 2.0f));
		line.setRotation(-ang_degrees);
		line.setFillColor(ln.m_Color);

		// store coordinates in CURRENT PLOT system
		line.setPosition(last_pos_point.x, last_pos_point.y);

		return line;
	}

	sf::CircleShape Plot::make_point(const Point& pt) {
		sf::CircleShape point{ pt.m_Radius, 50 };
		point.setOrigin({ pt.m_Radius, pt.m_Radius });
		point.setFillColor(pt.m_Color);
		
		// store coordinates in CURRENT PLOT system
		point.setPosition(pt.coords.x, pt.coords.y);

		return point;
	}
}