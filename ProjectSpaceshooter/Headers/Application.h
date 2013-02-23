#ifndef __SPACESHOOTER_APPLICATION__
#define __SPACESHOOTER_APPLICATION__


class Application
{
public:
	Application();
	~Application();

	bool run();

private:
	//Root object of Ogre
	Ogre::Root* mRoot;
	//Name of file with plugins
    Ogre::String mPluginsCfg;
	//Name of file with resources
	Ogre::String mResourcesCfg;
	//Render window object
	Ogre::RenderWindow* mWindow;
	
	//Ogre Scene Manager
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	Ogre::GLPlugin* mGLPlugin;

};

#endif



