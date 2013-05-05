#include "stdafx.h"
#include "BulletPrefabPlant.h"

const wstring BulletPrefabPlant::rootBulletPrefabsNode(L"bullet_prefabs");
const wstring BulletPrefabPlant::prefabName(L"bullet");
const wchar_t * BulletPrefabPlant::bullet_name  = L"bullet_name" ;
const wchar_t * BulletPrefabPlant::auto_aim     = L"auto_aim";
const wchar_t * BulletPrefabPlant::bullet_power = L"bullet_power";
const wchar_t * BulletPrefabPlant::ttl = L"ttl";


BulletPrefabPlant::~BulletPrefabPlant()
{
	PrefabWithCollider_Plant::setPrefab(static_cast<PrefabWithCollider*>(&mBulletPrefab));
	PrefabWithMesh_Plant::setPrefab(static_cast<PrefabWithMesh*>(&mBulletPrefab));
}

void BulletPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

void BulletPrefabPlant::resetPrefab()
{
	mBulletPrefab.resetPrefab();
	prefabReady = false;
}

const wstring BulletPrefabPlant::getPrefabRootNode()
{
	return wstring(rootBulletPrefabsNode);
}

const wstring BulletPrefabPlant::getPrefabNodeName()
{
	return wstring(prefabName);
}

Prefab & BulletPrefabPlant::getCreatedPrefab()
{
	return static_cast<Prefab &>(mBulletPrefab);
}

void BulletPrefabPlant::_setAutoAim( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		if (value == PrefabPlant::yes)
		{
			mBulletPrefab.setAutoAim(true);
		} else
		{
			mBulletPrefab.setAutoAim(false);
		}

	}
}

void BulletPrefabPlant::_setBulletPower( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned val;
		val = ValueToUINT(value);
		mBulletPrefab.setBulletPower(val);
	};
}

const wstring BulletPrefabPlant::getPrefabName()
{
	return wstring(bullet_name);
}

BulletPrefabPlant::BulletPrefabPlant()
{
	PrefabWithCollider_Plant::setPrefab(&mBulletPrefab);
	PrefabWithMesh_Plant::setPrefab(&mBulletPrefab);
	MovablePrefab_Plant::setPrefab(&mBulletPrefab);
}

void BulletPrefabPlant::_setTTL( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		double val;
		val = ValueToDouble(value);
		mBulletPrefab.setTTL(val);
	};
}

bool BulletPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	const  wstring & stack_top = elements.top();

	if (PrefabPlant::setAttribute(attribute, value))
	{
		return true;
	} else if (MovablePrefab_Plant::setAttribute(attribute, value))
	{
		return true;
	} else if (PrefabWithMesh_Plant::setAttribute(attribute,value))
	{
		return true;
	} else if (PrefabWithCollider_Plant::setAttribute(attribute, value))
	{
		return true;
	} else if (stack_top == auto_aim)
	{
		_setAutoAim(attribute, value);
	} else if(stack_top == bullet_power) 
	{
		_setBulletPower(attribute, value);
	} else if(stack_top == ttl) 
	{
		_setTTL(attribute, value);
	}else
	{
		return false;
	}

}

bool BulletPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	throw std::exception("The method or operation is not implemented.");
}





