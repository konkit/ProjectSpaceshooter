#ifndef __SPACESHOOTER_INPUT_MANAGER__
#define __SPACESHOOTER_INPUT_MANAGER__


class GameData
{
public:
	void initScene();
	void setScene();
private:
	//All GameObjects
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

};

#endif