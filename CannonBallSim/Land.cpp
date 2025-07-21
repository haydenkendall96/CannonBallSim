#include "Land.h"
#include <iostream>

using namespace std;

Land::Land() {}

void Land::Init(ConsoleGameEngine* engine, int x, int y, int l, int w)
{
	isInit = true;
	SetXPos(x);
	SetYPos(y);
	length = l;
	width = w;
	gameEngine = engine;
}

void Land::Draw()
{
	gameEngine->DrawRect(getXPos(), getYPos(), length, width, 0);

}