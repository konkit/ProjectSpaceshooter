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
	loadEnemyPrefabs(_gameData);
}

void ResoursceLoader::loadEnemyPrefabs( GameData & _gameData )
{
	PredabReader_XML enemyReader("media/prefabs_descriptions/ship_prefabs.xml",PREFAB_TYPE::EnemyPrefab);
	Prefab * _prefab;
	EnemyPrefab * _enemyPrefab;
	try{
	while(enemyReader.hasNext())
	{
		_prefab = enemyReader.getNext();
		_enemyPrefab = dynamic_cast<EnemyPrefab *>( _prefab);
		if (_enemyPrefab != NULL)
		{
			_gameData.addEnemyPrefab(*_enemyPrefab);
		} else
		{
			My_Exception("loadEnemyPrefabs: Can't convert prefab into enemyPrefab");
		}
	}
	}catch(My_Exception& excep)
	{
		MessageBoxA( NULL, excep.what(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
}
