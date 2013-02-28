#pragma once
enum  class GameObjectType 
{
	player,
	enemyObject,
	bulletObject,
	staticObject,
	physicObject
};

class GameObject 
{
	GameObjectType mObjectType;
public:
	GameObject(GameObjectType newObjectType);
	virtual ~GameObject(void);
};

