#pragma once



/** Player class
  * Gameobject representing player's spaceship
  *
  * @author konkit
  */

class Player : public GameObject
{
public:
	Player() : mWeapon(5.0)
	{}
	~Player()	{}
	unsigned int mResistance;

	void setShoot(unsigned long currentTime)	{
		std::cout<<"Player = set shoot "<<std::endl;
		mWeapon.setShoot(currentTime);
	}

	void unsetShoot()	{
		mWeapon.unsetShoot();
	}

	bool isShooting()	{
		return mWeapon.isShooting();
	}

	WeaponComponent& getCurrentWeapon()	{
		return mWeapon;
	}

	HealthComponent& getHealthComponent()	{
		return mHealthComponent;
	}

	bool isDead() {
		if( mHealthComponent.isDead() == true )
			return true;
		if( GameObject::isDead() == true )
			return true;

		return false;
	}

	GameObjectType getType() {
		return GameObjectType::player;
	}

private:  
	WeaponComponent mWeapon;
	HealthComponent mHealthComponent;
};