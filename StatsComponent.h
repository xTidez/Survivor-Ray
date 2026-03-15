#pragma once
#include "Component.h"
#include "raylib.h"

class StatsComponent : public Component
{
	public:
		
		float speed;
		int currentHealth;
		int maxHealth;
		int damage;
		float fireRate;
		int experience;
		int level;
		
		StatsComponent()
			: speed (1.0f), currentHealth (10), maxHealth(10), damage(1), fireRate(10.0f), experience(0), level(1)
		{ }



};