#pragma once
#include "ConsoleGameEngine.h"

class GameObject
{
public:
	GameObject();
	void SetXPos(int newX) { xPos = newX; };
	int getXPos() { return xPos;  };
	void SetYPos(int newY) { yPos = newY; };
	int getYPos() { return yPos; };
	bool isInit = false;
	ConsoleGameEngine* gameEngine;


private:
	int xPos;
	int yPos;
	int velX;
	int velY;
	
};