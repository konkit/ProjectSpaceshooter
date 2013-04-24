
bool HealthComponent::isDead()
{
	return health <= 0;
}

int HealthComponent::getHealth()
{
	return health;
}

void HealthComponent::restoreToMax()
{
	health = maxHealth;
}

void HealthComponent::decreaseHealth( int value )
{
	health -= value;
}

HealthComponent::HealthComponent() : health(100), maxHealth(100)
{

}

HealthComponent::HealthComponent(const PrefabWithCollider * prefab )
{
	maxHealth = health = prefab->getMaxHealth();
	resistance = prefab->getResistance();
}

void HealthComponent::setHealthFromPrefab(const PrefabWithCollider * prefab )
{
	maxHealth = health = prefab->getMaxHealth();
	resistance = prefab->getResistance();
}

