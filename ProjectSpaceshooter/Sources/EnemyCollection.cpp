#include "EnemyCollection.h"




void EnemyCollection::addPrefab( EnemyPrefab _enemyPrefab )
{
	if (mPrefabs.size()<_enemyPrefab.getPrefabID())
	{								   
		mPrefabs.resize(_enemyPrefab.getPrefabID()+1);
	}
	mPrefabs[_enemyPrefab.getPrefabID()] = _enemyPrefab;
}
