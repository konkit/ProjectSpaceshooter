#include "ResoursceLoader.h"
#include "PredabReader_XML.h"
ResoursceLoader::~ResoursceLoader()
{

}

ResoursceLoader::ResoursceLoader()
{

}

void ResoursceLoader::loadAllPrefabs( GameData & _gameData )
{
	loadPrefabs(PREFAB_TYPE::EnemyPrefab, enemyPrefabFile, _gameData);
	loadPrefabs(PREFAB_TYPE::BulletPrefab, bulletPrefabFile, _gameData);
	//loadPrefabs(PREFAB_TYPE::StaticPrefab, staticPrefabFile, _gameData);
	//loadPrefabs(PREFAB_TYPE::EffectPrefab, effectPrefabFile, _gameData);
}

void ResoursceLoader::loadPrefabs(PREFAB_TYPE prefabType, const char * prefabsFile, GameData & _gameData )
{
	PredabReader_XML prefabReader(prefabsFile, prefabType);
	try{
	while(prefabReader.hasNext())
	{
		_gameData.addPrefab(prefabType, prefabReader.getNext());
	}
	}catch(My_Exception& excep)
	{
		MessageBoxA( NULL, excep.what(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
}


const char * ResoursceLoader::bulletPrefabFile = "media/prefabs_descriptions/bullet_prefabs.xml";
const char * ResoursceLoader::effectPrefabFile = "media/prefabs_descriptions/ship_prefabs.xml";
const char * ResoursceLoader::staticPrefabFile = "media/prefabs_descriptions/ship_prefabs.xml";
const char * ResoursceLoader::enemyPrefabFile  = "media/prefabs_descriptions/ship_prefabs.xml";
