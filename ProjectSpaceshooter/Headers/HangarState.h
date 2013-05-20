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

	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

private:
	virtual void createCamera();
	virtual GAME_STATES nextState( SystemsSet & gameSystems );
	void updateCameraPosition( SystemsSet & gameSystems, TimeData& time );
	vector<shipPad_Struct> shipsPads;
	unsigned shipsNumber;
	const unsigned offsetBetweenShips;
	const unsigned CameraOffset;
	GameCollection<Ship> ships;
};