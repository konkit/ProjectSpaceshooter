#include "StaticPrefabPlant.h"

const wchar_t * StaticPrefabPlant::static_name         = L"static_name";
const wstring StaticPrefabPlant::prefabName            = L"static";
const wstring StaticPrefabPlant::rootStaticPrefabsNode = L"static_prefabs";

StaticPrefabPlant::StaticPrefabPlant()
{
	PrefabPlant::setPrefab(static_cast<Prefab*>(&mStaticPrefab));
	PrefabWithColider_Plant::setPrefab(static_cast<PrefabWithColider*>(&mStaticPrefab));
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

void StaticPrefabPlant::setMethodToFillProperty( const wstring & name )
{
	if (SetMethodToFillBasicProperty(name))
	{
		methodToFillStaticProperty = methodToFillBasicProperty;
	} else if(SetMethodToFillColiderProperty(name))
	{
		methodToFillStaticProperty = methodToFillColiderProperty;
	} else if(SetMethodToFillMeshProperty(name))
	{
		methodToFillStaticProperty = methodToFillMeshProperty;
	} else
	{
		methodToFillStaticProperty = &StaticPrefabPlant::_doNothing;
	}
}

void StaticPrefabPlant::fillPrefabProperty( const wstring & attribute, const wstring & value )
{
	(this->*methodToFillStaticProperty)(attribute,value);
}

StaticPrefabPlant::~StaticPrefabPlant()
{

}


