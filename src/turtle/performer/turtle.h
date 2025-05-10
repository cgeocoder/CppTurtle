#pragma once

#ifndef __TURTLE_H__
#define __TURTLE_H__

#include <SFML/Graphics.hpp>
#include "vec.h"
#include "turtle_window.h"
#include <atomic>
#include <mutex>
#include <functional>
#include <cmath>

using trange = std::list<long long>;
using trangef = std::list<float>;

namespace turtle {
    enum class TurtleSpeed {
        // disable animation
        no_animation,
        fast,
        slow,
        normal
    };

    enum class TurtleColors {
        black,
        red,
        yellow,
        blue
    };

    // Range function
    // @param _Count - count of items in list
    // @return list in range [0 ... _Count - 1]
    trange range(long long _Count);

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @return list in range [_Start ... _End - 1]
    trange range(long long _Start, long long _End);

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @param _Step - step
    // @return list in range [_Start ... _End - 1] with step _Step
    trange range(long long _Start, long long _End, long long _Step);

    // Range function
    // @param _Start - first item in the list
    // @param _End - last item in the list
    // @param _Step - step
    // @return list<float> in range [_Start ... _End - 1] with step _Step
    trangef range(float _Start, float _End, float _Step);

    // Turtle sin function
    // @param _Ang - angle in degrees
    float tsin(float _Ang);

    // Turtle Cos function
    // @param _Ang - angle in degrees
    float tcos(float _Ang);

    // A general class for working with turtle graphics
    class Turtle {
    private:
        void set_coord_scalar(float _Ang);
        inline sf::Vector2f get_pos() { return this->from_real_to_map(this->m_Pos.load()); }

        void movement_animation(
            const sf::Vector2f& _LastPos,
            const sf::Vector2f& _NewPos
        );

        inline sf::Vector2f from_map_to_real(const float& x, const float& y) {
            return sf::Vector2f(this->m_HalfWindowWidth + x, this->m_HalfWindowHeight - y);
        }

        inline sf::Vector2f from_map_to_real(const sf::Vector2f& cood) {
            return sf::Vector2f(this->m_HalfWindowWidth + cood.x, this->m_HalfWindowHeight - cood.y);
        }

        inline sf::Vector2f from_real_to_map(const float& x, const float& y) {
            return sf::Vector2f(x - this->m_HalfWindowWidth, this->m_HalfWindowHeight - y);
        }  

        inline sf::Vector2f from_real_to_map(const sf::Vector2f& cood) {
            return sf::Vector2f(cood.x - this->m_HalfWindowWidth, this->m_HalfWindowHeight - cood.y);
        }

    public:
        // Creating Turtle
        Turtle();

        inline ~Turtle() {
            this->done();
        }

        // Forward movement
        void forward(const float& _Offset);

        // Backward movement
        void backward(const float& _Offset);

        // Turn right by [_Ang] degrees
        // @param _Ang - the value of the rotation in degrees
        void right(const float& _Ang);

        // Turn left by [_Ang] degrees
        // @param _Ang - the value of the rotation in degrees
        void left(const float& _Ang);

        void dot(float _Radius = 2.0f, TurtleColors _Color = TurtleColors::black);

        // Raise the Turtle tail
        inline void up() { this->m_TailDown = false; }

        // Lower the Turtle tail
        inline void down() { this->m_TailDown = true; }

        // Get current angle
        inline float get_ang() const { return this->m_Ang; }

        // Set Turtle position
        void set_pos(const float& x, const float& y);

        // Waits until the window closes
        inline void done() { m_Window->done(); }

        // 
        void set_speed(TurtleSpeed _NewSpeed);

        friend void make_plot(turtle::Turtle& t, std::function<float(float)> f, trangef x_range);

    private:
        // Turtle position in read coords
        std::atomic<sf::Vector2f> m_Pos;
        std::atomic<sf::Vector2u> m_WindowSize;
        std::atomic<float> m_Ang;

        // Points 
        std::mutex m_upMutex;
        std::list<sf::CircleShape> m_UserPoints;

        // Lines 
        std::mutex m_ulMutex;
        std::list<sf::RectangleShape> m_UserLines;

        float m_Sin, m_Cos;
        bool m_TailDown;
        unsigned int m_HalfWindowWidth, m_HalfWindowHeight;

        const float m_TurtleStep = 35.0f;

        float m_Speed;
        TurtleWindow* m_Window;
    };
}

#endif // __TURTLE_H__