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
	string meshName;
	unsigned int resistance;
};

struct LevelStage
{
	unsigned number;
	missionType typeOfMission;
	GameCollection<EnemySpawner> enemySpawnerCollection;
};

struct LevelDescription
{
//	string resourceGroupName; Bêdzie potrzebne do wybierania zasobów dla konkretnego levelu
	Ogre::ColourValue ambientColour;
	GameCollection<Light> lightsCollections;
	GameCollection<StaticObjectDescribe> staticObjectList;
	GameCollection<LevelStage> levelStageCollection;
};






