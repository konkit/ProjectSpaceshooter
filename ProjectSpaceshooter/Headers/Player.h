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
		: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate,weapon, _sceneMenager) {}
	~Player(){}
	void setShip(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager)  {Ship::setShip(objectTemplate, weapon, _sceneMenager);}
};

