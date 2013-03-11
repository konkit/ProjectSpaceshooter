#pragma once

#include "GameObject.h"


class Bullet : public GameObject	{

public:
	Bullet() : GameObject(){}
	Bullet(std::string meshName) : GameObject(), meshName(meshName)	{
		
	}

	void setMesh(Ogre::Entity* entity)	{
		
	}


private:
	std::string meshName;
};
