
bool WeaponComponent::isShooting()
{
	return shooting;
}

void WeaponComponent::unsetShoot()
{
	shooting = false;
}

void WeaponComponent::setShoot( unsigned long currentTime )
{
	if( timeSinceLastShot + rateOfFire < currentTime )	{
		shooting = true;
		timeSinceLastShot = currentTime;
//		std::cout<<"Player = set shoot "<<std::endl;
	}
}

WeaponComponent::WeaponComponent() : shooting(false), rateOfFire(150), timeSinceLastShot(0), bulletPrefabID(1)
{

}

WeaponComponent::WeaponComponent( int weaponPrefabID )
	: shooting(false), rateOfFire(150), timeSinceLastShot(0), bulletPrefabID(1)
{

}

WeaponComponent::WeaponComponent(const WeaponPrefab * prefab )
{
	setWeapon(prefab);
}

void WeaponComponent::setWeapon(const WeaponPrefab * prefab )
{
	shooting = false;
	timeSinceLastShot = 0;
	rateOfFire = prefab->getRateOfFire();
	bulletPrefabID = prefab->getBulletPrefabID();
	weaponName = prefab->getName();
}

