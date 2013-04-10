#pragma once


#include "GameData.h"
#include "GameObject.h"

GameData::GameData(void)
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
	EffectPrefab * prefab = new EffectPrefab(_effectPrefab);
	mEffectsCollection.addPrefab(prefab);
}

void GameData::addStaticPrefab( const StaticPrefab & _staticPrefab )
{
	if (&_staticPrefab == NULL)
	{
		throw My_Exception("addStaticPrefab: Can't add NULL Static Prefab");
	}
	StaticPrefab * prefab = new StaticPrefab(_staticPrefab);
	mStaticCollection.addPrefab(prefab);
}

void GameData::addBulletPrefab( const BulletPrefab & _bulletPrefab )
{
	if (&_bulletPrefab == NULL)
	{
		throw My_Exception("addBulletPrefab: Can't add NULL Bullet Prefab");
	}
	BulletPrefab * prefab = new BulletPrefab(_bulletPrefab);
	mBulletCollection.addPrefab(prefab);
}

void GameData::addShipPrefab( const ShipPrefab & _enemyPrefab )
{
	if (&_enemyPrefab == NULL)
	{
		throw My_Exception("addShipPrefab: Can't add NULL Ship Prefab");
	}
	ShipPrefab * prefab = new ShipPrefab(_enemyPrefab);
	mEnemyCollection.addPrefab(prefab);
}

void GameData::addWeaponPrefab( const WeaponPrefab & _weaponPrefab )
{
	if (&_weaponPrefab == NULL)
	{
		throw My_Exception("addWeaponPrefab: Can't add NULL Weapon Prefab");
	}
	WeaponPrefab * prefab = new WeaponPrefab(_weaponPrefab);
	mWeaponCollection.addObject(prefab);
}




