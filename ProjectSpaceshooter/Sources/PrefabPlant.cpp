#include "stdafx.h"
#include "PrefabPlant.h"
#include "EnemyPrefabPlant.h"
#include "Exceptions.h"
PrefabPlant::PrefabPlant(void)
	: prefabReady(true)
{
}


PrefabPlant::~PrefabPlant(void)
{
}

void PrefabPlant::nextElement( const wstring & name )
{
	elements.push(name);
}


void PrefabPlant::nextElement( const wstring & name, const wstring & prefix )
{

}

void PrefabPlant::closeElement( const wstring & name )
{
	if(elements.top() != name)
		throw My_Exception("Close XML Element: XML document don't meet standard");
	else
		elements.pop();

}

void PrefabPlant::closeElement( const wstring & prefix, const wstring & name )
{
	closeElement(name);
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

bool PrefabPlant::IsPrefabReady()
{
	return prefabReady;
}

unsigned int PrefabPlant::ValueToUINT(const wstring &value )
{ 
	wchar_t *pEnd;
	unsigned int id = static_cast<unsigned int> (wcstol(value.c_str(), &pEnd, 10));
	return id;
}

const wchar_t * PrefabPlant::max_acceleration = L"max_acceleration";
const wchar_t * PrefabPlant::max_velocity=L"max_velocity";
const wchar_t * PrefabPlant::max_angle_velocity = L"max_angle_velocity";
const wchar_t * PrefabPlant::health			 = L"health";
const wchar_t * PrefabPlant::scale			 = L"scale";
const wchar_t * PrefabPlant::rotation		 = L"rotation";
const wchar_t * PrefabPlant::coliders		 = L"coliders";
const wchar_t * PrefabPlant::standard_waepon = L"standard_waepon";
const wchar_t * PrefabPlant::name	= L"name";
const wchar_t * PrefabPlant::id		= L"id";
const wchar_t * PrefabPlant::value	= L"value";
const wchar_t * PrefabPlant::x_scale= L"x_scale";
const wchar_t * PrefabPlant::y_scale= L"y_scale";
const wchar_t * PrefabPlant::z_scale= L"z_scale";
const wchar_t * PrefabPlant::x_rot	= L"x_rot";
const wchar_t * PrefabPlant::y_rot	= L"y_rot";
const wchar_t * PrefabPlant::z_rot	= L"z_rot";
const wchar_t * PrefabPlant::x_pos	= L"x_pos";
const wchar_t * PrefabPlant::y_pos	= L"y_pos";
const wchar_t * PrefabPlant::z_pos	= L"z_pos";
const wchar_t * PrefabPlant::close	= L"close";

const wchar_t * PrefabPlant::mesh	= L"mesh";
const wchar_t * PrefabPlant::colider= L"colider";
const wchar_t * PrefabPlant::offset = L"offset";
const wchar_t * PrefabPlant::radian = L"radian";
