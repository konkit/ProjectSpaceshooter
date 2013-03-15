#include "stdafx.h"
#include "EnemySpawner.h"
#include <iostream>

EnemySpawner::EnemySpawner(Ogre::Vector3 spawnerPosition, unsigned _spawnFrequency, unsigned _onceSpawn )
	: spawnFrequency(_spawnFrequency),
	  myPosition(spawnerPosition),
	  timeToNextSpawn(0),
	  onceMomentSpawn(_onceSpawn)
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
	EnemyCollection& enemysColl = _gameData->getEnemys();
	if (currentTime > timeToNextSpawn || timeToNextSpawn == 0)
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
			for(int i = amountToSpawnNow; i > 0; i --)
			{
				EnemyObject * tmpEnemy = enemysColl.instantiate(tmpSpawnInfo->prefabID, _gameData->getSceneManagerFor(GAME_STATES::PLAY));
				Vector3 newPosition = myPosition + Vector3(50*(i-1),0,0);
				tmpEnemy->getTransformComponent().setPosition(newPosition);
			}
			if (tmpSpawnInfo->amount == 0)
			{
				std::cout << "Wyspawnowane wszytkie obiekty - usuwamy\n";
				enemyToSpawn -= tmpSpawnInfo;
			}
		}
		timeToNextSpawn = currentTime + spawnFrequency;
		delete it;
	}

}


