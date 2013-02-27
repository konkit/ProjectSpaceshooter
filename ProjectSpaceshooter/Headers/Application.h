#ifndef __SPACESHOOTER_APPLICATION__
#define __SPACESHOOTER_APPLICATION__


class Application : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	Application();
	~Application();

	bool run();

	float camX, camY, camZ;

private:
	//Functions in init sequence
	void initScene();
	void setScene();
	void initOIS();
	bool updateInput(const Ogre::FrameEvent& evt);

	//Root object of Ogre
	Ogre::Root* mRoot;
	//Name of file with resources
	Ogre::String mResourcesCfg;
	//Render window object
	Ogre::RenderWindow* mWindow;
	
	//Ogre Scene Manager
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::GLPlugin* mGLPlugin;

	// OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;

	// Ogre::WindowEventListener
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);
 
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

};

#endif



