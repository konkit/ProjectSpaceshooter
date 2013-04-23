#pragma once
#include "PrefabPlant.h"

/**
 * TODO
 * 
 * @author Zyga
 */
class StaticPrefabPlant : virtual public PrefabWithCollider_Plant, virtual public PrefabWithMesh_Plant
{
public:
	StaticPrefabPlant();
	~StaticPrefabPlant();

	virtual void setText( const wstring & text );

	virtual Prefab & getCreatedPrefab();

	virtual const wstring getPrefabRootNode();

	virtual const wstring getPrefabNodeName();

	virtual const wstring getPrefabName();

	virtual void resetPrefab();

	virtual void setMethodToFillProperty( const wstring & name );

private:
	virtual void fillPrefabProperty( const wstring & attribute, const wstring & value );

	void (StaticPrefabPlant:: *methodToFillStaticProperty)(const wstring & attribute, const wstring & value);
	
	static const wstring rootStaticPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * static_name;

	StaticPrefab mStaticPrefab;

};