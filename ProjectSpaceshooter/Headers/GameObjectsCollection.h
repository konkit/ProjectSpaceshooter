#pragma once
#include "GameObject.h"
//Struct have destructor to delete pointed object;
struct GameObjectsListElement
	{
		GameObject * mObject;
		GameObjectsListElement * next;
		~GameObjectsListElement()
			{delete mObject;}
	};


class GameObjectsCollectionIterator
{
	GameObjectsListElement * pointer;
public:
	GameObjectsCollectionIterator(GameObjectsListElement * head)
		: pointer(head){};
	~GameObjectsCollectionIterator();
	bool hasNext()
	{
		return pointer->next != 0 ? true : false;
	};
	GameObject * getNext() 
	{
		if (pointer->next != 0)
		{
			pointer = pointer->next;
			return pointer->mObject;
		} else
		{
			return 0; //TODO change to exception?
		}
	};
};

class GameObjectsCollection
{
	friend class GameObjectsCollectionIterator;
private:
	GameObjectsListElement * mListHead;
	GameObjectsListElement * mListTail;
	GameObjectType mStoredObjectType;
public:
	GameObjectsCollection(GameObjectType storedObjectType);
	~GameObjectsCollection(void);

	GameObjectsCollectionIterator * getIterator();
	void deleteGameObject(GameObject * deletedObject);
	void addGameObject(GameObject * newObject);
	void operator-(GameObject * delegateObject);
	void operator+(GameObject * newObject);  
	GameObjectType storedObjectType() const { return mStoredObjectType; }
};

