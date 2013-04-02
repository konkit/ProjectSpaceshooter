#include "ResoursceLoader.h"
#include "PredabReader_XML.h"
ResoursceLoader::~ResoursceLoader()
{

}

ResoursceLoader::ResoursceLoader()
{

}

void ResoursceLoader::loadPrefabs( GameData & _gameData )
{
}

void ResoursceLoader::loadEnemyPrefabs( GameData & _gameData )
{
	PredabReader_XML enemyReader("media/prefabs_descriptions/ship_prefabs.xml",PREFAB_TYPE::EnemyPrefab);
	Prefab * _prefab;
	EnemyPrefab * _enemyPrefab;
	while(enemyReader.hasNext())
	{
		_prefab = enemyReader.getNext();
		_enemyPrefab = dynamic_cast<EnemyPrefab *>( _prefab);
		_gameData.addEnemyPrefab(*_enemyPrefab);
	}
}
