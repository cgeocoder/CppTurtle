#include "function.h"
#include "colors.h"

namespace cpl {
	Function::Function() : m_Width{ 0.1f }, m_Func{ nullptr }, m_Color{ sf::Color::Black }  {}
	Function::Function(const std::function<float(float)>& func) : m_Width{ 0.1f }, m_Func{ func }, m_Color{ sf::Color::Black } {}
	Function::Function(const std::function<float(float)>& func, float width) : m_Width{ width }, m_Func{ func }, m_Color{ sf::Color::Black } {}
	Function::Function(const std::function<float(float)>& func, const char* color) : m_Width{ 0.1f }, m_Func{ func } {
		set_color(color);
	}

	Function::Function(const std::function<float(float)>& func, const char* color, float width) : m_Width{ width }, m_Func{ func } {
		set_color(color);
	}

	void Function::set_width(float width) {
		if (width > 0)
			m_Width = width; 
	}

	void Function::set_color(const char* color) {
		try {
			m_Color = ColorMap.at(color);
		}
		catch (std::exception ex) {
			std::cout << "set_color() failed: " << ex.what() << '\n';
		}
	}
}