#pragma once
#include "Prefabs.h"
#include "TimeToLiveComponent.h"

class EffectObject : public GameObject_WithColider
{
public:
	EffectObject() : GameObject()
	{
		mTTLComponent.setTimeToLive(3.00);
	}

	EffectObject( EffectPrefab * objectTemplate, Ogre::SceneManager * _sceneMgr)
		: GameObject(), GameObject_WithColider(objectTemplate, _sceneMgr)
	{
		mTTLComponent.setTimeToLive(1.50);

		static int uniqueID = 0;

		uniqueID++;

		//Custom settings of SceneNode because of being a Particle System, not a Entity (mesh)

		//Creation of particle system
		Ogre::ParticleSystem* particleSystem;
			std::string uniqueName = std::to_string(uniqueID);
			particleSystem = _sceneMgr->createParticleSystem(uniqueName, objectTemplate->getParticleSystemName() );
			//particleSystem->fastForward(1.0);
			//particleSystem->setSpeedFactor(3.0);
		mNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
		mNode->attachObject( particleSystem );
	}

	~EffectObject() {

	}

	TimeToLiveComponent& getTTLComponent() {
		return mTTLComponent;
	}

	bool isDead()
	{
		if( mTTLComponent.isTimeIsUp()==true )
			return true;

		return false;
	}

	GameObjectType getType() {
		return GameObjectType::effectObject;
	}

	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection ) 
	{
		return false;
	}

	virtual bool kill() {return false;}

private:
	TimeToLiveComponent mTTLComponent;
};