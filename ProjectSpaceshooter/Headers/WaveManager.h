#pragma once

#include "GameData.h"


class WaveManager {
public:
	WaveManager() : waveNumber(0), enemySpawnerPos(0.0, 0.0, 200.0)	{

	}

	void setSpawnerPos(Ogre::Vector3 pos)	{

	}

	void update(GameData& mGameData, unsigned currentTime)	{
		//check if previous wave is still alive
		//bool isEmpty = mGameData.getEnemies().isCollectionEmpty();
		EnemyAndShipPrefabsCollections& enemies = mGameData.getEnemies();
		bool isEmpty = enemies.isCollectionEmpty();

		//if no, then spawn new wave
		if( isEmpty == true ) {
			unsigned enemyType;
			int numberOfEnemies;

			//increase wave number
			waveNumber++;

			//get number of enemies
			numberOfEnemies = waveNumber + 3;

			//get type of enemies
			enemyType = 1;

			//add message, that next wave is approaching
			mGameData.getMessageConsole().addNewMessage("Wave "+std::to_string(waveNumber)+" approaching! \n");

			//for 
			for( int i=0; i<numberOfEnemies; i++)	{
				//spawn proper enemies in proper place
				EnemyObject * tmpEnemy = 
					mGameData.getEnemies().instantiateEnemy(enemyType, 
															AI_TYPE::fighter, 
															mGameData.getSceneManagerFor(GAME_STATES::PLAY) 
															);
				Vector3 newPosition = enemySpawnerPos + Vector3(200.0*(i-1), 0.0, 0.0);
				tmpEnemy->setPosition(newPosition);
			}
		}
	}

private:
	int waveNumber;
	Ogre::Vector3 enemySpawnerPos;
};
