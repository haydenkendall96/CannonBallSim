#pragma once
#include "ConsoleGameEngine.h"

/**
 * @brief
 *
 * This class provides a parent definition for general simulation or gameobjects.
 * Inherited classes are able to keep track of position, velocity, and initialization.
 */
class GameObject
{

private:
	float xPos; //x-position of the object
	float yPos; //y-position of the object
	float velX = 0; //horizontal velocity of the object
	float velY = 0; //vertical velocity of the object

public:
	/**
	* @brief Default constructor of the object.
	*/
	GameObject();

	/**
	* @brief Setter of the x-position.
	*/
	void SetXPos(float newX) { xPos = newX; };

	/**
	* @brief Getter of the x-position.
	*/
	float GetXPos() { return xPos; };

	/**
	* @brief Setter of the y-position.
	*/
	void SetYPos(float newY) { yPos = newY; };

	/**
	* @brief Getter of the y-position.
	*/
	float GetYPos() { return yPos; };

	/**
	* @brief Setter of the objects horizontal velocity. 
	*/
	void SetXVel(float newXVel) { velX = newXVel; };

	/**
	* @brief Getter of the objects horizontal velocity.
	*/
	float GetXVel() { return velX; };

	/**
	* @brief Setter of the objects vertical velocity.
	*/
	void SetYVel(float newYVel) { velY = newYVel; };

	/**
	* @brief Getter of the objects vertical velocity. 
	*/
	float GetYVel() { return velY; };

	bool isInit = false; //Initialization tracker. 

	ConsoleGameEngine* gameEngine; //Game engine location for accessing methods.
};