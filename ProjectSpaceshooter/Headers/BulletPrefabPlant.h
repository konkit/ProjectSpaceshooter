#pragma once
#include "PrefabPlant.h"

class BulletPrefabPlant : virtual public PrefabWithCollider_Plant, virtual public PrefabWithMesh_Plant
{
public:
	BulletPrefabPlant();;
	~BulletPrefabPlant();;
	void setText(const wstring & text );
	Prefab & getCreatedPrefab();
	void virtual resetPrefab();
	virtual const wstring getPrefabRootNode();
	virtual const wstring getPrefabNodeName();
	virtual const wstring getPrefabName();
	void setMethodToFillProperty( const wstring & name );

private:
	void fillPrefabProperty(const wstring & attribute, const wstring & value );
	void _setMaxVelocity(const wstring & attribute, const wstring & value);
	void _setShipName(const wstring & attribute, const wstring & value);
	void _setAutoAim(const wstring & attribute, const wstring & value);
	void _setBulletPower(const wstring & attribute, const wstring & value);
	void _setTTL(const wstring & attribute, const wstring & value);

	//--------------------------------------------------------------------------------------


	void (BulletPrefabPlant:: *methodToFillBulletProperty)(const wstring & attribute, const wstring & value);


	static const wstring rootBulletPrefabsNode;
	static const wstring prefabName;
	BulletPrefab mBulletPrefab;

	static const wchar_t * bullet_name;
	static const wchar_t * auto_aim;
	static const wchar_t * bullet_power;
	static const wchar_t * ttl;

};
