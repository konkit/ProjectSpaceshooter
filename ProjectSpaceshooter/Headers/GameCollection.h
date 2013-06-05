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
  * @author Zyga
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
  * Game iterator, used to move forward the game collection.
  * It offer two main method hasNext checking if there are next object in collection,
  * and getNext which move to next object, and return it.
  * Iterator also stores the pointer to previous list element so it can be used to remove
  * object from collection without looking for object.
  * You can use iterator like STL iterator e.g.
  *		for(it = col.getIterator(); it.hasNext(); it++) { fun(*it); it->doSth;}
  * or in old way
  *		while(it.hasNext()) {obj = it.getNext();)
  * @author Zyga
  */
template <class gObject>
class GameCollectionIterator
{
public:
	/**
	 * Constructor which create empty iterator. 
	 * @author Zyga
	 */	
	GameCollectionIterator<gObject>() : pointerToActual(NULL), pointerToHead(NULL),  isFirstObject(true), pointerToNext(NULL), pointerToPrev(NULL){}
	/**
	 * Constructor which which point to first object in collection. 
	 * @author Zyga
	 */		
	GameCollectionIterator<gObject>(ListElement<gObject> * head)
		:	pointerToActual(head), pointerToHead(head),  isFirstObject(true), pointerToNext(NULL), pointerToPrev(NULL)
	{
		if (pointerToActual != NULL)
		{
			pointerToNext = pointerToActual->next;
		}
	};

	~GameCollectionIterator<gObject>(){}

	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
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
	
	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
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
	
	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
	gObject * getActual()
	{
		if(pointerToActual == NULL)
			return NULL;
		else
			return pointerToActual->mObject;
	}

	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
	void resetIterator()
	{
		pointerToActual = pointerToNext = pointerToHead;
		pointerToPrev = NULL;
	}

	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
	void removedActual()
	{
		pointerToActual = pointerToPrev;
	}
	gObject & operator * ()
	{
		if(pointerToActual != NULL)

			return *(pointerToActual->mObject);
		else
			throw(std::exception("There isn't actual pointed object"));
	}
	gObject * operator -> ()
	{
		if(pointerToActual != NULL)

			return pointerToActual->mObject;
		else
			return false;
	}
	void operator ++(int)
	{
		pointerToPrev = pointerToActual;
		pointerToActual = pointerToNext;
		if (pointerToNext != NULL)
		{
			pointerToNext = pointerToNext->next;
		}		
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
		:mListHead(NULL), mListTail(NULL)
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
	/**
	 * 
	 *
	 * @return 
	 * @param deletedObject 
	 * @author Zyga
	 */
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
	/**
	 * 
	 *
	 * @return 
	 * @param _it 
	 * @author Zyga
	 */
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
	/**
	 * 
	 *
	 * @return 
	 * @param newObject 
	 * @author Zyga
	 */
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
	/**
	 * 
	 *
	 * @return 
	 * @param deletedObject 
	 * @author Zyga
	 */
	void operator-=(gObject * deletedObject)
	{
		deleteObject(deletedObject);
	}
	/**
	 * 
	 *
	 * @return 
	 * @param it 
	 * @author Zyga
	 */
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
	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
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

	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
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

	/**
	 * 
	 *
	 * @return 
	 * @param _it 
	 * @author Zyga
	 */
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
	/**
	 * 
	 *
	 * @return 
	 * @param deletedObject 
	 * @author Zyga
	 */
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
	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
	gObject * getFirst() {return mListHead->mObject;}
	/**
	 * 
	 *
	 * @return 
	 * @author Zyga
	 */
	GameCollectionIterator<gObject> getIterator()
	{
		return GameCollectionIterator<gObject>(mListHead);
	} 

	/**
	 * 
	 *
	 * @return 
	 * @author konkit
	 */
	bool isEmpty()	{
		return mListHead == NULL;
	}

private:
	ListElement<gObject> * mListHead;
	ListElement<gObject> * mListTail;

};






