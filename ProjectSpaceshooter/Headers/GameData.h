#pragma once
#include "GameObject.h"
#include "Prefabs.h"
#include "Enemy.h"
#include "Player.h"
#include "Core.h"

#include "BaseCollection.h"
#include "LevelDescription.h"
#include "Exceptions.h"



enum class GAME_STATES
{
	PLAY,
	PAUSE,
	HANGAR,
	LEVEL_BUILDER
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

	//PROWIZORKA - to bêdzie chyba te¿ jakoœ wczytywane z pliku nie ?
	Core theCore;
		
	GameData();
	~GameData();

	/** Accessor functions */
	Player* getPlayer()	{return &mPlayer;}

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
		mPlayer.setShip(ship, weapon, getSceneManagerFor(state));
		return &mPlayer;
	}

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

	LevelDescription & getLevelDescription() {return currentLevelDecription;}

	//BulletCollection& getBullets()	{
	BaseCollection<BulletPrefab, Bullet>& getBullets() {return mBulletCollection;}
	//EnemyCollection& getEnemys()
	EnemyAndShipPrefabsCollections& getEnemies() {return mEnemyCollection;}
	BaseCollection<EffectPrefab, EffectObject>& getEffects() {return mEffectsCollection;}

	Core& getCore() { return theCore; }

	EnemyObject * instantiateEnemy(unsigned prefabID ,AI_TYPE myAi, GAME_STATES state = GAME_STATES::PLAY)
	{
			return mEnemyCollection.instantiateEnemy(prefabID, myAi, getSceneManagerFor(state));
	}
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
		GameObject_WithColider * getNext();
	
		Player * getPlayer() const { return player; }
		void setPlayer(Player * val) { player = val; }
		void  setEnemyIterator(const GameCollectionIterator<EnemyObject> & val) { enemyIT = val; }
		void setBulletIterator(const GameCollectionIterator<Bullet> & val) { bulletIT = val; }
		void setEffectIterator(const GameCollectionIterator<EffectObject> & val) { effectIT = val; }
		void setStaticIterator(const GameCollectionIterator<StaticObject> & val) { staticIT = val; }
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
		
		Player * player;
		
		GameCollectionIterator<EnemyObject> enemyIT;
		GameCollectionIterator<Bullet> bulletIT;
		GameCollectionIterator<StaticObject> staticIT;
		GameCollectionIterator<EffectObject> effectIT;
	};

	ColidingObjectsIterator getColidingObjectsIterator();
	StaticObject * instantiateStatic( int prefabID, GAME_STATES state = GAME_STATES::PLAY)
	{
		return mStaticCollection.instantiate(prefabID, getSceneManagerFor(state));
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
		default:
			break;
		}
		return NULL;
	}

	void setCameraFor(GAME_STATES gameState, Ogre::Camera * camera);

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
	BaseCollection<BulletPrefab, Bullet> mBulletCollection;
	BaseCollection<EffectPrefab, EffectObject> mEffectsCollection;
	BaseCollection<StaticPrefab, StaticObject> mStaticCollection;

	Player mPlayer;
	GameObjectTemplates mPrefabCollections;
	StateScenesManager_Struct mStateScenesManager;
	CameraManager_Struct mCamerasManager;
	LevelDescription currentLevelDecription;
};
