/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/
#include "game.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ship.h"
#include "bullet.h"
#include "rocks.h"
#include <limits>
#include <algorithm>
#include <list>
#include <vector>
#include <cmath>
#define OFF_SCREEN 5
using namespace std;

Game::Game (Point tl, Point br) : topLeft(tl), bottomRight(br)
{
	for (int i = 0; i < ROCK_NUMBER; i++)
	{
		LargeRock* largeAsteroid;
		largeAsteroid = new LargeRock();
		rocks.push_back(largeAsteroid);
	}
}

void Game :: advance()
{
	advanceBullets();
	advanceShip();
	advanceRocks();
	handleCollisions();
	cleanUp();

}

void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive                                                      
	for (vector <Bullet*> ::iterator it = bullets.begin(); it != bullets.end(); it++)
	{
		(*it)->advance();
		(*it)->killBullet();

		if ((*it)->getPoint().getX() > 200 || (*it)->getPoint().getX() < -200)
		{
			(*it)->setX((*it)->getPoint().getX() * -1);
		}

		if ((*it)->getPoint().getY() > 200 || (*it)->getPoint().getY() < -200)
		{
			(*it)->setY((*it)->getPoint().getY() * -1);
		}
	}
}

void Game::advanceShip()
{   //Moving the ship as it is alive
	if (ship.isAlive())
	{
		ship.inertia();
		ship.advance();
	}
	if (ship.getPoint().getX() > 200 || ship.getPoint().getX() < -200)
	{
		ship.setX(ship.getPoint().getX() * -1);
	}

	if (ship.getPoint().getY() > 200 || ship.getPoint().getY() < -200)
	{
		ship.setY(ship.getPoint().getY() * -1);
	}
}

void Game::advanceRocks()
{
	// Move each of the rocks forward if it is alive                                                      
	for (list <Rock*> ::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		(*it)->advance();

		if ((*it)->getPoint().getX() > 220 || (*it)->getPoint().getX() < -220)
		{
			(*it)->setX((*it)->getPoint().getX() * -1);
		}

		if ((*it)->getPoint().getY() > 220 || (*it)->getPoint().getY() < -220)
		{
			(*it)->setY((*it)->getPoint().getY() * -1);
		}
	}
}

void Game::handleInput(const Interface &ui)
{
	// Change the direction of the rifle                                                                    
	if (ui.isLeft())
	{
		ship.spinningLeft();
	}

	if (ui.isRight())
	{
		ship.spinningRight();
	}

	if (ui.isUp())
	{
		ship.thrustShip();
	}

	// Check for Spacebar                                                                                  
	if (ui.isSpace())
	{
		Bullet* newBullet = new Bullet(); 
		newBullet->fire(ship.getPoint(), ship.rotation());

		bullets.push_back(newBullet);
	}
}

bool Game::isOnScreen(const Point &point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN
		&& point.getY() <= topLeft.getY() + OFF_SCREEN);
}

void Game::draw(const Interface &ui) 
{
	if (ship.isAlive())
	{
		ship.draw();
	}
	for (list <Rock*> ::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		(*it)->draw();
	}


	// draw the bullets, if they are alive                                                                  
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
		{
			bullets[i]->draw();
		}
	}
}

void Game::handleCollisions()
{
	for (list <Rock*> ::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		float gettingClose = getClosestDistance(**it, ship);

		if (gettingClose < (*it)->getSize() + ship.getSize() && ship.isAlive())
		{
			(*it)->kill();
			ship.kill();
			(*it)->breakRock(rocks);
		}

		for (vector <Bullet*> ::iterator iy = bullets.begin(); iy != bullets.end(); iy++)
		{
			float closer = getClosestDistance(**iy, **it);

			if (closer < (*iy)->getSize() + (*it)->getSize())
			{
				(*iy)->kill();
				(*it)->kill();
				(*it)->breakRock(rocks);
			}
		}
	}
}

void Game::cleanUp()
{
	vector<Bullet*>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet * bullet = *bulletIt;
		                                                                     

		if (!bullet->isAlive())
		{
			                                                               
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++;                                                                          
		}
	}

	list<Rock*>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		Rock* rock = *rockIt;

		if (!rock->isAlive())
		{
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++;
		}
	}
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const flyingObject &obj1, const flyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

