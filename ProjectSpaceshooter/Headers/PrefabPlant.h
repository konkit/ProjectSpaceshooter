#pragma once
#include "Prefabs.h"
#include <string>
#include <stack>

using namespace std;

/**
 * @return Value converted to int
 * @param value 
 * @author Zyga
 */
unsigned int ValueToUINT(const wstring &value );
/**
 * @return  Value converted to double
 * @param value 
 * @author Zyga
 */
double ValueToDouble(const wstring &value );

/**
 * Base abstract class to each prefab plant.
 * Prefab plant are used to parse XML nodes into prefabs
 * @author Zyga
 */
class PrefabPlant
{
public:

	/**
	 * @author Zyga
	 */
	PrefabPlant(void);
	
	/**
	 * @author Zyga
	 */
	virtual ~PrefabPlant(void);
	
	/**
	 * Factory method used to create prefab plant matching to given type. 
	 * It require to delete prefab plant by DeletePrefabPlant method to avoid memory leaks.
	 * @param prefabType Type of prefab which will be created.
	 * @author Zyga
	 */
	static PrefabPlant * CreatePrefabPlantFor(PREFAB_TYPE prefabType);
	
	/**
	 * @param _prefabPlant Plant to destroy
	 * @author Zyga
	 */
	static void DeletePrefabPlant(PrefabPlant * _prefabPlant);
	
	/**
	 * Open next XML node and prepare to read its attributes
	 * @param name XML node name
	 * @author Zyga
	 */
	void nextElement(const wstring & name);
	
	/**
	 * Open next XML node and prepare to read its attributes
	 * @param name XML node name
	 * @author Zyga
	 */
	void nextElement(const wstring & prefix, const wstring & name);
	
	/**
	 * Close XML node having given name. If given node isn't actually processed node throw exception
	 * @param name XML node name
	 * @author Zyga
	 */
	void closeElement(const wstring & name) ;

	/**
	 * Close XML node having given name. If given node isn't actually processed node throw exception
	 * @param name XML node name
	 * @author Zyga
	 */
	void closeElement(const wstring & prefix, const wstring & name);
	
	/**
	 * Set attribute contained by last read node.  
	 * @return True if this plant can set property with this attribute.
	 * @param attribute Attribute to set.
	 * @param value Value to set in prefab.
	 * @author Zyga
	 */
	virtual bool setAttribute(const wstring & attribute, const wstring & value);
	
	/**
	 * Set attribute contained by last read node.  
	 * @return True if this plant can set property with this attribute.
	 * @param prefix 
	 * @param attribute Attribute to set.
	 * @param value Value to set in prefab.
	 * @author Zyga
	 */
	virtual bool setAttribute(const wstring & prefix, const wstring & attribute, const wstring & value);

	/**
	 * Set XML text (<node> TEXT </node>)
	 * @param text XML text to set.
	 * @author Zyga
	 */
	virtual void setText(const wstring & text) = 0;

	/**
	 * @return Created prefab. 
	 * @author Zyga
	 */
	virtual Prefab & getCreatedPrefab() = 0;
	
	/**
	 * @return Name which is used to open XML document. 
	 * @author Zyga
	 */
	virtual const wstring getPrefabRootNodeName() = 0; 

	/**
	 * @return Name of XML node describing prefab.
	 * @author Zyga
	 */
	virtual const wstring getPrefabNodeName() = 0;

	/**
	 * Return name of property "name" which describe prefab 
	 * @return "bullet_name"
	 * @author Zyga
	 */
	virtual const wstring getPrefabName() = 0;
	
	/**
	 * Reset all fields in prefab.
	 * Called before reading next prefab.
	 * @return 
	 * @author Zyga
	 */
	virtual void resetPrefab() = 0;

	/**
	 * @return True if there isn't any opened XML nodes
	 * @author Zyga
	 */
	bool IsPrefabReady();

	/**
	 * Method to set pointer to prefab which is precessing
	 * @return 
	 * @param pref 
	 * @author Zyga
	 */
	void setPrefab(Prefab * pref);

protected:
	
	void _doNothing(const wstring & attribute, const wstring & value);
	void _setPrefabID(const wstring & attribute, const wstring & value);
	void _setPrefabName(const wstring & attribute, const wstring & value);
	bool prefabReady;
	stack<wstring> elements;

//--------- Attribute names -------------------------
	static const wchar_t * name;
	static const wchar_t * id;
	static const wchar_t * value;
	static const wchar_t * x_pos;
	static const wchar_t * y_pos;
	static const wchar_t * z_pos;
	static const wchar_t * closeNode;
	static const wchar_t * yes;
	static const wchar_t * no;
	static const wchar_t * offset;

//---------- Element names --------------------------

	static const wchar_t * standard_waepon;

private:
	Prefab * _prefab;
};

/**
 * @author Zyga
 */
class PrefabWithCollider_Plant : virtual public PrefabPlant
{
public:
	PrefabWithCollider_Plant();
	virtual ~PrefabWithCollider_Plant();
	virtual bool setAttribute( const wstring & attribute, const wstring & value );
	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );
protected:
	void setPrefab(PrefabWithCollider * val) 
	{ 
		prefabWithCollider = val; 
		PrefabPlant::setPrefab(val);
	}
	void _setCollider(const wstring & attribute, const wstring & value);
	void _setInaccurateCollider(const wstring & attribute, const wstring & value);
	void _setColliderRadius(const wstring & attribute, const wstring & value);
	void _setColliderOffset(const wstring & attribute, const wstring & value);
	void _setMaxHealth(const wstring & attribute, const wstring & value);
	void _setExplosionID(const wstring & attribute, const wstring & value);

	static const wchar_t * health;
	static const wchar_t * Collider;
	static const wchar_t * inaccurate_Collider;
	static const wchar_t * Colliders;

	static const wchar_t * radius;
	static const wchar_t * explosion_id;
private:
	PrefabWithCollider * prefabWithCollider;
	void clearCollider();

	Collider_struct Collider_str;
};


/**
 * @author Zyga
 */
class PrefabWithMesh_Plant : virtual public PrefabPlant
{
public:
	PrefabWithMesh_Plant();
	virtual ~PrefabWithMesh_Plant();

	virtual bool setAttribute( const wstring & attribute, const wstring & value );
	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );

protected:
	void setPrefab(PrefabWithMesh * val) 
	{
		_prefabWithMesh = val;
		PrefabPlant::setPrefab(val);
	}
	void _setMeshName(const wstring & attribute, const wstring & value);
	void _setScale(const wstring & attribute, const wstring & value);
	void _setRotation(const wstring & attribute, const wstring & value);

	static const wchar_t * x_scale;
	static const wchar_t * y_scale;
	static const wchar_t * z_scale;
	static const wchar_t * x_rot;
	static const wchar_t * y_rot;
	static const wchar_t * z_rot;
	
	static const wchar_t * mesh;
	static const wchar_t * scale;
	static const wchar_t * rotation;

private:
	PrefabWithMesh * _prefabWithMesh;
};

/**
 * @author Zyga
 */
class MovablePrefab_Plant : virtual public PrefabPlant
{
public:
	MovablePrefab_Plant(){};
	virtual ~MovablePrefab_Plant(){};

	virtual bool setAttribute( const wstring & attribute, const wstring & value );
	virtual bool setAttribute( const wstring & prefix, const wstring & attribute, const wstring & value );

protected:
	void setPrefab(MovablePrefab * val) 
	{
		_MovablePrefab = val;
		PrefabPlant::setPrefab(val);
	}
	void _setMaxAcceleration(const wstring & attribute, const wstring & value);
	void _setMaxAngleVelocity(const wstring & attribute, const wstring & value);
	void _setMaxVelocity(const wstring & attribute, const wstring & value);
	void _setThrusterName(const wstring & attribute, const wstring & value);
	void _setThrusterOffset(const wstring & attribute, const wstring & value);

private:
	static const wchar_t * thruster;
	static const wchar_t * thrusterName;
	static const wchar_t * max_velocity;
	static const wchar_t * max_acceleration;
	static const wchar_t * max_angle_velocity;
	MovablePrefab * _MovablePrefab;
	Vector3 thr_offset;
};