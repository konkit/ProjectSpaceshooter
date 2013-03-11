#pragma once

#include "GameObject.h"


class Bullet : public GameObject	{

public:
	Bullet() : GameObject()	{
		
	}

	void setMesh(Ogre::Entity* entity, Ogre::SceneNode* newNode)	{
		mGraphicsComponent.initNode(newNode);
		mGraphicsComponent.getNode()->attachObject(entity);
	}


private:

};
