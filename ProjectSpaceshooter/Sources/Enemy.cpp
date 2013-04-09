#include "stdafx.h"
#include "Enemy.h"

ShipPrefab::~ShipPrefab(void)
{
}

EnemyObject::EnemyObject( ShipPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager)
	: GameObject(objectTemplate->getMeshName(), _sceneMenager), mResistance(objectTemplate->getResistance())
{}

EnemyObject::~EnemyObject()
{

}
