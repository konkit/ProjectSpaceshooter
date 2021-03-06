#pragma once
#include "StaticObject.h"
#include "EnemySpawner.h"


using namespace std;
enum class missionType
{
	destroyAllEnemy
};

struct Light
{
	Ogre::Vector3 position;
	Ogre::Vector3 direction;
	Ogre::Degree innerAngle;
	Ogre::Degree outerAngle;
	Ogre::Light::LightTypes mLightType;
	Ogre::ColourValue mDiffuseColour;
	Ogre::ColourValue mSpecularColour;
};

struct StaticObjectDescribe
{
	unsigned int prefabID;
	Vector3 position;
};

/** 
  *
  * @author Zygi
  */
class LevelStage
{
public:
	unsigned int getLevelNumber() {return number;}
	void setStageNumber(unsigned _number){number = _number;}
	missionType getMissionType() const {return typeOfMission;}
	void setMissionType(missionType _typeOfMission){typeOfMission = _typeOfMission;}
	void addSpawner(EnemySpawner * _newSpawner) {enemySpawnerCollection += _newSpawner;}
	void spawnEnemy(GameData & _gameData, unsigned long currentTime)
	{
		GameCollectionIterator<EnemySpawner> spawnerIT = enemySpawnerCollection.getIterator();
		EnemySpawner * tmpSpawner;
		while (spawnerIT.hasNext())
		{
			tmpSpawner = spawnerIT.getNext();
			tmpSpawner->spawnEnemy(&_gameData, currentTime);
		}
	}

private:
	missionType typeOfMission;
	unsigned number;
	GameCollection<EnemySpawner> enemySpawnerCollection;
};

/** 
  *
  * @author Zygi
  */
class LevelDescription
{
public:
	void spawn(GameData & _gameData, unsigned long currentTime)
	{
		levelStageCollection.getFirst()->spawnEnemy(_gameData, currentTime);
	}
	void addNewLevelStage(LevelStage * _newStage)
	{
		levelStageCollection += _newStage;
	}
	void clearLevelDescription();
	Ogre::ColourValue ambientColour;
	GameCollection<Light> lightsCollections;
	GameCollection<StaticObjectDescribe> staticObjectList;
private:
	GameCollection<LevelStage> levelStageCollection;
};






