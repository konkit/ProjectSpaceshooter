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
	loadPrefabs(PREFAB_TYPE::StaticPrefab, staticPrefabFile, _gameData);
	loadPrefabs(PREFAB_TYPE::EffectPrefab, effectPrefabFile, _gameData);
	loadPrefabs(PREFAB_TYPE::WeaponPrefab, weaponPrefabFile, _gameData);
}

void ResoursceLoader::loadPrefabs(PREFAB_TYPE prefabType, const char * prefabsFile, GameData & _gameData )
{
	try{
	XML_Reader_Lite xmlReader(prefabsFile);
	PrefabPlant * _prefabPlant = PrefabPlant::CreatePrefabPlantFor(prefabType);
	GameObjectReader prefabReader(_prefabPlant, &xmlReader);
	while(prefabReader.hasNext())
	{
		_gameData.addPrefab(prefabType, prefabReader.getNext());
	}
	PrefabPlant::DeletePrefabPlant(_prefabPlant);
	}catch(My_Exception& excep)
	{

		MessageBoxA( NULL, excep.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
}



const char * ResoursceLoader::weaponPrefabFile = "media/prefabs_descriptions/weapon_prefabs.xml";
const char * ResoursceLoader::bulletPrefabFile = "media/prefabs_descriptions/bullet_prefabs.xml";
const char * ResoursceLoader::effectPrefabFile = "media/prefabs_descriptions/effect_prefabs.xml";
const char * ResoursceLoader::staticPrefabFile = "media/prefabs_descriptions/static_prefabs.xml";
const char * ResoursceLoader::enemyPrefabFile  = "media/prefabs_descriptions/ship_prefabs.xml";
