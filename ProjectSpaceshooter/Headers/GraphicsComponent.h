#pragma once

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