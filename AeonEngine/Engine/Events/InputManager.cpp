#include "InputManager.h"

using namespace AEON_ENGINE;

InputManager::InputManager()
{
	//Empty
}


InputManager::~InputManager()
{
	//Empty
}

void InputManager::update()
{
	//Loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
	//For each -- Works the same as below -- works with containers with a begin and end method
	for (auto& it : m_keyMap) {
		m_previousKeyMap[it.first] = it.second;
	}

	/*
	for (auto it = _keyMap.begin(); it != _keyMap.end(); it++) {
	_previousKeyMap[it->first] = it->second;
	}
	*/
}

void InputManager::pressKey(unsigned int keyID_)
{							 //A map can be treated like an array
	m_keyMap[keyID_] = true; //First check if this keyID is in the map, if not then create it and set it to true
}

void InputManager::releaseKey(unsigned int keyID_)
{
	m_keyMap[keyID_] = false;
}

void InputManager::setMouseCoords(double x_, double y_)
{
	m_lastX = m_mouseCoordsX;
	m_lastY = m_mouseCoordsY;

	m_mouseCoordsX = x_;
	m_mouseCoordsY = y_;
}

bool InputManager::wasMouseMoved() {
	if (m_lastX == m_mouseCoordsX && m_lastY == m_mouseCoordsY) {
		return false;
	}

	return true;
}

bool InputManager::isKeyDown(unsigned int keyID_)
{
	auto it = m_keyMap.find(keyID_);

	if (it != m_keyMap.end())
		return it->second;
	else
		return false;
}

bool InputManager::isKeyPressed(unsigned int keyID_)
{
	//Check if it is pressed this frame, and wasn't pressed last frame
	if (isKeyDown(keyID_) == true && wasKeyDown(keyID_) == false)
		return true;

	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID_)
{
	auto it = m_previousKeyMap.find(keyID_);

	if (it != m_previousKeyMap.end())
		return it->second;
	else
		return false;
}