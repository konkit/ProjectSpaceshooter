#include "stdafx.h"
#include "EnemySpawner.h"
#include <iostream>

EnemySpawner::EnemySpawner(Ogre::Vector3 spawnerPosition, unsigned _spawnFrequency, unsigned _onceSpawn )
	: spawnFrequency(_spawnFrequency),
	  myPosition(spawnerPosition),
	  timeToNextSpawn(0),
	  onceMomentSpawn(_onceSpawn),
	  delaySinceSageStart(0)
{

}

EnemySpawner::~EnemySpawner(void)
{
}

void EnemySpawner::addEnemyToSpawn( unsigned prefabID, unsigned number )
{
	SpawnerInfo * tmpStruct =  new SpawnerInfo;
	tmpStruct->prefabID = prefabID;
	tmpStruct->amount = number;
	enemyToSpawn += tmpStruct;
}

void EnemySpawner::spawnEnemy( GameData * _gameData, unsigned long currentTime )
{
	initSpawnDelaySinceStart(currentTime);

	if (currentTime > timeToNextSpawn)
	{
		GameCollectionIterator<SpawnerInfo> * it = enemyToSpawn.getIterator();
		SpawnerInfo * tmpSpawnInfo;
		unsigned amountToSpawnNow;
		unsigned leftToSpawn = onceMomentSpawn;
		while (it->hasNext() && leftToSpawn > 0)
		{
			tmpSpawnInfo = it->getNext();
			amountToSpawnNow =  leftToSpawn >= tmpSpawnInfo->amount ? tmpSpawnInfo->amount : leftToSpawn;
			leftToSpawn -= amountToSpawnNow;
			tmpSpawnInfo->amount -= amountToSpawnNow;			
			spawnCountOfEnemy(amountToSpawnNow, _gameData, tmpSpawnInfo->prefabID);

			if (tmpSpawnInfo->amount == 0) //Delete empty spawn slot
				enemyToSpawn -= tmpSpawnInfo;
		}
		timeToNextSpawn = currentTime + spawnFrequency;
		delete it;
	}

}

void EnemySpawner::initSpawnDelaySinceStart( unsigned long currentTime )
{
	if (delaySinceSageStart != 0)
	{
		timeToNextSpawn += delaySinceSageStart + currentTime;
		delaySinceSageStart = 0;
	}
}

void EnemySpawner::spawnCountOfEnemy( unsigned amountToSpawnNow, GameData * _gameData, unsigned _prefabID )
{
	for(int i = amountToSpawnNow; i > 0; i --)
	{
		EnemyCollection& enemysColl = _gameData->getEnemys();
		EnemyObject * tmpEnemy = enemysColl.instantiate(_prefabID, _gameData->getSceneManagerFor(GAME_STATES::PLAY));
		Vector3 newPosition = myPosition + Vector3(50*(i-1),0,0);
		tmpEnemy->setPosition(newPosition);
	}
}


