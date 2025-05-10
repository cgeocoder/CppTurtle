#include "turtle_math.h"

namespace turtle {
    trange range(const long long& _Count) {
        trange _rng;

        for (long long i = 0; i < _Count; ++i)
            _rng.push_back(i);

        return _rng;
    }

    trange range(const long long& _Start, const long long& _End) {
        trange _rng;

        for (long long i = _Start; i < _End; ++i)
            _rng.push_back(i);

        return _rng;
    }

    trange range(const long long& _Start, const long long& _End, const long long& _Step) {
        trange _rng;

        for (long long i = _Start; i < _End; i += _Step)
            _rng.push_back(i);

        return _rng;
    }

    trangef range(const float& _Start, const float& _End, const float& _Step) {
        trangef _rng;

        for (float i = _Start; i < _End; i += _Step)
            _rng.push_back(i);

        return _rng;
    }

    float tsin(const float& _Ang) {
        float rad_ang = (float)M_PI * _Ang / 180.0f;
        float abs_rad_ang = std::fabs(rad_ang);

        if (abs_rad_ang == 90.f) {
            return 1.0f * (rad_ang / 90.f);
        }
        else if (abs_rad_ang == 180.f) {
            return 0.0f;
        }
        else if (abs_rad_ang == 270.f) {
            return -1.0f * (rad_ang / 270.f);
        }
        else if (abs_rad_ang == 360.f) {
            return 0.0f;
        }
        else {
            return std::sin(rad_ang);
        }
    }

    float tcos(const float& _Ang) {
        float rad_ang = (float)M_PI * _Ang / 180.0f;
        float abs_rad_ang = std::fabs(rad_ang);

        if (abs_rad_ang == 90.f) {
            return 0.0f;
        }
        else if (abs_rad_ang == 180.f) {
            return -1.0f;
        }
        else if (abs_rad_ang == 270.f) {
            return 0.0f;
        }
        else if (abs_rad_ang == 360.f) {
            return 1.0f;
        }
        else {
            return std::cos(rad_ang);
        }
    }

}

// Turtle Vectors

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