
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
	}
}

WeaponComponent::WeaponComponent() : shooting(false), rateOfFire(150), timeSinceLastShot(0)
{

}

WeaponComponent::WeaponComponent( int weaponPrefabID )
	: shooting(false), rateOfFire(150), timeSinceLastShot(0)
{

}

void WeaponComponent::setWeapon(const WeaponPrefab * prefab )
{
	rateOfFire = prefab->getRateOfFire();
	bulletPrefabID = prefab->getBulletPrefabID();
	weaponName = prefab->getName();
}

