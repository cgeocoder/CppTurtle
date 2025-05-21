#define _USE_MATH_DEFINES 

#include <cmath>
#include <iostream>

#include "turtle.h"
#include "turtle_color.h"


namespace turtle {

    Turtle::Turtle() : m_Ang{ 90.0l } {
        this->m_Color = ColorMap.at("black");
        this->m_Background = ColorMap.at("white");

        this->set_coord_scalar(this->m_Ang.load());
        this->up();
        
        m_Window = new TurtleWindow(
            this->m_Pos, 
            this->m_WindowSize,
            this->m_Ang,
            this->m_upMutex,
            this->m_UserPoints,
            this->m_ulMutex,
            this->m_UserLines,
            this->m_Trace,
            this->m_ScreenMove,
            this->m_Background
        );

        sf::Vector2u window_size = this->m_WindowSize.load();

        this->m_HalfWindowWidth = static_cast<unsigned int>(window_size.x / 2.0f);
        this->m_HalfWindowHeight = static_cast<unsigned int>(window_size.y / 2.0f);

        this->set_pos(0.0f, 0.0f);
        // this->set_speed(TurtleSpeed::normal);

        this->down();
        this->m_Trace = true;
        this->m_LineWidth = 0.125f;
    }

    void Turtle::set_coord_scalar(float _Ang) {
        this->m_Sin = tsin(_Ang);
        this->m_Cos = tcos(_Ang);
    }

    void Turtle::forward(const float& step) {
        sf::Vector2f last_pos = this->get_pos();

        this->set_pos(
            last_pos.x + step * this->m_Cos,
            last_pos.y + step * this->m_Sin
        );
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

    void Turtle::set_color(const char* _Color) {
        try {
            this->m_Color = ColorMap.at(_Color);
        } 
        catch (std::exception ex) {
            std::cout << "Turtle: unknown color '" << _Color << "'\n";
        }
    }

    void Turtle::set_color(const uint8_t& _R, const uint8_t& _G, const uint8_t& _B, const uint8_t& _A) {
        this->m_Color = sf::Color(_R, _G, _B, _A);
    }

    void Turtle::dot(const char* _Color, float _Radius) {
        sf::CircleShape point(_Radius, 10);
        float circle_center = _Radius / 2.f;

        point.setOrigin(circle_center, circle_center);
        point.setFillColor(ColorMap.at(_Color));
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

            sf::RectangleShape line(sf::Vector2f(vec_len, this->m_LineWidth));
            line.setFillColor(sf::Color::Black);
            line.setOrigin(sf::Vector2f(0.0f, this->m_LineWidth / 2.0f));
            line.setRotation(-ang_degrees);
            line.setPosition(this->from_map_to_real(last_pos_point));
            line.setFillColor(this->m_Color);

            m_ulMutex.lock();
            m_UserLines.push_back(line);
            m_ulMutex.unlock();
        }
        else {
            this->m_Pos.store(this->from_map_to_real(x, y));
        }
    }

    void draw_function(turtle::Turtle& t, const trangef& x_range, std::function<float(float)> f) {
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

    void draw_line(turtle::Turtle& t, const Vec2f& _Vec1, const Vec2f& _Vec2) {
        sf::Vector2f last_pos = t.get_pos();
        bool tail_state = t.m_TailDown;
        t.up();

        t.set_pos(_Vec1.x, _Vec1.y);
        t.down();
        t.set_pos(_Vec2.x, _Vec2.y);
        t.up();

        t.m_Pos.store(t.from_map_to_real(last_pos));
        t.m_TailDown = tail_state;
    }
}