#pragma once


#pragma once
//HOW TO USE ITERATOR
//
//GameObjectsCollectionIterator<GameObject> * myIterator = myCollection.getIterator();
//std::cout << "Poczatek wyswietlania\n"; 
//while (myIterator->hasNext())
//{
//	std::cout<<myIterator->getNext()->name << std::endl;
//}


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

template<typename gObject>
class GameCollection;

/** 
  *
  * @author Zygi
  */
template <class gObject>
class GameCollectionIterator
{
public:
	GameCollectionIterator<gObject>() : pointerToActual(NULL), pointerToHead(NULL),  isFirstObject(true), pointerToNext(NULL), pointerToPrev(NULL){}
	GameCollectionIterator<gObject>(ListElement<gObject> * head)
		:	pointerToActual(head), pointerToHead(head),  isFirstObject(true), pointerToNext(NULL), pointerToPrev(NULL)
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
		{
			if(pointerToNext != NULL)
				return true;
			else 
				return false;
		}else if (isFirstObject)
			return true; 
		else
			return pointerToNext != NULL ? true : false;
	};
	gObject * getNext() 
	{
		if (isFirstObject)
		{
			isFirstObject = false;
		} else
		{
			pointerToPrev = pointerToActual;
			pointerToActual = pointerToNext;
			if (pointerToNext != NULL)
			{
				pointerToNext = pointerToNext->next;
			}
		}
		if (pointerToActual != NULL)
		{
			return pointerToActual->mObject;
		} else
			return NULL;
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
		pointerToPrev = NULL;
	}
	void removedActual()
	{
		pointerToActual = pointerToPrev;
	}
private:
	ListElement<gObject> * pointerToActual;
	ListElement<gObject> * pointerToNext;
	ListElement<gObject> * pointerToHead;
	ListElement<gObject> * pointerToPrev;
	bool isFirstObject;
	friend class GameCollection<gObject>;
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
			if (it == mListTail)
			{
				mListTail = prevIt;
			}
		} else
		{
			mListHead = it->next;
		}
		delete it; // Deleted struct have destructor to delate pointed object;
		return;
	};
	void deleteObject(GameCollectionIterator<gObject> & _it)
	{
		ListElement<gObject> * it = _it.pointerToActual;
		ListElement<gObject> * prevIt = _it.pointerToPrev;
		if(it == 0)
			return; // TODO throw an exception
		if (prevIt != 0)
		{
			prevIt->next = it->next;
			if (it == mListTail)
			{
				mListTail = prevIt;
			}
		} else
		{
			mListHead = it->next;
		}
		delete it; // Deleted struct have destructor to delate pointed object;
		_it.removedActual();
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
		deleteObject(deletedObject);
	}
	void operator-=(GameCollectionIterator<gObject> & it)
	{
		deleteObject(it);
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

	gObject * detachFirst()
	{
		ListElement<gObject> * it = mListHead;
		if(it == 0)
			throw My_Exception("Try to remove from empty gameCollection");
		mListHead = it->next;
		gObject * tmp;
		tmp = it->mObject;
		it->mObject = NULL;
		delete it;
		return tmp;
	}

	gObject * detachObject(GameCollectionIterator<gObject> & _it)
	{
		ListElement<gObject> * it = _it.pointerToActual;
		ListElement<gObject> * prevIt = _it.pointerToPrev;
		if(it == 0)
			throw My_Exception("Try to remove from empty gameCollection");
		if (prevIt != 0)
		{
			prevIt->next = it->next;
			if (it == mListTail)
			{
				mListTail = prevIt;
			}
		} else
		{
			mListHead = it->next;
		}
		_it.removedActual();
		gObject * tmp;
		tmp = it->mObject;
		it->mObject = NULL;
		delete it;
		return tmp;
	}
	gObject * detachObject(gObject * deletedObject)
	{
		ListElement<gObject> * it = mListHead;
		ListElement<gObject> * prevIt = 0;
		while (it->mObject != deletedObject && it!= 0)
		{
			prevIt = it;
			it = it->next;
		}
		if(it == 0)
			throw My_Exception("Try to remove from empty gameCollection");
		if (prevIt != 0)
		{
			prevIt->next = it->next;
			if (it == mListTail)
			{
				mListTail = prevIt;
			}
		} else
		{
			mListHead = it->next;
		}
	
		gObject * tmp;
		tmp = it->mObject;
		it->mObject = NULL;
		delete it;
		return tmp;
	};
	gObject * getFirst() {return mListHead->mObject;}
	GameCollectionIterator<gObject> getIterator()
	{
		return GameCollectionIterator<gObject>(mListHead);
	} 

	bool isEmpty()	{
		return ( mListHead == NULL ) ;
	}

private:
	ListElement<gObject> * mListHead;
	ListElement<gObject> * mListTail;

};






