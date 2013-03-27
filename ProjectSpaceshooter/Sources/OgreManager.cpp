#include "OgreManager.h"

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

	loadResources();

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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

