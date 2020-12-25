#include "bullet.h"
#include "velocity.h"
#include "point.h"
#include "game.h"
#include <iostream>
#include "uiDraw.h"
#include <cmath>
#define M_PI 3.14
#define BULLET_SPEED 10.0
#define DEGREES 90.0

void Bullet::draw()
{
	drawDot(point);
}

void Bullet::fire(Point point, float angle)
{
	this->point = point;
	velocity.setDx(BULLET_SPEED * (cos(M_PI / 180.0 * (angle + DEGREES))));
	velocity.setDy(BULLET_SPEED * (sin(M_PI / 180.0 * (angle + DEGREES))));
}
