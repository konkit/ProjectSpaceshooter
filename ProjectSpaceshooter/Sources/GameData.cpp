#pragma once


#include "GameData.h"
#include "GameObject.h"
using std::string;
GameData::GameData(void)
	:mEffectsCollection("Effect Collection"), mBulletCollection("Bullet Collection"), mStaticCollection("Static Collection")
{
	changeFlags.changeToHangar = false;
	changeFlags.changeToMenu = false;
	changeFlags.changeToPause = false;
	changeFlags.changeToPlay = false;
}

GameData::~GameData(void)
{
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



const WeaponPrefab * GameData::getWeaponPrefab( unsigned prefabId )
{
	return mEnemyCollection.getWeaponPrefab(prefabId);
}


GameData::ColidingObjectsIterator GameData::getColidingObjectsIterator()
{
	ColidingObjectsIterator tmp;
	tmp.setPlayer(&mPlayer);
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
		break;
	case GAME_STATES::LEVEL_BUILDER:
		break;
	default:
		break;
	}
}


bool GameData::ColidingObjectsIterator::hasNext()
{
	switch (activeIterator)
	{
	case GameData::ColidingObjectsIterator::iterator::Player:
		return true;
	case GameData::ColidingObjectsIterator::iterator::Enemy:
		if (enemyIT.hasNext())
		{
			return true;
		} else
		{
			activeIterator = iterator::Bullet;
			return hasNext();
		}
	case GameData::ColidingObjectsIterator::iterator::Bullet:
		if (bulletIT.hasNext())
		{
			return true;
		} else
		{
			activeIterator = iterator::Static;
			return hasNext();
		}
	case GameData::ColidingObjectsIterator::iterator::Static:
		if (staticIT.hasNext())
		{
			return true;
		} else
		{
			activeIterator = iterator::Effect;
			return hasNext();
		}
	case GameData::ColidingObjectsIterator::iterator::Effect:
		if (effectIT.hasNext())
		{
			return true;
		} else
		{
			activeIterator = iterator::EMPTY;
			return hasNext();
		}
	case GameData::ColidingObjectsIterator::iterator::EMPTY:
			activeIterator = iterator::Player;
			return false;
	default:
		return false;
	}
}

GameObject_WithCollider * GameData::ColidingObjectsIterator::getNext()
{
	
	switch (activeIterator)
	{
	case GameData::ColidingObjectsIterator::iterator::Player:
		activeIterator = iterator::Enemy;
		return player;
	case GameData::ColidingObjectsIterator::iterator::Enemy:
		return enemyIT.getNext();
	case GameData::ColidingObjectsIterator::iterator::Bullet:
		return bulletIT.getNext();
	case GameData::ColidingObjectsIterator::iterator::Static:
		return staticIT.getNext();
	case GameData::ColidingObjectsIterator::iterator::Effect:
		return effectIT.getNext();
	case GameData::ColidingObjectsIterator::iterator::EMPTY:
	default:
		return NULL;
	}
}
