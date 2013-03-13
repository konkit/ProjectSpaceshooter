#pragma once
#include "GameObject.h"
#include "Enemy.h"

#include "BulletCollection.h"



//Class which stores gameobjects and all data required by systems to do their job
struct GameObjectTemplates
{
	GameObjectsCollection<EnemyPrefab> enemyPrefabCollection;
};

class GameData
{
public:
	Ogre::SceneNode* shipNode;
	Ogre::Entity* bulletEntity;

	
	GameData();
	~GameData();

	GameObject* getPlayer()	
	{
		return &mPlayer;
	}
	bool isSetPauseFlag() { return changeFlags.changeToPause;}
	bool isSetPlayFlag()  { return changeFlags.changeToPlay;}
	bool isSetHangarFlag(){ return changeFlags.changeToHangar;}
	bool isSetMenuFlag()  { return changeFlags.changeToMenu;}

	void setChangeToPause(bool flag) {changeFlags.changeToPause  = flag;} 
	void setChangeToPlay (bool flag) {changeFlags.changeToPlay   = flag;} 
	void setChangeToMenu (bool flag) {changeFlags.changeToMenu   = flag;} 
	void setChangeToHangar(bool flag){changeFlags.changeToHangar = flag;}


	BulletCollection& getBullets()	{
		return mBulletCollection;
	}
	void initObjectsTemplates();
	
private:
	struct changeFlagsStruct
	{
	bool changeToPause;
	bool changeToHangar;
	bool changeToPlay;
	bool changeToMenu;
	} changeFlags;
	//All GameObjects

	GameObjectsCollection<GameObject> mEnemyCollection;
	//GameObjectsCollection<GameObject> mBulletCollection;
	BulletCollection mBulletCollection;
	GameObjectsCollection<GameObject> mStaticCollection;
//	GameObjectsCollection mPhysicCollection;  there will be physics object ex. explosion sphere
	GameObject mPlayer;
	GameObjectTemplates mPrefabCollections;
};
