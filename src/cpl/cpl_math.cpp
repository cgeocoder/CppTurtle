#include "cpl_math.h"

namespace cpl {
    range_t range(const long long& _Count) {
        range_t _rng;

        for (long long i = 0; i < _Count; ++i)
            _rng.push_back(i);

        return _rng;
    }

    range_t range(const long long& _Start, const long long& _End) {
        range_t _rng;

        for (long long i = _Start; i < _End; ++i)
            _rng.push_back(i);

        return _rng;
    }

    range_t range(const long long& _Start, const long long& _End, const long long& _Step) {
        range_t _rng;

        for (long long i = _Start; i < _End; i += _Step)
            _rng.push_back(i);

        return _rng;
    }

    rangef_t range(const float& _Start, const float& _End, const float& _Step) {
        rangef_t _rng;

        for (float i = _Start; i < _End; i += _Step)
            _rng.push_back(i);

        return _rng;
    }

    float sin(const float& _Ang) {
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

    float cos(const float& _Ang) {
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