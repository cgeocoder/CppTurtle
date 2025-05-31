#pragma once

#ifndef __CPLOTLIB_POLYLINE_H__
#define __CPLOTLIB_POLYLINE_H__

#include "base_primitive.h"
#include <vector>
#include <SFML/Graphics/Shader.hpp>
#include "../cpl_math.h"

namespace cpl {
	class Polyline : public PrimitiveBase {
	private:
		float m_Width;
		std::vector<Vec2f> m_Points;

	public:
		friend class Window;
		friend class Plot;

		Polyline();
		Polyline(const Vec2f& start_point);

		void add_point(const Vec2f& coords);
		void set_color(const char* color) override;

		inline Vec2f& operator[] (size_t index) {
			return m_Points.at(index);
		}
	};
}

#endif // !__CPLOTLIB_POLYLINE_H__