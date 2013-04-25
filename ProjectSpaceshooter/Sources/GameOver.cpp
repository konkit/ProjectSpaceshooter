#include "GameOver.h"

GameOver::GameOver( SystemsSet & gameSystems )
	: deadCamera(false)
{
	mCamera = gameSystems.gameData.getCameraFor(GAME_STATES::PLAY);
	gameSystems.gameData.setCameraFor(GAME_STATES::GAME_OVER, mCamera);
}

GameOver::~GameOver()
{

}
GAME_STATES GameOver::update( SystemsSet & gameSystems, TimeData& time )
{
	if (!deadCamera)
	{
		setDeadCamera(gameSystems);
	}
	gameSystems.mAISystem.update(gameSystems.gameData, time);
	gameSystems.mPhysicsSystem.update( gameSystems.gameData, time.deltaTime );
	gameSystems.mCollisionSystem.update( gameSystems.gameData);
	gameSystems.mObjectStateSystem.update( gameSystems.gameData, time);
	renderOneFrame(gameSystems.ogreManager);
}

void GameOver::createCamera()
{
	throw std::exception("The method or operation is not implemented.");
}

GAME_STATES GameOver::nextState( SystemsSet & gameSystems )
{
	return GAME_STATES::GAME_OVER;
}

void GameOver::setDeadCamera( SystemsSet &gameSystems )
{
	GameData & gameData = gameSystems.gameData;
	Player * player = gameData.getPlayer();
	Ogre::Camera * camera = gameData.getCameraFor(GAME_STATES::PLAY);
	player->detachCamera();
	Vector3 position = player->getPosition();
	camera->setPosition(position + Vector3(30.0,30.0,0.0));
	camera->lookAt(position);
	deadCamera = true;
}




