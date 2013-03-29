#pragma once

class EffectPrefab
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

class EffectObject : public GameObject
{
public:
	EffectObject() : GameObject()
	{
		mTTLComponent.setTimeToLive(3000);
	}

	EffectObject( EffectPrefab * objectTemplate, Ogre::SceneManager * _sceneMgr)
		: GameObject()
	{
		mTTLComponent.setTimeToLive(3000);

		static int uniqueID = 0;

		uniqueID++;

		//Custom settings of SceneNode because of being a Particle System, not a Entity (mesh)

		//Creation of particle system
		Ogre::ParticleSystem* particleSystem;
			std::string uniqueName = std::to_string(uniqueID);
			particleSystem = _sceneMgr->createParticleSystem(uniqueName, objectTemplate->getParticleSystemName() );
			//particleSystem->fastForward(1.0);
			particleSystem->setSpeedFactor(3.0);
		mNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
		mNode->attachObject( particleSystem );
	}

	~EffectObject() {

	}

private:
	TimeToLiveComponent mTTLComponent;
};