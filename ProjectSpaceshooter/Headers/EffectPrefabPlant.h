#pragma once
#include "PrefabPlant.h"

class EffectPrefabPlant : public PrefabPlant
{
public:
	EffectPrefabPlant();
	~EffectPrefabPlant();

	virtual void setText( const wstring & text );

	virtual Prefab & getCreatedPrefab();

	virtual const wstring getPrefabRootNode();

	virtual const wstring getPrefabNodeName();

	virtual const wstring getPrefabName();

	virtual void resetPrefab();

	virtual void setMethodToFillProperty( const wstring & name );

	virtual void fillPrefabProperty( const wstring & attribute, const wstring & value );

private:
	void _setParticleSystemName(const wstring & attribute, const wstring & value);

	void (EffectPrefabPlant:: *methodToFillEffectProperty)(const wstring & attribute, const wstring & value);

	static const wstring rootEffectPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * effect_name;
	static const wchar_t * particleSystemName;

	EffectPrefab mEffectPrefab;
};

