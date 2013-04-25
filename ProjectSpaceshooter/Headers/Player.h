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
	~Player(){}
	void setShip(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager)  {Ship::setShip(objectTemplate, weapon, _sceneMenager);}
	GameObjectType getType() {
		return GameObjectType::player;
	}
	Ogre::SceneNode * createCameraNode();
	void detachCamera();
	void attachCamera(Ogre::Camera * cam);
private:
	Ogre::SceneNode * mCameraNode;
	Ogre::Camera * my_cam;
};

Ogre::SceneNode * Player::createCameraNode()
{
	mCameraNode = mNode->createChildSceneNode("CameraNode");
	return mCameraNode;
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


