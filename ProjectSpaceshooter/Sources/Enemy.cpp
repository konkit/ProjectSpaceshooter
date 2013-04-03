#include "stdafx.h"
#include "Enemy.h"


EnemyPrefab::EnemyPrefab(unsigned prefabID) 
	: mEnemyPrefabID(prefabID), mMyAI(AI_TYPE::fighter), mResistance(100), mWeaponPrefabID() 
{
}

EnemyPrefab::~EnemyPrefab(void)
{
}

EnemyObject::EnemyObject( EnemyPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager)
	: GameObject(objectTemplate->getMeshName(), _sceneMenager), mResistance(objectTemplate->getResistance())
{}

EnemyObject::~EnemyObject()
{

}
