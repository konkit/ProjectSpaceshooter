#pragma once

class GraphicsComponent
{
public:
	GraphicsComponent() : mNode(NULL)	{
	}


	void updateNode(float posX, float posY, float posZ, float angle)	{
		if(mNode != NULL)
			mNode->setPosition(Ogre::Vector3(posX, posY, posZ));
			mNode->setOrientation(Ogre::Quaternion( Ogre::Radian(angle), Ogre::Vector3::UNIT_Y));
	}

	void initNode( Ogre::SceneNode* newNode )	{
		mNode = newNode; 
	}



private:
	Ogre::SceneNode* mNode;

};