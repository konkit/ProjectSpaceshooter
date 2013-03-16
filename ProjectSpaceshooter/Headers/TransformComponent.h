#pragma once



class TransformComponent
{
public:
	TransformComponent() : pos(0.0, 0.0, 0.0), angle(0.0)
	{	}

	//nPos.z - forward direction relative to object
	//nPos.x - right direction relative to object
	void move(Ogre::Vector3 nPos) {
		pos.x += nPos.z * sin(angle) + nPos.x * cos(angle);
		pos.z += nPos.z * cos(angle) - nPos.x * sin(angle);
	}

	void rotate(float rotVelocity)	{
		angle += rotVelocity;
	}


	void setPosition(Ogre::Vector3 newPos)	{
		pos = newPos;
	}

	Ogre::Vector3 getPosition()	{
		return pos;
	}


	void setAngle(float nangle)	{
		angle = nangle;
	}

	float getAngle()	{
		return angle;
	}






private:
	Ogre::Vector3 pos;
	float angle;
};