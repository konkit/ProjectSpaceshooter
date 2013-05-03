#include "EnemyPrefabPlant.h"


const wstring EnemyPrefabPlant::rootEnemyPrefabsNode(L"ship_prefabs");
const wstring EnemyPrefabPlant::prefabName(L"ship");

const wchar_t * EnemyPrefabPlant::ship_name = L"ship_name";


EnemyPrefabPlant::EnemyPrefabPlant()
{
	PrefabPlant::setPrefab(static_cast<Prefab*>(&_enemyPrefab));
	PrefabWithCollider_Plant::setPrefab(static_cast<PrefabWithCollider*>(&_enemyPrefab));
	PrefabWithMesh_Plant::setPrefab(static_cast<PrefabWithMesh*>(&_enemyPrefab)); 
}

EnemyPrefabPlant::~EnemyPrefabPlant()
{

}

void EnemyPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

void EnemyPrefabPlant::resetPrefab()
{
	_enemyPrefab.resetPrefab();
	prefabReady = false;
}

const wstring EnemyPrefabPlant::getPrefabRootNode()
{
	return wstring(rootEnemyPrefabsNode);
}

const wstring EnemyPrefabPlant::getPrefabNodeName()
{
	return wstring(prefabName);
}


Prefab & EnemyPrefabPlant::getCreatedPrefab()
{
	return static_cast<Prefab &>(_enemyPrefab);
}

void EnemyPrefabPlant::_setWaeponPrefab( const wstring & attribute, const wstring & value )
{
	if (attribute == id)
	{
		unsigned int id;
		id = ValueToUINT(value);
		_enemyPrefab.setWeaponPrefabID(id);
	};
}


void EnemyPrefabPlant::_setMaxVelocity( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		double val;
		val = ValueToDouble(value);
		_enemyPrefab.setMaxVelocity(val);
	};
}

void EnemyPrefabPlant::_setMaxAcceleration( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		double val;
		val = ValueToDouble(value);
		_enemyPrefab.setMaxAcceleration(val);
	};
}

void EnemyPrefabPlant::_setMaxAngleVelocity( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		double val;
		val = ValueToDouble(value);
		_enemyPrefab.setMaxAngleVelocity(val);
	};
}

const wstring EnemyPrefabPlant::getPrefabName()
{
	return wstring(ship_name);
}

bool EnemyPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	const wstring & stack_top = elements.top();
	if (PrefabPlant::setAttribute(attribute, value))
	{
		return true;
	} else if (stack_top == PrefabPlant::max_velocity)
	{
		_setMaxVelocity(attribute, value);
	}
	else if (stack_top == PrefabPlant::max_acceleration)
	{
		_setMaxAcceleration(attribute, value);
	}
	else if (stack_top == PrefabPlant::max_angle_velocity)
	{
		_setMaxAngleVelocity(attribute, value);
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

bool EnemyPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return setAttribute(attribute, value);
}


