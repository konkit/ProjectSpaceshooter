#include "GameOver.h"



GameOver::~GameOver()
{

}

GAME_STATES GameOver::update( SystemsSet & gameSystems, TimeData& time )
{
	if (!deadCamera)
	{
		setDeadCamera(gameSystems);
		gameSystems.mObjectStateSystem.destroyPlayer(gameSystems.gameData);
	}
	gameSystems.inputManager.updateInputForPause(gameSystems.gameData);
	gameSystems.mAISystem.update(gameSystems.gameData, time);
	gameSystems.mPhysicsSystem.update( gameSystems.gameData, time.deltaTime );
	gameSystems.mCollisionSystem.update( gameSystems.gameData);
	gameSystems.mObjectStateSystem.update( gameSystems.gameData, time);

	gameSystems.mGUISystem.display(gameSystems.gameData, time, GAME_STATES::GAME_OVER);

#ifdef _DEBUG
	DebugDrawer::getSingleton().build();
#endif

	renderOneFrame(gameSystems.ogreManager);

#ifdef _DEBUG
	DebugDrawer::getSingleton().clear();
#endif
	return nextState(gameSystems);
}

void GameOver::createCamera()
{
	throw std::exception("The method or operation is not implemented.");
}

GAME_STATES GameOver::nextState( SystemsSet & gameSystems )
{
	if (gameSystems.gameData.isSetPlayFlag())
	{
		deadCamera = false;
		return GAME_STATES::HANGAR;
		gameSystems.gameData.getPlayer()->resetScore();
	}
	return GAME_STATES::GAME_OVER;
}

void GameOver::setDeadCamera( SystemsSet &gameSystems )
{
	GameData & gameData = gameSystems.gameData;
	Player * player = gameData.getPlayer();
	Ogre::Camera * camera = gameData.getCameraFor(GAME_STATES::PLAY);
	player->detachCamera();
	Vector3 position = player->getPosition();
	camera->setPosition(position + Vector3(70.0,30.0,-70.0));
	camera->lookAt(position);
	deadCamera = true;
}

GameOver::GameOver( SystemsSet & gameSystems )
	: deadCamera(false)
{
	mCamera = gameSystems.gameData.getCameraFor(GAME_STATES::PLAY);
	gameSystems.gameData.setCameraFor(GAME_STATES::GAME_OVER, mCamera);
		gameSystems.mGUISystem.init( mSceneMgr, GAME_STATES::GAME_OVER);
}




