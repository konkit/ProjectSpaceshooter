#pragma once


/** Health Component is responsible for storing data about
  * health and changing it on demand.
  *
  */
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