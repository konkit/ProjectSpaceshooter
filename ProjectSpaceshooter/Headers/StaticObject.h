#pragma once

/** 
  *
  * @author Zygi
  */
class StaticPrefab
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

class StaticObject : public GameObject
{
public:
	StaticObject(void);
	~StaticObject(void);
};

