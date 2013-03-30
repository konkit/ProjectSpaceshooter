
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

float WeaponComponent::getPower()
{
	return mPower;
}

void WeaponComponent::setPower( float newPower )
{
	mPower = newPower;
}

WeaponComponent::WeaponComponent( float power ) : mPower(power), shooting(false), rateOfFire(150), timeSinceLastShot(0)
{

}

WeaponComponent::WeaponComponent() : shooting(false), rateOfFire(150), timeSinceLastShot(0)
{

}

