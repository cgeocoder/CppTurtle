#include <iostream>

#include "turtle/turtle.h"
#include <corecrt_math_defines.h>

static void grid(turtle::Turtle& t, const float R) {
    t.set_line_width(0.05f);

    for (auto x : turtle::range(-R, R, 1.0f)) {
        draw_line(t, { x, -R }, { x, R });
        draw_line(t, { -R, x }, { R, x });
    }

    t.set_line_width(0.1f);
    draw_line(t, { -R, 0 }, { R, 0 });
    draw_line(t, { 0.0f, -R }, { 0.0f, R });
    t.set_line_width(0.125f);
}

int main(int argc, char* argv[]) {
    using namespace turtle;

    Turtle t;

    t.set_screen_movable(true);
    t.set_trace(false);

    grid(t, 2000.0f);

    trangef func_range = range(-100.0f, 100.0f, 0.05f);

    Polynomial3 p3(.1f, 1.0f, 1.0f, 1.0f);
    Polynomial2 p2 = p3.derivative();
    Polynomial1 p1 = p2.derivative();
    Polynomial0 p0 = p1.derivative();

    draw_function(t, func_range, p3);
    draw_function(t, func_range, p2);
    draw_function(t, func_range, p1);
    draw_function(t, func_range, p0);

    return 0;
}