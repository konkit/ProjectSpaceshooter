#pragma once

#include "GameObject.h"

/** 
  *
  * @author konkit
  */
class BulletPrefab
{
	//Ja to ogarnê, spoko ;P - Konkit
};

/** Class of Bullet gameobject
  * 
  * @author konkit 
  */
class Bullet : public GameObject	{

public:
	Bullet() : GameObject(){}
	Bullet(std::string meshName, Ogre::SceneManager* sceneMgr) : GameObject(meshName, sceneMgr)	{}

private:

};
