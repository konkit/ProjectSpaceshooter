#pragma once
#include <string>
using namespace std;

enum class PREFAB_TYPE
{
	EnemyPrefab,
	BulletPrefab,
	StaticPrefab,
	EffectPrefab
};

class Prefab
{
public:
	Prefab(void);
	virtual ~Prefab(void);
};

/** 
  *
  * @author konkit
  */
class BulletPrefab : public Prefab
{
public:
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
class StaticPrefab : public Prefab
{
public:
	void setStaticPrefabID(unsigned val) { mStaticPrefabID = val; }
	void setMeshName(string val) { mMeshName = val; }
	void setResistance(unsigned int val) { resistance = val; }

	unsigned	 getStaticPrefabID()   const { return mStaticPrefabID; }
	std::string	 getMeshName()	  const { return mMeshName; }
	unsigned int getResistance()  const { return resistance; }
private:
	unsigned	resistance;
	unsigned	mStaticPrefabID;
	string		mMeshName;
};


class EffectPrefab : public Prefab
{
public:
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
class EnemyPrefab: public Prefab
{
public:
	EnemyPrefab(){};
	EnemyPrefab(unsigned prefabID);
	~EnemyPrefab(void);
	
	void setPrefabID(unsigned val) { mEnemyPrefabID = val; }
	void setWeaponPrefabID(unsigned val) { mWeaponPrefabID = val; }
	void setAiType(AI_TYPE val) { mMyAI = val; }
	void setMeshName(string val) { mMeshName = val; }
	void setResistance(unsigned int val) { resistance = val; }

	unsigned	 getPrefabID()   const { return mEnemyPrefabID; }
	unsigned	 getWeaponPrefabID() const { return mWeaponPrefabID; }
	AI_TYPE		 getAiType()	  const { return mMyAI; }
	std::string	 getMeshName()	  const { return mMeshName; }
	unsigned int getResistance()  const { return resistance; }
private:
	unsigned	resistance;
	unsigned	mEnemyPrefabID;
	string		mMeshName;
	AI_TYPE		mMyAI; 
	unsigned	mWeaponPrefabID;
};