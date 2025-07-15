#pragma once
#include "ConsoleGameEngine.h"
#include "GameObject.h"

class Land : public GameObject
{
public:
	Land();
	void Init(ConsoleGameEngine *engine, int x, int y, int l, int w);
	void Draw();

private:
	int length;
	int width;
	ConsoleGameEngine *gameEngine;
};