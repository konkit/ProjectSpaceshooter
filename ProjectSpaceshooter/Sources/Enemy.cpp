#include "stdafx.h"
#include "Enemy.h"



EnemyObject::~EnemyObject()
{

}

EnemyObject::EnemyObject( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon,Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate, weapon, _sceneMenager), myAI(AI_TYPE::fighter)
{
	mPhysicsComponent.setMaxVelocityValue( objectTemplate->getMaxVelocity() );
	mPhysicsComponent.setAccelerationValue( objectTemplate->getMaxAcceleration() );
}


EnemyObject::EnemyObject( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, AI_TYPE _myAi, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate, weapon, _sceneMenager), myAI(_myAi)
{
	mPhysicsComponent.setMaxVelocityValue( objectTemplate->getMaxVelocity() );
	mPhysicsComponent.setAccelerationValue( objectTemplate->getMaxAcceleration() );
}
