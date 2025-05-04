#define _USE_MATH_DEFINES
#define M_PIl 3.141592653589793238462643383279502884L /* pi */

#include <iostream>
#include <cmath>

#include "turtle/turtle_common.h"

const std::string path =
    "C:\\Users\\Гео\\source\\repos\\EGE6Interpreter\\EGE6Interpreter\\src\\turtle\\interpreter\\test.ege6i";

auto printc(const turtle::Turtle& t) {
    auto pos = t.get_pos();
    std::cout << "Turtle (" << pos.x << ", " << pos.y << ") " << t.get_ang() << "\n";
}

int main(int argc, char* argv[]) {
    turtle::Turtle t = { true };

    t.set_speed(turtle::slow);

    while (1) {
        t.forward(5);
        t.right(90);
    }
    
    return 0;
}