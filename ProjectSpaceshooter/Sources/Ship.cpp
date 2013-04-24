#include "Ship.h"

using namespace std;
Ship::Ship()
	: GameObject(), GameObject_Movable(), GameObject_WithHealth()
{
}

Ship::Ship(const ShipPrefab * objectTemplate, const WeaponPrefab * weaponPrefab, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), GameObject_WithHealth(objectTemplate, _sceneMenager), GameObject_Movable(objectTemplate, _sceneMenager), mWeapon(weaponPrefab)
{
}

Ship::~Ship()
{
}
