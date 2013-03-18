#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject() : mNode(NULL)
{

}

GameObject::GameObject(std::string meshName, Ogre::SceneManager* sceneMgr) : mNode(NULL)
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