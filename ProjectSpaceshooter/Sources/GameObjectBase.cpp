#pragma once

#include "stdafx.h"
#include "GameObjectBase.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

GameObjectBase::GameObjectBase(void)
{
	mBulletCollection = new GameObjectsCollection(GameObjectType::bulletObject);
	mStaticCollection = new GameObjectsCollection(GameObjectType::staticObject);
	mEnemyCollection = new GameObjectsCollection(GameObjectType::enemyObject);
	mPlayer = GameObjectFactory::createGameObject(GameObjectType::player);
}


GameObjectBase::~GameObjectBase(void)
{
}
