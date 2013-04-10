#include "PrefabPlant.h"
#include "Prefabs.h"

/**
 * 
 * 
 * @author Zyga
 */
class WeaponPrefabPlant : public PrefabPlant
{
public:
	WeaponPrefabPlant();
	~WeaponPrefabPlant();

	virtual void setText( const wstring & text );

	virtual Prefab & getCreatedPrefab();
	virtual const wstring getPrefabRootNode();
	virtual const wstring getPrefabNodeName();
	virtual const wstring getPrefabName();
	virtual void resetPrefab();
	virtual void setMethodToFillProperty( const wstring & name );

private:
	void _setBulletPrefabID(const wstring & attribute, const wstring & value );
	void _setRateOfFire(const wstring & attribute, const wstring & value );

	virtual void fillPrefabProperty(const wstring & attribute, const wstring & value );

	void (WeaponPrefabPlant:: *methodToFillWeaponProperty)(const wstring & attribute, const wstring & value);
	
	WeaponPrefab mWeaponPrefab;
	static const wstring rootWeaponPrefabsNode;
	static const wstring prefabName;
	static const wstring bullet_prefab;
	static const wstring waepon_name;
	static const wstring rateOfFire;
};
