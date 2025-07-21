#pragma once
#include "ConsoleGameEngine.h"
#include "GameObject.h"

class CannonBall : public GameObject
{
public:
	CannonBall();
	void Init(ConsoleGameEngine *engine, int x, int y, int r, float sTime);
	void Draw(int gravity, float fDegree, float fTheta);

private:
	int radius;
	float startTime;
};