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
	virtual ~StaticPrefabPlant();

	virtual Prefab & getCreatedPrefab();

	virtual const wstring getPrefabRootNode();

	virtual const wstring getPrefabNodeName();

	virtual const wstring getPrefabName();

	virtual void resetPrefab();

	virtual bool setAttribute( const wstring & attribute, const wstring & value );

	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );

	virtual void setText( const wstring & text );

private:
	
	static const wstring rootStaticPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * static_name;

	StaticPrefab mStaticPrefab;

};