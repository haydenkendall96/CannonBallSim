#pragma once
#include "ConsoleGameEngine.h"

class GameObject
{
public:
	GameObject();
	void SetXPos(int newX);
	int getXPos();
	void SetYPos(int newY);
	int getYPos();


private:
	int xPos;
	int yPos;
	ConsoleGameEngine* gameEngine;
};