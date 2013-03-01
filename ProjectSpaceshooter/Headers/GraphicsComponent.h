#pragma once

class GraphicsComponent
{
public:
	GraphicsComponent() : mNode(NULL)	{
	}


	void updateNode(float posX, float posY, float posZ)	{
		if(mNode != NULL)
			mNode->setPosition(Ogre::Vector3(posX, posY, posZ));
	}

	void initNode( Ogre::SceneNode* newNode )	{
		mNode = newNode; 
	}



private:
	Ogre::SceneNode* mNode;

};