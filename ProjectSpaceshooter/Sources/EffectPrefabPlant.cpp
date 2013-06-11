#include "EffectPrefabPlant.h"

void EffectPrefabPlant::setText( const wstring & text )
{
	throw std::exception("The method or operation is not implemented.");
}

Prefab & EffectPrefabPlant::getCreatedPrefab()
{
	return mEffectPrefab;
}

const wstring EffectPrefabPlant::getPrefabRootNodeName()
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

EffectPrefabPlant::EffectPrefabPlant()
{
	PrefabPlant::setPrefab(&mEffectPrefab);
	PrefabWithCollider_Plant::setPrefab(&mEffectPrefab);
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

bool EffectPrefabPlant::setAttribute( const wstring & attribute, const wstring & value )
{
	const wstring & stack_top = elements.top();

	if (PrefabPlant::setAttribute(attribute,value))
	{
		return true;
	} 
	else if (PrefabWithCollider_Plant::setAttribute(attribute, value))
	{
		return true;
	}
	else if (stack_top == particleSystemName)
	{
		_setParticleSystemName(attribute,value);
	} else if (stack_top == ttl)
	{
		_setTTL(attribute,value);
	} else if (stack_top == effect_power)
	{
		_setEffectPower(attribute,value);
	} else
	{
		return false;
	}
}

bool EffectPrefabPlant::setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value )
{
	throw std::exception("The method or operation is not implemented.");
}


const wchar_t * EffectPrefabPlant::particleSystemName = L"particleSystemName";
const wchar_t * EffectPrefabPlant::effect_name = L"effect_name";
const wstring   EffectPrefabPlant::prefabName = L"effect";
const wstring   EffectPrefabPlant::rootEffectPrefabsNode = L"effect_prefabs";
const wchar_t * EffectPrefabPlant::ttl = L"ttl";
const wchar_t * EffectPrefabPlant::effect_power = L"effect_power";
