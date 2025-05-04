#pragma once

#ifndef __INTERPRETER_TURTLE_H__
#define __INTERPRETER_TURTLE_H__

#include <vector>
#include <string>

#include "../interpreter/genbc.h"

namespace turtle {
	// Turtle interpreter class
	class TurtleInterpreter {
	public:
		TurtleInterpreter() = default;
		// ~TurtleI() = delete;
		TurtleInterpreter(const std::string& _File);

		void print_bytecode();

	private:
		std::vector<ByteCode> m_Bc;
	};
}

#endif // __INTERPRETER_TURTLE_H__