#pragma once
#include "GameObjectsCollection.h"
#include "GameObject.h"
class GameObjectBase //TODO Required change name
{
public:
	GameObjectBase(void);
	virtual ~GameObjectBase(void);
private:
	GameObjectsCollection* mEnemyCollection;
	GameObjectsCollection* mBulletCollection;
	GameObjectsCollection* mStaticCollection;
//	GameObjectsCollection mPhysicCollection;  there will be physics object ex. explosion sphere
	GameObject* mPlayer;
};

