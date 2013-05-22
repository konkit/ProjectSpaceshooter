#pragma once
#include "Ship.h"

/** Player class
  * Gameobject representing player's spaceship
  *
  * @author konkit
  */
class Player : public Ship
{
public:
	/** Loads data of effect from prefab */
	Player(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager);
	virtual ~Player();

	/** Sets ship stats with data from prefab */
	void setShip(const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager);
	GameObjectType getType();

	/** Returns camera node attached to player
	  * @return Ogre::SceneNode - node of camera
	  */
	Ogre::SceneNode * getCameraNode();

	/**    */
	void createCameraNodesAndChoseActivCameraNode( const ShipPrefab * objectTemplate );

	/**    */
	void createCameraNodes( const ShipPrefab * objectTemplate );

	/**    */
	void switchCameraToNextHandler();

	/**    */
	void detachCamera();

	/**    */
	void attachCamera( Ogre::Camera * cam );

	
	//score manipulators
		int getScore()	{
			return score;
		}

		void resetScore()	{
			score = 0;
		}

		void addScore(int value)	{
			score += value;
		}

private:
	Ogre::SceneNode * mCameraNode;
	list<cameraHandler>::iterator mActiveCameraDataIt;
	Ogre::Camera * my_cam;
	list<cameraHandler> myCameraHandlers;

	//score of the player
	int score;
};
