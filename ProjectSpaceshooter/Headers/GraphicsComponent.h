#pragma once

class GraphicsComponent
{
public:
	GraphicsComponent() : mNode(NULL)	{
	}


	void updateNode(Ogre::Vector3 pos, float angle)	{
		if(mNode != NULL)
		{
			mNode->setPosition(pos);
			mNode->setOrientation(Ogre::Quaternion( Ogre::Radian(angle), Ogre::Vector3::UNIT_Y));
		}
	}

	void initNode( Ogre::SceneNode* newNode )	{
		mNode = newNode; 
		
	}

	Ogre::SceneNode* getNode()	{ return mNode; }

private:
	Ogre::SceneNode* mNode;
};