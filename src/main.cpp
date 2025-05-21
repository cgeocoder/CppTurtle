#include <iostream>

#include "turtle/turtle.h"
#include <corecrt_math_defines.h>

static void grid(turtle::Turtle& t) {
    t.set_line_width(0.05f);
    for (auto x : turtle::range(-100.0f, 100.0f, 1.0f)) {
        draw_line(t, { x, -100.0f }, { x, 100.0f });
    }

    for (auto y : turtle::range(-100.0f, 100.0f, 1.0f)) {
        draw_line(t, { -100.0f, y }, { 100.0f, y });
    }

    t.set_line_width(0.1f);
    draw_line(t, { -100.0f, 0 }, { 100.0f, 0 });
    draw_line(t, { 0.0f, -100.0f }, { 0.0f, 100.0f });
    t.set_line_width(0.125f);
}

int main(int argc, char* argv[]) {
    using namespace turtle;

    Turtle t;

    t.set_screen_movable(true);
    t.set_trace(false);

    grid(t);

    trangef func_range = range(-20.0f, 20.0f, 0.05f);

    t.set_color("red");
    
    // F(x) = x^3 + 2x^2 - x + 12
    draw_function(t, func_range,
        [&](float x) -> float {
            return x * x * x + 2 * x * x - x + 12;
        }
    );

    t.set_color("blue");

    // F`(x) = 3x^2 + 2x - 1
    draw_function(t, func_range,
        [&](float x) -> float {
            return 3 * x * x + 4 * x - 1;
        }
    );

    t.set_color("green");

    // F``(x) 6x + 2
    draw_function(t, func_range,
        [&](float x) -> float {
            return 6 * x + 2;
        }
    );

    return 0;
}