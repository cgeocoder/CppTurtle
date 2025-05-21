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
   
}