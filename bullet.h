#ifndef bullet_h
#define bullet_h
#define BULLET_SPEED 5
#define BULLET_LIFE 40
#include "flyingObject.h"

class Bullet : public flyingObject
{
private:
	int bullet = 0;

public:
	Bullet()
	{
		alive = true;
	}
	void draw();
	void fire(Point point, float angle);
	void killBullet()
	{

	}
};
#endif