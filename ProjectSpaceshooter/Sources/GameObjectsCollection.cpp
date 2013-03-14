#include "stdafx.h"
#include "GameCollection.h"


GameObjectsCollectionIterator * GameCollection::getIterator()
{
	return new GameObjectsCollectionIterator(mListHead);
}

void GameCollection::addGameObject( GameObject * newObject )
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

void GameCollection::deleteGameObject( GameObject * deletedObject )
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

void GameCollection::operator-( GameObject * deletedObject )
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

void GameCollection::operator+( GameObject * newObject )
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

GameCollection::GameCollection( GameObjectType storedObjectType )
{
	mStoredObjectType = storedObjectType;
}

GameCollection::~GameCollection( void )
{
	GameObjectsListElement *tmp;
	while (mListHead != 0)
	{
		tmp = mListHead;
		mListHead = mListHead->next;
		delete tmp;
	}
}
