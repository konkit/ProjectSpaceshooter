#pragma once

#include <stack>
#include <OgreEntity.h>


class EntityStack	{
public:


	void CreateMultipleEntities(int num, std::string name, Ogre::SceneManager& sceneMgr)	{
		Ogre::Entity* newEntity;
		
		for( int i=0; i<num; i++)	{
			uniqueId++;
			newEntity = sceneMgr.createEntity(std::to_string(uniqueId), name);
			mStack.push(newEntity);
		}
	}

	void pushEntity( Ogre::Entity* returnedEntity )	{
		mStack.push(returnedEntity);
	}

	Ogre::Entity* popOneEntity()	{
		std::cout<<"Popping one value from "<<mStack.size()<<"\n";

		Ogre::Entity* returnedValue = mStack.top();
		mStack.pop();
		return returnedValue;
	}

	static EntityStack& getSingleton()	{
		static EntityStack instance;
		return instance;
	}


private:
	EntityStack() : uniqueId(0)	{
	}


	std::stack<Ogre::Entity*> mStack;
	int uniqueId;
};