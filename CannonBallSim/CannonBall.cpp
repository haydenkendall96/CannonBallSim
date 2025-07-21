#include "CannonBall.h"
#include <iostream>

using namespace std;

CannonBall::CannonBall(){}

void CannonBall::Init(ConsoleGameEngine* engine, float x, float y, int r, float sTime, float angle, float initVel)
{
	isInit = true; //TODO: See if there is a better way to implement this.

	SetXPos(x);
	SetYPos(y);
	SetXVel(initVel * cosf(angle * (3.1415f / 180.0f)));
	SetYVel(initVel * sinf(angle * (3.1415f / 180.0f)));
	radius = r;
	gameEngine = engine;
	startTime = sTime;
}

//Calculates the motion of the object and draws the result to the screen.
void CannonBall::Draw(float gravity, float fTheta)
{
	float deltaTime = 1.0f + (fTheta - startTime);
	float delatTimeSq = deltaTime * deltaTime;

	if (GetYPos() < 230)
	{
		SetXPos(GetXPos() + GetXVel() * deltaTime);

		SetYVel(GetYVel() + (gravity * deltaTime));

		SetYPos(GetYPos() + (GetYVel() * deltaTime) + (0.5f * gravity * delatTimeSq));
	}
	else
	{
		SetYVel(0);
		SetYPos(230);
	}

	gameEngine -> FillCircle(GetXPos(), GetYPos(), radius);

}