#pragma once

#include "BaseCollection.h"
class EnemyAndShipPrefabsCollections : public BaseCollection<ShipPrefab, EnemyObject>
{
public: 
	EnemyAndShipPrefabsCollections();
	EnemyObject * instantiateEnemy(int ID, AI_TYPE myAi, Ogre::SceneManager* sceneMgr);
	vector<WeaponPrefab> getWeaponCollection() const;
	const WeaponPrefab * getWeaponPrefab(unsigned prefabID) const;
	void addWeaponPrefab(const WeaponPrefab& _weaponPrefab);

	void setCountOfWeaponPrefab(unsigned max_id);
	void setCountOfShipPrefab(unsigned max_id);
private:
	vector<WeaponPrefab> mWeaponCollection;
};