#pragma once

#ifndef __CPLOTLIB_BASE_PRIMITIVE_H__
#define __CPLOTLIB_BASE_PRIMITIVE_H__

#include <vector>
#include <SFML/Graphics/Shader.hpp>
#include "../cpl_math.h"

namespace cpl {
	class PrimitiveBase {
	protected:
		sf::Color m_Color;

	public:
		virtual void set_color(const char* color) = 0;
	};
}

#endif // !__CPLOTLIB_BASE_PRIMITIVE_H__