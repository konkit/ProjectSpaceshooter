#include "stdafx.h"
#include "GameObjectFactory.h"

GameObject * GameObjectFactory::getGameObject( GameObjectType newObjectType )
{
	GameObject * newGameObject = new GameObject(newObjectType);
	return newGameObject;
}
