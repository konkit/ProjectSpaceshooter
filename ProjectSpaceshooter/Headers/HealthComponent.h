#pragma once

class HealthComponent {
public:
	HealthComponent();

	void decreaseHealth( int value );

	void restoreToMax();

	int getHealth();

	bool isDead();

	int getMaxHealth() const { return maxHealth; }
	void setMaxHealth(int val) { maxHealth = val; }
	unsigned getResistance() const { return resistance; }
	void setResistance(unsigned val) { resistance = val; }

private:
	int health;
	int maxHealth;
	unsigned resistance;
};