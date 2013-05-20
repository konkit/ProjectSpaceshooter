#include "Player.h"

void Player::switchCameraToNextHandler()
{
	mActiveCameraDataIt++;
	if (mActiveCameraDataIt == myCameraHandlers.end())
	{
		mActiveCameraDataIt = myCameraHandlers.begin();
	}
	mCameraNode->setPosition(mActiveCameraDataIt->offset);
	mCameraNode->lookAt(mActiveCameraDataIt->lookAt, Ogre::Node::TS_PARENT);
}

void Player::createCameraNodes( const ShipPrefab * objectTemplate )
{
	myCameraHandlers = objectTemplate->getCameraHandlersList();
	mCameraNode = mNode->createChildSceneNode("CameraNode");
}

void Player::createCameraNodesAndChoseActivCameraNode( const ShipPrefab * objectTemplate )
{
	createCameraNodes(objectTemplate);	
	mActiveCameraDataIt = myCameraHandlers.begin();
}

Ogre::SceneNode * Player::getCameraNode()
{
	return mCameraNode;
}

void Player::detachCamera()
{
	mCameraNode->detachObject(my_cam);
}

void Player::attachCamera( Ogre::Camera * cam )
{
	my_cam = cam;
	my_cam->setPosition(0.0, 0.0, 0.0);
	Ogre::Quaternion quat;
	my_cam->setOrientation(quat);
	mCameraNode->setOrientation(quat);
	mCameraNode->attachObject(cam);
	mCameraNode->setPosition(mActiveCameraDataIt->offset);
	mCameraNode->lookAt(mActiveCameraDataIt->lookAt, Ogre::Node::TS_PARENT);
	quat.FromAngleAxis(Ogre::Degree(-180), Vector3::UNIT_Z);
	mCameraNode->rotate(quat);
}

GameObjectType Player::getType()
{
	return GameObjectType::player;
}

void Player::setShip( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager )
{
	Ship::setShip(objectTemplate, weapon, _sceneMenager);
}

Player::~Player()
{
	detachCamera();
}

Player::Player( const ShipPrefab * objectTemplate,const WeaponPrefab * weapon, Ogre::SceneManager * _sceneMenager ) : GameObject(objectTemplate, _sceneMenager), Ship(objectTemplate,weapon, _sceneMenager)
{
	createCameraNodesAndChoseActivCameraNode(objectTemplate);
}

