#pragma once
#include "ConsoleGameEngine.h"
#include "GameObject.h"

/**
 * @brief
 *
 * This class provides a land object definition for relative visuals..
 */
class Land : public GameObject
{
public:
	/**
	 * @brief
	 *
	 * The defualt constructor.
	 */
	Land();

	/**
	 * @brief
	 *
	 * The initialization method of the object to establish data.
	 * @param engine - The game engine.
	 * @param x - The x position.
	 * @param y - The y position.
	 * @param l - The length.
	 * @param w - The width.
	 */
	void Init(ConsoleGameEngine *engine, int x, int y, int l, int w);

	/**
	 * @brief
	 *
	 * Draws the object to the screen.
	 */
	void Draw();

private:
	int length;
	int width;
	ConsoleGameEngine *gameEngine;
};