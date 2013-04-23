#include "stdafx.h"
#include "BulletPrefabPlant.h"

const wstring BulletPrefabPlant::rootBulletPrefabsNode(L"bullet_prefabs");
const wstring BulletPrefabPlant::prefabName(L"bullet");
const wchar_t * BulletPrefabPlant::bullet_name  = L"bullet_name" ;
const wchar_t * BulletPrefabPlant::auto_aim     = L"auto_aim";
const wchar_t * BulletPrefabPlant::bullet_power = L"bullet_power";

BulletPrefabPlant::~BulletPrefabPlant()
{
	PrefabWithCollider_Plant::setPrefab(static_cast<PrefabWithCollider*>(&mBulletPrefab));
	PrefabWithMesh_Plant::setPrefab(static_cast<PrefabWithMesh*>(&mBulletPrefab));
}

void BulletPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

void BulletPrefabPlant::setMethodToFillProperty( const wstring & name )
{
	if (SetMethodToFillBasicProperty(name))
	{
		methodToFillBulletProperty = methodToFillBasicProperty;
	} else if (name == PrefabPlant::max_velocity)
	{
		methodToFillBulletProperty = &BulletPrefabPlant::_setMaxVelocity;
	} else if (SetMethodToFillMeshProperty(name))
	{
		methodToFillBulletProperty = methodToFillMeshProperty;
	} else if (SetMethodToFillColliderProperty(name))
	{
		methodToFillBulletProperty = methodToFillColliderProperty;
	} else if (name == auto_aim)
	{
		methodToFillBulletProperty = &BulletPrefabPlant::_setAutoAim;
	} else if(name == bullet_power) 
	{
		 methodToFillBulletProperty = &BulletPrefabPlant::_setBulletPower;
	} else
	{
		methodToFillBulletProperty = &BulletPrefabPlant::_doNothing;
	}

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

void BulletPrefabPlant::fillPrefabProperty( const wstring & attribute, const wstring & value )
{
	(this->*methodToFillBulletProperty)(attribute,value);
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

void BulletPrefabPlant::_setMaxVelocity( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		double val;
		val = ValueToDouble(value);
		mBulletPrefab.setMaxVelocity(val);
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
}




