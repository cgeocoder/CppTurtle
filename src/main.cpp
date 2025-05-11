#include <iostream>

#include "turtle/turtle.h"

int main(int argc, char* argv[]) {
    turtle::Turtle t;
    t.set_speed(turtle::TurtleSpeed::no_animation);

    t.set_color("blue");

    make_plot(t, turtle::range(-400.0f, 400.0f, 1.0f), 
        [&](float x) -> float {
            return 100.0f * turtle::tsin(x);
        }
    );

    t.set_color("red");

    make_plot(t, turtle::range(-400.0f, 400.0f, 1.0f),
        [&](float x) -> float {
            return 100.0f * turtle::tcos(x);
        }
    );

    return 0;
}