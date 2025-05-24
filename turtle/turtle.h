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
    // @param turtle - Turtle
    // @param xrange - range of X ordinate
    // @param function - ref to a function f(x) for drawing plot
    void draw_function(
        turtle::Turtle& turtle,
        const trangef& xrange,
        const std::function<float(float)> function
    );

    // Drawing plot by Polynomial function
    // @param turtle - Turtle
    // @param xrange - range of X ordinate
    // @param polynomial - x degree polynomial
    void draw_function(
        turtle::Turtle& turtle,
        const trangef& xrange,
        const Polynomial& polynomial
    );
    
    // Drawing line
    // @param turtle - Turtle
    // @param vec1 - begin point
    // @param vec2 - end point
    void draw_line(
        turtle::Turtle& turtle,
        const Vec2f& vec1,
        const Vec2f& vec2
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
        // @param offset - moving forward by [offset] units
        void forward(
            const float& offset
        );

        // Backward movement
        // @param offset - moving backward by [offset] units
        void backward(
            const float& offset
        );

        // Turn right by [angle] degrees
        // @param angle - the value of the rotation in degrees
        void right(
            const float& angle
        );

        // Turn left by [angle] degrees
        // @param angle - the value of the rotation in degrees
        void left(
            const float& angle
        );

        // Draw point
        // @param color - dot color
        // @param radius - dot radius
        void dot(
            const char* color = "black",
            float radius = 2.0f
        );

        // Set Turtle position
        // @param x - x ordinate
        // @param y - y ordinate
        void set_pos(
            const float& x, 
            const float& y
        );

        // Set Turtle position
        inline void set_pos(const Vec2f& vec) { this->set_pos(vec.x, vec.y); }
        // Set Turtle position
        inline void set_pos(const Vec2i& vec) { this->set_pos((float)vec.x, (float)vec.y); }

        // Raise the Turtle tail
        inline void up() { this->m_TailDown = false; }

        // Lower the Turtle tail
        inline void down() { this->m_TailDown = true; }

        // Get Turtle angle in [0; 360]
        inline float angle() const { return this->m_Ang; }

        // Waits until the window closes
        inline void done() { this->m_Window->done(); }

        inline void set_line_width(const float& new_width) {
            if (new_width < 0.0f)
                throw(std::exception("set_line_width() failed: width must be >= 0.0f"));

            this->m_LineWidth = new_width;
        }

        inline float get_line_width() const {
            return this->m_LineWidth;
        }

        inline void set_trace(const bool& trace) {
            this->m_Trace.store(trace);
        }

        inline void set_screen_movable(const bool& movable) {
            this->m_ScreenMove.store(movable);
        }

        inline void set_background(const char* const color) {
            try {
                this->m_Background = ColorMap.at(color);
            }
            catch (std::exception ex) {
                std::cout << "Turtle: unknown color '" 
                    << color << "'\n";
            }
        }

        void set_color(const char* color);
        void set_color(
            const uint8_t& r, 
            const uint8_t& g, 
            const uint8_t& b,
            const uint8_t& a = 255);

        friend void draw_function(turtle::Turtle&,const trangef&, const Polynomial&);
        friend void draw_function(turtle::Turtle&, const trangef&, const std::function<float(float)>);
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