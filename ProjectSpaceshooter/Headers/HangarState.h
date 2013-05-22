#pragma once
#include "GameState.h"
#include "TimeUtility.h"

struct shipPad_Struct
{
	unsigned prefabID;
	Vector3  position;
};
class HangarState : public GameState
{
public:
	HangarState(SystemsSet & gameSystems);
	~HangarState(){};

	/** all updates of systems are here */
	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

private:
	/** create the camera */
	virtual void createCamera();

	/** returns next game state */
	virtual GAME_STATES nextState( SystemsSet & gameSystems );

	/** updates camera position depending on current choice */
	void updateCameraPosition( SystemsSet & gameSystems, TimeData& time );


	vector<shipPad_Struct> shipsPads;
	unsigned shipsNumber;
	const unsigned offsetBetweenShips;
	const unsigned CameraOffset;
	GameCollection<Ship> ships;
};