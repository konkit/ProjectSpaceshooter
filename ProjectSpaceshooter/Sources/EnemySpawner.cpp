#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(Ogre::Vector3 spawnerPosition, unsigned _spawnFrequency, unsigned _onceSpawn )
	: spawnFrequency(_spawnFrequency),
	  myPosition(spawnerPosition),
	  timeToNextSpawn(0),
	  onceSpawn(_onceSpawn)
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
		unsigned amountToSpawn;
		unsigned leftToSpawn = onceSpawn;
		while (it->hasNext() && leftToSpawn > 0)
		{
			tmpSpawnInfo = it->getNext();
			amountToSpawn =  leftToSpawn >= tmpSpawnInfo->amount ? tmpSpawnInfo->amount : leftToSpawn;
			leftToSpawn -= amountToSpawn;
			for(int i = leftToSpawn; i > 0; i --)
			{
				EnemyObject * tmpEnemy = enemysColl.instantiate(tmpSpawnInfo->prefabID, _gameData->getSceneManagerFor(GAME_STATES::PLAY));
				tmpEnemy->getTransformComponent().setPosition(myPosition + Vector3(10*(i-1),0,0));
			}
			if (tmpSpawnInfo->amount == 0)
			{
				enemyToSpawn -= tmpSpawnInfo;
			}
		}
	}
}


