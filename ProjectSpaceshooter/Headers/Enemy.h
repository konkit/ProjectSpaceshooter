#pragma once

#include "Prefabs.h"
#include "Ship.h"

using namespace std;

enum class AI_TYPE
{
	fighter,
	defender
};
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

	AI_TYPE getAI() const { return myAI; }
	void setAI(AI_TYPE val) { myAI = val; }
private:
//  AI component
	AI_TYPE myAI;

};


