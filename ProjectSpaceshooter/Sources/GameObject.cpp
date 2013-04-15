#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject() : mNode(NULL), mDeadFlag(false)
{

}

GameObject::GameObject(std::string meshName, Ogre::SceneManager* sceneMgr) : mNode(NULL), mDeadFlag(false)
{
	createSceneNode(meshName, sceneMgr);
}

GameObject::~GameObject(void)
{
}

//Creates scene node for gameobject with given mesh name and within scenenode
void GameObject::createSceneNode(std::string meshName, Ogre::SceneManager* sceneMgr)	{
	//init SceneNode
	Ogre::Entity * tmp = sceneMgr->createEntity(meshName);
	mNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(tmp);

	
}

void GameObject::setColider( PrefabWithColider * prefab )
{
	mColiderList = prefab->getColiderList();
}

void GameObject::setMesh( PrefabWithMesh * prefab , Ogre::SceneManager* sceneMgr)
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
