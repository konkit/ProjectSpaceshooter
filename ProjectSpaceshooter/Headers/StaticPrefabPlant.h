#pragma once
#include "PrefabPlant.h"

/**
 * Class used to parse XML nodes into Static Prefab.
 * @author Zyga
 */
class StaticPrefabPlant : virtual public PrefabWithCollider_Plant, virtual public PrefabWithMesh_Plant
{
public:
	/**
	 * Initialize prefab, and initialize all base plants
	 * @author Zyga
	 */
	StaticPrefabPlant();

	/**
	 * @author Zyga
	 */
	virtual ~StaticPrefabPlant();

	/**
	 * @return created prefab. 
	 * @author Zyga
	 */
	virtual Prefab & getCreatedPrefab();

	/**
	 * Name which is used to open XML document. In this case it is "static_prefabs"
	 * @return "static_prefabs"
	 * @author Zyga
	 */
	virtual const wstring getPrefabRootNodeName();

	/**
	 * Name of XML node describing prefab.
	 * @return "static"
	 * @author Zyga
	 */
	virtual const wstring getPrefabNodeName();

	/**
	 * Return name of property "name" which describe prefab 
	 * @return "static_name"
	 * @author Zyga
	 */
	virtual const wstring getPrefabName();

	/**
	 * Reset prefab. This method should called before reading next prefab.
	 * @author Zyga
	 */
	virtual void resetPrefab();

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
	
	/**
	 * Set XML text (<node> TEXT </node>)
	 * @param text XML text to set.
	 * @author Zyga
	 */
	virtual void setText( const wstring & text );

private:
	
	static const wstring rootStaticPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * static_name;

	StaticPrefab mStaticPrefab;

};