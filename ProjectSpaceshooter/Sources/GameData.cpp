#pragma once


#include "GameData.h"
#include "GameObject.h"

GameData::GameData(void)
{
	changeFlags.changeToHangar = false;
	changeFlags.changeToMenu = false;
	changeFlags.changeToPause = false;
	changeFlags.changeToPlay = false;
	initObjectsTemplates();
}


GameData::~GameData(void)
{
}

void GameData::initObjectsTemplates()
{
	//TODO Iniciajlizowa� nowe obiekty z plik�w
	EnemyPrefab * myEnemy = new EnemyPrefab(1); 
	mPrefabCollections.enemyPrefabCollection.addObject(myEnemy);
	myEnemy->setAiType(AI_TYPE::fighter);
	myEnemy->setMeshName("smallfighter.MESH");
	myEnemy->setResistance(1000);
	myEnemy->setWeaponPrefabID(1);
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


