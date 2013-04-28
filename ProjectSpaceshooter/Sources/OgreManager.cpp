#include "OgreManager.h"

void OgreManager::initOgre()
{
#ifdef _DEBUG
	mPluginsCfg = "plugins_d.cfg";
#else
	mPluginsCfg = "plugins.cfg";
#endif

	// construct Ogre::Root
	mRoot = new Ogre::Root(mPluginsCfg);

	// Load config file and init window
	// configure
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(mRoot->restoreConfig() || mRoot->showConfigDialog())
	{
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		mWindow = mRoot->initialise(true, "Project: Spaceshooter");
	}
	else
	{
		//could not create window so we can all go home now ...
	}

	loadResources();

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mTime.reset();
	lastTime = 0;

	mTime.reset();
	lastTime = 0;

}

Ogre::Root* OgreManager::getRoot()
{
	return mRoot;
}

Ogre::RenderWindow* OgreManager::getWindowHandle()
{
	return mWindow;
}

void OgreManager::loadResources()
{
	//Set filenames
#ifdef _DEBUG
	Ogre::String mResourcesCfg = "resources_d.cfg";
#else
	Ogre::String mResourcesCfg = "resources.cfg";
#endif
	//-------------------------------------------------------------------------------------
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

}

