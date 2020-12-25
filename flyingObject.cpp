#include "flyingObject.h"
#include "velocity.h"
#include <cmath>

void flyingObject::kill()
{
	alive = false;
}

void flyingObject::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
}