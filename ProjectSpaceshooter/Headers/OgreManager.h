#pragma once




//Class enveloping Ogre3D library and simplifying usage.
//Stores Ogre::Root and other library-specific data
class OgreManager
{
public:
	//function which initializes Ogre
	//must be run before OIS initialization
	void initOgre();

	//getters for root and renderwindow
	Ogre::RenderWindow* getWindowHandle();
	Ogre::Root*			getRoot();

	float getDeltaTime()	{
		float deltaTime = ( mTime.getMilliseconds() - lastTime) / 1000.0;
		lastTime = mTime.getMilliseconds();

		return deltaTime;
	}

	unsigned long getCurrentTime()	{
		return mTime.getMilliseconds();
	}


private:
	//Root object of Ogre
	Ogre::Root* mRoot;
	//Name of file with resources
	Ogre::String mResourcesCfg;
	//Render window object
	Ogre::RenderWindow* mWindow;
	//OpenGL plugin
	Ogre::GLPlugin* mGLPlugin;
	//Timer
	Ogre::Timer mTime;
	unsigned long lastTime;
};

