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


#include "GUI_MessageConsole.h"



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
  * @author Zyga
  */
struct GameObjectTemplates
{
	GameCollection<ShipPrefab> enemyPrefabCollection;
};



/** Structure storage SceneManagers for each GameState
  *
  * @author Zyga
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

struct HangarManipulator
{
	unsigned activeShip;
	unsigned shipPrefab;
	bool moveToNext;
	bool moveToPrev;
	bool acceptModel;
	HangarManipulator() : activeShip(0), moveToNext(false), moveToPrev(false), acceptModel(false){}
};



/** GameData class
  * Stores all information about GameWorld
  * including GameObjects (Enemies, Bullets, etc)
  *
  * @author Zyga
  */
class GameData
{
public:
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
	Player * createPlayerFromPrefab(unsigned prefabID, GAME_STATES state = GAME_STATES::PLAY)	{
		const ShipPrefab * ship = mEnemyCollection.getPrefab(prefabID);
		const WeaponPrefab * weapon = mEnemyCollection.getWeaponPrefab(ship->getWeaponPrefabID());
		mPlayer = new Player(ship, weapon, getSceneManagerFor(state));
		return mPlayer;
	}

	void destroyPlayer();

	/** Flags getters */
	bool isSetPauseFlag() { return changeFlags.changeToPause;}
	bool isSetPlayFlag()  { return changeFlags.changeToPlay;}
	bool isSetHangarFlag(){ return changeFlags.changeToHangar;}
	bool isSetMenuFlag()  { return changeFlags.changeToMenu;}
	bool isSetLevelBuilderFlag() {return changeFlags.changeToBuilder;}

	/** Flags setters */
	void setChangeToPause(bool flag) {changeFlags.changeToPause  = flag;} 
	void setChangeToPlay (bool flag) {changeFlags.changeToPlay   = flag;} 
	void setChangeToMenu (bool flag) {changeFlags.changeToMenu   = flag;} 
	void setChangeToHangar(bool flag){changeFlags.changeToHangar = flag;}
	void setChangeToLevelBuilder(bool flag){changeFlags.changeToBuilder = flag;}
	
	/** Returns scene manager associated with particular gamestate */
	Ogre::SceneManager * getSceneManagerFor(GAME_STATES gameState);

	/** Saves particular scene manager as associated with given game state */
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
	
	void spawnEnemiesInCurrentLevel(unsigned currentTime) {
		currentLevelDecription->spawn(*this, currentTime);
	}


	void removeLevelDescription()
	{
		delete currentLevelDecription;
	}

	/** Collections getters */
	BaseCollection<BulletPrefab, Bullet>& getBullets() {return mBulletCollection;}
	EnemyAndShipPrefabsCollections& getEnemies() {return mEnemyCollection;}
	BaseCollection<EffectPrefab, EffectObject>& getEffects() {return mEffectsCollection;}
	BaseCollection<StaticPrefab, StaticObject>& getStatics()	{
		return mStaticCollection;
	}

	/** Returns the Core */
	Core& getCore() { return *theCore; }

	/**
	* Method which creates new Enemy in collection
	* it also returns this newly created enemy so it can be further modified
	*
	* @return EnemyObject *
	* @param unsigned prefabID
	* @param AI_TYPE myAi - type of AI (attacker, defender, etc)
	* @param GAME_STATES state
	* @author Zyga
	*/
	EnemyObject * instantiateEnemy(unsigned prefabID ,AI_TYPE myAi, GAME_STATES state = GAME_STATES::PLAY)
	{
			return mEnemyCollection.instantiateEnemy(prefabID, myAi, getSceneManagerFor(state));
	}

	/**
	* Method which creates new Bullet in collection
	* it also returns this newly created bullet so it can be further modified
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

	/** Methods which adds new prefabs */
	void addShipPrefab(const ShipPrefab & _enemyPrefab);
	void addBulletPrefab(const BulletPrefab & _bulletPrefab);
	void addStaticPrefab(const StaticPrefab & _staticPrefab);
	void addEffectPrefab(const EffectPrefab & _effectPrefab);
	void addWeaponPrefab(const WeaponPrefab & _weaponPrefab);
	void addPrefab(PREFAB_TYPE prefabType, Prefab & prefab );

	/** returns weapon prefab with given ID */
	const WeaponPrefab * getWeaponPrefab(unsigned prefabId);
	
	/** The iterator for colliding objects */
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

	/** Creates new static object */
	StaticObject * instantiateStatic( int prefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		return mStaticCollection.instantiate(prefabID, getSceneManagerFor(state));
	}

	/** Creates new effect object */
	EffectObject * instantiateEffect( int prefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		return mEffectsCollection.instantiate(prefabID, getSceneManagerFor(state));
	}

	/** Creates new core */
	Core * createCore(int staticPrefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		const StaticPrefab * staticPref = mStaticCollection.getPrefab(staticPrefabID);
		theCore = new Core(staticPref, getSceneManagerFor(state));
		mStaticCollection.addObjectToCollection(theCore);
		return theCore;
	}

	/** Returns camera for particular game state  */
	Ogre::Camera * getCameraFor(GAME_STATES state)
	{
		switch (state)
		{
		case GAME_STATES::PLAY:
			return mCamerasManager.playCamera;
		case GAME_STATES::PAUSE:
			return mCamerasManager.pauseCamera;
		case GAME_STATES::HANGAR:
			return mCamerasManager.hangarSceneCamera;
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
	void initializeDataPools();
	HangarManipulator & getHangarManipulator() { return mHangarManipulator; }
	void setHangarManipulator(HangarManipulator val) { mHangarManipulator = val; }
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
	HangarManipulator mHangarManipulator;
	//GUI data
	MessageConsole mMessageConsole;

	//score of player
	int score;
};
