#include "GameState.h"

class GameOver : public GameState
{
public:
	GameOver( SystemsSet & gameSystems );
	virtual ~GameOver();

	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

	void setDeadCamera( SystemsSet &gameSystems );

	virtual void createCamera();

	virtual GAME_STATES nextState( SystemsSet & gameSystems );
	bool deadCamera;
private:

};