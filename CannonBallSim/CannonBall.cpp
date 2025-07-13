#include "CannonBall.h"
#include <iostream>

using namespace std;

CannonBall::CannonBall(){}

void CannonBall::Init(ConsoleGameEngine *engine, int x, int y, int r)
{
	xPos = x;
	yPos = y;
	radius = r;
	gameEngine = engine;
}

void CannonBall::SetXPos(int newX)
{
	xPos = newX;
}

int CannonBall::getXPos()
{
	return xPos;
}

void CannonBall::Draw()
{
	gameEngine -> DrawCircle(xPos, yPos, radius);

}