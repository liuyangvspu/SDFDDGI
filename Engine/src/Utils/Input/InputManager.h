#pragma once
#include <Engine/src/Utils/Input/GLFWInputKeyStore.h>
#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include <algorithm>
namespace gip {

	class InputManager {

	private:
		static std::vector<uint16_t> 	_keyReleasedEvents;
		static std::vector<uint16_t>  	_keyPressedEvents;
		static std::vector<uint16_t>  	_mousePressEvents;
		static std::vector<uint16_t>	_mouseReleaseEvents;
		static std::vector<glm::vec2>  	_mouseMovedEvents;
		static glm::vec2 				_mousePosition;
	public:
		InputManager(const InputManager&) = delete;
		InputManager operator=(const InputManager&) = delete;

		static void addKeyPress(uint16_t key) {
			_keyPressedEvents.push_back(key);
		}
		static void addKeyRelease(uint16_t key) {
			_keyReleasedEvents.push_back(key);
		}
		static void addMousePosition(double x, double y) {
			_mousePosition.x = x;
			_mousePosition.y = y;
			_mouseMovedEvents.push_back(glm::vec2(x, y));
		}
		static void addMousePress(uint16_t keyPressed) {
			_mousePressEvents.push_back(keyPressed);
		}
		static void addMouseRelease(uint16_t keyReleased) {
			_mouseReleaseEvents.push_back(keyReleased);
		}
		static void clear() {
			std::vector<int> removeIndices;
			for (int i = 0; i < _keyPressedEvents.size(); i++) {
				for (int k = 0; k < _keyReleasedEvents.size(); k++) {
					if (_keyPressedEvents[i] == _keyReleasedEvents[k]) {
						removeIndices.push_back(i);
					}
				}
			}
			while (removeIndices.size() > 0) {
				_keyPressedEvents.erase(_keyPressedEvents.begin() + removeIndices[removeIndices.size() - 1]);
				removeIndices.pop_back();
			}
			_keyReleasedEvents.clear();
			_mouseMovedEvents.clear();
			_mousePressEvents.clear();
			_mouseReleaseEvents.clear();
		}

		inline static bool isKeyPressed(uint16_t key) {			
			for (int i = 0; i < _keyPressedEvents.size(); i++)
				if (_keyPressedEvents[i] == key)
					return true;
			return false;
		}
		inline static bool isKeyReleased(uint16_t key) {
			for (int i = 0; i < _keyReleasedEvents.size(); i++)
				if (_keyReleasedEvents[i] == key) {
					return true;
				}
			return false;
		}

		inline static bool isMousePressed(uint16_t key) {
			for (int i = 0; i < _mousePressEvents.size(); i++)
				if (_mousePressEvents[i] == key)
					return true;
			return false;
		}
		inline static bool isMouseReleased(uint16_t key) {
			for (int i = 0; i < _mouseReleaseEvents.size(); i++)
				if (_mouseReleaseEvents[i] == key)
					return true;
			return false;
		}

		inline static glm::vec2 getMouseMovedPosition() {
			return _mousePosition;
		}

	};


}