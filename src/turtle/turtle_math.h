#pragma once

#ifndef __TURTLE_MATH_H__
#define __TURTLE_MATH_H__

#define _USE_MATH_DEFINES

#include <cmath>
#include <list>

using trange = std::list<long long>;
using trangef = std::list<float>;

namespace turtle {
    // Range function
    // @param _Count - count of items in list
    // @return list in range [0 ... _Count - 1]
    trange range(
        const long long& _Count
    );

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @return list in range [_Start ... _End - 1]
    trange range(
        const long long& _Start,
        const long long& _End
    );

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @param _Step - step
    // @return list in range [_Start ... _End - 1] with step _Step
    trange range(
        const long long& _Start,
        const long long& _End,
        const long long& _Step
    );

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @param _Step - step
    // @return list<float> in range [_Start ... _End - 1] with step _Step
    trangef range(
        const float& _Start,
        const float& _End,
        const float& _Step
    );

    // Turtle sin function
    // @param _Ang - angle in degrees
    float tsin(
        const float& _Ang
    );

    // Turtle Cos function
    // @param _Ang - angle in degrees
    float tcos(
        const float& _Ang
    );

}

// Turtle Vectors

namespace turtle {

    class Vec2f {
    public:
        Vec2f();
        Vec2f(float x, float y);

        float len(Vec2f vec) const;
        // static float len(Vec2ld vec1, Vec2ld vec2);

        float x, y;
    };

    class Vec2u {
    public:
        Vec2u();
        Vec2u(unsigned x, unsigned y);

        float len(Vec2u vec) const;

        unsigned x, y;
    };
}

#endif // !__TURTLE_MATH_H__