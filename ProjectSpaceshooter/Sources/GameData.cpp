#pragma once


#include "GameData.h"
#include "GameObject.h"
#include "Exceptions.h"
using std::string;
GameData::GameData(void)
	:mEffectsCollection("Effect Collection"), mBulletCollection(), mStaticCollection("Static Collection"), mPlayer(NULL)
{
	changeFlags.changeToHangar = false;
	changeFlags.changeToMenu = false;
	changeFlags.changeToPause = false;
	changeFlags.changeToPlay = false;
	currentLevelDecription = NULL;
}

GameData::~GameData(void)
{
	delete mPlayer;
	delete currentLevelDecription;
}

Ogre::SceneManager * GameData::getSceneManagerFor( GAME_STATES gameState )
{
	switch (gameState)
	{
	case GAME_STATES::PLAY:
		return mStateScenesManager.playSceneManager;
	case GAME_STATES::PAUSE:
		return mStateScenesManager.pauseSceneManager;
	case GAME_STATES::HANGAR:
		return mStateScenesManager.hangarSceneManager;
	default:
		return NULL;
	}
}

void GameData::setSceneMenagerFor( GAME_STATES gameState, Ogre::SceneManager * sceneManagerForState )
{
	switch (gameState)
	{
	case GAME_STATES::PLAY:
		mStateScenesManager.playSceneManager = sceneManagerForState;
		break;
	case GAME_STATES::PAUSE:
		mStateScenesManager.pauseSceneManager = sceneManagerForState;
		break;
	case GAME_STATES::HANGAR:
		mStateScenesManager.hangarSceneManager = sceneManagerForState;
		break;
	}
	return;
}

void GameData::addPrefab( PREFAB_TYPE prefabType, Prefab & prefab )
{
;
	switch (prefabType)
	{
	case PREFAB_TYPE::EnemyPrefab:
		if (typeid(prefab) !=  typeid(ShipPrefab))
		{
			throw My_Exception("GameData::addPrefab: Can't convert prefab into ShipPrefab");
		}
		addShipPrefab(dynamic_cast<ShipPrefab &>(prefab));
		//TODO: po dodaniu tablicy prefabów zmieniæ to
		break;
	case PREFAB_TYPE::BulletPrefab:
		if (typeid(prefab) !=  typeid(BulletPrefab))
		{
			throw My_Exception("GameData::addPrefab: Can't convert prefab into BulletPrefab");
		}
		addBulletPrefab(dynamic_cast<BulletPrefab &>(prefab));
		break;
	case PREFAB_TYPE::StaticPrefab:
		if (typeid(prefab) !=  typeid(StaticPrefab))
		{
			throw My_Exception("GameData::addPrefab: Can't convert prefab into StaticPrefab");
		}
		addStaticPrefab(dynamic_cast<StaticPrefab &>(prefab));
		break;
	case PREFAB_TYPE::EffectPrefab:
		if (typeid(prefab) !=  typeid(EffectPrefab))
		{
			throw My_Exception("GameData::addPrefab: Can't convert prefab into EffectPrefab");
		}
		addEffectPrefab(dynamic_cast<EffectPrefab &>(prefab));
		break;
	case PREFAB_TYPE::WeaponPrefab:
		if (typeid(prefab) !=  typeid(WeaponPrefab))
		{
			throw My_Exception("GameData::addPrefab: Can't convert prefab into WeaponPrefab");
		}
		addWeaponPrefab(dynamic_cast<WeaponPrefab &>(prefab));
		break;
	default:
		break;
	}
}

void GameData::addEffectPrefab( const EffectPrefab & _effectPrefab )
{
	if (&_effectPrefab == NULL)
	{
		throw My_Exception("addEffectPrefab: Can't add NULL Effect Prefab");
	}
	mEffectsCollection.addPrefab(&_effectPrefab);
}

void GameData::addStaticPrefab( const StaticPrefab & _staticPrefab )
{
	if (&_staticPrefab == NULL)
	{
		throw My_Exception("addStaticPrefab: Can't add NULL Static Prefab");
	}
	mStaticCollection.addPrefab(&_staticPrefab);
}

void GameData::addBulletPrefab( const BulletPrefab & _bulletPrefab )
{
	if (&_bulletPrefab == NULL)
	{
		throw My_Exception("addBulletPrefab: Can't add NULL Bullet Prefab");
	}
	mBulletCollection.addPrefab(&_bulletPrefab);
}

void GameData::addShipPrefab( const ShipPrefab & _enemyPrefab )
{
	if (&_enemyPrefab == NULL)
	{
		throw My_Exception("addShipPrefab: Can't add NULL Ship Prefab");
	}
	mEnemyCollection.addPrefab(&_enemyPrefab);
}

void GameData::addWeaponPrefab( const WeaponPrefab & _weaponPrefab )
{
	mEnemyCollection.addWeaponPrefab(_weaponPrefab);
}

void GameData::removeGameObject( ColidingObjectsIterator & removedObjectIterator )
{
	GameObjectType objectType;
	try
	{
		objectType = removedObjectIterator.getPointedObjectType();
	}
	catch (IteratorException &  e)
	{
		throw My_Exception(string(e.what()) + "in GameData::removeGameObject");
	}

	switch (objectType)
	{
	case GameObjectType::enemyObject:
		mEnemyCollection.getCollection().deleteObject(removedObjectIterator.getEnemyIT());
		break;
	case GameObjectType::bulletObject:
		mBulletCollection.destroyBullet(removedObjectIterator.getBulletIT());
		break;
	case GameObjectType::core:
		theCore = NULL; // There is no break; in ths place, because TheCore is a staticObject, and The Core is removed like static
	case GameObjectType::staticObject:
		mStaticCollection.getCollection().deleteObject(removedObjectIterator.getStaticIT());
		break;
	case GameObjectType::effectObject:
		mEffectsCollection.getCollection().deleteObject(removedObjectIterator.getEffectIT());
		break;
	default:
		throw My_Exception("Incorrect game object type in GameData::removeGameObject");
	}
}

void GameData::removeGameObject( GameObject_WithCollider * removedObject )
{
	GameObjectType objectType = removedObject->getType();
	switch (objectType)
	{
	case GameObjectType::enemyObject:
		mEnemyCollection.getCollection().deleteObject(static_cast<EnemyObject *>(removedObject));
		break;
	case GameObjectType::bulletObject:
		mBulletCollection.destroyBullet(static_cast<Bullet *>(removedObject));
		break;
	case GameObjectType::core:
		theCore = NULL; // There is no break; in ths place, because TheCore is a staticObject, and The Core is removed like static
	case GameObjectType::staticObject:
		mStaticCollection.getCollection().deleteObject(static_cast<StaticObject*>(removedObject));
		break;
	case GameObjectType::effectObject:
		mEffectsCollection.getCollection().deleteObject(static_cast<EffectObject*>(removedObject));
		break;
	default:
		break;
	}
}


const WeaponPrefab * GameData::getWeaponPrefab( unsigned prefabId )
{
	return mEnemyCollection.getWeaponPrefab(prefabId);
}


GameData::ColidingObjectsIterator GameData::getColidingObjectsIterator()
{
	ColidingObjectsIterator tmp;
	tmp.setPlayer(mPlayer);
	tmp.setEnemyIterator(mEnemyCollection.getIterator());
	tmp.setBulletIterator(mBulletCollection.getIterator());
	tmp.setEffectIterator(mEffectsCollection.getIterator());
	tmp.setStaticIterator(mStaticCollection.getIterator());
	return tmp;
}

void GameData::setCameraFor( GAME_STATES gameState, Ogre::Camera * camera )
{
	switch (gameState)
	{
	case GAME_STATES::PLAY:
		mCamerasManager.playCamera = camera;
		break;
	case GAME_STATES::PAUSE:
		mCamerasManager.pauseCamera = camera;
		break;
	case GAME_STATES::HANGAR:
		mCamerasManager.hangarSceneCamera = camera;
		break;
	case GAME_STATES::LEVEL_BUILDER:
		break;
	case GAME_STATES::GAME_OVER:
		mCamerasManager.gameOverCamera = camera;
	default:
		break;
	}
}

void GameData::destroyPlayer()
{
	delete mPlayer;
	mPlayer = NULL;
}

bool GameData::isPlayerDead()
{
	if (mPlayer != NULL)
	{
		return mPlayer->isDead();
	}
	else true;
}

bool GameData::isCoreDead()
{
	if (theCore != NULL)
	{
		return theCore->isDead();
	}
	return true;
}

void GameData::setCountOfPrefabs( PREFAB_TYPE prefabType, unsigned count )
{
	switch (prefabType)
	{
	case PREFAB_TYPE::EnemyPrefab:
		mEnemyCollection.setCountOfShipPrefab(count);
		break;
	case PREFAB_TYPE::BulletPrefab:
		mBulletCollection.setCountOfPrefab(count);
		break;
	case PREFAB_TYPE::StaticPrefab:
		mStaticCollection.setCountOfPrefab(count);
		break;
	case PREFAB_TYPE::EffectPrefab:
		mEffectsCollection.setCountOfPrefab(count);
		break;
	case PREFAB_TYPE::WeaponPrefab:
		mEnemyCollection.setCountOfWeaponPrefab(count);
		break;
	default:
		break;
	}
}

void GameData::clearPlayData()
{
	mEnemyCollection.getCollection().clearCollection();
	mBulletCollection.clearCollection();
	mStaticCollection.getCollection().clearCollection();
	mEffectsCollection.getCollection().clearCollection();
	destroyPlayer();
	mStateScenesManager.playSceneManager->destroyAllLights();
	delete currentLevelDecription;

}

void GameData::initializeDataPulls()
{
	mBulletCollection.initializeBullet(mStateScenesManager.playSceneManager);
}


bool GameData::ColidingObjectsIterator::hasNext()
{
	if(activeIterator == iterator::Player && player == NULL)
		moveToNextIterator();
	if (activeIterator != iterator::EMPTY)
	{
		return true;
	} else
	{
		return false;
	}
}

GameObject_WithCollider * GameData::ColidingObjectsIterator::getNext()
{
	GameObject_WithCollider * tmp;

	if(activeIterator == iterator::Player && player == NULL)
		moveToNextIterator();

	switch (activeIterator)
	{
	case GameData::ColidingObjectsIterator::iterator::Player:
		tmp = player;
		lastElementType = GameObjectType::player;
		break;
	case GameData::ColidingObjectsIterator::iterator::Enemy:
		tmp = enemyIT.getNext();
		lastElementType = GameObjectType::enemyObject;
		break;
	case GameData::ColidingObjectsIterator::iterator::Bullet:
		tmp = bulletIT.getNext();
		lastElementType = GameObjectType::bulletObject;
		break;
	case GameData::ColidingObjectsIterator::iterator::Static:
		tmp = staticIT.getNext();
		lastElementType = GameObjectType::staticObject;
		break;
	case GameData::ColidingObjectsIterator::iterator::Effect:
		tmp = effectIT.getNext();
		lastElementType = GameObjectType::effectObject;
		break;
	case GameData::ColidingObjectsIterator::iterator::EMPTY:
	default:
		return NULL;
	}
	moveToNextIterator();
	return tmp;
}

void GameData::ColidingObjectsIterator::moveToNextIterator()
{
	switch (activeIterator)
	{
	case GameData::ColidingObjectsIterator::iterator::Player:
		activeIterator = iterator::Enemy;
	case GameData::ColidingObjectsIterator::iterator::Enemy:
		if (!enemyIT.hasNext())
		{
			activeIterator = iterator::Bullet;
			moveToNextIterator();
		} 
		return;
	case GameData::ColidingObjectsIterator::iterator::Bullet:
		if (!bulletIT.hasNext())
		{
			activeIterator = iterator::Static;
			moveToNextIterator();
		}
		return;
	case GameData::ColidingObjectsIterator::iterator::Static:
		if (!staticIT.hasNext())
		{
			activeIterator = iterator::Effect;
			moveToNextIterator();
		}
		return;
	case GameData::ColidingObjectsIterator::iterator::Effect:
		if (!effectIT.hasNext())
		{
			activeIterator = iterator::EMPTY;
			moveToNextIterator();
		}
		return;
	case GameData::ColidingObjectsIterator::iterator::EMPTY:
		return;
	default:
		return;
	}
}

GameObjectType GameData::ColidingObjectsIterator::getPointedObjectType()
{
	return lastElementType;
}
