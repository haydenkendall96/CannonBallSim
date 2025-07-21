#pragma once
#include "GameObject.h"

/**
 * @brief
 *
 * This class provides a cannon object definition for launching cannon balls.
 * The primary role of this class is to visualize user interaction in regards to position and angle of velocity. 
 */
class Cannon : public GameObject
{
private:
	int length; // The object length.
	int width; //The object width.
	int lengthDivisor; //The object length divisor.
	int wheelRadius; //The object wheel radius.

public:
	/**
	 * @brief
	 *
	 * Base constructor of the class.
	 */
	Cannon();

	/**
	 * @brief
	 * Initialization method of the object.
	 * @param engine - The game engine.
	 * @param x - The x position.
	 * @param y - The y position.
	 */
	void Init(ConsoleGameEngine* engine, float x, float y);

	/**
	 * @brief
	 * Draw method of the object.
	 * @param rotation - The degree for shape transformations.
	 */
	void Draw(int rotation);

	/**
	 * @brief
	 * Getter of the object width.
	 */
	int GetWidth() { return width; };

	/**
	 * @brief
	 * Getter of the object length.
	 */
	int GetLength() { return length; };
};