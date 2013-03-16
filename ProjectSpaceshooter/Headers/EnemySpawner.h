#pragma once

class GameData;

struct SpawnerInfo 
{
	unsigned prefabID;
	unsigned amount;
};

/** 
  *
  * @author Zygi
  */
class EnemySpawner
{
public:
	EnemySpawner(Ogre::Vector3 spawnerPosition ,unsigned _spawnFrequency, unsigned _onceSpawn);
	~EnemySpawner(void);
	void addEnemyToSpawn(unsigned prefabID, unsigned number);
	void spawnEnemy(GameData * _gameData, unsigned long currentTime);
private:
	GameCollection<SpawnerInfo> enemyToSpawn;
	Ogre::Vector3 myPosition;
	unsigned spawnFrequency;
	unsigned onceMomentSpawn;
	unsigned long timeToNextSpawn;
};

