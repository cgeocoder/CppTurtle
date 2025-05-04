#define _USE_MATH_DEFINES 

#include "turtle.h"
#include <cmath>
#include <iostream>

namespace turtle {
    Turtle::Turtle(bool grid_vosoble) : m_Ang{ 90.0l }, m_TailDown{ true } {
        this->set_coord_scalar(this->m_Ang);
        
        m_Window = new TurtleWindow(
            this->m_Pos, 
            this->m_WindowSize,
            grid_vosoble
        );

        this->set_pos(0.0f, 0.0f);
        this->set_speed(TurtleSpeed::normal);
    }

    void Turtle::set_coord_scalar(float _Ang) {
        float rad_ang = (float)M_PI * _Ang / 180.0f;
        int rounded_ang = static_cast<int>(std::fabs(_Ang));

        if (rounded_ang % 360 == 0) {
            this->m_Sin = 0.0f;
            this->m_Cos = 1.0f;
        }
        else if (rounded_ang % 180 == 0) {
            this->m_Sin = 0.0f;
            this->m_Cos = -1.0f;
        }
        else {
            float _sin = std::sin(rad_ang);
            this->m_Sin = _sin;
            this->m_Cos = std::sqrt(1 - _sin * _sin);
        }
    }

    void Turtle::forward(const float& step) {
        sf::Vector2f last_pos = this->get_pos();
        sf::Vector2f new_pos = {
            last_pos.x + step * this->m_Cos,
            last_pos.y + step * this->m_Sin
        };

        float step_x = (new_pos.x - last_pos.x) / this->m_Speed;
        float step_y = (new_pos.y - last_pos.y) / this->m_Speed;

        std::thread([&]() {
            for (int i = 0; i < (int)this->m_Speed; ++i) {
                sf::Vector2f pos = this->get_pos();

                this->set_pos(
                    pos.x += step_x,
                    pos.y += step_y
                );

                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }

        }).join(); // waiting animation

        this->set_pos(
            new_pos.x,
            new_pos.y
        );
    }

    void Turtle::backward(const float& step) {
        this->forward(-step); 
    }

    void Turtle::right(const float& ang) {
        this->m_Ang = std::fmod(this->m_Ang - ang, 360);
        this->set_coord_scalar(this->m_Ang);
    }
    
    void Turtle::left(const float& ang) {
        this->m_Ang = std::fmod(this->m_Ang + ang, 360);
        this->set_coord_scalar(this->m_Ang);
    }

    sf::Vector2f Turtle::get_pos() const {
        sf::Vector2f current_pos = this->m_Pos.load();
        sf::Vector2u window_size = m_WindowSize.load();

        return sf::Vector2f(
            (current_pos.x - window_size.x / 2.0f) / this->m_TurtleStep,
            (window_size.y / 2.0f - current_pos.y) / this->m_TurtleStep
        );
    }

    void Turtle::set_pos(const float& x, const float& y) {
        sf::Vector2u window_size = m_WindowSize.load();

        this->m_Pos.store(sf::Vector2f(
            window_size.x / 2.0f + x * this->m_TurtleStep,
            window_size.y / 2.0f - y * this->m_TurtleStep
        ));
    }
    void Turtle::set_speed(TurtleSpeed new_speed) {

        // TurtleSpeed::no_animation or undef
        this->m_Speed = 1.0f;

        if (new_speed == TurtleSpeed::fast)
            this->m_Speed = 10.f;
        else if (new_speed == TurtleSpeed::normal)
            this->m_Speed = 100.f;
        else if (new_speed == TurtleSpeed::slow)
            this->m_Speed = 400.f;
    }
}