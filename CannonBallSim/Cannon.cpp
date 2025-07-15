#include "Cannon.h"
#include <iostream>

using namespace std;

Cannon::Cannon() {}

void Cannon::Init(ConsoleGameEngine* engine, int x, int y)
{
	SetXPos(x);
	SetYPos(y);
	gameEngine = engine;
	degree = 45;
	length = 25;
	width = 10;

}

void Cannon::Draw()
{

	gameEngine->DrawRect(10, 10, length, width, -45);

}