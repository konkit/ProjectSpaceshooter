#include "EnemyPrefabPlant.h"


const wstring EnemyPrefabPlant::rootEnemyPrefabsNode(L"ship_prefabs");
const wstring EnemyPrefabPlant::prefabName(L"ship");

const wchar_t * EnemyPrefabPlant::ship_name = L"ship_name";


EnemyPrefabPlant::EnemyPrefabPlant()
{
	PrefabPlant::setPrefab(static_cast<Prefab*>(&_enemyPrefab));
	PrefabWithColider_Plant::setPrefab(static_cast<PrefabWithColider*>(&_enemyPrefab));
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

void EnemyPrefabPlant::setMethodToFillProperty( const wstring & name )
{
	if (SetMethodToFillBasicProperty(name))
	{
		methodToFillEnemyProperty = methodToFillBasicProperty;
	} else if (name == PrefabPlant::max_velocity)
	{
		methodToFillEnemyProperty = &EnemyPrefabPlant::_setMaxVelocity;
	}
	else if (name == PrefabPlant::max_acceleration)
	{
		methodToFillEnemyProperty = &EnemyPrefabPlant::_setMaxAcceleration;
	}
	else if (name == PrefabPlant::max_angle_velocity)
	{
		methodToFillEnemyProperty = &EnemyPrefabPlant::_setMaxAngleVellocity;
	} else if (SetMethodToFillMeshProperty(name))
	{
		methodToFillEnemyProperty = methodToFillMeshProperty;
	} else if (SetMethodToFillColiderProperty(name))
	{
		methodToFillEnemyProperty = methodToFillColiderProperty;
	}
	else if (name == PrefabPlant::standard_waepon)
	{
		methodToFillEnemyProperty = &EnemyPrefabPlant::_setWaeponPrefab;
	}	
	else
	{
		methodToFillEnemyProperty = &EnemyPrefabPlant::_doNothing;
	}

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

void EnemyPrefabPlant::_setMaxAngleVellocity( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		double val;
		val = ValueToDouble(value);
		_enemyPrefab.setMaxAngleVelocity(val);
	};
}


void EnemyPrefabPlant::fillPrefabProperty(const wstring & attribute, const wstring & value )
{
	(this->*methodToFillEnemyProperty)(attribute, value);
}

const wstring EnemyPrefabPlant::getPrefabName()
{
	return wstring(ship_name);
}


