#pragma once

#ifndef __TURTLE_MATH_H__
#define __TURTLE_MATH_H__

#define _USE_MATH_DEFINES

#include <cmath>
#include <list>
#include <stdarg.h>

// cpl range <long long>
using range_t = std::list<long long>;

// cpl range <float>
using rangef_t = std::list<float>;


namespace cpl {

    // Range function
    // @param _Count - count of items in list
    // @return list in range [0 ... _Count - 1]
    range_t range(
        const long long& _Count
    );

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @return list in range [_Start ... _End - 1]
    range_t range(
        const long long& _Start,
        const long long& _End
    );

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @param _Step - step
    // @return list in range [_Start ... _End - 1] with step _Step
    range_t range(
        const long long& _Start,
        const long long& _End,
        const long long& _Step
    );

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @param _Step - step
    // @return list<float> in range [_Start ... _End - 1] with step _Step
    rangef_t range(
        const float& _Start,
        const float& _End,
        const float& _Step
    );

    // cpl sin function
    // @param _Ang - angle in degrees
    float sin(
        const float& _Ang
    );

    // cpl Cos function
    // @param _Ang - angle in degrees
    float cos(
        const float& _Ang
    );

}

// cpl Vectors

namespace cpl {

    template<typename T>
    class Vec2 {
    public:
        inline Vec2() : x{ (T)0 }, y{ (T)0 } {}
        inline Vec2(const T& x, const T& y) : x{ x }, y{ y } {}

        template<typename U>
        inline auto operator+(const Vec2<U>& _Right) const {
            return Vec2<decltype(x + _Right.x)>(
                this->x + _Right.x,
                this->y + _Right.y
            );
        }

        template<typename U>
        inline auto operator-(const Vec2<U>& _Right) const  {
            return Vec2<decltype(x - _Right.x)>(
                this->x - _Right.x,
                this->y - _Right.y
            );
        }

        template<typename U>
        inline auto operator*(const U& _Scalar) const {
            return Vec2<decltype(x * _Scalar)>(
                this->x * _Scalar,
                this->y * _Scalar
            );
        }

        template<typename U>
        inline auto operator*(const Vec2<U>& _Right) const  {
            return this->x * _Right.x + this->y * _Right.y;
        }

        inline auto len() const {
            return std::sqrt(x * x + y * y);
        }

        T x, y;
    };

    using Vec2f = Vec2<float>;
    using Vec2d = Vec2<double>;
    using Vec2ld = Vec2<long double>;
    using Vec2i = Vec2<int>;
    using Vec2ui = Vec2<unsigned int>;
    using Vec2l = Vec2<long>;
    using Vec2ul = Vec2<unsigned long>;
    using Vec2ll = Vec2<long long>;
    using Vec2ull = Vec2<unsigned long long>;
    using Vec2c = Vec2<char>;
    using Vec2uc = Vec2<unsigned char>;

    template<typename T, typename U>
    static inline double angle(const Vec2<T>& _Vec1, const Vec2<U>& _Vec2) {
        return std::acos(
            (_Vec1 * _Vec2) / (_Vec1.len() * _Vec2.len())
        );
    }
}

#endif // !__TURTLE_MATH_H__