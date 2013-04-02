#include "EnemyPrefabPlant.h"

const wstring EnemyPrefabPlant::rootEnemyPrefabsNode(L"ship_prefabs");
const wstring EnemyPrefabPlant::prefabName(L"ship");

EnemyPrefabPlant::EnemyPrefabPlant()
{

}

EnemyPrefabPlant::~EnemyPrefabPlant()
{

}

void EnemyPrefabPlant::setAttribute( wstring attribute, wstring value )
{

}

void EnemyPrefabPlant::setAttribute( wstring prefix, wstring attribute, wstring value )
{
	throw std::exception("The method or operation is not implemented.");
}


Prefab * EnemyPrefabPlant::getCreatedPrefab()
{
	EnemyPrefab _prefab;
	return &_prefab;
}

void EnemyPrefabPlant::setText( wstring text )
{
	throw std::exception("The method or operation is not implemented.");
}

void EnemyPrefabPlant::resetPrefab()
{
	
}

const wstring & EnemyPrefabPlant::getPrefabRootNode()
{
	return rootEnemyPrefabsNode;
}

const wstring & EnemyPrefabPlant::getPrefabName()
{
	return prefabName;
}


