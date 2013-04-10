#pragma once
class ResoursceLoader
{
public:
	ResoursceLoader();
	~ResoursceLoader();
	void loadPrefabs(PREFAB_TYPE prefabType, const char * prefabsFile, GameData & _gameData );
	void loadAllPrefabs( GameData & _gameData );

private:
	static const char * weaponPrefabFile;
	static const char * enemyPrefabFile;
	static const char * staticPrefabFile;
	static const char * effectPrefabFile;
	static const char * bulletPrefabFile;
};