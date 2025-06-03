#include "window.h"

#include <SFML/Graphics.hpp>
#include "paths.h"

namespace cpl {
	Window::Window() : m_HalfWindowWidth{ 0 }, m_HalfWindowHeight{ 0 } {
		m_WndThread = std::thread([&]() { this->run(); });
	}

	Window::~Window() {
		done();
	}

	void Window::run() {
		const auto monitor_param = sf::VideoMode::getDesktopMode();

		sf::Vector2u window_size = sf::Vector2u(
			(unsigned)(monitor_param.width / 2),
			(unsigned)(monitor_param.height / 1.5)
		);

		m_HalfWindowWidth = window_size.x / 2;
		m_HalfWindowHeight = window_size.y / 2;

		// Window setting

		sf::ContextSettings wc_settings;
		wc_settings.antialiasingLevel = 8;

		sf::RenderWindow wnd(
			sf::VideoMode(window_size.x, window_size.y),
			"C++ Plots",
			sf::Style::Titlebar | sf::Style::Close,
			wc_settings
		);

		// Window Icon

		sf::Image window_logo;
		window_logo.loadFromFile(ICON_PATH);
		wnd.setIcon(
		 	window_logo.getSize().x,
		 	window_logo.getSize().y,
		 	window_logo.getPixelsPtr()
		);

		volatile bool view_move_enable = false;
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(wnd);

		sf::View view(sf::FloatRect(
			-(float)window_size.x,
			(float)window_size.y,
			(float)window_size.x * 2,
			(float)window_size.y * 2
		));

		view.zoom(0.02f);
		view.setCenter(window_size.x / 2.0f, window_size.y / 2.0f);

		// _Size.store(window_size);

		// Main loop

		float a = 0.0f;
		signed int zoom_count = 0;
		while (wnd.isOpen()) {
			sf::Event event;

			while (wnd.pollEvent(event)) {
				sf::Event::EventType event_type = event.type;

				// Close window event
				if (event_type == sf::Event::Closed) {
					wnd.close();
				}

				if (/*_ScreenMove.load()*/ true) {
					// Zooming map
					if (event.type == sf::Event::MouseWheelScrolled) {
						if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
							if (event.mouseWheelScroll.delta < 0) {
								if (zoom_count > -30) {
									view.zoom(1.1f);
									zoom_count -= 1;
								}
							}
							else {
								if (zoom_count < 30) {
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
				}
			}

			wnd.clear(sf::Color::White);
			wnd.setView(view);
			
			m_plotMutex.lock();

			for (Plot& Plot : m_plots) {
				for (sf::RectangleShape& line : Plot.m_PlotLines) {
					wnd.draw(line);
				}

				for (sf::RectangleShape& line : Plot.m_StaticFuncLines) {
					wnd.draw(line);
				}

				for (sf::RectangleShape& line : Plot.m_StaticLines) {
					wnd.draw(line);
				}

				for (sf::CircleShape& point : Plot.m_StaticPoints) {
					wnd.draw(point);
				}

				if (Plot.m_Title) {
					wnd.draw(*Plot.m_Title);
				}
			}

			m_plotMutex.unlock();

			wnd.display();
		}
	}

	void Window::add_plot(Plot& plot) {
		m_plotMutex.lock();

		plot.draw();

		// Convert from current plot coordinates to global

		for (sf::RectangleShape& line : plot.m_PlotLines) {
			line.setPosition(from_map_to_real(line.getPosition()));
		}

		for (sf::RectangleShape& line : plot.m_StaticFuncLines) {
			line.setPosition(from_map_to_real(line.getPosition()));
		}

		for (sf::RectangleShape& line : plot.m_StaticLines) {
			line.setPosition(from_map_to_real(line.getPosition()));
		}

		for (sf::CircleShape& point : plot.m_StaticPoints) {
			point.setPosition(from_map_to_real(point.getPosition()));
		}

		if (plot.m_Title)
			plot.m_Title->setPosition(from_map_to_real(plot.m_Title->getPosition()));

		m_plots.push_back(plot);
		m_plotMutex.unlock();
	}

	void Window::done() {
		if (m_WndThread.joinable())
			m_WndThread.join();
	}
}