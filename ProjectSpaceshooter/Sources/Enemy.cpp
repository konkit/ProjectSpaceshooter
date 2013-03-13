#include "stdafx.h"
#include "Enemy.h"


EnemyPrefab::EnemyPrefab(string name ) 
	: mName(), mMyAI(AI_TYPE::fighter), resistance(100), mWeaponName() 
{
}

EnemyPrefab::~EnemyPrefab(void)
{
}

EnemyObject::EnemyObject( EnemyPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager)
	: GameObject(), mResistance(objectTemplate->getResistance())
{
	mGraphicsComponent.initGraphicComponent(objectTemplate->getMeshName(), _sceneMenager);
}

EnemyObject::~EnemyObject()
{

}
