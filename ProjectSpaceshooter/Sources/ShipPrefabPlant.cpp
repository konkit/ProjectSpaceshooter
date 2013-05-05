#include "ShipPrefabPlant.h"


const wstring ShipPrefabPlant::rootEnemyPrefabsNode(L"ship_prefabs");
const wstring ShipPrefabPlant::prefabName(L"ship");

const wchar_t * ShipPrefabPlant::ship_name = L"ship_name";


ShipPrefabPlant::ShipPrefabPlant()
{
	PrefabPlant::setPrefab(static_cast<Prefab*>(&_enemyPrefab));
	PrefabWithCollider_Plant::setPrefab(static_cast<PrefabWithCollider*>(&_enemyPrefab));
	PrefabWithMesh_Plant::setPrefab(static_cast<PrefabWithMesh*>(&_enemyPrefab)); 
	MovablePrefab_Plant::setPrefab(static_cast<MovablePrefab*>(&_enemyPrefab));
}

ShipPrefabPlant::~ShipPrefabPlant()
{

}

void ShipPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

void ShipPrefabPlant::resetPrefab()
{
	_enemyPrefab.resetPrefab();
	prefabReady = false;
}

const wstring ShipPrefabPlant::getPrefabRootNode()
{
	return wstring(rootEnemyPrefabsNode);
}

const wstring ShipPrefabPlant::getPrefabNodeName()
{
	return wstring(prefabName);
}


Prefab & ShipPrefabPlant::getCreatedPrefab()
{
	return static_cast<Prefab &>(_enemyPrefab);
}

void ShipPrefabPlant::_setWaeponPrefab( const wstring & attribute, const wstring & value )
{
	if (attribute == id)
	{
		unsigned int id;
		id = ValueToUINT(value);
		_enemyPrefab.setWeaponPrefabID(id);
	};
}




const wstring ShipPrefabPlant::getPrefabName()
{
	return wstring(ship_name);
}

bool ShipPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	const wstring & stack_top = elements.top();
	if (PrefabPlant::setAttribute(attribute, value))
	{
		return true;
	} else if(MovablePrefab_Plant::setAttribute(attribute, value))
	{
		return true;
	} else if (PrefabWithMesh_Plant::setAttribute(attribute, value))
	{
		return true;
	} else if (PrefabWithCollider_Plant::setAttribute(attribute, value))
	{
		return true;
	}
	else if (stack_top == PrefabPlant::standard_waepon)
	{
		_setWaeponPrefab(attribute, value);
	}	
	else
	{
		return false;
	}

}

bool ShipPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return setAttribute(attribute, value);
}


