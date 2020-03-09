#pragma once
#include "../../Key.h"

struct InputState
{
	bool pressed = false;
	int frameNum = 0;
};

struct Input
{
	InputState keyStates[(unsigned int)Key::MAX];

	int entity_id = 0;
	float x = 0;
	float y = 0;

	bool jump = false;
};