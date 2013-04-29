#include "EffectPrefabPlant.h"

void EffectPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

Prefab & EffectPrefabPlant::getCreatedPrefab()
{
	return mEffectPrefab;
}

const wstring EffectPrefabPlant::getPrefabRootNode()
{
	return wstring(rootEffectPrefabsNode);
}

const wstring EffectPrefabPlant::getPrefabNodeName()
{
	return wstring(prefabName);
}

const wstring EffectPrefabPlant::getPrefabName()
{
	return wstring(effect_name);
}

void EffectPrefabPlant::resetPrefab()
{
	mEffectPrefab.resetPrefab();
	prefabReady = false;
}

void EffectPrefabPlant::setMethodToFillProperty( const wstring & name )
{
	if (SetMethodToFillBasicProperty(name))
	{
		methodToFillEffectProperty = methodToFillBasicProperty;
	} 
	else if (SetMethodToFillColliderProperty(name))
	{
		methodToFillEffectProperty = methodToFillColliderProperty;
	}
	else if (name == particleSystemName)
	{
		methodToFillEffectProperty = &EffectPrefabPlant::_setParticleSystemName;
	} else if (name == ttl)
	{
		methodToFillEffectProperty = &EffectPrefabPlant::_setTTL;
	} else if (name == effect_power)
	{
		methodToFillEffectProperty = &EffectPrefabPlant::_setEffectPower;
	} else
	{
		methodToFillEffectProperty = &EffectPrefabPlant::_doNothing;
	}
}

void EffectPrefabPlant::fillPrefabProperty( const wstring & attribute, const wstring & value )
{
	(this->*methodToFillEffectProperty)(attribute, value);
}

EffectPrefabPlant::EffectPrefabPlant()
{
	PrefabPlant::setPrefab(&mEffectPrefab);
	PrefabWithCollider_Plant::setPrefab(&mEffectPrefab);
	methodToFillEffectProperty = &EffectPrefabPlant::_doNothing;
}

EffectPrefabPlant::~EffectPrefabPlant()
{

}

void EffectPrefabPlant::_setParticleSystemName( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::name)
	{
		mEffectPrefab.setParticleSystemName(string(value.begin(), value.end()));
	} else if (attribute == PrefabPlant::closeNode)
	{
	} else
	{
		throw My_Exception(L"EffectPrefabPlant _setParticleSystemName: unrecognized attribute - " + attribute);
	}
}

void EffectPrefabPlant::_setTTL( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		double val;
		val = ValueToDouble(value);
		mEffectPrefab.setTTL(val);
	};
}

void EffectPrefabPlant::_setEffectPower( const wstring & attribute, const wstring & value )
{
	if (attribute == PrefabPlant::value)
	{
		unsigned val;
		val = ValueToUINT(value);
		mEffectPrefab.setPower(val);
	};
}

const wchar_t * EffectPrefabPlant::particleSystemName = L"particleSystemName";

const wchar_t * EffectPrefabPlant::effect_name = L"effect_name";

const wstring EffectPrefabPlant::prefabName = L"effect";

const wstring EffectPrefabPlant::rootEffectPrefabsNode = L"effect_prefabs";

const wchar_t * EffectPrefabPlant::ttl = L"ttl";
const wchar_t * EffectPrefabPlant::effect_power = L"effect_power";
