#pragma once

/** Class containing Ogre::SceneNode and providing functions for usage
  * Objects of this class are part of GameObject as components 
  * It contains methods manipulating rotation and position
  * @author konkit
  * 
  */
class GraphicsComponent
{
public:
	GraphicsComponent() : mNode(NULL)	{
	}

	GraphicsComponent(Ogre::SceneNode* newNode) : mNode(NULL)	
	{
		mNode = newNode;
	}
	~GraphicsComponent(){};
	void initGraphicComponent(std::string meshName, Ogre::SceneManager * _sceneMenager)
	{
		Ogre::Entity * tmp = _sceneMenager->createEntity(meshName);
		mNode = _sceneMenager->getRootSceneNode()->createChildSceneNode();
		mNode->attachObject(tmp);
	}

	Ogre::SceneNode* getOgreNode() {return mNode;}

	void initNode( Ogre::SceneNode* newNode )	{
		if (mNode != NULL)
		{
			delete mNode;
		}
		mNode = newNode; 
	}

	//void move(Ogre::Vector3 nPos) {
	//	mNode->translate( mNode->getOrientation() * nPos );
	//}

	//void rotate(float rotVelocity)	{
	//	mNode->yaw( Ogre::Radian(rotVelocity) );
	//}

	//void setPosition(Ogre::Vector3 newPos)	{
	//	mNode->setPosition( newPos );
	//}

	//Ogre::Vector3 getPosition()	{
	//	return mNode->getPosition();
	//}

	//void setOrientation(Ogre::Quaternion norientation)	{
	//	mNode->setOrientation(norientation);
	//}

	//Ogre::Quaternion getOrientation()	{
	//	//get proper quaterion
	//	return mNode->getOrientation();
	//}

	Ogre::SceneNode* getNode()	{ return mNode; }

private:
	Ogre::SceneNode* mNode;

};