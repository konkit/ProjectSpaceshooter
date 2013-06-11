#pragma once
#include "PrefabPlant.h"

/**
 * Class used to parse XML nodes into Effect Prefab.
 * @author Zyga
 */
class EffectPrefabPlant : public PrefabWithCollider_Plant
{
public:

	/**
	 * Initialize prefab, and initialize all base plants
	 * @author Zyga
	 */
	EffectPrefabPlant();
	/**
	 * @author Zyga
	 */
	~EffectPrefabPlant();

	/**
	 * Set XML text (<node> TEXT </node>)
	 * @param text XML text to set.
	 * @author Zyga
	 */
	virtual void setText( const wstring & text );
	
	/**
	 * @return Created prefab. 
	 * @author Zyga
	 */
	virtual Prefab & getCreatedPrefab();

	/**
	 * Reset all fields in prefab.
	 * Called before reading next prefab.
	 * @return 
	 * @author Zyga
	 */
	virtual void resetPrefab();

	/**
	 * Name which is used to open XML document. In this case it is "effect_prefabs"
	 * @return "effect_prefabs"
	 * @author Zyga
	 */
	virtual const wstring getPrefabRootNodeName();
	
	/**
	 * Name of XML node describing prefab.
	 * @return "effect"
	 * @author Zyga
	 */
	virtual const wstring getPrefabNodeName();
	
	/**
	 * Return name of property "name" which describe prefab 
	 * @return "effect_name"
	 * @author Zyga
	 */
	virtual const wstring getPrefabName();

	/**
	 * Set attribute contained by last read node.  
	 * @return True if this plant can set property with this attribute.
	 * @param attribute Attribute to set.
	 * @param value Value to set in prefab.
	 * @author Zyga
	 */
	virtual bool setAttribute( const wstring & attribute, const wstring & value );

	/**
	 * This plant don't use prefix so it relay attribute and value to setAttribute with two parameters.
	 * @author Zyga
	 */
	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );
	



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

