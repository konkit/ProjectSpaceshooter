#pragma once
#include "Systems.h"
#include "TimeUtility.h"

/** Basic GameState class
*/
class GameState
{
protected:
	GameData * mGameData;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera * mCamera;
public:
	Ogre::SceneManager* getSceneMgr(){return mSceneMgr;}
	GameState() : mCamera(NULL) {}
	virtual ~GameState(){}
	virtual GAME_STATES update(SystemsSet & gameSystems, TimeData& time) = 0;
	void renderOneFrame(OgreManager & _ogreManager);
	Ogre::Camera * getCamera() {return mCamera;}
private:
	virtual	void createCamera() = 0;
	virtual GAME_STATES nextState(SystemsSet & gameSystems) = 0;
};
