#pragma once
#include "GameObject.h"

class Cannon : public GameObject
{
public:
	Cannon();
	void Init(ConsoleGameEngine* engine, int x, int y);
	void Draw(int rotation);
private:
	int length;
	int width;


};