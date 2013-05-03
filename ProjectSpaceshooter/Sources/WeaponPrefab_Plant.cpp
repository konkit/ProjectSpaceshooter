#include "WeaponPrefab_Plant.h"

WeaponPrefabPlant::WeaponPrefabPlant()
{
	mWeaponPrefab.resetPrefab();
	PrefabPlant::setPrefab(&mWeaponPrefab);
}


void WeaponPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

Prefab & WeaponPrefabPlant::getCreatedPrefab()
{
	return mWeaponPrefab;
}

const wstring WeaponPrefabPlant::getPrefabRootNode()
{
	return rootWeaponPrefabsNode;
}

const wstring WeaponPrefabPlant::getPrefabNodeName()
{
	return prefabName;
}

const wstring WeaponPrefabPlant::getPrefabName()
{
	return waepon_name;
}

void WeaponPrefabPlant::resetPrefab()
{
	mWeaponPrefab.resetPrefab();
	prefabReady = false;
}

void WeaponPrefabPlant::_setRateOfFire( const wstring & attribute, const wstring & value )
{
	if (attribute == WeaponPrefabPlant::value)
	{
		unsigned val = ValueToUINT(value);
		mWeaponPrefab.setRateOfFire(val);
	} else if (attribute == WeaponPrefabPlant::closeNode)
	{
	} else
	{
		throw My_Exception(L"WeaponPrefabPlant setRateOfFire: Undefined attribute - " + attribute);
	}
}

WeaponPrefabPlant::~WeaponPrefabPlant()
{

}

void WeaponPrefabPlant::_setBulletPrefabID( const wstring & attribute, const wstring & value )
{
	if (attribute == WeaponPrefabPlant::id)
	{
		unsigned id = ValueToUINT(value);
		mWeaponPrefab.setBulletPrefabID(id);
	}
}

bool WeaponPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	const wstring & name = elements.top();
	//Try to fill fields in 'PrefabPlant' part
	if (PrefabPlant::setAttribute(attribute,value))
	{
		return true;
	} else if (name == bullet_prefab)
	{
		_setBulletPrefabID(attribute, value);
	} else if(name == rateOfFire)
	{
		_setRateOfFire(attribute, value);
	} else
	{
		return false;
	}
}

bool WeaponPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return setAttribute(attribute, value);
}

const wstring WeaponPrefabPlant::prefabName(L"weapon");
const wstring WeaponPrefabPlant::rootWeaponPrefabsNode(L"weapon_prefabs");
const wstring WeaponPrefabPlant::bullet_prefab  = L"bullet_prefab";
const wstring WeaponPrefabPlant::rateOfFire     = L"rateOfFire";
const wstring WeaponPrefabPlant::waepon_name    = L"weapon_name";

