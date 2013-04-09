#pragma once
#include "PrefabPlant.h"

class EnemyPrefabPlant : virtual public PrefabWithColider_Plant, virtual public PrefabWithMesh_Plant
{
public:
	EnemyPrefabPlant();
	~EnemyPrefabPlant();

	void setText(const wstring & text );
	Prefab & getCreatedPrefab();
	void virtual resetPrefab();
	virtual const wstring getPrefabRootNode();
	virtual const wstring getPrefabNodeName();
	virtual const wstring getPrefabName();
	void setMethodToFillProperty( const wstring & name );

private:
	void fillPrefabProperty(const wstring & attribute, const wstring & value );
	void _setWaeponPrefab(const wstring & attribute, const wstring & value);
	void _setMaxAcceleration(const wstring & attribute, const wstring & value);
	void _setMaxAngleVellocity(const wstring & attribute, const wstring & value);
	
	void _setMaxVelocity(const wstring & attribute, const wstring & value);
	
	
	//--------------------------------------------------------------------------------------


	void (EnemyPrefabPlant:: *methodToFillEnemyProperty)(const wstring & attribute, const wstring & value);


	static const wstring rootEnemyPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * ship_name;

	ShipPrefab _enemyPrefab;
	
};