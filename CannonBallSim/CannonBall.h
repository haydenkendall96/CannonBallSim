#pragma once
#include "ConsoleGameEngine.h"

class CannonBall 
{
public:
	CannonBall();
	void Init(ConsoleGameEngine *engine, int x, int y, int r);
	void Draw();
	void SetXPos(int newX);
	int getXPos();

private:
	int xPos;
	int yPos;
	int radius;
	ConsoleGameEngine *gameEngine;
};