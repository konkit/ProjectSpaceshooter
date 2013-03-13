#pragma once

using namespace std;

class EnemyPrefab
{
public:
	EnemyPrefab(unsigned prefabID);
	~EnemyPrefab(void);
	
	void setEnemyPrefabID(unsigned val) { mEnemyPrefabID = val; }
	void setWeaponPrefabID(unsigned val) { mWeaponPrefabID = val; }
	void setAiType(AI_TYPE val) { mMyAI = val; }
	void setMeshName(string val) { mMeshName = val; }
	void setResistance(unsigned int val) { resistance = val; }

	unsigned	 getEnemyPrefabID()   const { return mEnemyPrefabID; }
	unsigned	 getWaeponePrefabID() const { return mWeaponPrefabID; }
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

class EnemyObject : public GameObject
{
public:
	EnemyObject::EnemyObject( EnemyPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);
	~EnemyObject();
	unsigned int mResistance;
private:
//  AI component

};


