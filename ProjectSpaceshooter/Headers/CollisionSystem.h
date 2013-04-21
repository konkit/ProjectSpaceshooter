#pragma once

#include "DebugDrawer.h"

class CollisionSystem	{
public:
	//Method which resolves collisions
	//collisions are resolved a posteriori
	void update(GameData& mGameData)	{
		CheckForCollisions( mGameData.getPlayer(), mGameData, "player" );

		GameCollectionIterator<Bullet>  myBulletIterator = mGameData.getBullets().getIterator();
		Bullet* itBullet;
		while (myBulletIterator.hasNext())
		{
			itBullet = myBulletIterator.getNext();
			CheckForCollisions( itBullet, mGameData, "bullet" );
		}
		
		GameCollectionIterator<EnemyObject> myEnemyIterator = mGameData.getEnemies().getIterator();
		EnemyObject* itEnemy;
		while (myEnemyIterator.hasNext())
		{
			itEnemy = myEnemyIterator.getNext();
			CheckForCollisions( itEnemy, mGameData, "enemy" );
		}
					
	}

	void CheckForCollisions( GameObject* currentObject, GameData& mGameData, std::string typeName )	{
		//for every object2
		GameCollectionIterator<Bullet> myBulletIterator = mGameData.getBullets().getIterator();
		Bullet* itBullet;
		bool isColliding;
		while (myBulletIterator.hasNext())
		{
			itBullet = myBulletIterator.getNext();

			if( itBullet == currentObject)
				continue;

			isColliding = 
				Collider::isCollisionOccuring( currentObject->getCollider(), itBullet->getCollider(), currentObject->getPosition(), itBullet->getPosition() );

			if( isColliding == true )	
			{
				//std::cout<<"Collision of "<<typeName<<" with bullet \n";

				//PROWIZOOOORKAAAA - trzeba wykminic lepszy system rozpoznawania jakie typy obiektow sie zderzyly
				//a) polimorfizm - metoda getType
				//b) polimorfizm ale jakis niejawny - jakas metoda doSomething( objekt1)
				//c) jakies RTTI ? O_o

				if(typeName == "enemy" && itBullet->getOwner() != NULL && itBullet->getOwner() != currentObject )
				{
						currentObject->setDead();
						itBullet->setDead();
				}
			}
		}

		GameCollectionIterator<EnemyObject> myEnemyIterator = mGameData.getEnemies().getIterator();
		EnemyObject* itEnemy;
		while (myEnemyIterator.hasNext())
		{
			itEnemy = myEnemyIterator.getNext();

			if( itEnemy == currentObject)
				continue;

			isColliding = 
				Collider::isCollisionOccuring( currentObject->getCollider(), itEnemy->getCollider(), currentObject->getPosition(), itEnemy->getPosition() );

			if( isColliding == true )
			{
				//std::cout<<"Collision of "<<typeName<<" with enemy\n";
			}
		}


		//Draw debug sphere
#ifdef _DEBUG
		DebugDrawer::getSingleton().drawCircle( currentObject->getPosition(), currentObject->getCollider().radius, 25, Ogre::ColourValue(1.0f, 1.0f, 1.0f) );
#endif 
	}



private:

};
