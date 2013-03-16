#pragma once
#include "GameObject.h"
#include "Enemy.h"

#include "BulletCollection.h"
#include "EnemyCollection.h"
#include "LevelDescription.h"


enum class GAME_STATES
{
	PLAY,
	PAUSE,
	HANGAR
};

/** Class which stores gameobjects and all data required by systems to do their job
  * In other words - class storing prefabs -
  * - for quick instantiation of already configured objects
  *
  * @author Zygi
  */
struct GameObjectTemplates
{
	GameCollection<EnemyPrefab> enemyPrefabCollection;
};

/** Structure storing SceneManagers for each GameState
  *
  * @author Zygi
  */
struct StateScenesManager_Struct
{
	Ogre::SceneManager * playSceneManager;
	Ogre::SceneManager * pauseSceneManager;
	Ogre::SceneManager * hangarSceneManager;
};

/** GameData class
  * Stores all information about GameWorld
  * including GameObjects (Enemies, Bullets, etc)
  *
  * @author 
  */
class GameData
{
public:
	Ogre::SceneNode* shipNode;
	Ogre::Entity* bulletEntity;
		
	GameData();
	~GameData();

	/** Accessor functions */
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
	
	Ogre::SceneManager * getSceneManagerFor(GAME_STATES gameState);
	void setSceneMenagerFor(GAME_STATES gameState, Ogre::SceneManager * sceneManagerForState);

	LevelDescription & getLevelDescription() {return currentLevelDecription;}

	BulletCollection& getBullets()	{
		return mBulletCollection;
	}

	EnemyCollection& getEnemys()
	{
		return mEnemyCollection;
	}
	
private:
	struct changeFlagsStruct
	{
	bool changeToPause;
	bool changeToHangar;
	bool changeToPlay;
	bool changeToMenu;
	} changeFlags;
	//All GameObjects

	EnemyCollection mEnemyCollection;
	BulletCollection mBulletCollection;
	GameCollection<GameObject> mStaticCollection;
//	GameObjectsCollection mPhysicCollection;  there will be physics object ex. explosion sphere
	GameObject mPlayer;
	GameObjectTemplates mPrefabCollections;
	StateScenesManager_Struct mStateScenesManager;
	LevelDescription currentLevelDecription;
};
