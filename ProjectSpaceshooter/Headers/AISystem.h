#pragma once


/** 
  *
  * 
  * @author 
  */
class AISystem	{
	
public:
	void update(GameData& mGameData, float deltaTime)	{

		//For every enemy
		GameCollectionIterator<EnemyObject> * myEnemyIterator = mGameData.getEnemys().getEnemyIterator();
		EnemyObject* it;
		while (myEnemyIterator->hasNext())
		{
			it = myEnemyIterator->getNext();
			
			PhysicsComponent& currentPhysicsComponent = it->getPhysicsComponent();

			//get some random values
			float currentVelocity  = 350 + (rand()%400-200);
			float currentRotVelocity = 0.4 + (rand()%50-25)/10;

			//set speed of enemy
			currentPhysicsComponent.setVelocityValue(currentVelocity);
			//set its vector
			currentPhysicsComponent.setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
			//set it rotation speed
			currentPhysicsComponent.setRotVelocity(currentRotVelocity);			
		}
		delete myEnemyIterator;

	}


private:


};