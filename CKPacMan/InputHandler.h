#pragma once
#include <SFML/Window.hpp>
#include "InputEvent.h"

class InputHandler
{
public:
	InputHandler() = default;
	
	InputEvent onMoveRight;
	InputEvent onMoveUp;
	InputEvent onMoveLeft;
	InputEvent onMoveDown;

	void HandleInput();
};

