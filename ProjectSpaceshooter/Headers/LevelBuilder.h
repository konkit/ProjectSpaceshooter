#pragma once

class LevelBuilder : public GameState
{
public:
	LevelBuilder(SystemsSet & gameSystems);
	~LevelBuilder();

	bool update( SystemsSet & gameSystems, TimeData time );

	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

	void loadLevelDescribe( SystemsSet & gameSystems );

private:
	//Lever builder required camera because in refuter it will show progress bar
	virtual void createCamera();
	virtual GAME_STATES nextState( SystemsSet & gameSystems );
};