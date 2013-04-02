#pragma once
#include "Prefabs.h"
#include <string>
#include <stack>

using namespace std;
class PrefabPlant
{
public:
	PrefabPlant(void);
	~PrefabPlant(void);
	static PrefabPlant * CreatePrefabPlantFor(PREFAB_TYPE prefabType);
	static void DeletePrefabPlant(PrefabPlant * _prefabPlant);
	void nextElement(wstring name);
	void nextElement(wstring name, wstring prefix);
	void closeElement(wstring name);
	void virtual setAttribute(wstring attribute, wstring value) = 0;
	void virtual setText(wstring text) = 0;
	Prefab virtual getCreatedPrefab() = 0;
private:
	stack<wstring> elements;
};


