#include "stdafx.h"
#include "Enemy.h"



EnemyObject::~EnemyObject()
{

}

EnemyObject::EnemyObject( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon,Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate, weapon, _sceneMenager)
{
	mPhysicsComponent.setFromPrefab(objectTemplate);
	mAIComponent.setType(AI_TYPE::fighter);
}


EnemyObject::EnemyObject( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, AI_TYPE _myAi, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate, weapon, _sceneMenager)
{
	mPhysicsComponent.setFromPrefab(objectTemplate);
	mAIComponent.setType(_myAi);
}
