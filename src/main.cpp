#include <iostream>

#include "turtle/turtle.h"


int main(int argc, char* argv[]) {
    turtle::Turtle t;
    t.set_speed(turtle::TurtleSpeed::no_animation);

    make_grid(t, turtle::range(-100.0f, 100.0f, 10.0f));

    for (int i = 0; i < 100; ++i) {
        t.forward(i);
        t.right(90);
    }

    return 0;
}