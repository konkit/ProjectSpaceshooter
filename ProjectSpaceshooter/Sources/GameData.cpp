#pragma once


#include "GameData.h"
#include "GameObject.h"

GameData::GameData(void)
{
	changeFlags.changeToHangar = false;
	changeFlags.changeToMenu = false;
	changeFlags.changeToPause = false;
	changeFlags.changeToPlay = false;
	mEnemyCollection.loadPrefabs();
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


