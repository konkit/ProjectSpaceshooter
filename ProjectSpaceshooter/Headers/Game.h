#ifndef __SPACESHOOTER_GAME__
#define __SPACESHOOTER_GAME__

#include "InputManager.h"


class Game 
{
public:
	bool run();

	
	float camX, camY, camZ;

private:
	InputManager mInputManager;
	//OgreManager
	//GameData

	//Do ogre managera
		//Root object of Ogre
		Ogre::Root* mRoot;
		//Name of file with resources
		Ogre::String mResourcesCfg;
		//Render window object
		Ogre::RenderWindow* mWindow;
		//OpenGL plugin
		Ogre::GLPlugin* mGLPlugin;

		Ogre::RenderWindow* getWindowHandle()	{	return mWindow;	}
		Ogre::Root*			getRoot()	{		return mRoot;	}

		//inner functions
		void initOgre();
	
	//Do GameData
		Ogre::SceneManager* mSceneMgr;
		Ogre::Camera* mCamera;







	void initScene();
	void setScene();
};









 



#endif