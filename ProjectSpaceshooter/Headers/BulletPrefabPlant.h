#pragma once
#include "PrefabPlant.h"

class BulletPrefabPlant : public PrefabWithColider_Plant, public PrefabWithMesh_Plant
{
public:
	BulletPrefabPlant(){};
	~BulletPrefabPlant();;
	void setText(const wstring & text );
	Prefab * getCreatedPrefab();
	void virtual resetPrefab();
	virtual const wstring & getPrefabRootNode();
	virtual const wstring & getPrefabName();
	void setMethodToFillProperty( const wstring & name );

private:
	void fillPrefabProperty(const wstring & attribute, const wstring & value );
	void _setPrefabID(const wstring & attribute, const wstring & value);
	void _setWaeponPrefab(const wstring & attribute, const wstring & value);
	void _setMaxVelocity(const wstring & attribute, const wstring & value);
	void _setMaxAcceleration(const wstring & attribute, const wstring & value);
	void _setMaxAngleVellocity(const wstring & attribute, const wstring & value);
	void _setMaxHealth(const wstring & attribute, const wstring & value);
	void _setShipName(const wstring & attribute, const wstring & value);

	//--------------------------------------------------------------------------------------


	void (BulletPrefabPlant:: *methodToFillProperty)(const wstring & attribute, const wstring & value);
	static const wstring rootBulletPrefabsNode;
	static const wstring prefabName;
	BulletPrefab _bulletPrefab;

	static const wchar_t * ship;
	static const wchar_t * ship_name;

};
