#pragma once

class PhysicsComponent
{
public:
	PhysicsComponent() : velocityX(0.0), velocityY(0.0), velocityZ(0.0)	{

	}

	void setVelocity(float nx, float ny, float nz)	{
		velocityX = nx;
		velocityY = ny;
		velocityZ = nz;
	}

	//do czasu zrobienia funkcji getVector to bedzie public
	float velocityX, velocityY, velocityZ;

private:

	
};