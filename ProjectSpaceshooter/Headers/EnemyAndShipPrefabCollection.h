#pragma once

#include "BaseCollection.h"

/** Collection for enemies connected with ship prefabs 
  * 
  * @author 
  */
class EnemyAndShipPrefabsCollections : public BaseCollection<ShipPrefab, EnemyObject>
{
public: 
	/** constructor */
	EnemyAndShipPrefabsCollections();

	/** Create enemy from prefab with given ID and add it to collection */
	EnemyObject * instantiateEnemy(int ID, AI_TYPE myAi, Ogre::SceneManager* sceneMgr);

	/** Returns weapon collection */
	vector<WeaponPrefab> getWeaponCollection() const;

	/** returns weapon prefab with given ID */
	const WeaponPrefab * getWeaponPrefab(unsigned prefabID) const;

	/** save new prefab to collection */
	void addWeaponPrefab(const WeaponPrefab& _weaponPrefab);

	/** set new size of weapon prefab collection */
	void setCountOfWeaponPrefab(unsigned max_id);

	/** set new size of ship prefab collection */
	void setCountOfShipPrefab(unsigned max_id);

private:
	vector<WeaponPrefab> mWeaponCollection;
};