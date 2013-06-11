#pragma once


/** Class which governs loading prefabs from external source
  * in this case - XML files
  *
  * @author Zyga
  */
class ResoursceLoader
{
public:
	ResoursceLoader();
	~ResoursceLoader();

	/**
	 * Load all XML files 
	 * @param _gameData Store loaded prefabs
	 * @author Zyga
	 */
	void loadAllPrefabs( GameData & _gameData );

private:
	/** Loads one XML file with given filename and prefab type  */
	void loadPrefabs(PREFAB_TYPE prefabType, const char * prefabsFile, GameData & _gameData );

	static const char * weaponPrefabFile;
	static const char * enemyPrefabFile;
	static const char * staticPrefabFile;
	static const char * effectPrefabFile;
	static const char * bulletPrefabFile;
};