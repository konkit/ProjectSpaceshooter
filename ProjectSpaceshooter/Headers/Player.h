#pragma once
#include "Ship.h"


/** Player class
  * Gameobject representing player's spaceship
  *
  * @author konkit
  */

class Player : public Ship
{
public:
	Player() {;}
	Player(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager)
		: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate,weapon, _sceneMenager)
	{
		createCameraNode();
	}
	virtual ~Player(){}
	void setShip(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager)  {Ship::setShip(objectTemplate, weapon, _sceneMenager);}
	GameObjectType getType() {
		return GameObjectType::player;
	}



void Player::attachCamera( Ogre::Camera * cam )
{
	my_cam = cam;
	mCameraNode->attachObject(cam);
}

void Player::detachCamera()
{
	mCameraNode->detachObject(my_cam);
}

Ogre::SceneNode * getCameraNode() 
{
	return mCameraNode;
}


private:
	Ogre::SceneNode * Player::createCameraNode()
	{
		mCameraNode = mNode->createChildSceneNode("My_Camera");
		return mCameraNode;
	}




	Ogre::SceneNode * mCameraNode;

	Ogre::Camera * my_cam;
};
