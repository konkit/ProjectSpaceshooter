#pragma once



/** Player class
  *
  * @author konkit
  */
class Player : public GameObject
{
public:
	Player( Ogre::SceneManager * _sceneMenager)	{
		//mGraphicsComponent.initGraphicComponent()
	}
}
	~EnemyObject();
	unsigned int mResistance;

	void setShoot(unsigned long currentTime)	{
		mGamelogicComponent.setShoot(currentTime);
	}

	void unsetShoot()	{
		mGamelogicComponent.unsetShoot();
	}

	bool isShooting()	{
		return mGamelogicComponent.isShooting();
	}

private:  
};