#include "InputManager.h"

namespace gip {


	glm::vec2               InputManager::_mousePosition;
	std::vector<glm::vec2>  InputManager::_mouseMovedEvents;
	std::vector<uint16_t>   InputManager::_mousePressEvents;
	std::vector<uint16_t>   InputManager::_keyPressedEvents;
	std::vector<uint16_t>   InputManager::_keyReleasedEvents;
	std::vector<uint16_t>   InputManager::_mouseReleaseEvents;

}