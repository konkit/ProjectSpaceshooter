#include "stdafx.h"
#include "Prefabs.h"


Prefab::Prefab(void)
{
}


Prefab::~Prefab(void)
{
}

void EnemyPrefab::resetPrefab()
{
	mResistance       = 0;
	mEnemyPrefabID    = 0;
	mMeshName         = "";
	mMaxVelocity      = 0;
	mMaxAcceleration  = 0;
	mMaxAngleVelocity = 0;
	mMaxHealth        = 0;
	mScale.x_scale    = 0;
	mScale.y_scale    = 0;
	mScale.z_scale    = 0;
	mRotation.x_rot   = 0;
	mRotation.y_rot   = 0;
	mRotation.z_rot   = 0;
	mMyAI             = AI_TYPE::defender;
	mWeaponPrefabID   = 0;
	clearColiders();
}

EnemyPrefab::EnemyPrefab( unsigned prefabID )
	: Prefab()
{

}

void BulletPrefab::resetPrefab()
{
	throw std::exception("The method or operation is not implemented.");
}

BulletPrefab::BulletPrefab()
{
	resetPrefab();
}

void EffectPrefab::resetPrefab()
{
	throw std::exception("The method or operation is not implemented.");
}

EffectPrefab::EffectPrefab()
{
	resetPrefab();
}

void StaticPrefab::resetPrefab()
{
	throw std::exception("The method or operation is not implemented.");
}

void PrefabWithColider::resetPrefab()
{
	throw std::exception("The method or operation is not implemented.");
}

void PrefabWithMesh::resetPrefab()
{
	throw std::exception("The method or operation is not implemented.");
}
