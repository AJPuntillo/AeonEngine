#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <glm/glm.hpp>
#include <unordered_map>

namespace AEON_ENGINE
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();
		void pressKey(unsigned int keyID_);
		void releaseKey(unsigned int keyID_);
		bool isKeyDown(unsigned int keyID_); //Returns true if key is held down
		bool isKeyPressed(unsigned int keyID_); //Returns true if key was just pressed
		bool wasMouseMoved();

		//Getters
		glm::vec2 getMouseCoords() const { return glm::vec2((float)m_mouseCoordsX, (float)m_mouseCoordsY); }
		double getMouseCoordsX() const { return m_mouseCoordsX; }
		double getMouseCoordsY() const { return m_mouseCoordsY; }

		//Setters
		void setMouseCoords(double x_, double y_);

	private:
		bool wasKeyDown(unsigned int keyID_);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		double m_mouseCoordsX = 0;
		double m_mouseCoordsY = 0;
		double m_lastX = 0;
		double m_lastY = 0;
	};

}

#endif