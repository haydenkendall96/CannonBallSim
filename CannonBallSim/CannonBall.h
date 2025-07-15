#pragma once
#include "ConsoleGameEngine.h"
#include "GameObject.h"

class CannonBall : public GameObject
{
public:
	CannonBall();
	void Init(ConsoleGameEngine *engine, int x, int y, int r);
	void Draw();

private:
	int radius;
};