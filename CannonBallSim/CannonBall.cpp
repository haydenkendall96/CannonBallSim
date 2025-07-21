#include "CannonBall.h"
#include <iostream>

using namespace std;

CannonBall::CannonBall(){}

void CannonBall::Init(ConsoleGameEngine *engine, int x, int y, int r, float sTime)
{
	isInit = true; //TODO: See if there is a better way to implement this.
	SetXPos(x);
	SetYPos(y);
	radius = r;
	gameEngine = engine;
	startTime = 1.0f * sTime;
}

void CannonBall::Draw(int gravity, float angle, float fTheta)
{
	float deltaTime = fTheta - startTime;
	float deltaChange = (gravity * deltaTime);

	SetYPos(GetYPos() + (gravity * deltaChange));
	SetXPos(GetXPos() + (gravity * deltaChange));

	gameEngine -> FillCircle(GetXPos(), GetYPos(), radius);

}