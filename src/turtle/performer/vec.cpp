#include "vec.h"

#include <cmath>

namespace turtle {
    Vec2f::Vec2f() : x{ 0.0 }, y{ 0.0 } {}
    Vec2f::Vec2f(float x, float y) : x{ x }, y{ y } {}

    float Vec2f::len(Vec2f vec) const {
        float xs = vec.x - this->x;
        float ys = vec.y - this->y;

        return std::sqrt(xs * xs + ys * ys);
    }

    static float len(Vec2f vec1, Vec2f vec2) {
        float xs = vec2.x - vec1.x;
        float ys = vec2.y - vec1.y;

        return std::sqrt(xs * xs + ys * ys);
    }

    Vec2u::Vec2u() : x{ 0 }, y{ 0 } {}
    Vec2u::Vec2u(unsigned x, unsigned y) : x{ x }, y{ y } {}

    float Vec2u::len(Vec2u vec) const {
        unsigned xs = vec.x - this->x;
        unsigned ys = vec.y - this->y;

        return (float)std::sqrt(xs * xs + ys * ys);
    }

}