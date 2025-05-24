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
        float rad_ang = (float)M_PI * std::fmod(_Ang, 360.0f) / 180.0f;
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
        float rad_ang = (float)M_PI * std::fmod(_Ang, 360.0f) / 180.0f;
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

namespace turtle {
    Polynomial0::Polynomial0(float a) : Polynomial(), a{ a } {}
    float Polynomial0::f(float x) const { return a; }
    float Polynomial0::derivative() const { return 0.0f; }

    Polynomial1::Polynomial1(float a, float b) : Polynomial(), a{ a }, b{ b } {}
    float Polynomial1::f(float x) const { return (a * x) + b; }
    Polynomial0 Polynomial1::derivative() const { return Polynomial0(a); }

    Polynomial2::Polynomial2(float a, float b, float c) : Polynomial(), a{ a }, b{ b }, c{ c } {}
    float Polynomial2::f(float x) const { return (a * x * x) + (b * x) + c; }
    Polynomial1 Polynomial2::derivative() const { return Polynomial1(2 * a, b); }

    Polynomial3::Polynomial3(float a, float b, float c, float d) : Polynomial(), a{ a }, b{ b }, c{ c }, d{ d } {}
    float Polynomial3::f(float x) const { return (a * x * x * x) + (b * x * x) + (c * x) + d; }
    Polynomial2 Polynomial3::derivative() const { return Polynomial2(3 * a, 2 * b, c); }
}