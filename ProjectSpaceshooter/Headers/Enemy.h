#pragma once

using namespace std;

class EnemyPrefab
{
public:
	EnemyPrefab(string name);
	~EnemyPrefab(void);
	
	void setEnemyName(std::string val) { mName = val; }
	void setWaeponeName(std::string val) { mWaeponeName = val; }
	void setAiType(AI_TYPE val) { mMyAI = val; }
	void setMeshName(std::string val) { mMeshName = val; }
	void setResistance(unsigned int val) { resistance = val; }

	std::string	 getEnemyName()   const { return mName; }
	std::string	 getWaeponeName() const { return mWaeponeName; }
	AI_TYPE		 getAiType()	  const { return mMyAI; }
	std::string	 getMeshName()	  const { return mMeshName; }
	unsigned int getResistance()  const { return resistance; }
private:
	unsigned int resistance;
	string		 mName;
	string		 mMeshName;
	AI_TYPE		 mMyAI; 
	string		 mWaeponeName;
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


