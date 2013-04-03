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
	virtual void nextElement(const wstring & name);
	virtual void nextElement(const wstring & prefix, const wstring & name);
	virtual void closeElement(const wstring & name) ;
	virtual void closeElement(const wstring & prefix, const wstring & name) ;
	virtual void setAttribute(const wstring & attribute, const wstring & value) = 0;
	virtual void setAttribute(const wstring & prefix, const wstring & attribute, const wstring & value) = 0;
	virtual void setText(const wstring & text) = 0;
	virtual Prefab * getCreatedPrefab() = 0;
	virtual void resetPrefab() = 0;
	virtual const wstring &  getPrefabRootNode() = 0; 
	virtual const wstring &  getPrefabName() = 0;
	bool IsPrefabReady();
protected:
	unsigned int ValueToUINT(const wstring &value);
	bool prefabReady;
	stack<wstring> elements;

	static const wchar_t * name;
	static const wchar_t * id;
	static const wchar_t * value;
	static const wchar_t * x_scale;
	static const wchar_t * y_scale;
	static const wchar_t * z_scale;
	static const wchar_t * x_rot;
	static const wchar_t * y_rot;
	static const wchar_t * z_rot;
	static const wchar_t * x_pos;
	static const wchar_t * y_pos;
	static const wchar_t * z_pos;
	static const wchar_t * close;

//---------- Element names --------------------------
	static const wchar_t * mesh;
	static const wchar_t * max_velocity;
	static const wchar_t * max_acceleration;
	static const wchar_t * max_angle_velocity;
	static const wchar_t * health;
	static const wchar_t * scale;
	static const wchar_t * rotation;
	static const wchar_t * colider;
	static const wchar_t * coliders;
	static const wchar_t * offset;
	static const wchar_t * radian;
	static const wchar_t * standard_waepon;

};


