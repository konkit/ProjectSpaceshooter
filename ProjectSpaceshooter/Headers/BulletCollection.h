#pragma once
#include "BaseCollection.h"


/** This is collection which stores bullets
  * Bullets are game objects created most intensively
  * so creation of them must be treated individually
  *
  * @author Zyga
  */
class BulletCollection : public BaseCollection<BulletPrefab, Bullet>
{
public:
	/** Basic constructor, sets initial values of precreated count 
	 *
	 * @return 
	 * @author Zyga
	 */
	BulletCollection();

	/** create bullets in datapool 
	 *
	 * @return 
	 * @param sceneManager 
	 * @author Zyga
	 */
	void initializeBullet(Ogre::SceneManager * sceneManager);

	/** get free bullet from datapool and copy it to collection
	 *
	 * @return
	 * @param prefabID 
	 * @param sceneMgr 
	 * @author Zyga
	 */
	Bullet * instantiate(unsigned prefabID, Ogre::SceneManager* sceneMgr);

	/** remove bullet from collection and return it to datapool
	 *
	 * @return 
	 * @param it 
	 * @author Zyga
	 */
	void destroyBullet(GameCollectionIterator<Bullet> &it);

	/**
	 * 
	 *
	 * @return 
	 * @param it 
	 * @author Zyga
	 */
	void destroyBullet(Bullet * it);

	/** clears the whole collection 
	 *
	 * @return 
	 * @author Zyga
	 */
	void clearCollection();

private:
	/** nuber of pre-created objects in datapool */
	const int preCreatedCount;

	/** Vector of datapools of bullets. 
	  * Each type is in separate collection */
	std::vector<GameCollection<Bullet>> dataPool;

	/** pointer to scene manager of play gamestate */
	Ogre::SceneManager * playSceneManager;
};