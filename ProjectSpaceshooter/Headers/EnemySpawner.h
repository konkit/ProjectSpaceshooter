#pragma once
#include <vector>

struct SpawnerStruct 
{
	unsigned prefabID;
	unsigned number;
};

class EnemySpawner
{
public:
	EnemySpawner(unsigned numberOfEnemyTypes, unsigned _spawnFrequency);
	~EnemySpawner(void);
	void addEnemyToSpawn(unsigned prefabID, unsigned number);
	void spawnEnemy(GameData * _gameData, unsigned long currentTime);
private:
	std::vector<SpawnerStruct> enemyToSpawn;
	unsigned lastFreeIndex;
	unsigned spawnFrequency;
	unsigned long timeToNextSpawn;
};

