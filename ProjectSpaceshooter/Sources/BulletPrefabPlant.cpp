#include "stdafx.h"
#include "BulletPrefabPlant.h"

const wstring BulletPrefabPlant::rootBulletPrefabsNode(L"bullet_prefabs");
const wstring BulletPrefabPlant::prefabName(L"bullet");

BulletPrefabPlant::~BulletPrefabPlant()
{
	PrefabWithColider_Plant::setPrefab(static_cast<PrefabWithColider*>(&_bulletPrefab));
	PrefabWithMesh_Plant::setPrefab(static_cast<PrefabWithMesh*>(&_bulletPrefab));
}

void BulletPrefabPlant::setText( const wstring & text )
{

}

void BulletPrefabPlant::setMethodToFillProperty( const wstring & name )
{

}
