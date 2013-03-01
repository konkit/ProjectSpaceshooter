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
	Ogre::RenderWindow* getWindowHandle()	{	return mWindow;	}
	Ogre::Root*			getRoot()	{		return mRoot;	}

private:
	//Root object of Ogre
	Ogre::Root* mRoot;
	//Name of file with resources
	Ogre::String mResourcesCfg;
	//Render window object
	Ogre::RenderWindow* mWindow;
	//OpenGL plugin
	Ogre::GLPlugin* mGLPlugin;
};



void OgreManager::initOgre()
{
	// Create OgreRoot
	mRoot = OGRE_NEW Ogre::Root();

	// install openGL plugin
	mGLPlugin = OGRE_NEW Ogre::GLPlugin();
	mRoot->installPlugin(mGLPlugin);

	// Load config file and init window
	mRoot->restoreConfig();

	// Create render window
	mWindow = mRoot->initialise(true, "Project SpaceShooter");
	
	//Set filenames
	#ifdef _DEBUG
		Ogre::String mResourcesCfg = "resources_d.cfg";
	#else
		Ogre::String mResourcesCfg = "resources.cfg";
	#endif

	// set up resources
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);
	
	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

