#include "StaticPrefabPlant.h"

const wchar_t * StaticPrefabPlant::static_name         = L"static_name";
const wstring StaticPrefabPlant::prefabName            = L"static";
const wstring StaticPrefabPlant::rootStaticPrefabsNode = L"static_prefabs";

StaticPrefabPlant::StaticPrefabPlant()
{
	PrefabPlant::setPrefab(static_cast<Prefab*>(&mStaticPrefab));
	PrefabWithCollider_Plant::setPrefab(static_cast<PrefabWithCollider*>(&mStaticPrefab));
	PrefabWithMesh_Plant::setPrefab(static_cast<PrefabWithMesh*>(&mStaticPrefab)); 
}

void StaticPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

Prefab & StaticPrefabPlant::getCreatedPrefab()
{
	return mStaticPrefab;
}

const wstring StaticPrefabPlant::getPrefabRootNode()
{
	return wstring(rootStaticPrefabsNode);
}

const wstring StaticPrefabPlant::getPrefabNodeName()
{
	return wstring(prefabName);
}

const wstring StaticPrefabPlant::getPrefabName()
{
	return wstring(static_name);
}

void StaticPrefabPlant::resetPrefab()
{
	mStaticPrefab.resetPrefab();
	prefabReady = false;
}

StaticPrefabPlant::~StaticPrefabPlant()
{

}

bool StaticPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	const wstring & name = elements.top();
	if (PrefabPlant::setAttribute(attribute, value)) // Try to set properties in 'PrefabPlant'
	{
		return true;	// When succeed return true because property was set 
	} else if(PrefabWithCollider_Plant::setAttribute(attribute, value))
	{
		return true; 
	} else if(PrefabWithMesh_Plant::setAttribute(attribute, value))
	{
		return true;
	} else
	{
		return false;
	}
}

bool StaticPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	return setAttribute(attribute, value);
}


