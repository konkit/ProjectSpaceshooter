
void BulletCollection::clearCollection()
{
	GameCollectionIterator<Bullet> it = mCollection.getIterator();
	while (it.hasNext())
	{
		it.getNext();
		destroyBullet(it);
	}
}

void BulletCollection::destroyBullet( Bullet * it )
{
	Bullet *tmp = mCollection.detachObject(it); 
	tmp->setVisible(false);
	createdBullet[tmp->getPrefabID()].addObject(tmp);
	return;
}

void BulletCollection::destroyBullet( GameCollectionIterator<Bullet> &it )
{
	Bullet *tmp = mCollection.detachObject(it); 
	tmp->setVisible(false);
	createdBullet[tmp->getPrefabID()].addObject(tmp);
	return;
}

Bullet * BulletCollection::instantiate( unsigned prefabID, Ogre::SceneManager* sceneMgr )
{
	Bullet * tmp = createdBullet[prefabID].detachFirst();
	if (tmp != NULL)
	{
		tmp->setVisible(true);
	} else
	{
		BulletPrefab * prefab = getPrefab(prefabID);
		tmp =  new Bullet(prefab, playSceneManager);
	}
	tmp->resetBullet();
	mCollection.addObject(tmp);
	return tmp;
}

void BulletCollection::initializeBullet( Ogre::SceneManager * sceneManager )
{
	playSceneManager = sceneManager;
	createdBullet.resize(mPrefabs.size());
	for(int i = 1; i < mPrefabs.size(); i++)
	{
		BulletPrefab * prefab;
		try
		{
			prefab = getPrefab(i);
		} catch (PrefabException & e)
		{
			if (e.getType() == PrefabExceptionType::NO_PREFAB)
			{
				continue;
			}			
		}
		// Create count of bullet
		for (int j = 0; j < preCreatedCount; j++)
		{

			Bullet * tmp =  new Bullet(prefab, sceneManager);
			tmp->setVisible(false);
			createdBullet[i].addObject(tmp); 
		}
	}
}

BulletCollection::BulletCollection() : BaseCollection("BulletCollection"), preCreatedCount(150)
{

}

