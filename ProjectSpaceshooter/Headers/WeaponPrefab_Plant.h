#include "PrefabPlant.h"
#include "Prefabs.h"

/**
 * Class used to parse XML nodes into Weapon Prefab.
 * @author Zyga
 */
class WeaponPrefabPlant : public PrefabPlant
{
public:
	/**
	 * Initialize prefab, and initialize all base plants
	 * @author Zyga
	 */
	WeaponPrefabPlant();

	/**
	 * @author Zyga
	 */
	~WeaponPrefabPlant();

	/**
	 * Set XML text (<node> TEXT </node>)
	 * @param text XML text to set.
	 * @author Zyga
	 */
	virtual void setText( const wstring & text );

	/**
	 * @return created prefab. 
	 * @author Zyga
	 */
	virtual Prefab & getCreatedPrefab();


	/**
	 * Name which is used to open XML document. In this case it is "weapon_prefabs"
	 * @return "weapon_prefabs"
	 * @author Zyga
	 */
	virtual const wstring getPrefabRootNodeName();
	
	/**
	 * Name of XML node describing prefab.
	 * @return "weapon"
	 * @author Zyga
	 */
	virtual const wstring getPrefabNodeName();
	
	/**
	 * Return name of property "name" which describe prefab 
	 * @return "weapon_name"
	 * @author Zyga
	 */
	virtual const wstring getPrefabName();

	/**
	 * Reset all fields in prefab.
	 * Called before reading next prefab.
	 * @return 
	 * @author Zyga
	 */
	virtual void resetPrefab();

private:
	void _setBulletPrefabID(const wstring & attribute, const wstring & value );
	void _setRateOfFire(const wstring & attribute, const wstring & value );

	virtual bool setAttribute( const wstring & attribute, const wstring & value );

	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );


	WeaponPrefab mWeaponPrefab;
	static const wstring rootWeaponPrefabsNode;
	static const wstring prefabName;
	static const wstring bullet_prefab;
	static const wstring waepon_name;
	static const wstring rateOfFire;
};
