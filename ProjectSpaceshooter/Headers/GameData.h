#pragma once
#include "GameObject.h"




//Class which stores gameobjects and all data required by systems to do their job
class GameData
{
public:
	Ogre::SceneNode* shipNode;
	GameData();
	~GameData();
	bool changeFlag;

	GameObject* getPlayer()	
	{
		return &mPlayer;
	}

private:
	//All GameObjects

	Ogre::SceneManager* mSceneMgr;

	GameObjectsCollection<GameObject> mEnemyCollection;
	GameObjectsCollection<GameObject> mBulletCollection;
	GameObjectsCollection<GameObject> mStaticCollection;
//	GameObjectsCollection mPhysicCollection;  there will be physics object ex. explosion sphere
	GameObject mPlayer;

};
