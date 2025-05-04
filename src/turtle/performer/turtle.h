#pragma once

#ifndef __TURTLE_H__
#define __TURTLE_H__

#include <SFML/Graphics.hpp>
#include "vec.h"
#include "turtle_window.h"
#include <atomic>

namespace turtle {
    enum TurtleSpeed {
        // disable any turtle movement
        no_animation,
        fast,
        slow,
        normal
    };

    // A general class for working with turtle graphics
    class Turtle {
    private:
        void set_coord_scalar(float _Ang);

    public:
        // Creating Turtle
        Turtle(bool grid_vosoble = false);

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

        // Raise the Turtle tail
        inline void up() { this->m_TailDown = false; }

        // Lower the Turtle tail
        inline void down() { this->m_TailDown = true; }

        // Get current angle
        inline float get_ang() const { return this->m_Ang; }

        // Get current Turtle position
        sf::Vector2f get_pos() const;

        // Set Turtle position
        void set_pos(const float& x, const float& y);

        // Waits until the window closes
        inline void done() { m_Window->done(); }

        void set_speed(TurtleSpeed new_speed);

    private:
        std::atomic<sf::Vector2f> m_Pos;
        std::atomic<sf::Vector2u> m_WindowSize;

        float m_Ang, m_Sin, m_Cos;
        bool m_TailDown;

        const float m_TurtleStep = 35.0f;

        float m_Speed;
        TurtleWindow* m_Window;
    };
}

#endif // __TURTLE_H__