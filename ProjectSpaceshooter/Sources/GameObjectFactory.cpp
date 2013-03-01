#include "stdafx.h"
#include "GameObjectFactory.h"

GameObject * GameObjectFactory::createGameObject( GameObjectType newObjectType )
{
	GameObject * newGameObject = new GameObject(newObjectType);
	return newGameObject;
}
