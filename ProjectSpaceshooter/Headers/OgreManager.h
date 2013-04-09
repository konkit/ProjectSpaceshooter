#pragma once







/** Class enveloping Ogre3D library and simplifying usage.
  * Stores Ogre::Root and other library-specific data
  * 
  * @author konkit 
  */
class OgreManager
{
public:
	OgreManager(){}
	~OgreManager()
	{
		delete mRoot;
		delete mGLPlugin;
	}
	//function which initializes Ogre
	//must be run before OIS initialization
	void initOgre();

	void loadResources();

	//getters for root and renderwindow
	Ogre::RenderWindow* getWindowHandle();
	Ogre::Root*			getRoot();

	//get time since last frame in fraction of SECONDS
	float getDeltaTime()	{
		float deltaTime = ( mTime.getMilliseconds() - lastTime) / 1000.0f;
		lastTime = mTime.getMilliseconds();

		return deltaTime;
	}

	//get current time (from start of program ? ) in MILISECONDS
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
	Ogre::ParticleFXPlugin* mParticlePlugin;
	//Timer
	Ogre::Timer mTime;
	unsigned long lastTime;
};

