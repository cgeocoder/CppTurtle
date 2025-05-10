#pragma once

#ifndef __TURTLE_WINDOW_H__
#define __TURTLE_WINDOW_H__

#include <SFML/Graphics.hpp>

#include <thread>
#include <atomic>
#include <list>
#include <mutex>


namespace turtle {

	// The window class for coding and run in window
	class TurtleWindow {
	public:
		// TurtleWindow constructotr
		// @param _Pos - atomic ref to a Turtle position
		// @param _Size - atomic ref to a window size (sf::Vector2u)
		// @param _Ang - atomic ref to a Turtle angle
		// @param _upMutex - atomic ref to a User Point Mutex
		// @param _UserPoints - ref to a User Points (std::list)
		// @param _ulMutex - atomic ref to a User Line Mutex
		// @param _UserLines - ref to a User Line (std::list)
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