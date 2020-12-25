#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float x;
	float y;

public:

	Velocity()
	{
		x = 0;
		y = 0;
	}
	Velocity(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float getDx();
	float getDy();

	void setDx(float x);
	void setDy(float y);
};
#endif 
