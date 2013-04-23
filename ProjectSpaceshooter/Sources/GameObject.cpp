#include "stdafx.h"
#include "GameObject.h"


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
	//delete mNode; Czy to tu ma byæ?
}

//Creates scene node for gameobject with given mesh name and within scenenode
void GameObject::createSceneNode(std::string meshName, Ogre::SceneManager* sceneMgr)	{
	//init SceneNode
	Ogre::Entity * tmp = sceneMgr->createEntity(meshName);
	mNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(tmp);

	
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


position_struct GameObject::getObjectPosition()
{
	position_struct tmp;
	tmp.position = mNode->getPosition();
	tmp.orientation = mNode->getOrientation();
	return tmp;
}


bool GameObject_WithColider::isColidingWith( GameObject_WithColider * _object )
{
	position_struct my_pos = this->getPositionAndOrientation();
	position_struct oth_pos = _object->getPositionAndOrientation();
	const Collider & oth_coli = _object->getColider();
	return mColider.isCollidingWith(my_pos, oth_coli, oth_pos);
}

GameObject_WithColider::GameObject_WithColider(const PrefabWithColider * prefab, Ogre::SceneManager* sceneMgr )
	: GameObject(prefab, sceneMgr), mColider(prefab->getColider()), mDeadFlag(false)
{

}


GameObject_Movable::GameObject_Movable(const MovablePrefab * prefab, Ogre::SceneManager* sceneMgr )
	:GameObject(prefab, sceneMgr), mPhysicsComponent(prefab)
{

}

GameObject_WithHealth::GameObject_WithHealth(const PrefabWithColider * prefab, Ogre::SceneManager* sceneMgr )
	: GameObject(prefab, sceneMgr), GameObject_WithColider(prefab, sceneMgr), mHealth()
{

}

