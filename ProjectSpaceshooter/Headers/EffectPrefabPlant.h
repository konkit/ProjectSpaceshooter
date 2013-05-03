#pragma once
#include "PrefabPlant.h"

class EffectPrefabPlant : public PrefabWithCollider_Plant
{
public:
	EffectPrefabPlant();
	~EffectPrefabPlant();

	virtual bool setAttribute( const wstring & attribute, const wstring & value );
	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );
	virtual void setText( const wstring & text );

	virtual Prefab & getCreatedPrefab();

	virtual const wstring getPrefabRootNode();

	virtual const wstring getPrefabNodeName();

	virtual const wstring getPrefabName();

	virtual void resetPrefab();


private:
	void _setParticleSystemName(const wstring & attribute, const wstring & value);
	void _setTTL(const wstring & attribute, const wstring & value);
	void _setEffectPower(const wstring & attribute, const wstring & value);


	static const wstring rootEffectPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * effect_name;
	static const wchar_t * particleSystemName;
	static const wchar_t * ttl;
	static const wchar_t * effect_power;

	EffectPrefab mEffectPrefab;
};

