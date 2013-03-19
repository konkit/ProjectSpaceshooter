#pragma once


class CollisionSystem	{
public:
	//Method which resolves collisions
	//collisions are resolved a posteriori
	void update(GameData& mGameData)	{
		CheckForCollisions( mGameData.getPlayer(), mGameData, "player" );

		GameCollectionIterator<Bullet> * myBulletIterator = mGameData.getBullets().getBulletIterator();
		Bullet* itBullet;
		while (myBulletIterator->hasNext())
		{
			itBullet = myBulletIterator->getNext();
			CheckForCollisions( itBullet, mGameData, "bullet" );
		}

		GameCollectionIterator<EnemyObject> * myEnemyIterator = mGameData.getEnemys().getEnemyIterator();
		EnemyObject* itEnemy;
		while (myEnemyIterator->hasNext())
		{
			itEnemy = myEnemyIterator->getNext();
			CheckForCollisions( itEnemy, mGameData, "enemy" );
		}
				
	}

	void CheckForCollisions( GameObject* currentObject, GameData& mGameData, std::string typeName )	{
		//for every object2
		GameCollectionIterator<Bullet> * myBulletIterator = mGameData.getBullets().getBulletIterator();
		Bullet* itBullet;
		bool isColliding;
		while (myBulletIterator->hasNext())
		{
			itBullet = myBulletIterator->getNext();

			if( itBullet == currentObject)
				continue;

			isColliding = 
				Collider::isCollisionOccuring( currentObject->getCollider(), itBullet->getCollider(), currentObject->getPosition(), itBullet->getPosition() );

			if( isColliding == true )	
			{
				std::cout<<"Collision of "<<typeName<<" with bullet \n";
				//PROWIZOOOORKAAAA
				if(typeName == "enemy")	{
					currentObject->getGamelogicComponent().die();
				}
			}
		}
		delete myBulletIterator;

		GameCollectionIterator<EnemyObject> * myEnemyIterator = mGameData.getEnemys().getEnemyIterator();
		EnemyObject* itEnemy;
		while (myEnemyIterator->hasNext())
		{
			itEnemy = myEnemyIterator->getNext();

			if( itEnemy == currentObject)
				continue;

			isColliding = 
				Collider::isCollisionOccuring( currentObject->getCollider(), itEnemy->getCollider(), currentObject->getPosition(), itEnemy->getPosition() );

			if( isColliding == true )
			{
				std::cout<<"Collision of "<<typeName<<" with enemy\n";
			}
		}
		delete myEnemyIterator;
	}



private:

};
