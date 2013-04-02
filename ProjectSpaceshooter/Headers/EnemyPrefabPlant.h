#pragma once
#include "PrefabPlant.h"

class EnemyPrefabPlant : public PrefabPlant 
{
public:
	EnemyPrefabPlant();
	~EnemyPrefabPlant();
	void setAttribute( wstring attribute, wstring value );
	void virtual setText( wstring text );
	Prefab getCreatedPrefab();
private:
	EnemyPrefab _enemyPrefab;
};