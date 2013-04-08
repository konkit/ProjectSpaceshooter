#pragma once
#include <string>
#include <list>
using namespace std;

enum class PREFAB_TYPE
{
	EnemyPrefab,
	BulletPrefab,
	StaticPrefab,
	EffectPrefab
};

struct scale_struct
{
	unsigned x_scale; 
	unsigned y_scale; 
	unsigned z_scale;
	scale_struct()
		:x_scale(0), y_scale(0), z_scale(0){}
};

struct rotation_struct
{
	unsigned x_rot; 
	unsigned y_rot; 
	unsigned z_rot;
	rotation_struct()
		: x_rot(0), y_rot(0), z_rot(0) {}
};
struct offset_struct
{
	unsigned x_pos;
	unsigned y_pos;
	unsigned z_pos;
	offset_struct()
		: x_pos(0), y_pos(0), z_pos(0) {}
};
struct colider_struct
{
	offset_struct	offset;
	unsigned		radian;
	colider_struct()
		: radian(0) {}
};

class Prefab
{
public:
	Prefab(void);
	virtual ~Prefab(void);
	virtual void resetPrefab() = 0;
};

class PrefabWithColider : virtual public Prefab
{
public:
	void setColiderList(std::list<colider_struct> coliders){mColiders = coliders;}
	void addColider(colider_struct colider){mColiders.push_back(colider);}
	const colider_struct	&			getColider()	const {return mColiders.front();}
	const std::list<colider_struct> &	getColiderList() const {return mColiders;}
	void clearColiders() {mColiders.clear();}

	virtual void resetPrefab();

protected:
	std::list<colider_struct>	mColiders;
};

class PrefabWithMesh : virtual public Prefab
{
public:
	PrefabWithMesh(){;}
	~PrefabWithMesh(){;}
	void setMeshName(string val) { mMeshName = val; }
	void setScale(scale_struct scale){mScale = scale;}
	void setRotation(rotation_struct rotation){mRotation = rotation;}
	const scale_struct		&			getScale()		const {return mScale;}
	const rotation_struct	&			getRotation()	const {return mRotation;}
	const std::string		&			getMeshName()	const { return mMeshName; }

	virtual void resetPrefab();

protected:
	string			mMeshName;
	rotation_struct mRotation;
	scale_struct	mScale;

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

	void setPrefabID(unsigned val) { mPrefabID = val; }
	void setMeshName(string val) { mMeshName = val; }
	void setBulletPower(float newPower) { bulletPower = newPower; }
	void setMaxVelocity(float newMaxVelocity) { mMaxVelocity= newMaxVelocity; }
	void setVelocityVector( Ogre::Vector3 newVector){ mVelocityVector = newVector; }

	unsigned	 getPrefabID()   const { return mPrefabID; }
	std::string	 getMeshName()	  const { return mMeshName; }
	float		 getBulletPower() const { return bulletPower; }
	float		 getMaxVelocity() const { return mMaxVelocity; }
	Ogre::Vector3 getVelocityVector() const { return mVelocityVector; }

	virtual void resetPrefab();

private:
	unsigned	mPrefabID;
	string		mMeshName;
	float		bulletPower;
	float		mMaxVelocity;
	Ogre::Vector3 mVelocityVector;
};

/** 
  *
  * @author Zygi
  */
class StaticPrefab : public PrefabWithColider, public PrefabWithMesh
{
public:
	void setStaticPrefabID(unsigned val) { mStaticPrefabID = val; }
	void setMeshName(string val) { mMeshName = val; }
	void setResistance(unsigned int val) { resistance = val; }

	unsigned	 getStaticPrefabID()   const { return mStaticPrefabID; }
	std::string	 getMeshName()	  const { return mMeshName; }
	unsigned int getResistance()  const { return resistance; }

	virtual void resetPrefab();

private:
	unsigned	resistance;
	unsigned	mStaticPrefabID;
	string		mMeshName;
};


class EffectPrefab : public Prefab
{
public:
	EffectPrefab();
	EffectPrefab(unsigned prefabID) : mPrefabID(prefabID)
	{	}

	void setPrefabID(unsigned val) { mPrefabID = val; }
	unsigned	 getPrefabID()   const { return mPrefabID; }

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
	unsigned	mPrefabID;
};

/** 
  *
  * @author Zygi
  */
class EnemyPrefab: public PrefabWithMesh, public PrefabWithColider
{
public:
	EnemyPrefab()
		: Prefab()
	{
		resetPrefab();
	};
	EnemyPrefab(unsigned prefabID);
	~EnemyPrefab(void);
	void resetPrefab();
	
	void setPrefabID(unsigned val) { mEnemyPrefabID = val; }
	void setWeaponPrefabID(unsigned val) { mWeaponPrefabID = val; }
	void setAiType(AI_TYPE val) { mMyAI = val; }
	void setResistance(unsigned int val) { mResistance = val; }
	void setMaxVelocity(unsigned velocity){mMaxVelocity = velocity;}
	void setMaxAcceleration(unsigned acceleration){mMaxAcceleration = acceleration;}
	void setMaxAngleVelocity(unsigned angleVel){mMaxAngleVelocity = angleVel;}
	void setMaxHealth(unsigned health){mMaxHealth = health;}
	
	unsigned	 getPrefabID()			const { return mEnemyPrefabID; }
	unsigned	 getWeaponPrefabID()	const { return mWeaponPrefabID; }
	AI_TYPE		 getAiType()			const { return mMyAI; }
	unsigned int getResistance()		const { return mResistance; }
	unsigned	 getMaxVelocity()		const {return mMaxVelocity;}
	unsigned	 getMaxAcceleration()	const {return mMaxAcceleration;}
	unsigned	 getMaxAngleVelocity()	const {return mMaxAngleVelocity;}
	unsigned	 getMaxHealth()			const {return mMaxHealth;}
private:
	unsigned		mResistance;
	unsigned		mEnemyPrefabID;
	unsigned		mMaxVelocity;
	unsigned		mMaxAcceleration;
	unsigned		mMaxAngleVelocity;
	unsigned		mMaxHealth;
	AI_TYPE			mMyAI; 
	unsigned		mWeaponPrefabID;

};