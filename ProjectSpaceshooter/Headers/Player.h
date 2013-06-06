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

	/** 
	  * @param objectTemplate - object with data of this ship
	  * @author Zyga
	  */
	void createCameraNodesAndChoseActivCameraNode( const ShipPrefab * objectTemplate );

	/** 
	  * @param objectTemplate - object with data of this ship
	  * @author Zyga
	  */
	void createCameraNodes( const ShipPrefab * objectTemplate );

	/** 
	  * @author Zyga
	  */
	void switchCameraToNextHandler();

	/** 
	  * @author Zyga
	  */
	void detachCamera();

	/** 
	  * @param camera - 
	  * @author Zyga
	  */
	void attachCamera( Ogre::Camera * cam );

	
	//score manipulators

		/** Returns current score
		  * @return score amount
		  * @author konkit
		  */
		int getScore()	{
			return score;
		}

		/** Sets current player score to zero
		  * @author konkit
		  */
		void resetScore()	{
			score = 0;
		}

		/** Adds given value to score amount
		  * @param additional score points amount
		  * @author konkit
		  */
		void addScore(int value)	{
			score += value;
		}

	friend ostream& operator<< ( ostream & stream, Player& object)	{
		return stream<<"Player ("<<object.getPosition()<<") ";
	}
private:
	Ogre::SceneNode * mCameraNode;
	list<cameraHandler>::iterator mActiveCameraDataIt;
	Ogre::Camera * my_cam;
	list<cameraHandler> myCameraHandlers;

	//score of the player
	int score;
};
