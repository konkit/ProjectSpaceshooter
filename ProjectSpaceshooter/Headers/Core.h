#pragma once


class Core : public GameObject	{
public:
	Core() : GameObject()
	{

	}

	Core(std::string meshName, Ogre::SceneManager* sceneMgr) : GameObject(meshName, sceneMgr)	
	{

	}


private:


};