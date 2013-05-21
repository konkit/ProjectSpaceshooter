#pragma once
#include "Prefabs.h"


/** Health Component is responsible for storing data about
  * health, resistance from receiving damage etc.
  * It also governs changing it on demand.
  */
class HealthComponent {
public:
	HealthComponent();
	HealthComponent(const PrefabWithCollider * prefab);

	//Decreases health by specified value
	void decreaseHealth( int value );
	//Restores current health amount to max
	void restoreHealthToMax();
	//returns current health value
	int getHealth();
	//returns maximum health value
	int getMaxHealth() const { return maxHealth; }
	//returns true if health amount is below or equal to zero
	bool isDead();
	//returns resistance
	unsigned getResistance() const { return resistance; }
	//sets all fields by values specified in prefab
	void setHealthFromPrefab(const PrefabWithCollider * prefab);

private:
	int health;
	int maxHealth;
	unsigned resistance;
};