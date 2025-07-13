#include "Land.h"
#include <iostream>

using namespace std;

Land::Land() {}

void Land::Init(ConsoleGameEngine* engine, int x, int y, int l, int w)
{
	xPos = x;
	yPos = y;
	length = l;
	width = w;
	gameEngine = engine;
}

void Land::SetXPos(int newX)
{
	xPos = newX;
}

int Land::getXPos()
{
	return xPos;
}

void Land::SetYPos(int newY)
{
	yPos = newY;
}

int Land::getYPos()
{
	return yPos;
}

void Land::Draw()
{
	gameEngine->DrawRect(xPos, yPos, length, width);

}