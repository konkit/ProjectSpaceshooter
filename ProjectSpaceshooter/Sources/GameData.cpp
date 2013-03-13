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
	//TODO Iniciajlizowaæ nowe obiekty z plików
	EnemyPrefab * myEnemy = new EnemyPrefab("basicEnemy"); 
	mPrefabCollections.enemyPrefabCollection.addObject(myEnemy);
	myEnemy->setAiType(AI_TYPE::fighter);
	myEnemy->setMeshName("smallfighter.MESH");
	myEnemy->setResistance(1000);
	myEnemy->setWaeponeName("basicWaepon");
}


