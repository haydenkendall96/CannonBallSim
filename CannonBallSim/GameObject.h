#pragma once
#include "ConsoleGameEngine.h"

class GameObject
{
public:
	GameObject();
	void SetXPos(int newX) { xPos = newX; };
	int GetXPos() { return xPos;  };
	void SetYPos(int newY) { yPos = newY; };
	int GetYPos() { return yPos; };
	bool isInit = false;
	ConsoleGameEngine* gameEngine;


private:
	int xPos;
	int yPos;
	float velX;
	float velY;
	
};