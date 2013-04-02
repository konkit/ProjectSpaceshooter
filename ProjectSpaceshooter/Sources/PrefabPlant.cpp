#include "stdafx.h"
#include "PrefabPlant.h"
#include "EnemyPrefabPlant.h"
#include "Exceptions.h"
PrefabPlant::PrefabPlant(void)
{
}


PrefabPlant::~PrefabPlant(void)
{
}

void PrefabPlant::nextElement( wstring name )
{
	elements.push(name);
}


void PrefabPlant::nextElement( wstring name, wstring prefix )
{

}

void PrefabPlant::closeElement( wstring name )
{
	if(elements.top() != name)
		throw My_Exception("Close XML Element: XML document don't meet standard");
	else
		elements.pop();

}

PrefabPlant * PrefabPlant::CreatePrefabPlantFor( PREFAB_TYPE prefabType )
{
	switch (prefabType)
	{
	case PREFAB_TYPE::EnemyPrefab:
		return new EnemyPrefabPlant;
	case PREFAB_TYPE::BulletPrefab:
		break;
	case PREFAB_TYPE::StaticPrefab:
		break;
	case PREFAB_TYPE::EffectPrefab:
		break;
	default:
		break;
	}
	return NULL;
}

void PrefabPlant::DeletePrefabPlant( PrefabPlant * _prefabPlant )
{
	delete _prefabPlant;
}
