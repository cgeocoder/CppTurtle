#include "turtle_window.h"
#include "../../res/turtle_paths.h"
#include <iostream>

namespace turtle {
	constexpr const size_t default_grid_size = 10'670ULL;
	const sf::Vector2f turtle_sprite_scale(0.015f, 0.015f);

	TurtleWindow::TurtleWindow(
		std::atomic<sf::Vector2f>& _Pos, 
		std::atomic<sf::Vector2u>& _Size,
		const bool _GridVisible) {

		this->m_WndThread = std::thread([&]() {
			this->run(_Pos, _Size, _GridVisible);
		});

		while ((_Size.load().x == 0.0f) || (_Size.load().y == 0.0f));
	}

	void TurtleWindow::run(
		std::atomic<sf::Vector2f>& _Pos, 
		std::atomic<sf::Vector2u>& _Size,
		const bool _GridVisible) {

		const auto monitor_param = sf::VideoMode::getDesktopMode();

		sf::Vector2u window_size = sf::Vector2u(
			(unsigned)(monitor_param.width / 2),
			(unsigned)(monitor_param.height / 1.5)
		);

		// Window setting

		sf::ContextSettings wc_settings;
		wc_settings.antialiasingLevel = 8;

		sf::RenderWindow wnd(
			sf::VideoMode(window_size.x, window_size.y),
			"Turtle++",
			sf::Style::Titlebar | sf::Style::Close,
			wc_settings
		);

		// Window Icon

		sf::Image window_logo;
		window_logo.loadFromFile(ICON_PATH);
		wnd.setIcon(window_logo.getSize().x, window_logo.getSize().y, window_logo.getPixelsPtr());


		// Turtle sprite

		sf::Texture turtle_texture;
		if (!turtle_texture.loadFromFile(TURTULE_TEXTURE_PATH)) {
			__debugbreak();
		}

		turtle_texture.setSmooth(true);
		this->m_Turtle.setTexture(turtle_texture);
		sf::Vector2u texture_size = turtle_texture.getSize();

		this->m_Turtle.setOrigin(texture_size.x / 2.f, texture_size.y / 2.f);
		this->m_Turtle.setScale(turtle_sprite_scale);

		// Grid

		sf::CircleShape* grid = nullptr;

		if (_GridVisible) {
			grid = new sf::CircleShape[default_grid_size + 1];

			size_t counter = 0;
			constexpr const float scale = 35.0f;
			constexpr const float point_radius = 3.5f;
			unsigned int point_counter = 0;

			const float center_x = window_size.x / 2.0f;
			const float center_y = window_size.y / 2.0f;

			auto add_point = [&](const float &px, const float& py) {
				sf::CircleShape point(point_radius, 40);
				point.setOrigin(point_radius / 2.f, point_radius / 2.f);
				point.setFillColor(sf::Color::Black);
				point.setPosition(sf::Vector2f(px, py));

				grid[counter++] = point;
			};

			for (float x = center_x; x < (float)window_size.x * 2.f; x += scale) {
				for (float y = center_y; y < (float)window_size.y * 2.f; y += scale) {
					add_point(x, y);
				}

				for (float y = center_y; y > -(float)window_size.y * 1.5f; y -= scale) {
					add_point(x, y);
				}
			}

			for (float x = center_x; x > -(float)window_size.x * 1.f; x -= scale) {
				for (float y = center_y; y < (float)window_size.y * 2.f; y += scale) {
					add_point(x, y);
				}

				for (float y = center_y; y > -(float)window_size.y * 1.5f; y -= scale) {
					add_point(x, y);
				}
			}
		}

		volatile bool view_move_enable = false;
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(wnd);

		sf::View view(sf::FloatRect(
			-(float)window_size.x,
			(float)window_size.y,
			(float)window_size.x * 2,
			(float)window_size.y * 2
		));

		view.zoom(0.4f);
		view.setCenter(window_size.x / 2.0f, window_size.y / 2.0f);

		_Size.store(window_size);

		// Main loop
		
		signed int zoom_count = 0;
		while (wnd.isOpen()) {
			sf::Event event;

			while (wnd.pollEvent(event)) {
				sf::Event::EventType event_type = event.type;

				// Close window event
				if (event_type == sf::Event::Closed) {
					wnd.close();
				}

				// Zooming map
				else if (event.type == sf::Event::MouseWheelScrolled) {
					if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
						if (event.mouseWheelScroll.delta < 0) {
							if (zoom_count > -18) {
								view.zoom(1.1f);
								zoom_count -= 1;
							}
						}
						else {
							if (zoom_count < 15) {
								view.zoom(0.9f);
								zoom_count += 1;
							}
						}
					}
				}

				// Moving map
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						view_move_enable = true;
					}
				}
				else if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						view_move_enable = false;
					}
				}
				else if (event.type == sf::Event::MouseMoved) {
					if (view_move_enable) {
						float zoom_scale_offset = view.getSize().x / window_size.x;

						view.move(
							(mouse_pos.x - event.mouseMove.x) * zoom_scale_offset,
							(mouse_pos.y - event.mouseMove.y) * zoom_scale_offset
						);
					}

					mouse_pos = sf::Mouse::getPosition(wnd);
				}

				// Centering map by turtle
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					view.setCenter(_Pos.load());
				}
			}

			wnd.clear(sf::Color::White);
			wnd.setView(view);

			if (_GridVisible) {
				for (size_t i = 0; i < default_grid_size; ++i)
					wnd.draw(grid[i]);
			}

			sf::Vector2f pos = _Pos.load();
			this->m_Turtle.setPosition(pos.x, pos.y);

			wnd.draw(this->m_Turtle);

			wnd.display();
		}
	}
}