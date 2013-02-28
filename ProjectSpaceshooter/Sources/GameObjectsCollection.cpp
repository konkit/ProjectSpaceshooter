#include "stdafx.h"
#include "GameObjectsCollection.h"


GameObjectsCollectionIterator * GameObjectsCollection::getIterator()
{
	return new GameObjectsCollectionIterator(mListHead);
}

void GameObjectsCollection::addGameObject( GameObject * newObject )
{
	GameObjectsListElement * tmp = new GameObjectsListElement;
	if (mListHead)
	{
		mListHead = tmp;
	
	} else
	{
		mListTail->next = tmp;
	}
	mListTail = tmp;
	return;
}

void GameObjectsCollection::deleteGameObject( GameObject * deletedObject )
{
	GameObjectsListElement * it = mListHead;
	GameObjectsListElement * prevIt = 0;
	while (it->mObject != deletedObject && it!= 0)
	{
		prevIt = it;
		it = it->next;
	}
	if(it == 0)
		return; // TODO throw an exception
	if (prevIt != 0)
	{
		prevIt->next = it->next;
	} else
	{
		mListHead = it->next;
	}
		delete it; // Deleted struct have destructor to delate pointed object;
	return;
}

void GameObjectsCollection::operator-( GameObject * deletedObject )
{
	GameObjectsListElement * it = mListHead;
	GameObjectsListElement * prevIt = 0;
	while (it->mObject != deletedObject && it!= 0)
	{
		prevIt = it;
		it = it->next;
	}
	if(it == 0)
		return; // TODO throw an exception
	if (prevIt != 0)
	{
		prevIt->next = it->next;
	} else
	{
		mListHead = it->next;
	}
	delete it; // Deleted struct have destructor to delate pointed object;
	return;
}

void GameObjectsCollection::operator+( GameObject * newObject )
{
	GameObjectsListElement * tmp = new GameObjectsListElement;
	if (mListHead)
	{
		mListHead = tmp;

	} else
	{
		mListTail->next = tmp;
		}
		mListTail = tmp;
		return;
}

GameObjectsCollection::GameObjectsCollection( GameObjectType storedObjectType )
{
	mStoredObjectType = storedObjectType;
}

GameObjectsCollection::~GameObjectsCollection( void )
{
	GameObjectsListElement *tmp;
	while (mListHead != 0)
	{
		tmp = mListHead;
		mListHead = mListHead->next;
		delete tmp;
	}
}
