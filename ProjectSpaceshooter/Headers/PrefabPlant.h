#pragma once
#include "Prefabs.h"
#include <string>
#include <stack>



using namespace std;
class PrefabPlant
{
public:
	PrefabPlant(void);
	virtual ~PrefabPlant(void);
	
	static PrefabPlant * CreatePrefabPlantFor(PREFAB_TYPE prefabType);
	static void DeletePrefabPlant(PrefabPlant * _prefabPlant);
	
	virtual void nextElement(const wstring & name);
	virtual void nextElement(const wstring & prefix, const wstring & name);
	virtual void closeElement(const wstring & name) ;
	virtual void closeElement(const wstring & prefix, const wstring & name);
	virtual void setAttribute(const wstring & attribute, const wstring & value);
	virtual void setAttribute(const wstring & prefix, const wstring & attribute, const wstring & value);
	virtual void setText(const wstring & text) = 0;

	virtual Prefab * getCreatedPrefab() = 0;
	
	virtual const wstring &  getPrefabRootNode() = 0; 
	virtual const wstring &  getPrefabName() = 0;
	
	virtual void resetPrefab() = 0;
	bool IsPrefabReady();

	//Method to set pointer to prefab which is precessing
	void setPrefab(Prefab * pref);

protected:
	virtual void setMethodToFillProperty( const wstring & name ) = 0;
	unsigned int ValueToUINT(const wstring &value);

	virtual void fillPrefabProperty(const wstring & attribute, const wstring & value ) = 0;
	void _doNothing(const wstring & attribute, const wstring & value);
 
	
	void (PrefabPlant:: *methodToFillPrefabProperty)(const wstring & attribute, const wstring & value);
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

private:
	Prefab * _prefab;
};

class PrefabWithColider_Plant : virtual public PrefabPlant
{
public:
	PrefabWithColider_Plant();
	virtual ~PrefabWithColider_Plant();
protected:
	void setPrefab(PrefabWithColider * val) { prefabWithColider = val; }
	void _setColider(const wstring & attribute, const wstring & value);
	void _setColiderRadian(const wstring & attribute, const wstring & value);
	void _setColiderOffset(const wstring & attribute, const wstring & value);
	bool SetMethodToFillColiderProperty( const wstring & name );
	void (PrefabWithColider_Plant:: *methodToFillColiderProperty)(const wstring & attribute, const wstring & value);
private:
	PrefabWithColider * prefabWithColider;
	void clearColider();
	colider_struct colider;
};

class PrefabWithMesh_Plant : virtual public PrefabPlant
{
public:
	PrefabWithMesh_Plant();
	virtual ~PrefabWithMesh_Plant();
	bool SetMethodToFillMeshProperty( const wstring & name );
protected:
	void setPrefab(PrefabWithMesh * val) {_prefabWithMesh = val;}
	void _setMeshName(const wstring & attribute, const wstring & value);
	void _setScale(const wstring & attribute, const wstring & value);
	void _setRotation(const wstring & attribute, const wstring & value);
	void (PrefabWithMesh_Plant:: *methodToFillMeshProperty)(const wstring & attribute, const wstring & value);
private:
	PrefabWithMesh * _prefabWithMesh;
};
