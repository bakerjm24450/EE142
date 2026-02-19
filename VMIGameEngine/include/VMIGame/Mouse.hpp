// Codes for handling the mouse buttons.
#pragma once
#ifndef VMI_GAME_MOUSE_H
#define VMI_GAME_MOUSE_H


#include "Graphics.hpp"

namespace vmi {

enum class MouseButton {
	Left = (int) sf::Mouse::Button::Left,
	Right = (int) sf::Mouse::Button::Right,
	Middle = (int) sf::Mouse::Button::Middle
};

} // namespace vmi

#endif