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
	default:
		break;
	}
}


