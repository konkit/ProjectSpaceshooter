#pragma once
#include "PrefabPlant.h"

class EnemyPrefabPlant : public PrefabPlant 
{
public:
	EnemyPrefabPlant();
	~EnemyPrefabPlant();

	void setAttribute( wstring attribute, wstring value );
	void setAttribute( wstring prefix, wstring attribute, wstring value );

	void setText( wstring text );
	Prefab * getCreatedPrefab();

	void virtual resetPrefab();

	virtual const wstring & getPrefabRootNode();

	virtual const wstring & getPrefabName();

private:
	static const wstring rootEnemyPrefabsNode;
	static const wstring prefabName;
	EnemyPrefab _enemyPrefab;
};