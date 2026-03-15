#pragma once

#include "Component.h"
#include "Entity.h"
#include "StatsComponent.h"



class LevelingComponent : public Component
{
public:
	int xpNeededPerLevel = 30;

	void Update(float deltaTime) override
	{
		auto* stats = whatHasTheComponent->GetComponent<StatsComponent>();
		if (!stats) return;

		while (stats->experience >= xpNeededPerLevel * stats->level)
		{
			stats->experience -= xpNeededPerLevel * stats->level;
			stats->level++;

			stats->maxHealth += 20;
			stats->currentHealth = stats->maxHealth;

			stats->damage += 2;
			stats->fireRate += 0.2f;
			stats->speed += 5.0f;

		}
	}
};