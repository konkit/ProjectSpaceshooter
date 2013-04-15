#include "stdafx.h"
#include "Enemy.h"

ShipPrefab::~ShipPrefab(void)
{
}

EnemyObject::EnemyObject( ShipPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager)
	: mHealthComponent(), mWeapon(objectTemplate->getWeaponPrefabID())
{
	
	mHealthComponent.setResistance(objectTemplate->getResistance());
	mHealthComponent.setMaxHealth(objectTemplate->getMaxHealth());
}
EnemyObject::~EnemyObject()
{

}
