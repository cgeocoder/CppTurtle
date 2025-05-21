#include "turtle_window.h"
#include "../../res/turtle_paths.h"

namespace turtle {
	const sf::Vector2f turtle_sprite_scale(0.015f, 0.015f);

	TurtleWindow::TurtleWindow(
		std::atomic<sf::Vector2f>& _Pos,
		std::atomic<sf::Vector2u>& _Size,
		std::atomic<float>& _Ang,
		std::mutex& _upMutex,
		std::list<sf::CircleShape>& _UserPoints,
		std::mutex& _ulMutex,
		std::vector<sf::RectangleShape>& _UserLines,
		std::atomic<bool>& _Trace,
		std::atomic<bool>& _ScreenMove,
		std::atomic<sf::Color>& _Background) {

		this->m_WndThread = std::thread([&]() {
			this->run(
				_Pos, _Size, _Ang,
				_upMutex,
				_UserPoints,
				_ulMutex,
				_UserLines, 
				_Trace,
				_ScreenMove,
				_Background
			);
		});

		while ((_Size.load().x == 0.0f) || (_Size.load().y == 0.0f));
	}

	
	void TurtleWindow::run(
		std::atomic<sf::Vector2f>& _Pos,
		std::atomic<sf::Vector2u>& _Size,
		std::atomic<float>& _Ang,
		std::mutex& _upMutex,
		std::list<sf::CircleShape>& _UserPoints,
		std::mutex& _ulMutex,
		std::vector<sf::RectangleShape>& _UserLines,
		std::atomic<bool>& _Trace,
		std::atomic<bool>& _ScreenMove,
		std::atomic<sf::Color>& _Background) {

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
#ifdef _DEBUG
			"CppTurtle (Debug)",
#else
			"CppTurtle",
#endif 
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

		_Size.store(window_size);

		// Main loop
		
		float a = 0.0f;
		signed int zoom_count = 0;
		while (wnd.isOpen()) {
			while (!_Trace.load());

			sf::Event event;

			while (wnd.pollEvent(event)) {
				sf::Event::EventType event_type = event.type;

				// Close window event
				if (event_type == sf::Event::Closed) {
					wnd.close();
				}

				if (_ScreenMove.load()) {
					// Zooming map
					if (event.type == sf::Event::MouseWheelScrolled) {
						if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
							if (event.mouseWheelScroll.delta < 0) {
								if (zoom_count > -18) {
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

					// Centering map by turtle
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						view.setCenter(_Pos.load());
					}
				}
			}

			wnd.clear(_Background.load());
			wnd.setView(view);

			_upMutex.lock();

			for (auto& point : _UserPoints)
				wnd.draw(point);

			_upMutex.unlock();

			_ulMutex.lock();
			
			{
				size_t ulLen = _UserLines.size();
				sf::RectangleShape* ulArray = _UserLines.data();
				for (size_t i = 0; i < ulLen; ++i)
					wnd.draw(ulArray[i]);
			}
			
			_ulMutex.unlock();

			// sf::Vector2f pos = _Pos.load();
			// this->m_Turtle.setPosition(pos.x, pos.y);
			// wnd.draw(this->m_Turtle);

			wnd.display();
		}
	}
}