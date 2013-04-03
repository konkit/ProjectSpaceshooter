#include "stdafx.h"
#include "Prefabs.h"


Prefab::Prefab(void)
{
}


Prefab::~Prefab(void)
{
}

void EnemyPrefab::resetFields()
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
	mColiders.clear();
}
