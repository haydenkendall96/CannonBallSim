#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject() {}

void GameObject::SetXPos(int newX)
{
	xPos = newX;
}

int GameObject::getXPos()
{
	return xPos;
}

void GameObject::SetYPos(int newY)
{
	yPos = newY;
}

int GameObject::getYPos()
{
	return yPos;
}