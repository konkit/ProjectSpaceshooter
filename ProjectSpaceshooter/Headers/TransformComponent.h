#pragma once

class TransformComponent
{
public:
	TransformComponent() : x(0.0), y(0.0), z(0.0), angle(0.0)
	{	}

	void move(float nx, float ny, float nz) {
		x += nz * sin(angle) + nx * cos(angle);
		z += nz * cos(angle) - nx * sin(angle);
	}

	void rotate(float rotVelocity)	{
		angle += rotVelocity;
	}


	void setPosition(float nx, float ny, float nz)	{
		x = nx;
		y = ny;
		z = nz;
	}

	void setAngle(float nangle)	{
		angle = nangle;
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

	float getAngle()	{
		return angle;
	}






private:
	float x, y, z;
	float angle;
};