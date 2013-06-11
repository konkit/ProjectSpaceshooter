#pragma once
#include "PrefabPlant.h"

/**
 * Class used to parse XML nodes into Bullet Prefab.
 * @author Zyga
 */
class BulletPrefabPlant : virtual public PrefabWithCollider_Plant, virtual public PrefabWithMesh_Plant, virtual public MovablePrefab_Plant
{
public:

	/**
	 * Initialize prefab, and initialize all base plants
	 * @author Zyga
	 */
	BulletPrefabPlant();;
	~BulletPrefabPlant();;

	/**
	 * Set XML text (<node> TEXT </node>)
	 * @param text XML text to set.
	 * @author Zyga
	 */
	void setText(const wstring & text );

	/**
	 * @return Created prefab. 
	 * @author Zyga
	 */
	Prefab & getCreatedPrefab();

	/**
	 * Reset all fields in prefab.
	 * Called before reading next prefab.
	 * @return 
	 * @author Zyga
	 */
	void virtual resetPrefab();

	/**
	 * Name which is used to open XML document. In this case it is "bullet_prefabs"
	 * @return "bullet_prefabs"
	 * @author Zyga
	 */
	virtual const wstring getPrefabRootNodeName();

	/**
	 * Name of XML node describing prefab.
	 * @return "bullet"
	 * @author Zyga
	 */
	virtual const wstring getPrefabNodeName();

	/**
	 * Return name of property "name" which describe prefab 
	 * @return "bullet_name"
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
	void _setShipName(const wstring & attribute, const wstring & value);
	void _setAutoAim(const wstring & attribute, const wstring & value);
	void _setBulletPower(const wstring & attribute, const wstring & value);
	void _setTTL(const wstring & attribute, const wstring & value);


	static const wstring rootBulletPrefabsNode;
	static const wstring prefabName;
	BulletPrefab mBulletPrefab;

	static const wchar_t * bullet_name;
	static const wchar_t * auto_aim;
	static const wchar_t * bullet_power;
	static const wchar_t * ttl;

};
