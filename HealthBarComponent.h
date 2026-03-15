#pragma once

#include "Component.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "raylib.h"


class HealthBarComponent : public Component
{
public:
	float healtBarWidth = 30.0f;
	float healthBarHeight = 10.0f;
	float yOffset = 20.0f;
	Color bg = RED;
	Color health = GREEN;

	void Draw() const override
	{
		auto* transform = whatHasTheComponent->GetComponent<TransformComponent>();
		auto* stats = whatHasTheComponent->GetComponent<StatsComponent>();
		if (!transform || !stats) return;

		float x = transform->position.x - healtBarWidth * 0.5f;
		float y = transform->position.y - transform->radius - yOffset;

		float healthPercent = (float)stats->currentHealth / (float)stats->maxHealth;
		if (healthPercent < 0.0f) healthPercent = 0.0f;

		DrawRectangle((int)x, (int)y, (int)healtBarWidth, (int)healthBarHeight, bg);
		DrawRectangle((int)x, (int)y, (int)(healtBarWidth * healthPercent), (int)healthBarHeight, health);
	}
	

};

