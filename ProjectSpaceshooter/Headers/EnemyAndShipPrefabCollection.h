#pragma once

#include "BaseCollection.h"

/** Collection for enemies connected with ship prefabs 
  * 
  * @author 
  */
class EnemyAndShipPrefabsCollections : public BaseCollection<ShipPrefab, EnemyObject>
{
public: 
	/** constructor
	 *
	 * @return 
	 * @author Zyga
	 */
	EnemyAndShipPrefabsCollections();

	/** Create enemy from prefab with given ID and add it to collection
	 *
	 * @return 
	 * @param ID 
	 * @param myAi 
	 * @param sceneMgr 
	 * @author Zyga
	 */
	EnemyObject * instantiateEnemy(int ID, AI_TYPE myAi, Ogre::SceneManager* sceneMgr);

	/** Returns weapon collection 
	 * @return 
	 * @author Zyga
	 */
	vector<WeaponPrefab> getWeaponCollection() const;

	/** returns weapon prefab with given ID 
	 *
	 * @return 
	 * @param prefabID 
	 * @author Zyga
	 */
	const WeaponPrefab * getWeaponPrefab(unsigned prefabID) const;

	/** save new prefab to collection
	 *
	 * @return 
	 * @param _weaponPrefab 
	 * @author Zyga
	 */
	void addWeaponPrefab(const WeaponPrefab& _weaponPrefab);

	/** set new size of weapon prefab collection 
	 *
	 * @return 
	 * @param max_id 
	 * @author Zyga
	 */
	void setCountOfWeaponPrefab(unsigned max_id);

	/** set new size of ship prefab collection 
	 *
	 * @return 
	 * @param max_id 
	 * @author Zyga
	 */
	void setCountOfShipPrefab(unsigned max_id);

private:
	vector<WeaponPrefab> mWeaponCollection;
};