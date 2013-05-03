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

GameObjectType Ship::getType()
{
	throw std::exception("The method or operation is not implemented.");
}

bool Ship::receiveDamage( unsigned int damages, Vector3 fromDirection /*= Vector3(0,0,0 ) */ )
{
	bool isDead = GameObject_WithHealth::receiveDamage(damages, fromDirection);
	if (!isDead)
	{
		Vector3 recoil = getPosition() - fromDirection;
			recoil.normalise();
			recoil = recoil * (damages * 10) * (-1);
			addRecoilVectorToCurrentVelocity(recoil);
	}
	return isDead;
}
