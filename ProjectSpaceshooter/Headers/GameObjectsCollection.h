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

template <class gObject>
class GameObjectsCollectionIterator
{
public:
	GameObjectsCollectionIterator<gObject>(ListElement<gObject> * head)
		:	pointerToActual(head), pointerToNext(head)
	{
	};
	~GameObjectsCollectionIterator<gObject>(){}

	bool hasNext()
	{
		if (pointerToActual == NULL)
			return false;
		else if (pointerToActual == pointerToNext)
			return true; 
		else
			return pointerToActual->next != 0 ? true : false;
	};
	gObject * getNext() 
	{
		pointerToActual = pointerToNext;
		if (pointerToActual == NULL)
		{
			return NULL;
		}
		if (pointerToActual->next != NULL) // Czy usun¹æ to zabezpieczenie i pozwoliæ na wejœcie aktualnego wskaŸnika na puste?
		{
			pointerToNext = pointerToActual->next;
		} else
			pointerToNext = NULL;
		return pointerToActual->mObject;  

	}
	gObject * getActual()
	{
		if(pointerToActual == NULL)
			return NULL;
		else
			return pointerToActual->mObject;
	}

private:
	ListElement<gObject> * pointerToActual;
	ListElement<gObject> * pointerToNext;
};

template<typename gObject>
class GameObjectsCollection
{
public:
	GameObjectsCollection<gObject>()
		:mListHead(0), mListTail(0)
	{
	}

	~GameObjectsCollection<gObject>()
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
	
	//Required deleted iterator after used
	GameObjectsCollectionIterator<gObject> * getIterator(){return new GameObjectsCollectionIterator<gObject>(mListHead);} 
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
private:
	ListElement<gObject> * mListHead;
	ListElement<gObject> * mListTail;
};