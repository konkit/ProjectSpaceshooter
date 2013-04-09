#pragma once
#include "PrefabPlant.h"

class EnemyPrefabPlant : public PrefabPlant 
{
public:
	EnemyPrefabPlant();
	~EnemyPrefabPlant();

	void setAttribute(const wstring & attribute, const wstring & value );
	void setAttribute(const wstring &, const wstring & attribute, const wstring & value );

	void setText(const wstring & text );
	Prefab * getCreatedPrefab();

	void virtual resetPrefab();
	virtual const wstring & getPrefabRootNode();
	virtual const wstring & getPrefabName();
	virtual void nextElement( const wstring & name );

	virtual void nextElement( const wstring & prefix, const wstring & name );

	void setMethodToFillProperty( const wstring & name );

	virtual void closeElement( const wstring & name );

	virtual void closeElement( const wstring & prefix, const wstring & name );

private:

	void _setPrefabID(const wstring & attribute, const wstring & value);
	void _setWaeponPrefab(const wstring & attribute, const wstring & value);
	void _setMeshName(const wstring & attribute, const wstring & value);
	void _setMaxVelocity(const wstring & attribute, const wstring & value);
	void _setMaxAcceleration(const wstring & attribute, const wstring & value);
	void _setMaxAngleVellocity(const wstring & attribute, const wstring & value);
	void _setMaxHealth(const wstring & attribute, const wstring & value);
	void _setScale(const wstring & attribute, const wstring & value);
	void _setRotation(const wstring & attribute, const wstring & value);
	void _setColider(const wstring & attribute, const wstring & value);
	void _setShipName(const wstring & attribute, const wstring & value);
	void _setColiderRadian(const wstring & attribute, const wstring & value);
	void _setColiderOffset(const wstring & attribute, const wstring & value);
	void _doNothing(const wstring & attribute, const wstring & value);
	//--------------------------------------------------------------------------------------
	void clearColider();

	void (EnemyPrefabPlant:: *methodToFillProperty)(const wstring & attribute, const wstring & value);
	static const wstring rootEnemyPrefabsNode;
	static const wstring prefabName;
	EnemyPrefab _enemyPrefab;
	colider_struct colider;

	static const wchar_t * ship;
	static const wchar_t * ship_name;

};