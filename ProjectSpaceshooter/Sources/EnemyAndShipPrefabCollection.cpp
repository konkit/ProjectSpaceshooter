
void EnemyAndShipPrefabsCollections::setCountOfShipPrefab( unsigned max_id )
{
	mPrefabs.resize(max_id);
}

void EnemyAndShipPrefabsCollections::setCountOfWeaponPrefab( unsigned max_id )
{
	mWeaponCollection.resize(max_id);
}

void EnemyAndShipPrefabsCollections::addWeaponPrefab( const WeaponPrefab& _weaponPrefab )
{
	if (&_weaponPrefab == NULL)
	{
		throw My_Exception("addWeaponPrefab: Can't add NULL Weapon Prefab");
	}
	unsigned prefabID = _weaponPrefab.getPrefabID(); 
	if (prefabID >= mWeaponCollection.size())
	{
		mWeaponCollection.resize(prefabID+1);
	}
	mWeaponCollection[prefabID] = _weaponPrefab;
}

const WeaponPrefab * EnemyAndShipPrefabsCollections::getWeaponPrefab( unsigned prefabID ) const
{
	if (prefabID < mWeaponCollection.size())
	{
		return &mWeaponCollection[prefabID];
	}
	using std::string;
	std::stringstream exceptionString;
	exceptionString << "There are no prefab with id =" << prefabID << " in weapon prefab collection ";
	throw My_Exception(exceptionString.str().c_str());
}

vector<WeaponPrefab> EnemyAndShipPrefabsCollections::getWeaponCollection() const
{
	return mWeaponCollection;
}

EnemyObject * EnemyAndShipPrefabsCollections::instantiateEnemy( int ID, AI_TYPE myAi, Ogre::SceneManager* sceneMgr )
{
	//get prefab with id given
	const ShipPrefab* currentPrefab = getPrefab(ID);
	const WeaponPrefab* weaponPref = &mWeaponCollection[currentPrefab->getWeaponPrefabID()];
	//create new object from prefab
	EnemyObject * newObject = new EnemyObject(currentPrefab, weaponPref, myAi, sceneMgr);

	//add it to the collection
	mCollection.addObject(newObject);
	return newObject;
}

EnemyAndShipPrefabsCollections::EnemyAndShipPrefabsCollections() : BaseCollection("Enemy And ShipPrefabs Collections"), mWeaponCollection(20)
{

}

