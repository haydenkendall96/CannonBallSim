#include "Cannon.h"
#include <iostream>

using namespace std;

Cannon::Cannon() {}

void Cannon::Init(ConsoleGameEngine* engine, float x, float y)
{
	isInit = true;
	SetXPos(x);
	SetYPos(y);
	gameEngine = engine;
	length = 10;
	width = 35;
	lengthDivisor = 2;
	wheelRadius = 7;
}

void Cannon::Draw(int rotation)
{

	gameEngine->DrawRect(GetXPos(), GetYPos(), length, width, rotation);
	gameEngine->FillCircle(GetXPos(), GetYPos() + (length/ lengthDivisor), wheelRadius);

}