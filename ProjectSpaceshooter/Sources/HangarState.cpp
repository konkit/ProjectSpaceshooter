#include "GameState.h"


HangarState::HangarState( SystemsSet & gameSystems )
	:GameState(), shipsNumber(0), offsetBetweenShips(100), CameraOffset(200)
{
	mSceneMgr = gameSystems.ogreManager.getRoot()->createSceneManager(Ogre::ST_GENERIC, "hangar");
	gameSystems.gameData.setSceneMenagerFor(GAME_STATES::HANGAR, mSceneMgr);
	createCamera();
	gameSystems.gameData.setCameraFor(GAME_STATES::HANGAR, mCamera);


	mSceneMgr->setSkyBox(true, "Sky2");

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	// Create a light
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(-50,50,0);
	light->setPowerScale(200.0);

	mGameData = &(gameSystems.gameData);
	unsigned prefabNum = mGameData->getEnemies().getNumberOfPrefabs();
	shipsPads.resize(prefabNum + 1);

	Ship * ship;
	ShipPrefab * prefab;
	const WeaponPrefab * weapon;
	shipPad_Struct pad;
	HangarManipulator & manip = mGameData->getHangarManipulator();
	for (unsigned i = 1; i <= prefabNum; i++)
	{
		try
		{
			prefab = mGameData->getEnemies().getPrefab(i);
			weapon = mGameData->getWeaponPrefab(prefab->getWeaponPrefabID());
			ship = new Ship(prefab, weapon, mSceneMgr);
			shipsNumber++;
			pad.prefabID = i;
			pad.position = Vector3(offsetBetweenShips* (i-1), 0,0);
			shipsPads[shipsNumber] = pad;
			ship->setPosition(pad.position);
			ships.addObject(ship);
		}
		catch (PrefabException& e)
		{
			if (e.getType() == PrefabExceptionType::NO_PREFAB)
			{
			}
		}		
	}
	manip.activeShip = 1;
	manip.shipPrefab = shipsPads[1].prefabID;

	//Initialize GUI system
	gameSystems.mGUISystem.init( mSceneMgr, GAME_STATES::HANGAR );
}


GAME_STATES HangarState::update( SystemsSet & gameSystems, TimeData& time )
{
	gameSystems.inputManager.updateInputForHangar(gameSystems.gameData);
	updateCameraPosition(gameSystems, time);

	gameSystems.mGUISystem.display(gameSystems.gameData, time, GAME_STATES::HANGAR);

	renderOneFrame(gameSystems.ogreManager);
	return nextState(gameSystems);
}

void HangarState::createCamera()
{
	// create the camera
	mCamera = mSceneMgr->createCamera("HangarCam");
	// set its position, direction  
	mCamera->setPosition(Ogre::Vector3(0.0,0.0, CameraOffset));
	mCamera->lookAt(Ogre::Vector3(0,0.0,0.0));
	// set the near clip distance
	mCamera->setNearClipDistance(5);
}

GAME_STATES HangarState::nextState( SystemsSet & gameSystems )
{
	HangarManipulator & manip = gameSystems.gameData.getHangarManipulator();
	if (manip.acceptModel == true)
	{
		manip.acceptModel = false;
		return GAME_STATES::LEVEL_BUILDER;
	} else
		return GAME_STATES::HANGAR;
}

void HangarState::updateCameraPosition( SystemsSet & gameSystems, TimeData& time )
{
	Vector3 tmp;
	HangarManipulator & manip = gameSystems.gameData.getHangarManipulator();
	if (manip.moveToNext == true && manip.activeShip < shipsNumber)
	{
		manip.activeShip++;
	} else if (manip.moveToPrev == true && manip.activeShip > 1)
	{
		manip.activeShip--;
	}
	shipPad_Struct & pad = shipsPads[manip.activeShip];
	manip.shipPrefab = pad.prefabID;
	tmp = pad.position;
	tmp.z = CameraOffset;
	mCamera->setPosition(tmp);

	manip.moveToNext = false;
	manip.moveToPrev = false;
}
