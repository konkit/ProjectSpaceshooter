#pragma once

#include "Prefabs.h"
#include "Ship.h"
#include "AIComponent.h"

using namespace std;

/** Class of enemy game object
  *
  * @author Zyga
  */
class EnemyObject : public Ship
{
public:
	/**
	* EnemyObject constructor. Create enemy's ship from ship prefab, and add his mesh to scene given in param. Created enemy is set with default AI - 'fighter'
	* @param const ShipPrefab * objectTemplate Ship prefab which describe ship properties
	* @param const WeaponPrefab * weapon Weapon prefab which descriebe weapon properies
	* @param Ogre::SceneManager * _sceneMenager Scene menager to place mesh into.
	* @author Zyga
	*/
	EnemyObject::EnemyObject(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon,Ogre::SceneManager * _sceneMenager);
	/**
	* EnemyObject constructor. Create enemy's ship from ship prefab, and add his mesh to scene given in param. Enemy AI can be set throught param. 
	* @param const ShipPrefab * objectTemplate Ship prefab which describe ship properties
	* @param const WeaponPrefab * weapon Weapon prefab which descriebe weapon properies
	* @param AI_TYPE _myAi Type of AI, which will be set.
	* @param Ogre::SceneManager * _sceneMenager Scene menager to place mesh into.
	* @author Zyga
	*/
	EnemyObject::EnemyObject(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, AI_TYPE _myAi, Ogre::SceneManager * _sceneMenager);

	/**
	* Enemy destructor. This method destroy enemy and remove his node and mesh. 
	*
	* @author Zyga
	*/
	virtual ~EnemyObject();
	unsigned int mResistance;

	AI_TYPE getAI() const { return myAI; }
	void setAI(AI_TYPE val) { myAI = val; }
	AIComponent& getAIComponent()	{
		return mAIComponent;
	}
	

	GameObjectType getType() {
		return GameObjectType::enemyObject;
	}

	friend ostream& operator<< ( ostream & stream, EnemyObject& object)	{
		return stream<<"Enemy ("<<object.getPosition()<<") ";
	}
private:
//  AI component
	AI_TYPE myAI;
	AIComponent	mAIComponent;

};


