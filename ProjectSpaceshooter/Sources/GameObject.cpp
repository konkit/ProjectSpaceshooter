#include "stdafx.h"
#include "GameObject.h"

using namespace std;

unsigned GameObject::uniqueID = 0;

GameObject::GameObject() : mNode(NULL)
{
}

GameObject::GameObject(std::string meshName, Ogre::SceneManager* sceneMgr) : mNode(NULL)
{
	createSceneNode(meshName, sceneMgr);
}

GameObject::GameObject(const PrefabWithMesh * prefab, Ogre::SceneManager* sceneMgr)
{
	setMesh(prefab, sceneMgr);
} 

GameObject::~GameObject(void)
{
	if(mNode != NULL)
	{
		Ogre::SceneNode* parent = dynamic_cast<Ogre::SceneNode*>(mNode->getParent());
		if (parent != NULL)
		{
			parent->removeAndDestroyChild(mNode->getName());
		}
	}
}

//Creates scene node for gameobject with given mesh name and within scenenode
void GameObject::createSceneNode(std::string meshName, Ogre::SceneManager* sceneMgr)	{
	//init SceneNode
	uniqueID++;
	mNode = sceneMgr->getRootSceneNode()->createChildSceneNode(std::to_string(uniqueID));
	if (meshName != "")
	{	Ogre::Entity * tmp = sceneMgr->createEntity(meshName);
		mNode->attachObject(tmp);
	}	
}


void GameObject::setMesh(const PrefabWithMesh * prefab , Ogre::SceneManager* sceneMgr)
{
	createSceneNode(prefab->getMeshName().c_str(), sceneMgr);
	mNode->scale(prefab->getScale());
	rotation_struct rot = prefab->getRotation();
	Ogre::Quaternion x_rot(Ogre::Degree(rot.x_rot), Vector3::UNIT_X);
	Ogre::Quaternion y_rot(Ogre::Degree(rot.y_rot), Vector3::UNIT_Y);
	Ogre::Quaternion z_rot(Ogre::Degree(rot.z_rot), Vector3::UNIT_Z);
	Ogre::Quaternion rotation = x_rot * y_rot * z_rot;
	mNode->rotate(rotation);
}



bool GameObject_WithCollider::isColidingWith( GameObject_WithCollider * _object )
{
	position_struct my_pos = this->getPositionAndOrientation();
	position_struct oth_pos = _object->getPositionAndOrientation();
	const Collider & oth_coli = _object->getCollider();
	return mCollider.isCollidingWith(my_pos, oth_coli, oth_pos);
}

GameObject_WithCollider::GameObject_WithCollider(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr )
	: GameObject(prefab, sceneMgr), mCollider(prefab->getCollider()), mDeadFlag(false), mExpolsionEffectID(prefab->getExplosionEffectID())
{

}


GameObject_Movable::GameObject_Movable(const MovablePrefab * prefab, Ogre::SceneManager* sceneMgr )
	:GameObject(prefab, sceneMgr), mPhysicsComponent(prefab), mThrusterNode(NULL)
{
	createThrusters(prefab, sceneMgr);
}

void GameObject_Movable::createThrusters( const MovablePrefab * _prefab, Ogre::SceneManager * _sceneMenager )
{
	string throuserTemplate = _prefab->getThrusterName();
	if (throuserTemplate != "" )
	{
		string name("Thrusters");
		name = name + std::to_string(uniqueID);
		mThrusterNode = mNode->createChildSceneNode(name);
		Ogre::ParticleSystem* particleSystem;
		name = "particle " + std::to_string(uniqueID);
		particleSystem = _sceneMenager->createParticleSystem(name, throuserTemplate);
		mThrusterNode->attachObject( particleSystem );
		mThrusterNode->translate(_prefab->getThrusterOffset());
	}
}

GameObject_WithHealth::GameObject_WithHealth(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr )
	: GameObject(prefab, sceneMgr), GameObject_WithCollider(prefab, sceneMgr), mHealth(prefab)
{

}


std::string ObjectTypeToString( GameObjectType type )
{
	switch (type)
	{
	case GameObjectType::player:
		return string("Player");
	case GameObjectType::core:
		return string("Core");
	case GameObjectType::enemyObject:
		return string("Enemy");
	case GameObjectType::bulletObject:
		return string("Bullet");
	case GameObjectType::staticObject:
		return string("Static");
	case GameObjectType::physicObject:
		return string("Physic");
	case GameObjectType::effectObject:
		return string("Effect");
	default:
		return string("Unknown Object");
	}
}
