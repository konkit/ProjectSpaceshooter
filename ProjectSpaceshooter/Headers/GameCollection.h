#pragma once

//HOW TO USE ITERATOR
//
//GameObjectsCollectionIterator<GameObject> * myIterator = myCollection.getIterator();
//std::cout << "Poczatek wyswietlania\n"; 
//while (myIterator->hasNext())
//{
//	std::cout<<myIterator->getNext()->name << std::endl;
//}
//delete myIterator;

/** 
  *
  * @author Zygi
  */
template <class gObject>
struct ListElement
{
	gObject * mObject;
	ListElement * next;
	~ListElement()
	{
		delete mObject;
	}
};


/** 
  *
  * @author Zygi
  */
template <class gObject>
class GameCollectionIterator
{
public:
	GameCollectionIterator<gObject>(ListElement<gObject> * head)
		:	pointerToActual(head), pointerToHead(head),  isFirstObject(true)
	{
		if (pointerToActual != NULL)
		{
			pointerToNext = pointerToActual->next;
		}
	};
	~GameCollectionIterator<gObject>(){}

	bool hasNext()
	{
		if (pointerToActual == NULL)
			return false;
		else if (isFirstObject)
			return true; 
		else
			return pointerToNext != 0 ? true : false;
	};
	gObject * getNext() 
	{
		if (isFirstObject)
		{
			isFirstObject = false;
		} else
		{
			pointerToActual = pointerToNext;
			if (pointerToNext != NULL)
			{
				pointerToNext = pointerToNext->next;
			}
		}
		return pointerToActual->mObject;
	}
	gObject * getActual()
	{
		if(pointerToActual == NULL)
			return NULL;
		else
			return pointerToActual->mObject;
	}

	void resetIterator()
	{
		pointerToActual = pointerToNext = pointerToHead;
	}

private:
	ListElement<gObject> * pointerToActual;
	ListElement<gObject> * pointerToNext;
	ListElement<gObject> * pointerToHead;
	bool isFirstObject;
};


/** 
  *
  * @author Zygi
  */
template<typename gObject>
class GameCollection
{
public:
	GameCollection<gObject>()
		:mListHead(0), mListTail(0)
	{
	}

	~GameCollection<gObject>()
	{
		ListElement<gObject> * tmp = mListHead;
		while (tmp!=NULL)
		{
			mListHead = mListHead->next;
			delete tmp;
			tmp = mListHead;
		}
	}
	void deleteObject(gObject * deletedObject)
	{
		ListElement<gObject> * it = mListHead;
		ListElement<gObject> * prevIt = 0;
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
	};
	void addObject(gObject * newObject)
	{
		ListElement<gObject> * tmp = new ListElement<gObject>;
		tmp->mObject = newObject;
		tmp->next = NULL;
		if (mListHead==NULL)
		{
			mListHead = tmp;
		} else
		{
			mListTail->next = tmp;
		}
		mListTail = tmp;
		return;
	}
	void operator-=(gObject * deletedObject)
	{
		ListElement<gObject> * item = mListHead;
		ListElement<gObject> * prevIt = 0;
		while (item->mObject != deletedObject && item!= 0)
		{
			prevIt = item;
			item = item->next;
		}
		if(item == 0)
			return; // TODO throw an exception
		if (prevIt != 0)
		{
			prevIt->next = item->next;
		} else
		{
			mListHead = item->next;
		}
		delete item; // Deleted struct have destructor to delate pointed object;
		return;
	}
	void operator+=(gObject * newObject)
	{
		ListElement<gObject> * tmp = new ListElement<gObject>;
		tmp->mObject = newObject;
		tmp->next = NULL;
		if (mListHead==NULL)
		{
			mListHead = tmp;
		} else
		{
			mListTail->next = tmp;
		}
		mListTail = tmp;
		return;
	}
	void clearCollection()
	{
		ListElement<gObject> * tmp = mListHead;
		while (tmp!=NULL)
		{
			mListHead = mListHead->next;
			delete tmp;
			tmp = mListHead;
		}
		mListHead = mListTail = NULL;
	}

	gObject * getFirst() {return mListHead->mObject;}
	//Required delete iterator after used
	GameCollectionIterator<gObject> * getIterator()
	{
		return new GameCollectionIterator<gObject>(mListHead);
	} 
private:
	ListElement<gObject> * mListHead;
	ListElement<gObject> * mListTail;
};