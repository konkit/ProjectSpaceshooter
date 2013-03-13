#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner( unsigned numberOfEnemyTypes, unsigned _spawnFrequency )
	: enemyToSpawn(numberOfEnemyTypes), spawnFrequency(_spawnFrequency),
	  lastFreeIndex(0), timeToNextSpawn(0)
{

}


EnemySpawner::~EnemySpawner(void)
{
}

void EnemySpawner::addEnemyToSpawn( unsigned prefabID, unsigned number )
{
	SpawnerStruct tmpStruct = {prefabID, number};
	enemyToSpawn[lastFreeIndex] = tmpStruct;
	lastFreeIndex++;
}


