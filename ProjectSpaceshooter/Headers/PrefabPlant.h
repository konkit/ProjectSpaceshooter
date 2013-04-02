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
	void virtual setAttribute(wstring prefix, wstring attribute, wstring value) = 0;
	void virtual setText(wstring text) = 0;
	virtual Prefab * getCreatedPrefab() = 0;
	void virtual resetPrefab() = 0;
	bool IsPrefabReady();
	virtual const wstring &  getPrefabRootNode() = 0; 
	virtual const wstring &  getPrefabName() = 0;
private:
	bool mPrefabReady;
	stack<wstring> elements;
};


