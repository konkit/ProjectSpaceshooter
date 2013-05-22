#pragma once

class GameData;

struct SpawnerInfo 
{
	unsigned prefabID;
	unsigned amount;
	unsigned spawnEffectID;
};

/** Enemy spawner class
  * It governs creation of Enemies in waves in time intervals
  *
  * @author Zygi
  */
class EnemySpawner
{
public:
	EnemySpawner(Ogre::Vector3 spawnerPosition ,unsigned _spawnFrequency, unsigned _onceSpawn);
	~EnemySpawner(void);
	void addEnemyToSpawn(unsigned prefabID, unsigned number, unsigned _spawnEffectID = 3);
	void spawnEnemy(GameData * _gameData, unsigned long currentTime);
	void setSpawnerDelaySinceStageStart(unsigned delay_in_seconds) {delaySinceSageStart = 1000 * delay_in_seconds;}
	void spawnCountOfEnemy(const SpawnerInfo& enemyToSpawnNow, GameData * _gameData );
	void initSpawnDelaySinceStart( unsigned long currentTime );

private:
	GameCollection<SpawnerInfo> enemyToSpawn;
	Ogre::Vector3 myPosition;
	unsigned spawnFrequency;
	unsigned onceMomentSpawn;
	unsigned long timeToNextSpawn;
	unsigned delaySinceSageStart;
};

