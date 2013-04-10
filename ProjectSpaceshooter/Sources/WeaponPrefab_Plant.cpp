#include "WeaponPrefab_Plant.h"

WeaponPrefabPlant::WeaponPrefabPlant()
{
	mWeaponPrefab.resetPrefab();
	methodToFillWeaponProperty = &WeaponPrefabPlant::_doNothing;
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
	methodToFillWeaponProperty = &WeaponPrefabPlant::_doNothing;
}

void WeaponPrefabPlant::setMethodToFillProperty( const wstring & name )
{
	if (SetMethodToFillBasicProperty(name))
	{
		methodToFillWeaponProperty = methodToFillBasicProperty;
	} else if (name == bullet_prefab)
	{
		methodToFillWeaponProperty = &WeaponPrefabPlant::_setBulletPrefabID;
	} else if(name == rateOfFire)
	{
		methodToFillWeaponProperty = &WeaponPrefabPlant::_setRateOfFire;
	} else
	{
		methodToFillWeaponProperty = &WeaponPrefabPlant::_doNothing;
	}
}

void WeaponPrefabPlant::fillPrefabProperty( const wstring & attribute, const wstring & value )
{
	(this->*methodToFillWeaponProperty)(attribute, value);
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

const wstring WeaponPrefabPlant::prefabName(L"weapon");
const wstring WeaponPrefabPlant::rootWeaponPrefabsNode(L"weapon_prefabs");
const wstring WeaponPrefabPlant::bullet_prefab  = L"bullet_prefab";
const wstring WeaponPrefabPlant::rateOfFire     = L"rateOfFire";
const wstring WeaponPrefabPlant::waepon_name    = L"weapon_name";

