#pragma once

#include "GameObject.h"


class BulletPrefab;

class Bullet : public GameObject	{

public:
	Bullet() : GameObject(){}
	Bullet(std::string meshName) : GameObject(), meshName(meshName)	{
		
	}

	void setMesh(Ogre::SceneNode* newNode)	{
		mGraphicsComponent.initNode(newNode);
	}


private:
	std::string meshName;
};
