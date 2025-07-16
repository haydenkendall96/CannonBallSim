#include "Cannon.h"
#include <iostream>

using namespace std;

Cannon::Cannon() {}

void Cannon::Init(ConsoleGameEngine* engine, int x, int y)
{
	SetXPos(x);
	SetYPos(y);
	gameEngine = engine;
	length = 10;
	width = 20;
}

void Cannon::Draw(int rotation)
{

	gameEngine->DrawRect(getXPos(), getYPos(), length, width, rotation);

}