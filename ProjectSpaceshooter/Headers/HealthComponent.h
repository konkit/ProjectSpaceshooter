#pragma once

class HealthComponent {
public:
	HealthComponent() : health(100), maxHealth(100)
	{

	}

	void decreaseHealth( int value )	{
		health -= value;
	}

	void restoreToMax()	{
		health = maxHealth;
	}

	int getHealth()	{
		return health;
	}

	bool isDead()	{
		return health < 0;
	}


private:
	int health;
	int maxHealth;
};