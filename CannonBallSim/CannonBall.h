#pragma once
#include "ConsoleGameEngine.h"
#include "GameObject.h"

/**
 * @brief
 *
 * This class provides a cannon object definition for cannon balls.
 * The primary role of this class is to visualize user interaction in regards to position and angle of velocity.
 */
class CannonBall : public GameObject
{

private:
	int radius; //The radius of the ball.
	float startTime; //The time of initialization. 

public:
	/**
	 * @brief
	 *
	 * Default constructor class.
	 */
	CannonBall();
	
	/**
	 * @brief
	 *
	 * Initialization method to establish object data.
	 * @param engine - The game engine.
	 * @param x - The x position.
	 * @param y - The y position.
	 * @param r - The radius of the ball.
	 * @param sTime - The time of initialization. 
	 * @param angle - The angle of initial velocity. 
	 */
	void Init(ConsoleGameEngine *engine, float x, float y, int r, float sTime, float angle);

	/**
	 * @brief
	 *
	 * The draw method to visualize the projectile.
	 * @param gravity - The gravity of the world.
	 * @param fTheta - The world time.
	 */
	void Draw(float gravity, float fTheta);


};