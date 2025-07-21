#include "Cannon.h"
#include <iostream>

using namespace std;

Cannon::Cannon() {}

void Cannon::Init(ConsoleGameEngine* engine, int x, int y)
{
	isInit = true;
	SetXPos(x);
	SetYPos(y);
	gameEngine = engine;
	length = 10;
	width = 35;
}

void Cannon::Draw(int rotation)
{

	gameEngine->DrawRect(getXPos(), getYPos(), length, width, rotation);
	gameEngine->FillCircle(getXPos()-(width/6), getYPos() + (length/2), 7);

}