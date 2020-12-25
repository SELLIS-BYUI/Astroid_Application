/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/
#ifndef GAME_H
#define GAME_H
#include "uiInteract.h"
#include "point.h"
#include "uiDraw.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"
#include <vector>
#include <list>
#define ROCK_NUMBER 5

class Game
{
private:
	Point topLeft;
	Point bottomRight;
	list <Rock*> rocks;
	vector <Bullet*> bullets;
	Ship ship;

	void advanceBullets();
	void advanceRocks();
	void advanceShip();
	bool isOnScreen(const Point &point);
	float getClosestDistance(const flyingObject &obj1, const flyingObject &obj2) const;

public:
	Game(Point tl, Point br);

	~Game() {};

	void handleInput(const Interface & ui);
	void advance();
	void draw(const Interface & ui);
	void handleCollisions();
	void cleanUp();


};
#endif /* GAME_H */
