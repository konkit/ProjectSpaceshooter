#pragma once
#include "Prefabs.h"


/** Health Component is responsible for storing data about
  * health and changing it on demand.
  *
  */
class HealthComponent {
public:
	HealthComponent();
	HealthComponent(PrefabWithColider * prefab);

	void decreaseHealth( int value );

	void restoreToMax();

	int getHealth();

	bool isDead();

	int getMaxHealth() const { return maxHealth; }
	void setMaxHealth(int val) { maxHealth = val; }
	unsigned getResistance() const { return resistance; }
	void setResistance(unsigned val) { resistance = val; }
	void setHealthFromPrefab(const PrefabWithColider * prefab);

private:
	int health;
	int maxHealth;
	unsigned resistance;
};