#pragma once
#include "GameObject.h"
#include "Prefabs.h"
#include "Enemy.h"
#include "Player.h"
#include "Core.h"

#include "BaseCollection.h"
#include "EnemyAndShipPrefabCollection.h"
#include "BulletCollection.h"
#include "LevelDescription.h"
#include "Exceptions.h"
#include <string>

#include "MessageConsole.h"



enum class GAME_STATES
{
	PLAY,
	PAUSE,
	HANGAR,
	LEVEL_BUILDER,
	GAME_OVER,
};

/** Class which stores gameobjects and all data required by systems to do their job
  * In other words - class storing prefabs -
  * - for quick instantiation of already configured objects
  *
  * @author Zygi
  */
struct GameObjectTemplates
{
	GameCollection<ShipPrefab> enemyPrefabCollection;
};

/** Structure storage SceneManagers for each GameState
  *
  * @author Zygi
  */
struct StateScenesManager_Struct
{
	Ogre::SceneManager * playSceneManager;
	Ogre::SceneManager * pauseSceneManager;
	Ogre::SceneManager * hangarSceneManager;
};

struct CameraManager_Struct
{
	Ogre::Camera * playCamera;
	Ogre::Camera * pauseCamera;
	Ogre::Camera * hangarSceneCamera;
	Ogre::Camera * gameOverCamera;
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
	Player* getPlayer()	{return mPlayer;}

	/** 
	* Create player based on ship prefab
	*
	* @return Player &
	* @param Ship prefab which is used to create player ship
	* @author Zyga
	*/
	Player * createPlayerFromPrefab(unsigned prefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		const ShipPrefab * ship = mEnemyCollection.getPrefab(prefabID);
		const WeaponPrefab * weapon = mEnemyCollection.getWeaponPrefab(ship->getWeaponPrefabID());
		mPlayer = new Player(ship, weapon, getSceneManagerFor(state));
		return mPlayer;
	}
	void destroyPlayer();
	bool isSetPauseFlag() { return changeFlags.changeToPause;}
	bool isSetPlayFlag()  { return changeFlags.changeToPlay;}
	bool isSetHangarFlag(){ return changeFlags.changeToHangar;}
	bool isSetMenuFlag()  { return changeFlags.changeToMenu;}
	bool isSetLevelBuilderFlag() {return changeFlags.changeToBuilder;}

	void setChangeToPause(bool flag) {changeFlags.changeToPause  = flag;} 
	void setChangeToPlay (bool flag) {changeFlags.changeToPlay   = flag;} 
	void setChangeToMenu (bool flag) {changeFlags.changeToMenu   = flag;} 
	void setChangeToHangar(bool flag){changeFlags.changeToHangar = flag;}
	void setChangeToLevelBuilder(bool flag){changeFlags.changeToBuilder = flag;}
	
	Ogre::SceneManager * getSceneManagerFor(GAME_STATES gameState);
	void setSceneMenagerFor(GAME_STATES gameState, Ogre::SceneManager * sceneManagerForState);

	LevelDescription & createLevelDescription() 
	{
		currentLevelDecription = new LevelDescription();
		return *currentLevelDecription;
	}
	LevelDescription & getLevelDescription() 
	{
		return *currentLevelDecription;
	}
	void removeLevelDescription()
	{
		delete currentLevelDecription;
	}

	//BulletCollection& getBullets()	{
	BaseCollection<BulletPrefab, Bullet>& getBullets() {return mBulletCollection;}
	//EnemyCollection& getEnemys()
	EnemyAndShipPrefabsCollections& getEnemies() {return mEnemyCollection;}
	BaseCollection<EffectPrefab, EffectObject>& getEffects() {return mEffectsCollection;}
	BaseCollection<StaticPrefab, StaticObject>& getStatics()	{
		return mStaticCollection;
	}


	Core& getCore() { return *theCore; }

	EnemyObject * instantiateEnemy(unsigned prefabID ,AI_TYPE myAi, GAME_STATES state = GAME_STATES::PLAY)
	{
			return mEnemyCollection.instantiateEnemy(prefabID, myAi, getSceneManagerFor(state));
	}
	/**
	* 
	*
	* @return Bullet *
	* @param unsigned prefabID
	* @param GAME_STATES state
	* @author Zyga
	*/
	Bullet * instantiateBullet(unsigned prefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		return mBulletCollection.instantiate(prefabID, getSceneManagerFor(state));
	}
	void addShipPrefab(const ShipPrefab & _enemyPrefab);
	void addBulletPrefab(const BulletPrefab & _bulletPrefab);
	void addStaticPrefab(const StaticPrefab & _staticPrefab);
	void addEffectPrefab(const EffectPrefab & _effectPrefab);
	void addWeaponPrefab(const WeaponPrefab & _weaponPrefab);
	void addPrefab(PREFAB_TYPE prefabType, Prefab & prefab );
	const WeaponPrefab * getWeaponPrefab(unsigned prefabId);
	
	class ColidingObjectsIterator
	{
	public:
		ColidingObjectsIterator() : activeIterator(iterator::Player){;}
		bool hasNext();
		GameObject_WithCollider * getNext();
		
		Player * getPlayer() const { return player; }
		void setPlayer(Player * val) { player = val; }
		void setEnemyIterator(const GameCollectionIterator<EnemyObject> & val) { enemyIT = val; }
		void setBulletIterator(const GameCollectionIterator<Bullet> & val) { bulletIT = val; }
		void setEffectIterator(const GameCollectionIterator<EffectObject> & val) { effectIT = val; }
		void setStaticIterator(const GameCollectionIterator<StaticObject> & val) { staticIT = val; }
		void skipPlayer()
		{
			if (activeIterator == iterator::Player)
				moveToNextIterator();
		}
		
		GameObjectType getPointedObjectType();
		GameCollectionIterator<EnemyObject>	&	getEnemyIT()  { return enemyIT; }
		GameCollectionIterator<Bullet>		&	getBulletIT() { return bulletIT; }
		GameCollectionIterator<StaticObject>&	getStaticIT() { return staticIT; }
		GameCollectionIterator<EffectObject>&	getEffectIT() { return effectIT; }

	private:
		enum class iterator
		{
			Player,
			Enemy,
			Bullet,
			Static,
			Effect,
			EMPTY
		} activeIterator;
		
		void moveToNextIterator();
		Player * player;

		GameCollectionIterator<EnemyObject> enemyIT;
		GameCollectionIterator<Bullet> bulletIT;
		GameCollectionIterator<EffectObject> effectIT;
		GameCollectionIterator<StaticObject> staticIT;
		GameObjectType lastElementType;

	};

	ColidingObjectsIterator getColidingObjectsIterator();
	StaticObject * instantiateStatic( int prefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		return mStaticCollection.instantiate(prefabID, getSceneManagerFor(state));
	}
	EffectObject * instantiateEffect( int prefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		return mEffectsCollection.instantiate(prefabID, getSceneManagerFor(state));
	}
	Core * createCore(int staticPrefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		const StaticPrefab * staticPref = mStaticCollection.getPrefab(staticPrefabID);
		theCore = new Core(staticPref, getSceneManagerFor(state));
		mStaticCollection.addObjectToCollection(theCore);
		return theCore;
	}
	Ogre::Camera * getCameraFor(GAME_STATES state)
	{
		switch (state)
		{
		case GAME_STATES::PLAY:
			return mCamerasManager.playCamera;
		case GAME_STATES::PAUSE:
			return mCamerasManager.pauseCamera;
		case GAME_STATES::HANGAR:
			break;
		case GAME_STATES::LEVEL_BUILDER:
			break;
		case GAME_STATES::GAME_OVER:
			return mCamerasManager.gameOverCamera;
		default:
			break;
		}
		return NULL;
	}

	void setCameraFor(GAME_STATES gameState, Ogre::Camera * camera);
	void removeGameObject( GameObject_WithCollider * removedObject );
	void removeGameObject( ColidingObjectsIterator & removedObjectIterator );
	bool isPlayerDead();
	bool isCoreDead();
	void setCountOfPrefabs( PREFAB_TYPE prefabType, unsigned count );
	void clearPlayData();
	void initializeDataPulls();

	//Message console in GUI
	MessageConsole& getMessageConsole()	{
		return mMessageConsole;
	}

private:
	struct changeFlagsStruct
	{
	bool changeToPause;
	bool changeToHangar;
	bool changeToPlay;
	bool changeToMenu;
	bool changeToBuilder;
	} changeFlags;
	//All GameObjects
	
	EnemyAndShipPrefabsCollections mEnemyCollection;
	BulletCollection mBulletCollection;
	BaseCollection<EffectPrefab, EffectObject> mEffectsCollection;
	BaseCollection<StaticPrefab, StaticObject> mStaticCollection;

	Player* mPlayer;
	Core * theCore;
	GameObjectTemplates mPrefabCollections;
	StateScenesManager_Struct mStateScenesManager;
	CameraManager_Struct mCamerasManager;
	LevelDescription * currentLevelDecription;

	//GUI data
	MessageConsole mMessageConsole;
};
