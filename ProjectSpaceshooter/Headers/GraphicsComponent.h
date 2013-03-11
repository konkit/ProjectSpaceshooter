#pragma once

class GraphicsComponent
{
public:
	GraphicsComponent(Ogre::SceneNode* newNode ) : mNode(NULL)	{
	}

	GraphicsComponent(Ogre::SceneNode* newNode) : mNode(NULL)	{
		mNode = newNode;
	}

	GraphicsComponent(std::string meshName, Ogre::SceneManager * _sceneMenager) : mNode(NULL)	
	{
		Ogre::Entity * tmp = _sceneMenager->createEntity(meshName);
		mNode->attachObject(tmp);
	}

	void updateNode(Ogre::Vector3 pos, float angle)	{
		if(mNode != NULL)
		{
			mNode->setPosition(pos);
			mNode->setOrientation(Ogre::Quaternion( Ogre::Radian(angle), Ogre::Vector3::UNIT_Y));
		}
	}

	Ogre::SceneNode* getOgreNode() {return mNode;}
	void initNode( Ogre::SceneNode* newNode )	{
		if (mNode != NULL)
		{
			delete mNode;
		}
		mNode = newNode; 
		
	}

	Ogre::SceneNode* getNode()	{ return mNode; }
private:
	Ogre::SceneNode* mNode;
};