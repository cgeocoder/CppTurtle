#define _USE_MATH_DEFINES
#define M_PIl 3.141592653589793238462643383279502884L /* pi */

#include <iostream>
#include <cmath>

#include "turtle/turtle_common.h"

const std::string path =
    "C:\\Users\\Гео\\source\\repos\\EGE6Interpreter\\EGE6Interpreter\\src\\turtle\\interpreter\\test.ege6i";

static void make_grid(turtle::Turtle& t, trangef x_range, trangef y_range) {
    t.up();

    for (auto& x : x_range) {
        for (auto& y : y_range) {
            t.set_pos(x, y);
            t.dot();
        }
    }

    t.down();
}

static void make_grid(turtle::Turtle& t, trangef _range) {
    t.up();

    for (auto& x : _range) {
        for (auto& y : _range) {
            t.set_pos(x, y);
            t.dot(0.5f);
        }
    }

    t.set_pos(0, 0);
    t.down();
}

int main(int argc, char* argv[]) {
    turtle::Turtle t;

    // make_grid(t, turtle::range(-100.f, 100.f, 10.f));

    // OY

    t.up();
    t.set_pos(0, -200);
    t.down();
    t.set_pos(0, 200);

    // OX

    t.up();
    t.set_pos(200, 0);
    t.down();
    t.set_pos(-200, 0);

    make_plot(t, [&](float x) -> float {
        return 100.f * turtle::tsin(x);
    }, 
    turtle::range(-400.0f, 400.0f, 0.8f));
    
    return 0;
}