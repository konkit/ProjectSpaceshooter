#include "stdafx.h"
#include "Prefabs.h"


Prefab::Prefab(void)
{
}


Prefab::~Prefab(void)
{
}

void Prefab::resetPrefab()
{
	mPrefabID = 0;
	mName.clear();
}


void ShipPrefab::resetPrefab()
{
	PrefabWithColider::resetPrefab();
	PrefabWithMesh::resetPrefab();
	MovablePrefab::resetPrefab();
	mWeaponPrefabID = 0;
}

ShipPrefab::ShipPrefab( unsigned prefabID )
	: PrefabWithMesh()
{
	mPrefabID = prefabID;
}
ShipPrefab::~ShipPrefab(void)
{
}

BulletPrefab::BulletPrefab( unsigned prefabID )
{
	mPrefabID = prefabID;
	mAutoAim = false;
	MovablePrefab::resetPrefab();
}

BulletPrefab::BulletPrefab()
{
	resetPrefab();
}

void BulletPrefab::resetPrefab()
{
	mAutoAim = false;
	mBulletPower = 0.0;
	PrefabWithColider::resetPrefab();
	PrefabWithMesh::resetPrefab();
	MovablePrefab::resetPrefab();
}

EffectPrefab::EffectPrefab()
{
	resetPrefab();
}

void EffectPrefab::resetPrefab()
{
	mParticleSystemName.clear();
	Prefab::resetPrefab();
}

void StaticPrefab::resetPrefab()
{
	PrefabWithColider::resetPrefab();
	PrefabWithMesh::resetPrefab();
}

void PrefabWithColider::resetPrefab()
{
	
	clearColiders();
	mResistance = 0;
	mMaxHealth = 0;
	Prefab::resetPrefab();
}


void PrefabWithMesh::resetPrefab()
{
	mMeshName.clear();
	mRotation.resetScale();
	mScale = Vector3(0.0, 0.0, 0.0);
	Prefab::resetPrefab();
}

void WeaponPrefab::resetPrefab()
{
	Prefab::resetPrefab();
	rateOfFire = 0;
	bulletPrefabID = 0;
}

WeaponPrefab::~WeaponPrefab()
{
}

WeaponPrefab::WeaponPrefab()
{
	resetPrefab();
}

void MovablePrefab::resetPrefab()
{
	mMaxVelocity      = 0;
	mMaxAcceleration  = 0;
	mMaxAngleVelocity = 0;
}
