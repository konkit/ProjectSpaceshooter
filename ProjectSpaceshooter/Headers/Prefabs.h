#pragma once
#include <string>
#include <list>
using namespace std;

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
		: x_rot(0), y_rot(0), z_rot(0) {}
	void resetScale(){x_rot = y_rot = z_rot = 0;}
};

struct colider_struct
{
	Vector3			offset;
	unsigned		radian;
	colider_struct()
		: radian(0), offset(0.0, 0.0, 0.0) {}
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
class PrefabWithColider : virtual public Prefab
{
public:
	void setColiderList(std::list<colider_struct> coliders){mColiders = coliders;}
	void setMaxHealth(unsigned val) { mMaxHealth = val; }
	void setResistance(unsigned val) { mResistance = val; }

	void addColider(colider_struct colider)
	{
		//Square radian
		colider.radian *= colider.radian; 
		mColiders.push_back(colider);
	}
	const colider_struct	&			getColider()	const {return mColiders.front();}
	const std::list<colider_struct> &	getColiderList() const {return mColiders;}
	unsigned							getMaxHealth() const { return mMaxHealth; }
	unsigned							getResistance() const { return mResistance; }
	
	void clearColiders() {mColiders.clear();}
	virtual void resetPrefab();

protected:
	unsigned mResistance;
	unsigned mMaxHealth;
	std::list<colider_struct>	mColiders;
};


/**
 * 
 * 
 * @author Zyga
 */
class PrefabWithMesh : virtual public Prefab
{
public:
	PrefabWithMesh(){;}
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
  * @author konkit
  */
class BulletPrefab : public PrefabWithColider, public PrefabWithMesh
{
public:
	BulletPrefab();
	BulletPrefab(unsigned prefabID);

	void setBulletPower(float newPower) { mBulletPower = newPower; }
	void setMaxVelocity(float newMaxVelocity) { mMaxVelocity= newMaxVelocity; }
	void setVelocityVector( Ogre::Vector3 newVector){ mVelocityVector = newVector; }
	void setAutoAim(bool val) { mAutoAim = val; }

	bool			isAutoAim() const { return mAutoAim; }
	float			getBulletPower() const { return mBulletPower; }
	float			getMaxVelocity() const { return mMaxVelocity; }
	Ogre::Vector3	getVelocityVector() const { return mVelocityVector; }

	virtual void resetPrefab();

private:
	bool		mAutoAim;
	float		mBulletPower;
	float		mMaxVelocity;

//Czy to tu jest potrzebne?
	Ogre::Vector3 mVelocityVector;
};

/** 
  *
  * @author Zyga
  */
class StaticPrefab : public PrefabWithColider, public PrefabWithMesh
{
public:
	virtual void resetPrefab();
};

/**
 * 
 * 
 * @author konkit
 */
class EffectPrefab : public Prefab
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
class ShipPrefab: public PrefabWithMesh, public PrefabWithColider
{
public:
	ShipPrefab()
		: Prefab()
	{
		resetPrefab();
	};
	ShipPrefab(unsigned prefabID);
	~ShipPrefab(void);
	void resetPrefab();
	void setWeaponPrefabID(unsigned val) { mWeaponPrefabID = val; }
	void setMaxVelocity(unsigned velocity){mMaxVelocity = velocity;}
	void setMaxAcceleration(unsigned acceleration){mMaxAcceleration = acceleration;}
	void setMaxAngleVelocity(unsigned angleVel){mMaxAngleVelocity = angleVel;}
	void setMaxHealth(unsigned health){mMaxHealth = health;}
	
	unsigned	 getWeaponPrefabID()	const { return mWeaponPrefabID; }
	unsigned	 getMaxVelocity()		const {return mMaxVelocity;}
	unsigned	 getMaxAcceleration()	const {return mMaxAcceleration;}
	unsigned	 getMaxAngleVelocity()	const {return mMaxAngleVelocity;}
	unsigned	 getMaxHealth()			const {return mMaxHealth;}
	
	//void setResistance(unsigned int val) { mResistance = val; }
	//unsigned int getResistance()		const { return mResistance; }
private:
	//unsigned		mResistance;
	unsigned		mMaxVelocity;
	unsigned		mMaxAcceleration;
	unsigned		mMaxAngleVelocity;
	unsigned		mMaxHealth;
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