#define _USE_MATH_DEFINES 

#include "turtle.h"
#include <cmath>
#include <iostream>

namespace turtle {

    Turtle::Turtle() : m_Ang{ 90.0l } {
        this->set_coord_scalar(this->m_Ang.load());
        this->up();
        
        m_Window = new TurtleWindow(
            this->m_Pos, 
            this->m_WindowSize,
            this->m_Ang,
            this->m_upMutex,
            this->m_UserPoints,
            this->m_ulMutex,
            this->m_UserLines
        );

        sf::Vector2u window_size = this->m_WindowSize.load();

        this->m_HalfWindowWidth = static_cast<unsigned int>(window_size.x / 2.0f);
        this->m_HalfWindowHeight = static_cast<unsigned int>(window_size.y / 2.0f);

        this->set_pos(0.0f, 0.0f);
        this->set_speed(TurtleSpeed::normal);

        this->down();
    }

    void Turtle::set_coord_scalar(float _Ang) {
        this->m_Sin = tsin(_Ang);
        this->m_Cos = tcos(_Ang);
    }

    void Turtle::movement_animation(const sf::Vector2f& _LastPos, const sf::Vector2f& _NewPos) {
        float step_x = (_NewPos.x - _LastPos.x) / this->m_Speed;
        float step_y = (_NewPos.y - _LastPos.y) / this->m_Speed;

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
            _NewPos.x,
            _NewPos.y
        );
    }

    void Turtle::forward(const float& step) {
        sf::Vector2f last_pos = this->get_pos();
        sf::Vector2f new_pos = {
            last_pos.x + step * this->m_Cos,
            last_pos.y + step * this->m_Sin
        };

        this->movement_animation(last_pos, new_pos);
    }

    void Turtle::backward(const float& step) {
        this->forward(-step); 
    }

    void Turtle::right(const float& ang) {
        this->m_Ang.store((float) std::fmod(this->m_Ang.load() - ang, 360));
        this->set_coord_scalar(this->m_Ang.load());
    }
    
    void Turtle::left(const float& ang) {
        this->m_Ang.store((float) std::fmod(this->m_Ang.load() + ang, 360));
        this->set_coord_scalar(this->m_Ang.load());
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

    void Turtle::dot(float _Radius, TurtleColors _Color) {
        sf::CircleShape point(_Radius, 10);
        float circle_center = _Radius / 2.f;

        point.setOrigin(circle_center, circle_center);

        switch (_Color)
        {
        case turtle::TurtleColors::black:
            point.setFillColor(sf::Color::Black);
            break;
        case turtle::TurtleColors::red:
            point.setFillColor(sf::Color::Red);
            break;
        case turtle::TurtleColors::yellow:
            point.setFillColor(sf::Color::Yellow);
            break;
        case turtle::TurtleColors::blue:
            point.setFillColor(sf::Color::Blue);
            break;
        }

        point.setPosition(this->m_Pos.load());

        this->m_upMutex.lock();
        this->m_UserPoints.push_back(point);
        this->m_upMutex.unlock();
    }

    // Set Turtle position
    void Turtle::set_pos(const float& x, const float& y) {
        if (this->m_TailDown) {
            sf::Vector2f last_pos_point = this->get_pos();

            this->m_Pos.store(this->from_map_to_real(x, y));
            sf::Vector2f new_pos_point = this->get_pos();
            sf::Vector2f vec{ new_pos_point.x - last_pos_point.x, new_pos_point.y - last_pos_point.y };

            float vec_len = sqrt(vec.x * vec.x + vec.y * vec.y);

            float cos_a = vec.x / vec_len;
            float alpha = std::copysignf(acos(cos_a), vec.y);
            float ang_degrees = (180.f / (float)M_PI) * alpha;

            sf::RectangleShape line(sf::Vector2f(vec_len, 0.5f));
            line.setFillColor(sf::Color::Black);
            line.setOrigin(sf::Vector2f(0.0f, 0.5f / 2.0f));
            line.setRotation(-ang_degrees);
            line.setPosition(this->from_map_to_real(last_pos_point));

            m_ulMutex.lock();
            m_UserLines.push_back(line);
            m_ulMutex.unlock();
        }
        else {
            this->m_Pos.store(this->from_map_to_real(x, y));
        }
    }

    void make_plot(turtle::Turtle& t, std::function<float(float)> f, trangef x_range) {
        sf::Vector2f last_pos = t.get_pos();
        bool tail_state = t.m_TailDown;
        t.up();

        t.set_pos(*x_range.begin(), f(*x_range.begin()));
        t.down();

        for (auto& x : x_range) {
            t.set_pos(x, f(x));
        }

        t.m_Pos.store(t.from_map_to_real(last_pos));
        t.m_TailDown = tail_state;
    }

    void make_grid(turtle::Turtle& t, trangef x_range, trangef y_range, float _PointRadius) {
        sf::Vector2f last_pos = t.get_pos();
        bool tail_state = t.m_TailDown;
        t.up();

        for (auto& x : x_range) {
            for (auto& y : y_range) {
                t.set_pos(x, y);
                t.dot(_PointRadius);
            }
        }

        t.m_Pos.store(t.from_map_to_real(last_pos));
        t.m_TailDown = tail_state;
    }

    void make_grid(turtle::Turtle& t, trangef _range, float _PointRadius) {
        sf::Vector2f last_pos = t.get_pos();
        bool tail_state = t.m_TailDown;
        t.up();

        for (auto& x : _range) {
            for (auto& y : _range) {
                t.set_pos(x, y);
                t.dot(_PointRadius);
            }
        }

        t.m_Pos.store(t.from_map_to_real(last_pos));
        t.m_TailDown = tail_state;
    }

    void make_grid(turtle::Turtle& t, trangef _range) {
        sf::Vector2f last_pos = t.get_pos();
        bool tail_state = t.m_TailDown;
        t.up();

        for (auto& x : _range) {
            for (auto& y : _range) {
                t.set_pos(x, y);
                t.dot(1.0f);
            }
        }

        t.m_Pos.store(t.from_map_to_real(last_pos));
        t.m_TailDown = tail_state;
    }

    void make_line(turtle::Turtle& t, const float& _X1, const float& _Y1, const float& _X2, const float& _Y2) {
        sf::Vector2f last_pos = t.get_pos();
        bool tail_state = t.m_TailDown;
        t.up();

        t.set_pos(_X1, _Y1);
        t.down();
        t.set_pos(_X2, _Y2);
        t.up();

        t.m_Pos.store(t.from_map_to_real(last_pos));
        t.m_TailDown = tail_state;
    }
}