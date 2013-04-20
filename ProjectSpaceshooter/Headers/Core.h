#pragma once


class Core : public GameObject	{
public:
	Core() : GameObject()
	{

	}

	Core(std::string meshName, Ogre::SceneManager* sceneMgr) : GameObject(meshName, sceneMgr)	
	{

	}
	Ogre::SceneNode* getSceneNode(){return this->mNode;}

	GameObjectType getType() {
		return GameObjectType::core;
	}

private:


};