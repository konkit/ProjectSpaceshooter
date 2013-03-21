#pragma once

class WeaponComponent {
public:


	void setPower(float newPower)	{ power = newPower; }
	float getPower() { return power; }

private:
	float power;
};