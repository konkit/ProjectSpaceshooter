#pragma once
#include <string>
#include <list>
#include "ColliderComponent.h"

using namespace std;
using Ogre::Vector3;

enum class PREFAB_TYPE
{
	EnemyPrefab,
	BulletPrefab,
	StaticPrefab,
	EffectPrefab,
	WeaponPrefab,
	LevelDescription
};


struct rotation_struct
{
	float x_rot; 
	float y_rot; 
	float z_rot;
	rotation_struct()
		: x_rot(0), y_rot(0), z_rot(0) {;}
	void resetScale(){x_rot = y_rot = z_rot = 0;}
};



/**
 * 
 * 
 * @author Zyga
 */
class Prefab
{
public:
	Prefab(void);
	virtual ~Prefab(void);
	virtual void resetPrefab();
	void		setPrefabID( unsigned int id ) {mPrefabID = id;}
	void		setName(std::string val) { mName = val; }
	unsigned	getPrefabID()	const { return mPrefabID; }
	std::string getName() const { return mName; }
protected:
	unsigned	mPrefabID;
	string		mName;
};

/**
 * 
 * 
 * @author Zyga
 */
class PrefabWithMesh :  public Prefab
{
public:
	PrefabWithMesh(): Prefab(), mScale(0,0,0) {;}
	~PrefabWithMesh(){;}
	void setMeshName(string val) { mMeshName = val; }
	void setScale(Vector3 scale){mScale = scale;}
	void setRotation(rotation_struct rotation){mRotation = rotation;}
	const Vector3			&	getScale()		const {return mScale;}
	const rotation_struct	&	getRotation()	const {return mRotation;}
	const std::string		&	getMeshName()	const { return mMeshName; }

	virtual void resetPrefab();

protected:
	string			mMeshName;
	rotation_struct mRotation;
	Vector3			mScale;

};

/**
 * 
 * 
 * @author Zyga
 */
class PrefabWithCollider : virtual public PrefabWithMesh
{
public:
	PrefabWithCollider() : PrefabWithMesh(), mColliders(), mExplosionEffectID(1) {;}
	void setMaxHealth(unsigned val) { mMaxHealth = val; }
	void setResistance(unsigned val) { mResistance = val; }

	void addCollider(Collider_struct Collider)
	{
		mColliders.addCollider(Collider);
	}

	void setInaccurateCollider(Collider_struct Collider)
	{
		mColliders.setInaccurateCollider(Collider);
	}
	const Collider & getCollider()	const {return mColliders;}
	unsigned		 getMaxHealth() const { return mMaxHealth; }
	unsigned		 getResistance() const { return mResistance; }
	
	void clearColliders() {mColliders.reset();}
	virtual void resetPrefab();
	unsigned getExplosionEffectID() const { return mExplosionEffectID; }
	void setExplosionEffectID(unsigned val) { mExplosionEffectID = val; }

protected:

	unsigned mResistance;
	unsigned mMaxHealth;
	Collider mColliders;
	unsigned mExplosionEffectID;
};




class MovablePrefab: virtual public PrefabWithMesh
{
public:
	void setMaxVelocity(unsigned velocity){mMaxVelocity = velocity;}
	void setMaxAcceleration(unsigned acceleration){mMaxAcceleration = acceleration;}
	void setMaxAngleVelocity(unsigned angleVel){mMaxAngleVelocity = angleVel;}
	unsigned	 getMaxVelocity()		const {return mMaxVelocity;}
	unsigned	 getMaxAcceleration()	const {return mMaxAcceleration;}
	unsigned	 getMaxAngleVelocity()	const {return mMaxAngleVelocity;}
	void resetPrefab();
private:
	unsigned		mMaxVelocity;
	unsigned		mMaxAcceleration;
	unsigned		mMaxAngleVelocity;
};


/** 
  *
  * @author konkit
  */
class BulletPrefab : public PrefabWithCollider, public MovablePrefab
{
public:
	BulletPrefab();
	BulletPrefab(unsigned prefabID);

	void setBulletPower(unsigned newPower) { mBulletPower = newPower; }
	void setVelocityVector( Ogre::Vector3 newVector){ mVelocityVector = newVector; }
	void setAutoAim(bool val) { mAutoAim = val; }

	bool			isAutoAim() const { return mAutoAim; }
	unsigned		getBulletPower() const { return mBulletPower; }
	Ogre::Vector3	getVelocityVector() const { return mVelocityVector; }

	virtual void resetPrefab();

private:
	bool		mAutoAim;
	unsigned		mBulletPower;

//Czy to tu jest potrzebne?
	Ogre::Vector3 mVelocityVector;
};

/** 
  *
  * @author Zyga
  */
class StaticPrefab : public PrefabWithCollider
{
public:
	virtual void resetPrefab();
};

/**
 * 
 * 
 * @author konkit
 */
class EffectPrefab : public PrefabWithCollider
{
public:
	EffectPrefab();
	EffectPrefab(unsigned prefabID) 
	{	
		mPrefabID = prefabID;
	}

	void setParticleSystemName( std::string newParticleSystem) {
		mParticleSystemName = newParticleSystem;
	}

	std::string getParticleSystemName() {
		return mParticleSystemName;
	}

	virtual void resetPrefab();

	//void setParticleSystem( Ogre::ParticleSystem newParticleSystem) {
	//	mParticleSystem = newParticleSystem;
	//}

	//Ogre::ParticleSystem getParticleSystem() {
	//	return mParticleSystem;
	//}

private:
	std::string mParticleSystemName;
	//Ogre::ParticleSystem* mParticleSystem;
};

/** 
  *
  * @author Zyga
  */
class ShipPrefab: public PrefabWithCollider, public MovablePrefab
{
public:
	ShipPrefab()
		: PrefabWithMesh(), PrefabWithCollider(), MovablePrefab()
	{
		resetPrefab();
	};
	ShipPrefab(unsigned prefabID);
	~ShipPrefab(void);
	void resetPrefab();
	void setWeaponPrefabID(unsigned val) { mWeaponPrefabID = val; }
	
	unsigned	 getWeaponPrefabID()	const { return mWeaponPrefabID; }
private:
	unsigned		mWeaponPrefabID;

};

class WeaponPrefab : public Prefab
{
public:
	WeaponPrefab();
	~WeaponPrefab();
	void setRateOfFire(unsigned val) { rateOfFire = val; }
	void setBulletPrefabID(unsigned val) { bulletPrefabID = val; }
	unsigned getBulletPrefabID() const { return bulletPrefabID; }
	unsigned getRateOfFire() const { return rateOfFire; }
	virtual void resetPrefab();
private:
	unsigned bulletPrefabID;
	unsigned rateOfFire;
};