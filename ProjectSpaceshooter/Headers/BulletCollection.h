#pragma once
#include "BaseCollection.h"

class BulletCollection : public BaseCollection<BulletPrefab, Bullet>
{
public:
	BulletCollection();;
	void initializeBullet(Ogre::SceneManager * sceneManager);
	Bullet * instantiate(unsigned prefabID, Ogre::SceneManager* sceneMgr);
	void destroyBullet(GameCollectionIterator<Bullet> &it);
	void destroyBullet(Bullet * it);

	void clearCollection();

private:
	const int preCreatedCount;
	std::vector<GameCollection<Bullet>> createdBullet;
	Ogre::SceneManager * playSceneManager;
};