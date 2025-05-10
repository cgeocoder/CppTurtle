#pragma once

#ifndef __TURTLE_WINDOW_H__
#define __TURTLE_WINDOW_H__

#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include "vec.h"
#include <list>
#include <mutex>

namespace turtle {

	// The window class for coding and run in window-editor
	class TurtleWindow {
	public:
		TurtleWindow(
			std::atomic<sf::Vector2f>& _Pos,
			std::atomic<sf::Vector2u>& _Size,
			std::atomic<float>& _Ang,
			std::mutex& _upMutex,
			std::list<sf::CircleShape>& _UserPoints,
			std::mutex& _ulMutex,
			std::list<sf::RectangleShape>& _UserLines
		);

		inline ~TurtleWindow() {
			this->done();
		}

		void run(
			std::atomic<sf::Vector2f>& _Pos,
			std::atomic<sf::Vector2u>& _Size,
			std::atomic<float>& _Ang,
			std::mutex& _upMutex,
			std::list<sf::CircleShape>& _UserPoints,
			std::mutex& _ulMutex,
			std::list<sf::RectangleShape>& _UserLines
		);

		// Waits until the window closes
		inline void done() {
			if (m_WndThread.joinable())
				m_WndThread.join();
		}

	private:
		sf::Sprite m_Turtle;
		std::thread m_WndThread;
	};
}

#endif // __TURTLE_WINDOW_H__