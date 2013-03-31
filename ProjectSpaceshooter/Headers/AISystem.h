#pragma once


/** 
  *
  * 
  * @author 
  */
class AISystem	{
	
public:
	void update(GameData& mGameData, float deltaTime);

	void randomAI(EnemyObject* it, GameData& mGameData);

	void toCoreAI( EnemyObject* it, GameData& mGameData );


private:


};