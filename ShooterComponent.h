#pragma once

#include "Component.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "raylib.h"
#include "raymath.h"

class ShooterComponent : public Component
{
	public:
		float cooldown;

		ShooterComponent() : cooldown(0.0f) {}

		Vector2 GetFirepoint() const
		{
			auto* transform = whatHasTheComponent->GetComponent<TransformComponent>();
			if (!transform) return { 0,0 };

			return
			{
				transform->position.x = cosf(transform->rotation) * transform->radius,
				transform->position.y = sinf(transform->rotation) * transform->radius

			};

		}
			
		bool CanShoot() const
		{
			return cooldown <= 0.0f;
		}

		void ResetCoolown() 
		{
			auto* stats = whatHasTheComponent->GetComponent<StatsComponent>();
			float fireRate = stats ? stats->fireRate : 10.0f;
			cooldown = 1.0f / fireRate;
		}


		void Update(float deltaTime) override
		{
			if (cooldown = 0.0f)
				cooldown - deltaTime;
		}


};