#pragma once

class TransformComponent
{
public:
	TransformComponent() : x(0.0), y(0.0), z(0.0)
	{	}

	void move(float nx, float ny, float nz) {
		x+=nx;
		y+=ny;
		z+=nz;
	}

	void setPosition(float nx, float ny, float nz)	{
		x = nx;
		y = ny;
		z = nz;
	}

	//jak sie zrobi wektory zamiast luŸnych floatów, to to bedzie lepsze
	float getX()	{
		return x;
	}

	float getY()	{
		return y;
	}

	float getZ()	{
		return z;
	}





private:
	float x, y, z;
};