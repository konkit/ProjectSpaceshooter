#pragma once

/** Class containing Ogre::SceneNode and providing functions for usage
  * Objects of this class are part of GameObject as components 
  *
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

	//void updateNode(Ogre::Vector3 pos, float angle)	{
	//	if(mNode != NULL)
	//	{
	//		mNode->setPosition(pos);
	//		mNode->setOrientation(Ogre::Quaternion( Ogre::Radian(angle), Ogre::Vector3::UNIT_Y));
	//	}
	//}

	Ogre::SceneNode* getOgreNode() {return mNode;}

	void initNode( Ogre::SceneNode* newNode )	{
		if (mNode != NULL)
		{
			delete mNode;
		}
		mNode = newNode; 
		
	}
	void move(Ogre::Vector3 nPos) {
		//float x = nPos.z * sin(angle) + nPos.x * cos(angle);
		//float z = nPos.z * cos(angle) - nPos.x * sin(angle);
		mNode->translate( mNode->getOrientation() * nPos );
	}

	void rotate(float rotVelocity)	{
		//angle += rotVelocity;
		mNode->yaw( Ogre::Radian(rotVelocity) );
	}

	void setPosition(Ogre::Vector3 newPos)	{
		//pos = newPos;
		mNode->setPosition( newPos );
	}

	Ogre::Vector3 getPosition()	{
		return mNode->getPosition();
	}

	void setOrientation(Ogre::Quaternion norientation)	{
		//angle = nangle;
		//mNode->setOrientation(Ogre::Quaternion( Ogre::Radian(nangle), Ogre::Vector3::UNIT_Y));
		mNode->setOrientation(norientation);
	}

	Ogre::Quaternion getOrientation()	{
		//get proper quaterion
		return mNode->getOrientation();
	}

	Ogre::SceneNode* getNode()	{ return mNode; }

private:
	Ogre::SceneNode* mNode;

};