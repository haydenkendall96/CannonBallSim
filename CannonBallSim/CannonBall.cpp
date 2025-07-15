#include "CannonBall.h"
#include <iostream>

using namespace std;

CannonBall::CannonBall(){}

void CannonBall::Init(ConsoleGameEngine *engine, int x, int y, int r)
{
	SetXPos(x);
	SetYPos(y);
	radius = r;
	gameEngine = engine;
}

void CannonBall::Draw()
{
	gameEngine -> FillCircle(getXPos(), getYPos(), radius);

}