#ifndef flyingObject_h
#define flyingObject_h
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "flyingObject.h"

class flyingObject
{
protected:
	Point point;
	Velocity velocity;
	bool alive;
	int size;
	
public:
	flyingObject()
	{
		alive = true;
	}

	Point getPoint() const
	{
		return point;
	}
	
	Velocity getVelocity() const
	{
		return velocity;
	}

	bool isAlive()
	{
		return alive;
	}

	void setVelocity(Velocity velocity)
	{
		this->velocity = velocity;
	}

	void setPoint(Point point)
	{
		this->point = point;
	}

	void setX(float x)
	{
		point.setX(x);
	}

	void setY(float y)
	{
		point.setY(y);
	}

	int getSize()
	{
		return size;
	}

	void kill();
	void advance();
	virtual void draw() = 0;

};
#endif
