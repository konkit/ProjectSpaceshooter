#pragma once

#include "Prefabs.h"
#include "Ship.h"
#include "AIComponent.h"

using namespace std;

/** 
  *
  * @author Zyga
  */
class EnemyObject : public Ship
{
public:
	EnemyObject::EnemyObject(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon,Ogre::SceneManager * _sceneMenager);
	EnemyObject::EnemyObject(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, AI_TYPE _myAi, Ogre::SceneManager * _sceneMenager);
	~EnemyObject();
	unsigned int mResistance;

	AI_TYPE getAI() const { return myAI; }
	void setAI(AI_TYPE val) { myAI = val; }
	AIComponent& getAIComponent()	{
		return mAIComponent;
	}
	

	GameObjectType getType() {
		return GameObjectType::enemyObject;
	}
private:
//  AI component
	AI_TYPE myAI;
	AIComponent	mAIComponent;

};


