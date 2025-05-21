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
#include "turtle_color.h"

namespace turtle {
    class Turtle;

    // Drawing plot by function
    // @param _Turtle - Turtle
    // @param _Function - ref to a function f(x) for drawing plot
    // @param _XRange - range of X ordinate
    void draw_function(
        turtle::Turtle& _Turtle,
        const trangef& _XRange,
        std::function<float(float)> _Function
    );
    
    // Drawing line
    // @param _Turtle - Turtle
    void draw_line(
        turtle::Turtle& _Turtle,
        const Vec2f& _Vec1,
        const Vec2f& _Vec2
    );

    // A general class for working with Turtle graphics
    class Turtle {
    private:
        void set_coord_scalar(float _Ang);
        inline sf::Vector2f get_pos() { return this->from_real_to_map(this->m_Pos.load()); }

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

        inline ~Turtle() {
            this->set_trace(true);
            this->done(); 
        }

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
        // @param _Color - dot color
        // @param _Radius - dot radius
        void dot(
            const char* _Color = "black",
            float _Radius = 2.0f
        );

        // Raise the Turtle tail
        inline void up() { this->m_TailDown = false; }

        // Lower the Turtle tail
        inline void down() { this->m_TailDown = true; }

        // Get Turtle angle
        inline float angle() const { return this->m_Ang; }

        // Set Turtle position
        void set_pos(const float& x, const float& y);
        inline void set_pos(const Vec2f& _Vec) { this->set_pos(_Vec.x, _Vec.y); }
        inline void set_pos(const Vec2i& _Vec) { this->set_pos((float)_Vec.x, (float)_Vec.y); }

        // Waits until the window closes
        inline void done() { this->m_Window->done(); }

        inline void set_line_width(const float& _NewWidth) {
            if (_NewWidth < 0.0f)
                throw(std::exception("set_line_width() failed: width must be >= 0.0f"));

            this->m_LineWidth = _NewWidth;
        }

        inline float get_line_width() {
            return this->m_LineWidth;
        }

        inline void set_trace(const bool& _Trace) {
            this->m_Trace.store(_Trace);
        }

        inline void set_screen_movable(const bool& _Move) {
            this->m_ScreenMove.store(_Move);
        }

        inline void set_background(const char* const _Color) {
            try {
                this->m_Background = ColorMap.at(_Color);
            }
            catch (std::exception ex) {
                std::cout << "Turtle: unknown color '" 
                    << _Color << "'\n";
            }
        }

        void set_color(const char* _Color);
        void set_color(
            const uint8_t& _R, 
            const uint8_t& _G, 
            const uint8_t& _B,
            const uint8_t& _A = 255);

        friend void draw_function(turtle::Turtle&, const trangef&, std::function<float(float)>);
        friend void draw_line(turtle::Turtle&, const Vec2f&, const Vec2f&);

    private:
        // Turtle position in read coords
        std::atomic<sf::Vector2f> m_Pos;
        std::atomic<sf::Vector2u> m_WindowSize;
        std::atomic<float> m_Ang;
        std::atomic<bool> m_Trace;
        std::atomic<bool> m_ScreenMove;
        std::atomic<sf::Color> m_Background;

        // Color
        sf::Color m_Color;

        // Points 
        std::mutex m_upMutex;
        std::list<sf::CircleShape> m_UserPoints;

        // Lines 
        std::mutex m_ulMutex;
        std::vector<sf::RectangleShape> m_UserLines;

        float m_LineWidth;
        float m_Sin, m_Cos;

        bool m_TailDown;
        unsigned int m_HalfWindowWidth, m_HalfWindowHeight;
        TurtleWindow* m_Window;
    };
}

#endif // __TURTLE_H__