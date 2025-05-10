#pragma once

#ifndef __TURTLE_H__
#define __TURTLE_H__

#include <SFML/Graphics.hpp>

#include <functional>
#include <atomic>
#include <cmath>
#include <mutex>

#include "turtle_math.h"
#include "turtle_window.h"

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

    // A general class for working with Turtle graphics
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
        // Turtle default constructor
        Turtle();

        inline ~Turtle() { this->done(); }

        // Forward movement
        // @param _Offset - moving forward by [_Offset] units
        void forward(
            const float& _Offset
        );

        // Backward movement
        // @param _Offset - moving backward by [_Offset] units
        void backward(
            const float& _Offset
        );

        // Turn right by [_Ang] degrees
        // @param _Ang - the value of the rotation in degrees
        void right(
            const float& _Ang
        );

        // Turn left by [_Ang] degrees
        // @param _Ang - the value of the rotation in degrees
        void left(
            const float& _Ang
        );

        // Draw point
        // @param _Radius - dot radius
        // @param _Color - dot color
        void dot(
            float _Radius = 2.0f, 
            TurtleColors _Color = TurtleColors::black
        );

        // Raise the Turtle tail
        inline void up() { this->m_TailDown = false; }

        // Lower the Turtle tail
        inline void down() { this->m_TailDown = true; }

        // Get Turtle angle
        inline float get_angle() const { return this->m_Ang; }

        // Set Turtle position
        void set_pos(const float& x, const float& y);

        // Waits until the window closes
        inline void done() { m_Window->done(); }

        // Set Turtle speed
        // Default speed is turtle::TurtleSpeed::normal
        // @param _NewSpeed - val from turtle::TurtleSpeed
        void set_speed(
            TurtleSpeed _NewSpeed
        );

        // Drawing plot by function
        // @param _Turtle - Turtle
        // @param _Function - ref to a function f(x) for drawing plot
        // @param _XRange - range of X ordinate
        friend void make_plot(
            turtle::Turtle& _Turtle, 
            std::function<float(float)> _Function, 
            trangef _XRange
        );

        // Drawing grid
        // @param _Turtle - Turtle
        // @param _XRange - range of X ordinate
        // @param _YRange - range of Y ordinate
        // @param _PointRadius - point of radius
        friend void make_grid(
            turtle::Turtle& _Turtle,
            trangef _XRange,
            trangef _YRange,
            float _PointRadius
        );

        // Drawing grid
        // @param _Turtle - Turtle
        // @param _XRange - range of X and Y ordinates
        // @param _PointRadius - point of radius
        friend void make_grid(
            turtle::Turtle& _Turtle,
            trangef _Range,
            float _PointRadius
        );

        // Drawing grid
        // @param _Turtle - Turtle
        // @param _XRange - range of X and Y ordinates
        friend void make_grid(
            turtle::Turtle& _Turtle,
            trangef _Range
        );

        // Drawing line
        // @param _Turtle - Turtle
        // @param _X1 - X of start point
        // @param _Y1 - Y of start point
        // @param _X2 - X of end point
        // @param _Y2 - Y of end point
        friend void make_line(
            turtle::Turtle& _Turtle,
            const float& _X1,
            const float& _Y1,
            const float& _X2,
            const float& _Y2
        );

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

        float m_Speed;
        TurtleWindow* m_Window;
    };
}

#endif // __TURTLE_H__