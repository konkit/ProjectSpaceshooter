#pragma once

#include "OgreManager.h"
#include "GameData.h"

//do wywalenia - jak sie wywali tez TransformComponent i wszystko zapisze w node'ie

class GraphicsSystem
{
public:
	GraphicsSystem();


	void init(OgreManager* cntOgreManager);

	void updateNodesAndDrawForPlay( GameData& mGameData );


	void updateNodesAndDrawForPause( GameData& mGameData );

private:
	inline void renderFrame();
	inline void updatePlayer( GameData &mGameData );
	inline void updateEnemies( GameData &mGameData );
	inline void updateBullets( GameData &mGameData );
	OgreManager* mOgreManager;
};