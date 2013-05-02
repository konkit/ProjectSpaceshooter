#include "stdafx.h"
#include "Enemy.h"



EnemyObject::~EnemyObject()
{

}

EnemyObject::EnemyObject( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon,Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate, weapon, _sceneMenager), myAI(AI_TYPE::fighter)
{
	mPhysicsComponent.setFromPrefab(objectTemplate);
}


EnemyObject::EnemyObject( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, AI_TYPE _myAi, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate, weapon, _sceneMenager), myAI(_myAi)
{
	mPhysicsComponent.setFromPrefab(objectTemplate);
}
