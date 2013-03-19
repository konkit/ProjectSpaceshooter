#pragma once


class CollisionSystem	{
public:
	//Method which resolves collisions
	//collisions are resolved a posteriori
	void update(GameData& mGameData)	{

		//for every object1
		GameObject *currentObject = mGameData.getPlayer();

		CheckForCollisions( mGameData.getPlayer(), mGameData, "player" );

		GameCollectionIterator<Bullet> * myBulletIterator = mGameData.getBullets().getBulletIterator();
		GameObject* it;
		while (myBulletIterator->hasNext())
		{
			it = myBulletIterator->getNext();
			CheckForCollisions( it, mGameData, "bullet" );
		}

		GameCollectionIterator<EnemyObject> * myEnemyIterator = mGameData.getEnemys().getEnemyIterator();
		while (myEnemyIterator->hasNext())
		{
			it = myEnemyIterator->getNext();
			CheckForCollisions( it, mGameData, "enemy" );
		}
				
	}

	void CheckForCollisions( GameObject* currentObject, GameData& mGameData, std::string typeName )	{
		//for every object2
		GameCollectionIterator<Bullet> * myBulletIterator = mGameData.getBullets().getBulletIterator();
		GameObject* it;
		bool isColliding;
		while (myBulletIterator->hasNext())
		{
			it = myBulletIterator->getNext();

			if( it == currentObject)
				continue;

			isColliding = 
				Collider::isCollisionOccuring( currentObject->getCollider(), it->getCollider(), currentObject->getPosition(), it->getPosition() );

			if( isColliding == true )	
				std::cout<<"Collision of "<<typeName<<" with bullet \n";
		}

		GameCollectionIterator<EnemyObject> * myEnemyIterator = mGameData.getEnemys().getEnemyIterator();
		while (myEnemyIterator->hasNext())
		{
			it = myEnemyIterator->getNext();

			if( it == currentObject)
				continue;

			isColliding = 
				Collider::isCollisionOccuring( currentObject->getCollider(), it->getCollider(), currentObject->getPosition(), it->getPosition() );

			if( isColliding == true )
			{
				std::cout<<"Collision of "<<typeName<<" with enemy\n";
			}
		}
	}



private:

};
