#pragma once
#include "Prefabs.h"


/** Health Component is responsible for storing data about
  * health, resistance from receiving damage etc.
  * It also governs changing it on demand.
  * @author konkit
  */
class HealthComponent {
public:
	/**
	* 
	*
	* @return 
	* @author konkit
	*/
	HealthComponent();
	/**
	* 
	*
	* @return 
	* @param prefab 
	* @author konkit
	*/
	HealthComponent(const PrefabWithCollider * prefab);

	/**
	* Decreases health by specified value
	* @param value 
	* @author konkit
	*/
	void decreaseHealth( int value );
	/**
	* Restores current health amount to max
	* @author konkit
	*/
	void restoreHealthToMax();
	/**
	* @return current health value
	* @author konkit
	*/
	int getHealth();
	/**
	* @return maximum health value
	* @author konkit
	*/
	int getMaxHealth() const { return maxHealth; }
	/**
	* @return true if health amount is below or equal to zero
	* @author konkit
	*/
	bool isDead();
	/**
	* @return resistance
	* @author konkit
	*/
	unsigned getResistance() const { return resistance; }
	/**
	* sets all fields by values specified in prefab
	* @param prefab 
	* @author konkit
	*/
	void setHealthFromPrefab(const PrefabWithCollider * prefab);
private:
	int health;
	int maxHealth;
	unsigned resistance;
};