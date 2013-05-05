#pragma once
#include "PrefabPlant.h"

class BulletPrefabPlant : virtual public PrefabWithCollider_Plant, virtual public PrefabWithMesh_Plant, virtual public MovablePrefab_Plant
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
	virtual bool setAttribute( const wstring & attribute, const wstring & value );
	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );
private:
	void _setShipName(const wstring & attribute, const wstring & value);
	void _setAutoAim(const wstring & attribute, const wstring & value);
	void _setBulletPower(const wstring & attribute, const wstring & value);
	void _setTTL(const wstring & attribute, const wstring & value);


	static const wstring rootBulletPrefabsNode;
	static const wstring prefabName;
	BulletPrefab mBulletPrefab;

	static const wchar_t * bullet_name;
	static const wchar_t * auto_aim;
	static const wchar_t * bullet_power;
	static const wchar_t * ttl;

};
