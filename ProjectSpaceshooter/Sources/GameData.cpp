#pragma once

#include "stdafx.h"
#include "GameData.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

GameData::GameData(void)
{
	changeFlag = false;
	mBulletCollection = new GameObjectsCollection(GameObjectType::bulletObject);
	mStaticCollection = new GameObjectsCollection(GameObjectType::staticObject);
	mEnemyCollection = new GameObjectsCollection(GameObjectType::enemyObject);
	mPlayer = GameObjectFactory::createGameObject(GameObjectType::player);
}


GameData::~GameData(void)
{
}


