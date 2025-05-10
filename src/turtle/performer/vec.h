#pragma once

#ifndef __VEC2LD_H__
#define __VEC2LD_H__

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

#endif // !__VEC2LD_H__