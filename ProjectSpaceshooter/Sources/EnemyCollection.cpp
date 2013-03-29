#include "EnemyCollection.h"




void EnemyCollection::addPrefab( EnemyPrefab _enemyPrefab )
{
	if (mPrefabs.size()<_enemyPrefab.getEnemyPrefabID())
	{
		mPrefabs.resize(_enemyPrefab.getEnemyPrefabID()+1);
	}
	mPrefabs[_enemyPrefab.getEnemyPrefabID()] = _enemyPrefab;
}
