#include "stdafx.h"
#include "EnemySpawner.h"
#include "BaseCollection.h"
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

void EnemySpawner::addEnemyToSpawn( unsigned prefabID, unsigned number, unsigned _spawnEffectID )
{
	SpawnerInfo * tmpStruct =  new SpawnerInfo;
	tmpStruct->prefabID = prefabID;
	tmpStruct->amount = number;
	tmpStruct->spawnEffectID = _spawnEffectID;
	enemyToSpawn += tmpStruct;
}

void EnemySpawner::spawnEnemy( GameData * _gameData, unsigned long currentTime )
{
	initSpawnDelaySinceStart(currentTime);

	if (currentTime > timeToNextSpawn)
	{
		GameCollectionIterator<SpawnerInfo> it = enemyToSpawn.getIterator();
		SpawnerInfo * tmpSpawnInfo;
		SpawnerInfo enemyToSpawnNow;
		unsigned amountToSpawnNow;
		unsigned leftToSpawn = onceMomentSpawn;
		while (it.hasNext() && leftToSpawn > 0)
		{
			tmpSpawnInfo = it.getNext();
			amountToSpawnNow =  leftToSpawn >= tmpSpawnInfo->amount ? tmpSpawnInfo->amount : leftToSpawn;
			leftToSpawn -= amountToSpawnNow;
			tmpSpawnInfo->amount -= amountToSpawnNow;			
			enemyToSpawnNow.amount = amountToSpawnNow;
			enemyToSpawnNow.prefabID = tmpSpawnInfo->prefabID;
			enemyToSpawnNow.spawnEffectID = tmpSpawnInfo->spawnEffectID;
			spawnCountOfEnemy(enemyToSpawnNow, _gameData);

			if (tmpSpawnInfo->amount == 0) //Delete empty spawn slot
				enemyToSpawn.deleteObject(it);
		}
		timeToNextSpawn = currentTime + spawnFrequency;
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

void EnemySpawner::spawnCountOfEnemy(const SpawnerInfo& enemyToSpawnNow, GameData * _gameData )
{
	for(int i = enemyToSpawnNow.amount; i > 0; i --)
	{
		//EnemyCollection& enemysColl = _gameData->getEnemys();
		BaseCollection<ShipPrefab, EnemyObject>& enemiesCollection = _gameData->getEnemies();
		EnemyObject * tmpEnemy = _gameData->instantiateEnemy(enemyToSpawnNow.prefabID, AI_TYPE::fighter);
		Vector3 newPosition = myPosition + Vector3(200.0*(i-1), 0.0, 0.0);
		tmpEnemy->setPosition(newPosition);
		EffectObject * spawnEffect = _gameData->instantiateEffect(enemyToSpawnNow.spawnEffectID);
		spawnEffect->setPosition(newPosition);
	}
}


