#pragma once

class HealthComponent {
public:
	HealthComponent();

	void decreaseHealth( int value );

	void restoreToMax();

	int getHealth();

	bool isDead();


private:
	int health;
	int maxHealth;
};