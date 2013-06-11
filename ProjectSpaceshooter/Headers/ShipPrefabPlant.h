#pragma once
#include "PrefabPlant.h"

/**
 * Class used to parse XML nodes into Ship Prefab.
 * @author Zyga
 */
class ShipPrefabPlant : virtual public PrefabWithCollider_Plant, virtual public PrefabWithMesh_Plant, virtual public MovablePrefab_Plant
{
public:

	/**
	 * Initialize prefab, and initialize all base plants
	 * @author Zyga
	 */
	ShipPrefabPlant();
	
	/**
	 * @author Zyga
	 */
	~ShipPrefabPlant();

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
	 * Name which is used to open XML document. In this case it is "ship_prefabs"
	 * @return "ship_prefabs"
	 * @author Zyga
	 */
	virtual const wstring getPrefabRootNodeName();

	/**
	 * Name of XML node describing prefab.
	 * @return "ship"
	 * @author Zyga
	 */
	virtual const wstring getPrefabNodeName();

	/**
	 * Return name of property "name" which describe prefab 
	 * @return "ship_name"
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

	/**
	 * @author Zyga
	 */
	void _setWaeponPrefab(const wstring & attribute, const wstring & value);
	/**
	 * @author Zyga
	 */
	void _setCameraHandler(const wstring & attribute, const wstring & value);
	/**
	 * @author Zyga
	 */
	void _setCameraHandlerOffset( const wstring & attribute, const wstring & value );
	/**
	 * @author Zyga
	 */
	void _setCameraHandlerLookAt( const wstring & attribute, const wstring & value );

	static const wstring rootEnemyPrefabsNode;
	static const wstring prefabName;
	static const wchar_t * ship_name;
	static const wchar_t * lookAt;
	static const wchar_t * camera;
	static const wchar_t * cameraHandlers;

	ShipPrefab _shipPrefab;
	cameraHandler _cameraHandler;
};