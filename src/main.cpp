#include <iostream>

#include "cpl/cpl.h"

static float func1(float x) {
    return 2.0f * x * x;
}

static float func1_2(float x) {
    return -0.2f * x * x - 1.0f;
}

int main(int argc, char* argv[]) {
    cpl::Window wnd;

    // Plot 1 - line

    cpl::Plot plot1{ 10.0f, 1.0f };
    plot1.set_title("Plot 1");

    cpl::Polyline pline;

    pline.add_point({ -10.0f, 0.0f });
    pline.add_point({ -8.0f, 7.0f });
    pline.add_point({ -6.0f, -9.0f });
    pline.add_point({ -4.0f, -8.0f });
    pline.add_point({ -2.0f, 0.0f });
    pline.add_point({ 0.0f, 12.0f });

    plot1.add_polyline(pline);
    
    wnd.add_plot(plot1);

    return 0;
}