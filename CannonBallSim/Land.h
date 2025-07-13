#pragma once
#include "ConsoleGameEngine.h"

class Land 
{
public:
	Land();
	void Init(ConsoleGameEngine *engine, int x, int y, int l, int w);
	void Draw();
	void SetXPos(int newX);
	int getXPos();
	void SetYPos(int newY);
	int getYPos();

private:
	int xPos;
	int yPos;
	int length;
	int width;
	ConsoleGameEngine *gameEngine;
};